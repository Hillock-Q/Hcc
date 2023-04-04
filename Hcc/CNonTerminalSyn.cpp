#include "CNonTerminalSyn.h"
#include "CTag.h"
#include "CHillock.h"

NonTerminalSyn::n_syn_pt NonTerminalSyn::p_program=0;

NonTerminalSyn::n_syn_pt NonTerminalSyn::p_option=0;
NonTerminalSyn::n_syn_pt NonTerminalSyn::p_option_=0;

NonTerminalSyn::n_syn_pt NonTerminalSyn::p_decl=0;

NonTerminalSyn::n_syn_pt NonTerminalSyn::p_b=0;

NonTerminalSyn::n_syn_pt NonTerminalSyn::p_a=0;
NonTerminalSyn::n_syn_pt NonTerminalSyn::p_l_=0;

NonTerminalSyn::n_syn_pt NonTerminalSyn::p_f=0;
NonTerminalSyn::n_syn_pt NonTerminalSyn::p_params_=0;
NonTerminalSyn::n_syn_pt NonTerminalSyn::p_param=0;

NonTerminalSyn::n_syn_pt NonTerminalSyn::p_size=0;

NonTerminalSyn::n_syn_pt NonTerminalSyn::p_stmt=0;
NonTerminalSyn::n_syn_pt NonTerminalSyn::p_label=0;

NonTerminalSyn::n_syn_pt NonTerminalSyn::p_expr=0;
NonTerminalSyn::n_syn_pt NonTerminalSyn::p_e1=0;
NonTerminalSyn::n_syn_pt NonTerminalSyn::p_e2=0;
NonTerminalSyn::n_syn_pt NonTerminalSyn::p_e3=0;
NonTerminalSyn::n_syn_pt NonTerminalSyn::p_e4=0;
NonTerminalSyn::n_syn_pt NonTerminalSyn::p_e5=0;
NonTerminalSyn::n_syn_pt NonTerminalSyn::p_e6=0;
NonTerminalSyn::n_syn_pt NonTerminalSyn::p_e7=0;
NonTerminalSyn::n_syn_pt NonTerminalSyn::p_e8=0;
NonTerminalSyn::n_syn_pt NonTerminalSyn::p_e9=0;
NonTerminalSyn::n_syn_pt NonTerminalSyn::p_e10=0;
NonTerminalSyn::n_syn_pt NonTerminalSyn::p_e11=0;
NonTerminalSyn::n_syn_pt NonTerminalSyn::p_e12=0;
NonTerminalSyn::n_syn_pt NonTerminalSyn::p_e13=0;
NonTerminalSyn::n_syn_pt NonTerminalSyn::p_e14=0;

NonTerminalSyn::n_syn_pt NonTerminalSyn::p_args_=0;
NonTerminalSyn::n_syn_pt NonTerminalSyn::p_arg=0;

NonTerminalSyn::n_syn_pt NonTerminalSyn::p_loc=0;

void NonTerminalSyn::Generate()
{
	//...

	p_program	=	new NonTerminalSyn(Compiler::_program);
	p_program->pstr_err_list=new list<string>();
	p_program->psyn_set=new set<int>();
	p_program->ppl=new produce_list();
	p_program->Append(string("“"));
	p_program->Append(string());
	p_program->Append(string("”之前缺少类型名或主函数名。"));

	//...

	p_option	=	new NonTerminalSyn(Compiler::_option);
	p_option->pstr_err_list=new list<string>();
	p_option->psyn_set=new set<int>();
	p_option->ppl=new produce_list();
	p_option->Append(string("“"));
	p_option->Append(string());
	p_option->Append(string("”之前缺少类型名。"));

	p_option_	=	new NonTerminalSyn(Compiler::_option_);
	p_option_->pstr_err_list=new list<string>();
	p_option_->psyn_set=new set<int>();
	p_option_->ppl=new produce_list();
	p_option_->Append(string("“"));
	p_option_->Append(string());
	p_option_->Append(string("”之前可能缺少这些符号：“(”,“[”,“=”,“，”,“；”。"));

	//...

	p_decl		=	new NonTerminalSyn(Compiler::_decl);
	p_decl->pstr_err_list=new list<string>();
	p_decl->psyn_set=new set<int>();
	p_decl->ppl=new produce_list();
	p_decl->Append(string("“"));
	p_decl->Append(string());
	p_decl->Append(string("”之前缺少算术类型名。"));

	//...

	p_b			=	new NonTerminalSyn(Compiler::_b);
	p_b->pstr_err_list=new list<string>();
	p_b->psyn_set=new set<int>();
	p_b->ppl=new produce_list();
	p_b->Append(string("“"));
	p_b->Append(string());
	p_b->Append(string("”之前缺少算术类型名。"));

	//...

	p_a			=	new NonTerminalSyn(Compiler::_a);
	p_a->pstr_err_list=new list<string>();
	p_a->psyn_set=new set<int>();
	p_a->ppl=new produce_list();
	p_a->Append(string("“"));
	p_a->Append(string());
	p_a->Append(string("”之前缺少“]”。"));

	p_l_		=	new NonTerminalSyn(Compiler::_l_);
	p_l_->pstr_err_list=new list<string>();
	p_l_->psyn_set=new set<int>();
	p_l_->ppl=new produce_list();
	p_l_->Append(string("“"));
	p_l_->Append(string());
	p_l_->Append(string("”之前缺少整型常量。"));

	//...

	p_f			=	new NonTerminalSyn(Compiler::_f);
	p_f->pstr_err_list=new list<string>();
	p_f->psyn_set=new set<int>();
	p_f->ppl=new produce_list();
	p_f->Append(string("“"));
	p_f->Append(string());
	p_f->Append(string("”之前缺少“(”。"));

	p_params_	=	new NonTerminalSyn(Compiler::_params_);
	p_params_->pstr_err_list=new list<string>();
	p_params_->psyn_set=new set<int>();
	p_params_->ppl=new produce_list();
	p_params_->Append(string("“"));
	p_params_->Append(string());
	p_params_->Append(string("”之前缺少算术类型名。"));

	p_param		=	new NonTerminalSyn(Compiler::_param);
	p_param->pstr_err_list=new list<string>();
	p_param->psyn_set=new set<int>();
	p_param->ppl=new produce_list();
	p_param->Append(string("“"));
	p_param->Append(string());
	p_param->Append(string("”之前缺少算术类型名。"));

	//...

	p_size		=	new NonTerminalSyn(Compiler::_size);
	p_size->pstr_err_list=new list<string>();
	p_size->psyn_set=new set<int>();
	p_size->ppl=new produce_list();
	p_size->Append(string("数组大小以非法单词“"));
	p_size->Append(string());
	p_size->Append(string("”开头。"));

	//...

	p_stmt		=	new NonTerminalSyn(Compiler::_stmt);
	p_stmt->pstr_err_list=new list<string>();
	p_stmt->psyn_set=new set<int>();
	p_stmt->ppl=new produce_list();
	p_stmt->Append(string("“"));
	p_stmt->Append(string());
	p_stmt->Append(string("”之前缺少“；”或“}”或语句开头关键字，或者是表达式以非法单词“"));
	p_stmt->Append(string());
	p_stmt->Append(string("”开头。"));

	p_label		=	new NonTerminalSyn(Compiler::_label);
	p_label->pstr_err_list=new list<string>();
	p_label->psyn_set=new set<int>();
	p_label->ppl=new produce_list();
	p_label->Append(string("case后面的标号以非法单词“"));
	p_label->Append(string());
	p_label->Append(string("”开头。"));

	//...

	p_expr		=	new NonTerminalSyn(Compiler::_expr);
	p_expr->pstr_err_list=new list<string>();
	p_expr->psyn_set=new set<int>();
	p_expr->ppl=new produce_list();
	p_expr->Append(string("表达式expr以非法单词“"));
	p_expr->Append(string());
	p_expr->Append(string("”开头。"));

	p_e1		=	new NonTerminalSyn(Compiler::_e1);
	p_e1->pstr_err_list=new list<string>();
	p_e1->psyn_set=new set<int>();
	p_e1->ppl=new produce_list();
	p_e1->Append(string("表达式e1以非法单词“"));
	p_e1->Append(string());
	p_e1->Append(string("”开头。"));

	p_e2		=	new NonTerminalSyn(Compiler::_e2);
	p_e2->pstr_err_list=new list<string>();
	p_e2->psyn_set=new set<int>();
	p_e2->ppl=new produce_list();
	p_e2->Append(string("表达式e2以非法单词“"));
	p_e2->Append(string());
	p_e2->Append(string("”开头。"));

	p_e3		=	new NonTerminalSyn(Compiler::_e3);
	p_e3->pstr_err_list=new list<string>();
	p_e3->psyn_set=new set<int>();
	p_e3->ppl=new produce_list();
	p_e3->Append(string("表达式e3以非法单词“"));
	p_e3->Append(string());
	p_e3->Append(string("”开头。"));

	p_e4		=	new NonTerminalSyn(Compiler::_e4);
	p_e4->pstr_err_list=new list<string>();
	p_e4->psyn_set=new set<int>();
	p_e4->ppl=new produce_list();
	p_e4->Append(string("表达式e4以非法单词“"));
	p_e4->Append(string());
	p_e4->Append(string("”开头。"));

	p_e5		=	new NonTerminalSyn(Compiler::_e5);
	p_e5->pstr_err_list=new list<string>();
	p_e5->psyn_set=new set<int>();
	p_e5->ppl=new produce_list();
	p_e5->Append(string("表达式e5以非法单词“"));
	p_e5->Append(string());
	p_e5->Append(string("”开头。"));

	p_e6		=	new NonTerminalSyn(Compiler::_e6);
	p_e6->pstr_err_list=new list<string>();
	p_e6->psyn_set=new set<int>();
	p_e6->ppl=new produce_list();
	p_e6->Append(string("表达式e6以非法单词“"));
	p_e6->Append(string());
	p_e6->Append(string("”开头。"));

	p_e7		=	new NonTerminalSyn(Compiler::_e7);
	p_e7->pstr_err_list=new list<string>();
	p_e7->psyn_set=new set<int>();
	p_e7->ppl=new produce_list();
	p_e7->Append(string("表达式e7以非法单词“"));
	p_e7->Append(string());
	p_e7->Append(string("”开头。"));

	p_e8		=	new NonTerminalSyn(Compiler::_e8);
	p_e8->pstr_err_list=new list<string>();
	p_e8->psyn_set=new set<int>();
	p_e8->ppl=new produce_list();
	p_e8->Append(string("表达式e8以非法单词“"));
	p_e8->Append(string());
	p_e8->Append(string("”开头。"));

	p_e9		=	new NonTerminalSyn(Compiler::_e9);
	p_e9->pstr_err_list=new list<string>();
	p_e9->psyn_set=new set<int>();
	p_e9->ppl=new produce_list();
	p_e9->Append(string("表达式e9以非法单词“"));
	p_e9->Append(string());
	p_e9->Append(string("”开头。"));

	p_e10		=	new NonTerminalSyn(Compiler::_e10);
	p_e10->pstr_err_list=new list<string>();
	p_e10->psyn_set=new set<int>();
	p_e10->ppl=new produce_list();
	p_e10->Append(string("表达式e10以非法单词“"));
	p_e10->Append(string());
	p_e10->Append(string("”开头。"));

	p_e11		=	new NonTerminalSyn(Compiler::_e11);
	p_e11->pstr_err_list=new list<string>();
	p_e11->psyn_set=new set<int>();
	p_e11->ppl=new produce_list();
	p_e11->Append(string("表达式e11以非法单词“"));
	p_e11->Append(string());
	p_e11->Append(string("”开头。"));

	p_e12		=	new NonTerminalSyn(Compiler::_e12);
	p_e12->pstr_err_list=new list<string>();
	p_e12->psyn_set=new set<int>();
	p_e12->ppl=new produce_list();
	p_e12->Append(string("表达式e12以非法单词“"));
	p_e12->Append(string());
	p_e12->Append(string("”开头。"));

	p_e13		=	new NonTerminalSyn(Compiler::_e13);
	p_e13->pstr_err_list=new list<string>();
	p_e13->psyn_set=new set<int>();
	p_e13->ppl=new produce_list();
	p_e13->Append(string("表达式e13以非法单词“"));
	p_e13->Append(string());
	p_e13->Append(string("”开头。"));

	p_e14		=	new NonTerminalSyn(Compiler::_e14);
	p_e14->pstr_err_list=new list<string>();
	p_e14->psyn_set=new set<int>();
	p_e14->ppl=new produce_list();
	p_e14->Append(string("表达式e14以非法单词“"));
	p_e14->Append(string());
	p_e14->Append(string("”开头。"));

	//...

	p_args_		=	new NonTerminalSyn(Compiler::_args_);
	p_args_->pstr_err_list=new list<string>();
	p_args_->psyn_set=new set<int>();
	p_args_->ppl=new produce_list();
	p_args_->Append(string("函数实参表达式以非法单词“"));
	p_args_->Append(string());
	p_args_->Append(string("”开头。"));

	p_arg		=	new NonTerminalSyn(Compiler::_arg);
	p_arg->pstr_err_list=new list<string>();
	p_arg->psyn_set=new set<int>();
	p_arg->ppl=new produce_list();
	p_arg->Append(string("函数实参表达式以非法单词“"));
	p_arg->Append(string());
	p_arg->Append(string("”开头。"));

	//...

	p_loc		=	new NonTerminalSyn(Compiler::_loc);
	p_loc->pstr_err_list=new list<string>();
	p_loc->psyn_set=new set<int>();
	p_loc->ppl=new produce_list();
	p_loc->Append(string("L-Value要求以变量名或数组名开头，而不应该以单词“"));
	p_loc->Append(string());
	p_loc->Append(string("”开头。"));
}
string NonTerminalSyn::getError(Token const *ptoken)const
{
	string ret;

	for(list<string>::const_iterator citor=pstr_err_list->begin();citor!=pstr_err_list->end();++citor)
	{
		if(citor->empty())
			ret+=ptoken->toString();
		else
			ret+=*citor;
	}

	return ret;
}
void NonTerminalSyn::Destroy()
{
	//首先清空同步字符集

	//...

	p_program->psyn_set->clear();

	//...

	p_option->psyn_set->clear();
	p_option_->psyn_set->clear();

	//...

	p_decl->psyn_set->clear();

	//...

	p_b->psyn_set->clear();

	//...

	p_a->psyn_set->clear();
	p_l_->psyn_set->clear();

	//...

	p_f->psyn_set->clear();
	p_params_->psyn_set->clear();
	p_param->psyn_set->clear();

	//...

	p_size->psyn_set->clear();

	//...

	p_stmt->psyn_set->clear();

	p_label->psyn_set->clear();

	//...

	p_expr->psyn_set->clear();
	p_e1->psyn_set->clear();
	p_e2->psyn_set->clear();
	p_e3->psyn_set->clear();
	p_e4->psyn_set->clear();
	p_e5->psyn_set->clear();
	p_e6->psyn_set->clear();
	p_e7->psyn_set->clear();
	p_e8->psyn_set->clear();
	p_e9->psyn_set->clear();
	p_e10->psyn_set->clear();
	p_e11->psyn_set->clear();
	p_e12->psyn_set->clear();
	p_e13->psyn_set->clear();
	p_e14->psyn_set->clear();

	//...

	p_args_->psyn_set->clear();
	p_arg->psyn_set->clear();

	//...

	p_loc->psyn_set->clear();

	//销毁非终结符

	//...

	delete p_program->ppl;
	delete p_program->pstr_err_list;
	delete p_program->psyn_set;
	delete p_program;

	//...

	delete p_option->ppl;
	delete p_option->pstr_err_list;
	delete p_option->psyn_set;
	delete p_option;
	delete p_option_->ppl;
	delete p_option_->pstr_err_list;
	delete p_option_->psyn_set;
	delete p_option_;

	//...

	delete p_decl->ppl;
	delete p_decl->pstr_err_list;
	delete p_decl->psyn_set;
	delete p_decl;

	//...

	delete p_b->ppl;
	delete p_b->pstr_err_list;
	delete p_b->psyn_set;
	delete p_b;

	//...

	delete p_a->ppl;
	delete p_a->pstr_err_list;
	delete p_a->psyn_set;
	delete p_a;
	delete p_l_->ppl;
	delete p_l_->pstr_err_list;
	delete p_l_->psyn_set;
	delete p_l_;

	//...

	delete p_f->ppl;
	delete p_f->pstr_err_list;
	delete p_f->psyn_set;
	delete p_f;
	delete p_params_->ppl;
	delete p_params_->pstr_err_list;
	delete p_params_->psyn_set;
	delete p_params_;
	delete p_param->ppl;
	delete p_param->pstr_err_list;
	delete p_param->psyn_set;
	delete p_param;

	//...
	delete p_size->ppl;
	delete p_size->pstr_err_list;
	delete p_size->psyn_set;
	delete p_size;

	//...

	delete p_stmt->ppl;
	delete p_stmt->pstr_err_list;
	delete p_stmt->psyn_set;
	delete p_stmt;
	delete p_label->ppl;
	delete p_label->pstr_err_list;
	delete p_label->psyn_set;
	delete p_label;

	//...

	delete p_expr->ppl;
	delete p_expr->pstr_err_list;
	delete p_expr->psyn_set;
	delete p_expr;
	delete p_e1->ppl;
	delete p_e1->pstr_err_list;
	delete p_e1->psyn_set;
	delete p_e1;
	delete p_e2->ppl;
	delete p_e2->pstr_err_list;
	delete p_e2->psyn_set;
	delete p_e2;
	delete p_e3->ppl;
	delete p_e3->pstr_err_list;
	delete p_e3->psyn_set;
	delete p_e3;
	delete p_e4->ppl;
	delete p_e4->pstr_err_list;
	delete p_e4->psyn_set;
	delete p_e4;
	delete p_e5->ppl;
	delete p_e5->pstr_err_list;
	delete p_e5->psyn_set;
	delete p_e5;
	delete p_e6->ppl;
	delete p_e6->pstr_err_list;
	delete p_e6->psyn_set;
	delete p_e6;
	delete p_e7->ppl;
	delete p_e7->pstr_err_list;
	delete p_e7->psyn_set;
	delete p_e7;
	delete p_e8->ppl;
	delete p_e8->pstr_err_list;
	delete p_e8->psyn_set;
	delete p_e8;
	delete p_e9->ppl;
	delete p_e9->pstr_err_list;
	delete p_e9->psyn_set;
	delete p_e9;
	delete p_e10->ppl;
	delete p_e10->pstr_err_list;
	delete p_e10->psyn_set;
	delete p_e10;
	delete p_e11->ppl;
	delete p_e11->pstr_err_list;
	delete p_e11->psyn_set;
	delete p_e11;
	delete p_e12->ppl;
	delete p_e12->pstr_err_list;
	delete p_e12->psyn_set;
	delete p_e12;
	delete p_e13->ppl;
	delete p_e13->pstr_err_list;
	delete p_e13->psyn_set;
	delete p_e13;
	delete p_e14->ppl;
	delete p_e14->pstr_err_list;
	delete p_e14->psyn_set;
	delete p_e14;

	//...

	delete p_args_->ppl;
	delete p_args_->pstr_err_list;
	delete p_args_->psyn_set;
	delete p_args_;
	delete p_arg->ppl;
	delete p_arg->pstr_err_list;
	delete p_arg->psyn_set;
	delete p_arg;

	//...

	delete p_loc->ppl;
	delete p_loc->pstr_err_list;
	delete p_loc->psyn_set;
	delete p_loc;
}
void NonTerminalSyn::AddProduce()
{
	set<int> first_set;

	//...

	//program->options main( ){decls stmts} : {void,main} U first(B)
	first_set.insert(Terminal::p_void->Tag());

	first_set.insert(Terminal::p_main->Tag());

	first_set.insert(Terminal::p_bool->Tag());
	first_set.insert(Terminal::p_char->Tag());
	first_set.insert(Terminal::p_short->Tag());
	first_set.insert(Terminal::p_int->Tag());
	first_set.insert(Terminal::p_float->Tag());

	first_set.insert(Terminal::p_double->Tag());
	p_program->ppl->push_back(make_pair(Produce::p_p_program,first_set));

	//...

	//option->void id F : {void}
	first_set.clear();
	first_set.insert(Terminal::p_void->Tag());
	p_option->ppl->push_back(make_pair(Produce::p_p_option1,first_set));

	//option->B id option' : first(B)
	first_set.clear();
	first_set.insert(Terminal::p_bool->Tag());
	first_set.insert(Terminal::p_char->Tag());
	first_set.insert(Terminal::p_short->Tag());
	first_set.insert(Terminal::p_int->Tag());
	first_set.insert(Terminal::p_float->Tag());

	first_set.insert(Terminal::p_double->Tag());
	p_option->ppl->push_back(make_pair(Produce::p_p_option2,first_set));

	//option'->F : {(}
	first_set.clear();
	first_set.insert(Terminal::p_l_bracket->Tag());
	p_option_->ppl->push_back(make_pair(Produce::p_p_option_1,first_set));

	//option'->decl'; {[,=,',',;}
	first_set.clear();
	first_set.insert(Terminal::p_l_s_bracket->Tag());
	first_set.insert(Terminal::p_assign->Tag());
	first_set.insert(Terminal::p_comma->Tag());
	first_set.insert(Terminal::p_semicolon->Tag());
	p_option_->ppl->push_back(make_pair(Produce::p_p_option_2,first_set));

	//...

	//decl->B id decl'; : first(B)
	first_set.clear();
	first_set.insert(Terminal::p_bool->Tag());
	first_set.insert(Terminal::p_char->Tag());
	first_set.insert(Terminal::p_short->Tag());
	first_set.insert(Terminal::p_int->Tag());
	first_set.insert(Terminal::p_float->Tag());

	first_set.insert(Terminal::p_double->Tag());
	p_decl->ppl->push_back(make_pair(Produce::p_p_decl,first_set));

	//...

	//B->bool : {bool}
	first_set.clear();
	first_set.insert(Terminal::p_bool->Tag());
	p_b->ppl->push_back(make_pair(Produce::p_p_b1,first_set));

	//B->char : {char}
	first_set.clear();
	first_set.insert(Terminal::p_char->Tag());
	p_b->ppl->push_back(make_pair(Produce::p_p_b2,first_set));

	//B->short : {short}
	first_set.clear();
	first_set.insert(Terminal::p_short->Tag());
	p_b->ppl->push_back(make_pair(Produce::p_p_b3,first_set));

	//B->int : {int}
	first_set.clear();
	first_set.insert(Terminal::p_int->Tag());
	p_b->ppl->push_back(make_pair(Produce::p_p_b4,first_set));

	//B->float : {float}
	first_set.clear();
	first_set.insert(Terminal::p_float->Tag());
	p_b->ppl->push_back(make_pair(Produce::p_p_b5,first_set));

	//B->double : {double}
	first_set.clear();
	first_set.insert(Terminal::p_double->Tag());
	p_b->ppl->push_back(make_pair(Produce::p_p_b6,first_set));

	//...

	//A->[expr]Opt1 : {[}
	first_set.clear();
	first_set.insert(Terminal::p_l_s_bracket->Tag());
	p_a->ppl->push_back(make_pair(Produce::p_p_a,first_set));

	//L'->e1 L" : first(e1)
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
	p_l_->ppl->push_back(make_pair(Produce::p_p_l_,first_set));

	//...

	//F->(params){decls stmts} : {(}
	first_set.clear();
	first_set.insert(Terminal::p_l_bracket->Tag());
	p_f->ppl->push_back(make_pair(Produce::p_p_f,first_set));
	
	//params'->param params" : first(B)
	first_set.clear();
	first_set.insert(Terminal::p_bool->Tag());
	first_set.insert(Terminal::p_char->Tag());
	first_set.insert(Terminal::p_short->Tag());
	first_set.insert(Terminal::p_int->Tag());
	first_set.insert(Terminal::p_float->Tag());

	first_set.insert(Terminal::p_double->Tag());
	p_params_->ppl->push_back(make_pair(Produce::p_p_params_,first_set));

	//param->B id tail : first(B)
	first_set.clear();
	first_set.insert(Terminal::p_bool->Tag());
	first_set.insert(Terminal::p_char->Tag());
	first_set.insert(Terminal::p_short->Tag());
	first_set.insert(Terminal::p_int->Tag());
	first_set.insert(Terminal::p_float->Tag());

	first_set.insert(Terminal::p_double->Tag());
	p_param->ppl->push_back(make_pair(Produce::p_p_param,first_set));

	//...

	//size->num : {number}
	first_set.clear();
	first_set.insert(Terminal::p_number->Tag());
	p_size->ppl->push_back(make_pair(Produce::p_p_size1,first_set));

	//size->ascii : {ascii}
	first_set.clear();
	first_set.insert(Terminal::p_ascii->Tag());
	p_size->ppl->push_back(make_pair(Produce::p_p_size2,first_set));
		
	//...

	//stmt->; : {;}
	first_set.clear();
	first_set.insert(Terminal::p_semicolon->Tag());
	p_stmt->ppl->push_back(make_pair(Produce::p_p_stmt1,first_set));

	//stmt->expr; : first(expr)
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
	p_stmt->ppl->push_back(make_pair(Produce::p_p_stmt2,first_set));

	//stmt->if(expr)stmt E : {if}
	first_set.clear();
	first_set.insert(Terminal::p_if->Tag());
	p_stmt->ppl->push_back(make_pair(Produce::p_p_stmt3,first_set));

	//stmt->while(expr)stmt : {while}
	first_set.clear();
	first_set.insert(Terminal::p_while->Tag());	
	p_stmt->ppl->push_back(make_pair(Produce::p_p_stmt4,first_set));

	//stmt->do stmt while(expr); : {do}
	first_set.clear();
	first_set.insert(Terminal::p_do->Tag());
	p_stmt->ppl->push_back(make_pair(Produce::p_p_stmt5,first_set));

	//stmt->break; : {break}
	first_set.clear();
	first_set.insert(Terminal::p_break->Tag());
	p_stmt->ppl->push_back(make_pair(Produce::p_p_stmt6,first_set));

	//stmt->continue; : {continue}
	first_set.clear();
	first_set.insert(Terminal::p_continue->Tag());	
	p_stmt->ppl->push_back(make_pair(Produce::p_p_stmt7,first_set));

	//stmt->return optexpr2; : {return}
	first_set.clear();
	first_set.insert(Terminal::p_return->Tag());
	p_stmt->ppl->push_back(make_pair(Produce::p_p_stmt8,first_set));

	//stmt->for(optexpr2;optexpr2;optexpr2)stmt : {for}
	first_set.clear();
	first_set.insert(Terminal::p_for->Tag());
	p_stmt->ppl->push_back(make_pair(Produce::p_p_stmt9,first_set));

	//stmt->switch(expr)stmt : {switch}
	first_set.clear();
	first_set.insert(Terminal::p_switch->Tag());	
	p_stmt->ppl->push_back(make_pair(Produce::p_p_stmt10,first_set));

	//stmt->case expr: stmt : {case}
	first_set.clear();
	first_set.insert(Terminal::p_case->Tag());
	p_stmt->ppl->push_back(make_pair(Produce::p_p_stmt11,first_set));

	//stmt->default: stmt : {default}
	first_set.clear();
	first_set.insert(Terminal::p_default->Tag());
	p_stmt->ppl->push_back(make_pair(Produce::p_p_stmt12,first_set));

	//stmt->{stmts} : {'{'}
	first_set.clear();
	first_set.insert(Terminal::p_l_f_bracket->Tag());
	p_stmt->ppl->push_back(make_pair(Produce::p_p_stmt13,first_set));

	//label->false : {false}
	first_set.clear();
	first_set.insert(Terminal::p_false->Tag());
	p_label->ppl->push_back(make_pair(Produce::p_p_label1,first_set));

	//label->true : {true}
	first_set.clear();
	first_set.insert(Terminal::p_true->Tag());
	p_label->ppl->push_back(make_pair(Produce::p_p_label2,first_set));

	//label->ascii : {ascii}
	first_set.clear();
	first_set.insert(Terminal::p_ascii->Tag());
	p_label->ppl->push_back(make_pair(Produce::p_p_label3,first_set));

	//label->num : {number}
	first_set.clear();
	first_set.insert(Terminal::p_number->Tag());
	p_label->ppl->push_back(make_pair(Produce::p_p_label4,first_set));

	//label->-num : {-}
	first_set.clear();
	first_set.insert(Terminal::p_sub->Tag());
	p_label->ppl->push_back(make_pair(Produce::p_p_label5,first_set));
 
	//...

	//expr->e1 expr' : first(e1)
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
	p_expr->ppl->push_back(make_pair(Produce::p_p_expr,first_set));

	//e1->id T1 : {id}
	first_set.clear();
	first_set.insert(Terminal::p_id->Tag());
	p_e1->ppl->push_back(make_pair(Produce::p_p_e1A,first_set));

	//e1->e2 : first(e13)-{id}
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
	p_e1->ppl->push_back(make_pair(Produce::p_p_e1B,first_set));

	//e2->e3 e2' : first(e13)
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
	p_e2->ppl->push_back(make_pair(Produce::p_p_e2,first_set));

	//e3->e4 e3' : first(e13)
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
	p_e3->ppl->push_back(make_pair(Produce::p_p_e3,first_set));

	//e4->e5 e4' : first(e13)
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
	p_e4->ppl->push_back(make_pair(Produce::p_p_e4,first_set));

	//e5->e6 e5' : first(e13)
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
	p_e5->ppl->push_back(make_pair(Produce::p_p_e5,first_set));

	//e6->e7 e6' : first(e13)
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
	p_e6->ppl->push_back(make_pair(Produce::p_p_e6,first_set));

	//e7->e8 e7' : first(e13)
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
	p_e7->ppl->push_back(make_pair(Produce::p_p_e7,first_set));

	//e8->e9 e8' : first(e13)
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
	p_e8->ppl->push_back(make_pair(Produce::p_p_e8,first_set));

	//e9->e10 e9' : first(e13)
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
	p_e9->ppl->push_back(make_pair(Produce::p_p_e9,first_set));

	//e10->e11 e10' : first(e13)
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
	p_e10->ppl->push_back(make_pair(Produce::p_p_e10,first_set));

	//e11->e12 e11' : first(e13)
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
	p_e11->ppl->push_back(make_pair(Produce::p_p_e11,first_set));

	//e12->e13 e12' : first(e13)
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
	p_e12->ppl->push_back(make_pair(Produce::p_p_e12,first_set));


	//e13->~e13 : {~}
	first_set.clear();
	first_set.insert(Terminal::p_b_not->Tag());
	p_e13->ppl->push_back(make_pair(Produce::p_p_e13A,first_set));

	//e13->!e13 : {!}
	first_set.clear();
	first_set.insert(Terminal::p_log_not->Tag());
	p_e13->ppl->push_back(make_pair(Produce::p_p_e13B,first_set));

	//e13->-e13 : {-}
	first_set.clear();
	first_set.insert(Terminal::p_sub->Tag());
	p_e13->ppl->push_back(make_pair(Produce::p_p_e13C,first_set));

	//e13->+e13 : {+}
	first_set.clear();
	first_set.insert(Terminal::p_add->Tag());
	p_e13->ppl->push_back(make_pair(Produce::p_p_e13D,first_set));

	//e13->e14 : {true,false,ascii,num,real,++,--,(,id}
	first_set.clear();
	first_set.insert(Terminal::p_true->Tag());
	first_set.insert(Terminal::p_false->Tag());
	first_set.insert(Terminal::p_ascii->Tag());
	first_set.insert(Terminal::p_number->Tag());
	first_set.insert(Terminal::p_real->Tag());

	first_set.insert(Terminal::p_plus_plus->Tag());
	first_set.insert(Terminal::p_minus_minus->Tag());
	first_set.insert(Terminal::p_l_bracket->Tag());
	first_set.insert(Terminal::p_id->Tag());
	p_e13->ppl->push_back(make_pair(Produce::p_p_e13E,first_set));

	//e14->true : {true}
	first_set.clear();
	first_set.insert(Terminal::p_true->Tag());
	p_e14->ppl->push_back(make_pair(Produce::p_p_e14A,first_set));

	//e14->false : {false}
	first_set.clear();
	first_set.insert(Terminal::p_false->Tag());
	p_e14->ppl->push_back(make_pair(Produce::p_p_e14B,first_set));

	//e14->ascii : {ascii}
	first_set.clear();
	first_set.insert(Terminal::p_ascii->Tag());
	p_e14->ppl->push_back(make_pair(Produce::p_p_e14C,first_set));

	//e14->num : {num}
	first_set.clear();
	first_set.insert(Terminal::p_number->Tag());
	p_e14->ppl->push_back(make_pair(Produce::p_p_e14D,first_set));

	//e14->real : {real}
	first_set.clear();
	first_set.insert(Terminal::p_real->Tag());
	p_e14->ppl->push_back(make_pair(Produce::p_p_e14E,first_set));

	//e14->++loc : {++}
	first_set.clear();
	first_set.insert(Terminal::p_plus_plus->Tag());
	p_e14->ppl->push_back(make_pair(Produce::p_p_e14F,first_set));

	//e14->--loc : {--}
	first_set.clear();
	first_set.insert(Terminal::p_minus_minus->Tag());
	p_e14->ppl->push_back(make_pair(Produce::p_p_e14G,first_set));

	//e14->(expr) : {(}
	first_set.clear();
	first_set.insert(Terminal::p_l_bracket->Tag());
	p_e14->ppl->push_back(make_pair(Produce::p_p_e14H,first_set));

	//e14->id T3 : {id}
	first_set.clear();
	first_set.insert(Terminal::p_id->Tag());
	p_e14->ppl->push_back(make_pair(Produce::p_p_e14I,first_set));

	//...

	//args'->arg args" : first(e1)
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
	p_args_->ppl->push_back(make_pair(Produce::p_p_args_,first_set));

	//arg->e1 : first(e1)
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
	p_arg->ppl->push_back(make_pair(Produce::p_p_arg,first_set));

	//...

	//loc->id loc' : {id}
	first_set.clear();
	first_set.insert(Terminal::p_id->Tag());
	p_loc->ppl->push_back(make_pair(Produce::p_p_loc,first_set));
}
void NonTerminalSyn::InitSynSet()
{
	//...

	//first(B)
	p_program->psyn_set->insert(Terminal::p_bool->Tag());
	p_program->psyn_set->insert(Terminal::p_char->Tag());
	p_program->psyn_set->insert(Terminal::p_short->Tag());
	p_program->psyn_set->insert(Terminal::p_int->Tag());
	p_program->psyn_set->insert(Terminal::p_float->Tag());

	p_program->psyn_set->insert(Terminal::p_double->Tag());

	//first(stmt)
	p_program->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_program->psyn_set->insert(Terminal::p_l_f_bracket->Tag());

	p_program->psyn_set->insert(Terminal::p_b_not->Tag());
	p_program->psyn_set->insert(Terminal::p_log_not->Tag());
	p_program->psyn_set->insert(Terminal::p_add->Tag());
	p_program->psyn_set->insert(Terminal::p_sub->Tag());
	p_program->psyn_set->insert(Terminal::p_true->Tag());

	p_program->psyn_set->insert(Terminal::p_false->Tag());
	p_program->psyn_set->insert(Terminal::p_ascii->Tag());
	p_program->psyn_set->insert(Terminal::p_number->Tag());
	p_program->psyn_set->insert(Terminal::p_real->Tag());
	p_program->psyn_set->insert(Terminal::p_plus_plus->Tag());

	p_program->psyn_set->insert(Terminal::p_minus_minus->Tag());
	p_program->psyn_set->insert(Terminal::p_l_bracket->Tag());
	p_program->psyn_set->insert(Terminal::p_id->Tag());

	p_program->psyn_set->insert(Terminal::p_if->Tag());
	p_program->psyn_set->insert(Terminal::p_while->Tag());	
	p_program->psyn_set->insert(Terminal::p_do->Tag());
	p_program->psyn_set->insert(Terminal::p_break->Tag());
	p_program->psyn_set->insert(Terminal::p_continue->Tag());	

	p_program->psyn_set->insert(Terminal::p_return->Tag());
	p_program->psyn_set->insert(Terminal::p_for->Tag());
	p_program->psyn_set->insert(Terminal::p_switch->Tag());	
	p_program->psyn_set->insert(Terminal::p_case->Tag());
	p_program->psyn_set->insert(Terminal::p_default->Tag());

	// {'}',$}
	p_program->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	p_program->psyn_set->insert(Terminal::p_end->Tag());

	//...

	// {void,main}
	p_option->psyn_set->insert(Terminal::p_void->Tag());
	p_option->psyn_set->insert(Terminal::p_main->Tag());

	//first(B)
	p_option->psyn_set->insert(Terminal::p_bool->Tag());
	p_option->psyn_set->insert(Terminal::p_char->Tag());
	p_option->psyn_set->insert(Terminal::p_short->Tag());
	p_option->psyn_set->insert(Terminal::p_int->Tag());
	p_option->psyn_set->insert(Terminal::p_float->Tag());

	p_option->psyn_set->insert(Terminal::p_double->Tag());

	//first(stmt)
	p_option->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_option->psyn_set->insert(Terminal::p_l_f_bracket->Tag());

	p_option->psyn_set->insert(Terminal::p_b_not->Tag());
	p_option->psyn_set->insert(Terminal::p_log_not->Tag());
	p_option->psyn_set->insert(Terminal::p_add->Tag());
	p_option->psyn_set->insert(Terminal::p_sub->Tag());
	p_option->psyn_set->insert(Terminal::p_true->Tag());

	p_option->psyn_set->insert(Terminal::p_false->Tag());
	p_option->psyn_set->insert(Terminal::p_ascii->Tag());
	p_option->psyn_set->insert(Terminal::p_number->Tag());
	p_option->psyn_set->insert(Terminal::p_real->Tag());
	p_option->psyn_set->insert(Terminal::p_plus_plus->Tag());

	p_option->psyn_set->insert(Terminal::p_minus_minus->Tag());
	p_option->psyn_set->insert(Terminal::p_l_bracket->Tag());
	p_option->psyn_set->insert(Terminal::p_id->Tag());

	p_option->psyn_set->insert(Terminal::p_if->Tag());
	p_option->psyn_set->insert(Terminal::p_while->Tag());	
	p_option->psyn_set->insert(Terminal::p_do->Tag());
	p_option->psyn_set->insert(Terminal::p_break->Tag());
	p_option->psyn_set->insert(Terminal::p_continue->Tag());	

	p_option->psyn_set->insert(Terminal::p_return->Tag());
	p_option->psyn_set->insert(Terminal::p_for->Tag());
	p_option->psyn_set->insert(Terminal::p_switch->Tag());	
	p_option->psyn_set->insert(Terminal::p_case->Tag());
	p_option->psyn_set->insert(Terminal::p_default->Tag());

	// {'}',$}
	p_option->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	p_option->psyn_set->insert(Terminal::p_end->Tag());

	//...

	// {void,main}
	p_option_->psyn_set->insert(Terminal::p_void->Tag());
	p_option_->psyn_set->insert(Terminal::p_main->Tag());

	//first(B)
	p_option_->psyn_set->insert(Terminal::p_bool->Tag());
	p_option_->psyn_set->insert(Terminal::p_char->Tag());
	p_option_->psyn_set->insert(Terminal::p_short->Tag());
	p_option_->psyn_set->insert(Terminal::p_int->Tag());
	p_option_->psyn_set->insert(Terminal::p_float->Tag());

	p_option_->psyn_set->insert(Terminal::p_double->Tag());

	//first(stmt)
	p_option_->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_option_->psyn_set->insert(Terminal::p_l_f_bracket->Tag());

	p_option_->psyn_set->insert(Terminal::p_b_not->Tag());
	p_option_->psyn_set->insert(Terminal::p_log_not->Tag());
	p_option_->psyn_set->insert(Terminal::p_add->Tag());
	p_option_->psyn_set->insert(Terminal::p_sub->Tag());
	p_option_->psyn_set->insert(Terminal::p_true->Tag());

	p_option_->psyn_set->insert(Terminal::p_false->Tag());
	p_option_->psyn_set->insert(Terminal::p_ascii->Tag());
	p_option_->psyn_set->insert(Terminal::p_number->Tag());
	p_option_->psyn_set->insert(Terminal::p_real->Tag());
	p_option_->psyn_set->insert(Terminal::p_plus_plus->Tag());

	p_option_->psyn_set->insert(Terminal::p_minus_minus->Tag());
	p_option_->psyn_set->insert(Terminal::p_l_bracket->Tag());
	p_option_->psyn_set->insert(Terminal::p_id->Tag());

	p_option_->psyn_set->insert(Terminal::p_if->Tag());
	p_option_->psyn_set->insert(Terminal::p_while->Tag());	
	p_option_->psyn_set->insert(Terminal::p_do->Tag());
	p_option_->psyn_set->insert(Terminal::p_break->Tag());
	p_option_->psyn_set->insert(Terminal::p_continue->Tag());	

	p_option_->psyn_set->insert(Terminal::p_return->Tag());
	p_option_->psyn_set->insert(Terminal::p_for->Tag());
	p_option_->psyn_set->insert(Terminal::p_switch->Tag());	
	p_option_->psyn_set->insert(Terminal::p_case->Tag());
	p_option_->psyn_set->insert(Terminal::p_default->Tag());

	// {'}',$}
	p_option_->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	p_option_->psyn_set->insert(Terminal::p_end->Tag());

	//...

	//first(B)
	p_decl->psyn_set->insert(Terminal::p_bool->Tag());
	p_decl->psyn_set->insert(Terminal::p_char->Tag());
	p_decl->psyn_set->insert(Terminal::p_short->Tag());
	p_decl->psyn_set->insert(Terminal::p_int->Tag());
	p_decl->psyn_set->insert(Terminal::p_float->Tag());

	p_decl->psyn_set->insert(Terminal::p_double->Tag());

	//first(stmt)
	p_decl->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_decl->psyn_set->insert(Terminal::p_l_f_bracket->Tag());

	p_decl->psyn_set->insert(Terminal::p_b_not->Tag());
	p_decl->psyn_set->insert(Terminal::p_log_not->Tag());
	p_decl->psyn_set->insert(Terminal::p_add->Tag());
	p_decl->psyn_set->insert(Terminal::p_sub->Tag());
	p_decl->psyn_set->insert(Terminal::p_true->Tag());

	p_decl->psyn_set->insert(Terminal::p_false->Tag());
	p_decl->psyn_set->insert(Terminal::p_ascii->Tag());
	p_decl->psyn_set->insert(Terminal::p_number->Tag());
	p_decl->psyn_set->insert(Terminal::p_real->Tag());
	p_decl->psyn_set->insert(Terminal::p_plus_plus->Tag());

	p_decl->psyn_set->insert(Terminal::p_minus_minus->Tag());
	p_decl->psyn_set->insert(Terminal::p_l_bracket->Tag());
	p_decl->psyn_set->insert(Terminal::p_id->Tag());

	p_decl->psyn_set->insert(Terminal::p_if->Tag());
	p_decl->psyn_set->insert(Terminal::p_while->Tag());	
	p_decl->psyn_set->insert(Terminal::p_do->Tag());
	p_decl->psyn_set->insert(Terminal::p_break->Tag());
	p_decl->psyn_set->insert(Terminal::p_continue->Tag());	

	p_decl->psyn_set->insert(Terminal::p_return->Tag());
	p_decl->psyn_set->insert(Terminal::p_for->Tag());
	p_decl->psyn_set->insert(Terminal::p_switch->Tag());	
	p_decl->psyn_set->insert(Terminal::p_case->Tag());
	p_decl->psyn_set->insert(Terminal::p_default->Tag());

	// {'}',$}
	p_decl->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	p_decl->psyn_set->insert(Terminal::p_end->Tag());

	//...

	// {id}
	p_b->psyn_set->insert(Terminal::p_id->Tag());

	//first(B)
	p_b->psyn_set->insert(Terminal::p_bool->Tag());
	p_b->psyn_set->insert(Terminal::p_char->Tag());
	p_b->psyn_set->insert(Terminal::p_short->Tag());
	p_b->psyn_set->insert(Terminal::p_int->Tag());
	p_b->psyn_set->insert(Terminal::p_float->Tag());

	p_b->psyn_set->insert(Terminal::p_double->Tag());

	//first(stmt)
	p_b->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_b->psyn_set->insert(Terminal::p_l_f_bracket->Tag());

	p_b->psyn_set->insert(Terminal::p_b_not->Tag());
	p_b->psyn_set->insert(Terminal::p_log_not->Tag());
	p_b->psyn_set->insert(Terminal::p_add->Tag());
	p_b->psyn_set->insert(Terminal::p_sub->Tag());
	p_b->psyn_set->insert(Terminal::p_true->Tag());

	p_b->psyn_set->insert(Terminal::p_false->Tag());
	p_b->psyn_set->insert(Terminal::p_ascii->Tag());
	p_b->psyn_set->insert(Terminal::p_number->Tag());
	p_b->psyn_set->insert(Terminal::p_real->Tag());
	p_b->psyn_set->insert(Terminal::p_plus_plus->Tag());

	p_b->psyn_set->insert(Terminal::p_minus_minus->Tag());
	p_b->psyn_set->insert(Terminal::p_l_bracket->Tag());
	p_b->psyn_set->insert(Terminal::p_id->Tag());

	p_b->psyn_set->insert(Terminal::p_if->Tag());
	p_b->psyn_set->insert(Terminal::p_while->Tag());	
	p_b->psyn_set->insert(Terminal::p_do->Tag());
	p_b->psyn_set->insert(Terminal::p_break->Tag());
	p_b->psyn_set->insert(Terminal::p_continue->Tag());	

	p_b->psyn_set->insert(Terminal::p_return->Tag());
	p_b->psyn_set->insert(Terminal::p_for->Tag());
	p_b->psyn_set->insert(Terminal::p_switch->Tag());	
	p_b->psyn_set->insert(Terminal::p_case->Tag());
	p_b->psyn_set->insert(Terminal::p_default->Tag());

	// {'}',$}
	p_b->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	p_b->psyn_set->insert(Terminal::p_end->Tag());

	//...

	//{;}
	//p_a->psyn_set->insert(Terminal::p_semicolon->Tag());

	//first(B)
	p_a->psyn_set->insert(Terminal::p_bool->Tag());
	p_a->psyn_set->insert(Terminal::p_char->Tag());
	p_a->psyn_set->insert(Terminal::p_short->Tag());
	p_a->psyn_set->insert(Terminal::p_int->Tag());
	p_a->psyn_set->insert(Terminal::p_float->Tag());

	p_a->psyn_set->insert(Terminal::p_double->Tag());

	//first(stmt)
	p_a->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_a->psyn_set->insert(Terminal::p_l_f_bracket->Tag());

	p_a->psyn_set->insert(Terminal::p_b_not->Tag());
	p_a->psyn_set->insert(Terminal::p_log_not->Tag());
	p_a->psyn_set->insert(Terminal::p_add->Tag());
	p_a->psyn_set->insert(Terminal::p_sub->Tag());
	p_a->psyn_set->insert(Terminal::p_true->Tag());

	p_a->psyn_set->insert(Terminal::p_false->Tag());
	p_a->psyn_set->insert(Terminal::p_ascii->Tag());
	p_a->psyn_set->insert(Terminal::p_number->Tag());
	p_a->psyn_set->insert(Terminal::p_real->Tag());
	p_a->psyn_set->insert(Terminal::p_plus_plus->Tag());

	p_a->psyn_set->insert(Terminal::p_minus_minus->Tag());
	p_a->psyn_set->insert(Terminal::p_l_bracket->Tag());
	p_a->psyn_set->insert(Terminal::p_id->Tag());

	p_a->psyn_set->insert(Terminal::p_if->Tag());
	p_a->psyn_set->insert(Terminal::p_while->Tag());	
	p_a->psyn_set->insert(Terminal::p_do->Tag());
	p_a->psyn_set->insert(Terminal::p_break->Tag());
	p_a->psyn_set->insert(Terminal::p_continue->Tag());	

	p_a->psyn_set->insert(Terminal::p_return->Tag());
	p_a->psyn_set->insert(Terminal::p_for->Tag());
	p_a->psyn_set->insert(Terminal::p_switch->Tag());	
	p_a->psyn_set->insert(Terminal::p_case->Tag());
	p_a->psyn_set->insert(Terminal::p_default->Tag());

	// {'}',$}
	p_a->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	p_a->psyn_set->insert(Terminal::p_end->Tag());

	//...

	// {'}'}
	//p_l_->psyn_set->insert(Terminal::p_r_f_bracket->Tag());

	//first(B)
	p_l_->psyn_set->insert(Terminal::p_bool->Tag());
	p_l_->psyn_set->insert(Terminal::p_char->Tag());
	p_l_->psyn_set->insert(Terminal::p_short->Tag());
	p_l_->psyn_set->insert(Terminal::p_int->Tag());
	p_l_->psyn_set->insert(Terminal::p_float->Tag());

	p_l_->psyn_set->insert(Terminal::p_double->Tag());

	//first(stmt)
	p_l_->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_l_->psyn_set->insert(Terminal::p_l_f_bracket->Tag());

	p_l_->psyn_set->insert(Terminal::p_b_not->Tag());
	p_l_->psyn_set->insert(Terminal::p_log_not->Tag());
	p_l_->psyn_set->insert(Terminal::p_add->Tag());
	p_l_->psyn_set->insert(Terminal::p_sub->Tag());
	p_l_->psyn_set->insert(Terminal::p_true->Tag());

	p_l_->psyn_set->insert(Terminal::p_false->Tag());
	p_l_->psyn_set->insert(Terminal::p_ascii->Tag());
	p_l_->psyn_set->insert(Terminal::p_number->Tag());
	p_l_->psyn_set->insert(Terminal::p_real->Tag());
	p_l_->psyn_set->insert(Terminal::p_plus_plus->Tag());

	p_l_->psyn_set->insert(Terminal::p_minus_minus->Tag());
	p_l_->psyn_set->insert(Terminal::p_l_bracket->Tag());
	p_l_->psyn_set->insert(Terminal::p_id->Tag());

	p_l_->psyn_set->insert(Terminal::p_if->Tag());
	p_l_->psyn_set->insert(Terminal::p_while->Tag());	
	p_l_->psyn_set->insert(Terminal::p_do->Tag());
	p_l_->psyn_set->insert(Terminal::p_break->Tag());
	p_l_->psyn_set->insert(Terminal::p_continue->Tag());	

	p_l_->psyn_set->insert(Terminal::p_return->Tag());
	p_l_->psyn_set->insert(Terminal::p_for->Tag());
	p_l_->psyn_set->insert(Terminal::p_switch->Tag());	
	p_l_->psyn_set->insert(Terminal::p_case->Tag());
	p_l_->psyn_set->insert(Terminal::p_default->Tag());

	// {'}',$}
	p_l_->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	p_l_->psyn_set->insert(Terminal::p_end->Tag());

	//...

	// {void,main}
	p_f->psyn_set->insert(Terminal::p_void->Tag());
	p_f->psyn_set->insert(Terminal::p_main->Tag());

	//first(B)
	p_f->psyn_set->insert(Terminal::p_bool->Tag());
	p_f->psyn_set->insert(Terminal::p_char->Tag());
	p_f->psyn_set->insert(Terminal::p_short->Tag());
	p_f->psyn_set->insert(Terminal::p_int->Tag());
	p_f->psyn_set->insert(Terminal::p_float->Tag());

	p_f->psyn_set->insert(Terminal::p_double->Tag());

	//first(stmt)
	p_f->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_f->psyn_set->insert(Terminal::p_l_f_bracket->Tag());

	p_f->psyn_set->insert(Terminal::p_b_not->Tag());
	p_f->psyn_set->insert(Terminal::p_log_not->Tag());
	p_f->psyn_set->insert(Terminal::p_add->Tag());
	p_f->psyn_set->insert(Terminal::p_sub->Tag());
	p_f->psyn_set->insert(Terminal::p_true->Tag());

	p_f->psyn_set->insert(Terminal::p_false->Tag());
	p_f->psyn_set->insert(Terminal::p_ascii->Tag());
	p_f->psyn_set->insert(Terminal::p_number->Tag());
	p_f->psyn_set->insert(Terminal::p_real->Tag());
	p_f->psyn_set->insert(Terminal::p_plus_plus->Tag());

	p_f->psyn_set->insert(Terminal::p_minus_minus->Tag());
	p_f->psyn_set->insert(Terminal::p_l_bracket->Tag());
	p_f->psyn_set->insert(Terminal::p_id->Tag());

	p_f->psyn_set->insert(Terminal::p_if->Tag());
	p_f->psyn_set->insert(Terminal::p_while->Tag());	
	p_f->psyn_set->insert(Terminal::p_do->Tag());
	p_f->psyn_set->insert(Terminal::p_break->Tag());
	p_f->psyn_set->insert(Terminal::p_continue->Tag());	

	p_f->psyn_set->insert(Terminal::p_return->Tag());
	p_f->psyn_set->insert(Terminal::p_for->Tag());
	p_f->psyn_set->insert(Terminal::p_switch->Tag());	
	p_f->psyn_set->insert(Terminal::p_case->Tag());
	p_f->psyn_set->insert(Terminal::p_default->Tag());

	// {'}',$}
	p_f->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	p_f->psyn_set->insert(Terminal::p_end->Tag());

	//...

	// {),void,main}
	p_params_->psyn_set->insert(Terminal::p_r_bracket->Tag());
	p_params_->psyn_set->insert(Terminal::p_void->Tag());
	p_params_->psyn_set->insert(Terminal::p_main->Tag());

	//first(B)
	p_params_->psyn_set->insert(Terminal::p_bool->Tag());
	p_params_->psyn_set->insert(Terminal::p_char->Tag());
	p_params_->psyn_set->insert(Terminal::p_short->Tag());
	p_params_->psyn_set->insert(Terminal::p_int->Tag());
	p_params_->psyn_set->insert(Terminal::p_float->Tag());

	p_params_->psyn_set->insert(Terminal::p_double->Tag());

	//first(stmt)
	p_params_->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_params_->psyn_set->insert(Terminal::p_l_f_bracket->Tag());

	p_params_->psyn_set->insert(Terminal::p_b_not->Tag());
	p_params_->psyn_set->insert(Terminal::p_log_not->Tag());
	p_params_->psyn_set->insert(Terminal::p_add->Tag());
	p_params_->psyn_set->insert(Terminal::p_sub->Tag());
	p_params_->psyn_set->insert(Terminal::p_true->Tag());

	p_params_->psyn_set->insert(Terminal::p_false->Tag());
	p_params_->psyn_set->insert(Terminal::p_ascii->Tag());
	p_params_->psyn_set->insert(Terminal::p_number->Tag());
	p_params_->psyn_set->insert(Terminal::p_real->Tag());
	p_params_->psyn_set->insert(Terminal::p_plus_plus->Tag());

	p_params_->psyn_set->insert(Terminal::p_minus_minus->Tag());
	p_params_->psyn_set->insert(Terminal::p_l_bracket->Tag());
	p_params_->psyn_set->insert(Terminal::p_id->Tag());

	p_params_->psyn_set->insert(Terminal::p_if->Tag());
	p_params_->psyn_set->insert(Terminal::p_while->Tag());	
	p_params_->psyn_set->insert(Terminal::p_do->Tag());
	p_params_->psyn_set->insert(Terminal::p_break->Tag());
	p_params_->psyn_set->insert(Terminal::p_continue->Tag());	

	p_params_->psyn_set->insert(Terminal::p_return->Tag());
	p_params_->psyn_set->insert(Terminal::p_for->Tag());
	p_params_->psyn_set->insert(Terminal::p_switch->Tag());	
	p_params_->psyn_set->insert(Terminal::p_case->Tag());
	p_params_->psyn_set->insert(Terminal::p_default->Tag());

	// {'}',$}
	p_params_->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	p_params_->psyn_set->insert(Terminal::p_end->Tag());

	//...

	// {',',),void,main}
	p_param->psyn_set->insert(Terminal::p_comma->Tag());
	p_param->psyn_set->insert(Terminal::p_r_bracket->Tag());
	p_param->psyn_set->insert(Terminal::p_void->Tag());
	p_param->psyn_set->insert(Terminal::p_main->Tag());

	//first(B)
	p_param->psyn_set->insert(Terminal::p_bool->Tag());
	p_param->psyn_set->insert(Terminal::p_char->Tag());
	p_param->psyn_set->insert(Terminal::p_short->Tag());
	p_param->psyn_set->insert(Terminal::p_int->Tag());
	p_param->psyn_set->insert(Terminal::p_float->Tag());

	p_param->psyn_set->insert(Terminal::p_double->Tag());

	//first(stmt)
	p_param->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_param->psyn_set->insert(Terminal::p_l_f_bracket->Tag());

	p_param->psyn_set->insert(Terminal::p_b_not->Tag());
	p_param->psyn_set->insert(Terminal::p_log_not->Tag());
	p_param->psyn_set->insert(Terminal::p_add->Tag());
	p_param->psyn_set->insert(Terminal::p_sub->Tag());
	p_param->psyn_set->insert(Terminal::p_true->Tag());

	p_param->psyn_set->insert(Terminal::p_false->Tag());
	p_param->psyn_set->insert(Terminal::p_ascii->Tag());
	p_param->psyn_set->insert(Terminal::p_number->Tag());
	p_param->psyn_set->insert(Terminal::p_real->Tag());
	p_param->psyn_set->insert(Terminal::p_plus_plus->Tag());

	p_param->psyn_set->insert(Terminal::p_minus_minus->Tag());
	p_param->psyn_set->insert(Terminal::p_l_bracket->Tag());
	p_param->psyn_set->insert(Terminal::p_id->Tag());

	p_param->psyn_set->insert(Terminal::p_if->Tag());
	p_param->psyn_set->insert(Terminal::p_while->Tag());	
	p_param->psyn_set->insert(Terminal::p_do->Tag());
	p_param->psyn_set->insert(Terminal::p_break->Tag());
	p_param->psyn_set->insert(Terminal::p_continue->Tag());	

	p_param->psyn_set->insert(Terminal::p_return->Tag());
	p_param->psyn_set->insert(Terminal::p_for->Tag());
	p_param->psyn_set->insert(Terminal::p_switch->Tag());	
	p_param->psyn_set->insert(Terminal::p_case->Tag());
	p_param->psyn_set->insert(Terminal::p_default->Tag());

	// {'}',$}
	p_param->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	p_param->psyn_set->insert(Terminal::p_end->Tag());

	//...

	//{]}
	p_size->psyn_set->insert(Terminal::p_r_s_bracket->Tag());

	//first(stmt)
	p_size->psyn_set->insert(Terminal::p_semicolon->Tag());
	//p_size->psyn_set->insert(Terminal::p_l_f_bracket->Tag());

	//p_size->psyn_set->insert(Terminal::p_b_not->Tag());
	//p_size->psyn_set->insert(Terminal::p_log_not->Tag());
	//p_size->psyn_set->insert(Terminal::p_add->Tag());
	//p_size->psyn_set->insert(Terminal::p_sub->Tag());
	//p_size->psyn_set->insert(Terminal::p_true->Tag());

	//p_size->psyn_set->insert(Terminal::p_false->Tag());
	//p_size->psyn_set->insert(Terminal::p_ascii->Tag());
	p_size->psyn_set->insert(Terminal::p_number->Tag());
	//p_size->psyn_set->insert(Terminal::p_real->Tag());
	//p_size->psyn_set->insert(Terminal::p_plus_plus->Tag());

	//p_size->psyn_set->insert(Terminal::p_minus_minus->Tag());
	//p_size->psyn_set->insert(Terminal::p_l_bracket->Tag());
	//p_size->psyn_set->insert(Terminal::p_id->Tag());

	p_size->psyn_set->insert(Terminal::p_if->Tag());
	p_size->psyn_set->insert(Terminal::p_while->Tag());	
	p_size->psyn_set->insert(Terminal::p_do->Tag());
	p_size->psyn_set->insert(Terminal::p_break->Tag());
	p_size->psyn_set->insert(Terminal::p_continue->Tag());	

	p_size->psyn_set->insert(Terminal::p_return->Tag());
	p_size->psyn_set->insert(Terminal::p_for->Tag());
	p_size->psyn_set->insert(Terminal::p_switch->Tag());	
	p_size->psyn_set->insert(Terminal::p_case->Tag());
	p_size->psyn_set->insert(Terminal::p_default->Tag());

	// {'}',$}
	p_size->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	p_size->psyn_set->insert(Terminal::p_end->Tag());

	//...

	//{'}',else}
	//p_stmt->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	p_stmt->psyn_set->insert(Terminal::p_else->Tag());

	//first(stmt)
	p_stmt->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_stmt->psyn_set->insert(Terminal::p_l_f_bracket->Tag());

	p_stmt->psyn_set->insert(Terminal::p_b_not->Tag());
	p_stmt->psyn_set->insert(Terminal::p_log_not->Tag());
	p_stmt->psyn_set->insert(Terminal::p_add->Tag());
	p_stmt->psyn_set->insert(Terminal::p_sub->Tag());
	p_stmt->psyn_set->insert(Terminal::p_true->Tag());

	p_stmt->psyn_set->insert(Terminal::p_false->Tag());
	p_stmt->psyn_set->insert(Terminal::p_ascii->Tag());
	p_stmt->psyn_set->insert(Terminal::p_number->Tag());
	p_stmt->psyn_set->insert(Terminal::p_real->Tag());
	p_stmt->psyn_set->insert(Terminal::p_plus_plus->Tag());

	p_stmt->psyn_set->insert(Terminal::p_minus_minus->Tag());
	p_stmt->psyn_set->insert(Terminal::p_l_bracket->Tag());
	p_stmt->psyn_set->insert(Terminal::p_id->Tag());

	p_stmt->psyn_set->insert(Terminal::p_if->Tag());
	p_stmt->psyn_set->insert(Terminal::p_while->Tag());	
	p_stmt->psyn_set->insert(Terminal::p_do->Tag());
	p_stmt->psyn_set->insert(Terminal::p_break->Tag());
	p_stmt->psyn_set->insert(Terminal::p_continue->Tag());	

	p_stmt->psyn_set->insert(Terminal::p_return->Tag());
	p_stmt->psyn_set->insert(Terminal::p_for->Tag());
	p_stmt->psyn_set->insert(Terminal::p_switch->Tag());	
	p_stmt->psyn_set->insert(Terminal::p_case->Tag());
	p_stmt->psyn_set->insert(Terminal::p_default->Tag());

	// {'}',$}
	p_stmt->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	p_stmt->psyn_set->insert(Terminal::p_end->Tag());

	//{:}
	p_label->psyn_set->insert(Terminal::p_colon->Tag());

	//first(stmt)
	p_label->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_label->psyn_set->insert(Terminal::p_l_f_bracket->Tag());

	p_label->psyn_set->insert(Terminal::p_b_not->Tag());
	p_label->psyn_set->insert(Terminal::p_log_not->Tag());
	p_label->psyn_set->insert(Terminal::p_add->Tag());
	p_label->psyn_set->insert(Terminal::p_sub->Tag());
	p_label->psyn_set->insert(Terminal::p_true->Tag());

	p_label->psyn_set->insert(Terminal::p_false->Tag());
	p_label->psyn_set->insert(Terminal::p_ascii->Tag());
	p_label->psyn_set->insert(Terminal::p_number->Tag());
	p_label->psyn_set->insert(Terminal::p_real->Tag());
	p_label->psyn_set->insert(Terminal::p_plus_plus->Tag());

	p_label->psyn_set->insert(Terminal::p_minus_minus->Tag());
	p_label->psyn_set->insert(Terminal::p_l_bracket->Tag());
	p_label->psyn_set->insert(Terminal::p_id->Tag());

	p_label->psyn_set->insert(Terminal::p_if->Tag());
	p_label->psyn_set->insert(Terminal::p_while->Tag());	
	p_label->psyn_set->insert(Terminal::p_do->Tag());
	p_label->psyn_set->insert(Terminal::p_break->Tag());
	p_label->psyn_set->insert(Terminal::p_continue->Tag());	

	p_label->psyn_set->insert(Terminal::p_return->Tag());
	p_label->psyn_set->insert(Terminal::p_for->Tag());
	p_label->psyn_set->insert(Terminal::p_switch->Tag());	
	p_label->psyn_set->insert(Terminal::p_case->Tag());
	p_label->psyn_set->insert(Terminal::p_default->Tag());

	// {'}',$}
	p_label->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	p_label->psyn_set->insert(Terminal::p_end->Tag());

	//...

	//{;,:,),]}
	//p_expr->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_expr->psyn_set->insert(Terminal::p_colon->Tag());
	p_expr->psyn_set->insert(Terminal::p_r_bracket->Tag());
	p_expr->psyn_set->insert(Terminal::p_r_s_bracket->Tag());

	//first(stmt)
	p_expr->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_expr->psyn_set->insert(Terminal::p_l_f_bracket->Tag());

	p_expr->psyn_set->insert(Terminal::p_b_not->Tag());
	p_expr->psyn_set->insert(Terminal::p_log_not->Tag());
	p_expr->psyn_set->insert(Terminal::p_add->Tag());
	p_expr->psyn_set->insert(Terminal::p_sub->Tag());
	p_expr->psyn_set->insert(Terminal::p_true->Tag());

	p_expr->psyn_set->insert(Terminal::p_false->Tag());
	p_expr->psyn_set->insert(Terminal::p_ascii->Tag());
	p_expr->psyn_set->insert(Terminal::p_number->Tag());
	p_expr->psyn_set->insert(Terminal::p_real->Tag());
	p_expr->psyn_set->insert(Terminal::p_plus_plus->Tag());

	p_expr->psyn_set->insert(Terminal::p_minus_minus->Tag());
	p_expr->psyn_set->insert(Terminal::p_l_bracket->Tag());
	p_expr->psyn_set->insert(Terminal::p_id->Tag());

	p_expr->psyn_set->insert(Terminal::p_if->Tag());
	p_expr->psyn_set->insert(Terminal::p_while->Tag());	
	p_expr->psyn_set->insert(Terminal::p_do->Tag());
	p_expr->psyn_set->insert(Terminal::p_break->Tag());
	p_expr->psyn_set->insert(Terminal::p_continue->Tag());	

	p_expr->psyn_set->insert(Terminal::p_return->Tag());
	p_expr->psyn_set->insert(Terminal::p_for->Tag());
	p_expr->psyn_set->insert(Terminal::p_switch->Tag());	
	p_expr->psyn_set->insert(Terminal::p_case->Tag());
	p_expr->psyn_set->insert(Terminal::p_default->Tag());

	// {'}',$}
	p_expr->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	p_expr->psyn_set->insert(Terminal::p_end->Tag());

	//...

	//{',',}',;,:,),]}
	p_e1->psyn_set->insert(Terminal::p_comma->Tag());
	//p_e1->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	//p_e1->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_e1->psyn_set->insert(Terminal::p_colon->Tag());
	p_e1->psyn_set->insert(Terminal::p_r_bracket->Tag());
	p_e1->psyn_set->insert(Terminal::p_r_s_bracket->Tag());

	//first(stmt)
	p_e1->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_e1->psyn_set->insert(Terminal::p_l_f_bracket->Tag());

	p_e1->psyn_set->insert(Terminal::p_b_not->Tag());
	p_e1->psyn_set->insert(Terminal::p_log_not->Tag());
	p_e1->psyn_set->insert(Terminal::p_add->Tag());
	p_e1->psyn_set->insert(Terminal::p_sub->Tag());
	p_e1->psyn_set->insert(Terminal::p_true->Tag());

	p_e1->psyn_set->insert(Terminal::p_false->Tag());
	p_e1->psyn_set->insert(Terminal::p_ascii->Tag());
	p_e1->psyn_set->insert(Terminal::p_number->Tag());
	p_e1->psyn_set->insert(Terminal::p_real->Tag());
	p_e1->psyn_set->insert(Terminal::p_plus_plus->Tag());

	p_e1->psyn_set->insert(Terminal::p_minus_minus->Tag());
	p_e1->psyn_set->insert(Terminal::p_l_bracket->Tag());
	p_e1->psyn_set->insert(Terminal::p_id->Tag());

	p_e1->psyn_set->insert(Terminal::p_if->Tag());
	p_e1->psyn_set->insert(Terminal::p_while->Tag());	
	p_e1->psyn_set->insert(Terminal::p_do->Tag());
	p_e1->psyn_set->insert(Terminal::p_break->Tag());
	p_e1->psyn_set->insert(Terminal::p_continue->Tag());	

	p_e1->psyn_set->insert(Terminal::p_return->Tag());
	p_e1->psyn_set->insert(Terminal::p_for->Tag());
	p_e1->psyn_set->insert(Terminal::p_switch->Tag());	
	p_e1->psyn_set->insert(Terminal::p_case->Tag());
	p_e1->psyn_set->insert(Terminal::p_default->Tag());

	// {'}',$}
	p_e1->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	p_e1->psyn_set->insert(Terminal::p_end->Tag());

	//...

	//{',','}',;,:,),]}
	p_e2->psyn_set->insert(Terminal::p_comma->Tag());
	//p_e2->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	//p_e2->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_e2->psyn_set->insert(Terminal::p_colon->Tag());
	p_e2->psyn_set->insert(Terminal::p_r_bracket->Tag());
	p_e2->psyn_set->insert(Terminal::p_r_s_bracket->Tag());

	//first(stmt)
	p_e2->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_e2->psyn_set->insert(Terminal::p_l_f_bracket->Tag());

	p_e2->psyn_set->insert(Terminal::p_b_not->Tag());
	p_e2->psyn_set->insert(Terminal::p_log_not->Tag());
	p_e2->psyn_set->insert(Terminal::p_add->Tag());
	p_e2->psyn_set->insert(Terminal::p_sub->Tag());
	p_e2->psyn_set->insert(Terminal::p_true->Tag());

	p_e2->psyn_set->insert(Terminal::p_false->Tag());
	p_e2->psyn_set->insert(Terminal::p_ascii->Tag());
	p_e2->psyn_set->insert(Terminal::p_number->Tag());
	p_e2->psyn_set->insert(Terminal::p_real->Tag());
	p_e2->psyn_set->insert(Terminal::p_plus_plus->Tag());

	p_e2->psyn_set->insert(Terminal::p_minus_minus->Tag());
	p_e2->psyn_set->insert(Terminal::p_l_bracket->Tag());
	p_e2->psyn_set->insert(Terminal::p_id->Tag());

	p_e2->psyn_set->insert(Terminal::p_if->Tag());
	p_e2->psyn_set->insert(Terminal::p_while->Tag());	
	p_e2->psyn_set->insert(Terminal::p_do->Tag());
	p_e2->psyn_set->insert(Terminal::p_break->Tag());
	p_e2->psyn_set->insert(Terminal::p_continue->Tag());	

	p_e2->psyn_set->insert(Terminal::p_return->Tag());
	p_e2->psyn_set->insert(Terminal::p_for->Tag());
	p_e2->psyn_set->insert(Terminal::p_switch->Tag());	
	p_e2->psyn_set->insert(Terminal::p_case->Tag());
	p_e2->psyn_set->insert(Terminal::p_default->Tag());

	// {'}',$}
	p_e2->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	p_e2->psyn_set->insert(Terminal::p_end->Tag());

	//...

	//{?}
	p_e3->psyn_set->insert(Terminal::p_question->Tag());

	//{',','}',;,:,),]}
	p_e3->psyn_set->insert(Terminal::p_comma->Tag());
	//p_e3->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	//p_e3->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_e3->psyn_set->insert(Terminal::p_colon->Tag());
	p_e3->psyn_set->insert(Terminal::p_r_bracket->Tag());
	p_e3->psyn_set->insert(Terminal::p_r_s_bracket->Tag());

	//first(stmt)
	p_e3->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_e3->psyn_set->insert(Terminal::p_l_f_bracket->Tag());

	p_e3->psyn_set->insert(Terminal::p_b_not->Tag());
	p_e3->psyn_set->insert(Terminal::p_log_not->Tag());
	p_e3->psyn_set->insert(Terminal::p_add->Tag());
	p_e3->psyn_set->insert(Terminal::p_sub->Tag());
	p_e3->psyn_set->insert(Terminal::p_true->Tag());

	p_e3->psyn_set->insert(Terminal::p_false->Tag());
	p_e3->psyn_set->insert(Terminal::p_ascii->Tag());
	p_e3->psyn_set->insert(Terminal::p_number->Tag());
	p_e3->psyn_set->insert(Terminal::p_real->Tag());
	p_e3->psyn_set->insert(Terminal::p_plus_plus->Tag());

	p_e3->psyn_set->insert(Terminal::p_minus_minus->Tag());
	p_e3->psyn_set->insert(Terminal::p_l_bracket->Tag());
	p_e3->psyn_set->insert(Terminal::p_id->Tag());

	p_e3->psyn_set->insert(Terminal::p_if->Tag());
	p_e3->psyn_set->insert(Terminal::p_while->Tag());	
	p_e3->psyn_set->insert(Terminal::p_do->Tag());
	p_e3->psyn_set->insert(Terminal::p_break->Tag());
	p_e3->psyn_set->insert(Terminal::p_continue->Tag());	

	p_e3->psyn_set->insert(Terminal::p_return->Tag());
	p_e3->psyn_set->insert(Terminal::p_for->Tag());
	p_e3->psyn_set->insert(Terminal::p_switch->Tag());	
	p_e3->psyn_set->insert(Terminal::p_case->Tag());
	p_e3->psyn_set->insert(Terminal::p_default->Tag());

	// {'}',$}
	p_e3->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	p_e3->psyn_set->insert(Terminal::p_end->Tag());

	//...

	//{||,?}
	p_e4->psyn_set->insert(Terminal::p_log_or->Tag());
	p_e4->psyn_set->insert(Terminal::p_question->Tag());

	//{',','}',;,:,),]}
	p_e4->psyn_set->insert(Terminal::p_comma->Tag());
	//p_e4->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	//p_e4->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_e4->psyn_set->insert(Terminal::p_colon->Tag());
	p_e4->psyn_set->insert(Terminal::p_r_bracket->Tag());
	p_e4->psyn_set->insert(Terminal::p_r_s_bracket->Tag());

	//first(stmt)
	p_e4->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_e4->psyn_set->insert(Terminal::p_l_f_bracket->Tag());

	p_e4->psyn_set->insert(Terminal::p_b_not->Tag());
	p_e4->psyn_set->insert(Terminal::p_log_not->Tag());
	p_e4->psyn_set->insert(Terminal::p_add->Tag());
	p_e4->psyn_set->insert(Terminal::p_sub->Tag());
	p_e4->psyn_set->insert(Terminal::p_true->Tag());

	p_e4->psyn_set->insert(Terminal::p_false->Tag());
	p_e4->psyn_set->insert(Terminal::p_ascii->Tag());
	p_e4->psyn_set->insert(Terminal::p_number->Tag());
	p_e4->psyn_set->insert(Terminal::p_real->Tag());
	p_e4->psyn_set->insert(Terminal::p_plus_plus->Tag());

	p_e4->psyn_set->insert(Terminal::p_minus_minus->Tag());
	p_e4->psyn_set->insert(Terminal::p_l_bracket->Tag());
	p_e4->psyn_set->insert(Terminal::p_id->Tag());

	p_e4->psyn_set->insert(Terminal::p_if->Tag());
	p_e4->psyn_set->insert(Terminal::p_while->Tag());	
	p_e4->psyn_set->insert(Terminal::p_do->Tag());
	p_e4->psyn_set->insert(Terminal::p_break->Tag());
	p_e4->psyn_set->insert(Terminal::p_continue->Tag());	

	p_e4->psyn_set->insert(Terminal::p_return->Tag());
	p_e4->psyn_set->insert(Terminal::p_for->Tag());
	p_e4->psyn_set->insert(Terminal::p_switch->Tag());	
	p_e4->psyn_set->insert(Terminal::p_case->Tag());
	p_e4->psyn_set->insert(Terminal::p_default->Tag());

	// {'}',$}
	p_e4->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	p_e4->psyn_set->insert(Terminal::p_end->Tag());

	//...

	//{&&,||,?}
	p_e5->psyn_set->insert(Terminal::p_log_and->Tag());
	p_e5->psyn_set->insert(Terminal::p_log_or->Tag());
	p_e5->psyn_set->insert(Terminal::p_question->Tag());

	//{',','}',;,:,),]}
	p_e5->psyn_set->insert(Terminal::p_comma->Tag());
	//p_e5->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	//p_e5->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_e5->psyn_set->insert(Terminal::p_colon->Tag());
	p_e5->psyn_set->insert(Terminal::p_r_bracket->Tag());
	p_e5->psyn_set->insert(Terminal::p_r_s_bracket->Tag());

	//first(stmt)
	p_e5->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_e5->psyn_set->insert(Terminal::p_l_f_bracket->Tag());

	p_e5->psyn_set->insert(Terminal::p_b_not->Tag());
	p_e5->psyn_set->insert(Terminal::p_log_not->Tag());
	p_e5->psyn_set->insert(Terminal::p_add->Tag());
	p_e5->psyn_set->insert(Terminal::p_sub->Tag());
	p_e5->psyn_set->insert(Terminal::p_true->Tag());

	p_e5->psyn_set->insert(Terminal::p_false->Tag());
	p_e5->psyn_set->insert(Terminal::p_ascii->Tag());
	p_e5->psyn_set->insert(Terminal::p_number->Tag());
	p_e5->psyn_set->insert(Terminal::p_real->Tag());
	p_e5->psyn_set->insert(Terminal::p_plus_plus->Tag());

	p_e5->psyn_set->insert(Terminal::p_minus_minus->Tag());
	p_e5->psyn_set->insert(Terminal::p_l_bracket->Tag());
	p_e5->psyn_set->insert(Terminal::p_id->Tag());

	p_e5->psyn_set->insert(Terminal::p_if->Tag());
	p_e5->psyn_set->insert(Terminal::p_while->Tag());	
	p_e5->psyn_set->insert(Terminal::p_do->Tag());
	p_e5->psyn_set->insert(Terminal::p_break->Tag());
	p_e5->psyn_set->insert(Terminal::p_continue->Tag());	

	p_e5->psyn_set->insert(Terminal::p_return->Tag());
	p_e5->psyn_set->insert(Terminal::p_for->Tag());
	p_e5->psyn_set->insert(Terminal::p_switch->Tag());	
	p_e5->psyn_set->insert(Terminal::p_case->Tag());
	p_e5->psyn_set->insert(Terminal::p_default->Tag());

	// {'}',$}
	p_e5->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	p_e5->psyn_set->insert(Terminal::p_end->Tag());

	//...

	//{|,&&,||,?}
	p_e6->psyn_set->insert(Terminal::p_b_or->Tag());
	p_e6->psyn_set->insert(Terminal::p_log_and->Tag());
	p_e6->psyn_set->insert(Terminal::p_log_or->Tag());
	p_e6->psyn_set->insert(Terminal::p_question->Tag());

	//{',','}',;,:,),]}
	p_e6->psyn_set->insert(Terminal::p_comma->Tag());
	//p_e6->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	//p_e6->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_e6->psyn_set->insert(Terminal::p_colon->Tag());
	p_e6->psyn_set->insert(Terminal::p_r_bracket->Tag());
	p_e6->psyn_set->insert(Terminal::p_r_s_bracket->Tag());

	//first(stmt)
	p_e6->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_e6->psyn_set->insert(Terminal::p_l_f_bracket->Tag());

	p_e6->psyn_set->insert(Terminal::p_b_not->Tag());
	p_e6->psyn_set->insert(Terminal::p_log_not->Tag());
	p_e6->psyn_set->insert(Terminal::p_add->Tag());
	p_e6->psyn_set->insert(Terminal::p_sub->Tag());
	p_e6->psyn_set->insert(Terminal::p_true->Tag());

	p_e6->psyn_set->insert(Terminal::p_false->Tag());
	p_e6->psyn_set->insert(Terminal::p_ascii->Tag());
	p_e6->psyn_set->insert(Terminal::p_number->Tag());
	p_e6->psyn_set->insert(Terminal::p_real->Tag());
	p_e6->psyn_set->insert(Terminal::p_plus_plus->Tag());

	p_e6->psyn_set->insert(Terminal::p_minus_minus->Tag());
	p_e6->psyn_set->insert(Terminal::p_l_bracket->Tag());
	p_e6->psyn_set->insert(Terminal::p_id->Tag());

	p_e6->psyn_set->insert(Terminal::p_if->Tag());
	p_e6->psyn_set->insert(Terminal::p_while->Tag());	
	p_e6->psyn_set->insert(Terminal::p_do->Tag());
	p_e6->psyn_set->insert(Terminal::p_break->Tag());
	p_e6->psyn_set->insert(Terminal::p_continue->Tag());	

	p_e6->psyn_set->insert(Terminal::p_return->Tag());
	p_e6->psyn_set->insert(Terminal::p_for->Tag());
	p_e6->psyn_set->insert(Terminal::p_switch->Tag());	
	p_e6->psyn_set->insert(Terminal::p_case->Tag());
	p_e6->psyn_set->insert(Terminal::p_default->Tag());

	// {'}',$}
	p_e6->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	p_e6->psyn_set->insert(Terminal::p_end->Tag());

	//...

	//{^,|,&&,||,?}
	p_e7->psyn_set->insert(Terminal::p_b_xor->Tag());
	p_e7->psyn_set->insert(Terminal::p_b_or->Tag());
	p_e7->psyn_set->insert(Terminal::p_log_and->Tag());
	p_e7->psyn_set->insert(Terminal::p_log_or->Tag());
	p_e7->psyn_set->insert(Terminal::p_question->Tag());

	//{',','}',;,:,),]}
	p_e7->psyn_set->insert(Terminal::p_comma->Tag());
	//p_e7->psyn_set->insert(Terminal::p_r_f_bracket->Tag());	
	//p_e7->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_e7->psyn_set->insert(Terminal::p_colon->Tag());
	p_e7->psyn_set->insert(Terminal::p_r_bracket->Tag());
	p_e7->psyn_set->insert(Terminal::p_r_s_bracket->Tag());

	//first(stmt)
	p_e7->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_e7->psyn_set->insert(Terminal::p_l_f_bracket->Tag());

	p_e7->psyn_set->insert(Terminal::p_b_not->Tag());
	p_e7->psyn_set->insert(Terminal::p_log_not->Tag());
	p_e7->psyn_set->insert(Terminal::p_add->Tag());
	p_e7->psyn_set->insert(Terminal::p_sub->Tag());
	p_e7->psyn_set->insert(Terminal::p_true->Tag());

	p_e7->psyn_set->insert(Terminal::p_false->Tag());
	p_e7->psyn_set->insert(Terminal::p_ascii->Tag());
	p_e7->psyn_set->insert(Terminal::p_number->Tag());
	p_e7->psyn_set->insert(Terminal::p_real->Tag());
	p_e7->psyn_set->insert(Terminal::p_plus_plus->Tag());

	p_e7->psyn_set->insert(Terminal::p_minus_minus->Tag());
	p_e7->psyn_set->insert(Terminal::p_l_bracket->Tag());
	p_e7->psyn_set->insert(Terminal::p_id->Tag());

	p_e7->psyn_set->insert(Terminal::p_if->Tag());
	p_e7->psyn_set->insert(Terminal::p_while->Tag());	
	p_e7->psyn_set->insert(Terminal::p_do->Tag());
	p_e7->psyn_set->insert(Terminal::p_break->Tag());
	p_e7->psyn_set->insert(Terminal::p_continue->Tag());	

	p_e7->psyn_set->insert(Terminal::p_return->Tag());
	p_e7->psyn_set->insert(Terminal::p_for->Tag());
	p_e7->psyn_set->insert(Terminal::p_switch->Tag());	
	p_e7->psyn_set->insert(Terminal::p_case->Tag());
	p_e7->psyn_set->insert(Terminal::p_default->Tag());

	// {'}',$}
	p_e7->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	p_e7->psyn_set->insert(Terminal::p_end->Tag());

	//...

	//{&,^,|,&&,||,?}
	p_e8->psyn_set->insert(Terminal::p_b_and->Tag());
	p_e8->psyn_set->insert(Terminal::p_b_xor->Tag());
	p_e8->psyn_set->insert(Terminal::p_b_or->Tag());
	p_e8->psyn_set->insert(Terminal::p_log_and->Tag());
	p_e8->psyn_set->insert(Terminal::p_log_or->Tag());
	p_e8->psyn_set->insert(Terminal::p_question->Tag());

	//{',','}',;,:,),]}
	p_e8->psyn_set->insert(Terminal::p_comma->Tag());
	//p_e8->psyn_set->insert(Terminal::p_r_f_bracket->Tag());	
	//p_e8->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_e8->psyn_set->insert(Terminal::p_colon->Tag());
	p_e8->psyn_set->insert(Terminal::p_r_bracket->Tag());
	p_e8->psyn_set->insert(Terminal::p_r_s_bracket->Tag());

	//first(stmt)
	p_e8->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_e8->psyn_set->insert(Terminal::p_l_f_bracket->Tag());

	p_e8->psyn_set->insert(Terminal::p_b_not->Tag());
	p_e8->psyn_set->insert(Terminal::p_log_not->Tag());
	p_e8->psyn_set->insert(Terminal::p_add->Tag());
	p_e8->psyn_set->insert(Terminal::p_sub->Tag());
	p_e8->psyn_set->insert(Terminal::p_true->Tag());

	p_e8->psyn_set->insert(Terminal::p_false->Tag());
	p_e8->psyn_set->insert(Terminal::p_ascii->Tag());
	p_e8->psyn_set->insert(Terminal::p_number->Tag());
	p_e8->psyn_set->insert(Terminal::p_real->Tag());
	p_e8->psyn_set->insert(Terminal::p_plus_plus->Tag());

	p_e8->psyn_set->insert(Terminal::p_minus_minus->Tag());
	p_e8->psyn_set->insert(Terminal::p_l_bracket->Tag());
	p_e8->psyn_set->insert(Terminal::p_id->Tag());

	p_e8->psyn_set->insert(Terminal::p_if->Tag());
	p_e8->psyn_set->insert(Terminal::p_while->Tag());	
	p_e8->psyn_set->insert(Terminal::p_do->Tag());
	p_e8->psyn_set->insert(Terminal::p_break->Tag());
	p_e8->psyn_set->insert(Terminal::p_continue->Tag());	

	p_e8->psyn_set->insert(Terminal::p_return->Tag());
	p_e8->psyn_set->insert(Terminal::p_for->Tag());
	p_e8->psyn_set->insert(Terminal::p_switch->Tag());	
	p_e8->psyn_set->insert(Terminal::p_case->Tag());
	p_e8->psyn_set->insert(Terminal::p_default->Tag());

	// {'}',$}
	p_e8->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	p_e8->psyn_set->insert(Terminal::p_end->Tag());

	//...

	//{==,!=,&,^,|,&&,||,?}
	p_e9->psyn_set->insert(Terminal::p_eq->Tag());
	p_e9->psyn_set->insert(Terminal::p_ne->Tag());
	p_e9->psyn_set->insert(Terminal::p_b_and->Tag());
	p_e9->psyn_set->insert(Terminal::p_b_xor->Tag());
	p_e9->psyn_set->insert(Terminal::p_b_or->Tag());
	p_e9->psyn_set->insert(Terminal::p_log_and->Tag());
	p_e9->psyn_set->insert(Terminal::p_log_or->Tag());
	p_e9->psyn_set->insert(Terminal::p_question->Tag());

	//{',','}',;,:,),]}
	p_e9->psyn_set->insert(Terminal::p_comma->Tag());
	//p_e9->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	//p_e9->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_e9->psyn_set->insert(Terminal::p_colon->Tag());
	p_e9->psyn_set->insert(Terminal::p_r_bracket->Tag());
	p_e9->psyn_set->insert(Terminal::p_r_s_bracket->Tag());

	//first(stmt)
	p_e9->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_e9->psyn_set->insert(Terminal::p_l_f_bracket->Tag());

	p_e9->psyn_set->insert(Terminal::p_b_not->Tag());
	p_e9->psyn_set->insert(Terminal::p_log_not->Tag());
	p_e9->psyn_set->insert(Terminal::p_add->Tag());
	p_e9->psyn_set->insert(Terminal::p_sub->Tag());
	p_e9->psyn_set->insert(Terminal::p_true->Tag());

	p_e9->psyn_set->insert(Terminal::p_false->Tag());
	p_e9->psyn_set->insert(Terminal::p_ascii->Tag());
	p_e9->psyn_set->insert(Terminal::p_number->Tag());
	p_e9->psyn_set->insert(Terminal::p_real->Tag());
	p_e9->psyn_set->insert(Terminal::p_plus_plus->Tag());

	p_e9->psyn_set->insert(Terminal::p_minus_minus->Tag());
	p_e9->psyn_set->insert(Terminal::p_l_bracket->Tag());
	p_e9->psyn_set->insert(Terminal::p_id->Tag());

	p_e9->psyn_set->insert(Terminal::p_if->Tag());
	p_e9->psyn_set->insert(Terminal::p_while->Tag());	
	p_e9->psyn_set->insert(Terminal::p_do->Tag());
	p_e9->psyn_set->insert(Terminal::p_break->Tag());
	p_e9->psyn_set->insert(Terminal::p_continue->Tag());	

	p_e9->psyn_set->insert(Terminal::p_return->Tag());
	p_e9->psyn_set->insert(Terminal::p_for->Tag());
	p_e9->psyn_set->insert(Terminal::p_switch->Tag());	
	p_e9->psyn_set->insert(Terminal::p_case->Tag());
	p_e9->psyn_set->insert(Terminal::p_default->Tag());

	// {'}',$}
	p_e9->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	p_e9->psyn_set->insert(Terminal::p_end->Tag());

	//...

	//{<,<=,>,>=,==,!=,&,^,|,&&,||,?}
	p_e10->psyn_set->insert(Terminal::p_less->Tag());
	p_e10->psyn_set->insert(Terminal::p_le->Tag());
	p_e10->psyn_set->insert(Terminal::p_greater->Tag());
	p_e10->psyn_set->insert(Terminal::p_ge->Tag());
	p_e10->psyn_set->insert(Terminal::p_eq->Tag());
	p_e10->psyn_set->insert(Terminal::p_ne->Tag());
	p_e10->psyn_set->insert(Terminal::p_b_and->Tag());
	p_e10->psyn_set->insert(Terminal::p_b_xor->Tag());
	p_e10->psyn_set->insert(Terminal::p_b_or->Tag());
	p_e10->psyn_set->insert(Terminal::p_log_and->Tag());
	p_e10->psyn_set->insert(Terminal::p_log_or->Tag());
	p_e10->psyn_set->insert(Terminal::p_question->Tag());

	//{',','}',;,:,),]}
	p_e10->psyn_set->insert(Terminal::p_comma->Tag());
	//p_e10->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	//p_e10->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_e10->psyn_set->insert(Terminal::p_colon->Tag());
	p_e10->psyn_set->insert(Terminal::p_r_bracket->Tag());
	p_e10->psyn_set->insert(Terminal::p_r_s_bracket->Tag());

	//first(stmt)
	p_e10->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_e10->psyn_set->insert(Terminal::p_l_f_bracket->Tag());

	p_e10->psyn_set->insert(Terminal::p_b_not->Tag());
	p_e10->psyn_set->insert(Terminal::p_log_not->Tag());
	p_e10->psyn_set->insert(Terminal::p_add->Tag());
	p_e10->psyn_set->insert(Terminal::p_sub->Tag());
	p_e10->psyn_set->insert(Terminal::p_true->Tag());

	p_e10->psyn_set->insert(Terminal::p_false->Tag());
	p_e10->psyn_set->insert(Terminal::p_ascii->Tag());
	p_e10->psyn_set->insert(Terminal::p_number->Tag());
	p_e10->psyn_set->insert(Terminal::p_real->Tag());
	p_e10->psyn_set->insert(Terminal::p_plus_plus->Tag());

	p_e10->psyn_set->insert(Terminal::p_minus_minus->Tag());
	p_e10->psyn_set->insert(Terminal::p_l_bracket->Tag());
	p_e10->psyn_set->insert(Terminal::p_id->Tag());

	p_e10->psyn_set->insert(Terminal::p_if->Tag());
	p_e10->psyn_set->insert(Terminal::p_while->Tag());	
	p_e10->psyn_set->insert(Terminal::p_do->Tag());
	p_e10->psyn_set->insert(Terminal::p_break->Tag());
	p_e10->psyn_set->insert(Terminal::p_continue->Tag());	

	p_e10->psyn_set->insert(Terminal::p_return->Tag());
	p_e10->psyn_set->insert(Terminal::p_for->Tag());
	p_e10->psyn_set->insert(Terminal::p_switch->Tag());	
	p_e10->psyn_set->insert(Terminal::p_case->Tag());
	p_e10->psyn_set->insert(Terminal::p_default->Tag());

	// {'}',$}
	p_e10->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	p_e10->psyn_set->insert(Terminal::p_end->Tag());

	//...

	//{<<,>>,<,<=,>,>=,==,!=,&,^,|,&&,||,?}
	p_e11->psyn_set->insert(Terminal::p_l_sht->Tag());
	p_e11->psyn_set->insert(Terminal::p_r_sht->Tag());
	p_e11->psyn_set->insert(Terminal::p_less->Tag());
	p_e11->psyn_set->insert(Terminal::p_le->Tag());
	p_e11->psyn_set->insert(Terminal::p_greater->Tag());
	p_e11->psyn_set->insert(Terminal::p_ge->Tag());
	p_e11->psyn_set->insert(Terminal::p_eq->Tag());
	p_e11->psyn_set->insert(Terminal::p_ne->Tag());
	p_e11->psyn_set->insert(Terminal::p_b_and->Tag());
	p_e11->psyn_set->insert(Terminal::p_b_xor->Tag());
	p_e11->psyn_set->insert(Terminal::p_b_or->Tag());
	p_e11->psyn_set->insert(Terminal::p_log_and->Tag());
	p_e11->psyn_set->insert(Terminal::p_log_or->Tag());
	p_e11->psyn_set->insert(Terminal::p_question->Tag());

	//{',','}',;,:,),]}
	p_e11->psyn_set->insert(Terminal::p_comma->Tag());
	//p_e11->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	//p_e11->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_e11->psyn_set->insert(Terminal::p_colon->Tag());
	p_e11->psyn_set->insert(Terminal::p_r_bracket->Tag());
	p_e11->psyn_set->insert(Terminal::p_r_s_bracket->Tag());

	//first(stmt)
	p_e11->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_e11->psyn_set->insert(Terminal::p_l_f_bracket->Tag());

	p_e11->psyn_set->insert(Terminal::p_b_not->Tag());
	p_e11->psyn_set->insert(Terminal::p_log_not->Tag());
	p_e11->psyn_set->insert(Terminal::p_add->Tag());
	p_e11->psyn_set->insert(Terminal::p_sub->Tag());
	p_e11->psyn_set->insert(Terminal::p_true->Tag());

	p_e11->psyn_set->insert(Terminal::p_false->Tag());
	p_e11->psyn_set->insert(Terminal::p_ascii->Tag());
	p_e11->psyn_set->insert(Terminal::p_number->Tag());
	p_e11->psyn_set->insert(Terminal::p_real->Tag());
	p_e11->psyn_set->insert(Terminal::p_plus_plus->Tag());

	p_e11->psyn_set->insert(Terminal::p_minus_minus->Tag());
	p_e11->psyn_set->insert(Terminal::p_l_bracket->Tag());
	p_e11->psyn_set->insert(Terminal::p_id->Tag());

	p_e11->psyn_set->insert(Terminal::p_if->Tag());
	p_e11->psyn_set->insert(Terminal::p_while->Tag());	
	p_e11->psyn_set->insert(Terminal::p_do->Tag());
	p_e11->psyn_set->insert(Terminal::p_break->Tag());
	p_e11->psyn_set->insert(Terminal::p_continue->Tag());	

	p_e11->psyn_set->insert(Terminal::p_return->Tag());
	p_e11->psyn_set->insert(Terminal::p_for->Tag());
	p_e11->psyn_set->insert(Terminal::p_switch->Tag());	
	p_e11->psyn_set->insert(Terminal::p_case->Tag());
	p_e11->psyn_set->insert(Terminal::p_default->Tag());

	// {'}',$}
	p_e11->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	p_e11->psyn_set->insert(Terminal::p_end->Tag());

	//...

	//{+,-,<<,>>,<,<=,>,>=,==,!=,&,^,|,&&,||,?}
	p_e12->psyn_set->insert(Terminal::p_add->Tag());
	p_e12->psyn_set->insert(Terminal::p_sub->Tag());
	p_e12->psyn_set->insert(Terminal::p_l_sht->Tag());
	p_e12->psyn_set->insert(Terminal::p_r_sht->Tag());
	p_e12->psyn_set->insert(Terminal::p_less->Tag());
	p_e12->psyn_set->insert(Terminal::p_le->Tag());
	p_e12->psyn_set->insert(Terminal::p_greater->Tag());
	p_e12->psyn_set->insert(Terminal::p_ge->Tag());
	p_e12->psyn_set->insert(Terminal::p_eq->Tag());
	p_e12->psyn_set->insert(Terminal::p_ne->Tag());
	p_e12->psyn_set->insert(Terminal::p_b_and->Tag());
	p_e12->psyn_set->insert(Terminal::p_b_xor->Tag());
	p_e12->psyn_set->insert(Terminal::p_b_or->Tag());
	p_e12->psyn_set->insert(Terminal::p_log_and->Tag());
	p_e12->psyn_set->insert(Terminal::p_log_or->Tag());
	p_e12->psyn_set->insert(Terminal::p_question->Tag());

	//{',','}',;,:,),]}
	p_e12->psyn_set->insert(Terminal::p_comma->Tag());
	//p_e12->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	//p_e12->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_e12->psyn_set->insert(Terminal::p_colon->Tag());
	p_e12->psyn_set->insert(Terminal::p_r_bracket->Tag());
	p_e12->psyn_set->insert(Terminal::p_r_s_bracket->Tag());

	//first(stmt)
	p_e12->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_e12->psyn_set->insert(Terminal::p_l_f_bracket->Tag());

	p_e12->psyn_set->insert(Terminal::p_b_not->Tag());
	p_e12->psyn_set->insert(Terminal::p_log_not->Tag());
	p_e12->psyn_set->insert(Terminal::p_add->Tag());
	p_e12->psyn_set->insert(Terminal::p_sub->Tag());
	p_e12->psyn_set->insert(Terminal::p_true->Tag());

	p_e12->psyn_set->insert(Terminal::p_false->Tag());
	p_e12->psyn_set->insert(Terminal::p_ascii->Tag());
	p_e12->psyn_set->insert(Terminal::p_number->Tag());
	p_e12->psyn_set->insert(Terminal::p_real->Tag());
	p_e12->psyn_set->insert(Terminal::p_plus_plus->Tag());

	p_e12->psyn_set->insert(Terminal::p_minus_minus->Tag());
	p_e12->psyn_set->insert(Terminal::p_l_bracket->Tag());
	p_e12->psyn_set->insert(Terminal::p_id->Tag());

	p_e12->psyn_set->insert(Terminal::p_if->Tag());
	p_e12->psyn_set->insert(Terminal::p_while->Tag());	
	p_e12->psyn_set->insert(Terminal::p_do->Tag());
	p_e12->psyn_set->insert(Terminal::p_break->Tag());
	p_e12->psyn_set->insert(Terminal::p_continue->Tag());	

	p_e12->psyn_set->insert(Terminal::p_return->Tag());
	p_e12->psyn_set->insert(Terminal::p_for->Tag());
	p_e12->psyn_set->insert(Terminal::p_switch->Tag());	
	p_e12->psyn_set->insert(Terminal::p_case->Tag());
	p_e12->psyn_set->insert(Terminal::p_default->Tag());

	// {'}',$}
	p_e12->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	p_e12->psyn_set->insert(Terminal::p_end->Tag());

	//...

	//{*,/,%,+,-,<<,>>,<,<=,>,>=,==,!=,&,^,|,&&,||,?}
	p_e13->psyn_set->insert(Terminal::p_mul->Tag());
	p_e13->psyn_set->insert(Terminal::p_div->Tag());
	p_e13->psyn_set->insert(Terminal::p_mod->Tag());
	p_e13->psyn_set->insert(Terminal::p_add->Tag());
	p_e13->psyn_set->insert(Terminal::p_sub->Tag());
	p_e13->psyn_set->insert(Terminal::p_l_sht->Tag());
	p_e13->psyn_set->insert(Terminal::p_r_sht->Tag());
	p_e13->psyn_set->insert(Terminal::p_less->Tag());
	p_e13->psyn_set->insert(Terminal::p_le->Tag());
	p_e13->psyn_set->insert(Terminal::p_greater->Tag());
	p_e13->psyn_set->insert(Terminal::p_ge->Tag());
	p_e13->psyn_set->insert(Terminal::p_eq->Tag());
	p_e13->psyn_set->insert(Terminal::p_ne->Tag());
	p_e13->psyn_set->insert(Terminal::p_b_and->Tag());
	p_e13->psyn_set->insert(Terminal::p_b_xor->Tag());
	p_e13->psyn_set->insert(Terminal::p_b_or->Tag());
	p_e13->psyn_set->insert(Terminal::p_log_and->Tag());
	p_e13->psyn_set->insert(Terminal::p_log_or->Tag());
	p_e13->psyn_set->insert(Terminal::p_question->Tag());

	//{',','}',;,:,),]}
	p_e13->psyn_set->insert(Terminal::p_comma->Tag());
	//p_e13->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	//p_e13->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_e13->psyn_set->insert(Terminal::p_colon->Tag());
	p_e13->psyn_set->insert(Terminal::p_r_bracket->Tag());
	p_e13->psyn_set->insert(Terminal::p_r_s_bracket->Tag());

	//first(stmt)
	p_e13->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_e13->psyn_set->insert(Terminal::p_l_f_bracket->Tag());

	p_e13->psyn_set->insert(Terminal::p_b_not->Tag());
	p_e13->psyn_set->insert(Terminal::p_log_not->Tag());
	p_e13->psyn_set->insert(Terminal::p_add->Tag());
	p_e13->psyn_set->insert(Terminal::p_sub->Tag());
	p_e13->psyn_set->insert(Terminal::p_true->Tag());

	p_e13->psyn_set->insert(Terminal::p_false->Tag());
	p_e13->psyn_set->insert(Terminal::p_ascii->Tag());
	p_e13->psyn_set->insert(Terminal::p_number->Tag());
	p_e13->psyn_set->insert(Terminal::p_real->Tag());
	p_e13->psyn_set->insert(Terminal::p_plus_plus->Tag());

	p_e13->psyn_set->insert(Terminal::p_minus_minus->Tag());
	p_e13->psyn_set->insert(Terminal::p_l_bracket->Tag());
	p_e13->psyn_set->insert(Terminal::p_id->Tag());

	p_e13->psyn_set->insert(Terminal::p_if->Tag());
	p_e13->psyn_set->insert(Terminal::p_while->Tag());	
	p_e13->psyn_set->insert(Terminal::p_do->Tag());
	p_e13->psyn_set->insert(Terminal::p_break->Tag());
	p_e13->psyn_set->insert(Terminal::p_continue->Tag());	

	p_e13->psyn_set->insert(Terminal::p_return->Tag());
	p_e13->psyn_set->insert(Terminal::p_for->Tag());
	p_e13->psyn_set->insert(Terminal::p_switch->Tag());	
	p_e13->psyn_set->insert(Terminal::p_case->Tag());
	p_e13->psyn_set->insert(Terminal::p_default->Tag());

	// {'}',$}
	p_e13->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	p_e13->psyn_set->insert(Terminal::p_end->Tag());

	//...

	//{*,/,%,+,-,<<,>>,<,<=,>,>=,==,!=,&,^,|,&&,||,?}
	p_e14->psyn_set->insert(Terminal::p_mul->Tag());
	p_e14->psyn_set->insert(Terminal::p_div->Tag());
	p_e14->psyn_set->insert(Terminal::p_mod->Tag());
	p_e14->psyn_set->insert(Terminal::p_add->Tag());
	p_e14->psyn_set->insert(Terminal::p_sub->Tag());
	p_e14->psyn_set->insert(Terminal::p_l_sht->Tag());
	p_e14->psyn_set->insert(Terminal::p_r_sht->Tag());
	p_e14->psyn_set->insert(Terminal::p_less->Tag());
	p_e14->psyn_set->insert(Terminal::p_le->Tag());
	p_e14->psyn_set->insert(Terminal::p_greater->Tag());
	p_e14->psyn_set->insert(Terminal::p_ge->Tag());
	p_e14->psyn_set->insert(Terminal::p_eq->Tag());
	p_e14->psyn_set->insert(Terminal::p_ne->Tag());
	p_e14->psyn_set->insert(Terminal::p_b_and->Tag());
	p_e14->psyn_set->insert(Terminal::p_b_xor->Tag());
	p_e14->psyn_set->insert(Terminal::p_b_or->Tag());
	p_e14->psyn_set->insert(Terminal::p_log_and->Tag());
	p_e14->psyn_set->insert(Terminal::p_log_or->Tag());
	p_e14->psyn_set->insert(Terminal::p_question->Tag());

	//{',','}',;,:,),]}
	p_e14->psyn_set->insert(Terminal::p_comma->Tag());
	//p_e14->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	//p_e14->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_e14->psyn_set->insert(Terminal::p_colon->Tag());
	p_e14->psyn_set->insert(Terminal::p_r_bracket->Tag());
	p_e14->psyn_set->insert(Terminal::p_r_s_bracket->Tag());

	//first(stmt)
	p_e14->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_e14->psyn_set->insert(Terminal::p_l_f_bracket->Tag());

	p_e14->psyn_set->insert(Terminal::p_b_not->Tag());
	p_e14->psyn_set->insert(Terminal::p_log_not->Tag());
	p_e14->psyn_set->insert(Terminal::p_add->Tag());
	p_e14->psyn_set->insert(Terminal::p_sub->Tag());
	p_e14->psyn_set->insert(Terminal::p_true->Tag());

	p_e14->psyn_set->insert(Terminal::p_false->Tag());
	p_e14->psyn_set->insert(Terminal::p_ascii->Tag());
	p_e14->psyn_set->insert(Terminal::p_number->Tag());
	p_e14->psyn_set->insert(Terminal::p_real->Tag());
	p_e14->psyn_set->insert(Terminal::p_plus_plus->Tag());

	p_e14->psyn_set->insert(Terminal::p_minus_minus->Tag());
	p_e14->psyn_set->insert(Terminal::p_l_bracket->Tag());
	p_e14->psyn_set->insert(Terminal::p_id->Tag());

	p_e14->psyn_set->insert(Terminal::p_if->Tag());
	p_e14->psyn_set->insert(Terminal::p_while->Tag());	
	p_e14->psyn_set->insert(Terminal::p_do->Tag());
	p_e14->psyn_set->insert(Terminal::p_break->Tag());
	p_e14->psyn_set->insert(Terminal::p_continue->Tag());	

	p_e14->psyn_set->insert(Terminal::p_return->Tag());
	p_e14->psyn_set->insert(Terminal::p_for->Tag());
	p_e14->psyn_set->insert(Terminal::p_switch->Tag());	
	p_e14->psyn_set->insert(Terminal::p_case->Tag());
	p_e14->psyn_set->insert(Terminal::p_default->Tag());

	// {'}',$}
	p_e14->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	p_e14->psyn_set->insert(Terminal::p_end->Tag());

	//...

	//{)}
	p_args_->psyn_set->insert(Terminal::p_r_bracket->Tag());

	//first(stmt)
	p_args_->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_args_->psyn_set->insert(Terminal::p_l_f_bracket->Tag());

	p_args_->psyn_set->insert(Terminal::p_b_not->Tag());
	p_args_->psyn_set->insert(Terminal::p_log_not->Tag());
	p_args_->psyn_set->insert(Terminal::p_add->Tag());
	p_args_->psyn_set->insert(Terminal::p_sub->Tag());
	p_args_->psyn_set->insert(Terminal::p_true->Tag());

	p_args_->psyn_set->insert(Terminal::p_false->Tag());
	p_args_->psyn_set->insert(Terminal::p_ascii->Tag());
	p_args_->psyn_set->insert(Terminal::p_number->Tag());
	p_args_->psyn_set->insert(Terminal::p_real->Tag());
	p_args_->psyn_set->insert(Terminal::p_plus_plus->Tag());

	p_args_->psyn_set->insert(Terminal::p_minus_minus->Tag());
	p_args_->psyn_set->insert(Terminal::p_l_bracket->Tag());
	p_args_->psyn_set->insert(Terminal::p_id->Tag());

	p_args_->psyn_set->insert(Terminal::p_if->Tag());
	p_args_->psyn_set->insert(Terminal::p_while->Tag());	
	p_args_->psyn_set->insert(Terminal::p_do->Tag());
	p_args_->psyn_set->insert(Terminal::p_break->Tag());
	p_args_->psyn_set->insert(Terminal::p_continue->Tag());	

	p_args_->psyn_set->insert(Terminal::p_return->Tag());
	p_args_->psyn_set->insert(Terminal::p_for->Tag());
	p_args_->psyn_set->insert(Terminal::p_switch->Tag());	
	p_args_->psyn_set->insert(Terminal::p_case->Tag());
	p_args_->psyn_set->insert(Terminal::p_default->Tag());

	// {'}',$}
	p_args_->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	p_args_->psyn_set->insert(Terminal::p_end->Tag());

	//...

	//{',',)}
	p_arg->psyn_set->insert(Terminal::p_comma->Tag());
	p_arg->psyn_set->insert(Terminal::p_r_bracket->Tag());

	//first(stmt)
	p_arg->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_arg->psyn_set->insert(Terminal::p_l_f_bracket->Tag());

	p_arg->psyn_set->insert(Terminal::p_b_not->Tag());
	p_arg->psyn_set->insert(Terminal::p_log_not->Tag());
	p_arg->psyn_set->insert(Terminal::p_add->Tag());
	p_arg->psyn_set->insert(Terminal::p_sub->Tag());
	p_arg->psyn_set->insert(Terminal::p_true->Tag());

	p_arg->psyn_set->insert(Terminal::p_false->Tag());
	p_arg->psyn_set->insert(Terminal::p_ascii->Tag());
	p_arg->psyn_set->insert(Terminal::p_number->Tag());
	p_arg->psyn_set->insert(Terminal::p_real->Tag());
	p_arg->psyn_set->insert(Terminal::p_plus_plus->Tag());

	p_arg->psyn_set->insert(Terminal::p_minus_minus->Tag());
	p_arg->psyn_set->insert(Terminal::p_l_bracket->Tag());
	p_arg->psyn_set->insert(Terminal::p_id->Tag());

	p_arg->psyn_set->insert(Terminal::p_if->Tag());
	p_arg->psyn_set->insert(Terminal::p_while->Tag());	
	p_arg->psyn_set->insert(Terminal::p_do->Tag());
	p_arg->psyn_set->insert(Terminal::p_break->Tag());
	p_arg->psyn_set->insert(Terminal::p_continue->Tag());	

	p_arg->psyn_set->insert(Terminal::p_return->Tag());
	p_arg->psyn_set->insert(Terminal::p_for->Tag());
	p_arg->psyn_set->insert(Terminal::p_switch->Tag());	
	p_arg->psyn_set->insert(Terminal::p_case->Tag());
	p_arg->psyn_set->insert(Terminal::p_default->Tag());

	// {'}',$}
	p_arg->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	p_arg->psyn_set->insert(Terminal::p_end->Tag());

	//...

	//{*,/,%,+,-,<<,>>,<,<=,>,>=,==,!=,&,^,|,&&,||,?}
	p_loc->psyn_set->insert(Terminal::p_mul->Tag());
	p_loc->psyn_set->insert(Terminal::p_div->Tag());
	p_loc->psyn_set->insert(Terminal::p_mod->Tag());
	p_loc->psyn_set->insert(Terminal::p_add->Tag());
	p_loc->psyn_set->insert(Terminal::p_sub->Tag());
	p_loc->psyn_set->insert(Terminal::p_l_sht->Tag());
	p_loc->psyn_set->insert(Terminal::p_r_sht->Tag());
	p_loc->psyn_set->insert(Terminal::p_less->Tag());
	p_loc->psyn_set->insert(Terminal::p_le->Tag());
	p_loc->psyn_set->insert(Terminal::p_greater->Tag());
	p_loc->psyn_set->insert(Terminal::p_ge->Tag());
	p_loc->psyn_set->insert(Terminal::p_eq->Tag());
	p_loc->psyn_set->insert(Terminal::p_ne->Tag());
	p_loc->psyn_set->insert(Terminal::p_b_and->Tag());
	p_loc->psyn_set->insert(Terminal::p_b_xor->Tag());
	p_loc->psyn_set->insert(Terminal::p_b_or->Tag());
	p_loc->psyn_set->insert(Terminal::p_log_and->Tag());
	p_loc->psyn_set->insert(Terminal::p_log_or->Tag());
	p_loc->psyn_set->insert(Terminal::p_question->Tag());

	//{',','}',;,:,),]}
	p_loc->psyn_set->insert(Terminal::p_comma->Tag());
	//p_loc->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	//p_loc->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_loc->psyn_set->insert(Terminal::p_colon->Tag());
	p_loc->psyn_set->insert(Terminal::p_r_bracket->Tag());
	p_loc->psyn_set->insert(Terminal::p_r_s_bracket->Tag());

	//first(stmt)
	p_loc->psyn_set->insert(Terminal::p_semicolon->Tag());
	p_loc->psyn_set->insert(Terminal::p_l_f_bracket->Tag());

	p_loc->psyn_set->insert(Terminal::p_b_not->Tag());
	p_loc->psyn_set->insert(Terminal::p_log_not->Tag());
	p_loc->psyn_set->insert(Terminal::p_add->Tag());
	p_loc->psyn_set->insert(Terminal::p_sub->Tag());
	p_loc->psyn_set->insert(Terminal::p_true->Tag());

	p_loc->psyn_set->insert(Terminal::p_false->Tag());
	p_loc->psyn_set->insert(Terminal::p_ascii->Tag());
	p_loc->psyn_set->insert(Terminal::p_number->Tag());
	p_loc->psyn_set->insert(Terminal::p_real->Tag());
	p_loc->psyn_set->insert(Terminal::p_plus_plus->Tag());

	p_loc->psyn_set->insert(Terminal::p_minus_minus->Tag());
	p_loc->psyn_set->insert(Terminal::p_l_bracket->Tag());
	p_loc->psyn_set->insert(Terminal::p_id->Tag());

	p_loc->psyn_set->insert(Terminal::p_if->Tag());
	p_loc->psyn_set->insert(Terminal::p_while->Tag());	
	p_loc->psyn_set->insert(Terminal::p_do->Tag());
	p_loc->psyn_set->insert(Terminal::p_break->Tag());
	p_loc->psyn_set->insert(Terminal::p_continue->Tag());	

	p_loc->psyn_set->insert(Terminal::p_return->Tag());
	p_loc->psyn_set->insert(Terminal::p_for->Tag());
	p_loc->psyn_set->insert(Terminal::p_switch->Tag());	
	p_loc->psyn_set->insert(Terminal::p_case->Tag());
	p_loc->psyn_set->insert(Terminal::p_default->Tag());

	// {'}',$}
	p_loc->psyn_set->insert(Terminal::p_r_f_bracket->Tag());
	p_loc->psyn_set->insert(Terminal::p_end->Tag());
}