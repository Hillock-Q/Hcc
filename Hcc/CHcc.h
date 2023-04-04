#pragma once

#include "CCompileManager.h"
#include <set>
#include <map>
#include <vector>
#include <string>

using std::set;
using std::map;
using std::pair;
using std::vector;
using std::string;

class CHcc
{
	//对用户开放如下类型定义
public:
	typedef map<string, pair<int, bool> > addt_map;	//<addr-type,<id1,is_bit_addr> >
	typedef map<string, pair<int, addt_map> > dev_map;	//<dev-name,<id2,<addr-type,<id1,is_bit_addr> > > >
	typedef map<unsigned int, string> use_map;	//<id3,code>

	typedef multimap<size_t, string> ErrorRecord;	//errors

	typedef set<string> fun_set;	//sys-fun set
	typedef set<string> key_word;	//key-word set

	typedef map<string, VarInfo> var_map;	//可见变量集合

public:
	void const* compile(use_map const &in_use, dev_map const &dev, size_t &len);	//总编译

	bool compile(unsigned int code_id, string const &code, dev_map const &dev);	//一次编译
	ErrorRecord const& getErrorRecord();		//获取错误报告

	key_word const& getKeyWords();		//获取关键字集合

	fun_set const& getFunSet();		//获取库函数集合
	FunInfo const* getSignature(string const& name);		//获取函数签名

	var_map const& getVars(string const &code, dev_map const &dev);	//获取可见变量集合


private:
	CompileManager cmgr;
};

