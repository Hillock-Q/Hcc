#pragma once

namespace Compiler
{
	const size_t SysApiDefBase=0;
	enum SysApiDef
	{
		//一.数学运算函数(11)


		//double  Sqrt(double  x);
		api_Sqrt=SysApiDefBase+0,

		//double  Sin(double  x);
		api_Sin=SysApiDefBase+1,

		//double  Cos(double  x);
		api_Cos=SysApiDefBase+2,

		//double  Tan (double  x);
		api_Tan=SysApiDefBase+3,

		//double  Cot(double  x);
		api_Cot=SysApiDefBase+4,

		//double  Sec(double  x);
		api_Sec=SysApiDefBase+5,

		//double  Csc(double  x);
		api_Csc=SysApiDefBase+6,

		//double  Asin(double  x);
		api_Asin=SysApiDefBase+7,

		//double  Acos(double  x);
		api_Acos=SysApiDefBase+8,

		//double  Atan(double  x);
		api_Atan=SysApiDefBase+9,

		//int  Rand();
		api_Rand=SysApiDefBase+10,

		//int  Abs(int  x);
		api_Abs=SysApiDefBase+101,

		//float  fAbs(float  x);
		api_fAbs=SysApiDefBase+102,

		//double Exp(double x)
		api_Exp=SysApiDefBase+103,

		//double Pow(double x,double y)
		api_Pow=SysApiDefBase+104,

		//double Ln(double x)
		api_Ln=SysApiDefBase+105,

		//double Lg(double x)
		api_Lg=SysApiDefBase+106,




		//二.数据转换函数(6)


		//int  Bin2Bcd(int  x);
		api_Bin2Bcd=SysApiDefBase+11,

		//int  Bcd2Bin(int  x);
		api_Bcd2Bin=SysApiDefBase+12,

		//void  Dec2Ascii(int  x，char  result[ ]，int  index，int  len);
		api_Dec2Ascii=SysApiDefBase+13,

		//void  Hex2Ascii (int  x，char  result[ ]，int  index，int  len);
		api_Hex2Ascii=SysApiDefBase+14,

		//int  Ascii2Dec(char  array[ ]，int  index，int  len);
		api_Ascii2Dec=SysApiDefBase+15,

		//int  Ascii2Hex(char  array[ ]，int  index，int  len);
		api_Ascii2Hex=SysApiDefBase+16,




		//三.数据操作函数(7)


		//void  Fill(bool  val，bool  result[ ]，int  index，int  len);
		api_Fill=SysApiDefBase+17,

		//short  SwapByte (short  x);
		api_SwapByte=SysApiDefBase+18,

		//int  SwapWord(int  x);
		api_SwapWord=SysApiDefBase+19,

		//short  LoByte(short  x);
		api_LoByte=SysApiDefBase+20,

		//short  HiByte(short  x);
		api_HiByte=SysApiDefBase+21,

		//int  LoWord (int  x);
		api_LoWord=SysApiDefBase+22,

		//int  HiWord(int  x);
		api_HiWord=SysApiDefBase+23,

		//int Min(int x,int y);
		api_Min=SysApiDefBase+117,

		//int Max(int x,int y);
		api_Max=SysApiDefBase+118,

		//float fMin(float x,float y);
		api_fMin=SysApiDefBase+119,

		//float fMax(float x,float y);
		api_fMax=SysApiDefBase+120,




		//四.位状态转换函数(4)


		//bool  GetBit(int  x，int  offset);
		api_GetBit=SysApiDefBase+24,

		//int  SetBitOn(int  x，int  offset);
		api_SetBitOn=SysApiDefBase+25,

		//int  SetBitOff(int  x，int  offset);
		api_SetBitOff=SysApiDefBase+26,

		//int  ReverseBit(int  x，int  offset);
		api_ReverseBit=SysApiDefBase+27,




		//五.通讯相关的函数(6)


		//void  Delay(int  ms);
		api_Delay=SysApiDefBase+28,

		//int  AddSum (char[ ]，int  index，int  len);
		api_AddSum=SysApiDefBase+29,

		//int  XorSum(char[ ]，int  index，int  len);
		api_XorSum=SysApiDefBase+30,

		//short  CrcSum (char[ ]，int  index，int  len);
		api_CrcSum=SysApiDefBase+31,

		//void  SynTriMacro(int  id);
		api_SynTriMacro=SysApiDefBase+32,

		//void  AsynTriMacro(int  id);
		api_AsynTriMacro=SysApiDefBase+33,

		//int  Out(int  device，char  source [ ]，int  index，int  len);
		api_Out=SysApiDefBase+34,

		//int  In(int  device，char  target[ ]，int  index，int  len);
		api_In=SysApiDefBase+35,


		//bool  Get_bool_offset(int  device，int  addr_t，int  addr，int offset);
		api_Get_bool_offset=SysApiDefBase+36,

		//char  Get_char_offset(int  device，int  addr_t，int  addr，int offset);
		api_Get_char_offset=SysApiDefBase+37,

		//short  Get_short_offset(int  device，int  addr_t，int  addr，int offset);
		api_Get_short_offset=SysApiDefBase+38,

		//int  Get_int_offset(int  device，int  addr_t，int  addr，int offset);
		api_Get_int_offset=SysApiDefBase+39,

		//float  Get_float_offset(int  device，int  addr_t，int  addr，int offset);
		api_Get_float_offset=SysApiDefBase+40,

		//double  Get_double_offset(int  device，int  addr_t，int  addr，int offset);
		api_Get_double_offset=SysApiDefBase+41,


		//bool  Get_bool_bit(int  device，int  addr_t，int  addr);
		api_Get_bool_bit=SysApiDefBase+42,

		//bool  Get_bool_word(int  device，int  addr_t，int  addr);
		api_Get_bool_word=SysApiDefBase+43,

		//char  Get_char_bit(int  device，int  addr_t，int  addr);
		api_Get_char_bit=SysApiDefBase+44,

		//char  Get_char_word(int  device，int  addr_t，int  addr);
		api_Get_char_word=SysApiDefBase+45,

		//short  Get_short_bit(int  device，int  addr_t，int  addr);
		api_Get_short_bit=SysApiDefBase+46,

		//short  Get_short_word(int  device，int  addr_t，int  addr);
		api_Get_short_word=SysApiDefBase+47,

		//int  Get_int_bit(int  device，int  addr_t，int  addr);
		api_Get_int_bit=SysApiDefBase+48,

		//int  Get_int_word(int  device，int  addr_t，int  addr);
		api_Get_int_word=SysApiDefBase+49,

		//float  Get_float_bit(int  device，int  addr_t，int  addr);
		api_Get_float_bit=SysApiDefBase+50,

		//float  Get_float_word(int  device，int  addr_t，int  addr);
		api_Get_float_word=SysApiDefBase+51,

		//double  Get_double_bit(int  device，int  addr_t，int  addr);
		api_Get_double_bit=SysApiDefBase+52,

		//double  Get_double_word(int  device，int  addr_t，int  addr);
		api_Get_double_word=SysApiDefBase+53,


		//void  GetBlock_bit(int  device，int  addr_t，int  addr，bool  target[ ]，int  index，int  len);
		api_GetBlock_bit=SysApiDefBase+54,

		//void  GetBlock_word(int  device，int  addr_t，int  addr，bool  target[ ]，int  index，int  len);
		api_GetBlock_word=SysApiDefBase+55,

		//void  GetBlock_offset(int  device，int  addr_t，int  addr，int offset，bool  target[ ]，int  index，int  len);
		api_GetBlock_offset=SysApiDefBase+56,


		//void  Set_bit(int  device，int  addr_t，int  addr，bool  val);
		api_Set_bit=SysApiDefBase+57,

		//void  Set_word(int  device，int  addr_t，int  addr，bool  val);
		api_Set_word=SysApiDefBase+58,

		//void  Set_offset(int  device，int  addr_t，int  addr，int offset，bool  val);
		api_Set_offset=SysApiDefBase+59,


		//void  SetBlock_bit(int  device，int  addr_t，int  addr，bool  source[ ]，int  index，int  len);
		api_SetBlock_bit=SysApiDefBase+60,

		//void  SetBlock_word(int  device，int  addr_t，int  addr，bool  source[ ]，int  index，int  len);
		api_SetBlock_word=SysApiDefBase+61,

		//void  SetBlock_offset(int  device，int  addr_t，int  addr，int offset，bool  source[ ]，int  index，int  len);
		api_SetBlock_offset=SysApiDefBase+62,



		//六.宏指令辅助测试接口(10)


		//void KeyDown(char k);
		api_KeyDown=SysApiDefBase+63,

		//void KeyUp(char k);
		api_KeyUp=SysApiDefBase+64,

		//void KeyPress(char k);
		api_KeyPress=SysApiDefBase+65,	


		//void MouseMove(short x,short y);
		api_MouseMove=SysApiDefBase+66,	

		//void MouseLeftDown();	
		api_MouseLeftDown=SysApiDefBase+67,		

		//void MouseLeftUp();
		api_MouseLeftUp=SysApiDefBase+68,	

		//void MouseLeftPress();
		api_MouseLeftPress=SysApiDefBase+69,	

		//void MouseRightDown();	
		api_MouseRightDown=SysApiDefBase+70,		

		//void MouseRightUp();
		api_MouseRightUp=SysApiDefBase+71,		

		//void MouseRightPress();
		api_MouseRightPress=SysApiDefBase+72,



		//七.字符分类及转换函数


		//char ToUpper(char c);
		api_ToUpper=SysApiDefBase+73,

		//char ToLower(char c);
		api_ToLower=SysApiDefBase+74,

		//bool IsUpper(char c);
		api_IsUpper=SysApiDefBase+75,

		//bool IsLower(char c);
		api_IsLower=SysApiDefBase+76,

		//bool IsSpace(char c);
		api_IsSpace=SysApiDefBase+77,

		//bool IsAlpha(char c);
		api_IsAlpha=SysApiDefBase+78,

		//bool IsDigit(char c);
		api_IsDigit=SysApiDefBase+79,

		//bool IsAlnum(char c);
		api_IsAlnum=SysApiDefBase+80,



		//八.字符串处理函数


		//int StrLen(char s[]);
		api_StrLen=SysApiDefBase+81,

		//int StrCmp(char s1[],char s2[]);
		api_StrCmp=SysApiDefBase+82,

		//void StrCpy(char to[],char from[]);
		api_StrCpy=SysApiDefBase+83,

		//void StrCat(char s[],char t[]);
		api_StrCat=SysApiDefBase+84,

		//int StrChr(char s[],char c);
		api_StrChr=SysApiDefBase+85,

		//int StrStr(char s[],char t[]);
		api_StrStr=SysApiDefBase+86,



		//九.系统时间函数


		//short GetYear();
		api_GetYear=SysApiDefBase+87,

		//short GetMonth();
		api_GetMonth=SysApiDefBase+88,

		//short GetDay();
		api_GetDay=SysApiDefBase+89,

		//short GetHour();
		api_GetHour=SysApiDefBase+90,

		//short GetMinute();
		api_GetMinute=SysApiDefBase+91,

		//short GetSecond();
		api_GetSecond=SysApiDefBase+92,

		//short GetDayOfWeek();
		api_GetDayOfWeek=SysApiDefBase+93,



		//十.程序状态获取函数


		//bool GetLastIoState();
		api_GetLastIoState=SysApiDefBase+94,

	};
}