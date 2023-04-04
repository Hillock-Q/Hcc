#pragma once

#include "CTag.h"
#include "CToken.h"
#include <string>
using std::string;

class Real:public Token
{
public:
	Real(double const v,size_t const l):Token(Compiler::_REAL,l),val(v){}

	~Real(){}
	string toString()const{return Compiler::toString(val);}
	double getValue()const{return val;}	//����Ϊ����ӿ�,ʹ�û���ָ�����ʱҪ������ת��

private:
	Real* clone(size_t const l)const{return 0;}

private:
	double const val;
};