#pragma once

#include "CLocalTable.h"
#include "CConstTable.h"
#include "CGlobalTable.h"
#include "CMiddleCode.h"
#include "CAddress.h"
#include "CSection.h"
#include <vector>
using std::vector;
using namespace Compiler;

class Env
{
	typedef size_t instr;	
	typedef vector<instr> instr_list;
	typedef vector<unsigned char> byte_cont;
public:
	static MiddleCode const& getInitCode();
	static ConstTable const& getConstTable();
	static GlobalTable const& getGlobalTable();
	static void ClearUp();		//���������

	bool isVar(string const &name)const;	//�����Ѿ�����Ϊ����
	bool isFun(string const &name)const;	//�����Ѿ�����Ϊ����
	Address getAddress(string const &name)const;	//��ȡָ�������ڱ������ڴ��е���Ե�ַ
	FunInfo* getFunInfo(string const &name);		//��ȡ����������Ϣ	
	FunInfo* getEsFunInfo(string const &name);		//��ȡ���⺯��������Ϣ
	AllocInfo const* getAllocInfo(string const &name)const;		//��ȡ�����ڴ������Ϣ

	void defineFun(string const &name,unsigned char ret_type,vector<VarInfo> const &param_list,size_t line);	//����һ������
	void defineVar(string const &name,VarInfo const &var_info,size_t line,unsigned char sec=s_LOCAL);	//����һ������
	Address Temp(VarInfo const &var_info,unsigned char sec=s_LOCAL);	//����һ����ʱ����

	void Gen(unsigned short opr,unsigned char sec=s_LOCAL);	//�ۼ�����һ���޵�ַָ��
	void Gen(unsigned short opr,Address arg1,unsigned char sec=s_LOCAL);	//�ۼ�����һ������ַָ��
	void Gen(unsigned short opr,Address arg1,Address arg2,unsigned char sec=s_LOCAL);	//�ۼ�����һ��˫��ַָ��
	void Gen(unsigned short opr,Address arg1,Address arg2,Address result,unsigned char sec=s_LOCAL);	//�ۼ�����һ������ַָ��

	size_t getNextInstr(unsigned char sec=s_LOCAL);	//��ȡ��һ��ָ�����Ե�ַ
	void BackPatch(instr_list *pinstrlist,instr ins,unsigned char sec=s_LOCAL);	//����
	unsigned short getLastInstr()const;	//�������һ��ָ����

	Address getAddress(bool const val);		//��ȡbool�����ڳ������ڴ��е���Ե�ַ
	Address getAddress(unsigned char const val);	//��ȡascii�����ڳ������ڴ��е���Ե�ַ
	Address getAddress(int const val);		//��ȡ���ͳ����ڳ������ڴ��е���Ե�ַ
	Address getAddress(double const val);		//��ȡ���㳣���ڳ������ڴ��е���Ե�ַ

	string const& getName();	//��ȡ�����ĺ�����
	void ReName(string const &name);	//���������ĺ�����
	bool especial(string const &name)const;		//��������Ƿ���Ϊ����⺯����

	MiddleCode const& getFunCode();
	LocalTable const& getLocalTable();
	void Clear();	//��վֲ�������������

private:
	static ConstTable c_table;
	static GlobalTable g_table;
	static MiddleCode init_code;

	LocalTable l_table;
	MiddleCode fun_code;
};