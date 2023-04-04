#pragma once

namespace Compiler
{
	static void copy_option_1_F(Inh_Attr *ps,Inh_Attr *pt)
	{
		//option'-->F
		pt->F.iType=ps->option_.iType;
		pt->F.iLine=ps->option_.iLine;
		pt->F.iLexime->swap(*(ps->option_.iLexime));
	}
	static void copy_option_2_decl_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//option'->decl'
		pt->decl_.iSection=s_GLOBAL;
		pt->decl_.iType=ps->option_.iType;
		pt->decl_.iLine=ps->option_.iLine;
		pt->decl_.iLexime->swap(*(ps->option_.iLexime));
	}

	static void copy_decl_1_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//decl'->A
		pt->A.iSection=ps->decl_.iSection;
		pt->A.iType=ps->decl_.iType;
		pt->A.iLine=ps->decl_.iLine;
		pt->A.iLexime->swap(*(ps->decl_.iLexime));
	}
	static void copy_decl_2_V(Inh_Attr *ps,Inh_Attr *pt)
	{
		//decl'->V
		pt->V.iSection=ps->decl_.iSection;
		pt->V.iType=ps->decl_.iType;
		pt->V.iLine=ps->decl_.iLine;
		pt->V.iLexime->swap(*(ps->decl_.iLexime));
	}

	static void copy_A_S(Inh_Attr *ps,Inh_Attr *pt)
	{
		//A->S:iA
		pt->A.iSection=ps->A.iSection;
		pt->A.iType=ps->A.iType;
		pt->A.iLine=ps->A.iLine;
		*(pt->A.iLexime)=*(ps->A.iLexime);	//此处不能使用swap进行交换
	}
	static void copy_A_opt1(Inh_Attr *ps,Inh_Attr *pt)
	{
		//A->opt1
		pt->opt1.iSection=ps->A.iSection;
		pt->opt1.iLexime->swap(*(ps->A.iLexime));
	}

	static void copy_opt1A_L(Inh_Attr *ps,Inh_Attr *pt)
	{
		//opt1->L
		pt->L.iSection=ps->opt1.iSection;
		pt->L.iLexime->swap(*(ps->opt1.iLexime));
	}

	static void copy_L1_L_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//L->L'
		pt->L_.iSection=ps->L.iSection;
		pt->L_.iLexime->swap(*(ps->L.iLexime));
	}

	static void copy_L__e1(Inh_Attr *ps,Inh_Attr *pt)
	{
		//L'->e1
		pt->e1.iSection=ps->L_.iSection;
	}
	static void copy_L__S(Inh_Attr *ps,Inh_Attr *pt)
	{
		//L'->S:L'
		pt->L_.iSection=ps->L_.iSection;
		pt->L_.iIndex=ps->L_.iIndex;
		*(pt->L_.iLexime)=*(ps->L_.iLexime);	//此处不能使用swap进行交换
	}
	static void copy_L__L__(Inh_Attr *ps,Inh_Attr *pt)
	{
		//L'->L"
		pt->L__.iSection=ps->L_.iSection;
		pt->L__.iIndex=ps->L_.iIndex;
		pt->L__.iLexime->swap(*(ps->L_.iLexime));
	}

	static void copy_L__1_L_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//L"->L'
		pt->L_.iSection=ps->L__.iSection;
		pt->L_.iIndex=ps->L__.iIndex+1;
		pt->L_.iLexime->swap(*(ps->L__.iLexime));
	}

	static void copy_V_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//V->A:V
		pt->V.iSection=ps->V.iSection;
		pt->V.iType=ps->V.iType;
		pt->V.iLine=ps->V.iLine;
		*(pt->V.iLexime)=*(ps->V.iLexime);	//此处不能使用swap进行交换
	}
	static void copy_V_opt2(Inh_Attr *ps,Inh_Attr *pt)
	{
		//V->opt2
		pt->opt2.iSection=ps->V.iSection;
		pt->opt2.iLexime->swap(*(ps->V.iLexime));
	}
	static void copy_V_V_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//V->V'
		pt->V_.iSection=ps->V.iSection;
		pt->V_.iType=ps->V.iType;
	}

	static void copy_V_1_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//V'->A:V'
		pt->V_.iSection=ps->V_.iSection;
		pt->V_.iType=ps->V_.iType;
	}
	static void copy_V_1_opt2(Inh_Attr *ps,Inh_Attr *pt)
	{
		//V'->opt2
		pt->opt2.iSection=ps->V_.iSection;
	}
	static void copy_V_1_V_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//V'->V'
		pt->V_.iSection=ps->V_.iSection;
		pt->V_.iType=ps->V_.iType;
	}

	static void copy_opt2A_e1(Inh_Attr *ps,Inh_Attr *pt)
	{
		//opt2->e1
		pt->e1.iSection=ps->opt2.iSection;
	}
	static void copy_opt2A_S(Inh_Attr *ps,Inh_Attr *pt)
	{
		//opt2->S:opt2
		pt->opt2.iSection=ps->opt2.iSection;
		pt->opt2.iLexime->swap(*(ps->opt2.iLexime));
	}

	static void copy_F_A1(Inh_Attr *ps,Inh_Attr *pt)
	{
		//F->A1:F
		pt->F.iLine=ps->F.iLine;
		pt->F.iType=ps->F.iType;
		pt->F.iLexime->swap(*(ps->F.iLexime));
	}

	static void copy_tail1_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//tail1->A:tail
		pt->tail.iLine=ps->tail.iLine;
		pt->tail.iType=ps->tail.iType;
		pt->tail.iLexime->swap(*(ps->tail.iLexime));
	}
	static void copy_tail2_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//tail2->A:tail
		pt->tail.iLine=ps->tail.iLine;
		pt->tail.iType=ps->tail.iType;
		pt->tail.iLexime->swap(*(ps->tail.iLexime));
	}

	static void copy_stmt3_stmt(Inh_Attr *ps,Inh_Attr *pt)
	{
		//stmt3->stmt
		pt->stmt=ps->stmt;
	}
	static void copy_stmt3_E(Inh_Attr *ps,Inh_Attr *pt)
	{
		//stmt3->E
		pt->E.iAddr=ps->stmt.iAddr;
		pt->E.ipBreakList=ps->stmt.ipBreakList;
		pt->E.ipContinueList=ps->stmt.ipContinueList;
		pt->E.ipVarInstrList=ps->stmt.ipVarInstrList;
	}

	static void copy_stmt4_stmt(Inh_Attr *ps,Inh_Attr *pt)
	{
		//stmt4->stmt
		pt->stmt.iAddr=ps->stmt.iAddr;
		pt->stmt.ipVarInstrList=ps->stmt.ipVarInstrList;
	}

	static void copy_stmt5_stmt(Inh_Attr *ps,Inh_Attr *pt)
	{
		//stmt5->stmt
		pt->stmt.iAddr=ps->stmt.iAddr;
		pt->stmt.ipVarInstrList=ps->stmt.ipVarInstrList;
	}

	static void copy_stmt6_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//stmt6->A
		pt->stmt=ps->stmt;
	}

	static void copy_stmt7_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//stmt7->A
		pt->stmt=ps->stmt;
	}

	static void copy_stmt9_optexpr2_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		pt->optexpr2.iValFlag=true;
	}
	static void copy_stmt9_optexpr2_B(Inh_Attr *ps,Inh_Attr *pt)
	{
		pt->optexpr2.iValFlag=false;
	}
	static void copy_stmt9_optexpr2_C(Inh_Attr *ps,Inh_Attr *pt)
	{
		pt->optexpr2.iValFlag=true;
	}
	static void copy_stmt9_stmt(Inh_Attr *ps,Inh_Attr *pt)
	{
		//stmt9->stmt
		pt->stmt.iAddr=ps->stmt.iAddr;
		pt->stmt.ipVarInstrList=ps->stmt.ipVarInstrList;
	}

	static void copy_stmt10_stmt(Inh_Attr *ps,Inh_Attr *pt)
	{
		//stmt10->stmt
		pt->stmt.ipContinueList=ps->stmt.ipContinueList;
	}

	static void copy_stmt11_S1(Inh_Attr *ps,Inh_Attr *pt)
	{
		//stmt11->S1
		pt->stmt=ps->stmt;
	}
	static void copy_stmt11_stmt(Inh_Attr *ps,Inh_Attr *pt)
	{
		//stmt11->stmt
		pt->stmt=ps->stmt;
	}

	static void copy_stmt12_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//stmt12->A
		pt->stmt=ps->stmt;
	}
	static void copy_stmt12_stmt(Inh_Attr *ps,Inh_Attr *pt)
	{
		//stmt12->stmt
		pt->stmt=ps->stmt;
	}

	static void copy_stmt13_stmts(Inh_Attr *ps,Inh_Attr *pt)
	{
		//stmt13->stmts
		pt->stmts=ps->stmt;
	}

	static void copy_E1_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//E->A:E
		pt->E.ipNextList=ps->E.ipNextList;
		pt->E.ipFalseList=ps->E.ipFalseList;

		//E指针赋空
		ps->E.ipNextList=0;
		ps->E.ipFalseList=0;
	}
	static void copy_E1_stmt(Inh_Attr *ps,Inh_Attr *pt)
	{
		//E->stmt
		pt->stmt.iAddr=ps->E.iAddr;
		pt->stmt.ipBreakList=ps->E.ipBreakList;
		pt->stmt.ipContinueList=ps->E.ipContinueList;
		pt->stmt.ipVarInstrList=ps->E.ipVarInstrList;
	}
	static void copy_E2_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//E->A:E
		pt->E.ipNextList=ps->E.ipNextList;
		pt->E.ipFalseList=ps->E.ipFalseList;

		//E指针赋空
		ps->E.ipNextList=0;
		ps->E.ipFalseList=0;
	}

	static void copy_stmts1_stmt(Inh_Attr *ps,Inh_Attr *pt)
	{
		//stmts->stmt
		pt->stmt=ps->stmts;
	}
	static void copy_stmts1_stmts(Inh_Attr *ps,Inh_Attr *pt)
	{
		//stmts->stmts
		pt->stmts=ps->stmts;
	}

	static void copy_optexpr2A_S(Inh_Attr *ps,Inh_Attr *pt)
	{
		//optexpr2->S
		pt->optexpr2=ps->optexpr2;
	}
	static void copy_optexpr2B_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//optexpr2->A
		pt->optexpr2=ps->optexpr2;		
	}

	static void copy_optexpr3A_S(Inh_Attr *ps,Inh_Attr *pt)
	{
		//optexpr3->S
		pt->optexpr3=ps->optexpr3;		
	}
	static void copy_optexpr3B_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//optexpr3->A
		pt->optexpr3=ps->optexpr3;
	}

	static void copy_expr_e1(Inh_Attr *ps,Inh_Attr *pt)
	{
		//expr->e1
		pt->e1=ps->expr;
	}
	static void copy_expr_expr_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//expr->expr'
		pt->expr_.iSection=ps->expr.iSection;
	}

	static void copy_expr_1_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//expr'->A
		pt->expr_=ps->expr_;	//使用浅拷贝

		//赋空expr'动态内存指针
		ps->expr_.ipTrueList=0;
		ps->expr_.ipFalseList=0;
	}
	static void copy_expr_1_e1(Inh_Attr *ps,Inh_Attr *pt)
	{
		//expr'->e1
		pt->e1.iSection=ps->expr_.iSection;
	}
	static void copy_expr_1_expr_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//expr'->expr'
		pt->expr_.iSection=ps->expr_.iSection;	//只拷贝此属性
	}
	static void copy_expr_2_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//expr'->A
		pt->expr_=ps->expr_;	//使用浅拷贝

		//赋空expr'动态内存指针
		ps->expr_.ipTrueList=0;
		ps->expr_.ipFalseList=0;
	}

	static void copy_e1A_T1(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e1->T1
		pt->T1.iSection=ps->e1.iSection;
	}
	static void copy_e1B_e2(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e1->e2
		pt->e2.iSection=ps->e1.iSection;
	}

	static void copy_e2_e3(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e2->e3
		pt->e3.iSection=ps->e2.iSection;
	}
	static void copy_e2_e2_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e2->e2'
		pt->e2_.iSection=ps->e2.iSection;
	}

	static void copy_e2_1_A1(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e2'->A
		pt->e2_=ps->e2_;	//使用浅拷贝

		//赋空e2'动态内存指针
		ps->e2_.ipTrueList=0;
		ps->e2_.ipFalseList=0;
	}
	static void copy_e2_1_e3(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e2'->e3
		pt->e3.iSection=ps->e2_.iSection;
	}
	static void copy_e2_1_S1(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e2'->S1
		pt->e2_.iSection=ps->e2_.iSection;		//只拷贝section
	}
	static void copy_e2_1_e2(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e2'->e2
		pt->e2.iSection=ps->e2_.iSection;		
	}
	static void copy_e2_1_S2(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e2'->S2
		pt->e2_.iSection=ps->e2_.iSection;		//只拷贝section
	}
	static void copy_e2_2_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e2'->A
		pt->e2_=ps->e2_;	//使用浅拷贝

		//赋空e2'动态内存指针
		ps->e2_.ipTrueList=0;
		ps->e2_.ipFalseList=0;
	}

	static void copy_e3_e4(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e3->e4
		pt->e4.iSection=ps->e3.iSection;
	}
	static void copy_e3_e3_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e3->e3'
		pt->e3_.iSection=ps->e3.iSection;
	}

	static void copy_e3_1_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e3'->A
		pt->e3_=ps->e3_;	//使用浅拷贝

		//赋空e3'动态内存指针
		ps->e3_.ipTrueList=0;
		ps->e3_.ipFalseList=0;
	}
	static void copy_e3_1_e4(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e3'->e4
		pt->e4.iSection=ps->e3_.iSection;
	}
	static void copy_e3_1_S1(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e3'->S1
		pt->e3_.iSection=ps->e3_.iSection;	//只拷贝section
	}
	static void copy_e3_1_e3_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e3'->e3'
		pt->e3_.iSection=ps->e3_.iSection;	//只拷贝section
	}
	static void copy_e3_2_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e3'->A
		pt->e3_=ps->e3_;	//使用浅拷贝

		//赋空e3'动态内存指针
		ps->e3_.ipTrueList=0;
		ps->e3_.ipFalseList=0;
	}

	static void copy_e4_e5(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e4->e5
		pt->e5.iSection=ps->e4.iSection;
	}
	static void copy_e4_e4_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e4->e4'
		pt->e4_.iSection=ps->e4.iSection;
	}

	static void copy_e4_1_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e4'->A
		pt->e4_=ps->e4_;	//使用浅拷贝

		//赋空e4'动态内存指针
		ps->e4_.ipTrueList=0;
		ps->e4_.ipFalseList=0;
	}
	static void copy_e4_1_e5(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e4'->e5
		pt->e5.iSection=ps->e4_.iSection;
	}
	static void copy_e4_1_S1(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e4'->S1
		pt->e4_.iSection=ps->e4_.iSection;	//只拷贝section
	}
	static void copy_e4_1_e4_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e4'->e4'
		pt->e4_.iSection=ps->e4_.iSection;	//只拷贝section
	}
	static void copy_e4_2_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e4'->A
		pt->e4_=ps->e4_;	//使用浅拷贝

		//赋空e4'动态内存指针
		ps->e4_.ipTrueList=0;
		ps->e4_.ipFalseList=0;
	}

	static void copy_e5_e6(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e5->e6
		pt->e6.iSection=ps->e5.iSection;
	}
	static void copy_e5_e5_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e5->e5'
		pt->e5_.iSection=ps->e5.iSection;
	}

	static void copy_e5_1_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e5'->A
		pt->e5_=ps->e5_;	//使用浅拷贝

		//赋空e5'动态内存指针
		ps->e5_.ipTrueList=0;
		ps->e5_.ipFalseList=0;
	}
	static void copy_e5_1_e6(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e5'->e6
		pt->e6.iSection=ps->e5_.iSection;
	}
	static void copy_e5_1_S1(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e5'->S1
		pt->e5_.iSection=ps->e5_.iSection;	//只拷贝section
	}
	static void copy_e5_1_e5_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e5'->e5'
		pt->e5_.iSection=ps->e5_.iSection;	//只拷贝section
	}
	static void copy_e5_2_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e5'->A
		pt->e5_=ps->e5_;	//使用浅拷贝

		//赋空e5'动态内存指针
		ps->e5_.ipTrueList=0;
		ps->e5_.ipFalseList=0;
	}

	static void copy_e6_e7(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e6->e7
		pt->e7.iSection=ps->e6.iSection;
	}
	static void copy_e6_e6_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e6->e6'
		pt->e6_.iSection=ps->e6.iSection;
	}

	static void copy_e6_1_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e6'->A
		pt->e6_=ps->e6_;	//使用浅拷贝

		//赋空e6'动态内存指针
		ps->e6_.ipTrueList=0;
		ps->e6_.ipFalseList=0;
	}
	static void copy_e6_1_e7(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e6'->e7
		pt->e7.iSection=ps->e6_.iSection;
	}
	static void copy_e6_1_S1(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e6'->S1
		pt->e6_.iSection=ps->e6_.iSection;	//只拷贝section
	}
	static void copy_e6_1_e6_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e6'->e6'
		pt->e6_.iSection=ps->e6_.iSection;	//只拷贝section
	}
	static void copy_e6_2_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e6'->A
		pt->e6_=ps->e6_;	//使用浅拷贝

		//赋空e6'动态内存指针
		ps->e6_.ipTrueList=0;
		ps->e6_.ipFalseList=0;
	}

	static void copy_e7_e8(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e7->e8
		pt->e8.iSection=ps->e7.iSection;
	}
	static void copy_e7_e7_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e7->e7'
		pt->e7_.iSection=ps->e7.iSection;
	}

	static void copy_e7_1_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e7'->A
		pt->e7_=ps->e7_;	//使用浅拷贝

		//赋空e7'动态内存指针
		ps->e7_.ipTrueList=0;
		ps->e7_.ipFalseList=0;
	}
	static void copy_e7_1_e8(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e7'->e8
		pt->e8.iSection=ps->e7_.iSection;
	}
	static void copy_e7_1_S1(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e7'->S1
		pt->e7_.iSection=ps->e7_.iSection;	//只拷贝section
	}
	static void copy_e7_1_e7_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e7'->e7'
		pt->e7_.iSection=ps->e7_.iSection;	//只拷贝section
	}
	static void copy_e7_2_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e7'->A
		pt->e7_=ps->e7_;	//使用浅拷贝

		//赋空e7'动态内存指针
		ps->e7_.ipTrueList=0;
		ps->e7_.ipFalseList=0;
	}

	static void copy_e8_e9(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e8->e9
		pt->e9.iSection=ps->e8.iSection;
	}
	static void copy_e8_e8_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e8->e8'
		pt->e8_.iSection=ps->e8.iSection;
	}

	static void copy_e8_1_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e8'->A
		pt->e8_=ps->e8_;	//使用浅拷贝

		//赋空e8'动态内存指针
		ps->e8_.ipTrueList=0;
		ps->e8_.ipFalseList=0;
	}
	static void copy_e8_1_e9(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e8'->e9
		pt->e9.iSection=ps->e8_.iSection;
	}
	static void copy_e8_1_S1(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e8'->S1
		pt->e8_.iSection=ps->e8_.iSection;	//只拷贝section
	}
	static void copy_e8_1_e8_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e8'->e8'
		pt->e8_.iSection=ps->e8_.iSection;	//只拷贝section
	}
	static void copy_e8_2_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e8'->A
		pt->e8_=ps->e8_;	//使用浅拷贝

		//赋空e8'动态内存指针
		ps->e8_.ipTrueList=0;
		ps->e8_.ipFalseList=0;
	}
	static void copy_e8_2_e9(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e8'->e9
		pt->e9.iSection=ps->e8_.iSection;
	}
	static void copy_e8_2_S1(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e8'->S1
		pt->e8_.iSection=ps->e8_.iSection;	//只拷贝section
	}
	static void copy_e8_2_e8_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e8'->e8'
		pt->e8_.iSection=ps->e8_.iSection;	//只拷贝section
	}
	static void copy_e8_3_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e8'->A
		pt->e8_=ps->e8_;	//使用浅拷贝

		//赋空e8'动态内存指针
		ps->e8_.ipTrueList=0;
		ps->e8_.ipFalseList=0;
	}

	static void copy_e9_e10(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e9->e10
		pt->e10.iSection=ps->e9.iSection;
	}
	static void copy_e9_e9_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e9->e9'
		pt->e9_.iSection=ps->e9.iSection;
	}

	static void copy_e9_1_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e9'->A
		pt->e9_=ps->e9_;	//使用浅拷贝

		//赋空e9'动态内存指针
		ps->e9_.ipTrueList=0;
		ps->e9_.ipFalseList=0;
	}
	static void copy_e9_1_e10(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e9'->e10
		pt->e10.iSection=ps->e9_.iSection;
	}
	static void copy_e9_1_S1(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e9'->S1
		pt->e9_.iSection=ps->e9_.iSection;	//只拷贝section
	}
	static void copy_e9_1_e9_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e9'->e9'
		pt->e9_.iSection=ps->e9_.iSection;	//只拷贝section
	}
	static void copy_e9_2_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e9'->A
		pt->e9_=ps->e9_;	//使用浅拷贝

		//赋空e9'动态内存指针
		ps->e9_.ipTrueList=0;
		ps->e9_.ipFalseList=0;
	}
	static void copy_e9_2_e10(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e9'->e10
		pt->e10.iSection=ps->e9_.iSection;
	}
	static void copy_e9_2_S1(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e9'->S1
		pt->e9_.iSection=ps->e9_.iSection;	//只拷贝section
	}
	static void copy_e9_2_e9_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e9'->e9'
		pt->e9_.iSection=ps->e9_.iSection;	//只拷贝section
	}
	static void copy_e9_3_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e9'->A
		pt->e9_=ps->e9_;	//使用浅拷贝

		//赋空e9'动态内存指针
		ps->e9_.ipTrueList=0;
		ps->e9_.ipFalseList=0;
	}
	static void copy_e9_3_e10(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e9'->e10
		pt->e10.iSection=ps->e9_.iSection;
	}
	static void copy_e9_3_S1(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e9'->S1
		pt->e9_.iSection=ps->e9_.iSection;	//只拷贝section
	}
	static void copy_e9_3_e9_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e9'->e9'
		pt->e9_.iSection=ps->e9_.iSection;	//只拷贝section
	}
	static void copy_e9_4_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e9'->A
		pt->e9_=ps->e9_;	//使用浅拷贝

		//赋空e9'动态内存指针
		ps->e9_.ipTrueList=0;
		ps->e9_.ipFalseList=0;
	}
	static void copy_e9_4_e10(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e9'->e10
		pt->e10.iSection=ps->e9_.iSection;
	}
	static void copy_e9_4_S1(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e9'->S1
		pt->e9_.iSection=ps->e9_.iSection;	//只拷贝section
	}
	static void copy_e9_4_e9_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e9'->e9'
		pt->e9_.iSection=ps->e9_.iSection;	//只拷贝section
	}
	static void copy_e9_5_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e9'->A
		pt->e9_=ps->e9_;	//使用浅拷贝

		//赋空e9'动态内存指针
		ps->e9_.ipTrueList=0;
		ps->e9_.ipFalseList=0;
	}

	static void copy_e10_e11(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e10->e11
		pt->e11.iSection=ps->e10.iSection;
	}
	static void copy_e10_e10_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e10->e10'
		pt->e10_.iSection=ps->e10.iSection;
	}

	static void copy_e10_1_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e10'->A
		pt->e10_=ps->e10_;	//使用浅拷贝

		//赋空e10'动态内存指针
		ps->e10_.ipTrueList=0;
		ps->e10_.ipFalseList=0;
	}
	static void copy_e10_1_e11(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e10'->e11
		pt->e11.iSection=ps->e10_.iSection;
	}
	static void copy_e10_1_S1(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e10'->S1
		pt->e10_.iSection=ps->e10_.iSection;	//只拷贝section
	}
	static void copy_e10_1_e10_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e10'->e10'
		pt->e10_.iSection=ps->e10_.iSection;	//只拷贝section
	}
	static void copy_e10_2_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e10'->A
		pt->e10_=ps->e10_;	//使用浅拷贝

		//赋空e10'动态内存指针
		ps->e10_.ipTrueList=0;
		ps->e10_.ipFalseList=0;
	}
	static void copy_e10_2_e11(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e10'->e11
		pt->e11.iSection=ps->e10_.iSection;
	}
	static void copy_e10_2_S1(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e10'->S1
		pt->e10_.iSection=ps->e10_.iSection;	//只拷贝section
	}
	static void copy_e10_2_e10_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e10'->e10'
		pt->e10_.iSection=ps->e10_.iSection;	//只拷贝section
	}
	static void copy_e10_3_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e10'->A
		pt->e10_=ps->e10_;	//使用浅拷贝

		//赋空e10'动态内存指针
		ps->e10_.ipTrueList=0;
		ps->e10_.ipFalseList=0;
	}

	static void copy_e11_e12(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e11->e12
		pt->e12.iSection=ps->e11.iSection;
	}
	static void copy_e11_e11_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e11->e11'
		pt->e11_.iSection=ps->e11.iSection;
	}

	static void copy_e11_1_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e11'->A
		pt->e11_=ps->e11_;	//使用浅拷贝

		//赋空e11'动态内存指针
		ps->e11_.ipTrueList=0;
		ps->e11_.ipFalseList=0;
	}
	static void copy_e11_1_e12(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e11'->e12
		pt->e12.iSection=ps->e11_.iSection;
	}
	static void copy_e11_1_S1(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e11'->S1
		pt->e11_.iSection=ps->e11_.iSection;	//只拷贝section
	}
	static void copy_e11_1_e11_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e11'->e11'
		pt->e11_.iSection=ps->e11_.iSection;	//只拷贝section
	}
	static void copy_e11_2_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e11'->A
		pt->e11_=ps->e11_;	//使用浅拷贝

		//赋空e11'动态内存指针
		ps->e11_.ipTrueList=0;
		ps->e11_.ipFalseList=0;
	}
	static void copy_e11_2_e12(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e11'->e12
		pt->e12.iSection=ps->e11_.iSection;
	}
	static void copy_e11_2_S1(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e11'->S1
		pt->e11_.iSection=ps->e11_.iSection;	//只拷贝section
	}
	static void copy_e11_2_e11_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e11'->e11'
		pt->e11_.iSection=ps->e11_.iSection;	//只拷贝section
	}
	static void copy_e11_3_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e11'->A
		pt->e11_=ps->e11_;	//使用浅拷贝

		//赋空e11'动态内存指针
		ps->e11_.ipTrueList=0;
		ps->e11_.ipFalseList=0;
	}

	static void copy_e12_e13(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e12->e13
		pt->e13.iSection=ps->e12.iSection;
	}
	static void copy_e12_e12_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e12->e12'
		pt->e12_.iSection=ps->e12.iSection;
	}

	static void copy_e12_1_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e12'->A
		pt->e12_=ps->e12_;	//使用浅拷贝

		//赋空e12'动态内存指针
		ps->e12_.ipTrueList=0;
		ps->e12_.ipFalseList=0;
	}
	static void copy_e12_1_e13(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e12'->e13
		pt->e13.iSection=ps->e12_.iSection;
	}
	static void copy_e12_1_S1(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e12'->S1
		pt->e12_.iSection=ps->e12_.iSection;	//只拷贝section
	}
	static void copy_e12_1_e12_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e12'->e12'
		pt->e12_.iSection=ps->e12_.iSection;	//只拷贝section
	}
	static void copy_e12_2_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e12'->A
		pt->e12_=ps->e12_;	//使用浅拷贝

		//赋空e12'动态内存指针
		ps->e12_.ipTrueList=0;
		ps->e12_.ipFalseList=0;
	}
	static void copy_e12_2_e13(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e12'->e13
		pt->e13.iSection=ps->e12_.iSection;
	}
	static void copy_e12_2_S1(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e12'->S1
		pt->e12_.iSection=ps->e12_.iSection;	//只拷贝section
	}
	static void copy_e12_2_e12_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e12'->e12'
		pt->e12_.iSection=ps->e12_.iSection;	//只拷贝section
	}
	static void copy_e12_3_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e12'->A
		pt->e12_=ps->e12_;	//使用浅拷贝

		//赋空e12'动态内存指针
		ps->e12_.ipTrueList=0;
		ps->e12_.ipFalseList=0;
	}
	static void copy_e12_3_e13(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e12'->e13
		pt->e13.iSection=ps->e12_.iSection;
	}
	static void copy_e12_3_S1(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e12'->S1
		pt->e12_.iSection=ps->e12_.iSection;	//只拷贝section
	}
	static void copy_e12_3_e12_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e12'->e12'
		pt->e12_.iSection=ps->e12_.iSection;	//只拷贝section
	}
	static void copy_e12_4_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e12'->A
		pt->e12_=ps->e12_;	//使用浅拷贝

		//赋空e12'动态内存指针
		ps->e12_.ipTrueList=0;
		ps->e12_.ipFalseList=0;
	}

	static void copy_e13_e13(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e13->e13
		pt->e13.iSection=ps->e13.iSection;
	}
	static void copy_e13_S(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e13->S
		pt->e13.iSection=ps->e13.iSection;
	}
	static void copy_e13_e14(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e13->e14
		pt->e14.iSection=ps->e13.iSection;
	}

	static void copy_e14F_loc(Inh_Attr *ps,Inh_Attr *pt)
	{
		//++loc
		pt->loc.i_Inc=true;
		
		//e14->loc
		pt->loc.iSection=ps->e14.iSection;
	}
	static void copy_e14G_loc(Inh_Attr *ps,Inh_Attr *pt)
	{
		//--loc
		pt->loc.i_Inc=false;

		//e14->loc
		pt->loc.iSection=ps->e14.iSection;
	}
	static void copy_e14H_expr(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e14->expr
		pt->expr.iSection=ps->e14.iSection;
	}
	static void copy_e14I_T3(Inh_Attr *ps,Inh_Attr *pt)
	{
		//e14->T3
		pt->T3.iSection=ps->e14.iSection;
	}

	static void copy_T3_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T3->A
		pt->T3.iSection=ps->T3.iSection;
		pt->T3.iLine=ps->T3.iLine;
		*(pt->T3.iLexime)=*(ps->T3.iLexime);	//此处不能使用swap进行交换
	}
	static void copy_T3C_args(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T3->args
		pt->args.iSection=ps->T3.iSection;
		pt->args.iLine=ps->T3.iLine;
		pt->args.iLexime->swap(*(ps->T3.iLexime));
	}
	static void copy_T3D_expr(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T3->expr
		pt->expr.iSection=ps->T3.iSection;
	}
	static void copy_T3D_S1(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T3->S1
		pt->T3.iSection=ps->T3.iSection;
		pt->T3.iLine=ps->T3.iLine;
		*(pt->T3.iLexime)=*(ps->T3.iLexime);	//此处不能使用swap进行交换
	}
	static void copy_T3D_T4(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T3->T4
		pt->T4.iSection=ps->T3.iSection;
		pt->T4.iLexime->swap(*(ps->T3.iLexime));
	}

	static void copy_T4_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T4->A
		pt->T4.iSection=ps->T4.iSection;
		pt->T4.iAddr=ps->T4.iAddr;
		pt->T4.iLexime->swap(*(ps->T4.iLexime));
	}

	static void copy_loc_loc_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//loc->loc'
		pt->loc_.iSection=ps->loc.iSection;
		pt->loc_.i_Inc=ps->loc.i_Inc;
	}

	static void copy_loc__A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//loc'->A
		pt->loc_.iSection=ps->loc_.iSection;
		pt->loc_.i_Inc=ps->loc_.i_Inc;
		pt->loc_.iLine=ps->loc_.iLine;
		*(pt->loc_.iLexime)=*(ps->loc_.iLexime);	//此处不能使用swap进行交换
	}
	static void copy_loc__expr(Inh_Attr *ps,Inh_Attr *pt)
	{
		//loc'->expr
		pt->expr.iSection=ps->loc_.iSection;
	}
	static void copy_loc__S(Inh_Attr *ps,Inh_Attr *pt)
	{
		//loc'->S
		pt->loc_.iSection=ps->loc_.iSection;
		pt->loc_.i_Inc=ps->loc_.i_Inc;
		pt->loc_.iLine=ps->loc_.iLine;
		pt->loc_.iLexime->swap(*(ps->loc_.iLexime));
	}

	static void copy_args1_args_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//args1->args'
		pt->args_.iSection=ps->args.iSection;
		pt->args_.iLine=ps->args.iLine;
		*(pt->args_.iLexime)=*(ps->args.iLexime);	//此处不能使用swap进行交换
	}
	static void copy_args1_A2(Inh_Attr *ps,Inh_Attr *pt)
	{
		//args1->A2
		pt->args.iSection=ps->args.iSection;
		pt->args.iLine=ps->args.iLine;
		pt->args.iLexime->swap(*(ps->args.iLexime));
	}
	static void copy_args2_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//args2->A
		pt->args.iSection=ps->args.iSection;
		pt->args.iLine=ps->args.iLine;
		pt->args.iLexime->swap(*(ps->args.iLexime));
	}

	static void copy_args__arg(Inh_Attr *ps,Inh_Attr *pt)
	{
		//args'->arg
		pt->arg.iSection=ps->args_.iSection;
		pt->arg.iCnt=ps->args_.iCnt+1;
		pt->arg.ipArgList=ps->args_.ipArgList;
		pt->arg.iLine=ps->args_.iLine;
		*(pt->arg.iLexime)=*(ps->args_.iLexime);	//此处不能使用swap进行交换
	}
	static void copy_args__args__(Inh_Attr *ps,Inh_Attr *pt)
	{
		//args'->args"
		pt->args__.iSection=ps->args_.iSection;
		pt->args__.iCnt=ps->args_.iCnt+1;
		pt->args__.ipArgList=ps->args_.ipArgList;
		pt->args__.iLine=ps->args_.iLine;
		pt->args__.iLexime->swap(*(ps->args_.iLexime));
	}

	static void copy_args___args_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//args"->args'
		pt->args_.iSection=ps->args__.iSection;
		pt->args_.iCnt=ps->args__.iCnt;
		pt->args_.ipArgList=ps->args__.ipArgList;
		pt->args_.iLine=ps->args__.iLine;
		pt->args_.iLexime->swap(*(ps->args__.iLexime));
	}

	static void copy_arg_e1(Inh_Attr *ps,Inh_Attr *pt)
	{
		//arg->e1
		pt->e1.iSection=ps->arg.iSection;
	}
	static void copy_arg_S(Inh_Attr *ps,Inh_Attr *pt)
	{
		//arg->S
		pt->arg.iSection=ps->arg.iSection;
		pt->arg.iCnt=ps->arg.iCnt;
		pt->arg.ipArgList=ps->arg.ipArgList;
		pt->arg.iLine=ps->arg.iLine;
		pt->arg.iLexime->swap(*(ps->arg.iLexime));
	}

	static void copy_T1_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T1->A
		pt->T1.iSection=ps->T1.iSection;
		pt->T1.iLine=ps->T1.iLine;
		*(pt->T1.iLexime)=*(ps->T1.iLexime);	//此处不能使用swap进行交换
	}
	static void copy_T1C_args(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T1->args
		pt->args.iSection=ps->T1.iSection;
		pt->args.iLine=ps->T1.iLine;
		pt->args.iLexime->swap(*(ps->T1.iLexime));
	}
	static void copy_T1D_expr(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T1->expr
		pt->expr.iSection=ps->T1.iSection;
	}
	static void copy_T1D_S1(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T1->S1
		pt->T1.iSection=ps->T1.iSection;
		pt->T1.iLine=ps->T1.iLine;
		*(pt->T1.iLexime)=*(ps->T1.iLexime);	//此处不能使用swap进行交换
	}
	static void copy_T1D_T2(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T1->T2
		pt->T2.iSection=ps->T1.iSection;
		pt->T2.iLexime->swap(*(ps->T1.iLexime));
	}

	static void copy_T1E_e1(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T1->e1
		pt->e1.iSection=ps->T1.iSection;
	}
	static void copy_T1E_S(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T1->S1
		pt->T1.iSection=ps->T1.iSection;
		pt->T1.iLine=ps->T1.iLine;
		pt->T1.iLexime->swap(*(ps->T1.iLexime));
	}

	static void copy_T1Z_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T1->A
		pt->T1.iSection=ps->T1.iSection;
		pt->T1.iLine=ps->T1.iLine;
		pt->T1.iLexime->swap(*(ps->T1.iLexime));
	}
	static void copy_T1Z_e12_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T1->e12'
		pt->e12_.iSection=ps->T1.iSection;
	}
	static void copy_T1Z_e11_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T1->e11'
		pt->e11_.iSection=ps->T1.iSection;
	}
	static void copy_T1Z_e10_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T1->e10'
		pt->e10_.iSection=ps->T1.iSection;
	}
	static void copy_T1Z_e9_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T1->e9'
		pt->e9_.iSection=ps->T1.iSection;
	}
	static void copy_T1Z_e8_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T1->e8'
		pt->e8_.iSection=ps->T1.iSection;
	}
	static void copy_T1Z_e7_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T1->e7'
		pt->e7_.iSection=ps->T1.iSection;
	}
	static void copy_T1Z_e6_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T1->e6'
		pt->e6_.iSection=ps->T1.iSection;
	}
	static void copy_T1Z_e5_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T1->e5'
		pt->e5_.iSection=ps->T1.iSection;
	}
	static void copy_T1Z_e4_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T1->e4'
		pt->e4_.iSection=ps->T1.iSection;
	}
	static void copy_T1Z_e3_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T1->e3'
		pt->e3_.iSection=ps->T1.iSection;
	}
	static void copy_T1Z_e2_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T1->e2'
		pt->e2_.iSection=ps->T1.iSection;
	}

	static void copy_T2_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T2->A
		pt->T2.iSection=ps->T2.iSection;
		pt->T2.iAddr=ps->T2.iAddr;
		pt->T2.iLexime->swap(*(ps->T2.iLexime));
	}

	static void copy_T2C_e1(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T2->e1
		pt->e1.iSection=ps->T2.iSection;
	}
	static void copy_T2C_S(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T2->S
		pt->T2.iSection=ps->T2.iSection;
		pt->T2.iAddr=ps->T2.iAddr;
		pt->T2.iLexime->swap(*(ps->T2.iLexime));
	}

	static void copy_T2X_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T2->A
		pt->T2.iSection=ps->T2.iSection;
		pt->T2.iAddr=ps->T2.iAddr;
		pt->T2.iLexime->swap(*(ps->T2.iLexime));
	}
	static void copy_T2X_e12_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T2->e12'
		pt->e12_.iSection=ps->T2.iSection;
	}
	static void copy_T2X_e11_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T2->e11'
		pt->e11_.iSection=ps->T2.iSection;
	}
	static void copy_T2X_e10_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T2->e10'
		pt->e10_.iSection=ps->T2.iSection;
	}
	static void copy_T2X_e9_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T2->e9'
		pt->e9_.iSection=ps->T2.iSection;
	}
	static void copy_T2X_e8_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T2->e8'
		pt->e8_.iSection=ps->T2.iSection;
	}
	static void copy_T2X_e7_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T2->e7'
		pt->e7_.iSection=ps->T2.iSection;
	}
	static void copy_T2X_e6_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T2->e6'
		pt->e6_.iSection=ps->T2.iSection;
	}
	static void copy_T2X_e5_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T2->e5'
		pt->e5_.iSection=ps->T2.iSection;
	}
	static void copy_T2X_e4_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T2->e4'
		pt->e4_.iSection=ps->T2.iSection;
	}
	static void copy_T2X_e3_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T2->e3'
		pt->e3_.iSection=ps->T2.iSection;
	}
	static void copy_T2X_e2_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T2->e2'
		pt->e2_.iSection=ps->T2.iSection;
	}


	static void copy_T1_T5(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T1->T5
		pt->T5.iSection=ps->T1.iSection;
	}

	static void copy_T2_T5(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T2->T5
		pt->T5.iSection=ps->T2.iSection;
	}

	static void copy_T5_A(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T5->A
		pt->T5.iSection=ps->T5.iSection;
		pt->T5.iType=ps->T5.iType;
		pt->T5.iAddr=ps->T5.iAddr;
	}
	static void copy_T5_e12_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T5->e12'
		pt->e12_.iSection=ps->T5.iSection;
	}
	static void copy_T5_e11_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T5->e11'
		pt->e11_.iSection=ps->T5.iSection;
	}
	static void copy_T5_e10_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T5->e10'
		pt->e10_.iSection=ps->T5.iSection;
	}
	static void copy_T5_e9_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T5->e9'
		pt->e9_.iSection=ps->T5.iSection;
	}
	static void copy_T5_e8_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T5->e8'
		pt->e8_.iSection=ps->T5.iSection;
	}
	static void copy_T5_e7_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T5->e7'
		pt->e7_.iSection=ps->T5.iSection;
	}
	static void copy_T5_e6_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T5->e6'
		pt->e6_.iSection=ps->T5.iSection;
	}
	static void copy_T5_e5_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T5->e5'
		pt->e5_.iSection=ps->T5.iSection;
	}
	static void copy_T5_e4_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T5->e4'
		pt->e4_.iSection=ps->T5.iSection;
	}
	static void copy_T5_e3_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T5->e3'
		pt->e3_.iSection=ps->T5.iSection;
	}
	static void copy_T5_e2_(Inh_Attr *ps,Inh_Attr *pt)
	{
		//T5->e2'
		pt->e2_.iSection=ps->T5.iSection;
	}
}