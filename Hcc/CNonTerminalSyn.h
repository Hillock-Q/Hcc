#pragma once

#include "CNonTerminal.h"
#include <set>
using std::set;
using Compiler::Inh_Attr;

class NonTerminalSyn:public NonTerminal
{
	typedef NonTerminalSyn* n_syn_pt;

public:
	static n_syn_pt p_program;

	static n_syn_pt p_option;
	static n_syn_pt p_option_;

	static n_syn_pt p_decl;

	static n_syn_pt p_b;

	static n_syn_pt p_a;
	static n_syn_pt p_l_;

	static n_syn_pt p_f;
	static n_syn_pt p_params_;
	static n_syn_pt p_param;

	static n_syn_pt p_size;

	static n_syn_pt p_stmt;
	static n_syn_pt p_label;

	static n_syn_pt p_expr;
	static n_syn_pt p_e1;
	static n_syn_pt p_e2;
	static n_syn_pt p_e3;
	static n_syn_pt p_e4;
	static n_syn_pt p_e5;
	static n_syn_pt p_e6;
	static n_syn_pt p_e7;
	static n_syn_pt p_e8;
	static n_syn_pt p_e9;
	static n_syn_pt p_e10;
	static n_syn_pt p_e11;
	static n_syn_pt p_e12;
	static n_syn_pt p_e13;
	static n_syn_pt p_e14;

	static n_syn_pt p_args_;
	static n_syn_pt p_arg;

	static n_syn_pt p_loc;

public:
	NonTerminalSyn(int const t):NonTerminal(t),pstr_err_list(0),psyn_set(0){}

	//copy constructor
	NonTerminalSyn(NonTerminalSyn const &rhs,CopyFun pfn=0,Inh_Attr *pInh=0,DelInh deli=0):StackRecord(rhs),NonTerminal(rhs,pfn,pInh,deli),pstr_err_list(rhs.pstr_err_list),psyn_set(rhs.psyn_set){}

	static void Generate();
	static void Destroy();
	static void AddProduce();
	static void InitSynSet();

	void Append(string const str){pstr_err_list->push_back(str);}
	bool isSynToken(int tag)const{return psyn_set->count(tag) ? true : false;}	

	//redefine
	NonTerminalSyn* clone(CopyFun copy=0,Inh_Attr *pInh=0,DelInh deli=0,ActionFun act=0,Temp_Var *pTemp=0,DelTemp delt=0,Syn_Attr *pSyn=0,DelSyn dels=0)const{return new NonTerminalSyn(*this,copy,pInh,deli);}

	//redefine
	string getError(Token const *ptoken)const;

	//redefine	
	~NonTerminalSyn(){}

private:
	list<string> *pstr_err_list;	//error report
	set<int> *psyn_set;		//sys-set
};