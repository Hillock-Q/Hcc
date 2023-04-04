#pragma once

namespace Compiler
{
	const unsigned BASE=255;
	const unsigned NON_TERMINAL=60;

	enum Tag
	{
		//Key words: 13

		_BREAK		=	BASE+1,
		_CASE		=	BASE+2,
		_CONTINUE	=	BASE+3,
		_DEFAULT	=	BASE+4,
		_DO			=	BASE+5,

		_ELSE		=	BASE+6,
		_FALSE		=	BASE+7,
		_FOR		=	BASE+8,
		_IF			=	BASE+9,
		_RETURN		=	BASE+10,

		_SWITCH		=	BASE+11,
		_TRUE		=	BASE+12,
		_WHILE		=	BASE+13,


		//Multi-character operators: 20

		_LSHT		=	BASE+14,		// <<
		_RSHT		=	BASE+15,		// >>
		_LE			=	BASE+16,		// <=
		_GE			=	BASE+17,		// >=
		_EQ			=	BASE+18,		// ==

		_NE			=	BASE+19,		// !=
		_AND		=	BASE+20,		// &&
		_OR			=	BASE+21,		// ||
		_MUL_ASS	=	BASE+22,		// *=
		_DIV_ASS	=	BASE+23,		// /=

		_MOD_ASS	=	BASE+24,		// %=
		_ADD_ASS	=	BASE+25,		// +=
		_SUB_ASS	=	BASE+26,		// -=
		_LSHT_ASS	=	BASE+27,		// <<=
		_RSHT_ASS	=	BASE+28,		// >>=

		_BIT_AND_ASS=	BASE+29,		// &=
		_BIT_XOR_ASS=	BASE+30,		// ^=
		_BIT_OR_ASS	=	BASE+31,		// |=
		_PLUS_PLUS	=	BASE+32,		// ++
		_MINUS_MINUS=	BASE+33,		// --


		//Literal constants: 3

		_ASCII		=	BASE+34,			
		_NUM		=	BASE+35,
		_REAL		=	BASE+36,


		//Identifier: 1

		_ID			=	BASE+37,


		//Built-in type: 7

		_BOOL		=	BASE+38,
		_CHAR		=	BASE+39,
		_SHORT		=	BASE+40,
		_INT		=	BASE+41,
		_FLOAT		=	BASE+42,
		_DOUBLE		=	BASE+43,
		_VOID		=	BASE+44,


		//main : 1

		_MAIN		=	BASE+45,


		//终结标志

		_END		=	-1,


		//非文法符号标志

		_NON_SIGN	=	-2,


		//Non-terminal code: 64

		_program	=	BASE+NON_TERMINAL+1,

		_options	=	BASE+NON_TERMINAL+2,
		_option		=	BASE+NON_TERMINAL+3,
		_option_	=	BASE+NON_TERMINAL+4,

		_decls		=	BASE+NON_TERMINAL+5,
		_decl		=	BASE+NON_TERMINAL+6,
		_decl_		=	BASE+NON_TERMINAL+7,

		_b			=	BASE+NON_TERMINAL+8,

		_a			=	BASE+NON_TERMINAL+9,
		_opt1		=	BASE+NON_TERMINAL+10,
		_l			=	BASE+NON_TERMINAL+11,
		_l_			=	BASE+NON_TERMINAL+12,
		_l__		=	BASE+NON_TERMINAL+13,

		_v			=	BASE+NON_TERMINAL+14,
		_v_			=	BASE+NON_TERMINAL+15,
		_opt2		=	BASE+NON_TERMINAL+16,

		_f			=	BASE+NON_TERMINAL+17,
		_params		=	BASE+NON_TERMINAL+18,
		_params_	=	BASE+NON_TERMINAL+19,
		_params__	=	BASE+NON_TERMINAL+20,
		_param		=	BASE+NON_TERMINAL+21,
		_tail		=	BASE+NON_TERMINAL+22,
		_optexpr1	=	BASE+NON_TERMINAL+23,

		_stmt		=	BASE+NON_TERMINAL+24,
		_else		=	BASE+NON_TERMINAL+25,
		_stmts		=	BASE+NON_TERMINAL+26,
		_optexpr2	=	BASE+NON_TERMINAL+27,
		_optexpr3	=	BASE+NON_TERMINAL+28,
		_label		=	BASE+NON_TERMINAL+29,

		_expr		=	BASE+NON_TERMINAL+30,
		_expr_		=	BASE+NON_TERMINAL+31,

		_e1			=	BASE+NON_TERMINAL+32,

		_e2			=	BASE+NON_TERMINAL+33,
		_e2_		=	BASE+NON_TERMINAL+34,

		_e3			=	BASE+NON_TERMINAL+35,
		_e3_		=	BASE+NON_TERMINAL+36,

		_e4			=	BASE+NON_TERMINAL+37,
		_e4_		=	BASE+NON_TERMINAL+38,

		_e5			=	BASE+NON_TERMINAL+39,
		_e5_		=	BASE+NON_TERMINAL+40,

		_e6			=	BASE+NON_TERMINAL+41,
		_e6_		=	BASE+NON_TERMINAL+42,

		_e7			=	BASE+NON_TERMINAL+43,
		_e7_		=	BASE+NON_TERMINAL+44,

		_e8			=	BASE+NON_TERMINAL+45,
		_e8_		=	BASE+NON_TERMINAL+46,

		_e9			=	BASE+NON_TERMINAL+47,
		_e9_		=	BASE+NON_TERMINAL+48,

		_e10		=	BASE+NON_TERMINAL+49,
		_e10_		=	BASE+NON_TERMINAL+50,

		_e11		=	BASE+NON_TERMINAL+51,
		_e11_		=	BASE+NON_TERMINAL+52,

		_e12		=	BASE+NON_TERMINAL+53,
		_e12_		=	BASE+NON_TERMINAL+54,

		_e13		=	BASE+NON_TERMINAL+55,

		_e14		=	BASE+NON_TERMINAL+56,

		_t1			=	BASE+NON_TERMINAL+57,
		_t2			=	BASE+NON_TERMINAL+58,
		_t3			=	BASE+NON_TERMINAL+59,
		_t4			=	BASE+NON_TERMINAL+60,
		_t5			=	BASE+NON_TERMINAL+61,

		_args		=	BASE+NON_TERMINAL+62,
		_args_		=	BASE+NON_TERMINAL+63,
		_args__		=	BASE+NON_TERMINAL+64,
		_arg		=	BASE+NON_TERMINAL+65,

		_loc		=	BASE+NON_TERMINAL+66,
		_loc_		=	BASE+NON_TERMINAL+67,

		_size		=	BASE+NON_TERMINAL+68,
	};
}
