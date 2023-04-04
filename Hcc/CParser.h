#pragma once
#include "CLexer.h"
#include "CStackRecord.h"
#include "CEnv.h"
#include "CByteCode.h"
#include "CPretreatment.h"
#include <vector>
#include <list>
#include <map>
#include <set>
using std::vector;
using std::list;
using std::multimap;
using std::set;

class Parser
{
	typedef vector<StackRecord*> PPS;	
	typedef multimap<size_t,string> ErrorRecord;
	typedef map<string,pair<int,bool> > addt_map;
	typedef map<string,pair<int,addt_map> > dev_map;

	typedef list<StackRecord*> body_list;
	typedef body_list::iterator body_itor;
	typedef body_list::reverse_iterator body_ritor;

	typedef set<string> fun_set;	//sys-fun set
	typedef set<string> key_word;	//key-word set

	typedef map<string,VarInfo> var_map;

public:
	Parser();
	~Parser();
	bool parsing(string const &code,dev_map const &dev);			//����:ʵ��һ��������������Ԥ�������
	ErrorRecord const& get_error_record()const;						//��ȡ���󱨸�
	ByteCode const& get_byte_code()const;							//��ȡ�ֽ���
	key_word const& getKeyWord()const;								//��ȡ�ؼ��ּ���
	fun_set const& getFunSet()const;								//��ȡ�⺯������
	FunInfo const* getSignature(string const& name);				//��ȡ����ǩ��
	var_map const& getVars(string const &code,dev_map const &dev);	//��ȡ�ɼ���������

private:
	void init();							//��ʼ��
	void generate_grammar();				//�����������޹��ķ�
	void destroy_grammar();					//�����������޹��ķ�
	void pop();								//��ջ
	void move();							//��ǰ��ȡ�ʷ���Ԫ
	void terminal_error();					//�����ս������
	void non_terminal_error();				//������ս������
	void body_handler(body_list body);		//�������ʽ��
	void getVarSet();						//��ȡ�ɼ���������

private:
	StackRecord *psave;						//�ճ�ջ�ķ��ս����ָ��
	StackRecord *ptop;						//ջ���ķ�����ָ��
	Token *ptoken;							//��ǰ�ʷ���Ԫ
	ErrorRecord	err_record;					//�﷨���������¼
	Pretreatment pre_processor;				//Ԥ������
	Lexer lexer;							//�ʷ�������
	PPS pps;								//Ԥ�����ջ
	Env	context;							//������������	
	ByteCode byte_code;						//�м����ı�ʾ��ʽ: �ֽ���
	var_map vars;							//�ɼ���������
};