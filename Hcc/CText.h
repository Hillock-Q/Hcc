#pragma once

#include "CTag.h"
#include <string>
using std::string;

class Text
{
public:
	Text():ptext(0),index(0){}
	void reset(string &code){ptext=&code;index=0;ptext->push_back('\n');}
	char read(){if(index<ptext->size())return (*ptext)[index++]; return Compiler::_END;}

private:
	string *ptext;
	string::size_type index;
};