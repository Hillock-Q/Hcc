#pragma once

#include "CAddress.h"
#include "CInstructor.h"
#include <vector>
using std::vector;

class MiddleCode
{
	typedef size_t instr;
	typedef vector<instr> instr_list;
	typedef vector<Instructor> ins_cont;
	typedef vector<unsigned char> byte_cont;

public:
	void Clear();	//清空
	void Gen(unsigned short opr);	//累加生成一条无地址指令
	void Gen(unsigned short opr,Address arg1);	//累加生成一条单地址指令
	void Gen(unsigned short opr,Address arg1,Address arg2);	//累加生成一条双地址指令
	void Gen(unsigned short opr,Address arg1,Address arg2,Address result);	//累加生成一条三地址指令
	void BuildByteCode(byte_cont &byte_code)const;	//生成三地址代码的字节码形式
	size_t getNextInstr();	//获取下一条指令的相对地址
	void BackPatch(instr_list *pinstrlist,Address const& addr);	//回填
	unsigned short getLastInstr()const;	//返回最后一条指令码

private:
	ins_cont code;	//三地址代码
};