#pragma once

#include "CNonTerminal.h"
using Compiler::Inh_Attr;

class NonTerminalDef:public NonTerminal
{
	typedef NonTerminalDef* n_def_pt;

public:
	static n_def_pt p_options;

	static n_def_pt p_decls;
	static n_def_pt p_decl_;

	static n_def_pt p_opt1;
	static n_def_pt p_l;
	static n_def_pt p_l__;

	static n_def_pt p_v;
	static n_def_pt p_v_;
	static n_def_pt p_opt2;

	static n_def_pt p_params;
	static n_def_pt p_params__;
	static n_def_pt p_tail;
	static n_def_pt p_optexpr1;

	static n_def_pt p_else;
	static n_def_pt p_stmts;
	static n_def_pt p_optexpr2;
	static n_def_pt p_optexpr3;

	static n_def_pt p_expr_;
	static n_def_pt p_e2_;
	static n_def_pt p_e3_;
	static n_def_pt p_e4_;
	static n_def_pt p_e5_;
	static n_def_pt p_e6_;
	static n_def_pt p_e7_;
	static n_def_pt p_e8_;
	static n_def_pt p_e9_;
	static n_def_pt p_e10_;
	static n_def_pt p_e11_;
	static n_def_pt p_e12_;

	static n_def_pt p_t1;
	static n_def_pt p_t2;
	static n_def_pt p_t3;
	static n_def_pt p_t4;
	static n_def_pt p_t5;

	static n_def_pt p_args;
	static n_def_pt p_args__;

	static n_def_pt p_loc_;

public:
	NonTerminalDef(int const t):NonTerminal(t){}

	//copy constructor
	NonTerminalDef(NonTerminalDef const &rhs,CopyFun pfn=0,Inh_Attr *pInh=0,DelInh deli=0):StackRecord(rhs),NonTerminal(rhs,pfn,pInh,deli){}

	//redefine
	NonTerminalDef* clone(CopyFun copy=0,Inh_Attr *pInh=0,DelInh deli=0,ActionFun act=0,Temp_Var *pTemp=0,DelTemp delt=0,Syn_Attr *pSyn=0,DelSyn dels=0)const{return new NonTerminalDef(*this,copy,pInh,deli);}

	//redefine	
	~NonTerminalDef(){}

	static void Generate();
	static void Destroy();
	static void AddProduce();
};