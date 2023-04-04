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
	Token *const scanning();	//ɨ��:ʵ�ֱ����Զ�������дʷ�ģʽ�ķ�������
	void reset(string &code);	//���÷���Դ����
	key_word const& getKeyWord()const;	//��ȡ�ؼ��ּ���

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