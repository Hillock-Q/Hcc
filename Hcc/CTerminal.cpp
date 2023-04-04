#include "CTerminal.h"
#include "CTag.h"
#include "CHillock.h"
#include "CActionFunction.h"


Terminal::t_pt Terminal::p_main=0;				//	main
Terminal::t_pt Terminal::p_l_bracket=0;			//	(
Terminal::t_pt Terminal::p_r_bracket=0;			//	)
Terminal::t_pt Terminal::p_l_f_bracket=0;		//	{
Terminal::t_pt Terminal::p_r_f_bracket=0;		//	}

Terminal::t_pt Terminal::p_void=0;				//	void
Terminal::t_pt Terminal::p_id=0;				//	id
Terminal::t_pt Terminal::p_semicolon=0;			//	;
Terminal::t_pt Terminal::p_bool=0;				//	bool
Terminal::t_pt Terminal::p_char=0;				//	char

Terminal::t_pt Terminal::p_short=0;				//	short
Terminal::t_pt Terminal::p_int=0;				//	int
Terminal::t_pt Terminal::p_float=0;				//	float
Terminal::t_pt Terminal::p_double;				//	double
Terminal::t_pt Terminal::p_l_s_bracket=0;		//	[

Terminal::t_pt Terminal::p_r_s_bracket=0;		//	]
Terminal::t_pt Terminal::p_assign=0;			//	=
Terminal::t_pt Terminal::p_comma=0;				//	,
Terminal::t_pt Terminal::p_colon=0;				//	:
Terminal::t_pt Terminal::p_if=0;				//	if

Terminal::t_pt Terminal::p_while=0;				//	while
Terminal::t_pt Terminal::p_do=0;				//	do
Terminal::t_pt Terminal::p_break=0;				//	break
Terminal::t_pt Terminal::p_continue=0;			//	continue
Terminal::t_pt Terminal::p_return=0;			//	return

Terminal::t_pt Terminal::p_for=0;				//	for
Terminal::t_pt Terminal::p_switch=0;			//	switch
Terminal::t_pt Terminal::p_case=0;				//	case
Terminal::t_pt Terminal::p_default=0;			//	default
Terminal::t_pt Terminal::p_else=0;				//	else

Terminal::t_pt Terminal::p_b_and_ass=0;			//	&=
Terminal::t_pt Terminal::p_b_or_ass=0;			//	|=
Terminal::t_pt Terminal::p_b_xor_ass=0;			//	^=
Terminal::t_pt Terminal::p_l_sht_ass=0;			//	<<=
Terminal::t_pt Terminal::p_r_sht_ass=0;			//	>>=

Terminal::t_pt Terminal::p_add_ass=0;			//	+=
Terminal::t_pt Terminal::p_sub_ass=0;			//	-=
Terminal::t_pt Terminal::p_mul_ass=0;			//	*=
Terminal::t_pt Terminal::p_div_ass=0;			//	/=
Terminal::t_pt Terminal::p_mod_ass=0;			//	%=

Terminal::t_pt Terminal::p_plus_plus=0;			//	++
Terminal::t_pt Terminal::p_minus_minus=0;		//	--
Terminal::t_pt Terminal::p_question=0;			//	?
Terminal::t_pt Terminal::p_log_or=0;			//	||
Terminal::t_pt Terminal::p_log_and=0;			//	&&

Terminal::t_pt Terminal::p_b_or=0;				//	|
Terminal::t_pt Terminal::p_b_xor=0;				//	^
Terminal::t_pt Terminal::p_b_and=0;				//	&
Terminal::t_pt Terminal::p_eq=0;				//	==
Terminal::t_pt Terminal::p_ne=0;				//	!=

Terminal::t_pt Terminal::p_less=0;				//	<
Terminal::t_pt Terminal::p_le=0;				//	<=
Terminal::t_pt Terminal::p_greater=0;			//	>
Terminal::t_pt Terminal::p_ge=0;				//	>=
Terminal::t_pt Terminal::p_l_sht=0;				//	<<

Terminal::t_pt Terminal::p_r_sht=0;				//	>>
Terminal::t_pt Terminal::p_add=0;				//	+
Terminal::t_pt Terminal::p_sub=0;				//	-
Terminal::t_pt Terminal::p_mul=0;				//	*
Terminal::t_pt Terminal::p_div=0;				//	/

Terminal::t_pt Terminal::p_mod=0;				//	%
Terminal::t_pt Terminal::p_b_not=0;				//	~
Terminal::t_pt Terminal::p_log_not=0;			//	!
Terminal::t_pt Terminal::p_true=0;				//	true
Terminal::t_pt Terminal::p_false=0;				//	false

Terminal::t_pt Terminal::p_ascii=0;				//	ascii
Terminal::t_pt Terminal::p_number=0;			//	number
Terminal::t_pt Terminal::p_real=0;				//	real
Terminal::t_pt Terminal::p_end=0;				//	$

void Terminal::Generate()
{
	using namespace Compiler;

	p_main			=	new Terminal(Compiler::_MAIN,new string("main"),act_main);				//	main
	p_l_bracket		=	new Terminal('(',new string("("));										//	(
	p_r_bracket		=	new Terminal(')',new string(")"));										//	)
	p_l_f_bracket	=	new Terminal('{',new string("{"));										//	{
	p_r_f_bracket	=	new Terminal('}',new string("}"));										//	}

	p_void			=	new Terminal(Compiler::_VOID,new string("void"));						//	void
	p_id			=	new Terminal(Compiler::_ID,new string("id"),act_id);					//	id
	p_semicolon		=	new Terminal(';',new string(";"));										//	;
	p_bool			=	new Terminal(Compiler::_BOOL,new string("bool"),act_bool);				//	bool
	p_char			=	new Terminal(Compiler::_CHAR,new string("char"),act_char);				//	char

	p_short			=	new Terminal(Compiler::_SHORT,new string("short"),act_short);			//	short
	p_int			=	new Terminal(Compiler::_INT,new string("int"),act_int);					//	int
	p_float			=	new Terminal(Compiler::_FLOAT,new string("float"),act_float);			//	float
	p_double		=	new Terminal(Compiler::_DOUBLE,new string("double"),act_double);		//	double
	p_l_s_bracket	=	new Terminal('[',new string("["));										//	[

	p_r_s_bracket	=	new Terminal(']',new string("]"));										//	]
	p_assign		=	new Terminal('=',new string("="),act_op);								//	=
	p_comma			=	new Terminal(',',new string(","));										//	,
	p_colon			=	new Terminal(':',new string(":"),act_op);								//	:
	p_if			=	new Terminal(Compiler::_IF,new string("if"),act_if);					//	if

	p_while			=	new Terminal(Compiler::_WHILE,new string("while"),act_while);			//	while
	p_do			=	new Terminal(Compiler::_DO,new string("do"));							//	do
	p_break			=	new Terminal(Compiler::_BREAK,new string("break"),act_break);			//	break
	p_continue		=	new Terminal(Compiler::_CONTINUE,new string("continue"),act_continue);	//	continue
	p_return		=	new Terminal(Compiler::_RETURN,new string("return"),act_return);		//	return

	p_for			=	new Terminal(Compiler::_FOR,new string("for"),act_for);					//	for
	p_switch		=	new Terminal(Compiler::_SWITCH,new string("switch"),act_switch);		//	switch
	p_case			=	new Terminal(Compiler::_CASE,new string("case"));						//	case
	p_default		=	new Terminal(Compiler::_DEFAULT,new string("default"));					//	default
	p_else			=	new Terminal(Compiler::_ELSE,new string("else"));						//	else

	p_b_and_ass		=	new Terminal(Compiler::_BIT_AND_ASS,new string("&="),act_op);			//	&=
	p_b_or_ass		=	new Terminal(Compiler::_BIT_OR_ASS,new string("|="),act_op);			//	|=
	p_b_xor_ass		=	new Terminal(Compiler::_BIT_XOR_ASS,new string("^="),act_op);			//	^=
	p_l_sht_ass		=	new Terminal(Compiler::_LSHT_ASS,new string("<<="),act_op);				//	<<=
	p_r_sht_ass		=	new Terminal(Compiler::_RSHT_ASS,new string(">>="),act_op);				//	>>=

	p_add_ass		=	new Terminal(Compiler::_ADD_ASS,new string("+="),act_op);				//	+=
	p_sub_ass		=	new Terminal(Compiler::_SUB_ASS,new string("-="),act_op);				//	-=
	p_mul_ass		=	new Terminal(Compiler::_MUL_ASS,new string("*="),act_op);				//	*=
	p_div_ass		=	new Terminal(Compiler::_DIV_ASS,new string("/="),act_op);				//	/=
	p_mod_ass		=	new Terminal(Compiler::_MOD_ASS,new string("%="),act_op);				//	%=

	p_plus_plus		=	new Terminal(Compiler::_PLUS_PLUS,new string("++"));					//	++
	p_minus_minus	=	new Terminal(Compiler::_MINUS_MINUS,new string("--"));					//	--
	p_question		=	new Terminal('\?',new string("\?"),act_op);								//	?
	p_log_or		=	new Terminal(Compiler::_OR,new string("||"),act_op);					//	||
	p_log_and		=	new Terminal(Compiler::_AND,new string("&&"),act_op);					//	&&

	p_b_or			=	new Terminal('|',new string("|"),act_op);								//	|
	p_b_xor			=	new Terminal('^',new string("^"),act_op);								//	^
	p_b_and			=	new Terminal('&',new string("&"),act_op);								//	&
	p_eq			=	new Terminal(Compiler::_EQ,new string("=="),act_op);					//	==
	p_ne			=	new Terminal(Compiler::_NE,new string("!="),act_op);					//	!=

	p_less			=	new Terminal('<',new string("<"),act_op);								//	<
	p_le			=	new Terminal(Compiler::_LE,new string("<="),act_op);					//	<=
	p_greater		=	new Terminal('>',new string(">"),act_op);								//	>
	p_ge			=	new Terminal(Compiler::_GE,new string(">="),act_op);					//	>=
	p_l_sht			=	new Terminal(Compiler::_LSHT,new string("<<"),act_op);					//	<<

	p_r_sht			=	new Terminal(Compiler::_RSHT,new string(">>"),act_op);					//	>>
	p_add			=	new Terminal('+',new string("+"),act_op);								//	+
	p_sub			=	new Terminal('-',new string("-"),act_op);								//	-
	p_mul			=	new Terminal('*',new string("*"),act_op);								//	*
	p_div			=	new Terminal('/',new string("/"),act_op);								//	/

	p_mod			=	new Terminal('%',new string("%"),act_op);								//	%
	p_b_not			=	new Terminal('~',new string("~"),act_op);								//	~
	p_log_not		=	new Terminal('!',new string("!"),act_op);								//	!
	p_true			=	new Terminal(Compiler::_TRUE,new string("true"),act_true);				//	true
	p_false			=	new Terminal(Compiler::_FALSE,new string("false"),act_false);			//	false

	p_ascii			=	new Terminal(Compiler::_ASCII,new string("ascii"),act_ascii);			//	ascii
	p_number		=	new Terminal(Compiler::_NUM,new string("number"),act_number);			//	number
	p_real			=	new Terminal(Compiler::_REAL,new string("real"),act_real);				//	real
	p_end			=	new Terminal(Compiler::_END,new string("$"));							//	$	
}
void Terminal::Destroy()
{
	delete p_main->perr_str;
	delete p_main;			//	main
	delete p_l_bracket->perr_str;
	delete p_l_bracket;		//	(
	delete p_r_bracket->perr_str;
	delete p_r_bracket;		//	)
	delete p_l_f_bracket->perr_str;
	delete p_l_f_bracket;	//	{
	delete p_r_f_bracket->perr_str;
	delete p_r_f_bracket;	//	}

	delete p_void->perr_str;
	delete p_void;			//	void
	delete p_id->perr_str;
	delete p_id;			//	id
	delete p_semicolon->perr_str;
	delete p_semicolon;		//	;
	delete p_bool->perr_str;
	delete p_bool;			//	bool
	delete p_char->perr_str;
	delete p_char;			//	char

	delete p_short->perr_str;
	delete p_short;			//	short
	delete p_int->perr_str;
	delete p_int;			//	int
	delete p_float->perr_str;
	delete p_float;			//	float
	delete p_double->perr_str;
	delete p_double;		//	double
	delete p_l_s_bracket->perr_str;
	delete p_l_s_bracket;	//	[

	delete p_r_s_bracket->perr_str;
	delete p_r_s_bracket;	//	]
	delete p_assign->perr_str;
	delete p_assign;		//	=
	delete p_comma->perr_str;
	delete p_comma;			//	,
	delete p_colon->perr_str;
	delete p_colon;			//	:
	delete p_if->perr_str;
	delete p_if;			//	if

	delete p_while->perr_str;
	delete p_while;			//	while
	delete p_do->perr_str;
	delete p_do;			//	do
	delete p_break->perr_str;
	delete p_break;			//	break
	delete p_continue->perr_str;
	delete p_continue;		//	continue
	delete p_return->perr_str;
	delete p_return;		//	return

	delete p_for->perr_str;
	delete p_for;			//	for
	delete p_switch->perr_str;
	delete p_switch;		//	switch
	delete p_case->perr_str;
	delete p_case;			//	case
	delete p_default->perr_str;
	delete p_default;		//	default
	delete p_else->perr_str;
	delete p_else;			//	else

	delete p_b_and_ass->perr_str;
	delete p_b_and_ass;		//	&=
	delete p_b_or_ass->perr_str;
	delete p_b_or_ass;		//	|=
	delete p_b_xor_ass->perr_str;
	delete p_b_xor_ass;		//	^=
	delete p_l_sht_ass->perr_str;
	delete p_l_sht_ass;		//	<<=
	delete p_r_sht_ass->perr_str;
	delete p_r_sht_ass;		//	>>=

	delete p_add_ass->perr_str;
	delete p_add_ass;		//	+=
	delete p_sub_ass->perr_str;
	delete p_sub_ass;		//	-=
	delete p_mul_ass->perr_str;
	delete p_mul_ass;		//	*=
	delete p_div_ass->perr_str;
	delete p_div_ass;		//	/=
	delete p_mod_ass->perr_str;
	delete p_mod_ass;		//	%=

	delete p_plus_plus->perr_str;
	delete p_plus_plus;		//	++
	delete p_minus_minus->perr_str;
	delete p_minus_minus;	//	--
	delete p_question->perr_str;
	delete p_question;		//	?
	delete p_log_or->perr_str;
	delete p_log_or;		//	||
	delete p_log_and->perr_str;
	delete p_log_and;		//	&&

	delete p_b_or->perr_str;
	delete p_b_or;			//	|
	delete p_b_xor->perr_str;
	delete p_b_xor;			//	^
	delete p_b_and->perr_str;
	delete p_b_and;			//	&
	delete p_eq->perr_str;
	delete p_eq;			//	==
	delete p_ne->perr_str;
	delete p_ne;			//	!=

	delete p_less->perr_str;
	delete p_less;			//	<
	delete p_le->perr_str;
	delete p_le;			//	<=
	delete p_greater->perr_str;
	delete p_greater;		//	>
	delete p_ge->perr_str;
	delete p_ge;			//	>=
	delete p_l_sht->perr_str;
	delete p_l_sht;			//	<<

	delete p_r_sht->perr_str;
	delete p_r_sht;			//	>>
	delete p_add->perr_str;
	delete p_add;			//	+
	delete p_sub->perr_str;
	delete p_sub;			//	-
	delete p_mul->perr_str;
	delete p_mul;			//	*
	delete p_div->perr_str;
	delete p_div;			//	/

	delete p_mod->perr_str;
	delete p_mod;			//	%
	delete p_b_not->perr_str;
	delete p_b_not;			//	~
	delete p_log_not->perr_str;
	delete p_log_not;		//	!
	delete p_true->perr_str;
	delete p_true;			//	true
	delete p_false->perr_str;
	delete p_false;			//	false

	delete p_ascii->perr_str;
	delete p_ascii;			//	ascii
	delete p_number->perr_str;
	delete p_number;		//	number
	delete p_real->perr_str;
	delete p_real;			//	real
	delete p_end->perr_str;
	delete p_end;			//	$	
}
inline string Terminal::getError(Token const *ptoken)const
{
	return "在\""+ptoken->toString()+"\"之前缺少\""+*perr_str+"\"。";
}