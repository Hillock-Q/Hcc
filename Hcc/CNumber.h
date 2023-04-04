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
	int getValue()const{return val;} //不作为基类接口,使用基类指针调用时要求向下转型

private:
	Number* clone(size_t const l)const{return 0;}

private:
	int const val;
};