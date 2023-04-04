#pragma once

#include "CStackRecord.h"

class Record:virtual public StackRecord
{
public:
	Record():StackRecord(),copyFun(0),pInhAttr(0),delInh(0){}

	//copy constructor
	Record(Record const &rhs,CopyFun pfn,Inh_Attr *pInh,DelInh deli):StackRecord(rhs),copyFun(pfn),pInhAttr(pInh),delInh(deli){}

	//redefine
	Inh_Attr* getInhAttr(){return pInhAttr;}

	//redefine
	void doCopy(Inh_Attr *ps){if(copyFun)copyFun(ps,pInhAttr);}

	//redefine
	virtual ~Record()=0{if(delInh)delInh(pInhAttr); delete pInhAttr;}

protected:
	Inh_Attr *pInhAttr;	//ºÃ≥– Ù–‘
	DelInh delInh;
	CopyFun copyFun;
};