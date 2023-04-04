#pragma once

#include "CTag.h"
#include "CToken.h"
#include <string>
using std::string;

class Number:public Token
{
public:
	Number(int const v,size_t const l):Token(Compiler::_NUM,l),val(v){}

	~Number(){}
	string toString()const{return Compiler::toString(val);}
	int getValue()const{return val;} //����Ϊ����ӿ�,ʹ�û���ָ�����ʱҪ������ת��

private:
	Number* clone(size_t const l)const{return 0;}

private:
	int const val;
};