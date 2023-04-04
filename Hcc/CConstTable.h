#pragma once

#include "CTable.h"
#include "CSection.h"
#include "CAddress.h"
#include <map>
#include <vector>
using std::map;
using std::vector;
using Compiler::Address;

class ConstTable:public Table
{
	typedef map<bool,size_t> bool_map;
	typedef map<unsigned char,size_t> ascii_map;
	typedef map<int,size_t> number_map;
	typedef map<double,size_t> real_map;
	typedef vector<unsigned char> byte_cont;

public:
	ConstTable():Table(Compiler::s_CONST){}

	Address getAddress(bool const val);		//��ȡbool�����ڳ������ڴ��е���Ե�ַ
	Address getAddress(unsigned char const val);	//��ȡascii�����ڳ������ڴ��е���Ե�ַ
	Address getAddress(int const val);		//��ȡ���ͳ����ڳ������ڴ��е���Ե�ַ
	Address getAddress(double const val);		//��ȡ���㳣���ڳ������ڴ��е���Ե�ַ

	void Clear();
	void BuildByteCode(byte_cont &byte_code)const;	//���ɳ����ڴ������Ϣ���ֽ�����ʽ

private:
	bool_map bool_const;
	ascii_map ascii_const;
	number_map number_const;
	real_map real_const;
};