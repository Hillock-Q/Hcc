#pragma once

#include <set>
#include <map>
#include <vector>
#include <string>
#include "CByteCode.h"
#include "CParser.h"

using std::set;
using std::map;
using std::pair;
using std::vector;
using std::string;

class CompileManager
{ 
	typedef map<string,pair<int,bool> > addt_map;	//<addr-type,<id1,is_bit_addr> >
	typedef map<string,pair<int,addt_map> > dev_map;	//<dev-name,<id2,<addr-type,<id1,is_bit_addr> > > >
	typedef map<unsigned int,string> use_map;	//<id3,code>
	typedef map<unsigned int,ByteCode> code_map;	//<id3,byte-code>
	//typedef map<unsigned short,map<unsigned short,bool> > dev_addt_map;

	typedef vector<unsigned char> byte_cont;	//byte-code buffer
	typedef multimap<size_t,string> ErrorRecord;	//errors

	typedef set<string> fun_set;	//sys-fun set
	typedef set<string> key_word;	//key-word set

	typedef map<string,VarInfo> var_map;	//�ɼ���������
	
public:
	
	void const* compile(use_map const &in_use,dev_map const &dev,size_t &len);		//�ܱ���

	bool compile(unsigned int code_id,string const &code,dev_map const &dev);	//һ�α���
	ErrorRecord const& getErrorRecord()const;		//��ȡ���󱨸�

	key_word const& getKeyWords()const;		//��ȡ�ؼ��ּ���

	fun_set const& getFunSet()const;	//��ȡ�⺯������
	FunInfo const* getSignature(string const& name);	//��ȡ����ǩ��

	var_map const& getVars(string const &code,dev_map const &dev);		//��ȡ�ɼ���������

private:
	void Modify(unsigned short number);	//�޸��ֽ������
	//void BuildMap(dev_map const& dm,dev_addt_map &dam);	//������ʱӳ���

private:
	code_map pass_code;		//��ǰͨ�������Դ�������ɵ��ֽ��뼯��
	Parser parser;		//������
	byte_cont byte_code;	//�ֽ���
};