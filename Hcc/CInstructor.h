#pragma once

#include "CAddress.h"
#include <vector>
using std::vector;
using Compiler::Address;

//����ַָ�����Ԫʽ��ʾ
class Instructor
{
	typedef size_t instr;
	typedef vector<unsigned char> byte_cont;

public:
	Instructor(unsigned short opr);
	Instructor(unsigned short opr,Address arg1);
	Instructor(unsigned short opr,Address arg1,Address arg2);
	Instructor(unsigned short opr,Address arg1,Address arg2,Address result);

	void BuildByteCode(byte_cont &c)const;	//����һ������ַָ����ֽ���
	unsigned short getOpr()const;	//��ȡָ����
	void BackPatch(Address const& addr);	//������תĿ��

private:
	void BuildByteCode(byte_cont &c,Address const &addr)const;	//����һ����ַ���ֽ���

private:
	unsigned short op;	
	Address lhs;
	Address rhs;
	Address val;
};