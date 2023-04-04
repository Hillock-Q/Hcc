#include "CEnv.h"

ConstTable Env::c_table;
GlobalTable Env::g_table;
MiddleCode Env::init_code;

MiddleCode const& Env::getInitCode()
{
	return init_code;
}
ConstTable const& Env::getConstTable()
{
	return c_table;
}
GlobalTable const& Env::getGlobalTable()
{
	return g_table;
}
void Env::ClearUp()
{
	c_table.Clear();
	g_table.Clear();
	init_code.Clear();
}
void Env::Clear()
{
	l_table.Clear();
	fun_code.Clear();
}
bool Env::isVar(string const &name)const
{
	return l_table.isVar(name) || g_table.isVar(name);
}
bool Env::isFun(string const &name)const
{
	return g_table.isFun(name);
}
AllocInfo const* Env::getAllocInfo(string const &name)const
{
	return g_table.isVar(name) ? g_table.getAllocInfo(name) : l_table.getAllocInfo(name);
}
FunInfo* Env::getFunInfo(string const &name)
{
	return g_table.getFunInfo(name);
}
FunInfo* Env::getEsFunInfo(string const &name)
{
	return g_table.getEsFunInfo(name);
}
Address Env::getAddress(string const &name)const
{
	return g_table.isVar(name) ? g_table.getAddress(name) : l_table.getAddress(name);
}
MiddleCode const& Env::getFunCode()
{
	return fun_code;
}
LocalTable const& Env::getLocalTable()
{
	return 	l_table;
}
void Env::defineFun(string const &name,unsigned char ret_type,vector<VarInfo> const &param_list,size_t line)
{
	g_table.defineFun(name,ret_type,param_list,line);
}
void Env::defineVar(string const &name,VarInfo const &var_info,size_t line,unsigned char sec)
{
	if(s_LOCAL==sec)
	{
		l_table.defineVar(name,var_info,line);
	}
	else if(s_GLOBAL==sec)
	{
		g_table.defineVar(name,var_info,line);
	}
}
Address Env::Temp(VarInfo const &var_info,unsigned char sec)
{
	Address addr;
	addr.offset=-1;

	if(s_LOCAL==sec)
	{
		//在local table分配空间
		addr=l_table.Temp(var_info);
	}
	else if(s_GLOBAL==sec)
	{
		//在global table分配空间
		addr=g_table.Temp(var_info);
	}

	//打上区域标志
	addr.section=sec;

	return addr;
}
void Env::Gen(unsigned short opr,unsigned char sec)
{
	if(s_LOCAL==sec)
	{
		fun_code.Gen(opr);	
	}
	else if(s_GLOBAL==sec)
	{
		init_code.Gen(opr);
	}
}
void Env::Gen(unsigned short opr,Address arg1,unsigned char sec)
{
	if(s_LOCAL==sec)
	{
		fun_code.Gen(opr,arg1);	
	}
	else if(s_GLOBAL==sec)
	{
		init_code.Gen(opr,arg1);
	}
}
void Env::Gen(unsigned short opr,Address arg1,Address arg2,unsigned char sec)
{
	if(s_LOCAL==sec)
	{
		fun_code.Gen(opr,arg1,arg2);	
	}
	else if(s_GLOBAL==sec)
	{
		init_code.Gen(opr,arg1,arg2);
	}
}
void Env::Gen(unsigned short opr,Address arg1,Address arg2,Address result,unsigned char sec)
{
	if(s_LOCAL==sec)
	{
		fun_code.Gen(opr,arg1,arg2,result);	
	}
	else if(s_GLOBAL==sec)
	{
		init_code.Gen(opr,arg1,arg2,result);
	}
}
size_t Env::getNextInstr(unsigned char sec)
{
	if(s_LOCAL==sec)
	{
		return fun_code.getNextInstr();	
	}
	else if(s_GLOBAL==sec)
	{
		return init_code.getNextInstr();
	}

	return -1;
}
void Env::BackPatch(instr_list *pinstrlist,instr ins,unsigned char sec)
{
	if(s_LOCAL==sec)
	{
		fun_code.BackPatch(pinstrlist,getAddress(int(ins)));	
	}
	else if(s_GLOBAL==sec)
	{
		init_code.BackPatch(pinstrlist,getAddress(int(ins)));
	}
}
unsigned short Env::getLastInstr()const
{
	return fun_code.getLastInstr();
}
Address Env::getAddress(bool const val)
{
	return c_table.getAddress(val);
}
Address Env::getAddress(unsigned char const val)
{
	return c_table.getAddress(val);
}
Address Env::getAddress(int const val)
{
	return c_table.getAddress(val);
}
Address Env::getAddress(double const val)
{
	return c_table.getAddress(val);
}
string const& Env::getName()
{
	return l_table.getName();
}
void Env::ReName(string const &name)
{
	l_table.ReName(name);
}
bool Env::especial(string const &name)const
{
	return g_table.especial(name);
}