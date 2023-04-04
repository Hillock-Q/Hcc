#pragma once

#include "CConstTable.h"
#include "CGlobalTable.h"
#include "CLocalTable.h"
#include "CMiddleCode.h"
#include <vector>
#include <map>
#include <set>
using std::map;
using std::set;
using std::vector;
using std::pair;

class ByteCode
{
	typedef set<size_t> fun_set;
	typedef vector<unsigned char> byte_cont;
	typedef map<size_t,pair<byte_cont,byte_cont> > local_cont;

public:
	void BuildConstTableCode(ConstTable const& c_table);
	void BuildGlobalTableCode(GlobalTable const& g_table);
	void BuildInitCode(MiddleCode const& i_code);
	void BuildLocalCode(size_t id,LocalTable const& l_table,MiddleCode const& fun_code);
	fun_set& getCallSet();
	void MakeByteCode(byte_cont &byte_code)const;
	void Clear();

private:
	byte_cont const_data;
	byte_cont global_data;
	byte_cont init_code;
	local_cont local_list;	// <id, <local_data,fun_code> >
	fun_set call_set;
};