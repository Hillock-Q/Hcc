#pragma once

#include "CTag.h"
#include "CAttribute.h"
#include <vector>
#include <string>
#include <map>
using std::vector;
using std::string;
using std::multimap;
using Compiler::Inh_Attr;
using Compiler::Temp_Var;
using Compiler::Syn_Attr;

class Env;
class Token;
class Produce;
class ByteCode;
class StackRecord
{
public:
	typedef multimap<size_t,string> ErrorRecord;
	typedef vector<StackRecord*> PPS;	//‘§≤‚∑÷Œˆ’ª

	typedef Inh_Attr* (*InitInh)();
	typedef Temp_Var* (*InitTemp)();
	typedef Syn_Attr* (*InitSyn)();	

	typedef void (*DelInh)(Inh_Attr *pia);
	typedef void (*DelTemp)(Temp_Var *ptv);
	typedef void (*DelSyn)(Syn_Attr *psa);	

	typedef void (*CopyFun)(Inh_Attr *ps,Inh_Attr *pt);
	typedef void (*ActionFun)(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken);

public:
	virtual ~StackRecord()=0{}

	virtual Compiler::Inh_Attr*	getInhAttr(){return 0;}
	virtual Compiler::Temp_Var*	getTempVar(){return 0;}
	virtual Compiler::Syn_Attr*	getSynAttr(){return 0;}
	virtual void doCopy(Inh_Attr *ps){}
	virtual void Action(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken=0){}

	virtual int const Tag()const{return Compiler::_NON_SIGN;}
	virtual bool isTerminal()const{return false;}
	virtual string getError(Token const *ptoken)const{return string();}
	virtual Produce const* getProduce(Token const *ptoken)const{return 0;}

	virtual StackRecord* clone(CopyFun copy=0,Inh_Attr *pInh=0,DelInh deli=0,ActionFun act=0,Temp_Var *pTemp=0,DelTemp delt=0,Syn_Attr *pSyn=0,DelSyn dels=0)const=0;
};