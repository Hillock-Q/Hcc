#pragma once

#include "CTag.h"
#include "CToken.h"
#include <string>
using std::string;

class Word:public Token
{
public:
	Word(string const &s,int const t,size_t const l=0):Token(t,l),lexeme(s){}
	Word(Word const &rhs,size_t const l):Token(rhs,l),lexeme(rhs.lexeme){}

	~Word(){}
	Word* clone(size_t const l)const{return new Word(*this,l);}
	string toString()const{return lexeme;}

private:
	string const lexeme;
};