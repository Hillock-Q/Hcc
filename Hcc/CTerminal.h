#pragma once

#include "CSign.h"
#include "CToken.h"
#include <string>
using std::string;

class Terminal:public Sign
{	
	typedef Terminal* t_pt;

public:
	static t_pt p_main;				//	main
	static t_pt p_l_bracket;		//	(
	static t_pt p_r_bracket;		//	)
	static t_pt p_l_f_bracket;		//	{
	static t_pt p_r_f_bracket;		//	}

	static t_pt p_void;				//	void
	static t_pt p_id;				//	id
	static t_pt p_semicolon;		//	;
	static t_pt p_bool;				//	bool
	static t_pt p_char;				//	char

	static t_pt p_short;			//	short
	static t_pt p_int;				//	int
	static t_pt p_float;			//	float
	static t_pt p_double;			//	double
	static t_pt p_l_s_bracket;		//	[

	static t_pt p_r_s_bracket;		//	]
	static t_pt p_assign;			//	=
	static t_pt p_comma;			//	,
	static t_pt p_colon;			//	:
	static t_pt p_if;				//	if

	static t_pt p_while;			//	while
	static t_pt p_do;				//	do
	static t_pt p_break;			//	break
	static t_pt p_continue;			//	continue
	static t_pt p_return;			//	return

	static t_pt p_for;				//	for
	static t_pt p_switch;			//	switch
	static t_pt p_case;				//	case
	static t_pt p_default;			//	default
	static t_pt p_else;				//	else

	static t_pt p_b_and_ass;		//	&=
	static t_pt p_b_or_ass;			//	|=
	static t_pt p_b_xor_ass;		//	^=
	static t_pt p_l_sht_ass;		//	<<=
	static t_pt p_r_sht_ass;		//	>>=

	static t_pt p_add_ass;			//	+=
	static t_pt p_sub_ass;			//	-=
	static t_pt p_mul_ass;			//	*=
	static t_pt p_div_ass;			//	/=
	static t_pt p_mod_ass;			//	%=

	static t_pt p_plus_plus;		//	++
	static t_pt p_minus_minus;		//	--
	static t_pt p_question;			//	?
	static t_pt p_log_or;			//	||
	static t_pt p_log_and;			//	&&

	static t_pt p_b_or;				//	|
	static t_pt p_b_xor;			//	^
	static t_pt p_b_and;			//	&
	static t_pt p_eq;				//	==
	static t_pt p_ne;				//	!=

	static t_pt p_less;				//	<
	static t_pt p_le;				//	<=
	static t_pt p_greater;			//	>
	static t_pt p_ge;				//	>=
	static t_pt p_l_sht;			//	<<

	static t_pt p_r_sht;			//	>>
	static t_pt p_add;				//	+
	static t_pt p_sub;				//	-
	static t_pt p_mul;				//	*
	static t_pt p_div;				//	/

	static t_pt p_mod;				//	%
	static t_pt p_b_not;			//	~
	static t_pt p_log_not;			//	!
	static t_pt p_true;				//	true
	static t_pt p_false;			//	false

	static t_pt p_ascii;			//	ascii
	static t_pt p_number;			//	number
	static t_pt p_real;				//	real
	static t_pt p_end;				//	$	

public:
	Terminal(int const t,string *pstr=0,ActionFun act=0):Sign(t),perr_str(pstr),actFun(act){}

	//copy constructor
	Terminal(Terminal const &rhs):Sign(rhs),perr_str(rhs.perr_str),actFun(rhs.actFun){}

	//redefine	
	~Terminal(){}

	//redefine
	void release(){}

	//redefine	
	bool isTerminal()const{return true;}

	//redefine	
	string getError(Token const *ptoken)const;

	//redefine
	void Action(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken){if(actFun)actFun(pps,err_record,context,byte_code,cpToken);}

	//redefine	
	Terminal* clone(CopyFun copy=0,Inh_Attr *pInh=0,DelInh deli=0,ActionFun act=0,Temp_Var *pTemp=0,DelTemp delt=0,Syn_Attr *pSyn=0,DelSyn dels=0)const{return new Terminal(*this);}

	static void Generate();
	static void Destroy();

private:
	string const *perr_str;		//error report
	ActionFun actFun;
};