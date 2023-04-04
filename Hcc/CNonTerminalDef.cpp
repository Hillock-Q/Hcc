#include "CNonTerminalDef.h"
#include "CTag.h"

NonTerminalDef::n_def_pt NonTerminalDef::p_options=0;

NonTerminalDef::n_def_pt NonTerminalDef::p_decls=0;
NonTerminalDef::n_def_pt NonTerminalDef::p_decl_=0;

NonTerminalDef::n_def_pt NonTerminalDef::p_opt1=0;
NonTerminalDef::n_def_pt NonTerminalDef::p_l=0;
NonTerminalDef::n_def_pt NonTerminalDef::p_l__=0;

NonTerminalDef::n_def_pt NonTerminalDef::p_v=0;
NonTerminalDef::n_def_pt NonTerminalDef::p_v_=0;
NonTerminalDef::n_def_pt NonTerminalDef::p_opt2=0;

NonTerminalDef::n_def_pt NonTerminalDef::p_params=0;
NonTerminalDef::n_def_pt NonTerminalDef::p_params__=0;
NonTerminalDef::n_def_pt NonTerminalDef::p_tail=0;
NonTerminalDef::n_def_pt NonTerminalDef::p_optexpr1=0;

NonTerminalDef::n_def_pt NonTerminalDef::p_else=0;
NonTerminalDef::n_def_pt NonTerminalDef::p_stmts=0;
NonTerminalDef::n_def_pt NonTerminalDef::p_optexpr2=0;
NonTerminalDef::n_def_pt NonTerminalDef::p_optexpr3=0;

NonTerminalDef::n_def_pt NonTerminalDef::p_expr_=0;
NonTerminalDef::n_def_pt NonTerminalDef::p_e2_=0;
NonTerminalDef::n_def_pt NonTerminalDef::p_e3_=0;
NonTerminalDef::n_def_pt NonTerminalDef::p_e4_=0;
NonTerminalDef::n_def_pt NonTerminalDef::p_e5_=0;
NonTerminalDef::n_def_pt NonTerminalDef::p_e6_=0;
NonTerminalDef::n_def_pt NonTerminalDef::p_e7_=0;
NonTerminalDef::n_def_pt NonTerminalDef::p_e8_=0;
NonTerminalDef::n_def_pt NonTerminalDef::p_e9_=0;
NonTerminalDef::n_def_pt NonTerminalDef::p_e10_=0;
NonTerminalDef::n_def_pt NonTerminalDef::p_e11_=0;
NonTerminalDef::n_def_pt NonTerminalDef::p_e12_=0;

NonTerminalDef::n_def_pt NonTerminalDef::p_t1=0;
NonTerminalDef::n_def_pt NonTerminalDef::p_t2=0;
NonTerminalDef::n_def_pt NonTerminalDef::p_t3=0;
NonTerminalDef::n_def_pt NonTerminalDef::p_t4=0;
NonTerminalDef::n_def_pt NonTerminalDef::p_t5=0;

NonTerminalDef::n_def_pt NonTerminalDef::p_args=0;
NonTerminalDef::n_def_pt NonTerminalDef::p_args__=0;

NonTerminalDef::n_def_pt NonTerminalDef::p_loc_=0;

void NonTerminalDef::Generate()
{
	//...

	p_options	=	new NonTerminalDef(Compiler::_options);
	p_options->ppl= new produce_list();

	//...

	p_decls		=	new NonTerminalDef(Compiler::_decls);
	p_decls->ppl= new produce_list();
	p_decl_		=	new NonTerminalDef(Compiler::_decl_);
	p_decl_->ppl= new produce_list();

	//...

	p_opt1		=	new NonTerminalDef(Compiler::_opt1);
	p_opt1->ppl= new produce_list();
	p_l			=	new NonTerminalDef(Compiler::_l);
	p_l->ppl= new produce_list();
	p_l__		=	new NonTerminalDef(Compiler::_l__);
	p_l__->ppl= new produce_list();

	//...

	p_v			=	new NonTerminalDef(Compiler::_v);
	p_v->ppl= new produce_list();
	p_v_		=	new NonTerminalDef(Compiler::_v_);
	p_v_->ppl= new produce_list();
	p_opt2		=	new NonTerminalDef(Compiler::_opt2);
	p_opt2->ppl= new produce_list();

	//...

	p_params	=	new NonTerminalDef(Compiler::_params);
	p_params->ppl= new produce_list();
	p_params__	=	new NonTerminalDef(Compiler::_params__);
	p_params__->ppl= new produce_list();
	p_tail		=	new NonTerminalDef(Compiler::_tail);
	p_tail->ppl= new produce_list();
	p_optexpr1	=	new NonTerminalDef(Compiler::_optexpr1);
	p_optexpr1->ppl= new produce_list();

	//...

	p_else		=	new NonTerminalDef(Compiler::_else);
	p_else->ppl= new produce_list();
	p_stmts		=	new NonTerminalDef(Compiler::_stmts);
	p_stmts->ppl= new produce_list();
	p_optexpr2	=	new NonTerminalDef(Compiler::_optexpr2);
	p_optexpr2->ppl= new produce_list();
	p_optexpr3	=	new NonTerminalDef(Compiler::_optexpr3);
	p_optexpr3->ppl= new produce_list();

	//...

	p_expr_		=	new NonTerminalDef(Compiler::_expr_);
	p_expr_->ppl= new produce_list();
	p_e2_		=	new NonTerminalDef(Compiler::_e2_);
	p_e2_->ppl= new produce_list();
	p_e3_		=	new NonTerminalDef(Compiler::_e3_);
	p_e3_->ppl= new produce_list();
	p_e4_		=	new NonTerminalDef(Compiler::_e4_);
	p_e4_->ppl= new produce_list();
	p_e5_		=	new NonTerminalDef(Compiler::_e5_);
	p_e5_->ppl= new produce_list();
	p_e6_		=	new NonTerminalDef(Compiler::_e6_);
	p_e6_->ppl= new produce_list();
	p_e7_		=	new NonTerminalDef(Compiler::_e7_);
	p_e7_->ppl= new produce_list();
	p_e8_		=	new NonTerminalDef(Compiler::_e8_);
	p_e8_->ppl= new produce_list();
	p_e9_		=	new NonTerminalDef(Compiler::_e9_);
	p_e9_->ppl= new produce_list();
	p_e10_		=	new NonTerminalDef(Compiler::_e10_);
	p_e10_->ppl= new produce_list();
	p_e11_		=	new NonTerminalDef(Compiler::_e11_);
	p_e11_->ppl= new produce_list();
	p_e12_		=	new NonTerminalDef(Compiler::_e12_);
	p_e12_->ppl= new produce_list();

	//...

	p_t1		=	new NonTerminalDef(Compiler::_t1);
	p_t1->ppl= new produce_list();
	p_t2		=	new NonTerminalDef(Compiler::_t2);
	p_t2->ppl= new produce_list();
	p_t3		=	new NonTerminalDef(Compiler::_t3);
	p_t3->ppl= new produce_list();
	p_t4		=	new NonTerminalDef(Compiler::_t4);
	p_t4->ppl= new produce_list();
	p_t5		=	new NonTerminalDef(Compiler::_t5);
	p_t5->ppl= new produce_list();

	//...

	p_args		=	new NonTerminalDef(Compiler::_args);
	p_args->ppl= new produce_list();
	p_args__	=	new NonTerminalDef(Compiler::_args__);
	p_args__->ppl= new produce_list();

	//...

	p_loc_		=	new NonTerminalDef(Compiler::_loc_);
	p_loc_->ppl= new produce_list();
}
void NonTerminalDef::Destroy()
{
	//...

	delete p_options->ppl;
	delete p_options;

	//...

	delete p_decls->ppl;
	delete p_decls;
	delete p_decl_->ppl;
	delete p_decl_;

	//...

	delete p_opt1->ppl;
	delete p_opt1;
	delete p_l->ppl;
	delete p_l;
	delete p_l__->ppl;
	delete p_l__;

	//...

	delete p_v->ppl;
	delete p_v;
	delete p_v_->ppl;
	delete p_v_;
	delete p_opt2->ppl;
	delete p_opt2;

	//...

	delete p_params->ppl;
	delete p_params;
	delete p_params__->ppl;
	delete p_params__;
	delete p_tail->ppl;
	delete p_tail;
	delete p_optexpr1->ppl;
	delete p_optexpr1;

	//...

	delete p_else->ppl;
	delete p_else;
	delete p_stmts->ppl;
	delete p_stmts;
	delete p_optexpr2->ppl;
	delete p_optexpr2;
	delete p_optexpr3->ppl;
	delete p_optexpr3;

	//...

	delete p_expr_->ppl;
	delete p_expr_;
	delete p_e2_->ppl;
	delete p_e2_;
	delete p_e3_->ppl;
	delete p_e3_;
	delete p_e4_->ppl;
	delete p_e4_;
	delete p_e5_->ppl;
	delete p_e5_;
	delete p_e6_->ppl;
	delete p_e6_;
	delete p_e7_->ppl;
	delete p_e7_;
	delete p_e8_->ppl;
	delete p_e8_;
	delete p_e9_->ppl;
	delete p_e9_;
	delete p_e10_->ppl;
	delete p_e10_;
	delete p_e11_->ppl;
	delete p_e11_;
	delete p_e12_->ppl;
	delete p_e12_;

	//...

	delete p_t1->ppl;
	delete p_t1;
	delete p_t2->ppl;
	delete p_t2;
	delete p_t3->ppl;
	delete p_t3;
	delete p_t4->ppl;
	delete p_t4;
	delete p_t5->ppl;
	delete p_t5;

	//...

	delete p_args->ppl;
	delete p_args;
	delete p_args__->ppl;
	delete p_args__;

	//...

	delete p_loc_->ppl;
	delete p_loc_;
}
void NonTerminalDef::AddProduce()
{
	set<int> first_set;

	//...

	//options->option options : {void} U first(B)
	first_set.insert(Terminal::p_void->Tag());

	first_set.insert(Terminal::p_bool->Tag());
	first_set.insert(Terminal::p_char->Tag());
	first_set.insert(Terminal::p_short->Tag());
	first_set.insert(Terminal::p_int->Tag());
	first_set.insert(Terminal::p_float->Tag());

	first_set.insert(Terminal::p_double->Tag());
	p_options->ppl->push_back(make_pair(Produce::p_p_options1,first_set));

	//options->¦Å : {¦Å}
	first_set.clear();
	p_options->ppl->push_back(make_pair(Produce::p_p_options2,first_set));

	//...

	//decls->decl decls : first(B)
	first_set.clear();
	first_set.insert(Terminal::p_bool->Tag());
	first_set.insert(Terminal::p_char->Tag());
	first_set.insert(Terminal::p_short->Tag());
	first_set.insert(Terminal::p_int->Tag());
	first_set.insert(Terminal::p_float->Tag());

	first_set.insert(Terminal::p_double->Tag());
	p_decls->ppl->push_back(make_pair(Produce::p_p_decls1,first_set));

	//decls->¦Å : {¦Å}
	first_set.clear();
	p_decls->ppl->push_back(make_pair(Produce::p_p_decls2,first_set));

	//decl'->A : {[}
	first_set.clear();
	first_set.insert(Terminal::p_l_s_bracket->Tag());
	p_decl_->ppl->push_back(make_pair(Produce::p_p_decl_1,first_set));

	//decl'->V : {=,',',¦Å}
	first_set.clear();
	p_decl_->ppl->push_back(make_pair(Produce::p_p_decl_2,first_set));

	//...

	//Opt1->={L} : {=}
	first_set.clear();
	first_set.insert(Terminal::p_assign->Tag());
	p_opt1->ppl->push_back(make_pair(Produce::p_p_opt1A,first_set));;

	//Opt1->¦Å : {¦Å}
	first_set.clear();
	p_opt1->ppl->push_back(make_pair(Produce::p_p_opt1B,first_set));;

	//L->L' : first(e1)
	first_set.clear();
	first_set.insert(Terminal::p_b_not->Tag());
	first_set.insert(Terminal::p_log_not->Tag());
	first_set.insert(Terminal::p_add->Tag());
	first_set.insert(Terminal::p_sub->Tag());
	first_set.insert(Terminal::p_true->Tag());

	first_set.insert(Terminal::p_false->Tag());
	first_set.insert(Terminal::p_ascii->Tag());
	first_set.insert(Terminal::p_number->Tag());
	first_set.insert(Terminal::p_real->Tag());
	first_set.insert(Terminal::p_plus_plus->Tag());

	first_set.insert(Terminal::p_minus_minus->Tag());
	first_set.insert(Terminal::p_l_bracket->Tag());
	first_set.insert(Terminal::p_id->Tag());
	p_l->ppl->push_back(make_pair(Produce::p_p_l1,first_set));

	//L->¦Å : {¦Å} 
	first_set.clear();
	p_l->ppl->push_back(make_pair(Produce::p_p_l2,first_set));

	//L"->,L' : {,}
	first_set.clear();
	first_set.insert(Terminal::p_comma->Tag());
	p_l__->ppl->push_back(make_pair(Produce::p_p_l__1,first_set));

	//L"->¦Å : {¦Å}
	first_set.clear();
	p_l__->ppl->push_back(make_pair(Produce::p_p_l__2,first_set));

	//...

	//V->Opt2 V' : {=,',',¦Å}
	first_set.clear();
	p_v->ppl->push_back(make_pair(Produce::p_p_v,first_set));

	//V'->,id Opt2 V' : {','}
	first_set.clear();
	first_set.insert(Terminal::p_comma->Tag());
	p_v_->ppl->push_back(make_pair(Produce::p_p_v_1,first_set));

	//V'->¦Å : {¦Å}
	first_set.clear();
	p_v_->ppl->push_back(make_pair(Produce::p_p_v_2,first_set));

	//Opt2->=e1 : {=}
	first_set.clear();
	first_set.insert(Terminal::p_assign->Tag());
	p_opt2->ppl->push_back(make_pair(Produce::p_p_opt2A,first_set));

	//Opt2->¦Å : {¦Å}
	first_set.clear();
	p_opt2->ppl->push_back(make_pair(Produce::p_p_opt2B,first_set));

	//...

	//params->params' : first(B)
	first_set.clear();
	first_set.insert(Terminal::p_bool->Tag());
	first_set.insert(Terminal::p_char->Tag());
	first_set.insert(Terminal::p_short->Tag());
	first_set.insert(Terminal::p_int->Tag());
	first_set.insert(Terminal::p_float->Tag());

	first_set.insert(Terminal::p_double->Tag());
	p_params->ppl->push_back(make_pair(Produce::p_p_params1,first_set));

	//params->¦Å : {¦Å}
	first_set.clear();
	p_params->ppl->push_back(make_pair(Produce::p_p_params2,first_set));

	//params"->,params' : {,}
	first_set.clear();
	first_set.insert(Terminal::p_comma->Tag());
	p_params__->ppl->push_back(make_pair(Produce::p_p_params__1,first_set));

	//params"->¦Å : {¦Å}
	first_set.clear();
	p_params__->ppl->push_back(make_pair(Produce::p_p_params__2,first_set));

	//tail->[optexpr1] : {[}
	first_set.clear();
	first_set.insert(Terminal::p_l_s_bracket->Tag());
	p_tail->ppl->push_back(make_pair(Produce::p_p_tail1,first_set));

	//tail->¦Å : {¦Å}
	first_set.clear();
	p_tail->ppl->push_back(make_pair(Produce::p_p_tail2,first_set));

	//optexpr1->expr : first(expr)
	first_set.clear();
	first_set.insert(Terminal::p_b_not->Tag());
	first_set.insert(Terminal::p_log_not->Tag());
	first_set.insert(Terminal::p_add->Tag());
	first_set.insert(Terminal::p_sub->Tag());
	first_set.insert(Terminal::p_true->Tag());

	first_set.insert(Terminal::p_false->Tag());
	first_set.insert(Terminal::p_ascii->Tag());
	first_set.insert(Terminal::p_number->Tag());
	first_set.insert(Terminal::p_real->Tag());
	first_set.insert(Terminal::p_plus_plus->Tag());

	first_set.insert(Terminal::p_minus_minus->Tag());
	first_set.insert(Terminal::p_l_bracket->Tag());
	first_set.insert(Terminal::p_id->Tag());
	p_optexpr1->ppl->push_back(make_pair(Produce::p_p_optexpr1A,first_set));

	//optexpr1->¦Å : {¦Å}
	first_set.clear();
	p_optexpr1->ppl->push_back(make_pair(Produce::p_p_optexpr1B,first_set));

	//...

	//E->else stmt : {else}
	first_set.clear();
	first_set.insert(Terminal::p_else->Tag());
	p_else->ppl->push_back(make_pair(Produce::p_p_else1,first_set));

	//E->¦Å : {¦Å}
	first_set.clear();
	p_else->ppl->push_back(make_pair(Produce::p_p_else2,first_set));

	//stmts->stmt stmts : first(stmt)
	first_set.clear();
	first_set.insert(Terminal::p_semicolon->Tag());
	first_set.insert(Terminal::p_l_f_bracket->Tag());

	first_set.insert(Terminal::p_b_not->Tag());
	first_set.insert(Terminal::p_log_not->Tag());
	first_set.insert(Terminal::p_add->Tag());
	first_set.insert(Terminal::p_sub->Tag());
	first_set.insert(Terminal::p_true->Tag());

	first_set.insert(Terminal::p_false->Tag());
	first_set.insert(Terminal::p_ascii->Tag());
	first_set.insert(Terminal::p_number->Tag());
	first_set.insert(Terminal::p_real->Tag());
	first_set.insert(Terminal::p_plus_plus->Tag());

	first_set.insert(Terminal::p_minus_minus->Tag());
	first_set.insert(Terminal::p_l_bracket->Tag());
	first_set.insert(Terminal::p_id->Tag());

	first_set.insert(Terminal::p_if->Tag());
	first_set.insert(Terminal::p_while->Tag());	
	first_set.insert(Terminal::p_do->Tag());
	first_set.insert(Terminal::p_break->Tag());
	first_set.insert(Terminal::p_continue->Tag());	

	first_set.insert(Terminal::p_return->Tag());
	first_set.insert(Terminal::p_for->Tag());
	first_set.insert(Terminal::p_switch->Tag());	
	first_set.insert(Terminal::p_case->Tag());
	first_set.insert(Terminal::p_default->Tag());
	p_stmts->ppl->push_back(make_pair(Produce::p_p_stmts1,first_set));

	//stmts->¦Å : {¦Å}
	first_set.clear();
	p_stmts->ppl->push_back(make_pair(Produce::p_p_stmts2,first_set));

	//optexpr2->expr : first(expr)
	first_set.clear();
	first_set.insert(Terminal::p_b_not->Tag());
	first_set.insert(Terminal::p_log_not->Tag());
	first_set.insert(Terminal::p_add->Tag());
	first_set.insert(Terminal::p_sub->Tag());
	first_set.insert(Terminal::p_true->Tag());

	first_set.insert(Terminal::p_false->Tag());
	first_set.insert(Terminal::p_ascii->Tag());
	first_set.insert(Terminal::p_number->Tag());
	first_set.insert(Terminal::p_real->Tag());
	first_set.insert(Terminal::p_plus_plus->Tag());

	first_set.insert(Terminal::p_minus_minus->Tag());
	first_set.insert(Terminal::p_l_bracket->Tag());
	first_set.insert(Terminal::p_id->Tag());
	p_optexpr2->ppl->push_back(make_pair(Produce::p_p_optexpr2A,first_set));

	//optexpr2->¦Å : {¦Å}
	first_set.clear();
	p_optexpr2->ppl->push_back(make_pair(Produce::p_p_optexpr2B,first_set));

	//optexpr3->expr : first(expr)
	first_set.clear();
	first_set.insert(Terminal::p_b_not->Tag());
	first_set.insert(Terminal::p_log_not->Tag());
	first_set.insert(Terminal::p_add->Tag());
	first_set.insert(Terminal::p_sub->Tag());
	first_set.insert(Terminal::p_true->Tag());

	first_set.insert(Terminal::p_false->Tag());
	first_set.insert(Terminal::p_ascii->Tag());
	first_set.insert(Terminal::p_number->Tag());
	first_set.insert(Terminal::p_real->Tag());
	first_set.insert(Terminal::p_plus_plus->Tag());

	first_set.insert(Terminal::p_minus_minus->Tag());
	first_set.insert(Terminal::p_l_bracket->Tag());
	first_set.insert(Terminal::p_id->Tag());
	p_optexpr3->ppl->push_back(make_pair(Produce::p_p_optexpr3A,first_set));

	//optexpr3->¦Å : {¦Å}
	first_set.clear();
	p_optexpr3->ppl->push_back(make_pair(Produce::p_p_optexpr3B,first_set));

	//...

	//expr'->,e1 expr' ; {,}
	first_set.clear();
	first_set.insert(Terminal::p_comma->Tag());
	p_expr_->ppl->push_back(make_pair(Produce::p_p_expr_1,first_set));

	//expr'->¦Å : {¦Å}
	first_set.clear();
	p_expr_->ppl->push_back(make_pair(Produce::p_p_expr_2,first_set));

	//e2'->?e3:e2	: {?}
	first_set.clear();
	first_set.insert(Terminal::p_question->Tag());
	p_e2_->ppl->push_back(make_pair(Produce::p_p_e2_1,first_set));

	//e2'->¦Å : {¦Å}
	first_set.clear();
	p_e2_->ppl->push_back(make_pair(Produce::p_p_e2_2,first_set));

	//e3'->||e4 e3' : {||}
	first_set.clear();
	first_set.insert(Terminal::p_log_or->Tag());
	p_e3_->ppl->push_back(make_pair(Produce::p_p_e3_1,first_set));

	//e3'->¦Å : {¦Å}
	first_set.clear();
	p_e3_->ppl->push_back(make_pair(Produce::p_p_e3_2,first_set));

	//e4'->&&e5 e4' : {&&}
	first_set.clear();
	first_set.insert(Terminal::p_log_and->Tag());
	p_e4_->ppl->push_back(make_pair(Produce::p_p_e4_1,first_set));

	//e4'->¦Å : {¦Å}
	first_set.clear();
	p_e4_->ppl->push_back(make_pair(Produce::p_p_e4_2,first_set));

	//e5'->|e6 e5' : {|}
	first_set.clear();
	first_set.insert(Terminal::p_b_or->Tag());
	p_e5_->ppl->push_back(make_pair(Produce::p_p_e5_1,first_set));

	//e5'->¦Å : {¦Å}
	first_set.clear();
	p_e5_->ppl->push_back(make_pair(Produce::p_p_e5_2,first_set));

	//e6'->^e7 e6' : {^}
	first_set.clear();
	first_set.insert(Terminal::p_b_xor->Tag());
	p_e6_->ppl->push_back(make_pair(Produce::p_p_e6_1,first_set));

	//e6'->¦Å : {¦Å}
	first_set.clear();
	p_e6_->ppl->push_back(make_pair(Produce::p_p_e6_2,first_set));

	//e7'->&e8 e7' : {&}
	first_set.clear();
	first_set.insert(Terminal::p_b_and->Tag());
	p_e7_->ppl->push_back(make_pair(Produce::p_p_e7_1,first_set));

	//e7'->¦Å : {¦Å}
	first_set.clear();
	p_e7_->ppl->push_back(make_pair(Produce::p_p_e7_2,first_set));

	//e8'->==e9 e8' : {==}
	first_set.clear();
	first_set.insert(Terminal::p_eq->Tag());
	p_e8_->ppl->push_back(make_pair(Produce::p_p_e8_1,first_set));

	//e8'->!=e9 e8' : {!=}
	first_set.clear();
	first_set.insert(Terminal::p_ne->Tag());
	p_e8_->ppl->push_back(make_pair(Produce::p_p_e8_2,first_set));

	//e8'->¦Å : {¦Å}
	first_set.clear();
	p_e8_->ppl->push_back(make_pair(Produce::p_p_e8_3,first_set));

	//e9'-><e10 e9' : {<}
	first_set.clear();
	first_set.insert(Terminal::p_less->Tag());
	p_e9_->ppl->push_back(make_pair(Produce::p_p_e9_1,first_set));

	//e9'-><=e10 e9' : {<=}
	first_set.clear();
	first_set.insert(Terminal::p_le->Tag());
	p_e9_->ppl->push_back(make_pair(Produce::p_p_e9_2,first_set));

	//e9'->>e10 e9' : {>}
	first_set.clear();
	first_set.insert(Terminal::p_greater->Tag());
	p_e9_->ppl->push_back(make_pair(Produce::p_p_e9_3,first_set));

	//e9'->>=e10 e9' : {>=}
	first_set.clear();
	first_set.insert(Terminal::p_ge->Tag());
	p_e9_->ppl->push_back(make_pair(Produce::p_p_e9_4,first_set));

	//e9'->¦Å : {¦Å}
	first_set.clear();
	p_e9_->ppl->push_back(make_pair(Produce::p_p_e9_5,first_set)); 

	//e10'-><<e11 e10' : {<<}
	first_set.clear();
	first_set.insert(Terminal::p_l_sht->Tag());
	p_e10_->ppl->push_back(make_pair(Produce::p_p_e10_1,first_set));

	//e10'->>>e11 e10' : {>>}
	first_set.clear();
	first_set.insert(Terminal::p_r_sht->Tag());
	p_e10_->ppl->push_back(make_pair(Produce::p_p_e10_2,first_set));

	//e10'->¦Å : {¦Å}
	first_set.clear();
	p_e10_->ppl->push_back(make_pair(Produce::p_p_e10_3,first_set));

	//e11'->+e12 e11' : {+}
	first_set.clear();
	first_set.insert(Terminal::p_add->Tag());
	p_e11_->ppl->push_back(make_pair(Produce::p_p_e11_1,first_set));

	//e11'->-e12 e11' : {-}
	first_set.clear();
	first_set.insert(Terminal::p_sub->Tag());
	p_e11_->ppl->push_back(make_pair(Produce::p_p_e11_2,first_set));

	//e11'->¦Å : {¦Å}
	first_set.clear();
	p_e11_->ppl->push_back(make_pair(Produce::p_p_e11_3,first_set));

	//e12'->*e13 e12' : {*}
	first_set.clear();
	first_set.insert(Terminal::p_mul->Tag());
	p_e12_->ppl->push_back(make_pair(Produce::p_p_e12_1,first_set));

	//e12'->/e13 e12' : {/}
	first_set.clear();
	first_set.insert(Terminal::p_div->Tag());
	p_e12_->ppl->push_back(make_pair(Produce::p_p_e12_2,first_set));

	//e12'->%e13 e12' : {%}
	first_set.clear();
	first_set.insert(Terminal::p_mod->Tag());
	p_e12_->ppl->push_back(make_pair(Produce::p_p_e12_3,first_set));

	//e12'->¦Å : {¦Å}
	first_set.clear();
	p_e12_->ppl->push_back(make_pair(Produce::p_p_e12_4,first_set));

	//...

	//T1->++ : {++}
	first_set.clear();
	first_set.insert(Terminal::p_plus_plus->Tag());
	p_t1->ppl->push_back(make_pair(Produce::p_p_t1A,first_set));

	//T1->-- : {--}
	first_set.clear();
	first_set.insert(Terminal::p_minus_minus->Tag());
	p_t1->ppl->push_back(make_pair(Produce::p_p_t1B,first_set));

	//T1->(args) : {(}
	first_set.clear();
	first_set.insert(Terminal::p_l_bracket->Tag());
	p_t1->ppl->push_back(make_pair(Produce::p_p_t1C,first_set));

	//T1->[expr]T2 : {[}
	first_set.clear();
	first_set.insert(Terminal::p_l_s_bracket->Tag());
	p_t1->ppl->push_back(make_pair(Produce::p_p_t1D,first_set));

	//T1->=e1 : {=}
	first_set.clear();
	first_set.insert(Terminal::p_assign->Tag());
	p_t1->ppl->push_back(make_pair(Produce::p_p_t1E,first_set));

	//T1->*=e1 : {*=}
	first_set.clear();
	first_set.insert(Terminal::p_mul_ass->Tag());
	p_t1->ppl->push_back(make_pair(Produce::p_p_t1F,first_set));

	//T1->/=e1 : {/=}
	first_set.clear();
	first_set.insert(Terminal::p_div_ass->Tag());
	p_t1->ppl->push_back(make_pair(Produce::p_p_t1G,first_set));

	//T1->%=e1 : {%=}
	first_set.clear();
	first_set.insert(Terminal::p_mod_ass->Tag());
	p_t1->ppl->push_back(make_pair(Produce::p_p_t1H,first_set));

	//T1->+=e1 : {+=}
	first_set.clear();
	first_set.insert(Terminal::p_add_ass->Tag());
	p_t1->ppl->push_back(make_pair(Produce::p_p_t1I,first_set));

	//T1->-=e1 : {-=}
	first_set.clear();
	first_set.insert(Terminal::p_sub_ass->Tag());
	p_t1->ppl->push_back(make_pair(Produce::p_p_t1J,first_set));

	//T1-><<=e1 : {<<=}
	first_set.clear();
	first_set.insert(Terminal::p_l_sht_ass->Tag());
	p_t1->ppl->push_back(make_pair(Produce::p_p_t1K,first_set));

	//T1-> >>=e1 : {>>=}
	first_set.clear();
	first_set.insert(Terminal::p_r_sht_ass->Tag());
	p_t1->ppl->push_back(make_pair(Produce::p_p_t1L,first_set));

	//T1->&=e1 : {&=}
	first_set.clear();
	first_set.insert(Terminal::p_b_and_ass->Tag());
	p_t1->ppl->push_back(make_pair(Produce::p_p_t1M,first_set));

	//T1->|=e1 : {|=}
	first_set.clear();
	first_set.insert(Terminal::p_b_or_ass->Tag());
	p_t1->ppl->push_back(make_pair(Produce::p_p_t1N,first_set));

	//T1->^=e1 : {^=}
	first_set.clear();
	first_set.insert(Terminal::p_b_xor_ass->Tag());
	p_t1->ppl->push_back(make_pair(Produce::p_p_t1O,first_set));

	//T1->e2' : {?}
	first_set.clear();
	first_set.insert(Terminal::p_question->Tag());
	p_t1->ppl->push_back(make_pair(Produce::p_p_t1P,first_set));

	//T1->e3'e2' : {||}
	first_set.clear();
	first_set.insert(Terminal::p_log_or->Tag());
	p_t1->ppl->push_back(make_pair(Produce::p_p_t1Q,first_set));

	//T1->e4'e3'e2' : {&&}
	first_set.clear();
	first_set.insert(Terminal::p_log_and->Tag());
	p_t1->ppl->push_back(make_pair(Produce::p_p_t1R,first_set));

	//T1->e5'e4'e3'e2' : {|}
	first_set.clear();
	first_set.insert(Terminal::p_b_or->Tag());
	p_t1->ppl->push_back(make_pair(Produce::p_p_t1S,first_set));

	//T1->e6'e5'e4'e3'e2' : {^}
	first_set.clear();
	first_set.insert(Terminal::p_b_xor->Tag());
	p_t1->ppl->push_back(make_pair(Produce::p_p_t1T,first_set));

	//T1->e7'e6'e5'e4'e3'e2' : {&}
	first_set.clear();
	first_set.insert(Terminal::p_b_and->Tag());
	p_t1->ppl->push_back(make_pair(Produce::p_p_t1U,first_set));

	//T1->e8'e7'e6'e5'e4'e3'e2' : {==,!=}
	first_set.clear();
	first_set.insert(Terminal::p_eq->Tag());
	first_set.insert(Terminal::p_ne->Tag());
	p_t1->ppl->push_back(make_pair(Produce::p_p_t1V,first_set));

	//T1->e9'e8'e7'e6'e5'e4'e3'e2' : {<,<=,>,>=}
	first_set.clear();
	first_set.insert(Terminal::p_less->Tag());
	first_set.insert(Terminal::p_le->Tag());
	first_set.insert(Terminal::p_greater->Tag());
	first_set.insert(Terminal::p_ge->Tag());
	p_t1->ppl->push_back(make_pair(Produce::p_p_t1W,first_set));

	//T1->e10'e9'e8'e7'e6'e5'e4'e3'e2' : {<<,>>}
	first_set.clear();
	first_set.insert(Terminal::p_l_sht->Tag());
	first_set.insert(Terminal::p_r_sht->Tag());
	p_t1->ppl->push_back(make_pair(Produce::p_p_t1X,first_set));

	//T1->e11'e10'e9'e8'e7'e6'e5'e4'e3'e2' : {+,-}
	first_set.clear();
	first_set.insert(Terminal::p_add->Tag());
	first_set.insert(Terminal::p_sub->Tag());
	p_t1->ppl->push_back(make_pair(Produce::p_p_t1Y,first_set));

	//T1->e12'e11'e10'e9'e8'e7'e6'e5'e4'e3'e2' : {*,/,%}
	first_set.clear();
	first_set.insert(Terminal::p_mul->Tag());
	first_set.insert(Terminal::p_div->Tag());
	first_set.insert(Terminal::p_mod->Tag());
	p_t1->ppl->push_back(make_pair(Produce::p_p_t1Z,first_set));

	//T1->¦Å : {¦Å}
	first_set.clear();
	p_t1->ppl->push_back(make_pair(Produce::p_p_t1A1,first_set));


	//T2->++ : {++}
	first_set.clear();
	first_set.insert(Terminal::p_plus_plus->Tag());
	p_t2->ppl->push_back(make_pair(Produce::p_p_t2A,first_set));

	//T2->-- : {--}
	first_set.clear();
	first_set.insert(Terminal::p_minus_minus->Tag());
	p_t2->ppl->push_back(make_pair(Produce::p_p_t2B,first_set));

	//T2->=e1 : {=}
	first_set.clear();
	first_set.insert(Terminal::p_assign->Tag());
	p_t2->ppl->push_back(make_pair(Produce::p_p_t2C,first_set));

	//T2->*=e1 : {*=}
	first_set.clear();
	first_set.insert(Terminal::p_mul_ass->Tag());
	p_t2->ppl->push_back(make_pair(Produce::p_p_t2D,first_set));

	//T2->/=e1 : {/=}
	first_set.clear();
	first_set.insert(Terminal::p_div_ass->Tag());
	p_t2->ppl->push_back(make_pair(Produce::p_p_t2E,first_set));

	//T2->%=e1 : {%=}
	first_set.clear();
	first_set.insert(Terminal::p_mod_ass->Tag());
	p_t2->ppl->push_back(make_pair(Produce::p_p_t2F,first_set));

	//T2->+=e1 : {+=}
	first_set.clear();
	first_set.insert(Terminal::p_add_ass->Tag());
	p_t2->ppl->push_back(make_pair(Produce::p_p_t2G,first_set));

	//T2->-=e1 : {-=}
	first_set.clear();
	first_set.insert(Terminal::p_sub_ass->Tag());
	p_t2->ppl->push_back(make_pair(Produce::p_p_t2H,first_set));

	//T2-><<=e1 : {<<=}
	first_set.clear();
	first_set.insert(Terminal::p_l_sht_ass->Tag());
	p_t2->ppl->push_back(make_pair(Produce::p_p_t2I,first_set));

	//T2-> >>=e1 : {>>=}
	first_set.clear();
	first_set.insert(Terminal::p_r_sht_ass->Tag());
	p_t2->ppl->push_back(make_pair(Produce::p_p_t2J,first_set));

	//T2->&=e1 : {&=}
	first_set.clear();
	first_set.insert(Terminal::p_b_and_ass->Tag());
	p_t2->ppl->push_back(make_pair(Produce::p_p_t2K,first_set));

	//T2->|=e1 : {|=}
	first_set.clear();
	first_set.insert(Terminal::p_b_or_ass->Tag());
	p_t2->ppl->push_back(make_pair(Produce::p_p_t2L,first_set));

	//T2->^=e1 : {^=}
	first_set.clear();
	first_set.insert(Terminal::p_b_xor_ass->Tag());
	p_t2->ppl->push_back(make_pair(Produce::p_p_t2M,first_set));

	//T2->e2' : {?}
	first_set.clear();
	first_set.insert(Terminal::p_question->Tag());
	p_t2->ppl->push_back(make_pair(Produce::p_p_t2N,first_set));

	//T2->e3'e2' : {||}
	first_set.clear();
	first_set.insert(Terminal::p_log_or->Tag());
	p_t2->ppl->push_back(make_pair(Produce::p_p_t2O,first_set));

	//T2->e4'e3'e2' : {&&}
	first_set.clear();
	first_set.insert(Terminal::p_log_and->Tag());
	p_t2->ppl->push_back(make_pair(Produce::p_p_t2P,first_set));

	//T2->e5'e4'e3'e2' : {|}
	first_set.clear();
	first_set.insert(Terminal::p_b_or->Tag());
	p_t2->ppl->push_back(make_pair(Produce::p_p_t2Q,first_set));

	//T2->e6'e5'e4'e3'e2' : {^}
	first_set.clear();
	first_set.insert(Terminal::p_b_xor->Tag());
	p_t2->ppl->push_back(make_pair(Produce::p_p_t2R,first_set));

	//T2->e7'e6'e5'e4'e3'e2' : {&}
	first_set.clear();
	first_set.insert(Terminal::p_b_and->Tag());
	p_t2->ppl->push_back(make_pair(Produce::p_p_t2S,first_set));

	//T2->e8'e7'e6'e5'e4'e3'e2' : {==,!=}
	first_set.clear();
	first_set.insert(Terminal::p_eq->Tag());
	first_set.insert(Terminal::p_ne->Tag());
	p_t2->ppl->push_back(make_pair(Produce::p_p_t2T,first_set));

	//T2->e9'e8'e7'e6'e5'e4'e3'e2' : {<,<=,>,>=}
	first_set.clear();
	first_set.insert(Terminal::p_less->Tag());
	first_set.insert(Terminal::p_le->Tag());
	first_set.insert(Terminal::p_greater->Tag());
	first_set.insert(Terminal::p_ge->Tag());
	p_t2->ppl->push_back(make_pair(Produce::p_p_t2U,first_set));

	//T2->e10'e9'e8'e7'e6'e5'e4'e3'e2' : {<<,>>}
	first_set.clear();
	first_set.insert(Terminal::p_l_sht->Tag());
	first_set.insert(Terminal::p_r_sht->Tag());
	p_t2->ppl->push_back(make_pair(Produce::p_p_t2V,first_set));

	//T2->e11'e10'e9'e8'e7'e6'e5'e4'e3'e2' : {+,-}
	first_set.clear();
	first_set.insert(Terminal::p_add->Tag());
	first_set.insert(Terminal::p_sub->Tag());
	p_t2->ppl->push_back(make_pair(Produce::p_p_t2W,first_set));

	//T2->e12'e11'e10'e9'e8'e7'e6'e5'e4'e3'e2' : {*,/,%}
	first_set.clear();
	first_set.insert(Terminal::p_mul->Tag());
	first_set.insert(Terminal::p_div->Tag());
	first_set.insert(Terminal::p_mod->Tag());
	p_t2->ppl->push_back(make_pair(Produce::p_p_t2X,first_set));

	//T2->¦Å : {¦Å}
	first_set.clear();
	p_t2->ppl->push_back(make_pair(Produce::p_p_t2Y,first_set));


	//T3->++ : {++}
	first_set.clear();
	first_set.insert(Terminal::p_plus_plus->Tag());
	p_t3->ppl->push_back(make_pair(Produce::p_p_t3A,first_set));

	//T3->-- : {--}
	first_set.clear();
	first_set.insert(Terminal::p_minus_minus->Tag());
	p_t3->ppl->push_back(make_pair(Produce::p_p_t3B,first_set));

	//T3->(args) : {(}
	first_set.clear();
	first_set.insert(Terminal::p_l_bracket->Tag());
	p_t3->ppl->push_back(make_pair(Produce::p_p_t3C,first_set));

	//T3->[expr]T4 : {[}
	first_set.clear();
	first_set.insert(Terminal::p_l_s_bracket->Tag());
	p_t3->ppl->push_back(make_pair(Produce::p_p_t3D,first_set));

	//T3->¦Å : {¦Å}
	first_set.clear();
	p_t3->ppl->push_back(make_pair(Produce::p_p_t3E,first_set));


	//T4->++ : {++}
	first_set.clear();
	first_set.insert(Terminal::p_plus_plus->Tag());
	p_t4->ppl->push_back(make_pair(Produce::p_p_t4A,first_set));

	//T4->-- : {--}
	first_set.clear();
	first_set.insert(Terminal::p_minus_minus->Tag());
	p_t4->ppl->push_back(make_pair(Produce::p_p_t4B,first_set));

	//T4->¦Å : {¦Å}
	first_set.clear();
	p_t4->ppl->push_back(make_pair(Produce::p_p_t4C,first_set));


	//T5->e2' : {?}
	first_set.clear();
	first_set.insert(Terminal::p_question->Tag());
	p_t5->ppl->push_back(make_pair(Produce::p_p_t5A,first_set));

	//T5->e3'e2' : {||}
	first_set.clear();
	first_set.insert(Terminal::p_log_or->Tag());
	p_t5->ppl->push_back(make_pair(Produce::p_p_t5B,first_set));

	//T5->e4'e3'e2' : {&&}
	first_set.clear();
	first_set.insert(Terminal::p_log_and->Tag());
	p_t5->ppl->push_back(make_pair(Produce::p_p_t5C,first_set));

	//T5->e5'e4'e3'e2' : {|}
	first_set.clear();
	first_set.insert(Terminal::p_b_or->Tag());
	p_t5->ppl->push_back(make_pair(Produce::p_p_t5D,first_set));

	//T5->e6'e5'e4'e3'e2' : {^}
	first_set.clear();
	first_set.insert(Terminal::p_b_xor->Tag());
	p_t5->ppl->push_back(make_pair(Produce::p_p_t5E,first_set));

	//T5->e7'e6'e5'e4'e3'e2' : {&}
	first_set.clear();
	first_set.insert(Terminal::p_b_and->Tag());
	p_t5->ppl->push_back(make_pair(Produce::p_p_t5F,first_set));

	//T5->e8'e7'e6'e5'e4'e3'e2' : {==,!=}
	first_set.clear();
	first_set.insert(Terminal::p_eq->Tag());
	first_set.insert(Terminal::p_ne->Tag());
	p_t5->ppl->push_back(make_pair(Produce::p_p_t5G,first_set));

	//T5->e9'e8'e7'e6'e5'e4'e3'e2' : {<,<=,>,>=}
	first_set.clear();
	first_set.insert(Terminal::p_less->Tag());
	first_set.insert(Terminal::p_le->Tag());
	first_set.insert(Terminal::p_greater->Tag());
	first_set.insert(Terminal::p_ge->Tag());
	p_t5->ppl->push_back(make_pair(Produce::p_p_t5H,first_set));

	//T5->e10'e9'e8'e7'e6'e5'e4'e3'e2' : {<<,>>}
	first_set.clear();
	first_set.insert(Terminal::p_l_sht->Tag());
	first_set.insert(Terminal::p_r_sht->Tag());
	p_t5->ppl->push_back(make_pair(Produce::p_p_t5I,first_set));

	//T5->e11'e10'e9'e8'e7'e6'e5'e4'e3'e2' : {+,-}
	first_set.clear();
	first_set.insert(Terminal::p_add->Tag());
	first_set.insert(Terminal::p_sub->Tag());
	p_t5->ppl->push_back(make_pair(Produce::p_p_t5J,first_set));

	//T5->e12'e11'e10'e9'e8'e7'e6'e5'e4'e3'e2' : {*,/,%}
	first_set.clear();
	first_set.insert(Terminal::p_mul->Tag());
	first_set.insert(Terminal::p_div->Tag());
	first_set.insert(Terminal::p_mod->Tag());
	p_t5->ppl->push_back(make_pair(Produce::p_p_t5K,first_set));

	//T5->¦Å : {¦Å}
	first_set.clear();
	p_t5->ppl->push_back(make_pair(Produce::p_p_t5L,first_set));


	//...

	//args->args' : first(e1)
	first_set.clear();
	first_set.insert(Terminal::p_b_not->Tag());
	first_set.insert(Terminal::p_log_not->Tag());
	first_set.insert(Terminal::p_add->Tag());
	first_set.insert(Terminal::p_sub->Tag());
	first_set.insert(Terminal::p_true->Tag());

	first_set.insert(Terminal::p_false->Tag());
	first_set.insert(Terminal::p_ascii->Tag());
	first_set.insert(Terminal::p_number->Tag());
	first_set.insert(Terminal::p_real->Tag());
	first_set.insert(Terminal::p_plus_plus->Tag());

	first_set.insert(Terminal::p_minus_minus->Tag());
	first_set.insert(Terminal::p_l_bracket->Tag());
	first_set.insert(Terminal::p_id->Tag());
	p_args->ppl->push_back(make_pair(Produce::p_p_args1,first_set));

	//args->¦Å : {¦Å}
	first_set.clear();
	p_args->ppl->push_back(make_pair(Produce::p_p_args2,first_set));

	//args"->,args' : {,}
	first_set.clear();
	first_set.insert(Terminal::p_comma->Tag());
	p_args__->ppl->push_back(make_pair(Produce::p_p_args__1,first_set));

	//args"->¦Å : {¦Å}
	first_set.clear();
	p_args__->ppl->push_back(make_pair(Produce::p_p_args__2,first_set));

	//...

	//loc'->[expr] : {[}
	first_set.clear();
	first_set.insert(Terminal::p_l_s_bracket->Tag());		
	p_loc_->ppl->push_back(make_pair(Produce::p_p_loc_1,first_set));

	//loc'->¦Å : {¦Å}
	first_set.clear();
	p_loc_->ppl->push_back(make_pair(Produce::p_p_loc_2,first_set));
}