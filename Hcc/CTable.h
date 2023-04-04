#pragma once

#include <vector>
using std::vector;

class Table
{
	typedef vector<unsigned char> byte_cont;

public:
	Table(unsigned char sec):section(sec),offset(0){}
	void Clear(){offset=0;}
	void BuildByteCode(byte_cont &byte_code)const;	//���������ڴ������Ϣ���ֽ�����ʽ

protected:
	unsigned char const section;
	size_t offset;
};