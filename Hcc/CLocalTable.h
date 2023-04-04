#pragma once

#include "CSection.h"
#include "CVarTable.h"

class LocalTable:public VarTable
{
public:
	LocalTable(string name=""):VarTable(Compiler::s_LOCAL),fun_name(name){++offset;/*Ϊ��������ֵԤ��offset=0*/}
	void Clear(){fun_name.clear();VarTable::Clear();++offset;/*Ϊ��������ֵԤ��offset=0*/}
	string const& getName(){return fun_name;}	//��ȡ�����ĺ�����
	void ReName(string const &name){fun_name=name;} //���������ĺ�����

private:
	string fun_name;
};