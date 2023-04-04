#pragma once

#include "CTable.h"
#include "CVarInfo.h"
#include "CAddress.h"
#include <map>
#include <string>
#include <vector>
using std::map;
using std::string;
using std::vector;
using Compiler::VarInfo;
using Compiler::AllocInfo;
using Compiler::Address;

class VarTable:public Table
{
	typedef map<string,VarInfo> var_map2;
	typedef map<string,AllocInfo> var_map;
	typedef vector<unsigned char> byte_cont;

public:
	VarTable(unsigned char sec):Table(sec),temp_cnt(0){}
	void Clear();
	bool isVar(string const &name)const;	//�����Ѿ�����Ϊ����
	void defineVar(string const &name,VarInfo const &var_info,size_t line);	//����һ������
	Address Temp(VarInfo const &var_info);	//����һ����ʱ����,ͬʱ�������ַ
	AllocInfo const* getAllocInfo(string const &name)const;	//��ȡ�����ڴ������Ϣ
	Address getAddress(string const &name)const;	//��ȡָ�������ڱ������ڴ��е���Ե�ַ
	void BuildByteCode(byte_cont &byte_code)const;	//���ɱ����ڴ������Ϣ���ֽ�����ʽ
	void getVarSet(var_map2 &vm)const;	//��ȡ�ɼ���������

private:
	void BuildByteCode(byte_cont &c,VarInfo const &var_info)const;	//���ɵ�һ�����ڴ������Ϣ���ֽ���

protected:
	var_map var_table;

private:
	size_t temp_cnt;
};