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
	bool isFun(string const &name)const;	//�����Ѿ�����Ϊ����
	void defineFun(string const &name,unsigned char ret_type,vector<VarInfo> const &param_list,size_t line);	//����һ������
	FunInfo* getFunInfo(string const &name);	//��ȡ����������Ϣ
	FunInfo* getEsFunInfo(string const &name);	//��ȡ���⺯��������Ϣ
	bool especial(string const &name)const;		//��������Ƿ���Ϊ����⺯����
	fun_set const& getFunSet()const;	//��ȡ�⺯������

private:
	void importSysApi();	//����⺯��
	void buildEsFunTable();		//�������⺯����

private:
	unsigned short id;		//������ʶ:(ǰ1000����ʶ[0~999]Ϊ�⺯��Ԥ��)
	fun_map fun_table;		//������: Ϊ��������ṩ������
	esFunSet esSysApi;		//���⺯������: Ϊ�������ò���ƥ���ṩ������
	fun_map esfun_table;	//���⺯����: �ṩ����̨
	fun_set sys_fun_set;	//�⺯������: �ṩ����̨

};