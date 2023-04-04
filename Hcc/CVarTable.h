#pragma once

#include "CTable.h"
#include "CVarInfo.h"
#include "CAddress.h"
#include <map>
#include <string>
#include <vector>
using std::map;
using std::string;
using std::vector;
using Compiler::VarInfo;
using Compiler::AllocInfo;
using Compiler::Address;

class VarTable:public Table
{
	typedef map<string,VarInfo> var_map2;
	typedef map<string,AllocInfo> var_map;
	typedef vector<unsigned char> byte_cont;

public:
	VarTable(unsigned char sec):Table(sec),temp_cnt(0){}
	void Clear();
	bool isVar(string const &name)const;	//名字已经声明为变量
	void defineVar(string const &name,VarInfo const &var_info,size_t line);	//声明一个变量
	Address Temp(VarInfo const &var_info);	//声明一个临时变量,同时返回其地址
	AllocInfo const* getAllocInfo(string const &name)const;	//获取变量内存分配信息
	Address getAddress(string const &name)const;	//获取指定变量在变量区内存中的相对地址
	void BuildByteCode(byte_cont &byte_code)const;	//生成变量内存分配信息的字节码形式
	void getVarSet(var_map2 &vm)const;	//获取可见变量集合

private:
	void BuildByteCode(byte_cont &c,VarInfo const &var_info)const;	//生成单一变量内存分配信息的字节码

protected:
	var_map var_table;

private:
	size_t temp_cnt;
};