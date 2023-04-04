#pragma once

#include "CSection.h"
#include "CVarTable.h"

class LocalTable:public VarTable
{
public:
	LocalTable(string name=""):VarTable(Compiler::s_LOCAL),fun_name(name){++offset;/*为函数返回值预留offset=0*/}
	void Clear(){fun_name.clear();VarTable::Clear();++offset;/*为函数返回值预留offset=0*/}
	string const& getName(){return fun_name;}	//获取上下文函数名
	void ReName(string const &name){fun_name=name;} //重置上下文函数名

private:
	string fun_name;
};