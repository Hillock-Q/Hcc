#pragma once

#include "CStackRecord.h"
#include "CNonTerminal.h"
#include <list>
using std::pair;
using std::list;

class NonTerminal;
class Produce
{	
	struct CloneArgs
	{
		StackRecord::InitInh initInh;
		StackRecord::InitTemp initTemp;
		StackRecord::InitSyn initSyn;

		StackRecord::DelInh delInh;
		StackRecord::DelTemp delTemp;
		StackRecord::DelSyn delSyn;

		StackRecord::ActionFun act;
		StackRecord::CopyFun copy;

		CloneArgs(StackRecord::CopyFun copy_pfn=0,StackRecord::InitInh iniI=0,StackRecord::DelInh deli=0,StackRecord::ActionFun act_pfn=0,StackRecord::InitTemp iniT=0,StackRecord::DelTemp delt=0,StackRecord::InitSyn iniS=0,StackRecord::DelSyn dels=0):copy(copy_pfn),initInh(iniI),delInh(deli),act(act_pfn),initTemp(iniT),delTemp(delt),initSyn(iniS),delSyn(dels){}
	};

	typedef Produce* p_pt;
	typedef list<StackRecord*> bodylist;
	typedef list<pair<StackRecord*,CloneArgs> > CloneArgsList;

public: 
	static p_pt p_p_program;	//	options main( ){decls stmts}

	static p_pt p_p_options1;	//	option options
	static p_pt p_p_options2;	//	¦Å	
	static p_pt p_p_option1;	//	void id F
	static p_pt p_p_option2;	//	B id option'
	static p_pt p_p_option_1;	//	F
	static p_pt p_p_option_2;	//	decl';

	static p_pt p_p_decls1;		//	decl decls
	static p_pt p_p_decls2;		//	¦Å
	static p_pt p_p_decl;		//	B id decl';
	static p_pt p_p_decl_1;		//	A
	static p_pt p_p_decl_2;		//	V

	static p_pt p_p_b1;			//	bool
	static p_pt p_p_b2;			//	char
	static p_pt p_p_b3;			//	short
	static p_pt p_p_b4;			//	int
	static p_pt p_p_b5;			//	float
	static p_pt p_p_b6;			//	double

	static p_pt p_p_a;			//	[size]Opt1
	static p_pt p_p_opt1A;		//	={L}
	static p_pt p_p_opt1B;		//	¦Å
	static p_pt p_p_l1;			//	L'
	static p_pt p_p_l2;			//	¦Å
	static p_pt p_p_l_;			//	e1 L"
	static p_pt p_p_l__1;		//	,L' 
	static p_pt p_p_l__2;		//	¦Å

	static p_pt p_p_v;			//	Opt2 V'
	static p_pt p_p_v_1;		//	,id Opt2 V'
	static p_pt p_p_v_2;		//	¦Å
	static p_pt p_p_opt2A;		//	=e1
	static p_pt p_p_opt2B;		//	¦Å

	static p_pt p_p_f;			//	(params){decls stmts}
	static p_pt p_p_params1;	//	params'
	static p_pt p_p_params2;	//	¦Å
	static p_pt p_p_params_;	//	param params"
	static p_pt p_p_params__1;	//	,params'
	static p_pt p_p_params__2;	//	¦Å
	static p_pt p_p_param;		//	B id tail
	static p_pt p_p_tail1;		//	[optexpr1]
	static p_pt p_p_tail2;		//	¦Å
	static p_pt p_p_optexpr1A;	//	size
	static p_pt p_p_optexpr1B;	//	¦Å
	static p_pt p_p_size1;		//	num
	static p_pt p_p_size2;		//	ascii

	static p_pt p_p_stmt1;		//	;
	static p_pt p_p_stmt2;		//	expr;
	static p_pt p_p_stmt3;		//	if(expr)stmt E
	static p_pt p_p_stmt4;		//	while(expr)stmt
	static p_pt p_p_stmt5;		//	do stmt while(expr);
	static p_pt p_p_stmt6;		//	break;
	static p_pt p_p_stmt7;		//	continue;
	static p_pt p_p_stmt8;		//	return optexpr3;
	static p_pt p_p_stmt9;		//	for(optexpr2;optexpr2;optexpr2)stmt
	static p_pt p_p_stmt10;		//	switch(expr)stmt
	static p_pt p_p_stmt11;		//	case label: stmt
	static p_pt p_p_stmt12;		//	default: stmt
	static p_pt p_p_stmt13;		//	{stmts}
	static p_pt p_p_else1;		//	else stmt
	static p_pt p_p_else2;		//	¦Å
	static p_pt p_p_stmts1;		//	stmt stmts
	static p_pt p_p_stmts2;		//	¦Å
	static p_pt p_p_optexpr2A;	//	expr
	static p_pt p_p_optexpr2B;	//	¦Å
	static p_pt p_p_optexpr3A;	//	expr
	static p_pt p_p_optexpr3B;	//	¦Å
	static p_pt p_p_label1;		//	false
	static p_pt p_p_label2;		//	true
	static p_pt p_p_label3;		//	ascii
	static p_pt p_p_label4;		//	num
	static p_pt p_p_label5;		//	-num

	static p_pt p_p_expr;		// e1 expr'
	static p_pt p_p_expr_1;		// ,e1 expr'
	static p_pt p_p_expr_2;		// ¦Å

	static p_pt p_p_e1A;		// id T1
	static p_pt p_p_e1B;		// e2

	static p_pt p_p_e2;			// e3 e2'
	static p_pt p_p_e2_1;		// ?e3:e2
	static p_pt p_p_e2_2;		// ¦Å

	static p_pt p_p_e3;			// e4 e3'
	static p_pt p_p_e3_1;		// ||e4 e3'
	static p_pt p_p_e3_2;		// ¦Å

	static p_pt p_p_e4;			// e5 e4'
	static p_pt p_p_e4_1;		// &&e5 e4'
	static p_pt p_p_e4_2;		// ¦Å

	static p_pt p_p_e5;			// e6 e5'
	static p_pt p_p_e5_1;		// |e6 e5'
	static p_pt p_p_e5_2;		// ¦Å

	static p_pt p_p_e6;			// e7 e6'
	static p_pt p_p_e6_1;		// ^e7 e6'
	static p_pt p_p_e6_2;		// ¦Å

	static p_pt p_p_e7;			// e8 e7'
	static p_pt p_p_e7_1;		// &e8 e7'
	static p_pt p_p_e7_2;		// ¦Å

	static p_pt p_p_e8;			// e9 e8'
	static p_pt p_p_e8_1;		// ==e9 e8'
	static p_pt p_p_e8_2;		// !=e9 e8'
	static p_pt p_p_e8_3;		// ¦Å

	static p_pt p_p_e9;			// e10 e9'
	static p_pt p_p_e9_1;		// <e10 e9'
	static p_pt p_p_e9_2;		// <=e10 e9'
	static p_pt p_p_e9_3;		// >e10 e9'
	static p_pt p_p_e9_4;		// >=e10 e9'
	static p_pt p_p_e9_5;		// ¦Å

	static p_pt p_p_e10;		// e11 e10'
	static p_pt p_p_e10_1;		// <<e11 e10'
	static p_pt p_p_e10_2;		// >>e11 e10'
	static p_pt p_p_e10_3;		// ¦Å

	static p_pt p_p_e11;		// e12 e11'
	static p_pt p_p_e11_1;		// +e12 e11'
	static p_pt p_p_e11_2;		// -e12 e11'
	static p_pt p_p_e11_3;		// ¦Å

	static p_pt p_p_e12;		// e13 e12'
	static p_pt p_p_e12_1;		// *e13 e12'
	static p_pt p_p_e12_2;		// /e13 e12'
	static p_pt p_p_e12_3;		// %e13 e12'
	static p_pt p_p_e12_4;		// ¦Å

	static p_pt p_p_e13A;		// ~e13
	static p_pt p_p_e13B;		// !e13
	static p_pt p_p_e13C;		// -e13
	static p_pt p_p_e13D;		// +e13
	static p_pt p_p_e13E;		// e14

	static p_pt p_p_e14A;		// true
	static p_pt p_p_e14B;		// false
	static p_pt p_p_e14C;		// ascii
	static p_pt p_p_e14D;		// num
	static p_pt p_p_e14E;		// real
	static p_pt p_p_e14F;		// ++loc
	static p_pt p_p_e14G;		// --loc
	static p_pt p_p_e14H;		// (expr)
	static p_pt p_p_e14I;		// id T3

	static p_pt p_p_t1A;		// ++T5
	static p_pt p_p_t1B;		// --T5
	static p_pt p_p_t1C;		// (args)T5
	static p_pt p_p_t1D;		// [expr]T2
	static p_pt p_p_t1E;		// =e1
	static p_pt p_p_t1F;		// *=e1
	static p_pt p_p_t1G;		// /=e1
	static p_pt p_p_t1H;		// %=e1
	static p_pt p_p_t1I;		// +=e1
	static p_pt p_p_t1J;		// -=e1
	static p_pt p_p_t1K;		// <<=e1
	static p_pt p_p_t1L;		// >>=e1
	static p_pt p_p_t1M;		// &=e1
	static p_pt p_p_t1N;		// |=e1
	static p_pt p_p_t1O;		// ^=e1
	static p_pt p_p_t1P;		// e2'
	static p_pt p_p_t1Q;		// e3'e2'
	static p_pt p_p_t1R;		// e4'e3'e2'
	static p_pt p_p_t1S;		// e5'e4'e3'e2'
	static p_pt p_p_t1T;		// e6'e5'e4'e3'e2'
	static p_pt p_p_t1U;		// e7'e6'e5'e4'e3'e2'
	static p_pt p_p_t1V;		// e8'e7'e6'e5'e4'e3'e2'
	static p_pt p_p_t1W;		// e9'e8'e7'e6'e5'e4'e3'e2'
	static p_pt p_p_t1X;		// e10'e9'e8'e7'e6'e5'e4'e3'e2'
	static p_pt p_p_t1Y;		// e11'e10'e9'e8'e7'e6'e5'e4'e3'e2'
	static p_pt p_p_t1Z;		// e12'e11'e10'e9'e8'e7'e6'e5'e4'e3'e2'
	static p_pt p_p_t1A1;		// ¦Å

	static p_pt p_p_t2A;		// ++T5
	static p_pt p_p_t2B;		// --T5
	static p_pt p_p_t2C;		// =e1
	static p_pt p_p_t2D;		// *=e1
	static p_pt p_p_t2E;		// /=e1
	static p_pt p_p_t2F;		// %=e1
	static p_pt p_p_t2G;		// +=e1
	static p_pt p_p_t2H;		// -=e1
	static p_pt p_p_t2I;		// <<=e1
	static p_pt p_p_t2J;		// >>=e1
	static p_pt p_p_t2K;		// &=e1
	static p_pt p_p_t2L;		// |=e1
	static p_pt p_p_t2M;		// ^=e1
	static p_pt p_p_t2N;		// e2'
	static p_pt p_p_t2O;		// e3'e2'
	static p_pt p_p_t2P;		// e4'e3'e2'
	static p_pt p_p_t2Q;		// e5'e4'e3'e2'
	static p_pt p_p_t2R;		// e6'e5'e4'e3'e2'
	static p_pt p_p_t2S;		// e7'e6'e5'e4'e3'e2'
	static p_pt p_p_t2T;		// e8'e7'e6'e5'e4'e3'e2'
	static p_pt p_p_t2U;		// e9'e8'e7'e6'e5'e4'e3'e2'
	static p_pt p_p_t2V;		// e10'e9'e8'e7'e6'e5'e4'e3'e2'
	static p_pt p_p_t2W;		// e11'e10'e9'e8'e7'e6'e5'e4'e3'e2'
	static p_pt p_p_t2X;		// e12'e11'e10'e9'e8'e7'e6'e5'e4'e3'e2'
	static p_pt p_p_t2Y;		// ¦Å

	static p_pt p_p_t3A;		// ++
	static p_pt p_p_t3B;		// --
	static p_pt p_p_t3C;		// (args)
	static p_pt p_p_t3D;		// [expr]T4
	static p_pt p_p_t3E;		// ¦Å

	static p_pt p_p_t4A;		// ++
	static p_pt p_p_t4B;		// --
	static p_pt p_p_t4C;		// ¦Å

	static p_pt p_p_t5A;		// e2'
	static p_pt p_p_t5B;		// e3'e2'
	static p_pt p_p_t5C;		// e4'e3'e2'
	static p_pt p_p_t5D;		// e5'e4'e3'e2'
	static p_pt p_p_t5E;		// e6'e5'e4'e3'e2'
	static p_pt p_p_t5F;		// e7'e6'e5'e4'e3'e2'
	static p_pt p_p_t5G;		// e8'e7'e6'e5'e4'e3'e2'
	static p_pt p_p_t5H;		// e9'e8'e7'e6'e5'e4'e3'e2'
	static p_pt p_p_t5I;		// e10'e9'e8'e7'e6'e5'e4'e3'e2'
	static p_pt p_p_t5J;		// e11'e10'e9'e8'e7'e6'e5'e4'e3'e2'
	static p_pt p_p_t5K;		// e12'e11'e10'e9'e8'e7'e6'e5'e4'e3'e2'
	static p_pt p_p_t5L;		// ¦Å

	static p_pt p_p_args1;		// args'
	static p_pt p_p_args2;		// ¦Å
	static p_pt p_p_args_;		// arg args"
	static p_pt p_p_args__1;	// ,args'
	static p_pt p_p_args__2;	// ¦Å
	static p_pt p_p_arg;		// e1

	static p_pt p_p_loc;		// id loc'
	static p_pt p_p_loc_1;		// [expr]
	static p_pt p_p_loc_2;		// ¦Å

public:
	Produce(NonTerminal const* p):phead(p){}
	bodylist getBody()const;	//return clone

	static void Generate();
	static void Destroy();

private:
	NonTerminal const* phead;	//head
	CloneArgsList clone_args;
};