#pragma once

#include "CRecord.h"

class ActRecord:public Record
{
public:
	static ActRecord* p_act;

	static void Generate();
	static void Destroy();

public:
	ActRecord():Record(),actFun(0),pTempVar(0),delTemp(0){}

	//copy constructor
	ActRecord(ActRecord const &rhs,ActionFun act,Temp_Var *pTemp=0,DelTemp delt=0,CopyFun copy=0,Inh_Attr *pInh=0,DelInh deli=0):Record(rhs,copy,pInh,deli),actFun(act),pTempVar(pTemp),delTemp(delt){}

	//redefine
	ActRecord* clone(CopyFun copy=0,Inh_Attr *pInh=0,DelInh deli=0,ActionFun act=0,Temp_Var *pTemp=0,DelTemp delt=0,Syn_Attr *pSyn=0,DelSyn dels=0)const{return new ActRecord(*this,act,pTemp,delt,copy,pInh,deli);}

	//redefine
	void Action(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken=0){if(actFun)actFun(pps,err_record,context,byte_code,cpToken);}

	//redefine
	Temp_Var* getTempVar(){return pTempVar;}

	//redefine
	~ActRecord(){if(delTemp)delTemp(pTempVar); delete pTempVar;}

protected:
	Temp_Var *pTempVar;	//¡Ÿ ±±‰¡ø
	DelTemp delTemp;	
	ActionFun actFun;
};