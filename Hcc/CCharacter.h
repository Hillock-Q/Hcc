#pragma once

#include "CTag.h"
#include "CToken.h"
#include <string>
using std::string;

class Character:public Token
{
public:
	Character(unsigned char const v,size_t const l):Token(Compiler::_ASCII,l),ascii(v){}

	~Character(){}
	string toString()const{return Compiler::toString(int(ascii));}
	int getValue()const{return ascii;} //����Ϊ����ӿ�,ʹ�û���ָ�����ʱҪ������ת��

private:
	Character* clone(size_t const l)const{return 0;}

private:
	unsigned char const ascii;
};