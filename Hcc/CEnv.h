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
	static void ClearUp();		//清空上下文

	bool isVar(string const &name)const;	//名字已经声明为变量
	bool isFun(string const &name)const;	//名字已经声明为函数
	Address getAddress(string const &name)const;	//获取指定变量在变量区内存中的相对地址
	FunInfo* getFunInfo(string const &name);		//获取函数声明信息	
	FunInfo* getEsFunInfo(string const &name);		//获取特殊函数声明信息
	AllocInfo const* getAllocInfo(string const &name)const;		//获取变量内存分配信息

	void defineFun(string const &name,unsigned char ret_type,vector<VarInfo> const &param_list,size_t line);	//声明一个函数
	void defineVar(string const &name,VarInfo const &var_info,size_t line,unsigned char sec=s_LOCAL);	//声明一个变量
	Address Temp(VarInfo const &var_info,unsigned char sec=s_LOCAL);	//声明一个临时变量

	void Gen(unsigned short opr,unsigned char sec=s_LOCAL);	//累加生成一条无地址指令
	void Gen(unsigned short opr,Address arg1,unsigned char sec=s_LOCAL);	//累加生成一条单地址指令
	void Gen(unsigned short opr,Address arg1,Address arg2,unsigned char sec=s_LOCAL);	//累加生成一条双地址指令
	void Gen(unsigned short opr,Address arg1,Address arg2,Address result,unsigned char sec=s_LOCAL);	//累加生成一条三地址指令

	size_t getNextInstr(unsigned char sec=s_LOCAL);	//获取下一条指令的相对地址
	void BackPatch(instr_list *pinstrlist,instr ins,unsigned char sec=s_LOCAL);	//回填
	unsigned short getLastInstr()const;	//返回最后一条指令码

	Address getAddress(bool const val);		//获取bool常量在常量区内存中的相对地址
	Address getAddress(unsigned char const val);	//获取ascii常量在常量区内存中的相对地址
	Address getAddress(int const val);		//获取整型常量在常量区内存中的相对地址
	Address getAddress(double const val);		//获取浮点常量在常量区内存中的相对地址

	string const& getName();	//获取上下文函数名
	void ReName(string const &name);	//重置上下文函数名
	bool especial(string const &name)const;		//检查名字是否被列为特殊库函数名

	MiddleCode const& getFunCode();
	LocalTable const& getLocalTable();
	void Clear();	//清空局部声明的上下文

private:
	static ConstTable c_table;
	static GlobalTable g_table;
	static MiddleCode init_code;

	LocalTable l_table;
	MiddleCode fun_code;
};