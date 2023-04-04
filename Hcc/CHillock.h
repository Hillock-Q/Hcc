#pragma once
#include <cctype>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include "CEnv.h"
#include "CSection.h"
#include "CDataType.h"
#include "CVarInfo.h"
using std::string;
using std::vector;
using std::list;
using std::pair;

namespace Compiler
{
	typedef size_t instr;
	typedef vector<instr> instr_list;
	typedef list<pair<bool,pair<Address,instr> > > var_instr_list;

	enum NumSys
	{
		DEC=10,
		HEX=16,
		OCT=8
	};

	static unsigned digit(char c,NumSys const ns=DEC)
	{
		return
			ns!=HEX ? 
				c-'0' : 
					c<'A' ? 
						c-'0' : 			
							c<'a' ?
								c-'A'+10 :
									c-'a'+10;
	}

	static bool isDecDigit(char c){return isdigit(c) ? true : false;}
	static bool isHexDigit(char c){return isxdigit(c) ? true : false;}
	static bool isOctDigit(char c){return (isdigit(c) && c<'8');}	

	static bool isLetter(char c){return isalpha(c) ? true : false;}
	static bool isLetterOrDigit(char c){return isalnum(c) ? true : false;}

	static bool isPrint(char c){return isprint(c) ? true : false;}

	static string toString(int i){std::ostringstream oss;oss<<i;return oss.str();}
	static string toString(double d){std::ostringstream oss;oss<<d;return oss.str();}

	template<typename T>
	static void Enqueue(vector<unsigned char> &c,T const val)
	{
		//��������ͨ���ڴ濽��,ת�����ֽ���
		unsigned char const* p=reinterpret_cast<unsigned char const*>(&val);
		for(size_t i=0;i<sizeof(T)/sizeof(unsigned char);++i)
			c.push_back(p[i]);
	}

	static void Append(instr_list **pphead,instr_list **pptail)
	{
		//�����ָ�벻��
		if(*pphead && *pptail)
		{
			for(instr_list::const_iterator citor=(*pptail)->begin();citor!=(*pptail)->end();++citor)
				(*pphead)->push_back(*citor);

			//���β��
			(*pptail)->clear();
		}
	}

	static bool isInteger(unsigned char type)
	{
		switch(type)
		{
		case t_BOOL:
		case t_CHAR:
		case t_SHORT:
		case t_INT:
			return true;
		case t_FLOAT:
		case t_DOUBLE:
		case t_VOID:
		default:
			break;
		}
		return false;
	}

	static bool isExist(var_instr_list const* pvil,Address const &addr)
	{
		for(var_instr_list::const_iterator citor=pvil->begin();citor!=pvil->end();++citor)
			if(addr.section==citor->second.first.section && addr.offset==citor->second.first.offset)
				return true;
		
		return false;
	}

	//����������:int/float/double
	static unsigned char Advance(unsigned char type1)
	{
		if(t_FLOAT==type1 || t_DOUBLE==type1)
			return type1;

		return t_INT;
	}

	//˫��������:int/float/double
	static unsigned char Advance(unsigned char type1,unsigned char type2)
	{
		if(t_DOUBLE==type1 || t_DOUBLE==type2)
			return t_DOUBLE;

		if(t_FLOAT==type1 || t_FLOAT==type2)
			return t_FLOAT;

		return t_INT;
	}

	//�ɼ��������:���ڱ��ʽ���������ͼ��
	static bool Computable(VarInfo const &vi)
	{
		//��void,������
		return t_VOID!=vi.type && !vi.is_array;
	}

	inline bool beequal(bool a,bool b)
	{
		return (a==false)==(b==false);
	}

	//��������:���ں�������ʵ�α��ʽ���ͼ��
	static bool Compatible(VarInfo const &lhs,VarInfo const &rhs)
	{
		//ͬʱ��void,ͬʱΪ�����Ϊ����
		if(t_VOID==lhs.type || t_VOID==rhs.type || !beequal(lhs.is_array,rhs.is_array))
			return false;

		//��Ϊ����,����Ϊͬ������
		if(lhs.is_array)
			return lhs.type==rhs.type;

		//���������;��ɼ���
		return true;
	}

	//��������:����ĳЩ�⺯������ʵ�α��ʽ���ͼ��
	static bool esCompatible(VarInfo const &lhs,VarInfo const &rhs)
	{
		//ͬʱ��void,ͬʱΪ�����Ϊ����
		 return t_VOID!=lhs.type && t_VOID!=rhs.type && beequal(lhs.is_array,rhs.is_array);
	}
}