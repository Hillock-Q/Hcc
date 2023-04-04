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
	//生成文法
	generate_grammar();
}
Parser::~Parser()
{
	//销毁语法分析栈
	while(!pps.empty())
		pop();

	//销毁文法
	destroy_grammar();

	//释放当前词法单元
	delete ptoken;
}
void Parser::generate_grammar()
{
	//生成动作记录
	ActRecord::Generate();

	//生成综合记录
	SynRecord::Generate();

	//生成终结符
	Terminal::Generate();

	//生成非终结符(可推出空串)
	NonTerminalDef::Generate();

	//生成非终结符(不可推出空串)
	NonTerminalSyn::Generate();

	//生成产生式
	Produce::Generate();

	//为非终结符加入产生式
	NonTerminalDef::AddProduce();
	
	//为非终结符加入产生式
	NonTerminalSyn::AddProduce();

	//为非终结符加入同步字符集
	NonTerminalSyn::InitSynSet();
}
void Parser::destroy_grammar()
{
	//销毁产生式
	Produce::Destroy();

	//销毁非终结符(不可推出空串)
	NonTerminalSyn::Destroy();	
	
	//销毁非终结符(可推出空串)
	NonTerminalDef::Destroy();

	//销毁终结符
	Terminal::Destroy();

	//销毁综合记录
	SynRecord::Destroy();

	//销毁动作记录
	ActRecord::Destroy();
}
inline void Parser::pop()
{
	//释放内存
	delete pps.back();

	//出栈
	pps.pop_back();
}

inline void Parser::move()
{
	//释放当前词法单元
	delete ptoken;

	//获取下一个词法单元
	ptoken=lexer.scanning();
}
inline void Parser::terminal_error()
{
	//增加一条错误报告记录
	err_record.insert(make_pair(ptoken->Line(),ptop->getError(ptoken)));

	//出栈
	pop();
}
inline void Parser::non_terminal_error()
{
	//增加一条错误报告记录
	err_record.insert(make_pair(ptoken->Line(),ptop->getError(ptoken)));

	//向下转型
	NonTerminalSyn const* ptemp=dynamic_cast<NonTerminalSyn const*>(ptop);

	//使用恐慌模式进行错误恢复: 忽略输入,直至出现同步字符
	if(ptemp)
		while(!(ptemp->isSynToken(ptoken->Tag())))
			move();
	else
		throw std::exception("error @: void Parser::non_terminal_error()...\n");	//用于调试检测

	//出栈
	pop();
}
inline void Parser::body_handler(body_list body)
{
	//保存栈顶非终结符号指针
	psave=pps.back();

	//栈顶非终结符号出栈
	pps.pop_back();

	//入栈前顺序拷贝继承属性
	for(body_itor bg=body.begin();bg!=body.end();++bg)
		(*bg)->doCopy(psave->getInhAttr());

	//释放内存
	delete psave;

	//赋空指针
	psave=0;

	//产生式体逆序入栈
	for(body_ritor rbg=body.rbegin();rbg!=body.rend();++rbg)
		pps.push_back(*rbg);
}
void Parser::init()
{
	//清空语法分析栈
	while(!pps.empty())
		pop();

	//清空字节码
	byte_code.Clear();

	//清空错误记录
	err_record.clear();

	//清空上下文
	context.Clear();
	Env::ClearUp();

	//结束标志放于栈底
	pps.push_back(Terminal::p_end->clone());

	//开始符号放于栈顶
	pps.push_back(NonTerminalSyn::p_program->clone());

	//更新栈顶
	ptop=pps.back();

	//获取首个词法单元
	move();
}
bool Parser::parsing(string const &code,dev_map const &dev)
{
	//拷贝待分析源代码
	string ccode(code);

	//如果预处理未通过
	if(!pre_processor.preTreat(ccode,dev))
		return false;

	//预处理结果作为编译的输入
	lexer.reset(ccode);	

	//初始化
	init();

	//栈非空
	while(Terminal::p_end->Tag()!=ptop->Tag())
	{
		//栈顶不是文法符号
		if(Compiler::_NON_SIGN==ptop->Tag())
		{
			//执行动作函数
			ptop->Action(pps,err_record,context,byte_code);

			//出栈
			pop();
		}
		//栈顶是终结符号
		else if(ptop->isTerminal())
		{
			//当前词法单元与终结符号匹配
			if(ptop->Tag()==ptoken->Tag())
			{
				//执行动作函数
				ptop->Action(pps,err_record,context,byte_code,ptoken);

				//出栈
				pop();

				//当前词法单元指针前移
				move();
			}
			else
			{
				//处理终结符匹配错误
				terminal_error();
			}
		}
		//栈顶是非终结符号
		else
		{
			//为非终结符号选择产生式
			if(Produce const* ppro=ptop->getProduce(ptoken))
			{
				//处理产生式体
				body_handler(ppro->getBody());
			}
			else
			{
				//处理非终结符产生式匹配错误
				non_terminal_error();
			}
		}

		//更新栈顶
		ptop=pps.back();	///是否需要检查栈非空
	}

	//释放语法分析栈内存
	while(!pps.empty())
		pop();

	//检查main(){}之后是否存在非注释类的文本
	if(-1!=ptoken->Tag())
	{
		//增加一条错误报告记录
		if(err_record.empty())
			err_record.insert(make_pair(ptoken->Line(),"main(){}之后存在非注释类的文本: \""+ptoken->toString()+"...\""));
	}

	//返回编译是否通过
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
	//实现方法:做一次非正规的编译

	//拷贝待分析源代码
	string ccode(code);

	//预处理
	pre_processor.preTreat(ccode,dev);

	//预处理结果作为编译的输入
	lexer.reset(ccode);	

	//初始化
	init();

	//栈非空,或出现终结词法单元
	while(Terminal::p_end->Tag()!=ptop->Tag() && Terminal::p_end->Tag()!=ptoken->Tag())
	{
		//栈顶不是文法符号
		if(Compiler::_NON_SIGN==ptop->Tag())
		{
			//执行动作函数
			ptop->Action(pps,err_record,context,byte_code);

			//出栈
			pop();
		}
		//栈顶是终结符号
		else if(ptop->isTerminal())
		{
			//当前词法单元与终结符号匹配
			if(ptop->Tag()==ptoken->Tag())
			{
				//执行动作函数
				ptop->Action(pps,err_record,context,byte_code,ptoken);

				//出栈
				pop();

				//当前词法单元指针前移
				move();
			}
			else
			{
				//处理终结符匹配错误
				terminal_error();
			}
		}
		//栈顶是非终结符号
		else
		{
			//为非终结符号选择产生式
			if(Produce const* ppro=ptop->getProduce(ptoken))
			{
				//处理产生式体
				body_handler(ppro->getBody());
			}
			else
			{
				//处理非终结符产生式匹配错误
				non_terminal_error();
			}
		}

		//更新栈顶
		ptop=pps.back();	///是否需要检查栈非空
	}

	//获取可见变量集合
	getVarSet();

	//释放语法分析栈内存
	while(!pps.empty())
		pop();

	//返回可见变量集合
	return vars;
}
void Parser::getVarSet()
{
	//清空变量集合
	vars.clear();

	//首先加入全局变量定义
	Env::getGlobalTable().getVarSet(vars);

	//然后追加局部变量定义
	context.getLocalTable().getVarSet(vars);
}