#include "CParser.h"
#include "CActRecord.h"
#include "CSynRecord.h"
#include "CTerminal.h"
#include "CNonTerminalSyn.h"
#include "CNonTerminalDef.h"
#include "CProduce.h"
#include <iostream>
using std::cout;
using std::endl;
using std::make_pair;

Parser::Parser()
:
	ptoken(0),
	ptop(0),
	pre_processor(err_record),
	lexer(err_record)
{
	//�����ķ�
	generate_grammar();
}
Parser::~Parser()
{
	//�����﷨����ջ
	while(!pps.empty())
		pop();

	//�����ķ�
	destroy_grammar();

	//�ͷŵ�ǰ�ʷ���Ԫ
	delete ptoken;
}
void Parser::generate_grammar()
{
	//���ɶ�����¼
	ActRecord::Generate();

	//�����ۺϼ�¼
	SynRecord::Generate();

	//�����ս��
	Terminal::Generate();

	//���ɷ��ս��(���Ƴ��մ�)
	NonTerminalDef::Generate();

	//���ɷ��ս��(�����Ƴ��մ�)
	NonTerminalSyn::Generate();

	//���ɲ���ʽ
	Produce::Generate();

	//Ϊ���ս���������ʽ
	NonTerminalDef::AddProduce();
	
	//Ϊ���ս���������ʽ
	NonTerminalSyn::AddProduce();

	//Ϊ���ս������ͬ���ַ���
	NonTerminalSyn::InitSynSet();
}
void Parser::destroy_grammar()
{
	//���ٲ���ʽ
	Produce::Destroy();

	//���ٷ��ս��(�����Ƴ��մ�)
	NonTerminalSyn::Destroy();	
	
	//���ٷ��ս��(���Ƴ��մ�)
	NonTerminalDef::Destroy();

	//�����ս��
	Terminal::Destroy();

	//�����ۺϼ�¼
	SynRecord::Destroy();

	//���ٶ�����¼
	ActRecord::Destroy();
}
inline void Parser::pop()
{
	//�ͷ��ڴ�
	delete pps.back();

	//��ջ
	pps.pop_back();
}

inline void Parser::move()
{
	//�ͷŵ�ǰ�ʷ���Ԫ
	delete ptoken;

	//��ȡ��һ���ʷ���Ԫ
	ptoken=lexer.scanning();
}
inline void Parser::terminal_error()
{
	//����һ�����󱨸��¼
	err_record.insert(make_pair(ptoken->Line(),ptop->getError(ptoken)));

	//��ջ
	pop();
}
inline void Parser::non_terminal_error()
{
	//����һ�����󱨸��¼
	err_record.insert(make_pair(ptoken->Line(),ptop->getError(ptoken)));

	//����ת��
	NonTerminalSyn const* ptemp=dynamic_cast<NonTerminalSyn const*>(ptop);

	//ʹ�ÿֻ�ģʽ���д���ָ�: ��������,ֱ������ͬ���ַ�
	if(ptemp)
		while(!(ptemp->isSynToken(ptoken->Tag())))
			move();
	else
		throw std::exception("error @: void Parser::non_terminal_error()...\n");	//���ڵ��Լ��

	//��ջ
	pop();
}
inline void Parser::body_handler(body_list body)
{
	//����ջ�����ս����ָ��
	psave=pps.back();

	//ջ�����ս���ų�ջ
	pps.pop_back();

	//��ջǰ˳�򿽱��̳�����
	for(body_itor bg=body.begin();bg!=body.end();++bg)
		(*bg)->doCopy(psave->getInhAttr());

	//�ͷ��ڴ�
	delete psave;

	//����ָ��
	psave=0;

	//����ʽ��������ջ
	for(body_ritor rbg=body.rbegin();rbg!=body.rend();++rbg)
		pps.push_back(*rbg);
}
void Parser::init()
{
	//����﷨����ջ
	while(!pps.empty())
		pop();

	//����ֽ���
	byte_code.Clear();

	//��մ����¼
	err_record.clear();

	//���������
	context.Clear();
	Env::ClearUp();

	//������־����ջ��
	pps.push_back(Terminal::p_end->clone());

	//��ʼ���ŷ���ջ��
	pps.push_back(NonTerminalSyn::p_program->clone());

	//����ջ��
	ptop=pps.back();

	//��ȡ�׸��ʷ���Ԫ
	move();
}
bool Parser::parsing(string const &code,dev_map const &dev)
{
	//����������Դ����
	string ccode(code);

	//���Ԥ����δͨ��
	if(!pre_processor.preTreat(ccode,dev))
		return false;

	//Ԥ��������Ϊ���������
	lexer.reset(ccode);	

	//��ʼ��
	init();

	//ջ�ǿ�
	while(Terminal::p_end->Tag()!=ptop->Tag())
	{
		//ջ�������ķ�����
		if(Compiler::_NON_SIGN==ptop->Tag())
		{
			//ִ�ж�������
			ptop->Action(pps,err_record,context,byte_code);

			//��ջ
			pop();
		}
		//ջ�����ս����
		else if(ptop->isTerminal())
		{
			//��ǰ�ʷ���Ԫ���ս����ƥ��
			if(ptop->Tag()==ptoken->Tag())
			{
				//ִ�ж�������
				ptop->Action(pps,err_record,context,byte_code,ptoken);

				//��ջ
				pop();

				//��ǰ�ʷ���Ԫָ��ǰ��
				move();
			}
			else
			{
				//�����ս��ƥ�����
				terminal_error();
			}
		}
		//ջ���Ƿ��ս����
		else
		{
			//Ϊ���ս����ѡ�����ʽ
			if(Produce const* ppro=ptop->getProduce(ptoken))
			{
				//�������ʽ��
				body_handler(ppro->getBody());
			}
			else
			{
				//������ս������ʽƥ�����
				non_terminal_error();
			}
		}

		//����ջ��
		ptop=pps.back();	///�Ƿ���Ҫ���ջ�ǿ�
	}

	//�ͷ��﷨����ջ�ڴ�
	while(!pps.empty())
		pop();

	//���main(){}֮���Ƿ���ڷ�ע������ı�
	if(-1!=ptoken->Tag())
	{
		//����һ�����󱨸��¼
		if(err_record.empty())
			err_record.insert(make_pair(ptoken->Line(),"main(){}֮����ڷ�ע������ı�: \""+ptoken->toString()+"...\""));
	}

	//���ر����Ƿ�ͨ��
	return err_record.empty();
}
Parser::ErrorRecord const& Parser::get_error_record()const
{
	return err_record;
}
ByteCode const& Parser::get_byte_code()const
{
	return byte_code;
}
Parser::key_word const& Parser::getKeyWord()const
{
	return lexer.getKeyWord();
}
Parser::fun_set const& Parser::getFunSet()const
{
	return Env::getGlobalTable().getFunSet();
}
FunInfo const* Parser::getSignature(string const& name)
{
	if(FunInfo const* pf=context.getEsFunInfo(name))
	{
		return pf;
	}
	else
	{
		return context.getFunInfo(name);
	}
}
Parser::var_map const& Parser::getVars(string const &code,dev_map const &dev)
{
	//ʵ�ַ���:��һ�η�����ı���

	//����������Դ����
	string ccode(code);

	//Ԥ����
	pre_processor.preTreat(ccode,dev);

	//Ԥ��������Ϊ���������
	lexer.reset(ccode);	

	//��ʼ��
	init();

	//ջ�ǿ�,������ս�ʷ���Ԫ
	while(Terminal::p_end->Tag()!=ptop->Tag() && Terminal::p_end->Tag()!=ptoken->Tag())
	{
		//ջ�������ķ�����
		if(Compiler::_NON_SIGN==ptop->Tag())
		{
			//ִ�ж�������
			ptop->Action(pps,err_record,context,byte_code);

			//��ջ
			pop();
		}
		//ջ�����ս����
		else if(ptop->isTerminal())
		{
			//��ǰ�ʷ���Ԫ���ս����ƥ��
			if(ptop->Tag()==ptoken->Tag())
			{
				//ִ�ж�������
				ptop->Action(pps,err_record,context,byte_code,ptoken);

				//��ջ
				pop();

				//��ǰ�ʷ���Ԫָ��ǰ��
				move();
			}
			else
			{
				//�����ս��ƥ�����
				terminal_error();
			}
		}
		//ջ���Ƿ��ս����
		else
		{
			//Ϊ���ս����ѡ�����ʽ
			if(Produce const* ppro=ptop->getProduce(ptoken))
			{
				//�������ʽ��
				body_handler(ppro->getBody());
			}
			else
			{
				//������ս������ʽƥ�����
				non_terminal_error();
			}
		}

		//����ջ��
		ptop=pps.back();	///�Ƿ���Ҫ���ջ�ǿ�
	}

	//��ȡ�ɼ���������
	getVarSet();

	//�ͷ��﷨����ջ�ڴ�
	while(!pps.empty())
		pop();

	//���ؿɼ���������
	return vars;
}
void Parser::getVarSet()
{
	//��ձ�������
	vars.clear();

	//���ȼ���ȫ�ֱ�������
	Env::getGlobalTable().getVarSet(vars);

	//Ȼ��׷�Ӿֲ���������
	context.getLocalTable().getVarSet(vars);
}