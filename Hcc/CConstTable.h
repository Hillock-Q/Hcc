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

	Address getAddress(bool const val);		//获取bool常量在常量区内存中的相对地址
	Address getAddress(unsigned char const val);	//获取ascii常量在常量区内存中的相对地址
	Address getAddress(int const val);		//获取整型常量在常量区内存中的相对地址
	Address getAddress(double const val);		//获取浮点常量在常量区内存中的相对地址

	void Clear();
	void BuildByteCode(byte_cont &byte_code)const;	//生成常量内存分配信息的字节码形式

private:
	bool_map bool_const;
	ascii_map ascii_const;
	number_map number_const;
	real_map real_const;
};