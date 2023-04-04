#include "CGlobalTable.h"
#include "CSysApiDef.h"
#include "CDataType.h"
using namespace Compiler;

GlobalTable::GlobalTable()
:
VarTable(Compiler::s_GLOBAL),
id(1000)
{
	sys_fun_set.clear();

	//调入库函数
	importSysApi();

	//创建特殊函数表
	buildEsFunTable();		
}
GlobalTable::fun_set const& GlobalTable::getFunSet()const
{
	return sys_fun_set;
}
void GlobalTable::Clear()
{
	VarTable::Clear();

	id=1000;

	for(fun_map::const_iterator citor=fun_table.begin();citor!=fun_table.end();)
		if(citor->second.id<1000)
			++citor;
		else
			fun_table.erase(citor++);
}
bool GlobalTable::isFun(string const &name)const
{
	return fun_table.find(name)==fun_table.end() ? false : true;
}
void GlobalTable::defineFun(string const &name,unsigned char ret_type,vector<VarInfo> const &param_list,size_t line)
{
	if(name.empty())
		return;

	//生成函数声明信息
	FunInfo fun_info;
	fun_info.ret_type=ret_type;
	fun_info.param_list=param_list;
	fun_info.line=line;
	fun_info.id=id;

	//插入变量表
	std::pair<fun_map::iterator,bool> pr=fun_table.insert(make_pair(name,fun_info));

	//如果已定义
	if(!pr.second)
	{
		//如果是库函数,直接返回
		if(pr.first->second.id<1000)
			return;

		//以重定义后的上下文继续进行分析
		pr.first->second.line=line;
		pr.first->second.ret_type=ret_type;
		pr.first->second.param_list.clear();
	}	
	else
	{
		//避免无效的递长
		id++;
	}
}
FunInfo* GlobalTable::getFunInfo(string const &name)
{
	//返回函数声明信息
	fun_map::iterator itor=fun_table.find(name);

	return itor==fun_table.end() ? 0 : &(itor->second);
}
FunInfo* GlobalTable::getEsFunInfo(string const &name)
{
	//返回函数声明信息
	fun_map::iterator itor=esfun_table.find(name);

	return itor==esfun_table.end() ? 0 : &(itor->second);
}
bool GlobalTable::especial(string const &name)const
{
	esFunSet::const_iterator citor=esSysApi.find(name);

	if(citor==esSysApi.end())
		return false;

	return true;
}
void GlobalTable::buildEsFunTable()
{
	string name;
	VarInfo vi;
	FunInfo fi;

	//库函数使用0行号
	fi.line=0;

	//对用于形参的类型长度,默认为0
	vi.length=0;


	//type  Get(int  device，int  addr_t，int  addr, key-word);

	name="Get";		

	fi.id=api_Get_bool_offset;

	fi.ret_type=t_BOOL;

	fi.param_list.clear();
	vi.type=t_DEV_NAME;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_REG_TYPE;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_REG_ADDR;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_KEY_WORD;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	esfun_table.insert(make_pair(name,fi));

	sys_fun_set.insert(name);


	//void  GetBlock(int  device，int  addr_t，int  addr，bool  target[ ]，int  index，int  len);

	name="GetBlock";

	fi.id=api_GetBlock_offset;

	fi.ret_type=t_VOID;

	fi.param_list.clear();
	vi.type=t_DEV_NAME;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_REG_TYPE;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_REG_ADDR;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_BOOL;
	vi.is_array=true;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	esfun_table.insert(make_pair(name,fi));

	sys_fun_set.insert(name);


	//void  Set(int  device，int  addr_t，int  addr，bool  val);

	name="Set";

	fi.id=api_Set_offset;

	fi.ret_type=t_VOID;

	fi.param_list.clear();
	vi.type=t_DEV_NAME;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_REG_TYPE;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_REG_ADDR;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_BOOL;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	esfun_table.insert(make_pair(name,fi));	

	sys_fun_set.insert(name);


	//void  SetBlock(int  device，int  addr_t，int  addr，bool  source[ ]，int  index，int  len);

	name="SetBlock";

	fi.id=api_SetBlock_offset;

	fi.ret_type=t_VOID;

	fi.param_list.clear();
	vi.type=t_DEV_NAME;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_REG_TYPE;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_REG_ADDR;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_BOOL;
	vi.is_array=true;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	esfun_table.insert(make_pair(name,fi));

	sys_fun_set.insert(name);


	//int  Out(int  device，char  source [ ]，int  index，int  len);
	name="Out";
	fi.id=api_Out;

	fi.ret_type=t_INT;

	fi.param_list.clear();
	vi.type=t_DEV_NAME;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_CHAR;
	vi.is_array=true;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	esfun_table.insert(make_pair(name,fi));	


	//int  In(int  device，char  target[ ]，int  index，int  len);
	name="In";
	fi.id=api_In;

	fi.ret_type=t_INT;

	fi.param_list.clear();
	vi.type=t_DEV_NAME;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_CHAR;
	vi.is_array=true;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	esfun_table.insert(make_pair(name,fi));	
}
void GlobalTable::importSysApi()
{
	string name;
	VarInfo vi;
	FunInfo fi;


	//库函数使用0行号
	fi.line=0;

	//对用于形参的类型长度,默认为0
	vi.length=0;


	//一.数学运算函数(11)


	//double  Sqrt(double  x);
	name="Sqrt";
	fi.id=api_Sqrt;

	fi.ret_type=t_DOUBLE;

	fi.param_list.clear();
	vi.type=t_DOUBLE;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));


	//double  Sin(double  x);
	name="Sin";
	fi.id=api_Sin;

	fi.ret_type=t_DOUBLE;

	fi.param_list.clear();
	vi.type=t_DOUBLE;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));
	

	//double  Cos(double  x);
	name="Cos";
	fi.id=api_Cos;

	fi.ret_type=t_DOUBLE;

	fi.param_list.clear();
	vi.type=t_DOUBLE;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));
	

	//double  Tan (double  x);
	name="Tan";
	fi.id=api_Tan;

	fi.ret_type=t_DOUBLE;

	fi.param_list.clear();
	vi.type=t_DOUBLE;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));
	

	//double  Cot(double  x);
	name="Cot";
	fi.id=api_Cot;

	fi.ret_type=t_DOUBLE;

	fi.param_list.clear();
	vi.type=t_DOUBLE;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));
	

	//double  Sec(double  x);
	name="Sec";
	fi.id=api_Sec;

	fi.ret_type=t_DOUBLE;

	fi.param_list.clear();
	vi.type=t_DOUBLE;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));
	

	//double  Csc(double  x);
	name="Csc";
	fi.id=api_Csc;

	fi.ret_type=t_DOUBLE;

	fi.param_list.clear();
	vi.type=t_DOUBLE;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));
	

	//double  Asin(double  x);
	name="Asin";
	fi.id=api_Asin;

	fi.ret_type=t_DOUBLE;

	fi.param_list.clear();
	vi.type=t_DOUBLE;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));
	

	//double  Acos(double  x);
	name="Acos";
	fi.id=api_Acos;

	fi.ret_type=t_DOUBLE;

	fi.param_list.clear();
	vi.type=t_DOUBLE;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));
	

	//double  Atan(double  x);
	name="Atan";
	fi.id=api_Atan;

	fi.ret_type=t_DOUBLE;

	fi.param_list.clear();
	vi.type=t_DOUBLE;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));
	

	//int  Rand();
	name="Rand";
	fi.id=api_Rand;

	fi.ret_type=t_INT;

	fi.param_list.clear();

	fun_table.insert(make_pair(name,fi));
	

	//int  Abs(int  x);
	name="Abs";
	fi.id=api_Abs;

	fi.ret_type=t_INT;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));


	//float  fAbs(float  x);
	name="fAbs";
	fi.id=api_fAbs;

	fi.ret_type=t_FLOAT;

	fi.param_list.clear();
	vi.type=t_FLOAT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));

	//double Exp(double x)
	name="Exp";
	fi.id=api_Exp;

	fi.ret_type=t_DOUBLE;

	fi.param_list.clear();
	vi.type=t_DOUBLE;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));

	//double Pow(double x,double y)
	name="Pow";
	fi.id=api_Pow;

	fi.ret_type=t_DOUBLE;

	fi.param_list.clear();
	vi.type=t_DOUBLE;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_DOUBLE;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));

	//double Ln(double x)
	name="Ln";
	fi.id=api_Ln;

	fi.ret_type=t_DOUBLE;

	fi.param_list.clear();
	vi.type=t_DOUBLE;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));

	//double Lg(double x)
	name="Lg";
	fi.id=api_Lg;

	fi.ret_type=t_DOUBLE;

	fi.param_list.clear();
	vi.type=t_DOUBLE;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));




	//二.数据转换函数(6)


	//int  Bin2Bcd(int  x);
	name="Bin2Bcd";
	fi.id=api_Bin2Bcd;

	fi.ret_type=t_INT;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));
	

	//int  Bcd2Bin(int  x);
	name="Bcd2Bin";
	fi.id=api_Bcd2Bin;

	fi.ret_type=t_INT;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));
	

	//void  Dec2Ascii(int  x，char  result[ ]，int  index，int  len);
	name="Dec2Ascii";
	fi.id=api_Dec2Ascii;

	fi.ret_type=t_VOID;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_CHAR;
	vi.is_array=true;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));
	

	//void  Hex2Ascii (int  x，char  result[ ]，int  index，int  len);
	name="Hex2Ascii";
	fi.id=api_Hex2Ascii;

	fi.ret_type=t_VOID;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_CHAR;
	vi.is_array=true;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));
	

	//int  Ascii2Dec(char  array[ ]，int  index，int  len);
	name="Ascii2Dec";
	fi.id=api_Ascii2Dec;

	fi.ret_type=t_INT;

	fi.param_list.clear();
	vi.type=t_CHAR;
	vi.is_array=true;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));
	

	//int  Ascii2Hex(char  array[ ]，int  index，int  len);
	name="Ascii2Hex";
	fi.id=api_Ascii2Hex;

	fi.ret_type=t_INT;

	fi.param_list.clear();
	vi.type=t_CHAR;
	vi.is_array=true;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));
	




	//三.数据操作函数(6)


	//short  SwapByte (short  x);
	name="SwapByte";
	fi.id=api_SwapByte;

	fi.ret_type=t_SHORT;

	fi.param_list.clear();
	vi.type=t_SHORT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));
	

	//int  SwapWord(int  x);
	name="SwapWord";
	fi.id=api_SwapWord;

	fi.ret_type=t_INT;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));
	

	//short  LoByte(short  x);
	name="LoByte";
	fi.id=api_LoByte;

	fi.ret_type=t_SHORT;

	fi.param_list.clear();
	vi.type=t_SHORT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));
	

	//short  HiByte(short  x);
	name="HiByte";
	fi.id=api_HiByte;

	fi.ret_type=t_SHORT;

	fi.param_list.clear();
	vi.type=t_SHORT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));
	

	//int  LoWord (int  x);
	name="LoWord";
	fi.id=api_LoWord;

	fi.ret_type=t_INT;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));
	

	//int  HiWord(int  x);
	name="HiWord";
	fi.id=api_HiWord;

	fi.ret_type=t_INT;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));


	//int Min(int x,int y);
	name="Min";
	fi.id=api_Min;

	fi.ret_type=t_INT;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));


	//int Max(int x,int y);
	name="Max";
	fi.id=api_Max;

	fi.ret_type=t_INT;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));
	




	//四.位状态转换函数(4)


	//bool  GetBit(int  x，int  offset);
	name="GetBit";
	fi.id=api_GetBit;

	fi.ret_type=t_BOOL;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));
	

	//int  SetBitOn(int  x，int  offset);
	name="SetBitOn";
	fi.id=api_SetBitOn;

	fi.ret_type=t_INT;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));
	

	//int  SetBitOff(int  x，int  offset);
	name="SetBitOff";
	fi.id=api_SetBitOff;

	fi.ret_type=t_INT;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));
	

	//int  ReverseBit(int  x，int  offset);
	name="ReverseBit";
	fi.id=api_ReverseBit;

	fi.ret_type=t_INT;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));
	




	//五.通讯相关的函数(6)


	//void  Delay(int  ms);
	name="Delay";
	fi.id=api_Delay;

	fi.ret_type=t_VOID;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));
	

	//int  AddSum (char[ ]，int  index，int  len);
	name="AddSum";
	fi.id=api_AddSum;

	fi.ret_type=t_INT;

	fi.param_list.clear();
	vi.type=t_CHAR;
	vi.is_array=true;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));
	

	//int  XorSum(char[ ]，int  index，int  len);
	name="XorSum";
	fi.id=api_XorSum;

	fi.ret_type=t_INT;

	fi.param_list.clear();
	vi.type=t_CHAR;
	vi.is_array=true;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));
	

	//short  CrcSum (char[ ]，int  index，int  len);
	name="CrcSum";
	fi.id=api_CrcSum;

	fi.ret_type=t_SHORT;

	fi.param_list.clear();
	vi.type=t_CHAR;
	vi.is_array=true;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));
	

	//void  SynTriMacro(int  id);
	name="SynTriMacro";
	fi.id=api_SynTriMacro;

	fi.ret_type=t_VOID;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));
	

	//void  AsynTriMacro(int  id);
	name="AsynTriMacro";
	fi.id=api_AsynTriMacro;

	fi.ret_type=t_VOID;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));


	//int  Out(int  device，char  source [ ]，int  index，int  len);
	name="Out";
	fi.id=api_Out;

	fi.ret_type=t_INT;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_CHAR;
	vi.is_array=true;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));


	//int  In(int  device，char  target[ ]，int  index，int  len);
	name="In";
	fi.id=api_In;

	fi.ret_type=t_INT;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_CHAR;
	vi.is_array=true;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));
	

	//void  Fill(bool  val，bool  result[ ]，int  index，int  len);
	name="Fill";
	fi.id=api_Fill;

	fi.ret_type=t_VOID;

	fi.param_list.clear();
	vi.type=t_BOOL;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_BOOL;
	vi.is_array=true;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));

	//加入特殊函数集合
	esSysApi.insert(name);




	//char ToUpper(char c);
	name="ToUpper";
	fi.id=api_ToUpper;

	fi.ret_type=t_CHAR;

	fi.param_list.clear();
	vi.type=t_CHAR;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));
	

	//char ToLower(char c);
	name="ToLower";
	fi.id=api_ToLower;

	fi.ret_type=t_CHAR;

	fi.param_list.clear();
	vi.type=t_CHAR;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));


	//bool IsUpper(char c);
	name="IsUpper";
	fi.id=api_IsUpper;

	fi.ret_type=t_BOOL;

	fi.param_list.clear();
	vi.type=t_CHAR;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));


	//bool IsLower(char c);
	name="IsLower";
	fi.id=api_IsLower;

	fi.ret_type=t_BOOL;

	fi.param_list.clear();
	vi.type=t_CHAR;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));


	//bool IsSpace(char c);
	name="IsSpace";
	fi.id=api_IsSpace;

	fi.ret_type=t_BOOL;

	fi.param_list.clear();
	vi.type=t_CHAR;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));


	//bool IsAlpha(char c);
	name="IsAlpha";
	fi.id=api_IsAlpha;

	fi.ret_type=t_BOOL;

	fi.param_list.clear();
	vi.type=t_CHAR;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));


	//bool IsDigit(char c);
	name="IsDigit";
	fi.id=api_IsDigit;

	fi.ret_type=t_BOOL;

	fi.param_list.clear();
	vi.type=t_CHAR;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));


	//bool IsAlnum(char c);
	name="IsAlnum";
	fi.id=api_IsAlnum;

	fi.ret_type=t_BOOL;

	fi.param_list.clear();
	vi.type=t_CHAR;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));




	//short GetYear();
	name="GetYear";
	fi.id=api_GetYear;

	fi.ret_type=t_SHORT;

	fi.param_list.clear();

	fun_table.insert(make_pair(name,fi));


	//short GetMonth();
	name="GetMonth";
	fi.id=api_GetMonth;

	fi.ret_type=t_SHORT;

	fi.param_list.clear();

	fun_table.insert(make_pair(name,fi));


	//short GetDay();
	name="GetDay";
	fi.id=api_GetDay;

	fi.ret_type=t_SHORT;

	fi.param_list.clear();

	fun_table.insert(make_pair(name,fi));


	//short GetHour();
	name="GetHour";
	fi.id=api_GetHour;

	fi.ret_type=t_SHORT;

	fi.param_list.clear();

	fun_table.insert(make_pair(name,fi));


	//short GetMinute();
	name="GetMinute";
	fi.id=api_GetMinute;

	fi.ret_type=t_SHORT;

	fi.param_list.clear();

	fun_table.insert(make_pair(name,fi));


	//short GetSecond();
	name="GetSecond";
	fi.id=api_GetSecond;

	fi.ret_type=t_SHORT;

	fi.param_list.clear();

	fun_table.insert(make_pair(name,fi));


	//short GetDayOfWeek();
	name="GetDayOfWeek";
	fi.id=api_GetDayOfWeek;

	fi.ret_type=t_SHORT;

	fi.param_list.clear();

	fun_table.insert(make_pair(name,fi));




	//bool GetLastIoState();
	name="GetLastIoState";
	fi.id=api_GetLastIoState;

	fi.ret_type=t_BOOL;

	fi.param_list.clear();

	fun_table.insert(make_pair(name,fi));
	



	//int StrLen(char s[]);
	name="StrLen";
	fi.id=api_StrLen;

	fi.ret_type=t_INT;

	fi.param_list.clear();
	vi.type=t_CHAR;
	*reinterpret_cast<char*>(&vi.is_array)=3;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));


	//int StrCmp(char s1[],char s2[]);
	name="StrCmp";
	fi.id=api_StrCmp;

	fi.ret_type=t_INT;

	fi.param_list.clear();
	vi.type=t_CHAR;
	*reinterpret_cast<char*>(&vi.is_array)=3;
	fi.param_list.push_back(vi);
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));


	//void StrCpy(char to[],char from[]);
	name="StrCpy";
	fi.id=api_StrCpy;

	fi.ret_type=t_VOID;

	fi.param_list.clear();
	vi.type=t_CHAR;
	*reinterpret_cast<char*>(&vi.is_array)=3;
	fi.param_list.push_back(vi);
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));


	//void StrCat(char s[],char t[]);
	name="StrCat";
	fi.id=api_StrCat;

	fi.ret_type=t_VOID;

	fi.param_list.clear();
	vi.type=t_CHAR;
	*reinterpret_cast<char*>(&vi.is_array)=3;
	fi.param_list.push_back(vi);
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));


	//int StrChr(char s[],char c);
	name="StrChr";
	fi.id=api_StrChr;

	fi.ret_type=t_INT;

	fi.param_list.clear();
	vi.type=t_CHAR;
	*reinterpret_cast<char*>(&vi.is_array)=3;
	fi.param_list.push_back(vi);
	vi.type=t_CHAR;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));


	//int StrStr(char s[],char t[]);
	name="StrStr";
	fi.id=api_StrStr;

	fi.ret_type=t_INT;

	fi.param_list.clear();
	vi.type=t_CHAR;
	*reinterpret_cast<char*>(&vi.is_array)=3;
	fi.param_list.push_back(vi);
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));




	//生成函库数集合
	for(fun_map::const_iterator citor=fun_table.begin();citor!=fun_table.end();++citor)
		sys_fun_set.insert(citor->first);




	//void KeyDown(char k);

	name="KeyDown";
	fi.id=api_KeyDown;

	fi.ret_type=t_VOID;

	fi.param_list.clear();
	vi.type=t_CHAR;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));	


	//void KeyUp(char k);

	name="KeyUp";
	fi.id=api_KeyUp;

	fi.ret_type=t_VOID;

	fi.param_list.clear();
	vi.type=t_CHAR;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));	


	//void KeyPress(char k);

	name="KeyPress";
	fi.id=api_KeyPress;

	fi.ret_type=t_VOID;

	fi.param_list.clear();
	vi.type=t_CHAR;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));	



	//void MouseMove(short x,short y);

	name="MouseMove";
	fi.id=api_MouseMove;

	fi.ret_type=t_VOID;

	fi.param_list.clear();
	vi.type=t_SHORT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_SHORT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));


	//void MouseLeftDown();	

	name="MouseLeftDown";
	fi.id=api_MouseLeftDown;

	fi.ret_type=t_VOID;

	fi.param_list.clear();

	fun_table.insert(make_pair(name,fi));


	//void MouseLeftUp();

	name="MouseLeftUp";
	fi.id=api_MouseLeftUp;

	fi.ret_type=t_VOID;

	fi.param_list.clear();

	fun_table.insert(make_pair(name,fi));


	//void MouseLeftPress();

	name="MouseLeftPress";
	fi.id=api_MouseLeftPress;

	fi.ret_type=t_VOID;

	fi.param_list.clear();

	fun_table.insert(make_pair(name,fi));


	//void MouseRightDown();	

	name="MouseRightDown";
	fi.id=api_MouseRightDown;

	fi.ret_type=t_VOID;

	fi.param_list.clear();

	fun_table.insert(make_pair(name,fi));


	//void MouseRightUp();

	name="MouseRightUp";
	fi.id=api_MouseRightUp;

	fi.ret_type=t_VOID;

	fi.param_list.clear();

	fun_table.insert(make_pair(name,fi));


	//void MouseRightPress();

	name="MouseRightPress";
	fi.id=api_MouseRightPress;

	fi.ret_type=t_VOID;

	fi.param_list.clear();

	fun_table.insert(make_pair(name,fi));




	//bool  Get(int  device，int  addr_t，int  addr, void);

	name="Get";		//为避免Get被重定义,加入一个形式上的定义
	fi.id=api_Get_bool_offset;		//此定义永远不可能用于生成代码,故不必为其分配独立的id,小于1000即可

	fi.ret_type=t_BOOL;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_VOID;		//第四个参数为void，语法上不存在其合法的调用形式
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));


	
	//bool  Get_bool_offset(int  device，int  addr_t，int  addr，int offset);

	name="Get_bool_offset";
	fi.id=api_Get_bool_offset;

	fi.ret_type=t_BOOL;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));


	//char  Get_char_offset(int  device，int  addr_t，int  addr，int offset);

	name="Get_char_offset";
	fi.id=api_Get_char_offset;

	fi.ret_type=t_CHAR;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));


	//short  Get_short_offset(int  device，int  addr_t，int  addr，int offset);

	name="Get_short_offset";
	fi.id=api_Get_short_offset;

	fi.ret_type=t_SHORT;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));


	//int  Get_int_offset(int  device，int  addr_t，int  addr，int offset);

	name="Get_int_offset";
	fi.id=api_Get_int_offset;

	fi.ret_type=t_INT;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));


	//float  Get_float_offset(int  device，int  addr_t，int  addr，int offset);

	name="Get_float_offset";
	fi.id=api_Get_float_offset;

	fi.ret_type=t_FLOAT;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));


	//double  Get_double_offset(int  device，int  addr_t，int  addr，int offset);

	name="Get_double_offset";
	fi.id=api_Get_double_offset;

	fi.ret_type=t_DOUBLE;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));



	//bool  Get_bool_bit(int  device，int  addr_t，int  addr);

	name="Get_bool_bit";
	fi.id=api_Get_bool_bit;

	fi.ret_type=t_BOOL;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));


	//bool  Get_bool_word(int  device，int  addr_t，int  addr);

	name="Get_bool_word";
	fi.id=api_Get_bool_word;

	fi.ret_type=t_BOOL;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));


	//char  Get_char_bit(int  device，int  addr_t，int  addr);

	name="Get_char_bit";
	fi.id=api_Get_char_bit;

	fi.ret_type=t_CHAR;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));


	//char  Get_char_word(int  device，int  addr_t，int  addr);

	name="Get_char_word";
	fi.id=api_Get_char_word;

	fi.ret_type=t_CHAR;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));


	//short  Get_short_bit(int  device，int  addr_t，int  addr);

	name="Get_short_bit";
	fi.id=api_Get_short_bit;

	fi.ret_type=t_SHORT;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));


	//short  Get_short_word(int  device，int  addr_t，int  addr);

	name="Get_short_word";
	fi.id=api_Get_short_word;

	fi.ret_type=t_SHORT;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));


	//int  Get_int_bit(int  device，int  addr_t，int  addr);

	name="Get_int_bit";
	fi.id=api_Get_int_bit;

	fi.ret_type=t_INT;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));

	//int  Get_int_word(int  device，int  addr_t，int  addr);

	name="Get_int_word";
	fi.id=api_Get_int_word;

	fi.ret_type=t_INT;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));


	//float  Get_float_bit(int  device，int  addr_t，int  addr);

	name="Get_float_bit";
	fi.id=api_Get_float_bit;

	fi.ret_type=t_FLOAT;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));

	//float  Get_float_word(int  device，int  addr_t，int  addr);

	name="Get_float_word";
	fi.id=api_Get_float_word;

	fi.ret_type=t_FLOAT;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));


	//double  Get_double_bit(int  device，int  addr_t，int  addr);

	name="Get_double_bit";
	fi.id=api_Get_double_bit;

	fi.ret_type=t_DOUBLE;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));


	//double  Get_double_word(int  device，int  addr_t，int  addr);

	name="Get_double_word";
	fi.id=api_Get_double_word;

	fi.ret_type=t_DOUBLE;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));



	//void  GetBlock(int  device，int  addr_t，int  addr，bool  target[ ]，int  index，int  len, void);

	name="GetBlock";	//为避免GetBlock被重定义,加入一个形式上的定义
	fi.id=api_GetBlock_offset;		//此定义永远不可能用于生成代码,故不必为其分配独立的id,小于1000即可

	fi.ret_type=t_VOID;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_BOOL;
	vi.is_array=true;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_VOID;		//第七个参数为void，语法上不存在其合法的调用形式
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));



	//void  GetBlock_bit(int  device，int  addr_t，int  addr，bool  target[ ]，int  index，int  len);

	name="GetBlock_bit";
	fi.id=api_GetBlock_bit;

	fi.ret_type=t_VOID;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_BOOL;
	vi.is_array=true;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));

	//加入特殊函数集合
	esSysApi.insert(name);


	//void  GetBlock_word(int  device，int  addr_t，int  addr，bool  target[ ]，int  index，int  len);

	name="GetBlock_word";
	fi.id=api_GetBlock_word;

	fi.ret_type=t_VOID;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_BOOL;
	vi.is_array=true;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));

	//加入特殊函数集合
	esSysApi.insert(name);


	//void  GetBlock_offset(int  device，int  addr_t，int  addr，int offset，bool  target[ ]，int  index，int  len);

	name="GetBlock_offset";
	fi.id=api_GetBlock_offset;

	fi.ret_type=t_VOID;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_BOOL;
	vi.is_array=true; 
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));

	//加入特殊函数集合
	esSysApi.insert(name);



	//void  Set(int  device，int  addr_t，int  addr，bool  val, void);

	name="Set";		//为避免Set被重定义,加入一个形式上的定义
	fi.id=api_Set_offset;		//此定义永远不可能用于生成代码,故不必为其分配独立的id,小于1000即可

	fi.ret_type=t_BOOL;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_BOOL;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_VOID;		//第五个参数为void，语法上不存在其合法的调用形式
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));



	//void  Set_bit(int  device，int  addr_t，int  addr，bool  val);

	name="Set_bit";
	fi.id=api_Set_bit;

	fi.ret_type=t_VOID;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_BOOL;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));	


	//void  Set_word(int  device，int  addr_t，int  addr，bool  val);

	name="Set_word";
	fi.id=api_Set_word;

	fi.ret_type=t_VOID;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_BOOL;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));	


	//void  Set_offset(int  device，int  addr_t，int  addr，int offset，bool  val);

	name="Set_offset";
	fi.id=api_Set_offset;

	fi.ret_type=t_VOID;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_BOOL;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));



	//void  SetBlock(int  device，int  addr_t，int  addr，bool  source[ ]，int  index，int  len, void);

	name="SetBlock";	//为避免SetBlock被重定义,加入一个形式上的定义
	fi.id=api_SetBlock_offset;		//此定义永远不可能用于生成代码,故不必为其分配独立的id,小于1000即可

	fi.ret_type=t_VOID;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_BOOL;
	vi.is_array=true;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_VOID;		//第七个参数为void，语法上不存在其合法的调用形式
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));



	//void  SetBlock_bit(int  device，int  addr_t，int  addr，bool  source[ ]，int  index，int  len);

	name="SetBlock_bit";
	fi.id=api_SetBlock_bit;

	fi.ret_type=t_VOID;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_BOOL;
	vi.is_array=true;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));

	//加入特殊函数集合
	esSysApi.insert(name);


	//void  SetBlock_word(int  device，int  addr_t，int  addr，bool  source[ ]，int  index，int  len);

	name="SetBlock_word";
	fi.id=api_SetBlock_word;

	fi.ret_type=t_VOID;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_BOOL;
	vi.is_array=true;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));

	//加入特殊函数集合
	esSysApi.insert(name);


	//void  SetBlock_offset(int  device，int  addr_t，int  addr，int offset，bool  source[ ]，int  index，int  len);

	name="SetBlock_offset";
	fi.id=api_SetBlock_offset;

	fi.ret_type=t_VOID;

	fi.param_list.clear();
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_BOOL;
	vi.is_array=true;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);
	vi.type=t_INT;
	vi.is_array=false;
	fi.param_list.push_back(vi);

	fun_table.insert(make_pair(name,fi));

	//加入特殊函数集合
	esSysApi.insert(name);
}