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
	bool parsing(string const &code,dev_map const &dev);			//解析:实现一个分析表驱动的预测分析器
	ErrorRecord const& get_error_record()const;						//获取错误报告
	ByteCode const& get_byte_code()const;							//获取字节码
	key_word const& getKeyWord()const;								//获取关键字集合
	fun_set const& getFunSet()const;								//获取库函数集合
	FunInfo const* getSignature(string const& name);				//获取函数签名
	var_map const& getVars(string const &code,dev_map const &dev);	//获取可见变量集合

private:
	void init();							//初始化
	void generate_grammar();				//生成上下文无关文法
	void destroy_grammar();					//销毁上下文无关文法
	void pop();								//出栈
	void move();							//向前获取词法单元
	void terminal_error();					//处理终结符错误
	void non_terminal_error();				//处理非终结符错误
	void body_handler(body_list body);		//处理产生式体
	void getVarSet();						//获取可见变量集合

private:
	StackRecord *psave;						//刚出栈的非终结符号指针
	StackRecord *ptop;						//栈顶文法符号指针
	Token *ptoken;							//当前词法单元
	ErrorRecord	err_record;					//语法分析错误记录
	Pretreatment pre_processor;				//预处理器
	Lexer lexer;							//词法分析器
	PPS pps;								//预测分析栈
	Env	context;							//环境或上下文	
	ByteCode byte_code;						//中间代码的表示形式: 字节码
	var_map vars;							//可见变量集合
};