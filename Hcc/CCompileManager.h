#pragma once

#include <set>
#include <map>
#include <vector>
#include <string>
#include "CByteCode.h"
#include "CParser.h"

using std::set;
using std::map;
using std::pair;
using std::vector;
using std::string;

class CompileManager
{ 
	typedef map<string,pair<int,bool> > addt_map;	//<addr-type,<id1,is_bit_addr> >
	typedef map<string,pair<int,addt_map> > dev_map;	//<dev-name,<id2,<addr-type,<id1,is_bit_addr> > > >
	typedef map<unsigned int,string> use_map;	//<id3,code>
	typedef map<unsigned int,ByteCode> code_map;	//<id3,byte-code>
	//typedef map<unsigned short,map<unsigned short,bool> > dev_addt_map;

	typedef vector<unsigned char> byte_cont;	//byte-code buffer
	typedef multimap<size_t,string> ErrorRecord;	//errors

	typedef set<string> fun_set;	//sys-fun set
	typedef set<string> key_word;	//key-word set

	typedef map<string,VarInfo> var_map;	//可见变量集合
	
public:
	
	void const* compile(use_map const &in_use,dev_map const &dev,size_t &len);		//总编译

	bool compile(unsigned int code_id,string const &code,dev_map const &dev);	//一次编译
	ErrorRecord const& getErrorRecord()const;		//获取错误报告

	key_word const& getKeyWords()const;		//获取关键字集合

	fun_set const& getFunSet()const;	//获取库函数集合
	FunInfo const* getSignature(string const& name);	//获取函数签名

	var_map const& getVars(string const &code,dev_map const &dev);		//获取可见变量集合

private:
	void Modify(unsigned short number);	//修改字节码个数
	//void BuildMap(dev_map const& dm,dev_addt_map &dam);	//创建临时映射表

private:
	code_map pass_code;		//当前通过编译的源代码生成的字节码集合
	Parser parser;		//编译器
	byte_cont byte_code;	//字节码
};