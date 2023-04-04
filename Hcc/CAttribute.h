#include <vector>
#include <list>
#include "CVarInfo.h"
#include "CAddress.h"

namespace Compiler
{	
	using std::pair;
	using std::string;
	using std::vector;
	using std::list;

	typedef size_t instr;
	typedef vector<instr> instr_list;
	typedef list<pair<bool,pair<Address,instr> > > var_instr_list;
	typedef vector<Address> arg_list;


	// inherited attribute

	typedef struct
	{
		VarInfo iType;		
		string* iLexime;
		size_t iLine;
	}Inh_Attr_F, Inh_Attr_option_;

	typedef struct 
	{
		unsigned char iSection;
		VarInfo iType;
		string* iLexime;
		size_t iLine;
	}Inh_Attr_decl_, Inh_Attr_A, Inh_Attr_V;

	typedef struct 
	{
		unsigned char iSection;
		string* iLexime;
	}Inh_Attr_opt1,Inh_Attr_L, Inh_Attr_opt2;

	typedef struct 
	{
		unsigned char iSection;
		string* iLexime;
		size_t iIndex;
	}Inh_Attr_L_, Inh_Attr_L__;

	struct Inh_Attr_V_
	{
		unsigned char iSection;
		VarInfo iType;	
	};

	struct Inh_Attr_tail
	{
		VarInfo iType;
		string* iLexime;
		size_t iLine;
	};

	typedef struct 
	{		
		Address iAddr;
		instr_list* ipBreakList;
		instr_list* ipContinueList;
		var_instr_list* ipVarInstrList;
	}Inh_Attr_stmt, Inh_Attr_stmts;

	struct Inh_Attr_E
	{		
		Address iAddr;
		instr_list* ipBreakList;
		instr_list* ipContinueList;
		var_instr_list* ipVarInstrList;
		instr_list* ipNextList;
		instr_list* ipFalseList;
	};

	struct Inh_Attr_optexpr2
	{
		bool iValFlag;
		size_t iLine;
	};

	struct Inh_Attr_optexpr3
	{
		size_t iLine;
	};

	typedef struct 
	{
		unsigned char iSection;		
	}Inh_Attr_expr
		, Inh_Attr_e1
		, Inh_Attr_e2
		, Inh_Attr_e3
		, Inh_Attr_e4
		, Inh_Attr_e5
		, Inh_Attr_e6
		, Inh_Attr_e7
		, Inh_Attr_e8
		, Inh_Attr_e9
		, Inh_Attr_e10
		, Inh_Attr_e11
		, Inh_Attr_e12
		, Inh_Attr_e13
		, Inh_Attr_e14;

	typedef struct 
	{
		unsigned char iSection;				
		bool iValFlag;
		VarInfo iType;
		Address iAddr;
		instr_list* ipTrueList;
		instr_list* ipFalseList;
	}Inh_Attr_expr_
		, Inh_Attr_e2_
		, Inh_Attr_e3_
		, Inh_Attr_e4_
		, Inh_Attr_e5_
		, Inh_Attr_e6_
		, Inh_Attr_e7_
		, Inh_Attr_e8_
		, Inh_Attr_e9_
		, Inh_Attr_e10_
		, Inh_Attr_e11_
		, Inh_Attr_e12_;

	struct Inh_Attr_loc
	{
		bool i_Inc;
		unsigned char iSection;
	};

	typedef struct 
	{
		unsigned char iSection;
		string* iLexime;
		size_t iLine;
	}Inh_Attr_T1, Inh_Attr_T3, Inh_Attr_args;

	typedef struct 
	{
		unsigned char iSection;
		Address iAddr;
		string* iLexime;
	}Inh_Attr_T2, Inh_Attr_T4;

	struct Inh_Attr_T5
	{
		unsigned char iSection;
		VarInfo iType;
		Address iAddr;
	};

	struct Inh_Attr_loc_
	{			
		bool i_Inc;
		unsigned char iSection;
		string* iLexime;
		size_t iLine;
	};

	typedef struct 
	{
		unsigned char iSection;
		string* iLexime;
		size_t iLine;
		size_t iCnt;
		arg_list* ipArgList;

	}Inh_Attr_args_, Inh_Attr_args__, Inh_Attr_arg;

	union Inh_Attr
	{
		//isomorphic
		Inh_Attr_F F;
		Inh_Attr_option_ option_;

		//isomorphic
		Inh_Attr_decl_ decl_;
		Inh_Attr_A A;
		Inh_Attr_V V;

		//isomorphic
		Inh_Attr_opt1 opt1;
		Inh_Attr_L L;
		Inh_Attr_opt2 opt2;

		//isomorphic
		Inh_Attr_L_ L_;
		Inh_Attr_L__ L__;

		Inh_Attr_V_ V_;	

		Inh_Attr_tail tail;

		//isomorphic
		Inh_Attr_stmt stmt;
		Inh_Attr_stmts stmts;

		Inh_Attr_E E;	

		Inh_Attr_optexpr2 optexpr2;
		
		Inh_Attr_optexpr3 optexpr3;	

		//isomorphic
		Inh_Attr_expr expr;
		Inh_Attr_e1 e1;		
		Inh_Attr_e2 e2;	
		Inh_Attr_e3 e3;
		Inh_Attr_e4 e4;
		Inh_Attr_e5 e5;
		Inh_Attr_e6 e6;
		Inh_Attr_e7 e7;
		Inh_Attr_e8 e8;
		Inh_Attr_e9 e9;
		Inh_Attr_e10 e10;
		Inh_Attr_e11 e11;
		Inh_Attr_e12 e12;
		Inh_Attr_e13 e13;
		Inh_Attr_e14 e14;



		//isomorphic
		Inh_Attr_expr_ expr_;				
		Inh_Attr_e2_ e2_;		
		Inh_Attr_e3_ e3_;			
		Inh_Attr_e4_ e4_;			
		Inh_Attr_e5_ e5_;			
		Inh_Attr_e6_ e6_;			
		Inh_Attr_e7_ e7_;			
		Inh_Attr_e8_ e8_;			
		Inh_Attr_e9_ e9_;			
		Inh_Attr_e10_ e10_;			
		Inh_Attr_e11_ e11_;			
		Inh_Attr_e12_ e12_;

		Inh_Attr_loc loc;	

		//isomorphic
		Inh_Attr_T1 T1;
		Inh_Attr_T3 T3; 
		Inh_Attr_args args;

		//isomorphic
		Inh_Attr_T2 T2;
		Inh_Attr_T4 T4;

		Inh_Attr_T5 T5;

		Inh_Attr_loc_ loc_;

		//isomorphic
		Inh_Attr_args_ args_;
		Inh_Attr_args__ args__;
		Inh_Attr_arg arg;
	};


	// synthetic attribute

	typedef struct  
	{
		int tValue;
		size_t tLine;
	}Syn_Attr_size, Syn_Attr_label;

	struct Syn_Attr_B
	{
		VarInfo sType;
	};

	typedef struct 
	{
		instr_list* spNextList;
		size_t sRetCnt;
	}Syn_Attr_stmt, Syn_Attr_stmts, Syn_Attr_E;

	struct Syn_Attr_optexpr2
	{
		instr_list* spTrueList;
		instr_list* spFalseList;
	};

	typedef struct 
	{
		VarInfo sType;
		Address sAddr;
	}Syn_Attr_loc, Syn_Attr_loc_, Syn_Attr_T3, Syn_Attr_T4, Syn_Attr_args;

	typedef struct 
	{
		VarInfo sType;
		bool sValFlag;
		Address sAddr;
		instr_list* spTrueList;
		instr_list* spFalseList;
	}Syn_Attr_expr, Syn_Attr_expr_
		, Syn_Attr_e1
		, Syn_Attr_e2, Syn_Attr_e2_
		, Syn_Attr_e3, Syn_Attr_e3_
		, Syn_Attr_e4, Syn_Attr_e4_
		, Syn_Attr_e5, Syn_Attr_e5_
		, Syn_Attr_e6, Syn_Attr_e6_
		, Syn_Attr_e7, Syn_Attr_e7_
		, Syn_Attr_e8, Syn_Attr_e8_
		, Syn_Attr_e9, Syn_Attr_e9_
		, Syn_Attr_e10, Syn_Attr_e10_
		, Syn_Attr_e11, Syn_Attr_e11_
		, Syn_Attr_e12, Syn_Attr_e12_
		, Syn_Attr_e13
		, Syn_Attr_e14
		, Syn_Attr_T1, Syn_Attr_T2,Syn_Attr_T5;

	union Syn_Attr
	{
		//isomorphic
		Syn_Attr_size size;
		Syn_Attr_label label;

		Syn_Attr_B B;

		//isomorphic
		Syn_Attr_stmt stmt;
		Syn_Attr_stmts stmts;
		Syn_Attr_E E;

		Syn_Attr_optexpr2 optexpr2;

		//isomorphic
		Syn_Attr_loc loc;
		Syn_Attr_loc_ loc_;
		Syn_Attr_T3 T3;
		Syn_Attr_T4 T4;
		Syn_Attr_args args;

		//isomorphic
		Syn_Attr_expr expr;
		Syn_Attr_expr_ expr_;
		Syn_Attr_e1 e1;
		Syn_Attr_e2 e2;
		Syn_Attr_e2_ e2_;
		Syn_Attr_e3 e3;
		Syn_Attr_e3_ e3_;
		Syn_Attr_e4 e4;
		Syn_Attr_e4_ e4_;
		Syn_Attr_e5 e5;
		Syn_Attr_e5_ e5_;
		Syn_Attr_e6 e6;
		Syn_Attr_e6_ e6_;
		Syn_Attr_e7 e7;
		Syn_Attr_e7_ e7_;
		Syn_Attr_e8 e8;
		Syn_Attr_e8_ e8_;
		Syn_Attr_e9 e9;
		Syn_Attr_e9_ e9_;
		Syn_Attr_e10 e10;
		Syn_Attr_e10_ e10_;
		Syn_Attr_e11 e11;
		Syn_Attr_e11_ e11_;
		Syn_Attr_e12 e12;
		Syn_Attr_e12_ e12_;
		Syn_Attr_e13 e13;
		Syn_Attr_e14 e14;
		Syn_Attr_T1 T1;
		Syn_Attr_T2 T2;
		Syn_Attr_T5 T5;
	};


	// temporary variable

	typedef struct
	{
		string* tLexime;
		size_t tLine;
	}Temp_option_id, Temp_decl, Temp_V_, Temp_param, Temp_e1, Temp_e14_id, Temp_loc;

	typedef struct 
	{
		size_t tLine;	
	}Temp_program_main, Temp_stmt_if, Temp_while_Line, Temp_stmt_break, Temp_stmt_continue, Temp_stmt_return, Temp_stmt_switch_expr, Temp_op;

	typedef struct  
	{
		int tValue;
		size_t tLine;
	}Temp_A, Temp_e14_const, Temp_stmt_case;

	struct Temp_e14_real
	{
		double tValue;
	};

	struct Temp_stmt_do_expr
	{
		instr tBegin;
		size_t tLine;
	};	

	struct Temp_stmt_for_expr
	{
		instr tBegin;
		instr_list* tpOptexpr2TrueList;
	};
	
	struct Temp_stmt_do_stmt1
	{
		instr_list* tpContinueList;
	};

	struct Temp_stmt_while 
	{
		instr tBegin;
		instr_list* tpContinueList;
	};

	struct Temp_stmt_for_stmt1 
	{
		instr tContinue;
		instr_list* tpContinueList;
	};

	struct Temp_stmt_switch_stmt1
	{
		Address tAddr;
		instr_list* tpTestList;
		var_instr_list* tpVarInstrList;
	};

	struct Temp_args_arglist
	{
		arg_list* ipArgList;
	};

	union Temp_Var
	{
		//id
		Temp_option_id option_id;
		Temp_decl decl_id;
		Temp_V_ V__id;
		Temp_param param_id;
		Temp_e1 e1_id;
		Temp_e14_id e14_id;
		Temp_loc loc_id;

		//line
		Temp_program_main main_line;
		Temp_stmt_if if_line;
		Temp_while_Line while_line;
		Temp_stmt_break break_line;
		Temp_stmt_continue continue_line;
		Temp_stmt_return return_line;
		Temp_stmt_switch_expr switch_expr_line;
		Temp_op op_line;

		//const: true,false,num,ascii
		Temp_A A_const;
		Temp_e14_const e14_const;
		Temp_stmt_case case_const;

		//real
		Temp_e14_real e14_real;

		//begin,line
		Temp_stmt_do_expr do_expr;
		Temp_stmt_for_expr for_expr;

		//continue-list
		Temp_stmt_do_stmt1 do_stmt_continue_list;

		//begin,continue-list
		Temp_stmt_while while_begin_continue_list;

		//continue,continue-list
		Temp_stmt_for_stmt1 for_stmt_continue_continue_list;

		//test-list,var-instr-list
		Temp_stmt_switch_stmt1 swtich_stmt_testlist_var_instr_list;

		//args-arglist
		Temp_args_arglist args;
	};
}