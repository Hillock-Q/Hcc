#pragma once

#include "CSection.h"
#include "CVarTable.h"
#include "CFunInfo.h"
#include <map>
#include <set>
#include <vector>
#include <string>
using std::map;
using std::set;
using std::vector;
using std::string;
using Compiler::VarInfo;
using Compiler::FunInfo;

class GlobalTable:public VarTable
{
	typedef set<string> esFunSet;
	typedef map<string,FunInfo> fun_map;
	typedef set<string> fun_set;	//sys-fun set

public:
	GlobalTable();
	void Clear();
	bool isFun(string const &name)const;	//名字已经声明为函数
	void defineFun(string const &name,unsigned char ret_type,vector<VarInfo> const &param_list,size_t line);	//声明一个函数
	FunInfo* getFunInfo(string const &name);	//获取函数声明信息
	FunInfo* getEsFunInfo(string const &name);	//获取特殊函数声明信息
	bool especial(string const &name)const;		//检查名字是否被列为特殊库函数名
	fun_set const& getFunSet()const;	//获取库函数集合

private:
	void importSysApi();	//调入库函数
	void buildEsFunTable();		//创建特殊函数表

private:
	unsigned short id;		//函数标识:(前1000个标识[0~999]为库函数预留)
	fun_map fun_table;		//函数表: 为编译过程提供上下文
	esFunSet esSysApi;		//特殊函数集合: 为函数调用参数匹配提供上下文
	fun_map esfun_table;	//特殊函数表: 提供给后台
	fun_set sys_fun_set;	//库函数集合: 提供给后台

};