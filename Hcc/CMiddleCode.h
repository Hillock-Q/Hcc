#pragma once

#include "CAddress.h"
#include "CInstructor.h"
#include <vector>
using std::vector;

class MiddleCode
{
	typedef size_t instr;
	typedef vector<instr> instr_list;
	typedef vector<Instructor> ins_cont;
	typedef vector<unsigned char> byte_cont;

public:
	void Clear();	//���
	void Gen(unsigned short opr);	//�ۼ�����һ���޵�ַָ��
	void Gen(unsigned short opr,Address arg1);	//�ۼ�����һ������ַָ��
	void Gen(unsigned short opr,Address arg1,Address arg2);	//�ۼ�����һ��˫��ַָ��
	void Gen(unsigned short opr,Address arg1,Address arg2,Address result);	//�ۼ�����һ������ַָ��
	void BuildByteCode(byte_cont &byte_code)const;	//��������ַ������ֽ�����ʽ
	size_t getNextInstr();	//��ȡ��һ��ָ�����Ե�ַ
	void BackPatch(instr_list *pinstrlist,Address const& addr);	//����
	unsigned short getLastInstr()const;	//�������һ��ָ����

private:
	ins_cont code;	//����ַ����
};