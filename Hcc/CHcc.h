#pragma once

#include "CCompileManager.h"
#include <set>
#include <map>
#include <vector>
#include <string>

using std::set;
using std::map;
using std::pair;
using std::vector;
using std::string;

class CHcc
{
	//���û������������Ͷ���
public:
	typedef map<string, pair<int, bool> > addt_map;	//<addr-type,<id1,is_bit_addr> >
	typedef map<string, pair<int, addt_map> > dev_map;	//<dev-name,<id2,<addr-type,<id1,is_bit_addr> > > >
	typedef map<unsigned int, string> use_map;	//<id3,code>

	typedef multimap<size_t, string> ErrorRecord;	//errors

	typedef set<string> fun_set;	//sys-fun set
	typedef set<string> key_word;	//key-word set

	typedef map<string, VarInfo> var_map;	//�ɼ���������

public:
	void const* compile(use_map const &in_use, dev_map const &dev, size_t &len);	//�ܱ���

	bool compile(unsigned int code_id, string const &code, dev_map const &dev);	//һ�α���
	ErrorRecord const& getErrorRecord();		//��ȡ���󱨸�

	key_word const& getKeyWords();		//��ȡ�ؼ��ּ���

	fun_set const& getFunSet();		//��ȡ�⺯������
	FunInfo const* getSignature(string const& name);		//��ȡ����ǩ��

	var_map const& getVars(string const &code, dev_map const &dev);	//��ȡ�ɼ���������


private:
	CompileManager cmgr;
};

