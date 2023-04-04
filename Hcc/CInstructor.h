#pragma once

#include "CAddress.h"
#include <vector>
using std::vector;
using Compiler::Address;

//三地址指令的四元式表示
class Instructor
{
	typedef size_t instr;
	typedef vector<unsigned char> byte_cont;

public:
	Instructor(unsigned short opr);
	Instructor(unsigned short opr,Address arg1);
	Instructor(unsigned short opr,Address arg1,Address arg2);
	Instructor(unsigned short opr,Address arg1,Address arg2,Address result);

	void BuildByteCode(byte_cont &c)const;	//生成一条三地址指令的字节码
	unsigned short getOpr()const;	//获取指令码
	void BackPatch(Address const& addr);	//回填跳转目标

private:
	void BuildByteCode(byte_cont &c,Address const &addr)const;	//生成一个地址的字节码

private:
	unsigned short op;	
	Address lhs;
	Address rhs;
	Address val;
};