#pragma once

#include "CActRecord.h"

class SynRecord:public ActRecord
{
public:
	static SynRecord* p_syn;

	static void Generate();
	static void Destroy();

public:
	SynRecord():ActRecord(),pSynAttr(0),delSyn(0){}

	//copy constructor
	SynRecord(SynRecord const &rhs,Syn_Attr *pSyn,DelSyn dels,ActionFun act,Temp_Var *pTemp=0,DelTemp delt=0,CopyFun copy=0,Inh_Attr *pInh=0,DelInh deli=0):ActRecord(rhs,act,pTemp,delt,copy,pInh,deli),pSynAttr(pSyn),delSyn(dels){}

	//redefine
	SynRecord* clone(CopyFun copy=0,Inh_Attr *pInh=0,DelInh deli=0,ActionFun act=0,Temp_Var *pTemp=0,DelTemp delt=0,Syn_Attr *pSyn=0,DelSyn dels=0)const{return new SynRecord(*this,pSyn,dels,act,pTemp,delt,copy,pInh,deli);}

	//redefine
	Syn_Attr* getSynAttr(){return pSynAttr;}

	//redefine
	~SynRecord(){if(delSyn)delSyn(pSynAttr); delete pSynAttr;}	

private:
	Syn_Attr *pSynAttr;	//◊€∫œ Ù–‘
	DelSyn delSyn;
};