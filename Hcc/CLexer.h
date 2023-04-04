#pragma once

#include "CText.h"
#include "CToken.h"
#include "CWord.h"
#include <map>
#include <set>
using std::string;
using std::set;
using std::multimap;

class Lexer
{
	typedef multimap<size_t,string> ErrorRecord;
	typedef std::map<string,Token*> token_table;
	typedef set<string> key_word;

public:
	Lexer(ErrorRecord &err_record);	
	~Lexer();
	Token *const scanning();	//扫描:实现本语言定义的所有词法模式的分析过程
	void reset(string &code);	//重置分析源代码
	key_word const& getKeyWord()const;	//获取关键字集合

private:
	void reserve(Word *const pw);
	void read();
	void error(string s);
	void error(string s,char c,string s2);

private:
	char peek;
	size_t line;	
	ErrorRecord &err_record;
	Text text;
	token_table tokens;	
	key_word key_words;
};