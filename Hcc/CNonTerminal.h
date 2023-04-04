#pragma once

#include "CSign.h"
#include "CRecord.h"
#include "CProduce.h"
#include "CTerminal.h"
#include <set>
#include <list>
using std::set;
using std::list;

//class Produce;
class NonTerminal:public Sign,public Record
{
protected:
	typedef list<std::pair<Produce*,set<int> > > produce_list; 
public:
	NonTerminal(int const t):Sign(t){}

	//copy constructor
	NonTerminal(NonTerminal const &rhs,CopyFun pfn,Inh_Attr *pInh,DelInh deli):StackRecord(rhs),Sign(rhs),Record(rhs,pfn,pInh,deli),ppl(rhs.ppl){}

	//redefine	
	~NonTerminal()=0{}

	//redefine	
	Produce const* getProduce(Token const *ptoken)const;

	//use Sign define
	int const Tag()const{return Sign::Tag();}

	//use Record define
	void doCopy(Inh_Attr *ps){Record::doCopy(ps);}
	Compiler::Inh_Attr*	getInhAttr(){return Record::getInhAttr();}

	//use StackRecord define	
	bool isTerminal()const{return StackRecord::isTerminal();}
	Compiler::Temp_Var*	getTempVar(){return StackRecord::getTempVar();}
	Compiler::Syn_Attr*	getSynAttr(){return StackRecord::getSynAttr();}
	void Action(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken){StackRecord::Action(pps,err_record,context,byte_code,cpToken);}
	string getError(Token const *ptoken)const{return StackRecord::getError(ptoken);}

protected:
	produce_list *ppl;
};