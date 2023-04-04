#pragma once

#include <string>
using std::string;

class Token
{
public:	
	Token(int const t,size_t const l):tag(t),line(l){}
	Token(Token const &rhs,size_t const l):tag(rhs.tag),line(l){}
	int const Tag()const{return tag;}
	size_t const Line()const{return line;}

	virtual ~Token(){}
	virtual Token* clone(size_t const l)const{return 0;}
	virtual string toString()const{string s;s.push_back(char(tag));return s;}

private:
	int const tag;
	size_t const line;
};