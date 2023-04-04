#include "CProduce.h"
#include "CActRecord.h"
#include "CSynRecord.h"
#include "CTerminal.h"
#include "CNonTerminalSyn.h"
#include "CNonTerminalDef.h"
#include "CInitDel.h"
#include "CCopyFunction.h"
#include "CActionFunction.h"

using std::make_pair;
using namespace Compiler;

Produce::p_pt Produce::p_p_program=0;		//	options main( ){decls stmts}

Produce::p_pt Produce::p_p_options1=0;		//	option options
Produce::p_pt Produce::p_p_options2=0;		//	¦Å	
Produce::p_pt Produce::p_p_option1=0;		//	void id F
Produce::p_pt Produce::p_p_option2=0;		//	B id option'
Produce::p_pt Produce::p_p_option_1=0;		//	F
Produce::p_pt Produce::p_p_option_2=0;		//	decl';

Produce::p_pt Produce::p_p_decls1=0;		//	decl decls
Produce::p_pt Produce::p_p_decls2=0;		//	¦Å
Produce::p_pt Produce::p_p_decl=0;			//	B id decl';
Produce::p_pt Produce::p_p_decl_1=0;		//	A
Produce::p_pt Produce::p_p_decl_2=0;		//	V

Produce::p_pt Produce::p_p_b1=0;			//	bool
Produce::p_pt Produce::p_p_b2=0;			//	char
Produce::p_pt Produce::p_p_b3=0;			//	short
Produce::p_pt Produce::p_p_b4=0;			//	int
Produce::p_pt Produce::p_p_b5=0;			//	float
Produce::p_pt Produce::p_p_b6=0;			//	double

Produce::p_pt Produce::p_p_a=0;				//	[size]Opt1
Produce::p_pt Produce::p_p_opt1A=0;			//	={L}
Produce::p_pt Produce::p_p_opt1B=0;			//	¦Å
Produce::p_pt Produce::p_p_l1=0;			//	L'
Produce::p_pt Produce::p_p_l2=0;			//	¦Å
Produce::p_pt Produce::p_p_l_=0;			//	e1 L"
Produce::p_pt Produce::p_p_l__1=0;			//	,L' 
Produce::p_pt Produce::p_p_l__2=0;			//	¦Å

Produce::p_pt Produce::p_p_v=0;				//	Opt2 V'
Produce::p_pt Produce::p_p_v_1=0;			//	,id Opt2 V'
Produce::p_pt Produce::p_p_v_2=0;			//	¦Å
Produce::p_pt Produce::p_p_opt2A=0;			//	=e1
Produce::p_pt Produce::p_p_opt2B=0;			//	¦Å

Produce::p_pt Produce::p_p_f=0;				//	(params){decls stmts}
Produce::p_pt Produce::p_p_params1=0;		//	params'
Produce::p_pt Produce::p_p_params2=0;		//	¦Å
Produce::p_pt Produce::p_p_params_=0;		//	param params"
Produce::p_pt Produce::p_p_params__1=0;		//	,params'
Produce::p_pt Produce::p_p_params__2=0;		//	¦Å
Produce::p_pt Produce::p_p_param=0;			//	B id tail
Produce::p_pt Produce::p_p_tail1=0;			//	[optexpr1]
Produce::p_pt Produce::p_p_tail2=0;			//	¦Å
Produce::p_pt Produce::p_p_optexpr1A=0;		//	size
Produce::p_pt Produce::p_p_optexpr1B=0;		// ¦Å
Produce::p_pt Produce::p_p_size1=0;			//	num
Produce::p_pt Produce::p_p_size2=0;			//	ascii

Produce::p_pt Produce::p_p_stmt1=0;			// ;
Produce::p_pt Produce::p_p_stmt2=0;			// expr;
Produce::p_pt Produce::p_p_stmt3=0;			// if(expr)stmt E
Produce::p_pt Produce::p_p_stmt4=0;			// while(expr)stmt
Produce::p_pt Produce::p_p_stmt5=0;			// do stmt while(expr);
Produce::p_pt Produce::p_p_stmt6=0;			// break;
Produce::p_pt Produce::p_p_stmt7=0;			// continue;
Produce::p_pt Produce::p_p_stmt8=0;			// return optexpr3;
Produce::p_pt Produce::p_p_stmt9=0;			// for(optexpr2;optexpr2;optexpr2)stmt
Produce::p_pt Produce::p_p_stmt10=0;		// switch(expr)stmt
Produce::p_pt Produce::p_p_stmt11=0;		// case label: stmt
Produce::p_pt Produce::p_p_stmt12=0;		// default: stmt
Produce::p_pt Produce::p_p_stmt13=0;		// {stmts}
Produce::p_pt Produce::p_p_else1=0;			// else stmt
Produce::p_pt Produce::p_p_else2=0;			// ¦Å
Produce::p_pt Produce::p_p_stmts1=0;		// stmt stmts
Produce::p_pt Produce::p_p_stmts2=0;		// ¦Å
Produce::p_pt Produce::p_p_optexpr2A=0;		// expr
Produce::p_pt Produce::p_p_optexpr2B=0;		// ¦Å
Produce::p_pt Produce::p_p_optexpr3A=0;		// expr
Produce::p_pt Produce::p_p_optexpr3B=0;		// ¦Å
Produce::p_pt Produce::p_p_label1=0;		//	false
Produce::p_pt Produce::p_p_label2=0;		//	true
Produce::p_pt Produce::p_p_label3=0;		//	ascii
Produce::p_pt Produce::p_p_label4=0;		//	num
Produce::p_pt Produce::p_p_label5=0;		//	-num

Produce::p_pt Produce::p_p_expr=0;			// e1 expr'
Produce::p_pt Produce::p_p_expr_1=0;		// ,e1 expr'
Produce::p_pt Produce::p_p_expr_2=0;		// ¦Å

Produce::p_pt Produce::p_p_e1A=0;			// loc e1'
Produce::p_pt Produce::p_p_e1B=0;			// e2

Produce::p_pt Produce::p_p_e2=0;			// e3 e2'
Produce::p_pt Produce::p_p_e2_1=0;			// ?e3:e2
Produce::p_pt Produce::p_p_e2_2=0;			// ¦Å

Produce::p_pt Produce::p_p_e3=0;			// e4 e3'
Produce::p_pt Produce::p_p_e3_1=0;			// ||e4 e3'
Produce::p_pt Produce::p_p_e3_2=0;			// ¦Å

Produce::p_pt Produce::p_p_e4=0;			// e5 e4'
Produce::p_pt Produce::p_p_e4_1=0;			// &&e5 e4'
Produce::p_pt Produce::p_p_e4_2=0;			// ¦Å

Produce::p_pt Produce::p_p_e5=0;			// e6 e5'
Produce::p_pt Produce::p_p_e5_1=0;			// |e6 e5'
Produce::p_pt Produce::p_p_e5_2=0;			// ¦Å

Produce::p_pt Produce::p_p_e6=0;			// e7 e6'
Produce::p_pt Produce::p_p_e6_1=0;			// ^e7 e6'
Produce::p_pt Produce::p_p_e6_2=0;			// ¦Å

Produce::p_pt Produce::p_p_e7=0;			// e8 e7'
Produce::p_pt Produce::p_p_e7_1=0;			// &e8 e7'
Produce::p_pt Produce::p_p_e7_2=0;			// ¦Å

Produce::p_pt Produce::p_p_e8=0;			// e9 e8'
Produce::p_pt Produce::p_p_e8_1=0;			// ==e9 e8'
Produce::p_pt Produce::p_p_e8_2=0;			// !=e9 e8'
Produce::p_pt Produce::p_p_e8_3=0;			// ¦Å

Produce::p_pt Produce::p_p_e9=0;			// e10 e9'
Produce::p_pt Produce::p_p_e9_1=0;			// <e10 e9'
Produce::p_pt Produce::p_p_e9_2=0;			// <=e10 e9'
Produce::p_pt Produce::p_p_e9_3=0;			// >e10 e9'
Produce::p_pt Produce::p_p_e9_4=0;			// >=e10 e9'
Produce::p_pt Produce::p_p_e9_5=0;			// ¦Å

Produce::p_pt Produce::p_p_e10=0;			// e11 e10'
Produce::p_pt Produce::p_p_e10_1=0;			// <<e11 e10'
Produce::p_pt Produce::p_p_e10_2=0;			// >>e11 e10'
Produce::p_pt Produce::p_p_e10_3=0;			// ¦Å

Produce::p_pt Produce::p_p_e11=0;			// e12 e11'
Produce::p_pt Produce::p_p_e11_1=0;			// +e12 e11'
Produce::p_pt Produce::p_p_e11_2=0;			// -e12 e11'
Produce::p_pt Produce::p_p_e11_3=0;			// ¦Å

Produce::p_pt Produce::p_p_e12=0;			// e13 e12'
Produce::p_pt Produce::p_p_e12_1=0;			// *e13 e12'
Produce::p_pt Produce::p_p_e12_2=0;			// /e13 e12'
Produce::p_pt Produce::p_p_e12_3=0;			// %e13 e12'
Produce::p_pt Produce::p_p_e12_4=0;			// ¦Å

Produce::p_pt Produce::p_p_e13A=0;			// ~e13
Produce::p_pt Produce::p_p_e13B=0;			// !e13
Produce::p_pt Produce::p_p_e13C=0;			// -e13
Produce::p_pt Produce::p_p_e13D=0;			// +e13
Produce::p_pt Produce::p_p_e13E=0;			// e14

Produce::p_pt Produce::p_p_e14A=0;			// true
Produce::p_pt Produce::p_p_e14B=0;			// false
Produce::p_pt Produce::p_p_e14C=0;			// ascii
Produce::p_pt Produce::p_p_e14D=0;			// num
Produce::p_pt Produce::p_p_e14E=0;			// real
Produce::p_pt Produce::p_p_e14F=0;			// ++loc
Produce::p_pt Produce::p_p_e14G=0;			// --loc
Produce::p_pt Produce::p_p_e14H=0;			// (expr)
Produce::p_pt Produce::p_p_e14I=0;			// id T3

Produce::p_pt Produce::p_p_t1A=0;			// ++T5
Produce::p_pt Produce::p_p_t1B=0;			// --T5
Produce::p_pt Produce::p_p_t1C=0;			// (args)T5
Produce::p_pt Produce::p_p_t1D=0;			// [expr]T2
Produce::p_pt Produce::p_p_t1E=0;			// =e1
Produce::p_pt Produce::p_p_t1F=0;			// *=e1
Produce::p_pt Produce::p_p_t1G=0;			// /=e1
Produce::p_pt Produce::p_p_t1H=0;			// %=e1
Produce::p_pt Produce::p_p_t1I=0;			// +=e1
Produce::p_pt Produce::p_p_t1J=0;			// -=e1
Produce::p_pt Produce::p_p_t1K=0;			// <<=e1
Produce::p_pt Produce::p_p_t1L=0;			// >>=e1
Produce::p_pt Produce::p_p_t1M=0;			// &=e1
Produce::p_pt Produce::p_p_t1N=0;			// |=e1
Produce::p_pt Produce::p_p_t1O=0;			// ^=e1
Produce::p_pt Produce::p_p_t1P=0;			// e2'
Produce::p_pt Produce::p_p_t1Q=0;			// e3'e2'
Produce::p_pt Produce::p_p_t1R=0;			// e4'e3'e2'
Produce::p_pt Produce::p_p_t1S=0;			// e5'e4'e3'e2'
Produce::p_pt Produce::p_p_t1T=0;			// e6'e5'e4'e3'e2'
Produce::p_pt Produce::p_p_t1U=0;			// e7'e6'e5'e4'e3'e2'
Produce::p_pt Produce::p_p_t1V=0;			// e8'e7'e6'e5'e4'e3'e2'
Produce::p_pt Produce::p_p_t1W=0;			// e9'e8'e7'e6'e5'e4'e3'e2'
Produce::p_pt Produce::p_p_t1X=0;			// e10'e9'e8'e7'e6'e5'e4'e3'e2'
Produce::p_pt Produce::p_p_t1Y=0;			// e11'e10'e9'e8'e7'e6'e5'e4'e3'e2'
Produce::p_pt Produce::p_p_t1Z=0;			// e12'e11'e10'e9'e8'e7'e6'e5'e4'e3'e2'
Produce::p_pt Produce::p_p_t1A1=0;			// ¦Å

Produce::p_pt Produce::p_p_t2A=0;			// ++T5
Produce::p_pt Produce::p_p_t2B=0;			// --T5
Produce::p_pt Produce::p_p_t2C=0;			// =e1
Produce::p_pt Produce::p_p_t2D=0;			// *=e1
Produce::p_pt Produce::p_p_t2E=0;			// /=e1
Produce::p_pt Produce::p_p_t2F=0;			// %=e1
Produce::p_pt Produce::p_p_t2G=0;			// +=e1
Produce::p_pt Produce::p_p_t2H=0;			// -=e1
Produce::p_pt Produce::p_p_t2I=0;			// <<=e1
Produce::p_pt Produce::p_p_t2J=0;			// >>=e1
Produce::p_pt Produce::p_p_t2K=0;			// &=e1
Produce::p_pt Produce::p_p_t2L=0;			// |=e1
Produce::p_pt Produce::p_p_t2M=0;			// ^=e1
Produce::p_pt Produce::p_p_t2N=0;			// e2'
Produce::p_pt Produce::p_p_t2O=0;			// e3'e2'
Produce::p_pt Produce::p_p_t2P=0;			// e4'e3'e2'
Produce::p_pt Produce::p_p_t2Q=0;			// e5'e4'e3'e2'
Produce::p_pt Produce::p_p_t2R=0;			// e6'e5'e4'e3'e2'
Produce::p_pt Produce::p_p_t2S=0;			// e7'e6'e5'e4'e3'e2'
Produce::p_pt Produce::p_p_t2T=0;			// e8'e7'e6'e5'e4'e3'e2'
Produce::p_pt Produce::p_p_t2U=0;			// e9'e8'e7'e6'e5'e4'e3'e2'
Produce::p_pt Produce::p_p_t2V=0;			// e10'e9'e8'e7'e6'e5'e4'e3'e2'
Produce::p_pt Produce::p_p_t2W=0;			// e11'e10'e9'e8'e7'e6'e5'e4'e3'e2'
Produce::p_pt Produce::p_p_t2X=0;			// e12'e11'e10'e9'e8'e7'e6'e5'e4'e3'e2'
Produce::p_pt Produce::p_p_t2Y=0;			// ¦Å

Produce::p_pt Produce::p_p_t3A=0;			// ++
Produce::p_pt Produce::p_p_t3B=0;			// --
Produce::p_pt Produce::p_p_t3C=0;			// (args)
Produce::p_pt Produce::p_p_t3D=0;			// [expr]T2
Produce::p_pt Produce::p_p_t3E=0;			// ¦Å

Produce::p_pt Produce::p_p_t4A=0;			// ++
Produce::p_pt Produce::p_p_t4B=0;			// --
Produce::p_pt Produce::p_p_t4C=0;			// ¦Å

Produce::p_pt Produce::p_p_t5A=0;			// e2'
Produce::p_pt Produce::p_p_t5B=0;			// e3'e2'
Produce::p_pt Produce::p_p_t5C=0;			// e4'e3'e2'
Produce::p_pt Produce::p_p_t5D=0;			// e5'e4'e3'e2'
Produce::p_pt Produce::p_p_t5E=0;			// e6'e5'e4'e3'e2'
Produce::p_pt Produce::p_p_t5F=0;			// e7'e6'e5'e4'e3'e2'
Produce::p_pt Produce::p_p_t5G=0;			// e8'e7'e6'e5'e4'e3'e2'
Produce::p_pt Produce::p_p_t5H=0;			// e9'e8'e7'e6'e5'e4'e3'e2'
Produce::p_pt Produce::p_p_t5I=0;			// e10'e9'e8'e7'e6'e5'e4'e3'e2'
Produce::p_pt Produce::p_p_t5J=0;			// e11'e10'e9'e8'e7'e6'e5'e4'e3'e2'
Produce::p_pt Produce::p_p_t5K=0;			// e12'e11'e10'e9'e8'e7'e6'e5'e4'e3'e2'
Produce::p_pt Produce::p_p_t5L=0;			// ¦Å

Produce::p_pt Produce::p_p_args1=0;			// args'
Produce::p_pt Produce::p_p_args2=0;			// ¦Å
Produce::p_pt Produce::p_p_args_=0;			// arg args"
Produce::p_pt Produce::p_p_args__1=0;		// ,args'
Produce::p_pt Produce::p_p_args__2=0;		// ¦Å
Produce::p_pt Produce::p_p_arg=0;			// e1

Produce::p_pt Produce::p_p_loc=0;			// id loc'
Produce::p_pt Produce::p_p_loc_1=0;			// [expr]
Produce::p_pt Produce::p_p_loc_2=0;			// ¦Å


void Produce::Generate()
{
	p_p_program		=	new Produce(NonTerminalSyn::p_program);										//	program
	p_p_program->clone_args.push_back(make_pair(NonTerminalDef::p_options,CloneArgs()));			//	options
	p_p_program->clone_args.push_back(make_pair(Terminal::p_main,CloneArgs()));						//	main
	p_p_program->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_program_A1,init_temp_program_A1,0)));						//	A1
	p_p_program->clone_args.push_back(make_pair(Terminal::p_l_bracket,CloneArgs()));				//	(
	p_p_program->clone_args.push_back(make_pair(Terminal::p_r_bracket,CloneArgs()));				//	)
	p_p_program->clone_args.push_back(make_pair(Terminal::p_l_f_bracket,CloneArgs()));				//	{
	p_p_program->clone_args.push_back(make_pair(NonTerminalDef::p_decls,CloneArgs()));				//	decls
	p_p_program->clone_args.push_back(make_pair(NonTerminalDef::p_stmts,CloneArgs(0,init_inh_program_stmts,0,0,0,0,0,0)));				//	stmts
	p_p_program->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_program_S,0,0,init_syn_program_S,del_syn_program_S)));						//	S
	p_p_program->clone_args.push_back(make_pair(Terminal::p_r_f_bracket,CloneArgs()));				//	}
	p_p_program->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_program_A2)));						//	A2

	//...
	
	p_p_options1	=	new Produce(NonTerminalDef::p_options);										//	options
	p_p_options1->clone_args.push_back(make_pair(NonTerminalSyn::p_option,CloneArgs()));			//	option
	p_p_options1->clone_args.push_back(make_pair(NonTerminalDef::p_options,CloneArgs()));			//	options

	p_p_options2	=	new Produce(NonTerminalDef::p_options);										//	¦Å	

	p_p_option1		=	new Produce(NonTerminalSyn::p_option);										//	option
	p_p_option1->clone_args.push_back(make_pair(Terminal::p_void,CloneArgs()));						//	void
	p_p_option1->clone_args.push_back(make_pair(Terminal::p_id,CloneArgs()));						//	id
	p_p_option1->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_option1_A,init_temp_option1_A,del_temp_option1_A)));						//	A
	p_p_option1->clone_args.push_back(make_pair(NonTerminalSyn::p_f,CloneArgs(0,init_inh_option1_F,del_inh_option1_F)));					//	F

	p_p_option2		=	new Produce(NonTerminalSyn::p_option);										//	option	  
	p_p_option2->clone_args.push_back(make_pair(NonTerminalSyn::p_b,CloneArgs()));					//	B
	p_p_option2->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_option2_S,0,0,init_syn_option2_S)));						//	S
	p_p_option2->clone_args.push_back(make_pair(Terminal::p_id,CloneArgs()));						//	id
	p_p_option2->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_option2_A,init_temp_option2_A,del_temp_option2_A)));						//	A
	p_p_option2->clone_args.push_back(make_pair(NonTerminalSyn::p_option_,CloneArgs(0,init_inh_option2_option_,del_inh_option2_option_)));			//	option'

	p_p_option_1	=	new Produce(NonTerminalSyn::p_option_);										//	option'
	p_p_option_1->clone_args.push_back(make_pair(NonTerminalSyn::p_f,CloneArgs(copy_option_1_F,init_inh_option_1_F,del_inh_option_1_F)));					//	F

	p_p_option_2	=	new Produce(NonTerminalSyn::p_option_);										//	option'
	p_p_option_2->clone_args.push_back(make_pair(NonTerminalDef::p_decl_,CloneArgs(copy_option_2_decl_,init_inh_option_2_decl_,del_inh_option_2_decl_)));				//	decl'
	p_p_option_2->clone_args.push_back(make_pair(Terminal::p_semicolon,CloneArgs()));				//	;

	//...

	p_p_decls1		=	new Produce(NonTerminalDef::p_decls);										//	decls
	p_p_decls1->clone_args.push_back(make_pair(NonTerminalSyn::p_decl,CloneArgs()));				//	decl
	p_p_decls1->clone_args.push_back(make_pair(NonTerminalDef::p_decls,CloneArgs()));				//	decls

	p_p_decls2		=	new Produce(NonTerminalDef::p_decls);										//	¦Å

	p_p_decl		=	new Produce(NonTerminalSyn::p_decl);										//	decl
	p_p_decl->clone_args.push_back(make_pair(NonTerminalSyn::p_b,CloneArgs()));						//	B
	p_p_decl->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_decl_S,0,0,init_syn_decl_S)));						//	S
	p_p_decl->clone_args.push_back(make_pair(Terminal::p_id,CloneArgs()));							//	id
	p_p_decl->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_decl_A,init_temp_decl_A,del_temp_decl_A)));						//	A
	p_p_decl->clone_args.push_back(make_pair(NonTerminalDef::p_decl_,CloneArgs(0,init_inh_decl_decl_,del_inh_decl_decl_)));					//	decl'
	p_p_decl->clone_args.push_back(make_pair(Terminal::p_semicolon,CloneArgs()));					//	;

	p_p_decl_1		=	new Produce(NonTerminalDef::p_decl_);										//	decl'
	p_p_decl_1->clone_args.push_back(make_pair(NonTerminalSyn::p_a,CloneArgs(copy_decl_1_A,init_inh_decl_1_A,del_inh_decl_1_A)));					//	A

	p_p_decl_2		=	new Produce(NonTerminalDef::p_decl_);										//	decl'
	p_p_decl_2->clone_args.push_back(make_pair(NonTerminalDef::p_v,CloneArgs(copy_decl_2_V,init_inh_decl_2_V,del_inh_decl_2_V)));					//	V

	//...

	p_p_b1			=	new Produce(NonTerminalSyn::p_b);											//	B
	p_p_b1->clone_args.push_back(make_pair(Terminal::p_bool,CloneArgs()));							//	bool

	p_p_b2			=	new Produce(NonTerminalSyn::p_b);											//	B
	p_p_b2->clone_args.push_back(make_pair(Terminal::p_char,CloneArgs()));							//	char

	p_p_b3			=	new Produce(NonTerminalSyn::p_b);											//	B
	p_p_b3->clone_args.push_back(make_pair(Terminal::p_short,CloneArgs()));							//	short

	p_p_b4			=	new Produce(NonTerminalSyn::p_b);											//	B
	p_p_b4->clone_args.push_back(make_pair(Terminal::p_int,CloneArgs()));							//	int

	p_p_b5			=	new Produce(NonTerminalSyn::p_b);											//	B
	p_p_b5->clone_args.push_back(make_pair(Terminal::p_float,CloneArgs()));							//	float

	p_p_b6			=	new Produce(NonTerminalSyn::p_b);											//	B
	p_p_b6->clone_args.push_back(make_pair(Terminal::p_double,CloneArgs()));						//	double

	//...

	p_p_a			=	new Produce(NonTerminalSyn::p_a);											//	A
	p_p_a->clone_args.push_back(make_pair(Terminal::p_l_s_bracket,CloneArgs()));					//	[
	p_p_a->clone_args.push_back(make_pair(NonTerminalSyn::p_size,CloneArgs()));						//	size
	p_p_a->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_A_S,init_inh_A_S,del_inh_A_S,act_A_S,0,0,init_syn_A_S)));						//	S
	p_p_a->clone_args.push_back(make_pair(Terminal::p_r_s_bracket,CloneArgs()));					//	]
	p_p_a->clone_args.push_back(make_pair(NonTerminalDef::p_opt1,CloneArgs(copy_A_opt1,init_inh_A_opt1,del_inh_A_opt1)));						//	Opt1

	p_p_opt1A		=	new Produce(NonTerminalDef::p_opt1);										//	Opt1
	p_p_opt1A->clone_args.push_back(make_pair(Terminal::p_assign,CloneArgs()));						//	=
	p_p_opt1A->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,0,init_temp_opt1A_A)));						//	A
	p_p_opt1A->clone_args.push_back(make_pair(Terminal::p_l_f_bracket,CloneArgs()));				//	{
	p_p_opt1A->clone_args.push_back(make_pair(NonTerminalDef::p_l,CloneArgs(copy_opt1A_L,init_inh_opt1A_L,del_inh_opt1A_L)));					//	L
	p_p_opt1A->clone_args.push_back(make_pair(Terminal::p_r_f_bracket,CloneArgs()));				//	}

	p_p_opt1B		=	new Produce(NonTerminalDef::p_opt1);										//	¦Å

	p_p_l1			=	new Produce(NonTerminalDef::p_l);											//	L
	p_p_l1->clone_args.push_back(make_pair(NonTerminalSyn::p_l_,CloneArgs(copy_L1_L_,init_inh_L1_L_,del_inh_L1_L_)));						//	L'

	p_p_l2			=	new Produce(NonTerminalDef::p_l);											//	¦Å

	p_p_l_			=	new Produce(NonTerminalSyn::p_l_);											//	L'
	p_p_l_->clone_args.push_back(make_pair(NonTerminalSyn::p_e1,CloneArgs(copy_L__e1,init_inh_L__e1)));						//	e1
	p_p_l_->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_L__S,init_inh_L__S,del_inh_L__S,act_L__S,0,0,init_syn_L__S,del_syn_L__S)));						//	S
	p_p_l_->clone_args.push_back(make_pair(NonTerminalDef::p_l__,CloneArgs(copy_L__L__,init_inh_L__L__,del_inh_L__L__)));						//	L"

	p_p_l__1		=	new Produce(NonTerminalDef::p_l__);											//	L"
	p_p_l__1->clone_args.push_back(make_pair(Terminal::p_comma,CloneArgs()));						//	,
	p_p_l__1->clone_args.push_back(make_pair(NonTerminalSyn::p_l_,CloneArgs(copy_L__1_L_,init_inh_L__1_L_,del_inh_L__1_L_)));					//	L'

	p_p_l__2		=	new Produce(NonTerminalDef::p_l__);											//	¦Å

	//...

	p_p_v			=	new Produce(NonTerminalDef::p_v);											//	V
	p_p_v->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_V_A,init_inh_V_A,del_inh_V_A,act_V_A)));						//	A
	p_p_v->clone_args.push_back(make_pair(NonTerminalDef::p_opt2,CloneArgs(copy_V_opt2,init_inh_V_opt2,del_inh_V_opt2)));						//	Opt2
	p_p_v->clone_args.push_back(make_pair(NonTerminalDef::p_v_,CloneArgs(copy_V_V_,init_inh_V_V_)));						//	V'

	p_p_v_1			=	new Produce(NonTerminalDef::p_v_);											//	V'
	p_p_v_1->clone_args.push_back(make_pair(Terminal::p_comma,CloneArgs()));						//	,
	p_p_v_1->clone_args.push_back(make_pair(Terminal::p_id,CloneArgs()));							//	id
	p_p_v_1->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_V_1_A,init_inh_V_1_A,0,act_V_1_A,init_temp_V_1_A,del_temp_V_1_A)));						//	A
	p_p_v_1->clone_args.push_back(make_pair(NonTerminalDef::p_opt2,CloneArgs(copy_V_1_opt2,init_inh_V_1_opt2,del_inh_V_1_opt2)));					//	Opt2
	p_p_v_1->clone_args.push_back(make_pair(NonTerminalDef::p_v_,CloneArgs(copy_V_1_V_,init_inh_V_1_V_)));						//	V'

	p_p_v_2			=	new Produce(NonTerminalDef::p_v_);											//	¦Å

	p_p_opt2A		=	new Produce(NonTerminalDef::p_opt2);										//	Opt2
	p_p_opt2A->clone_args.push_back(make_pair(Terminal::p_assign,CloneArgs()));						//	=
	p_p_opt2A->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,0,init_temp_opt2A_A)));						//	A
	p_p_opt2A->clone_args.push_back(make_pair(NonTerminalSyn::p_e1,CloneArgs(copy_opt2A_e1,init_inh_opt2A_e1)));					//	e1
	p_p_opt2A->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_opt2A_S,init_inh_opt2A_S,del_inh_opt2A_S,act_opt2A_S,0,0,init_syn_opt2A_S,del_syn_opt2A_S)));						//	S

	p_p_opt2B		=	new Produce(NonTerminalDef::p_opt2);										//	¦Å

	//...

	p_p_f			=	new Produce(NonTerminalSyn::p_f);											//	F
	p_p_f->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_F_A1,init_inh_F_A1,del_inh_F_A1,act_F_A1)));							//	A1
	p_p_f->clone_args.push_back(make_pair(Terminal::p_l_bracket,CloneArgs()));						//	(
	p_p_f->clone_args.push_back(make_pair(NonTerminalDef::p_params,CloneArgs()));					//	params
	p_p_f->clone_args.push_back(make_pair(Terminal::p_r_bracket,CloneArgs()));						//	)
	p_p_f->clone_args.push_back(make_pair(Terminal::p_l_f_bracket,CloneArgs()));					//	{
	p_p_f->clone_args.push_back(make_pair(NonTerminalDef::p_decls,CloneArgs()));					//	decls
	p_p_f->clone_args.push_back(make_pair(NonTerminalDef::p_stmts,CloneArgs(0,init_inh_F_stmts)));					//	stmts
	p_p_f->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_F_S,0,0,init_syn_F_S,del_syn_F_S)));							//	S
	p_p_f->clone_args.push_back(make_pair(Terminal::p_r_f_bracket,CloneArgs()));					//	}
	p_p_f->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_F_A2)));							//	A2

	p_p_params1		=	new Produce(NonTerminalDef::p_params);										//	params
	p_p_params1->clone_args.push_back(make_pair(NonTerminalSyn::p_params_,CloneArgs()));			//	params'

	p_p_params2		=	new Produce(NonTerminalDef::p_params);										//	¦Å

	p_p_params_		=	new Produce(NonTerminalSyn::p_params_);										//	params'
	p_p_params_->clone_args.push_back(make_pair(NonTerminalSyn::p_param,CloneArgs()));				//	param
	p_p_params_->clone_args.push_back(make_pair(NonTerminalDef::p_params__,CloneArgs()));			//	params"

	p_p_params__1	=	new Produce(NonTerminalDef::p_params__);									//	params"
	p_p_params__1->clone_args.push_back(make_pair(Terminal::p_comma,CloneArgs()));					//	,
	p_p_params__1->clone_args.push_back(make_pair(NonTerminalSyn::p_params_,CloneArgs()));			//	params'

	p_p_params__2	=	new Produce(NonTerminalDef::p_params__);									//	¦Å

	p_p_param		=	new Produce(NonTerminalSyn::p_param);										//	param
	p_p_param->clone_args.push_back(make_pair(NonTerminalSyn::p_b,CloneArgs()));					//	B
	p_p_param->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_param_S,0,0,init_syn_param_S)));						//	S
	p_p_param->clone_args.push_back(make_pair(Terminal::p_id,CloneArgs()));							//	id
	p_p_param->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_param_A,init_temp_param_A,del_temp_param_A)));						//	A
	p_p_param->clone_args.push_back(make_pair(NonTerminalDef::p_tail,CloneArgs(0,init_inh_param_tail,del_inh_param_tail)));					//	tail

	p_p_tail1		=	new Produce(NonTerminalDef::p_tail);										//	tail
	p_p_tail1->clone_args.push_back(make_pair(Terminal::p_l_s_bracket,CloneArgs()));				//	[
	p_p_tail1->clone_args.push_back(make_pair(NonTerminalDef::p_optexpr1,CloneArgs()));				//	optexpr1
	p_p_tail1->clone_args.push_back(make_pair(Terminal::p_r_s_bracket,CloneArgs()));				//	]
	p_p_tail1->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_tail1_A,init_inh_tail1_A,del_inh_tail1_A,act_tail1_A)));						//	A

	p_p_tail2		=	new Produce(NonTerminalDef::p_tail);										//	¦Å
	p_p_tail2->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_tail2_A,init_inh_tail2_A,del_inh_tail2_A,act_tail2_A)));						//	A

	p_p_optexpr1A	=	new Produce(NonTerminalDef::p_optexpr1);									//	optexpr1
	p_p_optexpr1A->clone_args.push_back(make_pair(NonTerminalSyn::p_size,CloneArgs()));				//	size
	p_p_optexpr1A->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,0,0,0,init_syn_optexpr1A_S)));					//	S

	p_p_optexpr1B	=	new Produce(NonTerminalDef::p_optexpr1);									// ¦Å

	p_p_size1	=	new Produce(NonTerminalSyn::p_size);											//	size
	p_p_size1->clone_args.push_back(make_pair(Terminal::p_number,CloneArgs()));						//	num
	p_p_size1->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_size_A,init_temp_size_A)));						//	A

	p_p_size2	=	new Produce(NonTerminalSyn::p_size);											//	size
	p_p_size2->clone_args.push_back(make_pair(Terminal::p_ascii,CloneArgs()));						//	ascii
	p_p_size2->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_size_A,init_temp_size_A)));						//	A

	//...

	p_p_stmt1		=	new Produce(NonTerminalSyn::p_stmt);										//	stmt
	p_p_stmt1->clone_args.push_back(make_pair(Terminal::p_semicolon,CloneArgs()));					//	;

	p_p_stmt2		=	new Produce(NonTerminalSyn::p_stmt);										//	stmt
	p_p_stmt2->clone_args.push_back(make_pair(NonTerminalSyn::p_expr,CloneArgs(0,init_inh_stmt2_expr)));					//	expr
	p_p_stmt2->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_stmt2_S,0,0,init_syn_stmt2_S,del_syn_stmt2_S)));						//	S
	p_p_stmt2->clone_args.push_back(make_pair(Terminal::p_semicolon,CloneArgs()));					//	;

	p_p_stmt3		=	new Produce(NonTerminalSyn::p_stmt);										//	stmt
	p_p_stmt3->clone_args.push_back(make_pair(Terminal::p_if,CloneArgs()));							//	if
	p_p_stmt3->clone_args.push_back(make_pair(Terminal::p_l_bracket,CloneArgs()));					//	(
	p_p_stmt3->clone_args.push_back(make_pair(NonTerminalSyn::p_expr,CloneArgs(0,init_inh_stmt3_expr)));					//	expr
	p_p_stmt3->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_stmt3_S1,init_temp_stmt3_S1,0,init_syn_stmt3_S1,del_syn_stmt3_S1)));						//	S1
	p_p_stmt3->clone_args.push_back(make_pair(Terminal::p_r_bracket,CloneArgs()));					//	)
	p_p_stmt3->clone_args.push_back(make_pair(NonTerminalSyn::p_stmt,CloneArgs(copy_stmt3_stmt,init_inh_stmt3_stmt)));					//	stmt
	p_p_stmt3->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_stmt3_S2,0,0,init_syn_stmt3_S2,del_syn_stmt3_S2)));						//	S2
	p_p_stmt3->clone_args.push_back(make_pair(NonTerminalDef::p_else,CloneArgs(copy_stmt3_E,init_inh_stmt3_E)));					//	E
	p_p_stmt3->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_stmt3_S3,0,0,init_syn_stmt3_S3,del_syn_stmt3_S3)));						//	S3

	p_p_stmt4		=	new Produce(NonTerminalSyn::p_stmt);										//	stmt
	p_p_stmt4->clone_args.push_back(make_pair(Terminal::p_while,CloneArgs()));						//	while
	p_p_stmt4->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_stmt4_A)));						//	A
	p_p_stmt4->clone_args.push_back(make_pair(Terminal::p_l_bracket,CloneArgs()));					//	(
	p_p_stmt4->clone_args.push_back(make_pair(NonTerminalSyn::p_expr,CloneArgs(0,init_inh_stmt4_expr)));					//	expr
	p_p_stmt4->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_stmt4_S1,init_temp_stmt4_S1,0,init_syn_stmt4_S1,del_syn_stmt4_S1)));						//	S1
	p_p_stmt4->clone_args.push_back(make_pair(Terminal::p_r_bracket,CloneArgs()));					//	)
	p_p_stmt4->clone_args.push_back(make_pair(NonTerminalSyn::p_stmt,CloneArgs(copy_stmt4_stmt,init_inh_stmt4_stmt)));					//	stmt
	p_p_stmt4->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_stmt4_S2,init_temp_stmt4_S2,del_temp_stmt4_S2,init_syn_stmt4_S2,del_syn_stmt4_S2)));						//	S2

	p_p_stmt5		=	new Produce(NonTerminalSyn::p_stmt);										//	stmt
	p_p_stmt5->clone_args.push_back(make_pair(Terminal::p_do,CloneArgs()));							//	do
	p_p_stmt5->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_stmt5_A)));						//	A
	p_p_stmt5->clone_args.push_back(make_pair(NonTerminalSyn::p_stmt,CloneArgs(copy_stmt5_stmt,init_inh_stmt5_stmt)));					//	stmt
	p_p_stmt5->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_stmt5_S1,init_temp_stmt5_S1,del_temp_stmt5_S1,init_syn_stmt5_S1,del_syn_stmt5_S1)));						//	S1
	p_p_stmt5->clone_args.push_back(make_pair(Terminal::p_while,CloneArgs()));						//	while
	p_p_stmt5->clone_args.push_back(make_pair(Terminal::p_l_bracket,CloneArgs()));					//	(
	p_p_stmt5->clone_args.push_back(make_pair(NonTerminalSyn::p_expr,CloneArgs(0,init_inh_stmt5_expr)));					//	expr
	p_p_stmt5->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_stmt5_S2,init_temp_stmt5_S2,0,init_syn_stmt5_S2,del_syn_stmt5_S2)));						//	S2
	p_p_stmt5->clone_args.push_back(make_pair(Terminal::p_r_bracket,CloneArgs()));					//	)
	p_p_stmt5->clone_args.push_back(make_pair(Terminal::p_semicolon,CloneArgs()));					//	;

	p_p_stmt6		=	new Produce(NonTerminalSyn::p_stmt);										//	stmt
	p_p_stmt6->clone_args.push_back(make_pair(Terminal::p_break,CloneArgs()));						//	break
	p_p_stmt6->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_stmt6_A,init_inh_stmt6_A,0,act_stmt6_A,init_temp_stmt6_A)));						//	A
	p_p_stmt6->clone_args.push_back(make_pair(Terminal::p_semicolon,CloneArgs()));					//	;

	p_p_stmt7		=	new Produce(NonTerminalSyn::p_stmt);										//	stmt
	p_p_stmt7->clone_args.push_back(make_pair(Terminal::p_continue,CloneArgs()));					//	continue
	p_p_stmt7->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_stmt7_A,init_inh_stmt7_A,0,act_stmt7_A,init_temp_stmt7_A)));						//	A
	p_p_stmt7->clone_args.push_back(make_pair(Terminal::p_semicolon,CloneArgs()));					//	;

	p_p_stmt8		=	new Produce(NonTerminalSyn::p_stmt);										//	stmt
	p_p_stmt8->clone_args.push_back(make_pair(Terminal::p_return,CloneArgs()));						//	return
	p_p_stmt8->clone_args.push_back(make_pair(NonTerminalDef::p_optexpr3,CloneArgs(0,init_inh_stmt8_optexpr3)));				//	optexpr3
	p_p_stmt8->clone_args.push_back(make_pair(Terminal::p_semicolon,CloneArgs()));					//	;

	p_p_stmt9		=	new Produce(NonTerminalSyn::p_stmt);										//	stmt
	p_p_stmt9->clone_args.push_back(make_pair(Terminal::p_for,CloneArgs()));																								//	for
	p_p_stmt9->clone_args.push_back(make_pair(Terminal::p_l_bracket,CloneArgs()));																							//	(
	p_p_stmt9->clone_args.push_back(make_pair(NonTerminalDef::p_optexpr2,CloneArgs(copy_stmt9_optexpr2_A,init_inh_stmt9_optexpr2)));										//	optexpr2
	p_p_stmt9->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_stmt9_A1)));																				//	A1
	p_p_stmt9->clone_args.push_back(make_pair(Terminal::p_semicolon,CloneArgs()));																							//	;
	p_p_stmt9->clone_args.push_back(make_pair(NonTerminalDef::p_optexpr2,CloneArgs(copy_stmt9_optexpr2_B,init_inh_stmt9_optexpr2)));										//	optexpr2
	p_p_stmt9->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_stmt9_S1,0,0,init_syn_stmt9_S1,del_syn_stmt9_S1)));										//	S1
	p_p_stmt9->clone_args.push_back(make_pair(Terminal::p_semicolon,CloneArgs()));																							//	;
	p_p_stmt9->clone_args.push_back(make_pair(NonTerminalDef::p_optexpr2,CloneArgs(copy_stmt9_optexpr2_C,init_inh_stmt9_optexpr2)));										//	optexpr2
	p_p_stmt9->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_stmt9_A2,init_temp_stmt9_A2,del_temp_stmt9_A2)));										//	A2
	p_p_stmt9->clone_args.push_back(make_pair(Terminal::p_r_bracket,CloneArgs()));																							//	)
	p_p_stmt9->clone_args.push_back(make_pair(NonTerminalSyn::p_stmt,CloneArgs(copy_stmt9_stmt,init_inh_stmt9_stmt)));														//	stmt
	p_p_stmt9->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_stmt9_S2,init_temp_stmt9_S2,del_temp_stmt9_S2,init_syn_stmt9_S2,del_syn_stmt9_S2)));		//	S2

	p_p_stmt10		=	new Produce(NonTerminalSyn::p_stmt);										//	stmt
	p_p_stmt10->clone_args.push_back(make_pair(Terminal::p_switch,CloneArgs()));																									//	switch
	p_p_stmt10->clone_args.push_back(make_pair(Terminal::p_l_bracket,CloneArgs()));																									//	(
	p_p_stmt10->clone_args.push_back(make_pair(NonTerminalSyn::p_expr,CloneArgs(0,init_inh_stmt10_expr)));																			//	expr
	p_p_stmt10->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_stmt10_S1,init_temp_stmt10_S1,0,init_syn_stmt10_S1,del_syn_stmt10_S1)));						//	S1
	p_p_stmt10->clone_args.push_back(make_pair(Terminal::p_r_bracket,CloneArgs()));																									//	)
	p_p_stmt10->clone_args.push_back(make_pair(NonTerminalSyn::p_stmt,CloneArgs(copy_stmt10_stmt,init_inh_stmt10_stmt)));															//	stmt
	p_p_stmt10->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_stmt10_S2,init_temp_stmt10_S2,del_temp_stmt10_S2,init_syn_stmt10_S2,del_syn_stmt10_S2)));		//	S2

	p_p_stmt11		=	new Produce(NonTerminalSyn::p_stmt);										//	stmt
	p_p_stmt11->clone_args.push_back(make_pair(Terminal::p_case,CloneArgs()));																						//	case
	p_p_stmt11->clone_args.push_back(make_pair(NonTerminalSyn::p_label,CloneArgs()));																				//	label
	p_p_stmt11->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_stmt11_S1,init_inh_stmt11_S1,0,act_stmt11_S1,0,0,init_syn_stmt11_S1)));				//	S1
	p_p_stmt11->clone_args.push_back(make_pair(Terminal::p_colon,CloneArgs()));																						//	:
	p_p_stmt11->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,0,init_temp_stmt11_A)));															//	A
	p_p_stmt11->clone_args.push_back(make_pair(NonTerminalSyn::p_stmt,CloneArgs(copy_stmt11_stmt,init_inh_stmt11_stmt)));											//	stmt
	p_p_stmt11->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_stmt11_S2,0,0,init_syn_stmt11_S2,del_syn_stmt11_S2)));							//	S2

	p_p_stmt12		=	new Produce(NonTerminalSyn::p_stmt);										//	stmt
	p_p_stmt12->clone_args.push_back(make_pair(Terminal::p_default,CloneArgs()));					//	default
	p_p_stmt12->clone_args.push_back(make_pair(Terminal::p_colon,CloneArgs()));						//	:
	p_p_stmt12->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_stmt12_A,init_inh_stmt12_A,0,act_stmt12_A,init_temp_stmt12_A)));						//	A
	p_p_stmt12->clone_args.push_back(make_pair(NonTerminalSyn::p_stmt,CloneArgs(copy_stmt12_stmt,init_inh_stmt12_stmt)));				//	stmt
	p_p_stmt12->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_stmt12_S,0,0,init_syn_stmt12_S,del_syn_stmt12_S)));						//	S

	p_p_stmt13		=	new Produce(NonTerminalSyn::p_stmt);										//	stmt
	p_p_stmt13->clone_args.push_back(make_pair(Terminal::p_l_f_bracket,CloneArgs()));				//	{
	p_p_stmt13->clone_args.push_back(make_pair(NonTerminalDef::p_stmts,CloneArgs(copy_stmt13_stmts,init_inh_stmt13_stmts)));				//	stmts
	p_p_stmt13->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_stmt13_S,0,0,init_syn_stmt13_S,del_syn_stmt13_S)));						//	S
	p_p_stmt13->clone_args.push_back(make_pair(Terminal::p_r_f_bracket,CloneArgs()));				//	}

	p_p_else1			=	new Produce(NonTerminalDef::p_else);									//	E
	p_p_else1->clone_args.push_back(make_pair(Terminal::p_else,CloneArgs()));						//	else
	p_p_else1->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_E1_A,init_inh_E_A,del_inh_E_A,act_E1_A)));						//	A
	p_p_else1->clone_args.push_back(make_pair(NonTerminalSyn::p_stmt,CloneArgs(copy_E1_stmt,init_inh_E_stmt)));					//	stmt
	p_p_else1->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,init_inh_E_S,del_inh_E_S,act_E1_S,0,0,init_syn_E_S,del_syn_E_S)));						//	S

	p_p_else2			=	new Produce(NonTerminalDef::p_else);									// ¦Å
	p_p_else2->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_E2_A,init_inh_E_A,del_inh_E_A,act_E2_A)));						//	A

	p_p_stmts1		=	new Produce(NonTerminalDef::p_stmts);										//	stmts
	p_p_stmts1->clone_args.push_back(make_pair(NonTerminalSyn::p_stmt,CloneArgs(copy_stmts1_stmt,init_inh_stmts_stmt)));				//	stmt
	p_p_stmts1->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_stmts1_S1,0,0,init_syn_stmts_S1,del_syn_stmts_S1)));						//	S1
	p_p_stmts1->clone_args.push_back(make_pair(NonTerminalDef::p_stmts,CloneArgs(copy_stmts1_stmts,init_inh_stmts_stmts)));				//	stmts
	p_p_stmts1->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_stmts1_S2,0,0,init_syn_stmts_S2,del_syn_stmts_S2)));						//	S2

	p_p_stmts2		=	new Produce(NonTerminalDef::p_stmts);										// ¦Å

	p_p_optexpr2A	=	new Produce(NonTerminalDef::p_optexpr2);									//	optexpr2
	p_p_optexpr2A->clone_args.push_back(make_pair(NonTerminalSyn::p_expr,CloneArgs(0,init_inh_optexpr2_expr)));				//	expr
	p_p_optexpr2A->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_optexpr2A_S,init_inh_optexpr2_S,0,act_optexpr2A_S,0,0,init_syn_optexpr2_S,del_syn_optexpr2_S)));					//	S

	p_p_optexpr2B	=	new Produce(NonTerminalDef::p_optexpr2);									// ¦Å
	p_p_optexpr2B->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_optexpr2B_A,init_inh_optexpr2_A,0,act_optexpr2B_A)));					//	A

	p_p_optexpr3A	=	new Produce(NonTerminalDef::p_optexpr3);									//	optexpr3
	p_p_optexpr3A->clone_args.push_back(make_pair(NonTerminalSyn::p_expr,CloneArgs(0,init_inh_optexpr3_expr)));				//	expr
	p_p_optexpr3A->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_optexpr3A_S,init_inh_optexpr3_S,0,act_optexpr3A_S,0,0,init_syn_optexpr3_S,del_syn_optexpr3_S)));					//	S

	p_p_optexpr3B	=	new Produce(NonTerminalDef::p_optexpr3);									// ¦Å
	p_p_optexpr3B->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_optexpr3B_A,init_inh_optexpr3_A,0,act_optexpr3B_A)));					//	A
			
	p_p_label1		=	new Produce(NonTerminalSyn::p_label);										//	label
	p_p_label1->clone_args.push_back(make_pair(Terminal::p_false,CloneArgs()));						//	false
	p_p_label1->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_label_A,init_temp_label_A)));						//	A

	p_p_label2		=	new Produce(NonTerminalSyn::p_label);										//	label
	p_p_label2->clone_args.push_back(make_pair(Terminal::p_true,CloneArgs()));						//	true
	p_p_label2->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_label_A,init_temp_label_A)));						//	A

	p_p_label3		=	new Produce(NonTerminalSyn::p_label);										//	label
	p_p_label3->clone_args.push_back(make_pair(Terminal::p_ascii,CloneArgs()));						//	ascii
	p_p_label3->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_label_A,init_temp_label_A)));						//	A

	p_p_label4		=	new Produce(NonTerminalSyn::p_label);										//	label
	p_p_label4->clone_args.push_back(make_pair(Terminal::p_number,CloneArgs()));					//	num
	p_p_label4->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_label_A,init_temp_label_A)));						//	A

	p_p_label5		=	new Produce(NonTerminalSyn::p_label);										//	label
	p_p_label5->clone_args.push_back(make_pair(Terminal::p_sub,CloneArgs()));						//	-
	p_p_label5->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,0,init_temp_label_op_minus)));						//	A
	p_p_label5->clone_args.push_back(make_pair(Terminal::p_number,CloneArgs()));					//	num
	p_p_label5->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_label_A2,init_temp_label_A)));						//	A

	//...

	p_p_expr		=	new Produce(NonTerminalSyn::p_expr);										//	expr
	p_p_expr->clone_args.push_back(make_pair(NonTerminalSyn::p_e1,CloneArgs(copy_expr_e1,init_inh_expr_e1)));					//	e1
	p_p_expr->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_expr_S1,0,0,init_syn_expr_S1,del_syn_expr_S1)));						//	S1
	p_p_expr->clone_args.push_back(make_pair(NonTerminalDef::p_expr_,CloneArgs(copy_expr_expr_,init_inh_expr_expr_,del_inh_expr_expr_)));					//	expr'
	p_p_expr->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_expr_S2,0,0,init_syn_expr_S2,del_syn_expr_S2)));						//	S2

	p_p_expr_1		=	new Produce(NonTerminalDef::p_expr_);										//	expr'
	p_p_expr_1->clone_args.push_back(make_pair(Terminal::p_comma,CloneArgs()));						//	,
	p_p_expr_1->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_expr_1_A,init_inh_expr__A,del_inh_expr__A,act_expr_1_A)));						//	A
	p_p_expr_1->clone_args.push_back(make_pair(NonTerminalSyn::p_e1,CloneArgs(copy_expr_1_e1,init_inh_expr__e1)));					//	e1
	p_p_expr_1->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_expr_1_S1,0,0,init_syn_expr__S1,del_syn_expr__S1)));						//	S1
	p_p_expr_1->clone_args.push_back(make_pair(NonTerminalDef::p_expr_,CloneArgs(copy_expr_1_expr_,init_inh_expr__expr_,del_inh_expr__expr_)));				//	expr'
	p_p_expr_1->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_expr_1_S2,0,0,init_syn_expr__S2,del_syn_expr__S2)));						//	S2

	p_p_expr_2		=	new Produce(NonTerminalDef::p_expr_);										// ¦Å
	p_p_expr_2->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_expr_2_A,init_inh_expr__A,del_inh_expr__A,act_expr_2_A)));						//	A

	//...

	p_p_e1A			=	new Produce(NonTerminalSyn::p_e1);											//	e1
	p_p_e1A->clone_args.push_back(make_pair(Terminal::p_id,CloneArgs()));							//	id
	p_p_e1A->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_e1A_A,init_temp_e1A_A,del_temp_e1A_A)));							//	A
	p_p_e1A->clone_args.push_back(make_pair(NonTerminalDef::p_t1,CloneArgs(copy_e1A_T1,init_inh_e1A_T1,del_inh_e1A_T1)));						//	T1
	p_p_e1A->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e1A_S,0,0,init_syn_e1A_S,del_syn_e1A_S)));							//	S

	p_p_e1B			=	new Produce(NonTerminalSyn::p_e1);											//	e1
	p_p_e1B->clone_args.push_back(make_pair(NonTerminalSyn::p_e2,CloneArgs(copy_e1B_e2,init_inh_e1B_e2)));						//	e2
	p_p_e1B->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e1B_S,0,0,init_syn_e1B__S,del_syn_e1B_S)));							//	S

	//...

	p_p_e2			=	new Produce(NonTerminalSyn::p_e2);											//	e2
	p_p_e2->clone_args.push_back(make_pair(NonTerminalSyn::p_e3,CloneArgs(copy_e2_e3,init_inh_e2_e3)));						//	e3
	p_p_e2->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e2_S1,0,0,init_syn_e2_S1,del_syn_e2_S1)));							//	S1
	p_p_e2->clone_args.push_back(make_pair(NonTerminalDef::p_e2_,CloneArgs(copy_e2_e2_,init_inh_e2_e2_,del_inh_e2_e2_)));						//	e2'
	p_p_e2->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e2_S2,0,0,init_syn_e2_S2,del_syn_e2_S2)));							//	S2

	p_p_e2_1		=	new Produce(NonTerminalDef::p_e2_);											//	e2'
	p_p_e2_1->clone_args.push_back(make_pair(Terminal::p_question,CloneArgs()));					//	?
	p_p_e2_1->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_e2_1_A1,init_inh_e2_1_A1,del_inh_e2_1_A1,act_e2_1_A1,init_temp_e2_1_A1)));						//	A1
	p_p_e2_1->clone_args.push_back(make_pair(NonTerminalSyn::p_e3,CloneArgs(copy_e2_1_e3,init_inh_e2_1_e3)));					//	e3
	p_p_e2_1->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_e2_1_S1,init_inh_e2_1_S1,del_inh_e2_1_S1,act_e2_1_S1,0,0,init_syn_e2_1_S1,del_syn_e2_1_S1)));						//	S1
	p_p_e2_1->clone_args.push_back(make_pair(Terminal::p_colon,CloneArgs()));						//	:
	p_p_e2_1->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_e2_1_A2,init_temp_e2_1_A2)));						//	A2
	p_p_e2_1->clone_args.push_back(make_pair(NonTerminalSyn::p_e2,CloneArgs(copy_e2_1_e2,init_inh_e2_1_e2)));					//	e2
	p_p_e2_1->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_e2_1_S2,init_inh_e2_1_S2,del_inh_e2_1_S2,act_e2_1_S2,init_temp_e2_1_S2,0,init_syn_e2_1_S2,del_syn_e2_1_S2)));						//	S2

	p_p_e2_2		=	new Produce(NonTerminalDef::p_e2_);											// ¦Å
	p_p_e2_2->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_e2_2_A,init_inh_e2_2_A,del_inh_e2_2_A,act_e2_2_A)));						//	A

	//...

	p_p_e3			=	new Produce(NonTerminalSyn::p_e3);											//  e3
	p_p_e3->clone_args.push_back(make_pair(NonTerminalSyn::p_e4,CloneArgs(copy_e3_e4,init_inh_e3_e4)));						//	e4
	p_p_e3->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e3_S1,0,0,init_syn_e3_S1,del_syn_e3_S1)));							//	S1
	p_p_e3->clone_args.push_back(make_pair(NonTerminalDef::p_e3_,CloneArgs(copy_e3_e3_,init_inh_e3_e3_,del_inh_e3_e3_)));						//	e3'
	p_p_e3->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e3_S2,0,0,init_syn_e3_S2,del_syn_e3_S2)));							//	S2

	p_p_e3_1		=	new Produce(NonTerminalDef::p_e3_);											//  e3'
	p_p_e3_1->clone_args.push_back(make_pair(Terminal::p_log_or,CloneArgs()));						//	||
	p_p_e3_1->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_e3_1_A,init_inh_e3_1_A,del_inh_e3_1_A,act_e3_1_A,init_temp_e3_1_A)));						//	A
	p_p_e3_1->clone_args.push_back(make_pair(NonTerminalSyn::p_e4,CloneArgs(copy_e3_1_e4,init_inh_e3_1_e4)));					//	e4
	p_p_e3_1->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_e3_1_S1,init_inh_e3_1_S1,del_inh_e3_1_S1,act_e3_1_S1,init_temp_e3_1_S1,0,init_syn_e3_1_S1,del_syn_e3_1_S1)));						//	S1
	p_p_e3_1->clone_args.push_back(make_pair(NonTerminalDef::p_e3_,CloneArgs(copy_e3_1_e3_,init_inh_e3_e3_,del_inh_e3_e3_)));					//	e3'
	p_p_e3_1->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e3_1_S2,0,0,init_syn_e3_1_S2,del_syn_e3_1_S2)));						//	S2

	p_p_e3_2		=	new Produce(NonTerminalDef::p_e3_);											// ¦Å
	p_p_e3_2->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_e3_2_A,init_inh_e3_2_A,del_inh_e3_2_A,act_e3_2_A)));						//	A

	//...

	p_p_e4			=	new Produce(NonTerminalSyn::p_e4);											//  e4
	p_p_e4->clone_args.push_back(make_pair(NonTerminalSyn::p_e5,CloneArgs(copy_e4_e5,init_inh_e4_e5)));						//	e5
	p_p_e4->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e4_S1,0,0,init_syn_e4_S1,del_syn_e4_S1)));							//	S1
	p_p_e4->clone_args.push_back(make_pair(NonTerminalDef::p_e4_,CloneArgs(copy_e4_e4_,init_inh_e4_e4_,del_inh_e4_e4_)));						//	e4'
	p_p_e4->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e4_S2,0,0,init_syn_e4_S2,del_syn_e4_S2)));							//	S2

	p_p_e4_1		=	new Produce(NonTerminalDef::p_e4_);											//  e4'
	p_p_e4_1->clone_args.push_back(make_pair(Terminal::p_log_and,CloneArgs()));						//	&&
	p_p_e4_1->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_e4_1_A,init_inh_e4_1_A,del_inh_e4_1_A,act_e4_1_A,init_temp_e4_1_A)));						//	A
	p_p_e4_1->clone_args.push_back(make_pair(NonTerminalSyn::p_e5,CloneArgs(copy_e4_1_e5,init_inh_e4_1_e5)));					//	e5
	p_p_e4_1->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_e4_1_S1,init_inh_e4_1_S1,del_inh_e4_1_S1,act_e4_1_S1,init_temp_e4_1_S1,0,init_syn_e4_1_S1,del_syn_e4_1_S1)));						//	S1
	p_p_e4_1->clone_args.push_back(make_pair(NonTerminalDef::p_e4_,CloneArgs(copy_e4_1_e4_,init_inh_e4_1_e4_,del_inh_e4_1_e4_)));					//	e4'
	p_p_e4_1->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e4_1_S2,0,0,init_syn_e4_1_S2,del_syn_e4_1_S2)));						//	S2

	p_p_e4_2		=	new Produce(NonTerminalDef::p_e4_);											// ¦Å
	p_p_e4_2->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_e4_2_A,init_inh_e4_2_A,del_inh_e4_2_A,act_e4_2_A)));						//	A

	//...

	p_p_e5			=	new Produce(NonTerminalSyn::p_e5);											//  e5
	p_p_e5->clone_args.push_back(make_pair(NonTerminalSyn::p_e6,CloneArgs(copy_e5_e6,init_inh_e5_e6)));						//	e6
	p_p_e5->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e5_S1,0,0,init_syn_e5_S1,del_syn_e5_S1)));							//	S1
	p_p_e5->clone_args.push_back(make_pair(NonTerminalDef::p_e5_,CloneArgs(copy_e5_e5_,init_inh_e5_e5_,del_inh_e5_e5_)));						//	e5'
	p_p_e5->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e5_S2,0,0,init_syn_e5_S2,del_syn_e5_S2)));							//	S2

	p_p_e5_1		=	new Produce(NonTerminalDef::p_e5_);											//  e5'
	p_p_e5_1->clone_args.push_back(make_pair(Terminal::p_b_or,CloneArgs()));						//	|
	p_p_e5_1->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_e5_1_A,init_inh_e5_1_A,del_inh_e5_1_A,act_e5_1_A,init_temp_e5_1_A)));						//	A
	p_p_e5_1->clone_args.push_back(make_pair(NonTerminalSyn::p_e6,CloneArgs(copy_e5_1_e6,init_inh_e5_1_e6)));					//	e6
	p_p_e5_1->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_e5_1_S1,init_inh_e5_1_S1,del_inh_e5_1_S1,act_e5_1_S1,init_temp_e5_1_S1,0,init_syn_e5_1_S1,del_syn_e5_1_S1)));						//	S1
	p_p_e5_1->clone_args.push_back(make_pair(NonTerminalDef::p_e5_,CloneArgs(copy_e5_1_e5_,init_inh_e5_1_e5_,del_inh_e5_1_e5_)));					//	e5'
	p_p_e5_1->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e5_1_S2,0,0,init_syn_e5_1_S2,del_syn_e5_1_S2)));						//	S2

	p_p_e5_2		=	new Produce(NonTerminalDef::p_e5_);											// ¦Å
	p_p_e5_2->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_e5_2_A,init_inh_e5_2_A,del_inh_e5_2_A,act_e5_2_A)));						//	A

	//...

	p_p_e6			=	new Produce(NonTerminalSyn::p_e6);											//  e6
	p_p_e6->clone_args.push_back(make_pair(NonTerminalSyn::p_e7,CloneArgs(copy_e6_e7,init_inh_e6_e7)));						//	e7
	p_p_e6->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e6_S1,0,0,init_syn_e6_S1,del_syn_e6_S1)));							//	S1
	p_p_e6->clone_args.push_back(make_pair(NonTerminalDef::p_e6_,CloneArgs(copy_e6_e6_,init_inh_e6_e6_,del_inh_e6_e6_)));						//	e6'
	p_p_e6->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e6_S2,0,0,init_syn_e6_S2,del_syn_e6_S2)));							//	S2

	p_p_e6_1		=	new Produce(NonTerminalDef::p_e6_);											//  e6'
	p_p_e6_1->clone_args.push_back(make_pair(Terminal::p_b_xor,CloneArgs()));						//	^
	p_p_e6_1->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_e6_1_A,init_inh_e6_1_A,del_inh_e6_1_A,act_e6_1_A,init_temp_e6_1_A)));						//	A
	p_p_e6_1->clone_args.push_back(make_pair(NonTerminalSyn::p_e7,CloneArgs(copy_e6_1_e7,init_inh_e6_1_e7)));					//	e7
	p_p_e6_1->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_e6_1_S1,init_inh_e6_1_S1,del_inh_e6_1_S1,act_e6_1_S1,init_temp_e6_1_S1,0,init_syn_e6_1_S1,del_syn_e6_1_S1)));						//	S1
	p_p_e6_1->clone_args.push_back(make_pair(NonTerminalDef::p_e6_,CloneArgs(copy_e6_1_e6_,init_inh_e6_1_e6_,del_inh_e6_1_e6_)));					//	e6'
	p_p_e6_1->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e6_1_S2,0,0,init_syn_e6_1_S2,del_syn_e6_1_S2)));						//	S2

	p_p_e6_2		=	new Produce(NonTerminalDef::p_e6_);											// ¦Å
	p_p_e6_2->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_e6_2_A,init_inh_e6_2_A,del_inh_e6_2_A,act_e6_2_A)));						//	A

	//...

	p_p_e7			=	new Produce(NonTerminalSyn::p_e7);											//  e7
	p_p_e7->clone_args.push_back(make_pair(NonTerminalSyn::p_e8,CloneArgs(copy_e7_e8,init_inh_e7_e8)));						//	e8
	p_p_e7->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e7_S1,0,0,init_syn_e7_S1,del_syn_e7_S1)));							//	S1
	p_p_e7->clone_args.push_back(make_pair(NonTerminalDef::p_e7_,CloneArgs(copy_e7_e7_,init_inh_e7_e7_,del_inh_e7_e7_)));						//	e7'
	p_p_e7->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e7_S2,0,0,init_syn_e7_S2,del_syn_e7_S2)));							//	S2

	p_p_e7_1		=	new Produce(NonTerminalDef::p_e7_);											//  e7'
	p_p_e7_1->clone_args.push_back(make_pair(Terminal::p_b_and,CloneArgs()));						//	&
	p_p_e7_1->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_e7_1_A,init_inh_e7_1_A,del_inh_e7_1_A,act_e7_1_A,init_temp_e7_1_A)));						//	A
	p_p_e7_1->clone_args.push_back(make_pair(NonTerminalSyn::p_e8,CloneArgs(copy_e7_1_e8,init_inh_e7_1_e8)));					//	e8
	p_p_e7_1->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_e7_1_S1,init_inh_e7_1_S1,del_inh_e7_1_S1,act_e7_1_S1,init_temp_e7_1_S1,0,init_syn_e7_1_S1,del_syn_e7_1_S1)));						//	S1
	p_p_e7_1->clone_args.push_back(make_pair(NonTerminalDef::p_e7_,CloneArgs(copy_e7_1_e7_,init_inh_e7_1_e7_,del_inh_e7_1_e7_)));					//	e7'
	p_p_e7_1->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e7_1_S2,0,0,init_syn_e7_1_S2,del_syn_e7_1_S2)));						//	S2

	p_p_e7_2		=	new Produce(NonTerminalDef::p_e7_);											// ¦Å
	p_p_e7_2->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_e7_2_A,init_inh_e7_2_A,del_inh_e7_2_A,act_e7_2_A)));						//	A

	//...

	p_p_e8			=	new Produce(NonTerminalSyn::p_e8);											//	e8
	p_p_e8->clone_args.push_back(make_pair(NonTerminalSyn::p_e9,CloneArgs(copy_e8_e9,init_inh_e8_e9)));						//	e9
	p_p_e8->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e8_S1,0,0,init_syn_e8_S1,del_syn_e8_S1)));							//	S1
	p_p_e8->clone_args.push_back(make_pair(NonTerminalDef::p_e8_,CloneArgs(copy_e8_e8_,init_inh_e8_e8_,del_inh_e8_e8_)));						//	e8'
	p_p_e8->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e8_S2,0,0,init_syn_e8_S2,del_syn_e8_S2)));							//	S2

	p_p_e8_1		=	new Produce(NonTerminalDef::p_e8_);											//	e8'
	p_p_e8_1->clone_args.push_back(make_pair(Terminal::p_eq,CloneArgs()));							//	==
	p_p_e8_1->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_e8_1_A,init_inh_e8_1_A,del_inh_e8_1_A,act_e8_1_A,init_temp_e8_1_A)));						//	A
	p_p_e8_1->clone_args.push_back(make_pair(NonTerminalSyn::p_e9,CloneArgs(copy_e8_1_e9,init_inh_e8_1_e9)));					//	e9
	p_p_e8_1->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_e8_1_S1,init_inh_e8_1_S1,del_inh_e8_1_S1,act_e8_1_S1,init_temp_e8_1_S1,0,init_syn_e8_1_S1,del_syn_e8_1_S1)));						//	S1
	p_p_e8_1->clone_args.push_back(make_pair(NonTerminalDef::p_e8_,CloneArgs(copy_e8_1_e8_,init_inh_e8_1_e8_,del_inh_e8_1_e8_)));					//	e8'
	p_p_e8_1->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e8_1_S2,0,0,init_syn_e8_1_S2,del_syn_e8_1_S2)));						//	S2

	p_p_e8_2		=	new Produce(NonTerminalDef::p_e8_);											//  e8'
	p_p_e8_2->clone_args.push_back(make_pair(Terminal::p_ne,CloneArgs()));							//	!=
	p_p_e8_2->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_e8_2_A,init_inh_e8_1_A,del_inh_e8_1_A,act_e8_2_A,init_temp_e8_1_A)));						//	A
	p_p_e8_2->clone_args.push_back(make_pair(NonTerminalSyn::p_e9,CloneArgs(copy_e8_2_e9,init_inh_e8_1_e9)));					//	e9
	p_p_e8_2->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_e8_2_S1,init_inh_e8_1_S1,del_inh_e8_1_S1,act_e8_2_S1,init_temp_e8_1_S1,0,init_syn_e8_1_S1,del_syn_e8_1_S1)));						//	S1
	p_p_e8_2->clone_args.push_back(make_pair(NonTerminalDef::p_e8_,CloneArgs(copy_e8_2_e8_,init_inh_e8_1_e8_,del_inh_e8_1_e8_)));					//	e8'
	p_p_e8_2->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e8_2_S2,0,0,init_syn_e8_1_S2,del_syn_e8_1_S2)));						//	S2

	p_p_e8_3		=	new Produce(NonTerminalDef::p_e8_);											// ¦Å
	p_p_e8_3->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_e8_3_A,init_inh_e8_2_A,del_inh_e8_3_A,act_e8_3_A)));						//	A

	//...

	p_p_e9			=	new Produce(NonTerminalSyn::p_e9);											//  e9
	p_p_e9->clone_args.push_back(make_pair(NonTerminalSyn::p_e10,CloneArgs(copy_e9_e10,init_inh_e9_e10)));						//	e10
	p_p_e9->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e9_S1,0,0,init_syn_e9_S1,del_syn_e9_S1)));							//	S1
	p_p_e9->clone_args.push_back(make_pair(NonTerminalDef::p_e9_,CloneArgs(copy_e9_e9_,init_inh_e9_e9_,del_inh_e9_e9_)));						//	e9'
	p_p_e9->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e9_S2,0,0,init_syn_e9_S2,del_syn_e9_S2)));							//	S2

	p_p_e9_1		=	new Produce(NonTerminalDef::p_e9_);											//  e9'
	p_p_e9_1->clone_args.push_back(make_pair(Terminal::p_less,CloneArgs()));						//	<
	p_p_e9_1->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_e9_1_A,init_inh_e9_1_A,del_inh_e9_1_A,act_e9_1_A,init_temp_e9_1_A)));						//	A
	p_p_e9_1->clone_args.push_back(make_pair(NonTerminalSyn::p_e10,CloneArgs(copy_e9_1_e10,init_inh_e9_1_e10)));					//	e10
	p_p_e9_1->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_e9_1_S1,init_inh_e9_1_S1,del_inh_e9_1_S1,act_e9_1_S1,init_temp_e9_1_S1,0,init_syn_e9_1_S1,del_syn_e9_1_S1)));						//	S1
	p_p_e9_1->clone_args.push_back(make_pair(NonTerminalDef::p_e9_,CloneArgs(copy_e9_1_e9_,init_inh_e9_1_e9_,del_inh_e9_1_e9_)));					//	e9'
	p_p_e9_1->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e9_1_S2,0,0,init_syn_e9_1_S2,del_syn_e9_1_S2)));						//	S2

	p_p_e9_2		=	new Produce(NonTerminalDef::p_e9_);											//  e9'
	p_p_e9_2->clone_args.push_back(make_pair(Terminal::p_le,CloneArgs()));							//	<=
	p_p_e9_2->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_e9_2_A,init_inh_e9_1_A,del_inh_e9_1_A,act_e9_2_A,init_temp_e9_1_A)));						//	A
	p_p_e9_2->clone_args.push_back(make_pair(NonTerminalSyn::p_e10,CloneArgs(copy_e9_2_e10,init_inh_e9_1_e10)));					//	e10
	p_p_e9_2->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_e9_2_S1,init_inh_e9_1_S1,del_inh_e9_1_S1,act_e9_2_S1,init_temp_e9_1_S1,0,init_syn_e9_1_S1,del_syn_e9_1_S1)));						//	S1
	p_p_e9_2->clone_args.push_back(make_pair(NonTerminalDef::p_e9_,CloneArgs(copy_e9_2_e9_,init_inh_e9_1_e9_,del_inh_e9_1_e9_)));					//	e9'
	p_p_e9_2->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e9_2_S2,0,0,init_syn_e9_1_S2,del_syn_e9_1_S2)));						//	S2

	p_p_e9_3		=	new Produce(NonTerminalDef::p_e9_);											//  e9'
	p_p_e9_3->clone_args.push_back(make_pair(Terminal::p_greater,CloneArgs()));						//	>
	p_p_e9_3->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_e9_3_A,init_inh_e9_1_A,del_inh_e9_1_A,act_e9_3_A,init_temp_e9_1_A)));						//	A
	p_p_e9_3->clone_args.push_back(make_pair(NonTerminalSyn::p_e10,CloneArgs(copy_e9_3_e10,init_inh_e9_1_e10)));					//	e10
	p_p_e9_3->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_e9_3_S1,init_inh_e9_1_S1,del_inh_e9_1_S1,act_e9_3_S1,init_temp_e9_1_S1,0,init_syn_e9_1_S1,del_syn_e9_1_S1)));						//	S1
	p_p_e9_3->clone_args.push_back(make_pair(NonTerminalDef::p_e9_,CloneArgs(copy_e9_3_e9_,init_inh_e9_1_e9_,del_inh_e9_1_e9_)));					//	e9'
	p_p_e9_3->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e9_3_S2,0,0,init_syn_e9_1_S2,del_syn_e9_1_S2)));						//	S2

	p_p_e9_4		=	new Produce(NonTerminalDef::p_e9_);											//  e9'
	p_p_e9_4->clone_args.push_back(make_pair(Terminal::p_ge,CloneArgs()));							//	>=
	p_p_e9_4->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_e9_4_A,init_inh_e9_1_A,del_inh_e9_1_A,act_e9_4_A,init_temp_e9_1_A)));						//	A
	p_p_e9_4->clone_args.push_back(make_pair(NonTerminalSyn::p_e10,CloneArgs(copy_e9_4_e10,init_inh_e9_1_e10)));					//	e10
	p_p_e9_4->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_e9_4_S1,init_inh_e9_1_S1,del_inh_e9_1_S1,act_e9_4_S1,init_temp_e9_1_S1,0,init_syn_e9_1_S1,del_syn_e9_1_S1)));						//	S1
	p_p_e9_4->clone_args.push_back(make_pair(NonTerminalDef::p_e9_,CloneArgs(copy_e9_4_e9_,init_inh_e9_1_e9_,del_inh_e9_1_e9_)));					//	e9'
	p_p_e9_4->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e9_4_S2,0,0,init_syn_e9_1_S2,del_syn_e9_1_S2)));						//	S2

	p_p_e9_5		=	new Produce(NonTerminalDef::p_e9_);											// ¦Å
	p_p_e9_5->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_e9_5_A,init_inh_e9_2_A,del_inh_e9_2_A,act_e9_5_A)));						//	A

	//...

	p_p_e10			=	new Produce(NonTerminalSyn::p_e10);											//  e10
	p_p_e10->clone_args.push_back(make_pair(NonTerminalSyn::p_e11,CloneArgs(copy_e10_e11,init_inh_e10_e11)));					//	e11
	p_p_e10->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e10_S1,0,0,init_syn_e10_S1,del_syn_e10_S1)));						//	S1
	p_p_e10->clone_args.push_back(make_pair(NonTerminalDef::p_e10_,CloneArgs(copy_e10_e10_,init_inh_e10_e10_,del_inh_e10_e10_)));					//	e10'
	p_p_e10->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e10_S2,0,0,init_syn_e10_S2,del_syn_e10_S2)));						//	S2

	p_p_e10_1		=	new Produce(NonTerminalDef::p_e10_);										//  e10'
	p_p_e10_1->clone_args.push_back(make_pair(Terminal::p_l_sht,CloneArgs()));						//	<<
	p_p_e10_1->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_e10_1_A,init_inh_e10_1_A,del_inh_e10_1_A,act_e10_1_A,init_temp_e10_1_A)));						//	A
	p_p_e10_1->clone_args.push_back(make_pair(NonTerminalSyn::p_e11,CloneArgs(copy_e10_1_e11,init_inh_e10_1_e11)));					//	e11
	p_p_e10_1->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_e10_1_S1,init_inh_e10_1_S1,del_inh_e10_1_S1,act_e10_1_S1,init_temp_e10_1_S1,0,init_syn_e10_1_S1,del_syn_e10_1_S1)));						//	S1
	p_p_e10_1->clone_args.push_back(make_pair(NonTerminalDef::p_e10_,CloneArgs(copy_e10_1_e10_,init_inh_e10_1_e10_,del_inh_e10_1_e10_)));					//	e10'
	p_p_e10_1->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e10_1_S2,0,0,init_syn_e10_1_S2,del_syn_e10_1_S2)));						//	S2

	p_p_e10_2		=	new Produce(NonTerminalDef::p_e10_);										//  e10'
	p_p_e10_2->clone_args.push_back(make_pair(Terminal::p_r_sht,CloneArgs()));						//	>>
	p_p_e10_2->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_e10_2_A,init_inh_e10_1_A,del_inh_e10_1_A,act_e10_2_A,init_temp_e10_1_A)));						//	A
	p_p_e10_2->clone_args.push_back(make_pair(NonTerminalSyn::p_e11,CloneArgs(copy_e10_2_e11,init_inh_e10_1_e11)));					//	e11
	p_p_e10_2->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_e10_2_S1,init_inh_e10_1_S1,del_inh_e10_1_S1,act_e10_2_S1,init_temp_e10_1_S1,0,init_syn_e10_1_S1,del_syn_e10_1_S1)));						//	S1
	p_p_e10_2->clone_args.push_back(make_pair(NonTerminalDef::p_e10_,CloneArgs(copy_e10_2_e10_,init_inh_e10_1_e10_,del_inh_e10_1_e10_)));					//	e10'
	p_p_e10_2->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e10_2_S2,0,0,init_syn_e10_1_S2,del_syn_e10_1_S2)));						//	S2

	p_p_e10_3		=	new Produce(NonTerminalDef::p_e10_);										// ¦Å
	p_p_e10_3->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_e10_3_A,init_inh_e10_2_A,del_inh_e10_2_A,act_e10_3_A)));						//	A

	//...

	p_p_e11			=	new Produce(NonTerminalSyn::p_e11);											//  e11
	p_p_e11->clone_args.push_back(make_pair(NonTerminalSyn::p_e12,CloneArgs(copy_e11_e12,init_inh_e11_e12)));					//	e12
	p_p_e11->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e11_S1,0,0,init_syn_e11_S1,del_syn_e11_S1)));						//	S1
	p_p_e11->clone_args.push_back(make_pair(NonTerminalDef::p_e11_,CloneArgs(copy_e11_e11_,init_inh_e11_e11_,del_inh_e11_e11_)));					//	e11'
	p_p_e11->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e11_S2,0,0,init_syn_e11_S2,del_syn_e11_S2)));						//	S2

	p_p_e11_1		=	new Produce(NonTerminalDef::p_e11_);										//  e11'
	p_p_e11_1->clone_args.push_back(make_pair(Terminal::p_add,CloneArgs()));						//	+
	p_p_e11_1->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_e11_1_A,init_inh_e11_1_A,del_inh_e11_1_A,act_e11_1_A,init_temp_e11_1_A)));						//	A
	p_p_e11_1->clone_args.push_back(make_pair(NonTerminalSyn::p_e12,CloneArgs(copy_e11_1_e12,init_inh_e11_1_e12)));					//	e12
	p_p_e11_1->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_e11_1_S1,init_inh_e11_1_S1,del_inh_e11_1_S1,act_e11_1_S1,init_temp_e11_1_S1,0,init_syn_e11_1_S1,del_syn_e11_1_S1)));			//	S1
	p_p_e11_1->clone_args.push_back(make_pair(NonTerminalDef::p_e11_,CloneArgs(copy_e11_1_e11_,init_inh_e11_1_e11_,del_inh_e11_1_e11_)));					//	e11'
	p_p_e11_1->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e11_1_S2,0,0,init_syn_e11_1_S2,del_syn_e11_1_S2)));						//	S2

	p_p_e11_2		=	new Produce(NonTerminalDef::p_e11_);										//	e11'
	p_p_e11_2->clone_args.push_back(make_pair(Terminal::p_sub,CloneArgs()));						//	-
	p_p_e11_2->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_e11_2_A,init_inh_e11_1_A,del_inh_e11_1_A,act_e11_2_A,init_temp_e11_1_A)));						//	A
	p_p_e11_2->clone_args.push_back(make_pair(NonTerminalSyn::p_e12,CloneArgs(copy_e11_2_e12,init_inh_e11_1_e12)));					//	e12
	p_p_e11_2->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_e11_2_S1,init_inh_e11_1_S1,del_inh_e11_1_S1,act_e11_2_S1,init_temp_e11_1_S1,0,init_syn_e11_1_S1,del_syn_e11_1_S1)));						//	S1
	p_p_e11_2->clone_args.push_back(make_pair(NonTerminalDef::p_e11_,CloneArgs(copy_e11_2_e11_,init_inh_e11_1_e11_,del_inh_e11_1_e11_)));					//	e11'
	p_p_e11_2->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e11_2_S2,0,0,init_syn_e11_1_S2,del_syn_e11_1_S2)));						//	S2

	p_p_e11_3		=	new Produce(NonTerminalDef::p_e11_);										// ¦Å
	p_p_e11_3->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_e11_3_A,init_inh_e11_2_A,del_inh_e11_2_A,act_e11_3_A)));						//	A

	//...

	p_p_e12			=	new Produce(NonTerminalSyn::p_e12);											//	e12
	p_p_e12->clone_args.push_back(make_pair(NonTerminalSyn::p_e13,CloneArgs(copy_e12_e13,init_inh_e12_e13)));					//	e13
	p_p_e12->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e12_S1,0,0,init_syn_e12_S1,del_syn_e12_S1)));						//	S1
	p_p_e12->clone_args.push_back(make_pair(NonTerminalDef::p_e12_,CloneArgs(copy_e12_e12_,init_inh_e12_e12_,del_inh_e12_e12_)));					//	e12'
	p_p_e12->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e12_S2,0,0,init_syn_e12_S2,del_syn_e12_S2)));						//	S2

	p_p_e12_1		=	new Produce(NonTerminalDef::p_e12_);										//	e12'
	p_p_e12_1->clone_args.push_back(make_pair(Terminal::p_mul,CloneArgs()));						//	*
	p_p_e12_1->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_e12_1_A,init_inh_e12_1_A,del_inh_e12_1_A,act_e12_1_A,init_temp_e12_1_A)));						//	A
	p_p_e12_1->clone_args.push_back(make_pair(NonTerminalSyn::p_e13,CloneArgs(copy_e12_1_e13,init_inh_e12_1_e13)));					//	e13
	p_p_e12_1->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_e12_1_S1,init_inh_e12_1_S1,del_inh_e12_1_S1,act_e12_1_S1,init_temp_e12_1_S1,0,init_syn_e12_1_S1,del_syn_e12_1_S1)));						//	S1
	p_p_e12_1->clone_args.push_back(make_pair(NonTerminalDef::p_e12_,CloneArgs(copy_e12_1_e12_,init_inh_e12_1_e12_,del_inh_e12_1_e12_)));					//	e12'
	p_p_e12_1->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e12_1_S2,0,0,init_syn_e12_1_S2,del_syn_e12_1_S2)));						//	S2

	p_p_e12_2		=	new Produce(NonTerminalDef::p_e12_);										//	e12'
	p_p_e12_2->clone_args.push_back(make_pair(Terminal::p_div,CloneArgs()));						//	/
	p_p_e12_2->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_e12_2_A,init_inh_e12_1_A,del_inh_e12_1_A,act_e12_2_A,init_temp_e12_1_A)));						//	A
	p_p_e12_2->clone_args.push_back(make_pair(NonTerminalSyn::p_e13,CloneArgs(copy_e12_2_e13,init_inh_e12_1_e13)));					//	e13
	p_p_e12_2->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_e12_2_S1,init_inh_e12_1_S1,del_inh_e12_1_S1,act_e12_2_S1,init_temp_e12_1_S1,0,init_syn_e12_1_S1,del_syn_e12_1_S1)));						//	S1
	p_p_e12_2->clone_args.push_back(make_pair(NonTerminalDef::p_e12_,CloneArgs(copy_e12_2_e12_,init_inh_e12_1_e12_,del_inh_e12_1_e12_)));					//	e12'
	p_p_e12_2->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e12_2_S2,0,0,init_syn_e12_1_S2,del_syn_e12_1_S2)));						//	S2

	p_p_e12_3		=	new Produce(NonTerminalDef::p_e12_);										//	e12'
	p_p_e12_3->clone_args.push_back(make_pair(Terminal::p_mod,CloneArgs()));						//	%
	p_p_e12_3->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_e12_3_A,init_inh_e12_1_A,del_inh_e12_1_A,act_e12_3_A,init_temp_e12_1_A)));						//	A
	p_p_e12_3->clone_args.push_back(make_pair(NonTerminalSyn::p_e13,CloneArgs(copy_e12_3_e13,init_inh_e12_1_e13)));					//	e13
	p_p_e12_3->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_e12_3_S1,init_inh_e12_1_S1,del_inh_e12_1_S1,act_e12_3_S1,init_temp_e12_1_S1,0,init_syn_e12_1_S1,del_syn_e12_1_S1)));						//	S1
	p_p_e12_3->clone_args.push_back(make_pair(NonTerminalDef::p_e12_,CloneArgs(copy_e12_3_e12_,init_inh_e12_1_e12_,del_inh_e12_1_e12_)));					//	e12'
	p_p_e12_3->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e12_3_S2,0,0,init_syn_e12_1_S2,del_syn_e12_1_S2)));						//	S2

	p_p_e12_4		=	new Produce(NonTerminalDef::p_e12_);										// ¦Å
	p_p_e12_4->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_e12_4_A,init_inh_e12_2_A,del_inh_e12_2_A,act_e12_4_A)));						//	A

	//...

	p_p_e13A		=	new Produce(NonTerminalSyn::p_e13);											// e13
	p_p_e13A->clone_args.push_back(make_pair(Terminal::p_b_not,CloneArgs()));						//	~
	p_p_e13A->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_e13_A,init_temp_e13_A)));						//	A
	p_p_e13A->clone_args.push_back(make_pair(NonTerminalSyn::p_e13,CloneArgs(copy_e13_e13,init_inh_e13_e13)));					//	e13
	p_p_e13A->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_e13_S,init_inh_e13_S,0,act_e13A_S,init_temp_e13_S,0,init_syn_e13_S,del_syn_e13_S)));						//	S

	p_p_e13B		=	new Produce(NonTerminalSyn::p_e13);											// e13
	p_p_e13B->clone_args.push_back(make_pair(Terminal::p_log_not,CloneArgs()));						//	!
	p_p_e13B->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_e13_A,init_temp_e13_A)));						//	A
	p_p_e13B->clone_args.push_back(make_pair(NonTerminalSyn::p_e13,CloneArgs(copy_e13_e13,init_inh_e13_e13)));					//	e13
	p_p_e13B->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_e13_S,init_inh_e13_S,0,act_e13B_S,init_temp_e13_S,0,init_syn_e13_S,del_syn_e13_S)));						//	S

	p_p_e13C		=	new Produce(NonTerminalSyn::p_e13);											// e13
	p_p_e13C->clone_args.push_back(make_pair(Terminal::p_sub,CloneArgs()));							//	-
	p_p_e13C->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_e13_A,init_temp_e13_A)));						//	A
	p_p_e13C->clone_args.push_back(make_pair(NonTerminalSyn::p_e13,CloneArgs(copy_e13_e13,init_inh_e13_e13)));					//	e13
	p_p_e13C->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_e13_S,init_inh_e13_S,0,act_e13C_S,init_temp_e13_S,0,init_syn_e13_S,del_syn_e13_S)));						//	S

	p_p_e13D		=	new Produce(NonTerminalSyn::p_e13);											// e13
	p_p_e13D->clone_args.push_back(make_pair(Terminal::p_add,CloneArgs()));							//	+
	p_p_e13D->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_e13_A,init_temp_e13_A)));						//	A
	p_p_e13D->clone_args.push_back(make_pair(NonTerminalSyn::p_e13,CloneArgs(copy_e13_e13,init_inh_e13_e13)));					//	e13
	p_p_e13D->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_e13_S,init_inh_e13_S,0,act_e13D_S,init_temp_e13_S,0,init_syn_e13_S,del_syn_e13_S)));						//	S

	p_p_e13E		=	new Produce(NonTerminalSyn::p_e13);											// e13
	p_p_e13E->clone_args.push_back(make_pair(NonTerminalSyn::p_e14,CloneArgs(copy_e13_e14,init_inh_e13_e14)));					//	e14
	p_p_e13E->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e13E_S,0,0,init_syn_e13E_S,del_syn_e13E_S)));						//	S

	//...

	p_p_e14A		=	new Produce(NonTerminalSyn::p_e14);											//	e14
	p_p_e14A->clone_args.push_back(make_pair(Terminal::p_true,CloneArgs()));						//	true
	p_p_e14A->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_e14A_A,init_temp_e14_A)));						//	A

	p_p_e14B		=	new Produce(NonTerminalSyn::p_e14);											//	e14
	p_p_e14B->clone_args.push_back(make_pair(Terminal::p_false,CloneArgs()));						//	false
	p_p_e14B->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_e14B_A,init_temp_e14_A)));						//	A

	p_p_e14C		=	new Produce(NonTerminalSyn::p_e14);											//	e14
	p_p_e14C->clone_args.push_back(make_pair(Terminal::p_ascii,CloneArgs()));						//	ascii
	p_p_e14C->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_e14C_A,init_temp_e14_A)));						//	A

	p_p_e14D		=	new Produce(NonTerminalSyn::p_e14);											//	e14
	p_p_e14D->clone_args.push_back(make_pair(Terminal::p_number,CloneArgs()));						//	num
	p_p_e14D->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_e14D_A,init_temp_e14_A)));						//	A

	p_p_e14E		=	new Produce(NonTerminalSyn::p_e14);											//	e14
	p_p_e14E->clone_args.push_back(make_pair(Terminal::p_real,CloneArgs()));						//	real
	p_p_e14E->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_e14E_A,init_temp_e14E_A)));

	p_p_e14F		=	new Produce(NonTerminalSyn::p_e14);											//	e14
	p_p_e14F->clone_args.push_back(make_pair(Terminal::p_plus_plus,CloneArgs()));					//	++
	p_p_e14F->clone_args.push_back(make_pair(NonTerminalSyn::p_loc,CloneArgs(copy_e14F_loc,init_inh_e14FG_loc)));					//	loc
	p_p_e14F->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e14FG_S,0,0,init_syn_e14FG_S)));						//	S

	p_p_e14G		=	new Produce(NonTerminalSyn::p_e14);											//	e14
	p_p_e14G->clone_args.push_back(make_pair(Terminal::p_minus_minus,CloneArgs()));					//	--
	p_p_e14G->clone_args.push_back(make_pair(NonTerminalSyn::p_loc,CloneArgs(copy_e14G_loc,init_inh_e14FG_loc)));					//	loc
	p_p_e14G->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e14FG_S,0,0,init_syn_e14FG_S)));						//	S

	p_p_e14H		=	new Produce(NonTerminalSyn::p_e14);											//	e14
	p_p_e14H->clone_args.push_back(make_pair(Terminal::p_l_bracket,CloneArgs()));					//	(
	p_p_e14H->clone_args.push_back(make_pair(NonTerminalSyn::p_expr,CloneArgs(copy_e14H_expr,init_inh_e14H_expr)));					//	expr
	p_p_e14H->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e14H_S,0,0,init_syn_e14H_S,del_syn_e14H_S)));						//	S
	p_p_e14H->clone_args.push_back(make_pair(Terminal::p_r_bracket,CloneArgs()));					//	)

	p_p_e14I		=	new Produce(NonTerminalSyn::p_e14);											//	e14
	p_p_e14I->clone_args.push_back(make_pair(Terminal::p_id,CloneArgs()));							//	id
	p_p_e14I->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_e14I_A,init_temp_e14I_A,del_temp_e14I_A)));						//	A
	p_p_e14I->clone_args.push_back(make_pair(NonTerminalDef::p_t3,CloneArgs(copy_e14I_T3,init_inh_e14I_T3,del_inh_e14I_T3)));					//	T3
	p_p_e14I->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_e14I_S,0,0,init_syn_e14I_S)));						//	S

	//...

	p_p_t1A			=	new Produce(NonTerminalDef::p_t1);											//	t1
	p_p_t1A->clone_args.push_back(make_pair(Terminal::p_plus_plus,CloneArgs()));					//	++
	p_p_t1A->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T1_A,init_inh_T1_A,del_inh_T1_A,act_T1A_A)));						//	A
	p_p_t1A->clone_args.push_back(make_pair(NonTerminalDef::p_t5,CloneArgs(copy_T1_T5,init_inh_T5)));											//  T5
	p_p_t1A->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5_S,0,0,init_syn_T5_S,del_syn_T5_S)));						//  S

	p_p_t1B			=	new Produce(NonTerminalDef::p_t1);											//	t1
	p_p_t1B->clone_args.push_back(make_pair(Terminal::p_minus_minus,CloneArgs()));					//	--
	p_p_t1B->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T1_A,init_inh_T1_A,del_inh_T1_A,act_T1B_A)));						//	A
	p_p_t1B->clone_args.push_back(make_pair(NonTerminalDef::p_t5,CloneArgs(copy_T1_T5,init_inh_T5)));											//  T5
	p_p_t1B->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5_S,0,0,init_syn_T5_S,del_syn_T5_S)));						//  S

	p_p_t1C			=	new Produce(NonTerminalDef::p_t1);											//	t1
	p_p_t1C->clone_args.push_back(make_pair(Terminal::p_l_bracket,CloneArgs()));																//	(
	p_p_t1C->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T1_A,init_inh_T1_A,del_inh_T1_A,act_T1C_A)));						//	A
	p_p_t1C->clone_args.push_back(make_pair(NonTerminalDef::p_args,CloneArgs(copy_T1C_args,init_inh_T1C_args,del_inh_T1C_args)));				//	args
	p_p_t1C->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1C_S,0,0,init_syn_T1C_S)));									//	S
	p_p_t1C->clone_args.push_back(make_pair(Terminal::p_r_bracket,CloneArgs()));																//	)
	p_p_t1C->clone_args.push_back(make_pair(NonTerminalDef::p_t5,CloneArgs(copy_T1_T5,init_inh_T5)));											//  T5
	p_p_t1C->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5_S,0,0,init_syn_T5_S,del_syn_T5_S)));						//  S

	p_p_t1D			=	new Produce(NonTerminalDef::p_t1);											//	t1
	p_p_t1D->clone_args.push_back(make_pair(Terminal::p_l_s_bracket,CloneArgs()));					//	[
	p_p_t1D->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T1_A,init_inh_T1_A,del_inh_T1_A,act_T1D_A)));						//	A
	p_p_t1D->clone_args.push_back(make_pair(NonTerminalSyn::p_expr,CloneArgs(copy_T1D_expr,init_inh_T1D_expr)));					//	expr
	p_p_t1D->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_T1D_S1,init_inh_T1D_S1,del_inh_T1D_S1,act_T1D_S1,0,0,init_syn_T1D_S1,del_syn_T1D_S1)));						//	S1
	p_p_t1D->clone_args.push_back(make_pair(Terminal::p_r_s_bracket,CloneArgs()));					//	]
	p_p_t1D->clone_args.push_back(make_pair(NonTerminalDef::p_t2,CloneArgs(copy_T1D_T2,init_inh_T1D_T2,del_inh_T1D_T2)));						//	T2
	p_p_t1D->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1D_S2,0,0,init_syn_T1D_S2,del_syn_T1D_S2)));						//	S2

	p_p_t1E			=	new Produce(NonTerminalDef::p_t1);											//	t1
	p_p_t1E->clone_args.push_back(make_pair(Terminal::p_assign,CloneArgs()));						//	=
	p_p_t1E->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_T1E_A,init_temp_T1E_A)));						//	A
	p_p_t1E->clone_args.push_back(make_pair(NonTerminalSyn::p_e1,CloneArgs(copy_T1E_e1,init_inh_T1E_e1)));						//	e1
	p_p_t1E->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_T1E_S,init_inh_T1E_S,del_inh_T1E_S,act_T1E_S,init_temp_T1E_S,0,init_syn_T1E_S,del_syn_T1E_S)));						//	S

	p_p_t1F			=	new Produce(NonTerminalDef::p_t1);											//	t1
	p_p_t1F->clone_args.push_back(make_pair(Terminal::p_mul_ass,CloneArgs()));						//	*=
	p_p_t1F->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_T1E_A,init_temp_T1E_A)));						//	A
	p_p_t1F->clone_args.push_back(make_pair(NonTerminalSyn::p_e1,CloneArgs(copy_T1E_e1,init_inh_T1E_e1)));						//	e1
	p_p_t1F->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_T1E_S,init_inh_T1E_S,del_inh_T1E_S,act_T1F_S,init_temp_T1E_S,0,init_syn_T1E_S,del_syn_T1E_S)));						//	S

	p_p_t1G			=	new Produce(NonTerminalDef::p_t1);											//	t1
	p_p_t1G->clone_args.push_back(make_pair(Terminal::p_div_ass,CloneArgs()));						//	/=
	p_p_t1G->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_T1E_A,init_temp_T1E_A)));						//	A
	p_p_t1G->clone_args.push_back(make_pair(NonTerminalSyn::p_e1,CloneArgs(copy_T1E_e1,init_inh_T1E_e1)));						//	e1
	p_p_t1G->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_T1E_S,init_inh_T1E_S,del_inh_T1E_S,act_T1G_S,init_temp_T1E_S,0,init_syn_T1E_S,del_syn_T1E_S)));						//	S

	p_p_t1H			=	new Produce(NonTerminalDef::p_t1);											//	t1
	p_p_t1H->clone_args.push_back(make_pair(Terminal::p_mod_ass,CloneArgs()));						//	%=
	p_p_t1H->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_T1E_A,init_temp_T1E_A)));						//	A
	p_p_t1H->clone_args.push_back(make_pair(NonTerminalSyn::p_e1,CloneArgs(copy_T1E_e1,init_inh_T1E_e1)));						//	e1
	p_p_t1H->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_T1E_S,init_inh_T1E_S,del_inh_T1E_S,act_T1H_S,init_temp_T1E_S,0,init_syn_T1E_S,del_syn_T1E_S)));						//	S

	p_p_t1I			=	new Produce(NonTerminalDef::p_t1);											//	t1
	p_p_t1I->clone_args.push_back(make_pair(Terminal::p_add_ass,CloneArgs()));						//	+=
	p_p_t1I->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_T1E_A,init_temp_T1E_A)));						//	A
	p_p_t1I->clone_args.push_back(make_pair(NonTerminalSyn::p_e1,CloneArgs(copy_T1E_e1,init_inh_T1E_e1)));						//	e1
	p_p_t1I->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_T1E_S,init_inh_T1E_S,del_inh_T1E_S,act_T1I_S,init_temp_T1E_S,0,init_syn_T1E_S,del_syn_T1E_S)));						//	S

	p_p_t1J			=	new Produce(NonTerminalDef::p_t1);											//	t1
	p_p_t1J->clone_args.push_back(make_pair(Terminal::p_sub_ass,CloneArgs()));						//	-=
	p_p_t1J->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_T1E_A,init_temp_T1E_A)));						//	A
	p_p_t1J->clone_args.push_back(make_pair(NonTerminalSyn::p_e1,CloneArgs(copy_T1E_e1,init_inh_T1E_e1)));						//	e1
	p_p_t1J->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_T1E_S,init_inh_T1E_S,del_inh_T1E_S,act_T1J_S,init_temp_T1E_S,0,init_syn_T1E_S,del_syn_T1E_S)));						//	S

	p_p_t1K			=	new Produce(NonTerminalDef::p_t1);											//	t1
	p_p_t1K->clone_args.push_back(make_pair(Terminal::p_l_sht_ass,CloneArgs()));					//	<<=
	p_p_t1K->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_T1E_A,init_temp_T1E_A)));						//	A
	p_p_t1K->clone_args.push_back(make_pair(NonTerminalSyn::p_e1,CloneArgs(copy_T1E_e1,init_inh_T1E_e1)));						//	e1
	p_p_t1K->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_T1E_S,init_inh_T1E_S,del_inh_T1E_S,act_T1K_S,init_temp_T1E_S,0,init_syn_T1E_S,del_syn_T1E_S)));						//	S

	p_p_t1L			=	new Produce(NonTerminalDef::p_t1);											//	t1
	p_p_t1L->clone_args.push_back(make_pair(Terminal::p_r_sht_ass,CloneArgs()));					//	>>=
	p_p_t1L->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_T1E_A,init_temp_T1E_A)));						//	A
	p_p_t1L->clone_args.push_back(make_pair(NonTerminalSyn::p_e1,CloneArgs(copy_T1E_e1,init_inh_T1E_e1)));						//	e1
	p_p_t1L->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_T1E_S,init_inh_T1E_S,del_inh_T1E_S,act_T1L_S,init_temp_T1E_S,0,init_syn_T1E_S,del_syn_T1E_S)));						//	S

	p_p_t1M			=	new Produce(NonTerminalDef::p_t1);											//	t1
	p_p_t1M->clone_args.push_back(make_pair(Terminal::p_b_and_ass,CloneArgs()));					//	&=
	p_p_t1M->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_T1E_A,init_temp_T1E_A)));						//	A
	p_p_t1M->clone_args.push_back(make_pair(NonTerminalSyn::p_e1,CloneArgs(copy_T1E_e1,init_inh_T1E_e1)));						//	e1
	p_p_t1M->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_T1E_S,init_inh_T1E_S,del_inh_T1E_S,act_T1M_S,init_temp_T1E_S,0,init_syn_T1E_S,del_syn_T1E_S)));						//	S

	p_p_t1N			=	new Produce(NonTerminalDef::p_t1);											//	t1
	p_p_t1N->clone_args.push_back(make_pair(Terminal::p_b_or_ass,CloneArgs()));						//	|=
	p_p_t1N->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_T1E_A,init_temp_T1E_A)));						//	A
	p_p_t1N->clone_args.push_back(make_pair(NonTerminalSyn::p_e1,CloneArgs(copy_T1E_e1,init_inh_T1E_e1)));						//	e1
	p_p_t1N->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_T1E_S,init_inh_T1E_S,del_inh_T1E_S,act_T1N_S,init_temp_T1E_S,0,init_syn_T1E_S,del_syn_T1E_S)));						//	S

	p_p_t1O			=	new Produce(NonTerminalDef::p_t1);											//	t1
	p_p_t1O->clone_args.push_back(make_pair(Terminal::p_b_xor_ass,CloneArgs()));					//	^=
	p_p_t1O->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_T1E_A,init_temp_T1E_A)));						//	A
	p_p_t1O->clone_args.push_back(make_pair(NonTerminalSyn::p_e1,CloneArgs(copy_T1E_e1,init_inh_T1E_e1)));						//	e1
	p_p_t1O->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_T1E_S,init_inh_T1E_S,del_inh_T1E_S,act_T1O_S,init_temp_T1E_S,0,init_syn_T1E_S,del_syn_T1E_S)));						//	S

	p_p_t1P			=	new Produce(NonTerminalDef::p_t1);											//	t1
	p_p_t1P->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T1Z_A,init_inh_T1Z_A,del_inh_T1Z_A,act_T1P_A)));						//	A
	p_p_t1P->clone_args.push_back(make_pair(NonTerminalDef::p_e2_,CloneArgs(copy_T1Z_e2_,init_inh_T1Z_e2_,del_inh_T1Z_e2_)));					//	e2'
	p_p_t1P->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1P_S,0,0,init_syn_T1Z_e2_,del_syn_T1Z_e2_)));						//	S

	p_p_t1Q			=	new Produce(NonTerminalDef::p_t1);											//	t1
	p_p_t1Q->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T1Z_A,init_inh_T1Z_A,del_inh_T1Z_A,act_T1Q_A)));						//	A
	p_p_t1Q->clone_args.push_back(make_pair(NonTerminalDef::p_e3_,CloneArgs(copy_T1Z_e3_,init_inh_T1Z_e3_,del_inh_T1Z_e3_)));					//	e3'
	p_p_t1Q->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1Q_S1,0,0,init_syn_T1Z_e3_,del_syn_T1Z_e3_)));						//	S1
	p_p_t1Q->clone_args.push_back(make_pair(NonTerminalDef::p_e2_,CloneArgs(copy_T1Z_e2_,init_inh_T1Z_e2_,del_inh_T1Z_e2_)));					//	e2'
	p_p_t1Q->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1Q_S2,0,0,init_syn_T1Z_e2_,del_syn_T1Z_e2_)));						//	S2

	p_p_t1R			=	new Produce(NonTerminalDef::p_t1);											//	t1
	p_p_t1R->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T1Z_A,init_inh_T1Z_A,del_inh_T1Z_A,act_T1R_A)));						//	A
	p_p_t1R->clone_args.push_back(make_pair(NonTerminalDef::p_e4_,CloneArgs(copy_T1Z_e4_,init_inh_T1Z_e4_,del_inh_T1Z_e4_)));					//	e4'
	p_p_t1R->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1R_S1,0,0,init_syn_T1Z_e4_,del_syn_T1Z_e4_)));						//	S1
	p_p_t1R->clone_args.push_back(make_pair(NonTerminalDef::p_e3_,CloneArgs(copy_T1Z_e3_,init_inh_T1Z_e3_,del_inh_T1Z_e3_)));					//	e3'
	p_p_t1R->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1R_S2,0,0,init_syn_T1Z_e3_,del_syn_T1Z_e3_)));						//	S2
	p_p_t1R->clone_args.push_back(make_pair(NonTerminalDef::p_e2_,CloneArgs(copy_T1Z_e2_,init_inh_T1Z_e2_,del_inh_T1Z_e2_)));					//	e2'
	p_p_t1R->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1R_S3,0,0,init_syn_T1Z_e2_,del_syn_T1Z_e2_)));						//	S3

	p_p_t1S			=	new Produce(NonTerminalDef::p_t1);											//	t1
	p_p_t1S->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T1Z_A,init_inh_T1Z_A,del_inh_T1Z_A,act_T1S_A)));						//	A
	p_p_t1S->clone_args.push_back(make_pair(NonTerminalDef::p_e5_,CloneArgs(copy_T1Z_e5_,init_inh_T1Z_e5_,del_inh_T1Z_e5_)));					//	e5'
	p_p_t1S->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1S_S1,0,0,init_syn_T1Z_e5_,del_syn_T1Z_e5_)));						//	S1
	p_p_t1S->clone_args.push_back(make_pair(NonTerminalDef::p_e4_,CloneArgs(copy_T1Z_e4_,init_inh_T1Z_e4_,del_inh_T1Z_e4_)));					//	e4'
	p_p_t1S->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1S_S2,0,0,init_syn_T1Z_e4_,del_syn_T1Z_e4_)));						//	S2
	p_p_t1S->clone_args.push_back(make_pair(NonTerminalDef::p_e3_,CloneArgs(copy_T1Z_e3_,init_inh_T1Z_e3_,del_inh_T1Z_e3_)));					//	e3'
	p_p_t1S->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1S_S3,0,0,init_syn_T1Z_e3_,del_syn_T1Z_e3_)));						//	S3
	p_p_t1S->clone_args.push_back(make_pair(NonTerminalDef::p_e2_,CloneArgs(copy_T1Z_e2_,init_inh_T1Z_e2_,del_inh_T1Z_e2_)));					//	e2'
	p_p_t1S->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1S_S4,0,0,init_syn_T1Z_e2_,del_syn_T1Z_e2_)));						//	S4

	p_p_t1T			=	new Produce(NonTerminalDef::p_t1);											//	t1
	p_p_t1T->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T1Z_A,init_inh_T1Z_A,del_inh_T1Z_A,act_T1T_A)));						//	A
	p_p_t1T->clone_args.push_back(make_pair(NonTerminalDef::p_e6_,CloneArgs(copy_T1Z_e6_,init_inh_T1Z_e6_,del_inh_T1Z_e6_)));					//	e6'
	p_p_t1T->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1T_S1,0,0,init_syn_T1Z_e6_,del_syn_T1Z_e6_)));						//	S1
	p_p_t1T->clone_args.push_back(make_pair(NonTerminalDef::p_e5_,CloneArgs(copy_T1Z_e5_,init_inh_T1Z_e5_,del_inh_T1Z_e5_)));					//	e5'
	p_p_t1T->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1T_S2,0,0,init_syn_T1Z_e5_,del_syn_T1Z_e5_)));						//	S2
	p_p_t1T->clone_args.push_back(make_pair(NonTerminalDef::p_e4_,CloneArgs(copy_T1Z_e4_,init_inh_T1Z_e4_,del_inh_T1Z_e4_)));					//	e4'
	p_p_t1T->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1T_S3,0,0,init_syn_T1Z_e4_,del_syn_T1Z_e4_)));						//	S3
	p_p_t1T->clone_args.push_back(make_pair(NonTerminalDef::p_e3_,CloneArgs(copy_T1Z_e3_,init_inh_T1Z_e3_,del_inh_T1Z_e3_)));					//	e3'
	p_p_t1T->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1T_S4,0,0,init_syn_T1Z_e3_,del_syn_T1Z_e3_)));						//	S4
	p_p_t1T->clone_args.push_back(make_pair(NonTerminalDef::p_e2_,CloneArgs(copy_T1Z_e2_,init_inh_T1Z_e2_,del_inh_T1Z_e2_)));					//	e2'
	p_p_t1T->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1T_S5,0,0,init_syn_T1Z_e2_,del_syn_T1Z_e2_)));						//	S5

	p_p_t1U			=	new Produce(NonTerminalDef::p_t1);											//	t1
	p_p_t1U->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T1Z_A,init_inh_T1Z_A,del_inh_T1Z_A,act_T1U_A)));						//	A
	p_p_t1U->clone_args.push_back(make_pair(NonTerminalDef::p_e7_,CloneArgs(copy_T1Z_e7_,init_inh_T1Z_e7_,del_inh_T1Z_e7_)));					//	e7'
	p_p_t1U->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1U_S1,0,0,init_syn_T1Z_e7_,del_syn_T1Z_e7_)));						//	S1
	p_p_t1U->clone_args.push_back(make_pair(NonTerminalDef::p_e6_,CloneArgs(copy_T1Z_e6_,init_inh_T1Z_e6_,del_inh_T1Z_e6_)));					//	e6'
	p_p_t1U->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1U_S2,0,0,init_syn_T1Z_e6_,del_syn_T1Z_e6_)));						//	S2
	p_p_t1U->clone_args.push_back(make_pair(NonTerminalDef::p_e5_,CloneArgs(copy_T1Z_e5_,init_inh_T1Z_e5_,del_inh_T1Z_e5_)));					//	e5'
	p_p_t1U->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1U_S3,0,0,init_syn_T1Z_e5_,del_syn_T1Z_e5_)));						//	S3
	p_p_t1U->clone_args.push_back(make_pair(NonTerminalDef::p_e4_,CloneArgs(copy_T1Z_e4_,init_inh_T1Z_e4_,del_inh_T1Z_e4_)));					//	e4'
	p_p_t1U->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1U_S4,0,0,init_syn_T1Z_e4_,del_syn_T1Z_e4_)));						//	S4
	p_p_t1U->clone_args.push_back(make_pair(NonTerminalDef::p_e3_,CloneArgs(copy_T1Z_e3_,init_inh_T1Z_e3_,del_inh_T1Z_e3_)));					//	e3'
	p_p_t1U->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1U_S5,0,0,init_syn_T1Z_e3_,del_syn_T1Z_e3_)));						//	S5
	p_p_t1U->clone_args.push_back(make_pair(NonTerminalDef::p_e2_,CloneArgs(copy_T1Z_e2_,init_inh_T1Z_e2_,del_inh_T1Z_e2_)));					//	e2'
	p_p_t1U->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1U_S6,0,0,init_syn_T1Z_e2_,del_syn_T1Z_e2_)));						//	S6

	p_p_t1V			=	new Produce(NonTerminalDef::p_t1);											//	t1
	p_p_t1V->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T1Z_A,init_inh_T1Z_A,del_inh_T1Z_A,act_T1V_A)));						//	A
	p_p_t1V->clone_args.push_back(make_pair(NonTerminalDef::p_e8_,CloneArgs(copy_T1Z_e8_,init_inh_T1Z_e8_,del_inh_T1Z_e8_)));					//	e8'
	p_p_t1V->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1V_S1,0,0,init_syn_T1Z_e8_,del_syn_T1Z_e8_)));						//	S1
	p_p_t1V->clone_args.push_back(make_pair(NonTerminalDef::p_e7_,CloneArgs(copy_T1Z_e7_,init_inh_T1Z_e7_,del_inh_T1Z_e7_)));					//	e7'
	p_p_t1V->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1V_S2,0,0,init_syn_T1Z_e7_,del_syn_T1Z_e7_)));						//	S2
	p_p_t1V->clone_args.push_back(make_pair(NonTerminalDef::p_e6_,CloneArgs(copy_T1Z_e6_,init_inh_T1Z_e6_,del_inh_T1Z_e6_)));					//	e6'
	p_p_t1V->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1V_S3,0,0,init_syn_T1Z_e6_,del_syn_T1Z_e6_)));						//	S3
	p_p_t1V->clone_args.push_back(make_pair(NonTerminalDef::p_e5_,CloneArgs(copy_T1Z_e5_,init_inh_T1Z_e5_,del_inh_T1Z_e5_)));					//	e5'
	p_p_t1V->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1V_S4,0,0,init_syn_T1Z_e5_,del_syn_T1Z_e5_)));						//	S4
	p_p_t1V->clone_args.push_back(make_pair(NonTerminalDef::p_e4_,CloneArgs(copy_T1Z_e4_,init_inh_T1Z_e4_,del_inh_T1Z_e4_)));					//	e4'
	p_p_t1V->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1V_S5,0,0,init_syn_T1Z_e4_,del_syn_T1Z_e4_)));						//	S5
	p_p_t1V->clone_args.push_back(make_pair(NonTerminalDef::p_e3_,CloneArgs(copy_T1Z_e3_,init_inh_T1Z_e3_,del_inh_T1Z_e3_)));					//	e3'
	p_p_t1V->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1V_S6,0,0,init_syn_T1Z_e3_,del_syn_T1Z_e3_)));						//	S6
	p_p_t1V->clone_args.push_back(make_pair(NonTerminalDef::p_e2_,CloneArgs(copy_T1Z_e2_,init_inh_T1Z_e2_,del_inh_T1Z_e2_)));					//	e2'
	p_p_t1V->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1V_S7,0,0,init_syn_T1Z_e2_,del_syn_T1Z_e2_)));						//	S7

	p_p_t1W			=	new Produce(NonTerminalDef::p_t1);											//	t1
	p_p_t1W->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T1Z_A,init_inh_T1Z_A,del_inh_T1Z_A,act_T1W_A)));						//	A
	p_p_t1W->clone_args.push_back(make_pair(NonTerminalDef::p_e9_,CloneArgs(copy_T1Z_e9_,init_inh_T1Z_e9_,del_inh_T1Z_e9_)));					//	e9'
	p_p_t1W->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1W_S1,0,0,init_syn_T1Z_e9_,del_syn_T1Z_e9_)));						//	S1
	p_p_t1W->clone_args.push_back(make_pair(NonTerminalDef::p_e8_,CloneArgs(copy_T1Z_e8_,init_inh_T1Z_e8_,del_inh_T1Z_e8_)));					//	e8'
	p_p_t1W->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1W_S2,0,0,init_syn_T1Z_e8_,del_syn_T1Z_e8_)));						//	S2
	p_p_t1W->clone_args.push_back(make_pair(NonTerminalDef::p_e7_,CloneArgs(copy_T1Z_e7_,init_inh_T1Z_e7_,del_inh_T1Z_e7_)));					//	e7'
	p_p_t1W->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1W_S3,0,0,init_syn_T1Z_e7_,del_syn_T1Z_e7_)));						//	S3
	p_p_t1W->clone_args.push_back(make_pair(NonTerminalDef::p_e6_,CloneArgs(copy_T1Z_e6_,init_inh_T1Z_e6_,del_inh_T1Z_e6_)));					//	e6'
	p_p_t1W->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1W_S4,0,0,init_syn_T1Z_e6_,del_syn_T1Z_e6_)));						//	S4
	p_p_t1W->clone_args.push_back(make_pair(NonTerminalDef::p_e5_,CloneArgs(copy_T1Z_e5_,init_inh_T1Z_e5_,del_inh_T1Z_e5_)));					//	e5'
	p_p_t1W->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1W_S5,0,0,init_syn_T1Z_e5_,del_syn_T1Z_e5_)));						//	S5
	p_p_t1W->clone_args.push_back(make_pair(NonTerminalDef::p_e4_,CloneArgs(copy_T1Z_e4_,init_inh_T1Z_e4_,del_inh_T1Z_e4_)));					//	e4'
	p_p_t1W->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1W_S6,0,0,init_syn_T1Z_e4_,del_syn_T1Z_e4_)));						//	S6
	p_p_t1W->clone_args.push_back(make_pair(NonTerminalDef::p_e3_,CloneArgs(copy_T1Z_e3_,init_inh_T1Z_e3_,del_inh_T1Z_e3_)));					//	e3'
	p_p_t1W->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1W_S7,0,0,init_syn_T1Z_e3_,del_syn_T1Z_e3_)));						//	S7
	p_p_t1W->clone_args.push_back(make_pair(NonTerminalDef::p_e2_,CloneArgs(copy_T1Z_e2_,init_inh_T1Z_e2_,del_inh_T1Z_e2_)));					//	e2'
	p_p_t1W->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1W_S8,0,0,init_syn_T1Z_e2_,del_syn_T1Z_e2_)));						//	S8

	p_p_t1X			=	new Produce(NonTerminalDef::p_t1);											//	t1
	p_p_t1X->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T1Z_A,init_inh_T1Z_A,del_inh_T1Z_A,act_T1X_A)));						//	A
	p_p_t1X->clone_args.push_back(make_pair(NonTerminalDef::p_e10_,CloneArgs(copy_T1Z_e10_,init_inh_T1Z_e10_,del_inh_T1Z_e10_)));				//	e10'
	p_p_t1X->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1X_S1,0,0,init_syn_T1Z_e10_,del_syn_T1Z_e10_)));						//	S1
	p_p_t1X->clone_args.push_back(make_pair(NonTerminalDef::p_e9_,CloneArgs(copy_T1Z_e9_,init_inh_T1Z_e9_,del_inh_T1Z_e9_)));					//	e9'
	p_p_t1X->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1X_S2,0,0,init_syn_T1Z_e9_,del_syn_T1Z_e9_)));						//	S2
	p_p_t1X->clone_args.push_back(make_pair(NonTerminalDef::p_e8_,CloneArgs(copy_T1Z_e8_,init_inh_T1Z_e8_,del_inh_T1Z_e8_)));					//	e8'
	p_p_t1X->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1X_S3,0,0,init_syn_T1Z_e8_,del_syn_T1Z_e8_)));						//	S3
	p_p_t1X->clone_args.push_back(make_pair(NonTerminalDef::p_e7_,CloneArgs(copy_T1Z_e7_,init_inh_T1Z_e7_,del_inh_T1Z_e7_)));					//	e7'
	p_p_t1X->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1X_S4,0,0,init_syn_T1Z_e7_,del_syn_T1Z_e7_)));						//	S4
	p_p_t1X->clone_args.push_back(make_pair(NonTerminalDef::p_e6_,CloneArgs(copy_T1Z_e6_,init_inh_T1Z_e6_,del_inh_T1Z_e6_)));					//	e6'
	p_p_t1X->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1X_S5,0,0,init_syn_T1Z_e6_,del_syn_T1Z_e6_)));						//	S5
	p_p_t1X->clone_args.push_back(make_pair(NonTerminalDef::p_e5_,CloneArgs(copy_T1Z_e5_,init_inh_T1Z_e5_,del_inh_T1Z_e5_)));					//	e5'
	p_p_t1X->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1X_S6,0,0,init_syn_T1Z_e5_,del_syn_T1Z_e5_)));						//	S6
	p_p_t1X->clone_args.push_back(make_pair(NonTerminalDef::p_e4_,CloneArgs(copy_T1Z_e4_,init_inh_T1Z_e4_,del_inh_T1Z_e4_)));					//	e4'
	p_p_t1X->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1X_S7,0,0,init_syn_T1Z_e4_,del_syn_T1Z_e4_)));						//	S7
	p_p_t1X->clone_args.push_back(make_pair(NonTerminalDef::p_e3_,CloneArgs(copy_T1Z_e3_,init_inh_T1Z_e3_,del_inh_T1Z_e3_)));					//	e3'
	p_p_t1X->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1X_S8,0,0,init_syn_T1Z_e3_,del_syn_T1Z_e3_)));						//	S8
	p_p_t1X->clone_args.push_back(make_pair(NonTerminalDef::p_e2_,CloneArgs(copy_T1Z_e2_,init_inh_T1Z_e2_,del_inh_T1Z_e2_)));					//	e2'
	p_p_t1X->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1X_S9,0,0,init_syn_T1Z_e2_,del_syn_T1Z_e2_)));						//	S9

	p_p_t1Y			=	new Produce(NonTerminalDef::p_t1);											//	t1
	p_p_t1Y->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T1Z_A,init_inh_T1Z_A,del_inh_T1Z_A,act_T1Y_A)));						//	A
	p_p_t1Y->clone_args.push_back(make_pair(NonTerminalDef::p_e11_,CloneArgs(copy_T1Z_e11_,init_inh_T1Z_e11_,del_inh_T1Z_e11_)));				//	e11'
	p_p_t1Y->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1Y_S1,0,0,init_syn_T1Z_e11_,del_syn_T1Z_e11_)));						//	S1
	p_p_t1Y->clone_args.push_back(make_pair(NonTerminalDef::p_e10_,CloneArgs(copy_T1Z_e10_,init_inh_T1Z_e10_,del_inh_T1Z_e10_)));				//	e10'
	p_p_t1Y->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1Y_S2,0,0,init_syn_T1Z_e10_,del_syn_T1Z_e10_)));						//	S2
	p_p_t1Y->clone_args.push_back(make_pair(NonTerminalDef::p_e9_,CloneArgs(copy_T1Z_e9_,init_inh_T1Z_e9_,del_inh_T1Z_e9_)));					//	e9'
	p_p_t1Y->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1Y_S3,0,0,init_syn_T1Z_e9_,del_syn_T1Z_e9_)));						//	S3
	p_p_t1Y->clone_args.push_back(make_pair(NonTerminalDef::p_e8_,CloneArgs(copy_T1Z_e8_,init_inh_T1Z_e8_,del_inh_T1Z_e8_)));					//	e8'
	p_p_t1Y->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1Y_S4,0,0,init_syn_T1Z_e8_,del_syn_T1Z_e8_)));						//	S4
	p_p_t1Y->clone_args.push_back(make_pair(NonTerminalDef::p_e7_,CloneArgs(copy_T1Z_e7_,init_inh_T1Z_e7_,del_inh_T1Z_e7_)));					//	e7'
	p_p_t1Y->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1Y_S5,0,0,init_syn_T1Z_e7_,del_syn_T1Z_e7_)));						//	S5
	p_p_t1Y->clone_args.push_back(make_pair(NonTerminalDef::p_e6_,CloneArgs(copy_T1Z_e6_,init_inh_T1Z_e6_,del_inh_T1Z_e6_)));					//	e6'
	p_p_t1Y->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1Y_S6,0,0,init_syn_T1Z_e6_,del_syn_T1Z_e6_)));						//	S6
	p_p_t1Y->clone_args.push_back(make_pair(NonTerminalDef::p_e5_,CloneArgs(copy_T1Z_e5_,init_inh_T1Z_e5_,del_inh_T1Z_e5_)));					//	e5'
	p_p_t1Y->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1Y_S7,0,0,init_syn_T1Z_e5_,del_syn_T1Z_e5_)));						//	S7
	p_p_t1Y->clone_args.push_back(make_pair(NonTerminalDef::p_e4_,CloneArgs(copy_T1Z_e4_,init_inh_T1Z_e4_,del_inh_T1Z_e4_)));					//	e4'
	p_p_t1Y->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1Y_S8,0,0,init_syn_T1Z_e4_,del_syn_T1Z_e4_)));						//	S8
	p_p_t1Y->clone_args.push_back(make_pair(NonTerminalDef::p_e3_,CloneArgs(copy_T1Z_e3_,init_inh_T1Z_e3_,del_inh_T1Z_e3_)));					//	e3'
	p_p_t1Y->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1Y_S9,0,0,init_syn_T1Z_e3_,del_syn_T1Z_e3_)));						//	S9
	p_p_t1Y->clone_args.push_back(make_pair(NonTerminalDef::p_e2_,CloneArgs(copy_T1Z_e2_,init_inh_T1Z_e2_,del_inh_T1Z_e2_)));					//	e2'
	p_p_t1Y->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1Y_S10,0,0,init_syn_T1Z_e2_,del_syn_T1Z_e2_)));						//	S10

	p_p_t1Z			=	new Produce(NonTerminalDef::p_t1);											//	t1
	p_p_t1Z->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T1Z_A,init_inh_T1Z_A,del_inh_T1Z_A,act_T1Z_A)));						//	A
	p_p_t1Z->clone_args.push_back(make_pair(NonTerminalDef::p_e12_,CloneArgs(copy_T1Z_e12_,init_inh_T1Z_e12_,del_inh_T1Z_e12_)));				//	e12'
	p_p_t1Z->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1Z_S1,0,0,init_syn_T1Z_e12_,del_syn_T1Z_e12_)));						//	S1
	p_p_t1Z->clone_args.push_back(make_pair(NonTerminalDef::p_e11_,CloneArgs(copy_T1Z_e11_,init_inh_T1Z_e11_,del_inh_T1Z_e11_)));				//	e11'
	p_p_t1Z->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1Z_S2,0,0,init_syn_T1Z_e11_,del_syn_T1Z_e11_)));						//	S2
	p_p_t1Z->clone_args.push_back(make_pair(NonTerminalDef::p_e10_,CloneArgs(copy_T1Z_e10_,init_inh_T1Z_e10_,del_inh_T1Z_e10_)));				//	e10'
	p_p_t1Z->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1Z_S3,0,0,init_syn_T1Z_e10_,del_syn_T1Z_e10_)));						//	S3
	p_p_t1Z->clone_args.push_back(make_pair(NonTerminalDef::p_e9_,CloneArgs(copy_T1Z_e9_,init_inh_T1Z_e9_,del_inh_T1Z_e9_)));					//	e9'
	p_p_t1Z->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1Z_S4,0,0,init_syn_T1Z_e9_,del_syn_T1Z_e9_)));						//	S4
	p_p_t1Z->clone_args.push_back(make_pair(NonTerminalDef::p_e8_,CloneArgs(copy_T1Z_e8_,init_inh_T1Z_e8_,del_inh_T1Z_e8_)));					//	e8'
	p_p_t1Z->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1Z_S5,0,0,init_syn_T1Z_e8_,del_syn_T1Z_e8_)));						//	S5
	p_p_t1Z->clone_args.push_back(make_pair(NonTerminalDef::p_e7_,CloneArgs(copy_T1Z_e7_,init_inh_T1Z_e7_,del_inh_T1Z_e7_)));					//	e7'
	p_p_t1Z->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1Z_S6,0,0,init_syn_T1Z_e7_,del_syn_T1Z_e7_)));						//	S6
	p_p_t1Z->clone_args.push_back(make_pair(NonTerminalDef::p_e6_,CloneArgs(copy_T1Z_e6_,init_inh_T1Z_e6_,del_inh_T1Z_e6_)));					//	e6'
	p_p_t1Z->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1Z_S7,0,0,init_syn_T1Z_e6_,del_syn_T1Z_e6_)));						//	S7
	p_p_t1Z->clone_args.push_back(make_pair(NonTerminalDef::p_e5_,CloneArgs(copy_T1Z_e5_,init_inh_T1Z_e5_,del_inh_T1Z_e5_)));					//	e5'
	p_p_t1Z->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1Z_S8,0,0,init_syn_T1Z_e5_,del_syn_T1Z_e5_)));						//	S8
	p_p_t1Z->clone_args.push_back(make_pair(NonTerminalDef::p_e4_,CloneArgs(copy_T1Z_e4_,init_inh_T1Z_e4_,del_inh_T1Z_e4_)));					//	e4'
	p_p_t1Z->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1Z_S9,0,0,init_syn_T1Z_e4_,del_syn_T1Z_e4_)));						//	S9
	p_p_t1Z->clone_args.push_back(make_pair(NonTerminalDef::p_e3_,CloneArgs(copy_T1Z_e3_,init_inh_T1Z_e3_,del_inh_T1Z_e3_)));					//	e3'
	p_p_t1Z->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1Z_S10,0,0,init_syn_T1Z_e3_,del_syn_T1Z_e3_)));						//	S10
	p_p_t1Z->clone_args.push_back(make_pair(NonTerminalDef::p_e2_,CloneArgs(copy_T1Z_e2_,init_inh_T1Z_e2_,del_inh_T1Z_e2_)));					//	e2'
	p_p_t1Z->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T1Z_S11,0,0,init_syn_T1Z_e2_,del_syn_T1Z_e2_)));						//	S11

	p_p_t1A1			=	new Produce(NonTerminalDef::p_t1);										// ¦Å
	p_p_t1A1->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T1_A,init_inh_T1_A,del_inh_T1_A,act_T1A1_A)));						//	A

	//...

	p_p_t2A			=	new Produce(NonTerminalDef::p_t2);											//	t2
	p_p_t2A->clone_args.push_back(make_pair(Terminal::p_plus_plus,CloneArgs()));					//	++
	p_p_t2A->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T2_A,init_inh_T2_A,del_inh_T2_A,act_T2A_A)));						//	A
	p_p_t2A->clone_args.push_back(make_pair(NonTerminalDef::p_t5,CloneArgs(copy_T2_T5,init_inh_T5)));											//  T5
	p_p_t2A->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5_S,0,0,init_syn_T5_S,del_syn_T5_S)));						//  S

	p_p_t2B			=	new Produce(NonTerminalDef::p_t2);											//	t2
	p_p_t2B->clone_args.push_back(make_pair(Terminal::p_minus_minus,CloneArgs()));					//	--
	p_p_t2B->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T2_A,init_inh_T2_A,del_inh_T2_A,act_T2B_A)));						//	A
	p_p_t2B->clone_args.push_back(make_pair(NonTerminalDef::p_t5,CloneArgs(copy_T2_T5,init_inh_T5)));											//  T5
	p_p_t2B->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5_S,0,0,init_syn_T5_S,del_syn_T5_S)));						//  S

	p_p_t2C			=	new Produce(NonTerminalDef::p_t2);											//	t2
	p_p_t2C->clone_args.push_back(make_pair(Terminal::p_assign,CloneArgs()));						//	=
	p_p_t2C->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_T2C_A,init_temp_T2C_A)));						//	A
	p_p_t2C->clone_args.push_back(make_pair(NonTerminalSyn::p_e1,CloneArgs(copy_T2C_e1,init_inh_T2C_e1)));						//	e1
	p_p_t2C->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_T2C_S,init_inh_T2C_S,del_inh_T2C_S,act_T2C_S,init_temp_T2C_S,0,init_syn_T2C_S,del_syn_T2C_S)));						//	S

	p_p_t2D			=	new Produce(NonTerminalDef::p_t2);											//	t2
	p_p_t2D->clone_args.push_back(make_pair(Terminal::p_mul_ass,CloneArgs()));						//	*=
	p_p_t2D->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_T2C_A,init_temp_T2C_A)));						//	A
	p_p_t2D->clone_args.push_back(make_pair(NonTerminalSyn::p_e1,CloneArgs(copy_T2C_e1,init_inh_T2C_e1)));						//	e1
	p_p_t2D->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_T2C_S,init_inh_T2C_S,del_inh_T2C_S,act_T2D_S,init_temp_T2C_S,0,init_syn_T2C_S,del_syn_T2C_S)));						//	S

	p_p_t2E			=	new Produce(NonTerminalDef::p_t2);											//	t2
	p_p_t2E->clone_args.push_back(make_pair(Terminal::p_div_ass,CloneArgs()));						//	/=
	p_p_t2E->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_T2C_A,init_temp_T2C_A)));						//	A
	p_p_t2E->clone_args.push_back(make_pair(NonTerminalSyn::p_e1,CloneArgs(copy_T2C_e1,init_inh_T2C_e1)));						//	e1
	p_p_t2E->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_T2C_S,init_inh_T2C_S,del_inh_T2C_S,act_T2E_S,init_temp_T2C_S,0,init_syn_T2C_S,del_syn_T2C_S)));						//	S

	p_p_t2F			=	new Produce(NonTerminalDef::p_t2);											//	t2
	p_p_t2F->clone_args.push_back(make_pair(Terminal::p_mod_ass,CloneArgs()));						//	%=
	p_p_t2F->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_T2C_A,init_temp_T2C_A)));						//	A
	p_p_t2F->clone_args.push_back(make_pair(NonTerminalSyn::p_e1,CloneArgs(copy_T2C_e1,init_inh_T2C_e1)));						//	e1
	p_p_t2F->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_T2C_S,init_inh_T2C_S,del_inh_T2C_S,act_T2F_S,init_temp_T2C_S,0,init_syn_T2C_S,del_syn_T2C_S)));						//	S

	p_p_t2G			=	new Produce(NonTerminalDef::p_t2);											//	t2
	p_p_t2G->clone_args.push_back(make_pair(Terminal::p_add_ass,CloneArgs()));						//	+=
	p_p_t2G->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_T2C_A,init_temp_T2C_A)));						//	A
	p_p_t2G->clone_args.push_back(make_pair(NonTerminalSyn::p_e1,CloneArgs(copy_T2C_e1,init_inh_T2C_e1)));						//	e1
	p_p_t2G->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_T2C_S,init_inh_T2C_S,del_inh_T2C_S,act_T2G_S,init_temp_T2C_S,0,init_syn_T2C_S,del_syn_T2C_S)));						//	S

	p_p_t2H			=	new Produce(NonTerminalDef::p_t2);											//	t2
	p_p_t2H->clone_args.push_back(make_pair(Terminal::p_sub_ass,CloneArgs()));						//	-=
	p_p_t2H->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_T2C_A,init_temp_T2C_A)));						//	A
	p_p_t2H->clone_args.push_back(make_pair(NonTerminalSyn::p_e1,CloneArgs(copy_T2C_e1,init_inh_T2C_e1)));						//	e1
	p_p_t2H->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_T2C_S,init_inh_T2C_S,del_inh_T2C_S,act_T2H_S,init_temp_T2C_S,0,init_syn_T2C_S,del_syn_T2C_S)));						//	S

	p_p_t2I			=	new Produce(NonTerminalDef::p_t2);											//	t2
	p_p_t2I->clone_args.push_back(make_pair(Terminal::p_l_sht_ass,CloneArgs()));					//	<<=
	p_p_t2I->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_T2C_A,init_temp_T2C_A)));						//	A
	p_p_t2I->clone_args.push_back(make_pair(NonTerminalSyn::p_e1,CloneArgs(copy_T2C_e1,init_inh_T2C_e1)));						//	e1
	p_p_t2I->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_T2C_S,init_inh_T2C_S,del_inh_T2C_S,act_T2I_S,init_temp_T2C_S,0,init_syn_T2C_S,del_syn_T2C_S)));						//	S

	p_p_t2J			=	new Produce(NonTerminalDef::p_t2);											//	t2
	p_p_t2J->clone_args.push_back(make_pair(Terminal::p_r_sht_ass,CloneArgs()));					//	>>=
	p_p_t2J->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_T2C_A,init_temp_T2C_A)));						//	A
	p_p_t2J->clone_args.push_back(make_pair(NonTerminalSyn::p_e1,CloneArgs(copy_T2C_e1,init_inh_T2C_e1)));						//	e1
	p_p_t2J->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_T2C_S,init_inh_T2C_S,del_inh_T2C_S,act_T2J_S,init_temp_T2C_S,0,init_syn_T2C_S,del_syn_T2C_S)));						//	S

	p_p_t2K			=	new Produce(NonTerminalDef::p_t2);											//	t2
	p_p_t2K->clone_args.push_back(make_pair(Terminal::p_b_and_ass,CloneArgs()));					//	&=
	p_p_t2K->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_T2C_A,init_temp_T2C_A)));						//	A
	p_p_t2K->clone_args.push_back(make_pair(NonTerminalSyn::p_e1,CloneArgs(copy_T2C_e1,init_inh_T2C_e1)));						//	e1
	p_p_t2K->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_T2C_S,init_inh_T2C_S,del_inh_T2C_S,act_T2K_S,init_temp_T2C_S,0,init_syn_T2C_S,del_syn_T2C_S)));						//	S

	p_p_t2L			=	new Produce(NonTerminalDef::p_t2);											//	t2
	p_p_t2L->clone_args.push_back(make_pair(Terminal::p_b_or_ass,CloneArgs()));						//	|=
	p_p_t2L->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_T2C_A,init_temp_T2C_A)));						//	A
	p_p_t2L->clone_args.push_back(make_pair(NonTerminalSyn::p_e1,CloneArgs(copy_T2C_e1,init_inh_T2C_e1)));						//	e1
	p_p_t2L->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_T2C_S,init_inh_T2C_S,del_inh_T2C_S,act_T2L_S,init_temp_T2C_S,0,init_syn_T2C_S,del_syn_T2C_S)));						//	S

	p_p_t2M			=	new Produce(NonTerminalDef::p_t2);											//	t2
	p_p_t2M->clone_args.push_back(make_pair(Terminal::p_b_xor_ass,CloneArgs()));					//	^=
	p_p_t2M->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_T2C_A,init_temp_T2C_A)));						//	A
	p_p_t2M->clone_args.push_back(make_pair(NonTerminalSyn::p_e1,CloneArgs(copy_T2C_e1,init_inh_T2C_e1)));						//	e1
	p_p_t2M->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_T2C_S,init_inh_T2C_S,del_inh_T2C_S,act_T2M_S,init_temp_T2C_S,0,init_syn_T2C_S,del_syn_T2C_S)));						//	S

	p_p_t2N			=	new Produce(NonTerminalDef::p_t2);											//	t2
	p_p_t2N->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T2X_A,init_inh_T2X_A,del_inh_T2X_A,act_T2N_A)));						//	A
	p_p_t2N->clone_args.push_back(make_pair(NonTerminalDef::p_e2_,CloneArgs(copy_T2X_e2_,init_inh_T2X_e2_,del_inh_T2X_e2_,act_T2N_A)));					//	e2'
	p_p_t2N->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2N_S,0,0,init_syn_T2X_e2_,del_syn_T2X_e2_)));						//	S

	p_p_t2O			=	new Produce(NonTerminalDef::p_t2);											//	t2
	p_p_t2O->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T2X_A,init_inh_T2X_A,del_inh_T2X_A,act_T2O_A)));						//	A
	p_p_t2O->clone_args.push_back(make_pair(NonTerminalDef::p_e3_,CloneArgs(copy_T2X_e3_,init_inh_T2X_e3_,del_inh_T2X_e3_)));					//	e3'
	p_p_t2O->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2O_S1,0,0,init_syn_T2X_e3_,del_syn_T2X_e3_)));						//	S1
	p_p_t2O->clone_args.push_back(make_pair(NonTerminalDef::p_e2_,CloneArgs(copy_T2X_e2_,init_inh_T2X_e2_,del_inh_T2X_e2_)));					//	e2'
	p_p_t2O->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2O_S2,0,0,init_syn_T2X_e2_,del_syn_T2X_e2_)));						//	S2

	p_p_t2P			=	new Produce(NonTerminalDef::p_t2);											//	t2
	p_p_t2P->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T2X_A,init_inh_T2X_A,del_inh_T2X_A,act_T2P_A)));						//	A
	p_p_t2P->clone_args.push_back(make_pair(NonTerminalDef::p_e4_,CloneArgs(copy_T2X_e4_,init_inh_T2X_e4_,del_inh_T2X_e4_)));					//	e4'
	p_p_t2P->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2P_S1,0,0,init_syn_T2X_e4_,del_syn_T2X_e4_)));						//	S1
	p_p_t2P->clone_args.push_back(make_pair(NonTerminalDef::p_e3_,CloneArgs(copy_T2X_e3_,init_inh_T2X_e3_,del_inh_T2X_e3_)));					//	e3'
	p_p_t2P->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2P_S2,0,0,init_syn_T2X_e3_,del_syn_T2X_e3_)));						//	S2
	p_p_t2P->clone_args.push_back(make_pair(NonTerminalDef::p_e2_,CloneArgs(copy_T2X_e2_,init_inh_T2X_e2_,del_inh_T2X_e2_)));					//	e2'
	p_p_t2P->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2P_S3,0,0,init_syn_T2X_e2_,del_syn_T2X_e2_)));						//	S3

	p_p_t2Q			=	new Produce(NonTerminalDef::p_t2);											//	t2
	p_p_t2Q->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T2X_A,init_inh_T2X_A,del_inh_T2X_A,act_T2Q_A)));						//	A
	p_p_t2Q->clone_args.push_back(make_pair(NonTerminalDef::p_e5_,CloneArgs(copy_T2X_e5_,init_inh_T2X_e5_,del_inh_T2X_e5_)));					//	e5'
	p_p_t2Q->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2Q_S1,0,0,init_syn_T2X_e5_,del_syn_T2X_e5_)));						//	S1
	p_p_t2Q->clone_args.push_back(make_pair(NonTerminalDef::p_e4_,CloneArgs(copy_T2X_e4_,init_inh_T2X_e4_,del_inh_T2X_e4_)));					//	e4'
	p_p_t2Q->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2Q_S2,0,0,init_syn_T2X_e4_,del_syn_T2X_e4_)));						//	S2
	p_p_t2Q->clone_args.push_back(make_pair(NonTerminalDef::p_e3_,CloneArgs(copy_T2X_e3_,init_inh_T2X_e3_,del_inh_T2X_e3_)));					//	e3'
	p_p_t2Q->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2Q_S3,0,0,init_syn_T2X_e3_,del_syn_T2X_e3_)));						//	S3
	p_p_t2Q->clone_args.push_back(make_pair(NonTerminalDef::p_e2_,CloneArgs(copy_T2X_e2_,init_inh_T2X_e2_,del_inh_T2X_e2_)));					//	e2'
	p_p_t2Q->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2Q_S4,0,0,init_syn_T2X_e2_,del_syn_T2X_e2_)));						//	S4

	p_p_t2R			=	new Produce(NonTerminalDef::p_t2);											//	t2
	p_p_t2R->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T2X_A,init_inh_T2X_A,del_inh_T2X_A,act_T2R_A)));						//	A
	p_p_t2R->clone_args.push_back(make_pair(NonTerminalDef::p_e6_,CloneArgs(copy_T2X_e6_,init_inh_T2X_e6_,del_inh_T2X_e6_)));					//	e6'
	p_p_t2R->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2R_S1,0,0,init_syn_T2X_e6_,del_syn_T2X_e6_)));						//	S1
	p_p_t2R->clone_args.push_back(make_pair(NonTerminalDef::p_e5_,CloneArgs(copy_T2X_e5_,init_inh_T2X_e5_,del_inh_T2X_e5_)));					//	e5'
	p_p_t2R->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2R_S2,0,0,init_syn_T2X_e5_,del_syn_T2X_e5_)));						//	S2
	p_p_t2R->clone_args.push_back(make_pair(NonTerminalDef::p_e4_,CloneArgs(copy_T2X_e4_,init_inh_T2X_e4_,del_inh_T2X_e4_)));					//	e4'
	p_p_t2R->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2R_S3,0,0,init_syn_T2X_e4_,del_syn_T2X_e4_)));						//	S3
	p_p_t2R->clone_args.push_back(make_pair(NonTerminalDef::p_e3_,CloneArgs(copy_T2X_e3_,init_inh_T2X_e3_,del_inh_T2X_e3_)));					//	e3'
	p_p_t2R->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2R_S4,0,0,init_syn_T2X_e3_,del_syn_T2X_e3_)));						//	S4
	p_p_t2R->clone_args.push_back(make_pair(NonTerminalDef::p_e2_,CloneArgs(copy_T2X_e2_,init_inh_T2X_e2_,del_inh_T2X_e2_)));					//	e2'
	p_p_t2R->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2R_S5,0,0,init_syn_T2X_e2_,del_syn_T2X_e2_)));						//	S5

	p_p_t2S			=	new Produce(NonTerminalDef::p_t2);											//	t2
	p_p_t2S->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T2X_A,init_inh_T2X_A,del_inh_T2X_A,act_T2S_A)));						//	A
	p_p_t2S->clone_args.push_back(make_pair(NonTerminalDef::p_e7_,CloneArgs(copy_T2X_e7_,init_inh_T2X_e7_,del_inh_T2X_e7_)));					//	e7'
	p_p_t2S->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2S_S1,0,0,init_syn_T2X_e7_,del_syn_T2X_e7_)));						//	S1
	p_p_t2S->clone_args.push_back(make_pair(NonTerminalDef::p_e6_,CloneArgs(copy_T2X_e6_,init_inh_T2X_e6_,del_inh_T2X_e6_)));					//	e6'
	p_p_t2S->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2S_S2,0,0,init_syn_T2X_e6_,del_syn_T2X_e6_)));						//	S2
	p_p_t2S->clone_args.push_back(make_pair(NonTerminalDef::p_e5_,CloneArgs(copy_T2X_e5_,init_inh_T2X_e5_,del_inh_T2X_e5_)));					//	e5'
	p_p_t2S->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2S_S3,0,0,init_syn_T2X_e5_,del_syn_T2X_e5_)));						//	S3
	p_p_t2S->clone_args.push_back(make_pair(NonTerminalDef::p_e4_,CloneArgs(copy_T2X_e4_,init_inh_T2X_e4_,del_inh_T2X_e4_)));					//	e4'
	p_p_t2S->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2S_S4,0,0,init_syn_T2X_e4_,del_syn_T2X_e4_)));						//	S4
	p_p_t2S->clone_args.push_back(make_pair(NonTerminalDef::p_e3_,CloneArgs(copy_T2X_e3_,init_inh_T2X_e3_,del_inh_T2X_e3_)));					//	e3'
	p_p_t2S->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2S_S5,0,0,init_syn_T2X_e3_,del_syn_T2X_e3_)));						//	S5
	p_p_t2S->clone_args.push_back(make_pair(NonTerminalDef::p_e2_,CloneArgs(copy_T2X_e2_,init_inh_T2X_e2_,del_inh_T2X_e2_)));					//	e2'
	p_p_t2S->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2S_S6,0,0,init_syn_T2X_e2_,del_syn_T2X_e2_)));						//	S6

	p_p_t2T			=	new Produce(NonTerminalDef::p_t2);											//	t2
	p_p_t2T->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T2X_A,init_inh_T2X_A,del_inh_T2X_A,act_T2T_A)));						//	A
	p_p_t2T->clone_args.push_back(make_pair(NonTerminalDef::p_e8_,CloneArgs(copy_T2X_e8_,init_inh_T2X_e8_,del_inh_T2X_e8_)));					//	e8'
	p_p_t2T->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2T_S1,0,0,init_syn_T2X_e8_,del_syn_T2X_e8_)));						//	S1
	p_p_t2T->clone_args.push_back(make_pair(NonTerminalDef::p_e7_,CloneArgs(copy_T2X_e7_,init_inh_T2X_e7_,del_inh_T2X_e7_)));					//	e7'
	p_p_t2T->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2T_S2,0,0,init_syn_T2X_e7_,del_syn_T2X_e7_)));						//	S2
	p_p_t2T->clone_args.push_back(make_pair(NonTerminalDef::p_e6_,CloneArgs(copy_T2X_e6_,init_inh_T2X_e6_,del_inh_T2X_e6_)));					//	e6'
	p_p_t2T->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2T_S3,0,0,init_syn_T2X_e6_,del_syn_T2X_e6_)));						//	S3
	p_p_t2T->clone_args.push_back(make_pair(NonTerminalDef::p_e5_,CloneArgs(copy_T2X_e5_,init_inh_T2X_e5_,del_inh_T2X_e5_)));					//	e5'
	p_p_t2T->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2T_S4,0,0,init_syn_T2X_e5_,del_syn_T2X_e5_)));						//	S4
	p_p_t2T->clone_args.push_back(make_pair(NonTerminalDef::p_e4_,CloneArgs(copy_T2X_e4_,init_inh_T2X_e4_,del_inh_T2X_e4_)));					//	e4'
	p_p_t2T->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2T_S5,0,0,init_syn_T2X_e4_,del_syn_T2X_e4_)));						//	S5
	p_p_t2T->clone_args.push_back(make_pair(NonTerminalDef::p_e3_,CloneArgs(copy_T2X_e3_,init_inh_T2X_e3_,del_inh_T2X_e3_)));					//	e3'
	p_p_t2T->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2T_S6,0,0,init_syn_T2X_e3_,del_syn_T2X_e3_)));						//	S6
	p_p_t2T->clone_args.push_back(make_pair(NonTerminalDef::p_e2_,CloneArgs(copy_T2X_e2_,init_inh_T2X_e2_,del_inh_T2X_e2_)));					//	e2'
	p_p_t2T->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2T_S7,0,0,init_syn_T2X_e2_,del_syn_T2X_e2_)));						//	S7

	p_p_t2U			=	new Produce(NonTerminalDef::p_t2);											//	t2
	p_p_t2U->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T2X_A,init_inh_T2X_A,del_inh_T2X_A,act_T2U_A)));						//	A
	p_p_t2U->clone_args.push_back(make_pair(NonTerminalDef::p_e9_,CloneArgs(copy_T2X_e9_,init_inh_T2X_e9_,del_inh_T2X_e9_)));					//	e9'
	p_p_t2U->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2U_S1,0,0,init_syn_T2X_e9_,del_syn_T2X_e9_)));						//	S1
	p_p_t2U->clone_args.push_back(make_pair(NonTerminalDef::p_e8_,CloneArgs(copy_T2X_e8_,init_inh_T2X_e8_,del_inh_T2X_e8_)));					//	e8'
	p_p_t2U->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2U_S2,0,0,init_syn_T2X_e8_,del_syn_T2X_e8_)));						//	S2
	p_p_t2U->clone_args.push_back(make_pair(NonTerminalDef::p_e7_,CloneArgs(copy_T2X_e7_,init_inh_T2X_e7_,del_inh_T2X_e7_)));					//	e7'
	p_p_t2U->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2U_S3,0,0,init_syn_T2X_e7_,del_syn_T2X_e7_)));						//	S3
	p_p_t2U->clone_args.push_back(make_pair(NonTerminalDef::p_e6_,CloneArgs(copy_T2X_e6_,init_inh_T2X_e6_,del_inh_T2X_e6_)));					//	e6'
	p_p_t2U->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2U_S4,0,0,init_syn_T2X_e6_,del_syn_T2X_e6_)));						//	S4
	p_p_t2U->clone_args.push_back(make_pair(NonTerminalDef::p_e5_,CloneArgs(copy_T2X_e5_,init_inh_T2X_e5_,del_inh_T2X_e5_)));					//	e5'
	p_p_t2U->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2U_S5,0,0,init_syn_T2X_e5_,del_syn_T2X_e5_)));						//	S5
	p_p_t2U->clone_args.push_back(make_pair(NonTerminalDef::p_e4_,CloneArgs(copy_T2X_e4_,init_inh_T2X_e4_,del_inh_T2X_e4_)));					//	e4'
	p_p_t2U->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2U_S6,0,0,init_syn_T2X_e4_,del_syn_T2X_e4_)));						//	S6
	p_p_t2U->clone_args.push_back(make_pair(NonTerminalDef::p_e3_,CloneArgs(copy_T2X_e3_,init_inh_T2X_e3_,del_inh_T2X_e3_)));					//	e3'
	p_p_t2U->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2U_S7,0,0,init_syn_T2X_e3_,del_syn_T2X_e3_)));						//	S7
	p_p_t2U->clone_args.push_back(make_pair(NonTerminalDef::p_e2_,CloneArgs(copy_T2X_e2_,init_inh_T2X_e2_,del_inh_T2X_e2_)));					//	e2'
	p_p_t2U->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2U_S8,0,0,init_syn_T2X_e2_,del_syn_T2X_e2_)));						//	S8

	p_p_t2V			=	new Produce(NonTerminalDef::p_t2);											//	t2
	p_p_t2V->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T2X_A,init_inh_T2X_A,del_inh_T2X_A,act_T2V_A)));						//	A
	p_p_t2V->clone_args.push_back(make_pair(NonTerminalDef::p_e10_,CloneArgs(copy_T2X_e10_,init_inh_T2X_e10_,del_inh_T2X_e10_)));					//	e10'
	p_p_t2V->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2V_S1,0,0,init_syn_T2X_e10_,del_syn_T2X_e10_)));						//	S1
	p_p_t2V->clone_args.push_back(make_pair(NonTerminalDef::p_e9_,CloneArgs(copy_T2X_e9_,init_inh_T2X_e9_,del_inh_T2X_e9_)));					//	e9'
	p_p_t2V->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2V_S2,0,0,init_syn_T2X_e9_,del_syn_T2X_e9_)));						//	S2
	p_p_t2V->clone_args.push_back(make_pair(NonTerminalDef::p_e8_,CloneArgs(copy_T2X_e8_,init_inh_T2X_e8_,del_inh_T2X_e8_)));					//	e8'
	p_p_t2V->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2V_S3,0,0,init_syn_T2X_e8_,del_syn_T2X_e8_)));						//	S3
	p_p_t2V->clone_args.push_back(make_pair(NonTerminalDef::p_e7_,CloneArgs(copy_T2X_e7_,init_inh_T2X_e7_,del_inh_T2X_e7_)));					//	e7'
	p_p_t2V->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2V_S4,0,0,init_syn_T2X_e7_,del_syn_T2X_e7_)));						//	S4
	p_p_t2V->clone_args.push_back(make_pair(NonTerminalDef::p_e6_,CloneArgs(copy_T2X_e6_,init_inh_T2X_e6_,del_inh_T2X_e6_)));					//	e6'
	p_p_t2V->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2V_S5,0,0,init_syn_T2X_e6_,del_syn_T2X_e6_)));						//	S5
	p_p_t2V->clone_args.push_back(make_pair(NonTerminalDef::p_e5_,CloneArgs(copy_T2X_e5_,init_inh_T2X_e5_,del_inh_T2X_e5_)));					//	e5'
	p_p_t2V->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2V_S6,0,0,init_syn_T2X_e5_,del_syn_T2X_e5_)));						//	S6
	p_p_t2V->clone_args.push_back(make_pair(NonTerminalDef::p_e4_,CloneArgs(copy_T2X_e4_,init_inh_T2X_e4_,del_inh_T2X_e4_)));					//	e4'
	p_p_t2V->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2V_S7,0,0,init_syn_T2X_e4_,del_syn_T2X_e4_)));						//	S7
	p_p_t2V->clone_args.push_back(make_pair(NonTerminalDef::p_e3_,CloneArgs(copy_T2X_e3_,init_inh_T2X_e3_,del_inh_T2X_e3_)));					//	e3'
	p_p_t2V->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2V_S8,0,0,init_syn_T2X_e3_,del_syn_T2X_e3_)));						//	S8
	p_p_t2V->clone_args.push_back(make_pair(NonTerminalDef::p_e2_,CloneArgs(copy_T2X_e2_,init_inh_T2X_e2_,del_inh_T2X_e2_)));					//	e2'
	p_p_t2V->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2V_S9,0,0,init_syn_T2X_e2_,del_syn_T2X_e2_)));						//	S9

	p_p_t2W			=	new Produce(NonTerminalDef::p_t2);											//	t2
	p_p_t2W->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T2X_A,init_inh_T2X_A,del_inh_T2X_A,act_T2W_A)));						//	A
	p_p_t2W->clone_args.push_back(make_pair(NonTerminalDef::p_e11_,CloneArgs(copy_T2X_e11_,init_inh_T2X_e11_,del_inh_T2X_e11_)));					//	e11'
	p_p_t2W->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2W_S1,0,0,init_syn_T2X_e11_,del_syn_T2X_e11_)));						//	S1
	p_p_t2W->clone_args.push_back(make_pair(NonTerminalDef::p_e10_,CloneArgs(copy_T2X_e10_,init_inh_T2X_e10_,del_inh_T2X_e10_)));					//	e10'
	p_p_t2W->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2W_S2,0,0,init_syn_T2X_e10_,del_syn_T2X_e10_)));						//	S2
	p_p_t2W->clone_args.push_back(make_pair(NonTerminalDef::p_e9_,CloneArgs(copy_T2X_e9_,init_inh_T2X_e9_,del_inh_T2X_e9_)));					//	e9'
	p_p_t2W->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2W_S3,0,0,init_syn_T2X_e9_,del_syn_T2X_e9_)));						//	S3
	p_p_t2W->clone_args.push_back(make_pair(NonTerminalDef::p_e8_,CloneArgs(copy_T2X_e8_,init_inh_T2X_e8_,del_inh_T2X_e8_)));					//	e8'
	p_p_t2W->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2W_S4,0,0,init_syn_T2X_e8_,del_syn_T2X_e8_)));						//	S4
	p_p_t2W->clone_args.push_back(make_pair(NonTerminalDef::p_e7_,CloneArgs(copy_T2X_e7_,init_inh_T2X_e7_,del_inh_T2X_e7_)));					//	e7'
	p_p_t2W->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2W_S5,0,0,init_syn_T2X_e7_,del_syn_T2X_e7_)));						//	S5
	p_p_t2W->clone_args.push_back(make_pair(NonTerminalDef::p_e6_,CloneArgs(copy_T2X_e6_,init_inh_T2X_e6_,del_inh_T2X_e6_)));					//	e6'
	p_p_t2W->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2W_S6,0,0,init_syn_T2X_e6_,del_syn_T2X_e6_)));						//	S6
	p_p_t2W->clone_args.push_back(make_pair(NonTerminalDef::p_e5_,CloneArgs(copy_T2X_e5_,init_inh_T2X_e5_,del_inh_T2X_e5_)));					//	e5'
	p_p_t2W->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2W_S7,0,0,init_syn_T2X_e5_,del_syn_T2X_e5_)));						//	S7
	p_p_t2W->clone_args.push_back(make_pair(NonTerminalDef::p_e4_,CloneArgs(copy_T2X_e4_,init_inh_T2X_e4_,del_inh_T2X_e4_)));					//	e4'
	p_p_t2W->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2W_S8,0,0,init_syn_T2X_e4_,del_syn_T2X_e4_)));						//	S8
	p_p_t2W->clone_args.push_back(make_pair(NonTerminalDef::p_e3_,CloneArgs(copy_T2X_e3_,init_inh_T2X_e3_,del_inh_T2X_e3_)));					//	e3'
	p_p_t2W->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2W_S9,0,0,init_syn_T2X_e3_,del_syn_T2X_e3_)));						//	S9
	p_p_t2W->clone_args.push_back(make_pair(NonTerminalDef::p_e2_,CloneArgs(copy_T2X_e2_,init_inh_T2X_e2_,del_inh_T2X_e2_)));					//	e2'
	p_p_t2W->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2W_S10,0,0,init_syn_T2X_e2_,del_syn_T2X_e2_)));						//	S10

	p_p_t2X			=	new Produce(NonTerminalDef::p_t2);											//	t2
	p_p_t2X->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T2X_A,init_inh_T2X_A,del_inh_T2X_A,act_T2X_A)));						//	A
	p_p_t2X->clone_args.push_back(make_pair(NonTerminalDef::p_e12_,CloneArgs(copy_T2X_e12_,init_inh_T2X_e12_,del_inh_T2X_e12_)));					//	e12'
	p_p_t2X->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2X_S1,0,0,init_syn_T2X_e12_,del_syn_T2X_e12_)));						//	S1
	p_p_t2X->clone_args.push_back(make_pair(NonTerminalDef::p_e11_,CloneArgs(copy_T2X_e11_,init_inh_T2X_e11_,del_inh_T2X_e11_)));					//	e11'
	p_p_t2X->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2X_S2,0,0,init_syn_T2X_e11_,del_syn_T2X_e11_)));						//	S2
	p_p_t2X->clone_args.push_back(make_pair(NonTerminalDef::p_e10_,CloneArgs(copy_T2X_e10_,init_inh_T2X_e10_,del_inh_T2X_e10_)));					//	e10'
	p_p_t2X->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2X_S3,0,0,init_syn_T2X_e10_,del_syn_T2X_e10_)));						//	S3
	p_p_t2X->clone_args.push_back(make_pair(NonTerminalDef::p_e9_,CloneArgs(copy_T2X_e9_,init_inh_T2X_e9_,del_inh_T2X_e9_)));					//	e9'
	p_p_t2X->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2X_S4,0,0,init_syn_T2X_e9_,del_syn_T2X_e9_)));						//	S4
	p_p_t2X->clone_args.push_back(make_pair(NonTerminalDef::p_e8_,CloneArgs(copy_T2X_e8_,init_inh_T2X_e8_,del_inh_T2X_e8_)));					//	e8'
	p_p_t2X->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2X_S5,0,0,init_syn_T2X_e8_,del_syn_T2X_e8_)));						//	S5
	p_p_t2X->clone_args.push_back(make_pair(NonTerminalDef::p_e7_,CloneArgs(copy_T2X_e7_,init_inh_T2X_e7_,del_inh_T2X_e7_)));					//	e7'
	p_p_t2X->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2X_S6,0,0,init_syn_T2X_e7_,del_syn_T2X_e7_)));						//	S6
	p_p_t2X->clone_args.push_back(make_pair(NonTerminalDef::p_e6_,CloneArgs(copy_T2X_e6_,init_inh_T2X_e6_,del_inh_T2X_e6_)));					//	e6'
	p_p_t2X->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2X_S7,0,0,init_syn_T2X_e6_,del_syn_T2X_e6_)));						//	S7
	p_p_t2X->clone_args.push_back(make_pair(NonTerminalDef::p_e5_,CloneArgs(copy_T2X_e5_,init_inh_T2X_e5_,del_inh_T2X_e5_)));					//	e5'
	p_p_t2X->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2X_S8,0,0,init_syn_T2X_e5_,del_syn_T2X_e5_)));						//	S8
	p_p_t2X->clone_args.push_back(make_pair(NonTerminalDef::p_e4_,CloneArgs(copy_T2X_e4_,init_inh_T2X_e4_,del_inh_T2X_e4_)));					//	e4'
	p_p_t2X->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2X_S9,0,0,init_syn_T2X_e4_,del_syn_T2X_e4_)));						//	S9
	p_p_t2X->clone_args.push_back(make_pair(NonTerminalDef::p_e3_,CloneArgs(copy_T2X_e3_,init_inh_T2X_e3_,del_inh_T2X_e3_)));					//	e3'
	p_p_t2X->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2X_S10,0,0,init_syn_T2X_e3_,del_syn_T2X_e3_)));						//	S10
	p_p_t2X->clone_args.push_back(make_pair(NonTerminalDef::p_e2_,CloneArgs(copy_T2X_e2_,init_inh_T2X_e2_,del_inh_T2X_e2_)));					//	e2'
	p_p_t2X->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T2X_S11,0,0,init_syn_T2X_e2_,del_syn_T2X_e2_)));						//	S11

	p_p_t2Y			=	new Produce(NonTerminalDef::p_t2);											//	¦Å
	p_p_t2Y->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T2_A,init_inh_T2_A,del_inh_T2_A,act_T2Y_A)));						//	A

	//...

	p_p_t3A			=	new Produce(NonTerminalDef::p_t3);											//	t3
	p_p_t3A->clone_args.push_back(make_pair(Terminal::p_plus_plus,CloneArgs()));					//	++
	p_p_t3A->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T3_A,init_inh_T3_A,del_inh_T3_A,act_T3A_A)));						//	A

	p_p_t3B			=	new Produce(NonTerminalDef::p_t3);											//	t3
	p_p_t3B->clone_args.push_back(make_pair(Terminal::p_minus_minus,CloneArgs()));					//	--
	p_p_t3B->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T3_A,init_inh_T3_A,del_inh_T3_A,act_T3B_A)));						//	A

	p_p_t3C			=	new Produce(NonTerminalDef::p_t3);											//	t3
	p_p_t3C->clone_args.push_back(make_pair(Terminal::p_l_bracket,CloneArgs()));					//	(
	p_p_t3C->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T3_A,init_inh_T3_A,del_inh_T3_A,act_T3C_A)));						//	A
	p_p_t3C->clone_args.push_back(make_pair(NonTerminalDef::p_args,CloneArgs(copy_T3C_args,init_inh_T3C_args,del_inh_T3C_args)));					//	args
	p_p_t3C->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T3C_S,0,0,init_syn_T3C_S)));						//	S
	p_p_t3C->clone_args.push_back(make_pair(Terminal::p_r_bracket,CloneArgs()));					//	)

	p_p_t3D			=	new Produce(NonTerminalDef::p_t3);											//	t3
	p_p_t3D->clone_args.push_back(make_pair(Terminal::p_l_s_bracket,CloneArgs()));					//	[
	p_p_t3D->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T3_A,init_inh_T3_A,del_inh_T3_A,act_T3D_A)));						//	A
	p_p_t3D->clone_args.push_back(make_pair(NonTerminalSyn::p_expr,CloneArgs(copy_T3D_expr,init_inh_T3D_expr)));					//	expr
	p_p_t3D->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_T3D_S1,init_inh_T3D_S1,del_inh_T3D_S1,act_T3D_S1,0,0,init_syn_T3D_S1,del_syn_T3D_S1)));						//	S1
	p_p_t3D->clone_args.push_back(make_pair(Terminal::p_r_s_bracket,CloneArgs()));					//	]
	p_p_t3D->clone_args.push_back(make_pair(NonTerminalDef::p_t4,CloneArgs(copy_T3D_T4,init_inh_T3D_T4,del_inh_T3D_T4)));						//	T4
	p_p_t3D->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T3D_S2,0,0,init_syn_T3D_S2)));						//	S2

	p_p_t3E			=	new Produce(NonTerminalDef::p_t3);											// ¦Å
	p_p_t3E->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T3_A,init_inh_T3_A,del_inh_T3_A,act_T3E_A)));						//	A

	//...

	p_p_t4A			=	new Produce(NonTerminalDef::p_t4);											//	t4
	p_p_t4A->clone_args.push_back(make_pair(Terminal::p_plus_plus,CloneArgs()));					//	++
	p_p_t4A->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T4_A,init_inh_T4_A,del_inh_T4_A,act_T4A_A)));						//	A

	p_p_t4B			=	new Produce(NonTerminalDef::p_t4);											//	t4
	p_p_t4B->clone_args.push_back(make_pair(Terminal::p_minus_minus,CloneArgs()));					//	--
	p_p_t4B->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T4_A,init_inh_T4_A,del_inh_T4_A,act_T4B_A)));						//	A

	p_p_t4C			=	new Produce(NonTerminalDef::p_t4);											//	¦Å
	p_p_t4C->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T4_A,init_inh_T4_A,del_inh_T4_A,act_T4C_A)));						//	A

	//...

	p_p_t5A			=	new Produce(NonTerminalDef::p_t5);											//	t5
	p_p_t5A->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T5_A,init_inh_T5_A,0,act_T5A_A)));						//	A
	p_p_t5A->clone_args.push_back(make_pair(NonTerminalDef::p_e2_,CloneArgs(copy_T5_e2_,init_inh_T5_e2_,del_inh_T5_e2_)));					//	e2'
	p_p_t5A->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5A_S,0,0,init_syn_T5_e2_,del_syn_T5_e2_)));						//	S

	p_p_t5B			=	new Produce(NonTerminalDef::p_t5);											//	t5
	p_p_t5B->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T5_A,init_inh_T5_A,0,act_T5B_A)));						//	A
	p_p_t5B->clone_args.push_back(make_pair(NonTerminalDef::p_e3_,CloneArgs(copy_T5_e3_,init_inh_T5_e3_,del_inh_T5_e3_)));					//	e3'
	p_p_t5B->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5B_S1,0,0,init_syn_T5_e3_,del_syn_T5_e3_)));						//	S1
	p_p_t5B->clone_args.push_back(make_pair(NonTerminalDef::p_e2_,CloneArgs(copy_T5_e2_,init_inh_T5_e2_,del_inh_T5_e2_)));					//	e2'
	p_p_t5B->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5B_S2,0,0,init_syn_T5_e2_,del_syn_T5_e2_)));						//	S2

	p_p_t5C			=	new Produce(NonTerminalDef::p_t5);											//	t5
	p_p_t5C->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T5_A,init_inh_T5_A,0,act_T5C_A)));						//	A
	p_p_t5C->clone_args.push_back(make_pair(NonTerminalDef::p_e4_,CloneArgs(copy_T5_e4_,init_inh_T5_e4_,del_inh_T5_e4_)));					//	e4'
	p_p_t5C->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5C_S1,0,0,init_syn_T5_e4_,del_syn_T5_e4_)));						//	S1
	p_p_t5C->clone_args.push_back(make_pair(NonTerminalDef::p_e3_,CloneArgs(copy_T5_e3_,init_inh_T5_e3_,del_inh_T5_e3_)));					//	e3'
	p_p_t5C->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5C_S2,0,0,init_syn_T5_e3_,del_syn_T5_e3_)));						//	S2
	p_p_t5C->clone_args.push_back(make_pair(NonTerminalDef::p_e2_,CloneArgs(copy_T5_e2_,init_inh_T5_e2_,del_inh_T5_e2_)));					//	e2'
	p_p_t5C->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5C_S3,0,0,init_syn_T5_e2_,del_syn_T5_e2_)));						//	S3

	p_p_t5D			=	new Produce(NonTerminalDef::p_t5);											//	t5
	p_p_t5D->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T5_A,init_inh_T5_A,0,act_T5D_A)));						//	A
	p_p_t5D->clone_args.push_back(make_pair(NonTerminalDef::p_e5_,CloneArgs(copy_T5_e5_,init_inh_T5_e5_,del_inh_T5_e5_)));					//	e5'
	p_p_t5D->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5D_S1,0,0,init_syn_T5_e5_,del_syn_T5_e5_)));						//	S1
	p_p_t5D->clone_args.push_back(make_pair(NonTerminalDef::p_e4_,CloneArgs(copy_T5_e4_,init_inh_T5_e4_,del_inh_T5_e4_)));					//	e4'
	p_p_t5D->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5D_S2,0,0,init_syn_T5_e4_,del_syn_T5_e4_)));						//	S2
	p_p_t5D->clone_args.push_back(make_pair(NonTerminalDef::p_e3_,CloneArgs(copy_T5_e3_,init_inh_T5_e3_,del_inh_T5_e3_)));					//	e3'
	p_p_t5D->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5D_S3,0,0,init_syn_T5_e3_,del_syn_T5_e3_)));						//	S3
	p_p_t5D->clone_args.push_back(make_pair(NonTerminalDef::p_e2_,CloneArgs(copy_T5_e2_,init_inh_T5_e2_,del_inh_T5_e2_)));					//	e2'
	p_p_t5D->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5D_S4,0,0,init_syn_T5_e2_,del_syn_T5_e2_)));						//	S4

	p_p_t5E			=	new Produce(NonTerminalDef::p_t5);											//	t5
	p_p_t5E->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T5_A,init_inh_T5_A,0,act_T5E_A)));						//	A
	p_p_t5E->clone_args.push_back(make_pair(NonTerminalDef::p_e6_,CloneArgs(copy_T5_e6_,init_inh_T5_e6_,del_inh_T5_e6_)));					//	e6'
	p_p_t5E->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5E_S1,0,0,init_syn_T5_e6_,del_syn_T5_e6_)));						//	S1
	p_p_t5E->clone_args.push_back(make_pair(NonTerminalDef::p_e5_,CloneArgs(copy_T5_e5_,init_inh_T5_e5_,del_inh_T5_e5_)));					//	e5'
	p_p_t5E->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5E_S2,0,0,init_syn_T5_e5_,del_syn_T5_e5_)));						//	S2
	p_p_t5E->clone_args.push_back(make_pair(NonTerminalDef::p_e4_,CloneArgs(copy_T5_e4_,init_inh_T5_e4_,del_inh_T5_e4_)));					//	e4'
	p_p_t5E->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5E_S3,0,0,init_syn_T5_e4_,del_syn_T5_e4_)));						//	S3
	p_p_t5E->clone_args.push_back(make_pair(NonTerminalDef::p_e3_,CloneArgs(copy_T5_e3_,init_inh_T5_e3_,del_inh_T5_e3_)));					//	e3'
	p_p_t5E->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5E_S4,0,0,init_syn_T5_e3_,del_syn_T5_e3_)));						//	S4
	p_p_t5E->clone_args.push_back(make_pair(NonTerminalDef::p_e2_,CloneArgs(copy_T5_e2_,init_inh_T5_e2_,del_inh_T5_e2_)));					//	e2'
	p_p_t5E->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5E_S5,0,0,init_syn_T5_e2_,del_syn_T5_e2_)));						//	S5

	p_p_t5F			=	new Produce(NonTerminalDef::p_t5);											//	t5
	p_p_t5F->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T5_A,init_inh_T5_A,0,act_T5F_A)));						//	A
	p_p_t5F->clone_args.push_back(make_pair(NonTerminalDef::p_e7_,CloneArgs(copy_T5_e7_,init_inh_T5_e7_,del_inh_T5_e7_)));					//	e7'
	p_p_t5F->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5F_S1,0,0,init_syn_T5_e7_,del_syn_T5_e7_)));						//	S1
	p_p_t5F->clone_args.push_back(make_pair(NonTerminalDef::p_e6_,CloneArgs(copy_T5_e6_,init_inh_T5_e6_,del_inh_T5_e6_)));					//	e6'
	p_p_t5F->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5F_S2,0,0,init_syn_T5_e6_,del_syn_T5_e6_)));						//	S2
	p_p_t5F->clone_args.push_back(make_pair(NonTerminalDef::p_e5_,CloneArgs(copy_T5_e5_,init_inh_T5_e5_,del_inh_T5_e5_)));					//	e5'
	p_p_t5F->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5F_S3,0,0,init_syn_T5_e5_,del_syn_T5_e5_)));						//	S3
	p_p_t5F->clone_args.push_back(make_pair(NonTerminalDef::p_e4_,CloneArgs(copy_T5_e4_,init_inh_T5_e4_,del_inh_T5_e4_)));					//	e4'
	p_p_t5F->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5F_S4,0,0,init_syn_T5_e4_,del_syn_T5_e4_)));						//	S4
	p_p_t5F->clone_args.push_back(make_pair(NonTerminalDef::p_e3_,CloneArgs(copy_T5_e3_,init_inh_T5_e3_,del_inh_T5_e3_)));					//	e3'
	p_p_t5F->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5F_S5,0,0,init_syn_T5_e3_,del_syn_T5_e3_)));						//	S5
	p_p_t5F->clone_args.push_back(make_pair(NonTerminalDef::p_e2_,CloneArgs(copy_T5_e2_,init_inh_T5_e2_,del_inh_T5_e2_)));					//	e2'
	p_p_t5F->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5F_S6,0,0,init_syn_T5_e2_,del_syn_T5_e2_)));						//	S6

	p_p_t5G			=	new Produce(NonTerminalDef::p_t5);											//	t5
	p_p_t5G->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T5_A,init_inh_T5_A,0,act_T5G_A)));						//	A
	p_p_t5G->clone_args.push_back(make_pair(NonTerminalDef::p_e8_,CloneArgs(copy_T5_e8_,init_inh_T5_e8_,del_inh_T5_e8_)));					//	e8'
	p_p_t5G->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5G_S1,0,0,init_syn_T5_e8_,del_syn_T5_e8_)));						//	S1
	p_p_t5G->clone_args.push_back(make_pair(NonTerminalDef::p_e7_,CloneArgs(copy_T5_e7_,init_inh_T5_e7_,del_inh_T5_e7_)));					//	e7'
	p_p_t5G->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5G_S2,0,0,init_syn_T5_e7_,del_syn_T5_e7_)));						//	S2
	p_p_t5G->clone_args.push_back(make_pair(NonTerminalDef::p_e6_,CloneArgs(copy_T5_e6_,init_inh_T5_e6_,del_inh_T5_e6_)));					//	e6'
	p_p_t5G->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5G_S3,0,0,init_syn_T5_e6_,del_syn_T5_e6_)));						//	S3
	p_p_t5G->clone_args.push_back(make_pair(NonTerminalDef::p_e5_,CloneArgs(copy_T5_e5_,init_inh_T5_e5_,del_inh_T5_e5_)));					//	e5'
	p_p_t5G->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5G_S4,0,0,init_syn_T5_e5_,del_syn_T5_e5_)));						//	S4
	p_p_t5G->clone_args.push_back(make_pair(NonTerminalDef::p_e4_,CloneArgs(copy_T5_e4_,init_inh_T5_e4_,del_inh_T5_e4_)));					//	e4'
	p_p_t5G->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5G_S5,0,0,init_syn_T5_e4_,del_syn_T5_e4_)));						//	S5
	p_p_t5G->clone_args.push_back(make_pair(NonTerminalDef::p_e3_,CloneArgs(copy_T5_e3_,init_inh_T5_e3_,del_inh_T5_e3_)));					//	e3'
	p_p_t5G->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5G_S6,0,0,init_syn_T5_e3_,del_syn_T5_e3_)));						//	S6
	p_p_t5G->clone_args.push_back(make_pair(NonTerminalDef::p_e2_,CloneArgs(copy_T5_e2_,init_inh_T5_e2_,del_inh_T5_e2_)));					//	e2'
	p_p_t5G->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5G_S7,0,0,init_syn_T5_e2_,del_syn_T5_e2_)));						//	S7

	p_p_t5H			=	new Produce(NonTerminalDef::p_t5);											//	t5
	p_p_t5H->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T5_A,init_inh_T5_A,0,act_T5H_A)));						//	A
	p_p_t5H->clone_args.push_back(make_pair(NonTerminalDef::p_e9_,CloneArgs(copy_T5_e9_,init_inh_T5_e9_,del_inh_T5_e9_)));					//	e9'
	p_p_t5H->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5H_S1,0,0,init_syn_T5_e9_,del_syn_T5_e9_)));						//	S1
	p_p_t5H->clone_args.push_back(make_pair(NonTerminalDef::p_e8_,CloneArgs(copy_T5_e8_,init_inh_T5_e8_,del_inh_T5_e8_)));					//	e8'
	p_p_t5H->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5H_S2,0,0,init_syn_T5_e8_,del_syn_T5_e8_)));						//	S2
	p_p_t5H->clone_args.push_back(make_pair(NonTerminalDef::p_e7_,CloneArgs(copy_T5_e7_,init_inh_T5_e7_,del_inh_T5_e7_)));					//	e7'
	p_p_t5H->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5H_S3,0,0,init_syn_T5_e7_,del_syn_T5_e7_)));						//	S3
	p_p_t5H->clone_args.push_back(make_pair(NonTerminalDef::p_e6_,CloneArgs(copy_T5_e6_,init_inh_T5_e6_,del_inh_T5_e6_)));					//	e6'
	p_p_t5H->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5H_S4,0,0,init_syn_T5_e6_,del_syn_T5_e6_)));						//	S4
	p_p_t5H->clone_args.push_back(make_pair(NonTerminalDef::p_e5_,CloneArgs(copy_T5_e5_,init_inh_T5_e5_,del_inh_T5_e5_)));					//	e5'
	p_p_t5H->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5H_S5,0,0,init_syn_T5_e5_,del_syn_T5_e5_)));						//	S5
	p_p_t5H->clone_args.push_back(make_pair(NonTerminalDef::p_e4_,CloneArgs(copy_T5_e4_,init_inh_T5_e4_,del_inh_T5_e4_)));					//	e4'
	p_p_t5H->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5H_S6,0,0,init_syn_T5_e4_,del_syn_T5_e4_)));						//	S6
	p_p_t5H->clone_args.push_back(make_pair(NonTerminalDef::p_e3_,CloneArgs(copy_T5_e3_,init_inh_T5_e3_,del_inh_T5_e3_)));					//	e3'
	p_p_t5H->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5H_S7,0,0,init_syn_T5_e3_,del_syn_T5_e3_)));						//	S7
	p_p_t5H->clone_args.push_back(make_pair(NonTerminalDef::p_e2_,CloneArgs(copy_T5_e2_,init_inh_T5_e2_,del_inh_T5_e2_)));					//	e2'
	p_p_t5H->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5H_S8,0,0,init_syn_T5_e2_,del_syn_T5_e2_)));						//	S8

	p_p_t5I			=	new Produce(NonTerminalDef::p_t5);											//	t5
	p_p_t5I->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T5_A,init_inh_T5_A,0,act_T5I_A)));						//	A
	p_p_t5I->clone_args.push_back(make_pair(NonTerminalDef::p_e10_,CloneArgs(copy_T5_e10_,init_inh_T5_e10_,del_inh_T5_e10_)));				//	e10'
	p_p_t5I->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5I_S1,0,0,init_syn_T5_e10_,del_syn_T5_e10_)));						//	S1
	p_p_t5I->clone_args.push_back(make_pair(NonTerminalDef::p_e9_,CloneArgs(copy_T5_e9_,init_inh_T5_e9_,del_inh_T5_e9_)));					//	e9'
	p_p_t5I->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5I_S2,0,0,init_syn_T5_e9_,del_syn_T5_e9_)));						//	S2
	p_p_t5I->clone_args.push_back(make_pair(NonTerminalDef::p_e8_,CloneArgs(copy_T5_e8_,init_inh_T5_e8_,del_inh_T5_e8_)));					//	e8'
	p_p_t5I->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5I_S3,0,0,init_syn_T5_e8_,del_syn_T5_e8_)));						//	S3
	p_p_t5I->clone_args.push_back(make_pair(NonTerminalDef::p_e7_,CloneArgs(copy_T5_e7_,init_inh_T5_e7_,del_inh_T5_e7_)));					//	e7'
	p_p_t5I->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5I_S4,0,0,init_syn_T5_e7_,del_syn_T5_e7_)));						//	S4
	p_p_t5I->clone_args.push_back(make_pair(NonTerminalDef::p_e6_,CloneArgs(copy_T5_e6_,init_inh_T5_e6_,del_inh_T5_e6_)));					//	e6'
	p_p_t5I->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5I_S5,0,0,init_syn_T5_e6_,del_syn_T5_e6_)));						//	S5
	p_p_t5I->clone_args.push_back(make_pair(NonTerminalDef::p_e5_,CloneArgs(copy_T5_e5_,init_inh_T5_e5_,del_inh_T5_e5_)));					//	e5'
	p_p_t5I->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5I_S6,0,0,init_syn_T5_e5_,del_syn_T5_e5_)));						//	S6
	p_p_t5I->clone_args.push_back(make_pair(NonTerminalDef::p_e4_,CloneArgs(copy_T5_e4_,init_inh_T5_e4_,del_inh_T5_e4_)));					//	e4'
	p_p_t5I->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5I_S7,0,0,init_syn_T5_e4_,del_syn_T5_e4_)));						//	S7
	p_p_t5I->clone_args.push_back(make_pair(NonTerminalDef::p_e3_,CloneArgs(copy_T5_e3_,init_inh_T5_e3_,del_inh_T5_e3_)));					//	e3'
	p_p_t5I->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5I_S8,0,0,init_syn_T5_e3_,del_syn_T5_e3_)));						//	S8
	p_p_t5I->clone_args.push_back(make_pair(NonTerminalDef::p_e2_,CloneArgs(copy_T5_e2_,init_inh_T5_e2_,del_inh_T5_e2_)));					//	e2'
	p_p_t5I->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5I_S9,0,0,init_syn_T5_e2_,del_syn_T5_e2_)));						//	S9

	p_p_t5J			=	new Produce(NonTerminalDef::p_t5);											//	t5
	p_p_t5J->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T5_A,init_inh_T5_A,0,act_T5J_A)));						//	A
	p_p_t5J->clone_args.push_back(make_pair(NonTerminalDef::p_e11_,CloneArgs(copy_T5_e11_,init_inh_T5_e11_,del_inh_T5_e11_)));				//	e11'
	p_p_t5J->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5J_S1,0,0,init_syn_T5_e11_,del_syn_T5_e11_)));						//	S1
	p_p_t5J->clone_args.push_back(make_pair(NonTerminalDef::p_e10_,CloneArgs(copy_T5_e10_,init_inh_T5_e10_,del_inh_T5_e10_)));				//	e10'
	p_p_t5J->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5J_S2,0,0,init_syn_T5_e10_,del_syn_T5_e10_)));						//	S2
	p_p_t5J->clone_args.push_back(make_pair(NonTerminalDef::p_e9_,CloneArgs(copy_T5_e9_,init_inh_T5_e9_,del_inh_T5_e9_)));					//	e9'
	p_p_t5J->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5J_S3,0,0,init_syn_T5_e9_,del_syn_T5_e9_)));						//	S3
	p_p_t5J->clone_args.push_back(make_pair(NonTerminalDef::p_e8_,CloneArgs(copy_T5_e8_,init_inh_T5_e8_,del_inh_T5_e8_)));					//	e8'
	p_p_t5J->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5J_S4,0,0,init_syn_T5_e8_,del_syn_T5_e8_)));						//	S4
	p_p_t5J->clone_args.push_back(make_pair(NonTerminalDef::p_e7_,CloneArgs(copy_T5_e7_,init_inh_T5_e7_,del_inh_T5_e7_)));					//	e7'
	p_p_t5J->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5J_S5,0,0,init_syn_T5_e7_,del_syn_T5_e7_)));						//	S5
	p_p_t5J->clone_args.push_back(make_pair(NonTerminalDef::p_e6_,CloneArgs(copy_T5_e6_,init_inh_T5_e6_,del_inh_T5_e6_)));					//	e6'
	p_p_t5J->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5J_S6,0,0,init_syn_T5_e6_,del_syn_T5_e6_)));						//	S6
	p_p_t5J->clone_args.push_back(make_pair(NonTerminalDef::p_e5_,CloneArgs(copy_T5_e5_,init_inh_T5_e5_,del_inh_T5_e5_)));					//	e5'
	p_p_t5J->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5J_S7,0,0,init_syn_T5_e5_,del_syn_T5_e5_)));						//	S7
	p_p_t5J->clone_args.push_back(make_pair(NonTerminalDef::p_e4_,CloneArgs(copy_T5_e4_,init_inh_T5_e4_,del_inh_T5_e4_)));					//	e4'
	p_p_t5J->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5J_S8,0,0,init_syn_T5_e4_,del_syn_T5_e4_)));						//	S8
	p_p_t5J->clone_args.push_back(make_pair(NonTerminalDef::p_e3_,CloneArgs(copy_T5_e3_,init_inh_T5_e3_,del_inh_T5_e3_)));					//	e3'
	p_p_t5J->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5J_S9,0,0,init_syn_T5_e3_,del_syn_T5_e3_)));						//	S9
	p_p_t5J->clone_args.push_back(make_pair(NonTerminalDef::p_e2_,CloneArgs(copy_T5_e2_,init_inh_T5_e2_,del_inh_T5_e2_)));					//	e2'
	p_p_t5J->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5J_S10,0,0,init_syn_T5_e2_,del_syn_T5_e2_)));						//	S10

	p_p_t5K			=	new Produce(NonTerminalDef::p_t5);											//	t5
	p_p_t5K->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T5_A,init_inh_T5_A,0,act_T5K_A)));						//	A
	p_p_t5K->clone_args.push_back(make_pair(NonTerminalDef::p_e12_,CloneArgs(copy_T5_e12_,init_inh_T5_e12_,del_inh_T5_e12_)));				//	e12'
	p_p_t5K->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5K_S1,0,0,init_syn_T5_e12_,del_syn_T5_e12_)));						//	S1
	p_p_t5K->clone_args.push_back(make_pair(NonTerminalDef::p_e11_,CloneArgs(copy_T5_e11_,init_inh_T5_e11_,del_inh_T5_e11_)));				//	e11'
	p_p_t5K->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5K_S2,0,0,init_syn_T5_e11_,del_syn_T5_e11_)));						//	S2
	p_p_t5K->clone_args.push_back(make_pair(NonTerminalDef::p_e10_,CloneArgs(copy_T5_e10_,init_inh_T5_e10_,del_inh_T5_e10_)));				//	e10'
	p_p_t5K->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5K_S3,0,0,init_syn_T5_e10_,del_syn_T5_e10_)));						//	S3
	p_p_t5K->clone_args.push_back(make_pair(NonTerminalDef::p_e9_,CloneArgs(copy_T5_e9_,init_inh_T5_e9_,del_inh_T5_e9_)));					//	e9'
	p_p_t5K->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5K_S4,0,0,init_syn_T5_e9_,del_syn_T5_e9_)));						//	S4
	p_p_t5K->clone_args.push_back(make_pair(NonTerminalDef::p_e8_,CloneArgs(copy_T5_e8_,init_inh_T5_e8_,del_inh_T5_e8_)));					//	e8'
	p_p_t5K->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5K_S5,0,0,init_syn_T5_e8_,del_syn_T5_e8_)));						//	S5
	p_p_t5K->clone_args.push_back(make_pair(NonTerminalDef::p_e7_,CloneArgs(copy_T5_e7_,init_inh_T5_e7_,del_inh_T5_e7_)));					//	e7'
	p_p_t5K->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5K_S6,0,0,init_syn_T5_e7_,del_syn_T5_e7_)));						//	S6
	p_p_t5K->clone_args.push_back(make_pair(NonTerminalDef::p_e6_,CloneArgs(copy_T5_e6_,init_inh_T5_e6_,del_inh_T5_e6_)));					//	e6'
	p_p_t5K->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5K_S7,0,0,init_syn_T5_e6_,del_syn_T5_e6_)));						//	S7
	p_p_t5K->clone_args.push_back(make_pair(NonTerminalDef::p_e5_,CloneArgs(copy_T5_e5_,init_inh_T5_e5_,del_inh_T5_e5_)));					//	e5'
	p_p_t5K->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5K_S8,0,0,init_syn_T5_e5_,del_syn_T5_e5_)));						//	S8
	p_p_t5K->clone_args.push_back(make_pair(NonTerminalDef::p_e4_,CloneArgs(copy_T5_e4_,init_inh_T5_e4_,del_inh_T5_e4_)));					//	e4'
	p_p_t5K->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5K_S9,0,0,init_syn_T5_e4_,del_syn_T5_e4_)));						//	S9
	p_p_t5K->clone_args.push_back(make_pair(NonTerminalDef::p_e3_,CloneArgs(copy_T5_e3_,init_inh_T5_e3_,del_inh_T5_e3_)));					//	e3'
	p_p_t5K->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5K_S10,0,0,init_syn_T5_e3_,del_syn_T5_e3_)));						//	S10
	p_p_t5K->clone_args.push_back(make_pair(NonTerminalDef::p_e2_,CloneArgs(copy_T5_e2_,init_inh_T5_e2_,del_inh_T5_e2_)));					//	e2'
	p_p_t5K->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_T5K_S11,0,0,init_syn_T5_e2_,del_syn_T5_e2_)));						//	S11

	p_p_t5L			=	new Produce(NonTerminalDef::p_t5);										// ¦Å
	p_p_t5L->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_T5_A,init_inh_T5_A,0,act_T5L_A)));		

	//...

	p_p_args1		=	new Produce(NonTerminalDef::p_args);										//	args
	p_p_args1->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_args1_A1)));						//	A1
	p_p_args1->clone_args.push_back(make_pair(NonTerminalSyn::p_args_,CloneArgs(copy_args1_args_,init_inh_args1_args_,del_inh_args1_args_)));				//	args'
	p_p_args1->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_args1_A2,init_inh_args1_A2,del_inh_args1_A2,act_args1_A2,init_temp_args1_A2,del_temp_args1_A2)));						//	A2

	p_p_args2		=	new Produce(NonTerminalDef::p_args);										// ¦Å
	p_p_args2->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_args2_A,init_inh_args2_A,del_inh_args2_A,act_args2_A)));						//	A

	p_p_args_		=	new Produce(NonTerminalSyn::p_args_);										//	args'
	p_p_args_->clone_args.push_back(make_pair(NonTerminalSyn::p_arg,CloneArgs(copy_args__arg,init_inh_args__arg,del_inh_args__arg)));					//	arg
	p_p_args_->clone_args.push_back(make_pair(NonTerminalDef::p_args__,CloneArgs(copy_args__args__,init_inh_args__args__,del_inh_args__args__)));				//	args"

	p_p_args__1		=	new Produce(NonTerminalDef::p_args__);										//	args"
	p_p_args__1->clone_args.push_back(make_pair(Terminal::p_comma,CloneArgs()));					//	,
	p_p_args__1->clone_args.push_back(make_pair(NonTerminalSyn::p_args_,CloneArgs(copy_args___args_,init_inh_args___args_,del_inh_args___args_)));				//	args'

	p_p_args__2		=	new Produce(NonTerminalDef::p_args__);										// ¦Å

	p_p_arg			=	new Produce(NonTerminalSyn::p_arg);											//	arg
	p_p_arg->clone_args.push_back(make_pair(NonTerminalSyn::p_e1,CloneArgs(copy_arg_e1,init_inh_arg_e1)));						//	e1
	p_p_arg->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_arg_S,init_inh_arg_S,del_inh_arg_S,act_arg_S,0,0,init_syn_arg_S,del_syn_arg_S)));						//	S

	//...

	p_p_loc			=	new Produce(NonTerminalSyn::p_loc);											//	loc
	p_p_loc->clone_args.push_back(make_pair(Terminal::p_id,CloneArgs()));							//	id
	p_p_loc->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(0,0,0,act_loc_A,init_temp_loc_A,del_temp_loc_A)));						//	A
	p_p_loc->clone_args.push_back(make_pair(NonTerminalDef::p_loc_,CloneArgs(copy_loc_loc_,init_inh_loc_loc_,del_inh_loc_loc_)));					//	loc'
	p_p_loc->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(0,0,0,act_loc_S,0,0,init_syn_loc_S)));						//	S

	p_p_loc_1		=	new Produce(NonTerminalDef::p_loc_);										//	loc'
	p_p_loc_1->clone_args.push_back(make_pair(Terminal::p_l_s_bracket,CloneArgs()));				//	[
	p_p_loc_1->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_loc__A,init_inh_loc__A,del_inh_loc__A,act_loc_1_A)));						//	A
	p_p_loc_1->clone_args.push_back(make_pair(NonTerminalSyn::p_expr,CloneArgs(copy_loc__expr,init_inh_loc__expr)));					//	expr
	p_p_loc_1->clone_args.push_back(make_pair(SynRecord::p_syn,CloneArgs(copy_loc__S,init_inh_loc__S,del_inh_loc__S,act_loc_1_S,0,0,init_syn_loc__S,del_syn_loc__S)));						//	S
	p_p_loc_1->clone_args.push_back(make_pair(Terminal::p_r_s_bracket,CloneArgs()));				//	]

	p_p_loc_2		=	new Produce(NonTerminalDef::p_loc_);										// ¦Å
	p_p_loc_2->clone_args.push_back(make_pair(ActRecord::p_act,CloneArgs(copy_loc__A,init_inh_loc__A,del_inh_loc__A,act_loc_2_A)));						//	A

}
void Produce::Destroy()
{
	delete p_p_program;			//	options main( ){decls stmts}

	delete p_p_options1;		//	option options
	delete p_p_options2;		//	¦Å	
	delete p_p_option1;			//	void id F
	delete p_p_option2;			//	B id option'
	delete p_p_option_1;		//	F
	delete p_p_option_2;		//	decl';

	delete p_p_decls1;			//	decl decls
	delete p_p_decls2;			//	¦Å
	delete p_p_decl;			//	B id decl';
	delete p_p_decl_1;			//	A
	delete p_p_decl_2;			//	V

	delete p_p_b1;				//	bool
	delete p_p_b2;				//	char
	delete p_p_b3;				//	short
	delete p_p_b4;				//	int
	delete p_p_b5;				//	float
	delete p_p_b6;				//	double

	delete p_p_a;				//	[size]Opt1
	delete p_p_opt1A;			//	={L}
	delete p_p_opt1B;			//	¦Å
	delete p_p_l1;				//	L'
	delete p_p_l2;				//	¦Å
	delete p_p_l_;				//	e1 L"
	delete p_p_l__1;			//	,L' 
	delete p_p_l__2;			//	¦Å

	delete p_p_v;				//	Opt2 V'
	delete p_p_v_1;				//	,id Opt2 V'
	delete p_p_v_2;				//	¦Å
	delete p_p_opt2A;			//	=e1
	delete p_p_opt2B;			//	¦Å

	delete p_p_f;				//	(params){decls stmts}
	delete p_p_params1;			//	params'
	delete p_p_params2;			//	¦Å
	delete p_p_params_;			//	param params"
	delete p_p_params__1;		//	,params'
	delete p_p_params__2;		//	¦Å
	delete p_p_param;			//	B id tail
	delete p_p_tail1;			//	[optexpr1]
	delete p_p_tail2;			//	¦Å
	delete p_p_optexpr1A;		//	size
	delete p_p_optexpr1B;		// ¦Å
	delete p_p_size1;			//	num
	delete p_p_size2;			//	ascii

	delete p_p_stmt1;			// ;
	delete p_p_stmt2;			// expr;
	delete p_p_stmt3;			// if(expr)stmt E
	delete p_p_stmt4;			// while(expr)stmt
	delete p_p_stmt5;			// do stmt while(expr);
	delete p_p_stmt6;			// break;
	delete p_p_stmt7;			// continue;
	delete p_p_stmt8;			// return optexpr3;
	delete p_p_stmt9;			// for(optexpr2;optexpr2;optexpr2)stmt
	delete p_p_stmt10;			// switch(expr)stmt
	delete p_p_stmt11;			// case label: stmt
	delete p_p_stmt12;			// default: stmt
	delete p_p_stmt13;			// {stmts}
	delete p_p_else1;			// else stmt
	delete p_p_else2;			// ¦Å
	delete p_p_stmts1;			// stmt stmts
	delete p_p_stmts2;			// ¦Å
	delete p_p_optexpr2A;		// expr
	delete p_p_optexpr2B;		// ¦Å
	delete p_p_optexpr3A;		// expr
	delete p_p_optexpr3B;		// ¦Å
	delete p_p_label1;			//	false
	delete p_p_label2;			//	true
	delete p_p_label3;			//	ascii
	delete p_p_label4;			//	num
	delete p_p_label5;			//	-num

	delete p_p_expr;			// e1 expr'
	delete p_p_expr_1;			// ,e1 expr'
	delete p_p_expr_2;			// ¦Å

	delete p_p_e1A;				// loc e1'
	delete p_p_e1B;				// e2

	delete p_p_e2;				// e3 e2'
	delete p_p_e2_1;			// ?e3:e2
	delete p_p_e2_2;			// ¦Å

	delete p_p_e3;				// e4 e3'
	delete p_p_e3_1;			// ||e4 e3'
	delete p_p_e3_2;			// ¦Å

	delete p_p_e4;				// e5 e4'
	delete p_p_e4_1;			// &&e5 e4'
	delete p_p_e4_2;			// ¦Å

	delete p_p_e5;				// e6 e5'
	delete p_p_e5_1;			// |e6 e5'
	delete p_p_e5_2;			// ¦Å

	delete p_p_e6;				// e7 e6'
	delete p_p_e6_1;			// ^e7 e6'
	delete p_p_e6_2;			// ¦Å

	delete p_p_e7;				// e8 e7'
	delete p_p_e7_1;			// &e8 e7'
	delete p_p_e7_2;			// ¦Å

	delete p_p_e8;				// e9 e8'
	delete p_p_e8_1;			// ==e9 e8'
	delete p_p_e8_2;			// !=e9 e8'
	delete p_p_e8_3;			// ¦Å

	delete p_p_e9;				// e10 e9'
	delete p_p_e9_1;			// <e10 e9'
	delete p_p_e9_2;			// <=e10 e9'
	delete p_p_e9_3;			// >e10 e9'
	delete p_p_e9_4;			// >=e10 e9'
	delete p_p_e9_5;			// ¦Å

	delete p_p_e10;				// e11 e10'
	delete p_p_e10_1;			// <<e11 e10'
	delete p_p_e10_2;			// >>e11 e10'
	delete p_p_e10_3;			// ¦Å

	delete p_p_e11;				// e12 e11'
	delete p_p_e11_1;			// +e12 e11'
	delete p_p_e11_2;			// -e12 e11'
	delete p_p_e11_3;			// ¦Å

	delete p_p_e12;				// e13 e12'
	delete p_p_e12_1;			// *e13 e12'
	delete p_p_e12_2;			// /e13 e12'
	delete p_p_e12_3;			// %e13 e12'
	delete p_p_e12_4;			// ¦Å

	delete p_p_e13A;			// ~e13
	delete p_p_e13B;			// !e13
	delete p_p_e13C;			// -e13
	delete p_p_e13D;			// +e13
	delete p_p_e13E;			// e14

	delete p_p_e14A;			// true
	delete p_p_e14B;			// false
	delete p_p_e14C;			// ascii
	delete p_p_e14D;			// num
	delete p_p_e14E;			// real
	delete p_p_e14F;			// ++loc
	delete p_p_e14G;			// --loc
	delete p_p_e14H;			// (expr)
	delete p_p_e14I;			// id T3

	delete p_p_t1A;				// ++T5
	delete p_p_t1B;				// --T5
	delete p_p_t1C;				// (args)T5
	delete p_p_t1D;				// [expr]T2
	delete p_p_t1E;				// =e1
	delete p_p_t1F;				// *=e1
	delete p_p_t1G;				// /=e1
	delete p_p_t1H;				// %=e1
	delete p_p_t1I;				// +=e1
	delete p_p_t1J;				// -=e1
	delete p_p_t1K;				// <<=e1
	delete p_p_t1L;				// >>=e1
	delete p_p_t1M;				// &=e1
	delete p_p_t1N;				// |=e1
	delete p_p_t1O;				// ^=e1
	delete p_p_t1P;				// e2'
	delete p_p_t1Q;				// e3'e2'
	delete p_p_t1R;				// e4'e3'e2'
	delete p_p_t1S;				// e5'e4'e3'e2'
	delete p_p_t1T;				// e6'e5'e4'e3'e2'
	delete p_p_t1U;				// e7'e6'e5'e4'e3'e2'
	delete p_p_t1V;				// e8'e7'e6'e5'e4'e3'e2'
	delete p_p_t1W;				// e9'e8'e7'e6'e5'e4'e3'e2'
	delete p_p_t1X;				// e10'e9'e8'e7'e6'e5'e4'e3'e2'
	delete p_p_t1Y;				// e11'e10'e9'e8'e7'e6'e5'e4'e3'e2'
	delete p_p_t1Z;				// e12'e11'e10'e9'e8'e7'e6'e5'e4'e3'e2'
	delete p_p_t1A1;			// ¦Å

	delete p_p_t2A;				// ++T5
	delete p_p_t2B;				// --T5
	delete p_p_t2C;				// =e1
	delete p_p_t2D;				// *=e1
	delete p_p_t2E;				// /=e1
	delete p_p_t2F;				// %=e1
	delete p_p_t2G;				// +=e1
	delete p_p_t2H;				// -=e1
	delete p_p_t2I;				// <<=e1
	delete p_p_t2J;				// >>=e1
	delete p_p_t2K;				// &=e1
	delete p_p_t2L;				// |=e1
	delete p_p_t2M;				// ^=e1
	delete p_p_t2N;				// e2'
	delete p_p_t2O;				// e3'e2'
	delete p_p_t2P;				// e4'e3'e2'
	delete p_p_t2Q;				// e5'e4'e3'e2'
	delete p_p_t2R;				// e6'e5'e4'e3'e2'
	delete p_p_t2S;				// e7'e6'e5'e4'e3'e2'
	delete p_p_t2T;				// e8'e7'e6'e5'e4'e3'e2'
	delete p_p_t2U;				// e9'e8'e7'e6'e5'e4'e3'e2'
	delete p_p_t2V;				// e10'e9'e8'e7'e6'e5'e4'e3'e2'
	delete p_p_t2W;				// e11'e10'e9'e8'e7'e6'e5'e4'e3'e2'
	delete p_p_t2X;				// e12'e11'e10'e9'e8'e7'e6'e5'e4'e3'e2'
	delete p_p_t2Y;				// ¦Å

	delete p_p_t3A;				// ++
	delete p_p_t3B;				// --
	delete p_p_t3C;				// (args)
	delete p_p_t3D;				// [expr]T2
	delete p_p_t3E;				// ¦Å

	delete p_p_t4A;				// ++
	delete p_p_t4B;				// --
	delete p_p_t4C;				// ¦Å

	delete p_p_t5A;				// e2'
	delete p_p_t5B;				// e3'e2'
	delete p_p_t5C;				// e4'e3'e2'
	delete p_p_t5D;				// e5'e4'e3'e2'
	delete p_p_t5E;				// e6'e5'e4'e3'e2'
	delete p_p_t5F;				// e7'e6'e5'e4'e3'e2'
	delete p_p_t5G;				// e8'e7'e6'e5'e4'e3'e2'
	delete p_p_t5H;				// e9'e8'e7'e6'e5'e4'e3'e2'
	delete p_p_t5I;				// e10'e9'e8'e7'e6'e5'e4'e3'e2'
	delete p_p_t5J;				// e11'e10'e9'e8'e7'e6'e5'e4'e3'e2'
	delete p_p_t5K;				// e12'e11'e10'e9'e8'e7'e6'e5'e4'e3'e2'
	delete p_p_t5L;				// ¦Å

	delete p_p_args1;			// args'
	delete p_p_args2;			// ¦Å
	delete p_p_args_;			// arg args"
	delete p_p_args__1;			// ,args'
	delete p_p_args__2;			// ¦Å
	delete p_p_arg;				// e1

	delete p_p_loc;				// id loc'
	delete p_p_loc_1;			// [expr]
	delete p_p_loc_2;			// ¦Å
}
Produce::bodylist Produce::getBody()const
{
	bodylist ret;

	for(CloneArgsList::const_iterator citor=clone_args.begin();citor!=clone_args.end();++citor)
		ret.push_back(
				citor->first->clone(
					citor->second.copy,
					citor->second.initInh ? citor->second.initInh() : 0,
					citor->second.delInh,
					citor->second.act,
					citor->second.initTemp ? citor->second.initTemp() : 0,
					citor->second.delTemp,
					citor->second.initSyn ? citor->second.initSyn() : 0,
					citor->second.delSyn
				)
			);

	return ret;
}