#pragma once

#include "CSection.h"
#include "CDataType.h"

namespace Compiler
{
	Temp_Var* init_temp_program_A1()
	{
		Temp_Var *pt=new Temp_Var();

		pt->main_line.tLine=0;	//这种初始化操作本无必要,但可以明确说明变量的用途,功能比一般注释还强,下同

		return pt;
	}

	Inh_Attr* init_inh_program_stmts()
	{
		Inh_Attr *pi=new Inh_Attr();

		//初始化为无效地址
		pi->stmts.iAddr.section=s_INVALID;
		pi->stmts.iAddr.offset=-1;

		//初始化为空指针
		pi->stmts.ipBreakList=0;
		pi->stmts.ipContinueList=0;
		pi->stmts.ipVarInstrList=0;

		return pi;
	}

	Syn_Attr* init_syn_program_S()
	{
		Syn_Attr *ps=new Syn_Attr();

		//初始化为0
		ps->stmts.sRetCnt=0;

		//初始化为空表
		ps->stmts.spNextList=new instr_list();

		return ps;
	}
	void del_syn_program_S(Syn_Attr *psa)
	{
		delete psa->stmts.spNextList;
	}



	Temp_Var* init_temp_option1_A()
	{
		Temp_Var *pt=new Temp_Var();

		pt->option_id.tLine=0;
		pt->option_id.tLexime=new string();

		return pt;
	}
	void del_temp_option1_A(Temp_Var *ptv)
	{
		delete ptv->option_id.tLexime;	
	}

	Inh_Attr* init_inh_option1_F()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->F.iLine=0;

		pi->F.iType.type=t_VOID;
		pi->F.iType.is_array=false;
		pi->F.iType.length=0;

		pi->F.iLexime=new string();

		return pi;
	}
	void del_inh_option1_F(Inh_Attr *pia)
	{
		delete pia->F.iLexime;
	}

	Syn_Attr* init_syn_option2_S()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->B.sType.type=t_VOID;
		ps->B.sType.is_array=false;
		ps->B.sType.length=0;

		return ps;
	}

	Temp_Var* init_temp_option2_A()
	{
		Temp_Var *pt=new Temp_Var();

		pt->option_id.tLine=0;
		pt->option_id.tLexime=new string();

		return pt;
	}
	void del_temp_option2_A(Temp_Var *ptv)
	{
		delete ptv->option_id.tLexime;	
	}

	Inh_Attr* init_inh_option2_option_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->option_.iLine=0;

		pi->option_.iType.type=t_VOID;
		pi->option_.iType.is_array=false;
		pi->option_.iType.length=0;

		pi->option_.iLexime=new string();

		return pi;
	}
	void del_inh_option2_option_(Inh_Attr *pia)
	{
		delete pia->option_.iLexime;
	}



	Inh_Attr* init_inh_option_1_F()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->F.iLine=0;

		pi->F.iType.type=t_VOID;
		pi->F.iType.is_array=false;
		pi->F.iType.length=0;

		pi->F.iLexime=new string();

		return pi;
	}
	void del_inh_option_1_F(Inh_Attr *pia)
	{
		delete pia->F.iLexime;
	}

	Inh_Attr* init_inh_option_2_decl_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->decl_.iSection=s_INVALID;

		pi->decl_.iLine=0;

		pi->decl_.iType.type=t_VOID;
		pi->decl_.iType.is_array=false;
		pi->decl_.iType.length=0;

		pi->decl_.iLexime=new string();

		return pi;
	}
	void del_inh_option_2_decl_(Inh_Attr *pia)
	{
		delete pia->decl_.iLexime;
	}



	Syn_Attr* init_syn_decl_S()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->B.sType.type=t_VOID;
		ps->B.sType.is_array=false;
		ps->B.sType.length=0;

		return ps;
	}

	Temp_Var* init_temp_decl_A()
	{
		Temp_Var *pt=new Temp_Var();

		pt->decl_id.tLine=0;
		pt->decl_id.tLexime=new string();

		return pt;
	}
	void del_temp_decl_A(Temp_Var *ptv)
	{
		delete ptv->decl_id.tLexime;	
	}

	Inh_Attr* init_inh_decl_decl_()
	{
		Inh_Attr *pi=new Inh_Attr();

		//合理初始化
		pi->decl_.iSection=s_LOCAL;

		pi->decl_.iLine=0;

		pi->decl_.iType.type=t_VOID;
		pi->decl_.iType.is_array=false;
		pi->decl_.iType.length=0;

		pi->decl_.iLexime=new string();

		return pi;
	}
	void del_inh_decl_decl_(Inh_Attr *pia)
	{
		delete pia->decl_.iLexime;
	}



	Inh_Attr* init_inh_decl_1_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->A.iSection=s_INVALID;

		pi->A.iLine=0;

		pi->A.iType.type=t_VOID;
		pi->A.iType.is_array=false;
		pi->A.iType.length=0;

		pi->A.iLexime=new string();

		return pi;
	}
	void del_inh_decl_1_A(Inh_Attr *pia)
	{
		delete pia->A.iLexime;
	}



	Inh_Attr* init_inh_decl_2_V()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->V.iSection=s_INVALID;

		pi->V.iLine=0;

		pi->V.iType.type=t_VOID;
		pi->V.iType.is_array=false;
		pi->V.iType.length=0;

		pi->V.iLexime=new string();

		return pi;
	}
	void del_inh_decl_2_V(Inh_Attr *pia)
	{
		delete pia->V.iLexime;
	}



	Inh_Attr* init_inh_A_S()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->A.iSection=s_INVALID;

		pi->A.iLine=0;

		pi->A.iType.type=t_VOID;
		pi->A.iType.is_array=false;
		pi->A.iType.length=0;

		pi->A.iLexime=new string();

		return pi;
	}
	void del_inh_A_S(Inh_Attr *pia)
	{
		delete pia->A.iLexime;
	}
	Syn_Attr* init_syn_A_S()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->size.tLine=0;
		ps->size.tValue=-1;

		return ps;
	}

	Inh_Attr* init_inh_A_opt1()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->opt1.iSection=s_INVALID;
		pi->opt1.iLexime=new string();

		return pi;
	}
	void del_inh_A_opt1(Inh_Attr *pia)
	{
		delete pia->opt1.iLexime;
	}



	Temp_Var* init_temp_opt1A_A()
	{
		Temp_Var *pt=new Temp_Var();

		pt->op_line.tLine=0;

		return pt;
	}

	Inh_Attr* init_inh_opt1A_L()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->L.iSection=s_INVALID;
		pi->L.iLexime=new string();

		return pi;
	}
	void del_inh_opt1A_L(Inh_Attr *pia)
	{
		delete pia->L.iLexime;
	}



	Inh_Attr* init_inh_L1_L_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->L_.iSection=s_INVALID;
		pi->L_.iIndex=0;
		pi->L_.iLexime=new string();

		return pi;
	}
	void del_inh_L1_L_(Inh_Attr *pia)
	{
		delete pia->L_.iLexime;
	}



	Inh_Attr* init_inh_L__e1()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e1.iSection=s_INVALID;

		return pi;
	}

	Inh_Attr* init_inh_L__S()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->L_.iSection=s_INVALID;
		pi->L_.iIndex=0;
		pi->L_.iLexime=new string();

		return pi;
	}
	void del_inh_L__S(Inh_Attr *pia)
	{
		delete pia->L_.iLexime;
	}

	Syn_Attr* init_syn_L__S()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e1.spTrueList=new instr_list();
		ps->e1.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_L__S(Syn_Attr *psa)
	{
		delete psa->e1.spTrueList;
		delete psa->e1.spFalseList;
	}

	Inh_Attr* init_inh_L__L__()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->L__.iSection=s_INVALID;
		pi->L__.iIndex=0;
		pi->L__.iLexime=new string();

		return pi;
	}
	void del_inh_L__L__(Inh_Attr *pia)
	{
		delete pia->L__.iLexime;
	}



	Inh_Attr* init_inh_L__1_L_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->L_.iSection=s_INVALID;
		pi->L_.iIndex=0;
		pi->L_.iLexime=new string();

		return pi;
	}
	void del_inh_L__1_L_(Inh_Attr *pia)
	{
		delete pia->L_.iLexime;
	}



	Inh_Attr* init_inh_V_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->V.iSection=s_INVALID;

		pi->V.iLine=0;

		pi->V.iType.type=t_VOID;
		pi->V.iType.is_array=false;
		pi->V.iType.length=0;

		pi->V.iLexime=new string();

		return pi;
	}
	void del_inh_V_A(Inh_Attr *pia)
	{
		delete pia->V.iLexime;
	}

	Inh_Attr* init_inh_V_opt2()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->opt2.iSection=s_INVALID;
		pi->opt2.iLexime=new string();

		return pi;
	}
	void del_inh_V_opt2(Inh_Attr *pia)
	{
		delete pia->opt2.iLexime;
	}

	Inh_Attr* init_inh_V_V_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->V_.iSection=s_INVALID;

		pi->V_.iType.type=t_VOID;
		pi->V_.iType.is_array=false;
		pi->V_.iType.length=0;

		return pi;
	}



	Inh_Attr* init_inh_V_1_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->V_.iSection=s_INVALID;

		pi->V_.iType.type=t_VOID;
		pi->V_.iType.is_array=false;
		pi->V_.iType.length=0;

		return pi;
	}
	Temp_Var* init_temp_V_1_A()
	{
		Temp_Var *pt=new Temp_Var();

		pt->V__id.tLine=0;
		pt->V__id.tLexime=new string();

		return pt;
	}
	void del_temp_V_1_A(Temp_Var *ptv)
	{
		delete ptv->V__id.tLexime;
	}

	Inh_Attr* init_inh_V_1_opt2()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->opt2.iSection=s_INVALID;
		pi->opt2.iLexime=new string();

		return pi;
	}
	void del_inh_V_1_opt2(Inh_Attr *pia)
	{
		delete pia->opt2.iLexime;
	}

	Inh_Attr* init_inh_V_1_V_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->V_.iSection=s_INVALID;

		pi->V_.iType.type=t_VOID;
		pi->V_.iType.is_array=false;
		pi->V_.iType.length=0;

		return pi;
	}



	Temp_Var* init_temp_opt2A_A()
	{
		Temp_Var *pt=new Temp_Var();

		pt->op_line.tLine=0;

		return pt;
	}

	Inh_Attr* init_inh_opt2A_e1()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e1.iSection=s_INVALID;

		return pi;
	}

	Inh_Attr* init_inh_opt2A_S()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->opt2.iSection=s_INVALID;
		pi->opt2.iLexime=new string();

		return pi;
	}
	void del_inh_opt2A_S(Inh_Attr *pia)
	{
		delete pia->opt2.iLexime;
	}

	Syn_Attr* init_syn_opt2A_S()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e1.spTrueList=new instr_list();
		ps->e1.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_opt2A_S(Syn_Attr *psa)
	{
		delete psa->e1.spTrueList;
		delete psa->e1.spFalseList;
	}



	Inh_Attr* init_inh_F_A1()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->F.iLine=0;

		pi->F.iType.type=t_VOID;
		pi->F.iType.is_array=false;
		pi->F.iType.length=0;

		pi->F.iLexime=new string();

		return pi;
	}
	void del_inh_F_A1(Inh_Attr *pia)
	{
		delete pia->F.iLexime;
	}


	Inh_Attr* init_inh_F_stmts()
	{
		Inh_Attr *pi=new Inh_Attr();

		//初始化为无效地址
		pi->stmts.iAddr.section=s_INVALID;
		pi->stmts.iAddr.offset=-1;

		//初始化为空指针
		pi->stmts.ipBreakList=0;
		pi->stmts.ipContinueList=0;
		pi->stmts.ipVarInstrList=0;

		return pi;
	}

	Syn_Attr* init_syn_F_S()
	{
		Syn_Attr *ps=new Syn_Attr();

		//初始化为0
		ps->stmts.sRetCnt=0;

		//初始化为空表
		ps->stmts.spNextList=new instr_list();

		return ps;
	}
	void del_syn_F_S(Syn_Attr *psa)
	{
		delete psa->stmts.spNextList;
	}



	Syn_Attr* init_syn_param_S()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->B.sType.type=t_VOID;
		ps->B.sType.is_array=false;
		ps->B.sType.length=0;

		return ps;
	}

	Temp_Var* init_temp_param_A()
	{
		Temp_Var *pt=new Temp_Var();

		pt->param_id.tLine=0;
		pt->param_id.tLexime=new string();

		return pt;
	}
	void del_temp_param_A(Temp_Var *ptv)
	{
		delete ptv->param_id.tLexime;	
	}

	Inh_Attr* init_inh_param_tail()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->tail.iLine=0;

		pi->tail.iType.type=t_VOID;
		pi->tail.iType.is_array=false;
		pi->tail.iType.length=0;

		pi->tail.iLexime=new string();

		return pi;
	}
	void del_inh_param_tail(Inh_Attr *pia)
	{
		delete pia->tail.iLexime;
	}



	Inh_Attr* init_inh_tail1_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->tail.iLine=0;

		pi->tail.iType.type=t_VOID;
		pi->tail.iType.is_array=false;
		pi->tail.iType.length=0;

		pi->tail.iLexime=new string();

		return pi;
	}
	void del_inh_tail1_A(Inh_Attr *pia)
	{
		delete pia->tail.iLexime;
	}

	Inh_Attr* init_inh_tail2_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->tail.iLine=0;

		pi->tail.iType.type=t_VOID;
		pi->tail.iType.is_array=false;
		pi->tail.iType.length=0;

		pi->tail.iLexime=new string();

		return pi;
	}
	void del_inh_tail2_A(Inh_Attr *pia)
	{
		delete pia->tail.iLexime;
	}



	Syn_Attr* init_syn_optexpr1A_S()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->size.tLine=0;
		ps->size.tValue=-1;

		return ps;
	}



	Temp_Var* init_temp_size_A()
	{
		Temp_Var *pt=new Temp_Var();

		pt->A_const.tLine=0;
		pt->A_const.tValue=-1;

		return pt;
	}



	Inh_Attr* init_inh_stmt2_expr()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->expr.iSection=s_LOCAL;

		return pi;
	}

	Syn_Attr* init_syn_stmt2_S()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->expr.spTrueList=new instr_list();
		ps->expr.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_stmt2_S(Syn_Attr *psa)
	{
		delete psa->expr.spTrueList;
		delete psa->expr.spFalseList;
	}



	Inh_Attr* init_inh_stmt3_expr()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->expr.iSection=s_LOCAL;

		return pi;
	}

	Temp_Var* init_temp_stmt3_S1()
	{
		Temp_Var *pt=new Temp_Var();

		pt->if_line.tLine=0;

		return pt;
	}
	Syn_Attr* init_syn_stmt3_S1()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->expr.spTrueList=new instr_list();
		ps->expr.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_stmt3_S1(Syn_Attr *psa)
	{
		delete psa->expr.spTrueList;
		delete psa->expr.spFalseList;
	}

	Inh_Attr* init_inh_stmt3_stmt()
	{
		Inh_Attr *pi=new Inh_Attr();

		//初始化为无效地址
		pi->stmt.iAddr.section=s_INVALID;
		pi->stmt.iAddr.offset=-1;

		//初始化为空指针
		pi->stmt.ipBreakList=0;
		pi->stmt.ipContinueList=0;
		pi->stmt.ipVarInstrList=0;

		return pi;
	}

	Syn_Attr* init_syn_stmt3_S2()
	{
		Syn_Attr *ps=new Syn_Attr();

		//初始化为0
		ps->stmt.sRetCnt=0;

		//初始化为空表
		ps->stmt.spNextList=new instr_list();

		return ps;
	}
	void del_syn_stmt3_S2(Syn_Attr *psa)
	{
		delete psa->stmt.spNextList;
	}

	Inh_Attr* init_inh_stmt3_E()
	{
		Inh_Attr *pi=new Inh_Attr();

		//初始化为无效地址
		pi->E.iAddr.section=s_INVALID;
		pi->E.iAddr.offset=-1;

		//初始化为空指针
		pi->E.ipBreakList=0;
		pi->E.ipContinueList=0;
		pi->E.ipVarInstrList=0;
		pi->E.ipFalseList=0;
		pi->E.ipNextList=0;

		return pi;
	}
	void del_inh_stmt3_E(Inh_Attr *pia)
	{
		delete pia->E.ipFalseList;	//此处释放由expr传递过来的falselist
		delete pia->E.ipNextList;	//此处释放由S(stmt)传递过来的nextlist
	}

	Syn_Attr* init_syn_stmt3_S3()
	{
		Syn_Attr *ps=new Syn_Attr();

		//初始化为0
		ps->E.sRetCnt=0;

		//初始化为空表
		ps->E.spNextList=new instr_list();

		return ps;
	}
	void del_syn_stmt3_S3(Syn_Attr *psa)
	{
		delete psa->E.spNextList;
	}



	Inh_Attr* init_inh_stmt4_expr()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->expr.iSection=s_LOCAL;

		return pi;
	}

	Temp_Var* init_temp_stmt4_S1()
	{
		Temp_Var *pt=new Temp_Var();

		pt->while_line.tLine=0;

		return pt;
	}
	Syn_Attr* init_syn_stmt4_S1()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->expr.spTrueList=new instr_list();
		ps->expr.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_stmt4_S1(Syn_Attr *psa)
	{
		delete psa->expr.spTrueList;
		delete psa->expr.spFalseList;
	}

	Inh_Attr* init_inh_stmt4_stmt()
	{
		Inh_Attr *pi=new Inh_Attr();

		//初始化为无效地址
		pi->stmt.iAddr.section=s_INVALID;
		pi->stmt.iAddr.offset=-1;

		//初始化为空指针
		pi->stmt.ipBreakList=0;
		pi->stmt.ipContinueList=0;
		pi->stmt.ipVarInstrList=0;

		return pi;
	}

	Temp_Var* init_temp_stmt4_S2()
	{
		Temp_Var *pt=new Temp_Var();

		pt->while_begin_continue_list.tBegin=-1;
		pt->while_begin_continue_list.tpContinueList=new instr_list();

		return pt;
	}
	void del_temp_stmt4_S2(Temp_Var *ptv)
	{
		delete ptv->while_begin_continue_list.tpContinueList;
	}
	Syn_Attr* init_syn_stmt4_S2()
	{
		Syn_Attr *ps=new Syn_Attr();

		//初始化为0
		ps->stmt.sRetCnt=0;

		//初始化为空表
		ps->stmt.spNextList=new instr_list();

		return ps;
	}
	void del_syn_stmt4_S2(Syn_Attr *psa)
	{
		delete psa->stmt.spNextList;
	}



	Inh_Attr* init_inh_stmt5_stmt()
	{
		Inh_Attr *pi=new Inh_Attr();

		//初始化为无效地址
		pi->stmt.iAddr.section=s_INVALID;
		pi->stmt.iAddr.offset=-1;

		//初始化为空指针
		pi->stmt.ipBreakList=0;
		pi->stmt.ipContinueList=0;
		pi->stmt.ipVarInstrList=0;

		return pi;
	}

	Temp_Var* init_temp_stmt5_S1()
	{
		Temp_Var *pt=new Temp_Var();

		pt->do_stmt_continue_list.tpContinueList=new instr_list();

		return pt;
	}
	void del_temp_stmt5_S1(Temp_Var *ptv)
	{
		delete ptv->do_stmt_continue_list.tpContinueList;
	}
	Syn_Attr* init_syn_stmt5_S1()
	{
		Syn_Attr *ps=new Syn_Attr();

		//初始化为0
		ps->stmt.sRetCnt=0;

		//初始化为空表
		ps->stmt.spNextList=new instr_list();

		return ps;
	}
	void del_syn_stmt5_S1(Syn_Attr *psa)
	{
		delete psa->stmt.spNextList;
	}

	Inh_Attr* init_inh_stmt5_expr()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->expr.iSection=s_LOCAL;

		return pi;
	}

	Temp_Var* init_temp_stmt5_S2()
	{
		Temp_Var *pt=new Temp_Var();

		pt->do_expr.tLine=0;
		pt->do_expr.tBegin=-1;

		return pt;
	}
	Syn_Attr* init_syn_stmt5_S2()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->expr.spTrueList=new instr_list();
		ps->expr.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_stmt5_S2(Syn_Attr *psa)
	{
		delete psa->expr.spTrueList;
		delete psa->expr.spFalseList;
	}



	Inh_Attr* init_inh_stmt6_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		//初始化为无效地址
		pi->stmt.iAddr.section=s_INVALID;
		pi->stmt.iAddr.offset=-1;

		//初始化为空指针
		pi->stmt.ipBreakList=0;
		pi->stmt.ipContinueList=0;
		pi->stmt.ipVarInstrList=0;

		return pi;
	}
	Temp_Var* init_temp_stmt6_A()
	{
		Temp_Var *pt=new Temp_Var();

		pt->break_line.tLine=0;

		return pt;
	}



	Inh_Attr* init_inh_stmt7_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		//初始化为无效地址
		pi->stmt.iAddr.section=s_INVALID;
		pi->stmt.iAddr.offset=-1;

		//初始化为空指针
		pi->stmt.ipBreakList=0;
		pi->stmt.ipContinueList=0;
		pi->stmt.ipVarInstrList=0;

		return pi;
	}
	Temp_Var* init_temp_stmt7_A()
	{
		Temp_Var *pt=new Temp_Var();

		pt->continue_line.tLine=0;

		return pt;
	}



	Inh_Attr* init_inh_stmt8_optexpr3()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->optexpr3.iLine=0;

		return pi;
	}



	Inh_Attr* init_inh_stmt9_optexpr2()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->optexpr2.iLine=0;
		pi->optexpr2.iValFlag=true;

		return pi;
	}

	Syn_Attr* init_syn_stmt9_S1()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->optexpr2.spFalseList=new instr_list();
		ps->optexpr2.spTrueList=new instr_list();

		return ps;
	}
	void del_syn_stmt9_S1(Syn_Attr *psa)
	{
		delete psa->optexpr2.spFalseList;
		delete psa->optexpr2.spTrueList;
	}

	Temp_Var* init_temp_stmt9_A2()
	{
		Temp_Var *pt=new Temp_Var();

		pt->for_expr.tBegin=-1;
		pt->for_expr.tpOptexpr2TrueList=0;	//初始化为空指针,不分配内存

		return pt;
	}
	void del_temp_stmt9_A2(Temp_Var *ptv)
	{
		delete ptv->for_expr.tpOptexpr2TrueList;
	}

	Inh_Attr* init_inh_stmt9_stmt()
	{
		Inh_Attr *pi=new Inh_Attr();

		//初始化为无效地址
		pi->stmt.iAddr.section=s_INVALID;
		pi->stmt.iAddr.offset=-1;

		//初始化为空指针
		pi->stmt.ipBreakList=0;
		pi->stmt.ipContinueList=0;
		pi->stmt.ipVarInstrList=0;

		return pi;
	}

	Temp_Var* init_temp_stmt9_S2()
	{
		Temp_Var *pt=new Temp_Var();

		pt->for_stmt_continue_continue_list.tContinue=-1;
		pt->for_stmt_continue_continue_list.tpContinueList=new instr_list();

		return pt;
	}
	void del_temp_stmt9_S2(Temp_Var *ptv)
	{
		delete ptv->for_stmt_continue_continue_list.tpContinueList;
	}
	Syn_Attr* init_syn_stmt9_S2()
	{
		Syn_Attr *ps=new Syn_Attr();

		//初始化为0
		ps->stmt.sRetCnt=0;

		//初始化为空表
		ps->stmt.spNextList=new instr_list();

		return ps;
	}
	void del_syn_stmt9_S2(Syn_Attr *psa)
	{
		delete psa->stmt.spNextList;
	}



	Inh_Attr* init_inh_stmt10_expr()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->expr.iSection=s_LOCAL;

		return pi;
	}

	Temp_Var* init_temp_stmt10_S1()
	{
		Temp_Var *pt=new Temp_Var();

		pt->switch_expr_line.tLine=0;

		return pt;
	}
	Syn_Attr* init_syn_stmt10_S1()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->expr.spTrueList=new instr_list();
		ps->expr.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_stmt10_S1(Syn_Attr *psa)
	{
		delete psa->expr.spTrueList;
		delete psa->expr.spFalseList;
	}

	Inh_Attr* init_inh_stmt10_stmt()
	{
		Inh_Attr *pi=new Inh_Attr();

		//初始化为无效地址
		pi->stmt.iAddr.section=s_INVALID;
		pi->stmt.iAddr.offset=-1;

		//初始化为空指针
		pi->stmt.ipBreakList=0;
		pi->stmt.ipContinueList=0;
		pi->stmt.ipVarInstrList=0;

		return pi;
	}

	Temp_Var* init_temp_stmt10_S2()
	{
		Temp_Var *pt=new Temp_Var();

		pt->swtich_stmt_testlist_var_instr_list.tpTestList=new instr_list();
		pt->swtich_stmt_testlist_var_instr_list.tpVarInstrList=new var_instr_list();

		return pt;
	}
	void del_temp_stmt10_S2(Temp_Var *ptv)
	{
		delete ptv->swtich_stmt_testlist_var_instr_list.tpTestList;
		delete ptv->swtich_stmt_testlist_var_instr_list.tpVarInstrList;
	}
	Syn_Attr* init_syn_stmt10_S2()
	{
		Syn_Attr *ps=new Syn_Attr();

		//初始化为0
		ps->stmt.sRetCnt=0;

		//初始化为空表
		ps->stmt.spNextList=new instr_list();

		return ps;
	}
	void del_syn_stmt10_S2(Syn_Attr *psa)
	{
		delete psa->stmt.spNextList;
	}



	Inh_Attr* init_inh_stmt11_S1()
	{
		Inh_Attr *pi=new Inh_Attr();

		//初始化为无效地址
		pi->stmt.iAddr.section=s_INVALID;
		pi->stmt.iAddr.offset=-1;

		//初始化为空指针
		pi->stmt.ipBreakList=0;
		pi->stmt.ipContinueList=0;
		pi->stmt.ipVarInstrList=0;

		return pi;
	}
	Syn_Attr* init_syn_stmt11_S1()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->label.tLine=0;

		return ps;
	}

	Temp_Var* init_temp_stmt11_A()
	{
		Temp_Var *pt=new Temp_Var();

		pt->op_line.tLine=0;

		return pt;
	}

	Inh_Attr* init_inh_stmt11_stmt()
	{
		Inh_Attr *pi=new Inh_Attr();

		//初始化为无效地址
		pi->stmt.iAddr.section=s_INVALID;
		pi->stmt.iAddr.offset=-1;

		//初始化为空指针
		pi->stmt.ipBreakList=0;
		pi->stmt.ipContinueList=0;
		pi->stmt.ipVarInstrList=0;

		return pi;
	}

	Syn_Attr* init_syn_stmt11_S2()
	{
		Syn_Attr *ps=new Syn_Attr();

		//初始化为0
		ps->stmt.sRetCnt=0;

		//初始化为空表
		ps->stmt.spNextList=new instr_list();

		return ps;
	}
	void del_syn_stmt11_S2(Syn_Attr *psa)
	{
		delete psa->stmt.spNextList;
	}



	Inh_Attr* init_inh_stmt12_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		//初始化为无效地址
		pi->stmt.iAddr.section=s_INVALID;
		pi->stmt.iAddr.offset=-1;

		//初始化为空指针
		pi->stmt.ipBreakList=0;
		pi->stmt.ipContinueList=0;
		pi->stmt.ipVarInstrList=0;

		return pi;
	}
	Temp_Var* init_temp_stmt12_A()
	{
		Temp_Var *pt=new Temp_Var();

		pt->op_line.tLine=0;

		return pt;
	}

	Inh_Attr* init_inh_stmt12_stmt()
	{
		Inh_Attr *pi=new Inh_Attr();

		//初始化为无效地址
		pi->stmt.iAddr.section=s_INVALID;
		pi->stmt.iAddr.offset=-1;

		//初始化为空指针
		pi->stmt.ipBreakList=0;
		pi->stmt.ipContinueList=0;
		pi->stmt.ipVarInstrList=0;

		return pi;
	}

	Syn_Attr* init_syn_stmt12_S()
	{
		Syn_Attr *ps=new Syn_Attr();

		//初始化为0
		ps->stmt.sRetCnt=0;

		//初始化为空表
		ps->stmt.spNextList=new instr_list();

		return ps;
	}
	void del_syn_stmt12_S(Syn_Attr *psa)
	{
		delete psa->stmt.spNextList;
	}



	Inh_Attr* init_inh_stmt13_stmts()
	{
		Inh_Attr *pi=new Inh_Attr();

		//初始化为无效地址
		pi->stmts.iAddr.section=s_INVALID;
		pi->stmts.iAddr.offset=-1;

		//初始化为空指针
		pi->stmts.ipBreakList=0;
		pi->stmts.ipContinueList=0;
		pi->stmts.ipVarInstrList=0;

		return pi;
	}

	Syn_Attr* init_syn_stmt13_S()
	{
		Syn_Attr *ps=new Syn_Attr();

		//初始化为0
		ps->stmts.sRetCnt=0;

		//初始化为空表
		ps->stmts.spNextList=new instr_list();

		return ps;
	}
	void del_syn_stmt13_S(Syn_Attr *psa)
	{
		delete psa->stmts.spNextList;
	}



	Inh_Attr* init_inh_E_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		//初始化为无效地址
		pi->E.iAddr.section=s_INVALID;
		pi->E.iAddr.offset=-1;

		//初始化为空指针
		pi->E.ipBreakList=0;
		pi->E.ipContinueList=0;
		pi->E.ipVarInstrList=0;
		pi->E.ipFalseList=0;
		pi->E.ipNextList=0;

		return pi;
	}
	void del_inh_E_A(Inh_Attr *pia)
	{
		delete pia->E.ipFalseList;	//此处释放由E传递过来的ifalselist
		delete pia->E.ipNextList;	//此处释放由E传递过来的inextlist
	}

	Inh_Attr* init_inh_E_stmt()
	{
		Inh_Attr *pi=new Inh_Attr();

		//初始化为无效地址
		pi->stmt.iAddr.section=s_INVALID;
		pi->stmt.iAddr.offset=-1;

		//初始化为空指针
		pi->stmt.ipBreakList=0;
		pi->stmt.ipContinueList=0;
		pi->stmt.ipVarInstrList=0;

		return pi;
	}

	Inh_Attr* init_inh_E_S()
	{
		Inh_Attr *pi=new Inh_Attr();

		//初始化为无效地址
		pi->E.iAddr.section=s_INVALID;
		pi->E.iAddr.offset=-1;

		//初始化为空指针
		pi->E.ipBreakList=0;
		pi->E.ipContinueList=0;
		pi->E.ipVarInstrList=0;
		pi->E.ipFalseList=0;
		pi->E.ipNextList=0;

		return pi;
	}
	void del_inh_E_S(Inh_Attr *pia)
	{
		delete pia->E.ipFalseList;	//此处释放由A传递过来的ifalselist
		delete pia->E.ipNextList;	//此处释放由A传递过来的inextlist
	}
	Syn_Attr* init_syn_E_S()
	{
		Syn_Attr *ps=new Syn_Attr();

		//初始化为0
		ps->stmt.sRetCnt=0;

		//初始化为空表
		ps->stmt.spNextList=new instr_list();

		return ps;
	}
	void del_syn_E_S(Syn_Attr *psa)
	{
		delete psa->stmt.spNextList;
	}



	Inh_Attr* init_inh_stmts_stmt()
	{
		Inh_Attr *pi=new Inh_Attr();

		//初始化为无效地址
		pi->stmt.iAddr.section=s_INVALID;
		pi->stmt.iAddr.offset=-1;

		//初始化为空指针
		pi->stmt.ipBreakList=0;
		pi->stmt.ipContinueList=0;
		pi->stmt.ipVarInstrList=0;

		return pi;
	}

	Syn_Attr* init_syn_stmts_S1()
	{
		Syn_Attr *ps=new Syn_Attr();

		//初始化为0
		ps->stmt.sRetCnt=0;

		//初始化为空表
		ps->stmt.spNextList=new instr_list();

		return ps;
	}
	void del_syn_stmts_S1(Syn_Attr *psa)
	{
		delete psa->stmt.spNextList;
	}

	Inh_Attr* init_inh_stmts_stmts()
	{
		Inh_Attr *pi=new Inh_Attr();

		//初始化为无效地址
		pi->stmts.iAddr.section=s_INVALID;
		pi->stmts.iAddr.offset=-1;

		//初始化为空指针
		pi->stmts.ipBreakList=0;
		pi->stmts.ipContinueList=0;
		pi->stmts.ipVarInstrList=0;

		return pi;
	}

	Syn_Attr* init_syn_stmts_S2()
	{
		Syn_Attr *ps=new Syn_Attr();

		//初始化为0
		ps->stmts.sRetCnt=0;

		//初始化为空表
		ps->stmts.spNextList=new instr_list();

		return ps;
	}
	void del_syn_stmts_S2(Syn_Attr *psa)
	{
		delete psa->stmts.spNextList;
	}



	Inh_Attr* init_inh_optexpr2_expr()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->expr.iSection=s_LOCAL;

		return pi;
	}

	Inh_Attr* init_inh_optexpr2_S()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->optexpr2.iLine=0;

		return pi;
	}
	Syn_Attr* init_syn_optexpr2_S()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->expr.spTrueList=new instr_list();
		ps->expr.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_optexpr2_S(Syn_Attr *psa)
	{
		delete psa->expr.spTrueList;
		delete psa->expr.spFalseList;
	}

	Inh_Attr* init_inh_optexpr2_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->optexpr2.iLine=0;

		return pi;
	}



	Inh_Attr* init_inh_optexpr3_expr()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->expr.iSection=s_LOCAL;

		return pi;
	}

	Inh_Attr* init_inh_optexpr3_S()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->optexpr3.iLine=0;

		return pi;
	}
	Syn_Attr* init_syn_optexpr3_S()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->expr.spTrueList=new instr_list();
		ps->expr.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_optexpr3_S(Syn_Attr *psa)
	{
		delete psa->expr.spTrueList;
		delete psa->expr.spFalseList;
	}

	Inh_Attr* init_inh_optexpr3_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->optexpr3.iLine=0;

		return pi;
	}




	Temp_Var* init_temp_label_op_minus()
	{
		Temp_Var *pt=new Temp_Var();

		pt->op_line.tLine=0;

		return pt;
	}

	Temp_Var* init_temp_label_A()
	{
		Temp_Var *pt=new Temp_Var();

		pt->case_const.tLine=0;

		return pt;
	}



	Inh_Attr* init_inh_expr_e1()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e1.iSection=s_INVALID;

		return pi;
	}

	Syn_Attr* init_syn_expr_S1()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e1.spTrueList=new instr_list();
		ps->e1.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_expr_S1(Syn_Attr *psa)
	{
		delete psa->e1.spTrueList;
		delete psa->e1.spFalseList;
	}

	Inh_Attr* init_inh_expr_expr_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->expr_.iSection=s_INVALID;
		pi->expr_.ipFalseList=0;
		pi->expr_.ipTrueList=0;

		return pi;
	}
	void del_inh_expr_expr_(Inh_Attr *pia)
	{
		delete pia->expr_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->expr_.ipTrueList;	//	
	}

	Syn_Attr* init_syn_expr_S2()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->expr_.spTrueList=new instr_list();
		ps->expr_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_expr_S2(Syn_Attr *psa)
	{
		delete psa->expr_.spTrueList;
		delete psa->expr_.spFalseList;
	}



	Inh_Attr* init_inh_expr__A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->expr_.iSection=s_INVALID;
		pi->expr_.ipFalseList=0;
		pi->expr_.ipTrueList=0;

		return pi;
	}
	void del_inh_expr__A(Inh_Attr *pia)
	{
		delete pia->expr_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->expr_.ipTrueList;	//	
	}

	Inh_Attr* init_inh_expr__e1()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e1.iSection=s_INVALID;

		return pi;
	}

	Syn_Attr* init_syn_expr__S1()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e1.spTrueList=new instr_list();
		ps->e1.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_expr__S1(Syn_Attr *psa)
	{
		delete psa->e1.spTrueList;
		delete psa->e1.spFalseList;
	}

	Inh_Attr* init_inh_expr__expr_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->expr_.iSection=s_INVALID;
		pi->expr_.ipFalseList=0;
		pi->expr_.ipTrueList=0;

		return pi;
	}
	void del_inh_expr__expr_(Inh_Attr *pia)
	{
		delete pia->expr_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->expr_.ipTrueList;	//	
	}

	Syn_Attr* init_syn_expr__S2()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->expr_.spTrueList=new instr_list();
		ps->expr_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_expr__S2(Syn_Attr *psa)
	{
		delete psa->expr_.spTrueList;
		delete psa->expr_.spFalseList;
	}



	Temp_Var* init_temp_e1A_A()
	{
		Temp_Var *pt=new Temp_Var();

		pt->e1_id.tLine=0;
		pt->e1_id.tLexime=new string();

		return pt;
	}
	void del_temp_e1A_A(Temp_Var *ptv)
	{
		delete ptv->e1_id.tLexime;
	}

	Inh_Attr* init_inh_e1A_T1()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->T1.iSection=s_INVALID;
		pi->T1.iLine=0;
		pi->T1.iLexime=new string();

		return pi;
	}
	void del_inh_e1A_T1(Inh_Attr *pia)
	{
		delete pia->T1.iLexime;
	}

	Syn_Attr* init_syn_e1A_S()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->T1.spTrueList=new instr_list();
		ps->T1.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e1A_S(Syn_Attr *psa)
	{
		delete psa->T1.spTrueList;
		delete psa->T1.spFalseList;
	}

	Inh_Attr* init_inh_e1B_e2()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e2.iSection=s_INVALID;

		return pi;
	}

	Syn_Attr* init_syn_e1B__S()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e2.spTrueList=new instr_list();
		ps->e2.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e1B_S(Syn_Attr *psa)
	{
		delete psa->e2.spTrueList;
		delete psa->e2.spFalseList;
	}



	Inh_Attr* init_inh_e2_e3()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e3.iSection=s_INVALID;

		return pi;
	}

	Syn_Attr* init_syn_e2_S1()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e3.spTrueList=new instr_list();
		ps->e3.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e2_S1(Syn_Attr *psa)
	{
		delete psa->e3.spTrueList;
		delete psa->e3.spFalseList;
	}

	Inh_Attr* init_inh_e2_e2_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e2_.iSection=s_INVALID;
		pi->e2_.ipFalseList=0;
		pi->e2_.ipTrueList=0;

		return pi;
	}
	void del_inh_e2_e2_(Inh_Attr *pia)
	{
		delete pia->e2_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e2_.ipTrueList;
	}

	Syn_Attr* init_syn_e2_S2()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e2_.spTrueList=new instr_list();
		ps->e2_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e2_S2(Syn_Attr *psa)
	{
		delete psa->e2_.spTrueList;
		delete psa->e2_.spFalseList;
	}



	Inh_Attr* init_inh_e2_1_A1()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e2_.iSection=s_INVALID;
		pi->e2_.ipFalseList=0;
		pi->e2_.ipTrueList=0;

		return pi;
	}
	void del_inh_e2_1_A1(Inh_Attr *pia)
	{
		delete pia->e2_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e2_.ipTrueList;
	}
	Temp_Var* init_temp_e2_1_A1()
	{
		Temp_Var *pt=new Temp_Var();

		pt->op_line.tLine=0;

		return pt;
	}

	Inh_Attr* init_inh_e2_1_e3()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e3.iSection=s_INVALID;

		return pi;
	}

	Inh_Attr* init_inh_e2_1_S1()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e2_.iSection=s_INVALID;
		pi->e2_.ipFalseList=0;
		pi->e2_.ipTrueList=0;

		return pi;
	}
	void del_inh_e2_1_S1(Inh_Attr *pia)
	{
		delete pia->e2_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e2_.ipTrueList;
	}
	Syn_Attr* init_syn_e2_1_S1()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e3.spTrueList=new instr_list();
		ps->e3.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e2_1_S1(Syn_Attr *psa)
	{
		delete psa->e3.spTrueList;
		delete psa->e3.spFalseList;
	}

	Temp_Var* init_temp_e2_1_A2()
	{
		Temp_Var *pt=new Temp_Var();

		pt->op_line.tLine=0;

		return pt;
	}

	Inh_Attr* init_inh_e2_1_e2()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e2.iSection=s_INVALID;

		return pi;
	}

	Inh_Attr* init_inh_e2_1_S2()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e2_.iSection=s_INVALID;
		pi->e2_.ipFalseList=new instr_list();	//作为临时变量使用
		pi->e2_.ipTrueList=new instr_list();	//作为临时变量使用

		return pi;
	}
	void del_inh_e2_1_S2(Inh_Attr *pia)
	{
		delete pia->e2_.ipFalseList;	//释放临时内存
		delete pia->e2_.ipTrueList;
	}
	Temp_Var* init_temp_e2_1_S2()
	{
		Temp_Var *pt=new Temp_Var();

		pt->op_line.tLine=0;

		return pt;
	}
	Syn_Attr* init_syn_e2_1_S2()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e2.spTrueList=new instr_list();
		ps->e2.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e2_1_S2(Syn_Attr *psa)
	{
		delete psa->e2.spTrueList;
		delete psa->e2.spFalseList;
	}

	Inh_Attr* init_inh_e2_2_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e2_.iSection=s_INVALID;
		pi->e2_.ipFalseList=0;
		pi->e2_.ipTrueList=0;

		return pi;
	}
	void del_inh_e2_2_A(Inh_Attr *pia)
	{
		delete pia->e2_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e2_.ipTrueList;
	}



	Inh_Attr* init_inh_e3_e4()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e4.iSection=s_INVALID;

		return pi;
	}

	Syn_Attr* init_syn_e3_S1()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e4.spTrueList=new instr_list();
		ps->e4.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e3_S1(Syn_Attr *psa)
	{
		delete psa->e4.spTrueList;
		delete psa->e4.spFalseList;
	}

	Inh_Attr* init_inh_e3_e3_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e3_.iSection=s_INVALID;
		pi->e3_.ipFalseList=0;
		pi->e3_.ipTrueList=0;

		return pi;
	}
	void del_inh_e3_e3_(Inh_Attr *pia)
	{
		delete pia->e3_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e3_.ipTrueList;
	}

	Syn_Attr* init_syn_e3_S2()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e3_.spTrueList=new instr_list();
		ps->e3_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e3_S2(Syn_Attr *psa)
	{
		delete psa->e3_.spTrueList;
		delete psa->e3_.spFalseList;
	}



	Inh_Attr* init_inh_e3_1_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e3_.iSection=s_INVALID;
		pi->e3_.ipFalseList=0;
		pi->e3_.ipTrueList=0;

		return pi;
	}
	void del_inh_e3_1_A(Inh_Attr *pia)
	{
		delete pia->e3_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e3_.ipTrueList;
	}
	Temp_Var* init_temp_e3_1_A()
	{
		Temp_Var *pt=new Temp_Var();

		pt->op_line.tLine=0;

		return pt;
	}

	Inh_Attr* init_inh_e3_1_e4()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e4.iSection=s_INVALID;

		return pi;
	}

	Inh_Attr* init_inh_e3_1_S1()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e3_.iSection=s_INVALID;
		pi->e3_.ipFalseList=0;	
		pi->e3_.ipTrueList=0;

		return pi;
	}
	void del_inh_e3_1_S1(Inh_Attr *pia)
	{
		delete pia->e3_.ipFalseList;	
		delete pia->e3_.ipTrueList;
	}
	Temp_Var* init_temp_e3_1_S1()
	{
		Temp_Var *pt=new Temp_Var();

		pt->op_line.tLine=0;

		return pt;
	}
	Syn_Attr* init_syn_e3_1_S1()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e4.spTrueList=new instr_list();
		ps->e4.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e3_1_S1(Syn_Attr *psa)
	{
		delete psa->e4.spTrueList;
		delete psa->e4.spFalseList;
	}

	Inh_Attr* init_inh_e3_1_e3_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e3_.iSection=s_INVALID;
		pi->e3_.ipFalseList=0;
		pi->e3_.ipTrueList=0;

		return pi;
	}
	void del_inh_e3_1_e3_(Inh_Attr *pia)
	{
		delete pia->e3_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e3_.ipTrueList;
	}

	Syn_Attr* init_syn_e3_1_S2()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e3_.spTrueList=new instr_list();
		ps->e3_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e3_1_S2(Syn_Attr *psa)
	{
		delete psa->e3_.spTrueList;
		delete psa->e3_.spFalseList;
	}

	Inh_Attr* init_inh_e3_2_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e3_.iSection=s_INVALID;
		pi->e3_.ipFalseList=0;
		pi->e3_.ipTrueList=0;

		return pi;
	}
	void del_inh_e3_2_A(Inh_Attr *pia)
	{
		delete pia->e3_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e3_.ipTrueList;
	}



	Inh_Attr* init_inh_e4_e5()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e5.iSection=s_INVALID;

		return pi;
	}

	Syn_Attr* init_syn_e4_S1()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e5.spTrueList=new instr_list();
		ps->e5.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e4_S1(Syn_Attr *psa)
	{
		delete psa->e5.spTrueList;
		delete psa->e5.spFalseList;
	}

	Inh_Attr* init_inh_e4_e4_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e4_.iSection=s_INVALID;
		pi->e4_.ipFalseList=0;
		pi->e4_.ipTrueList=0;

		return pi;
	}
	void del_inh_e4_e4_(Inh_Attr *pia)
	{
		delete pia->e4_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e4_.ipTrueList;
	}

	Syn_Attr* init_syn_e4_S2()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e4_.spTrueList=new instr_list();
		ps->e4_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e4_S2(Syn_Attr *psa)
	{
		delete psa->e4_.spTrueList;
		delete psa->e4_.spFalseList;
	}



	Inh_Attr* init_inh_e4_1_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e4_.iSection=s_INVALID;
		pi->e4_.ipFalseList=0;
		pi->e4_.ipTrueList=0;

		return pi;
	}
	void del_inh_e4_1_A(Inh_Attr *pia)
	{
		delete pia->e4_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e4_.ipTrueList;
	}
	Temp_Var* init_temp_e4_1_A()
	{
		Temp_Var *pt=new Temp_Var();

		pt->op_line.tLine=0;

		return pt;
	}

	Inh_Attr* init_inh_e4_1_e5()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e5.iSection=s_INVALID;

		return pi;
	}

	Inh_Attr* init_inh_e4_1_S1()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e4_.iSection=s_INVALID;
		pi->e4_.ipFalseList=0;	
		pi->e4_.ipTrueList=0;

		return pi;
	}
	void del_inh_e4_1_S1(Inh_Attr *pia)
	{
		delete pia->e4_.ipFalseList;	
		delete pia->e4_.ipTrueList;
	}
	Temp_Var* init_temp_e4_1_S1()
	{
		Temp_Var *pt=new Temp_Var();

		pt->op_line.tLine=0;

		return pt;
	}
	Syn_Attr* init_syn_e4_1_S1()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e5.spTrueList=new instr_list();
		ps->e5.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e4_1_S1(Syn_Attr *psa)
	{
		delete psa->e5.spTrueList;
		delete psa->e5.spFalseList;
	}

	Inh_Attr* init_inh_e4_1_e4_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e4_.iSection=s_INVALID;
		pi->e4_.ipFalseList=0;
		pi->e4_.ipTrueList=0;

		return pi;
	}
	void del_inh_e4_1_e4_(Inh_Attr *pia)
	{
		delete pia->e4_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e4_.ipTrueList;
	}

	Syn_Attr* init_syn_e4_1_S2()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e4_.spTrueList=new instr_list();
		ps->e4_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e4_1_S2(Syn_Attr *psa)
	{
		delete psa->e4_.spTrueList;
		delete psa->e4_.spFalseList;
	}

	Inh_Attr* init_inh_e4_2_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e4_.iSection=s_INVALID;
		pi->e4_.ipFalseList=0;
		pi->e4_.ipTrueList=0;

		return pi;
	}
	void del_inh_e4_2_A(Inh_Attr *pia)
	{
		delete pia->e4_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e4_.ipTrueList;
	}



	Inh_Attr* init_inh_e5_e6()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e6.iSection=s_INVALID;

		return pi;
	}

	Syn_Attr* init_syn_e5_S1()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e6.spTrueList=new instr_list();
		ps->e6.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e5_S1(Syn_Attr *psa)
	{
		delete psa->e6.spTrueList;
		delete psa->e6.spFalseList;
	}

	Inh_Attr* init_inh_e5_e5_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e5_.iSection=s_INVALID;
		pi->e5_.ipFalseList=0;
		pi->e5_.ipTrueList=0;

		return pi;
	}
	void del_inh_e5_e5_(Inh_Attr *pia)
	{
		delete pia->e5_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e5_.ipTrueList;
	}

	Syn_Attr* init_syn_e5_S2()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e5_.spTrueList=new instr_list();
		ps->e5_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e5_S2(Syn_Attr *psa)
	{
		delete psa->e5_.spTrueList;
		delete psa->e5_.spFalseList;
	}



	Inh_Attr* init_inh_e5_1_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e5_.iSection=s_INVALID;
		pi->e5_.ipFalseList=0;
		pi->e5_.ipTrueList=0;

		return pi;
	}
	void del_inh_e5_1_A(Inh_Attr *pia)
	{
		delete pia->e5_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e5_.ipTrueList;
	}
	Temp_Var* init_temp_e5_1_A()
	{
		Temp_Var *pt=new Temp_Var();

		pt->op_line.tLine=0;

		return pt;
	}

	Inh_Attr* init_inh_e5_1_e6()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e6.iSection=s_INVALID;

		return pi;
	}

	Inh_Attr* init_inh_e5_1_S1()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e5_.iSection=s_INVALID;
		pi->e5_.ipFalseList=0;	
		pi->e5_.ipTrueList=0;

		return pi;
	}
	void del_inh_e5_1_S1(Inh_Attr *pia)
	{
		delete pia->e5_.ipFalseList;	
		delete pia->e5_.ipTrueList;
	}
	Temp_Var* init_temp_e5_1_S1()
	{
		Temp_Var *pt=new Temp_Var();

		pt->op_line.tLine=0;

		return pt;
	}
	Syn_Attr* init_syn_e5_1_S1()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e6.spTrueList=new instr_list();
		ps->e6.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e5_1_S1(Syn_Attr *psa)
	{
		delete psa->e6.spTrueList;
		delete psa->e6.spFalseList;
	}

	Inh_Attr* init_inh_e5_1_e5_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e5_.iSection=s_INVALID;
		pi->e5_.ipFalseList=0;
		pi->e5_.ipTrueList=0;

		return pi;
	}
	void del_inh_e5_1_e5_(Inh_Attr *pia)
	{
		delete pia->e5_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e5_.ipTrueList;
	}

	Syn_Attr* init_syn_e5_1_S2()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e5_.spTrueList=new instr_list();
		ps->e5_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e5_1_S2(Syn_Attr *psa)
	{
		delete psa->e5_.spTrueList;
		delete psa->e5_.spFalseList;
	}

	Inh_Attr* init_inh_e5_2_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e5_.iSection=s_INVALID;
		pi->e5_.ipFalseList=0;
		pi->e5_.ipTrueList=0;

		return pi;
	}
	void del_inh_e5_2_A(Inh_Attr *pia)
	{
		delete pia->e5_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e5_.ipTrueList;
	}



	Inh_Attr* init_inh_e6_e7()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e7.iSection=s_INVALID;

		return pi;
	}

	Syn_Attr* init_syn_e6_S1()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e7.spTrueList=new instr_list();
		ps->e7.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e6_S1(Syn_Attr *psa)
	{
		delete psa->e7.spTrueList;
		delete psa->e7.spFalseList;
	}

	Inh_Attr* init_inh_e6_e6_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e6_.iSection=s_INVALID;
		pi->e6_.ipFalseList=0;
		pi->e6_.ipTrueList=0;

		return pi;
	}
	void del_inh_e6_e6_(Inh_Attr *pia)
	{
		delete pia->e6_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e6_.ipTrueList;
	}

	Syn_Attr* init_syn_e6_S2()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e6_.spTrueList=new instr_list();
		ps->e6_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e6_S2(Syn_Attr *psa)
	{
		delete psa->e6_.spTrueList;
		delete psa->e6_.spFalseList;
	}



	Inh_Attr* init_inh_e6_1_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e6_.iSection=s_INVALID;
		pi->e6_.ipFalseList=0;
		pi->e6_.ipTrueList=0;

		return pi;
	}
	void del_inh_e6_1_A(Inh_Attr *pia)
	{
		delete pia->e6_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e6_.ipTrueList;
	}
	Temp_Var* init_temp_e6_1_A()
	{
		Temp_Var *pt=new Temp_Var();

		pt->op_line.tLine=0;

		return pt;
	}

	Inh_Attr* init_inh_e6_1_e7()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e7.iSection=s_INVALID;

		return pi;
	}

	Inh_Attr* init_inh_e6_1_S1()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e6_.iSection=s_INVALID;
		pi->e6_.ipFalseList=0;	
		pi->e6_.ipTrueList=0;

		return pi;
	}
	void del_inh_e6_1_S1(Inh_Attr *pia)
	{
		delete pia->e6_.ipFalseList;	
		delete pia->e6_.ipTrueList;
	}
	Temp_Var* init_temp_e6_1_S1()
	{
		Temp_Var *pt=new Temp_Var();

		pt->op_line.tLine=0;

		return pt;
	}
	Syn_Attr* init_syn_e6_1_S1()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e7.spTrueList=new instr_list();
		ps->e7.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e6_1_S1(Syn_Attr *psa)
	{
		delete psa->e7.spTrueList;
		delete psa->e7.spFalseList;
	}

	Inh_Attr* init_inh_e6_1_e6_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e6_.iSection=s_INVALID;
		pi->e6_.ipFalseList=0;
		pi->e6_.ipTrueList=0;

		return pi;
	}
	void del_inh_e6_1_e6_(Inh_Attr *pia)
	{
		delete pia->e6_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e6_.ipTrueList;
	}

	Syn_Attr* init_syn_e6_1_S2()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e6_.spTrueList=new instr_list();
		ps->e6_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e6_1_S2(Syn_Attr *psa)
	{
		delete psa->e6_.spTrueList;
		delete psa->e6_.spFalseList;
	}

	Inh_Attr* init_inh_e6_2_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e6_.iSection=s_INVALID;
		pi->e6_.ipFalseList=0;
		pi->e6_.ipTrueList=0;

		return pi;
	}
	void del_inh_e6_2_A(Inh_Attr *pia)
	{
		delete pia->e6_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e6_.ipTrueList;
	}



	Inh_Attr* init_inh_e7_e8()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e8.iSection=s_INVALID;

		return pi;
	}

	Syn_Attr* init_syn_e7_S1()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e8.spTrueList=new instr_list();
		ps->e8.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e7_S1(Syn_Attr *psa)
	{
		delete psa->e8.spTrueList;
		delete psa->e8.spFalseList;
	}

	Inh_Attr* init_inh_e7_e7_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e7_.iSection=s_INVALID;
		pi->e7_.ipFalseList=0;
		pi->e7_.ipTrueList=0;

		return pi;
	}
	void del_inh_e7_e7_(Inh_Attr *pia)
	{
		delete pia->e7_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e7_.ipTrueList;
	}

	Syn_Attr* init_syn_e7_S2()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e7_.spTrueList=new instr_list();
		ps->e7_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e7_S2(Syn_Attr *psa)
	{
		delete psa->e7_.spTrueList;
		delete psa->e7_.spFalseList;
	}



	Inh_Attr* init_inh_e7_1_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e7_.iSection=s_INVALID;
		pi->e7_.ipFalseList=0;
		pi->e7_.ipTrueList=0;

		return pi;
	}
	void del_inh_e7_1_A(Inh_Attr *pia)
	{
		delete pia->e7_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e7_.ipTrueList;
	}
	Temp_Var* init_temp_e7_1_A()
	{
		Temp_Var *pt=new Temp_Var();

		pt->op_line.tLine=0;

		return pt;
	}

	Inh_Attr* init_inh_e7_1_e8()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e8.iSection=s_INVALID;

		return pi;
	}

	Inh_Attr* init_inh_e7_1_S1()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e7_.iSection=s_INVALID;
		pi->e7_.ipFalseList=0;	
		pi->e7_.ipTrueList=0;

		return pi;
	}
	void del_inh_e7_1_S1(Inh_Attr *pia)
	{
		delete pia->e7_.ipFalseList;	
		delete pia->e7_.ipTrueList;
	}
	Temp_Var* init_temp_e7_1_S1()
	{
		Temp_Var *pt=new Temp_Var();

		pt->op_line.tLine=0;

		return pt;
	}
	Syn_Attr* init_syn_e7_1_S1()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e8.spTrueList=new instr_list();
		ps->e8.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e7_1_S1(Syn_Attr *psa)
	{
		delete psa->e8.spTrueList;
		delete psa->e8.spFalseList;
	}

	Inh_Attr* init_inh_e7_1_e7_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e7_.iSection=s_INVALID;
		pi->e7_.ipFalseList=0;
		pi->e7_.ipTrueList=0;

		return pi;
	}
	void del_inh_e7_1_e7_(Inh_Attr *pia)
	{
		delete pia->e7_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e7_.ipTrueList;
	}

	Syn_Attr* init_syn_e7_1_S2()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e7_.spTrueList=new instr_list();
		ps->e7_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e7_1_S2(Syn_Attr *psa)
	{
		delete psa->e7_.spTrueList;
		delete psa->e7_.spFalseList;
	}

	Inh_Attr* init_inh_e7_2_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e7_.iSection=s_INVALID;
		pi->e7_.ipFalseList=0;
		pi->e7_.ipTrueList=0;

		return pi;
	}
	void del_inh_e7_2_A(Inh_Attr *pia)
	{
		delete pia->e7_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e7_.ipTrueList;
	}



	Inh_Attr* init_inh_e8_e9()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e9.iSection=s_INVALID;

		return pi;
	}

	Syn_Attr* init_syn_e8_S1()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e9.spTrueList=new instr_list();
		ps->e9.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e8_S1(Syn_Attr *psa)
	{
		delete psa->e9.spTrueList;
		delete psa->e9.spFalseList;
	}

	Inh_Attr* init_inh_e8_e8_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e8_.iSection=s_INVALID;
		pi->e8_.ipFalseList=0;
		pi->e8_.ipTrueList=0;

		return pi;
	}
	void del_inh_e8_e8_(Inh_Attr *pia)
	{
		delete pia->e8_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e8_.ipTrueList;
	}

	Syn_Attr* init_syn_e8_S2()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e8_.spTrueList=new instr_list();
		ps->e8_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e8_S2(Syn_Attr *psa)
	{
		delete psa->e8_.spTrueList;
		delete psa->e8_.spFalseList;
	}



	Inh_Attr* init_inh_e8_1_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e8_.iSection=s_INVALID;
		pi->e8_.ipFalseList=0;
		pi->e8_.ipTrueList=0;

		return pi;
	}
	void del_inh_e8_1_A(Inh_Attr *pia)
	{
		delete pia->e8_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e8_.ipTrueList;
	}
	Temp_Var* init_temp_e8_1_A()
	{
		Temp_Var *pt=new Temp_Var();

		pt->op_line.tLine=0;

		return pt;
	}

	Inh_Attr* init_inh_e8_1_e9()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e9.iSection=s_INVALID;

		return pi;
	}

	Inh_Attr* init_inh_e8_1_S1()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e8_.iSection=s_INVALID;
		pi->e8_.ipFalseList=0;	
		pi->e8_.ipTrueList=0;

		return pi;
	}
	void del_inh_e8_1_S1(Inh_Attr *pia)
	{
		delete pia->e8_.ipFalseList;	
		delete pia->e8_.ipTrueList;
	}
	Temp_Var* init_temp_e8_1_S1()
	{
		Temp_Var *pt=new Temp_Var();

		pt->op_line.tLine=0;

		return pt;
	}
	Syn_Attr* init_syn_e8_1_S1()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e9.spTrueList=new instr_list();
		ps->e9.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e8_1_S1(Syn_Attr *psa)
	{
		delete psa->e9.spTrueList;
		delete psa->e9.spFalseList;
	}

	Inh_Attr* init_inh_e8_1_e8_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e8_.iSection=s_INVALID;
		pi->e8_.ipFalseList=0;
		pi->e8_.ipTrueList=0;

		return pi;
	}
	void del_inh_e8_1_e8_(Inh_Attr *pia)
	{
		delete pia->e8_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e8_.ipTrueList;
	}

	Syn_Attr* init_syn_e8_1_S2()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e8_.spTrueList=new instr_list();
		ps->e8_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e8_1_S2(Syn_Attr *psa)
	{
		delete psa->e8_.spTrueList;
		delete psa->e8_.spFalseList;
	}

	Inh_Attr* init_inh_e8_2_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e8_.iSection=s_INVALID;
		pi->e8_.ipFalseList=0;
		pi->e8_.ipTrueList=0;

		return pi;
	}
	void del_inh_e8_3_A(Inh_Attr *pia)
	{
		delete pia->e8_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e8_.ipTrueList;
	}



	Inh_Attr* init_inh_e9_e10()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e10.iSection=s_INVALID;

		return pi;
	}

	Syn_Attr* init_syn_e9_S1()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e10.spTrueList=new instr_list();
		ps->e10.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e9_S1(Syn_Attr *psa)
	{
		delete psa->e10.spTrueList;
		delete psa->e10.spFalseList;
	}

	Inh_Attr* init_inh_e9_e9_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e9_.iSection=s_INVALID;
		pi->e9_.ipFalseList=0;
		pi->e9_.ipTrueList=0;

		return pi;
	}
	void del_inh_e9_e9_(Inh_Attr *pia)
	{
		delete pia->e9_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e9_.ipTrueList;
	}

	Syn_Attr* init_syn_e9_S2()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e9_.spTrueList=new instr_list();
		ps->e9_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e9_S2(Syn_Attr *psa)
	{
		delete psa->e9_.spTrueList;
		delete psa->e9_.spFalseList;
	}



	Inh_Attr* init_inh_e9_1_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e9_.iSection=s_INVALID;
		pi->e9_.ipFalseList=0;
		pi->e9_.ipTrueList=0;

		return pi;
	}
	void del_inh_e9_1_A(Inh_Attr *pia)
	{
		delete pia->e9_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e9_.ipTrueList;
	}
	Temp_Var* init_temp_e9_1_A()
	{
		Temp_Var *pt=new Temp_Var();

		pt->op_line.tLine=0;

		return pt;
	}

	Inh_Attr* init_inh_e9_1_e10()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e10.iSection=s_INVALID;

		return pi;
	}

	Inh_Attr* init_inh_e9_1_S1()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e9_.iSection=s_INVALID;
		pi->e9_.ipFalseList=0;	
		pi->e9_.ipTrueList=0;

		return pi;
	}
	void del_inh_e9_1_S1(Inh_Attr *pia)
	{
		delete pia->e9_.ipFalseList;	
		delete pia->e9_.ipTrueList;
	}
	Temp_Var* init_temp_e9_1_S1()
	{
		Temp_Var *pt=new Temp_Var();

		pt->op_line.tLine=0;

		return pt;
	}
	Syn_Attr* init_syn_e9_1_S1()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e10.spTrueList=new instr_list();
		ps->e10.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e9_1_S1(Syn_Attr *psa)
	{
		delete psa->e10.spTrueList;
		delete psa->e10.spFalseList;
	}

	Inh_Attr* init_inh_e9_1_e9_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e9_.iSection=s_INVALID;
		pi->e9_.ipFalseList=0;
		pi->e9_.ipTrueList=0;

		return pi;
	}
	void del_inh_e9_1_e9_(Inh_Attr *pia)
	{
		delete pia->e9_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e9_.ipTrueList;
	}

	Syn_Attr* init_syn_e9_1_S2()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e9_.spTrueList=new instr_list();
		ps->e9_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e9_1_S2(Syn_Attr *psa)
	{
		delete psa->e9_.spTrueList;
		delete psa->e9_.spFalseList;
	}

	Inh_Attr* init_inh_e9_2_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e9_.iSection=s_INVALID;
		pi->e9_.ipFalseList=0;
		pi->e9_.ipTrueList=0;

		return pi;
	}
	void del_inh_e9_2_A(Inh_Attr *pia)
	{
		delete pia->e9_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e9_.ipTrueList;
	}



	Inh_Attr* init_inh_e10_e11()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e11.iSection=s_INVALID;

		return pi;
	}

	Syn_Attr* init_syn_e10_S1()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e11.spTrueList=new instr_list();
		ps->e11.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e10_S1(Syn_Attr *psa)
	{
		delete psa->e11.spTrueList;
		delete psa->e11.spFalseList;
	}

	Inh_Attr* init_inh_e10_e10_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e10_.iSection=s_INVALID;
		pi->e10_.ipFalseList=0;
		pi->e10_.ipTrueList=0;

		return pi;
	}
	void del_inh_e10_e10_(Inh_Attr *pia)
	{
		delete pia->e10_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e10_.ipTrueList;
	}

	Syn_Attr* init_syn_e10_S2()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e10_.spTrueList=new instr_list();
		ps->e10_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e10_S2(Syn_Attr *psa)
	{
		delete psa->e10_.spTrueList;
		delete psa->e10_.spFalseList;
	}



	Inh_Attr* init_inh_e10_1_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e10_.iSection=s_INVALID;
		pi->e10_.ipFalseList=0;
		pi->e10_.ipTrueList=0;

		return pi;
	}
	void del_inh_e10_1_A(Inh_Attr *pia)
	{
		delete pia->e10_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e10_.ipTrueList;
	}
	Temp_Var* init_temp_e10_1_A()
	{
		Temp_Var *pt=new Temp_Var();

		pt->op_line.tLine=0;

		return pt;
	}

	Inh_Attr* init_inh_e10_1_e11()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e11.iSection=s_INVALID;

		return pi;
	}

	Inh_Attr* init_inh_e10_1_S1()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e10_.iSection=s_INVALID;
		pi->e10_.ipFalseList=0;	
		pi->e10_.ipTrueList=0;

		return pi;
	}
	void del_inh_e10_1_S1(Inh_Attr *pia)
	{
		delete pia->e10_.ipFalseList;	
		delete pia->e10_.ipTrueList;
	}
	Temp_Var* init_temp_e10_1_S1()
	{
		Temp_Var *pt=new Temp_Var();

		pt->op_line.tLine=0;

		return pt;
	}
	Syn_Attr* init_syn_e10_1_S1()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e11.spTrueList=new instr_list();
		ps->e11.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e10_1_S1(Syn_Attr *psa)
	{
		delete psa->e11.spTrueList;
		delete psa->e11.spFalseList;
	}

	Inh_Attr* init_inh_e10_1_e10_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e10_.iSection=s_INVALID;
		pi->e10_.ipFalseList=0;
		pi->e10_.ipTrueList=0;

		return pi;
	}
	void del_inh_e10_1_e10_(Inh_Attr *pia)
	{
		delete pia->e10_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e10_.ipTrueList;
	}

	Syn_Attr* init_syn_e10_1_S2()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e10_.spTrueList=new instr_list();
		ps->e10_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e10_1_S2(Syn_Attr *psa)
	{
		delete psa->e10_.spTrueList;
		delete psa->e10_.spFalseList;
	}

	Inh_Attr* init_inh_e10_2_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e10_.iSection=s_INVALID;
		pi->e10_.ipFalseList=0;
		pi->e10_.ipTrueList=0;

		return pi;
	}
	void del_inh_e10_2_A(Inh_Attr *pia)
	{
		delete pia->e10_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e10_.ipTrueList;
	}



	Inh_Attr* init_inh_e11_e12()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e12.iSection=s_INVALID;

		return pi;
	}

	Syn_Attr* init_syn_e11_S1()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e12.spTrueList=new instr_list();
		ps->e12.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e11_S1(Syn_Attr *psa)
	{
		delete psa->e12.spTrueList;
		delete psa->e12.spFalseList;
	}

	Inh_Attr* init_inh_e11_e11_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e11_.iSection=s_INVALID;
		pi->e11_.ipFalseList=0;
		pi->e11_.ipTrueList=0;

		return pi;
	}
	void del_inh_e11_e11_(Inh_Attr *pia)
	{
		delete pia->e11_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e11_.ipTrueList;
	}

	Syn_Attr* init_syn_e11_S2()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e11_.spTrueList=new instr_list();
		ps->e11_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e11_S2(Syn_Attr *psa)
	{
		delete psa->e11_.spTrueList;
		delete psa->e11_.spFalseList;
	}



	Inh_Attr* init_inh_e11_1_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e11_.iSection=s_INVALID;
		pi->e11_.ipFalseList=0;
		pi->e11_.ipTrueList=0;

		return pi;
	}
	void del_inh_e11_1_A(Inh_Attr *pia)
	{
		delete pia->e11_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e11_.ipTrueList;
	}
	Temp_Var* init_temp_e11_1_A()
	{
		Temp_Var *pt=new Temp_Var();

		pt->op_line.tLine=0;

		return pt;
	}

	Inh_Attr* init_inh_e11_1_e12()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e12.iSection=s_INVALID;

		return pi;
	}

	Inh_Attr* init_inh_e11_1_S1()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e11_.iSection=s_INVALID;
		pi->e11_.ipFalseList=0;	
		pi->e11_.ipTrueList=0;

		return pi;
	}
	void del_inh_e11_1_S1(Inh_Attr *pia)
	{
		delete pia->e11_.ipFalseList;	
		delete pia->e11_.ipTrueList;
	}
	Temp_Var* init_temp_e11_1_S1()
	{
		Temp_Var *pt=new Temp_Var();

		pt->op_line.tLine=0;

		return pt;
	}
	Syn_Attr* init_syn_e11_1_S1()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e12.spTrueList=new instr_list();
		ps->e12.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e11_1_S1(Syn_Attr *psa)
	{
		delete psa->e12.spTrueList;
		delete psa->e12.spFalseList;
	}

	Inh_Attr* init_inh_e11_1_e11_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e11_.iSection=s_INVALID;
		pi->e11_.ipFalseList=0;
		pi->e11_.ipTrueList=0;

		return pi;
	}
	void del_inh_e11_1_e11_(Inh_Attr *pia)
	{
		delete pia->e11_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e11_.ipTrueList;
	}

	Syn_Attr* init_syn_e11_1_S2()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e11_.spTrueList=new instr_list();
		ps->e11_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e11_1_S2(Syn_Attr *psa)
	{
		delete psa->e11_.spTrueList;
		delete psa->e11_.spFalseList;
	}

	Inh_Attr* init_inh_e11_2_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e11_.iSection=s_INVALID;
		pi->e11_.ipFalseList=0;
		pi->e11_.ipTrueList=0;

		return pi;
	}
	void del_inh_e11_2_A(Inh_Attr *pia)
	{
		delete pia->e11_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e11_.ipTrueList;
	}



	Inh_Attr* init_inh_e12_e13()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e13.iSection=s_INVALID;

		return pi;
	}

	Syn_Attr* init_syn_e12_S1()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e13.spTrueList=new instr_list();
		ps->e13.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e12_S1(Syn_Attr *psa)
	{
		delete psa->e13.spTrueList;
		delete psa->e13.spFalseList;
	}

	Inh_Attr* init_inh_e12_e12_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e12_.iSection=s_INVALID;
		pi->e12_.ipFalseList=0;
		pi->e12_.ipTrueList=0;

		return pi;
	}
	void del_inh_e12_e12_(Inh_Attr *pia)
	{
		delete pia->e12_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e12_.ipTrueList;
	}

	Syn_Attr* init_syn_e12_S2()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e12_.spTrueList=new instr_list();
		ps->e12_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e12_S2(Syn_Attr *psa)
	{
		delete psa->e12_.spTrueList;
		delete psa->e12_.spFalseList;
	}



	Inh_Attr* init_inh_e12_1_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e12_.iSection=s_INVALID;
		pi->e12_.ipFalseList=0;
		pi->e12_.ipTrueList=0;

		return pi;
	}
	void del_inh_e12_1_A(Inh_Attr *pia)
	{
		delete pia->e12_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e12_.ipTrueList;
	}
	Temp_Var* init_temp_e12_1_A()
	{
		Temp_Var *pt=new Temp_Var();

		pt->op_line.tLine=0;

		return pt;
	}

	Inh_Attr* init_inh_e12_1_e13()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e13.iSection=s_INVALID;

		return pi;
	}

	Inh_Attr* init_inh_e12_1_S1()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e12_.iSection=s_INVALID;
		pi->e12_.ipFalseList=0;	
		pi->e12_.ipTrueList=0;

		return pi;
	}
	void del_inh_e12_1_S1(Inh_Attr *pia)
	{
		delete pia->e12_.ipFalseList;	
		delete pia->e12_.ipTrueList;
	}
	Temp_Var* init_temp_e12_1_S1()
	{
		Temp_Var *pt=new Temp_Var();

		pt->op_line.tLine=0;

		return pt;
	}
	Syn_Attr* init_syn_e12_1_S1()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e13.spTrueList=new instr_list();
		ps->e13.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e12_1_S1(Syn_Attr *psa)
	{
		delete psa->e13.spTrueList;
		delete psa->e13.spFalseList;
	}

	Inh_Attr* init_inh_e12_1_e12_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e12_.iSection=s_INVALID;
		pi->e12_.ipFalseList=0;
		pi->e12_.ipTrueList=0;

		return pi;
	}
	void del_inh_e12_1_e12_(Inh_Attr *pia)
	{
		delete pia->e12_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e12_.ipTrueList;
	}

	Syn_Attr* init_syn_e12_1_S2()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e12_.spTrueList=new instr_list();
		ps->e12_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e12_1_S2(Syn_Attr *psa)
	{
		delete psa->e12_.spTrueList;
		delete psa->e12_.spFalseList;
	}

	Inh_Attr* init_inh_e12_2_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e12_.iSection=s_INVALID;
		pi->e12_.ipFalseList=0;
		pi->e12_.ipTrueList=0;

		return pi;
	}
	void del_inh_e12_2_A(Inh_Attr *pia)
	{
		delete pia->e12_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e12_.ipTrueList;
	}



	Temp_Var* init_temp_e13_A()
	{
		Temp_Var *pt=new Temp_Var();

		pt->op_line.tLine=0;

		return pt;
	}
	Inh_Attr* init_inh_e13_e13()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e13.iSection=s_INVALID;

		return pi;
	}
	Inh_Attr* init_inh_e13_S()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e13.iSection=s_INVALID;

		return pi;
	}
	Temp_Var* init_temp_e13_S()
	{
		Temp_Var *pt=new Temp_Var();

		pt->op_line.tLine=0;

		return pt;
	}
	Syn_Attr* init_syn_e13_S()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e13.spTrueList=new instr_list();
		ps->e13.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e13_S(Syn_Attr *psa)
	{
		delete psa->e13.spTrueList;
		delete psa->e13.spFalseList;
	}

	Inh_Attr* init_inh_e13_e14()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e14.iSection=s_INVALID;

		return pi;
	}
	Syn_Attr* init_syn_e13E_S()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e14.spTrueList=new instr_list();
		ps->e14.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e13E_S(Syn_Attr *psa)
	{
		delete psa->e14.spTrueList;
		delete psa->e14.spFalseList;
	}



	Temp_Var* init_temp_e14_A()
	{
		Temp_Var *pt=new Temp_Var();

		pt->e14_const.tLine=0;

		return pt;
	}
	Temp_Var* init_temp_e14E_A()
	{
		Temp_Var *pt=new Temp_Var();

		pt->e14_real.tValue=0;

		return pt;
	}

	Inh_Attr* init_inh_e14FG_loc()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->loc.iSection=s_INVALID;

		return pi;
	}
	Syn_Attr* init_syn_e14FG_S()
	{
		Syn_Attr *ps=new Syn_Attr();

		//初始化为无效地址
		ps->loc.sAddr.section=s_INVALID;
		ps->loc.sAddr.offset=-1;

		ps->loc.sType.type=t_VOID;
		ps->loc.sType.is_array=false;
		ps->loc.sType.length=0;

		return ps;
	}

	Inh_Attr* init_inh_e14H_expr()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->expr.iSection=s_INVALID;

		return pi;
	}
	Syn_Attr* init_syn_e14H_S()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->expr.spTrueList=new instr_list();
		ps->expr.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_e14H_S(Syn_Attr *psa)
	{
		delete psa->expr.spTrueList;
		delete psa->expr.spFalseList;
	}

	Temp_Var* init_temp_e14I_A()
	{
		Temp_Var *pt=new Temp_Var();

		pt->e14_id.tLine=0;
		pt->e14_id.tLexime=new string();

		return pt;
	}
	void del_temp_e14I_A(Temp_Var *ptv)
	{
		delete ptv->e14_id.tLexime;
	}
	Inh_Attr* init_inh_e14I_T3()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->T3.iSection=s_INVALID;
		pi->T3.iLine=0;
		pi->T3.iLexime=new string();

		return pi;
	}
	void del_inh_e14I_T3(Inh_Attr *pia)
	{
		delete pia->T3.iLexime;
	}
	Syn_Attr* init_syn_e14I_S()
	{
		Syn_Attr *ps=new Syn_Attr();

		//初始化为无效地址
		ps->T3.sAddr.section=s_INVALID;
		ps->T3.sAddr.offset=-1;

		ps->T3.sType.type=t_VOID;
		ps->T3.sType.is_array=false;
		ps->T3.sType.length=0;

		return ps;
	}



	Inh_Attr* init_inh_T3_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->T3.iSection=s_INVALID;
		pi->T3.iLine=0;
		pi->T3.iLexime=new string();

		return pi;
	}
	void del_inh_T3_A(Inh_Attr *pia)
	{
		delete pia->T3.iLexime;
	}

	Inh_Attr* init_inh_T3C_args()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->args.iSection=s_INVALID;
		pi->args.iLine=0;
		pi->args.iLexime=new string();

		return pi;
	}
	void del_inh_T3C_args(Inh_Attr *pia)
	{
		delete pia->args.iLexime;
	}
	Syn_Attr* init_syn_T3C_S()
	{
		Syn_Attr *ps=new Syn_Attr();

		//初始化为无效地址
		ps->args.sAddr.section=s_INVALID;
		ps->args.sAddr.offset=-1;

		ps->args.sType.type=t_VOID;
		ps->args.sType.is_array=false;
		ps->args.sType.length=0;

		return ps;
	}

	Inh_Attr* init_inh_T3D_expr()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->expr.iSection=s_INVALID;

		return pi;
	}
	Inh_Attr* init_inh_T3D_S1()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->T3.iSection=s_INVALID;
		pi->T3.iLine=0;
		pi->T3.iLexime=new string();

		return pi;
	}
	void del_inh_T3D_S1(Inh_Attr *pia)
	{
		delete pia->T3.iLexime;
	}
	Syn_Attr* init_syn_T3D_S1()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->expr.spTrueList=new instr_list();
		ps->expr.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T3D_S1(Syn_Attr *psa)
	{
		delete psa->expr.spTrueList;
		delete psa->expr.spFalseList;
	}
	Inh_Attr* init_inh_T3D_T4()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->T4.iSection=s_INVALID;
		pi->T4.iLexime=new string();

		return pi;
	}
	void del_inh_T3D_T4(Inh_Attr *pia)
	{
		delete pia->T4.iLexime;
	}
	Syn_Attr* init_syn_T3D_S2()
	{
		Syn_Attr *ps=new Syn_Attr();

		//初始化为无效地址
		ps->T4.sAddr.section=s_INVALID;
		ps->T4.sAddr.offset=-1;

		ps->T4.sType.type=t_VOID;
		ps->T4.sType.is_array=false;
		ps->T4.sType.length=0;

		return ps;
	}



	Inh_Attr* init_inh_T4_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->T4.iSection=s_INVALID;
		pi->T4.iLexime=new string();

		return pi;
	}
	void del_inh_T4_A(Inh_Attr *pia)
	{
		delete pia->T4.iLexime;
	}



	Temp_Var* init_temp_loc_A()
	{
		Temp_Var *pt=new Temp_Var();

		pt->loc_id.tLine=0;
		pt->loc_id.tLexime=new string();

		return pt;
	}
	void del_temp_loc_A(Temp_Var *ptv)
	{
		delete ptv->loc_id.tLexime;
	}

	Inh_Attr* init_inh_loc_loc_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->loc_.iSection=s_INVALID;
		pi->loc_.iLine=0;
		pi->loc_.iLexime=new string();

		return pi;
	}
	void del_inh_loc_loc_(Inh_Attr *pia)
	{
		delete pia->loc_.iLexime;
	}

	Syn_Attr* init_syn_loc_S()
	{
		Syn_Attr *ps=new Syn_Attr();

		//初始化为无效地址
		ps->loc.sAddr.section=s_INVALID;
		ps->loc.sAddr.offset=-1;

		ps->loc.sType.type=t_VOID;
		ps->loc.sType.is_array=false;
		ps->loc.sType.length=0;

		return ps;
	}



	Inh_Attr* init_inh_loc__A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->loc_.iSection=s_INVALID;
		pi->loc_.iLine=0;
		pi->loc_.iLexime=new string();

		return pi;
	}
	void del_inh_loc__A(Inh_Attr *pia)
	{
		delete pia->loc_.iLexime;
	}

	Inh_Attr* init_inh_loc__expr()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->expr.iSection=s_INVALID;

		return pi;
	}

	Inh_Attr* init_inh_loc__S()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->loc_.iSection=s_INVALID;
		pi->loc_.iLine=0;
		pi->loc_.iLexime=new string();

		return pi;
	}
	void del_inh_loc__S(Inh_Attr *pia)
	{
		delete pia->loc_.iLexime;
	}
	Syn_Attr* init_syn_loc__S()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->expr.spTrueList=new instr_list();
		ps->expr.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_loc__S(Syn_Attr *psa)
	{
		delete psa->expr.spTrueList;
		delete psa->expr.spFalseList;
	}



	Inh_Attr* init_inh_args1_args_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->args_.iSection=s_INVALID;
		pi->args_.iCnt=0;
		pi->args_.ipArgList=0;
		pi->args_.iLine=0;
		pi->args_.iLexime=new string();

		return pi;
	}
	void del_inh_args1_args_(Inh_Attr *pia)
	{
		delete pia->args_.iLexime;
	}

	Inh_Attr* init_inh_args1_A2()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->args.iSection=s_INVALID;
		pi->args.iLine=0;
		pi->args.iLexime=new string();

		return pi;
	}
	void del_inh_args1_A2(Inh_Attr *pia)
	{
		delete pia->args.iLexime;
	}
	Temp_Var* init_temp_args1_A2()
	{
		Temp_Var *pt=new Temp_Var();

		pt->args.ipArgList=new arg_list();

		return pt;
	}
	void del_temp_args1_A2(Temp_Var *ptv)
	{
		delete ptv->args.ipArgList;
	}

	Inh_Attr* init_inh_args2_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->args.iSection=s_INVALID;
		pi->args.iLine=0;
		pi->args.iLexime=new string();

		return pi;
	}
	void del_inh_args2_A(Inh_Attr *pia)
	{
		delete pia->args.iLexime;
	}



	Inh_Attr* init_inh_args__arg()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->arg.iSection=s_INVALID;
		pi->arg.iCnt=0;
		pi->arg.ipArgList=0;
		pi->arg.iLine=0;
		pi->arg.iLexime=new string();

		return pi;
	}
	void del_inh_args__arg(Inh_Attr *pia)
	{
		delete pia->arg.iLexime;
	}

	Inh_Attr* init_inh_args__args__()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->args__.iSection=s_INVALID;
		pi->args__.iCnt=0;
		pi->args__.ipArgList=0;
		pi->args__.iLine=0;
		pi->args__.iLexime=new string();

		return pi;
	}
	void del_inh_args__args__(Inh_Attr *pia)
	{
		delete pia->args__.iLexime;
	}



	Inh_Attr* init_inh_args___args_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->args_.iSection=s_INVALID;
		pi->args_.iCnt=0;
		pi->args_.ipArgList=0;
		pi->args_.iLine=0;
		pi->args_.iLexime=new string();

		return pi;
	}
	void del_inh_args___args_(Inh_Attr *pia)
	{
		delete pia->args_.iLexime;
	}



	Inh_Attr* init_inh_arg_e1()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e1.iSection=s_INVALID;

		return pi;
	}

	Inh_Attr* init_inh_arg_S()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->arg.iSection=s_INVALID;
		pi->arg.iCnt=0;
		pi->arg.ipArgList=0;
		pi->arg.iLine=0;
		pi->arg.iLexime=new string();

		return pi;
	}
	void del_inh_arg_S(Inh_Attr *pia)
	{
		delete pia->arg.iLexime;
	}
	Syn_Attr* init_syn_arg_S()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e1.spTrueList=new instr_list();
		ps->e1.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_arg_S(Syn_Attr *psa)
	{
		delete psa->e1.spTrueList;
		delete psa->e1.spFalseList;
	}



	Inh_Attr* init_inh_T1_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->T1.iSection=s_INVALID;
		pi->T1.iLine=0;
		pi->T1.iLexime=new string();

		return pi;
	}
	void del_inh_T1_A(Inh_Attr *pia)
	{
		delete pia->T1.iLexime;
	}

	Inh_Attr* init_inh_T1C_args()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->args.iSection=s_INVALID;
		pi->args.iLine=0;
		pi->args.iLexime=new string();

		return pi;
	}
	void del_inh_T1C_args(Inh_Attr *pia)
	{
		delete pia->args.iLexime;
	}
	Syn_Attr* init_syn_T1C_S()
	{
		Syn_Attr *ps=new Syn_Attr();

		//初始化为无效地址
		ps->args.sAddr.section=s_INVALID;
		ps->args.sAddr.offset=-1;

		ps->args.sType.type=t_VOID;
		ps->args.sType.is_array=false;
		ps->args.sType.length=0;

		return ps;
	}

	Inh_Attr* init_inh_T1D_expr()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->expr.iSection=s_INVALID;

		return pi;
	}
	Inh_Attr* init_inh_T1D_S1()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->T1.iSection=s_INVALID;
		pi->T1.iLine=0;
		pi->T1.iLexime=new string();

		return pi;
	}
	void del_inh_T1D_S1(Inh_Attr *pia)
	{
		delete pia->T1.iLexime;
	}
	Syn_Attr* init_syn_T1D_S1()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->expr.spTrueList=new instr_list();
		ps->expr.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T1D_S1(Syn_Attr *psa)
	{
		delete psa->expr.spTrueList;
		delete psa->expr.spFalseList;
	}
	Inh_Attr* init_inh_T1D_T2()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->T2.iSection=s_INVALID;
		pi->T2.iLexime=new string();

		return pi;
	}
	void del_inh_T1D_T2(Inh_Attr *pia)
	{
		delete pia->T2.iLexime;
	}
	Syn_Attr* init_syn_T1D_S2()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->T2.spTrueList=new instr_list();
		ps->T2.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T1D_S2(Syn_Attr *psa)
	{
		delete psa->T2.spTrueList;
		delete psa->T2.spFalseList;
	}

	Temp_Var* init_temp_T1E_A()
	{
		Temp_Var *pt=new Temp_Var();

		pt->op_line.tLine=0;

		return pt;
	}
	Inh_Attr* init_inh_T1E_e1()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e1.iSection=s_INVALID;

		return pi;
	}
	Inh_Attr* init_inh_T1E_S()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->T1.iSection=s_INVALID;
		pi->T1.iLine=0;
		pi->T1.iLexime=new string();

		return pi;
	}
	void del_inh_T1E_S(Inh_Attr *pia)
	{
		delete pia->T1.iLexime;
	}
	Temp_Var* init_temp_T1E_S()
	{
		Temp_Var *pt=new Temp_Var();

		pt->op_line.tLine=0;

		return pt;
	}
	Syn_Attr* init_syn_T1E_S()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e1.spTrueList=new instr_list();
		ps->e1.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T1E_S(Syn_Attr *psa)
	{
		delete psa->e1.spTrueList;
		delete psa->e1.spFalseList;
	}

	Inh_Attr* init_inh_T1Z_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->T1.iSection=s_INVALID;
		pi->T1.iLine=0;
		pi->T1.iLexime=new string();

		return pi;
	}
	void del_inh_T1Z_A(Inh_Attr *pia)
	{
		delete pia->T1.iLexime;
	}
	Inh_Attr* init_inh_T1Z_e2_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e2_.iSection=s_INVALID;
		pi->e2_.ipFalseList=0;
		pi->e2_.ipTrueList=0;

		return pi;
	}
	void del_inh_T1Z_e2_(Inh_Attr *pia)
	{
		delete pia->e2_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e2_.ipTrueList;
	}
	Syn_Attr* init_syn_T1Z_e2_()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e2_.spTrueList=new instr_list();
		ps->e2_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T1Z_e2_(Syn_Attr *psa)
	{
		delete psa->e2_.spTrueList;
		delete psa->e2_.spFalseList;
	}
	Inh_Attr* init_inh_T1Z_e3_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e3_.iSection=s_INVALID;
		pi->e3_.ipFalseList=0;
		pi->e3_.ipTrueList=0;

		return pi;
	}
	void del_inh_T1Z_e3_(Inh_Attr *pia)
	{
		delete pia->e3_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e3_.ipTrueList;
	}
	Syn_Attr* init_syn_T1Z_e3_()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e3_.spTrueList=new instr_list();
		ps->e3_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T1Z_e3_(Syn_Attr *psa)
	{
		delete psa->e3_.spTrueList;
		delete psa->e3_.spFalseList;
	}
	Inh_Attr* init_inh_T1Z_e4_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e4_.iSection=s_INVALID;
		pi->e4_.ipFalseList=0;
		pi->e4_.ipTrueList=0;

		return pi;
	}
	void del_inh_T1Z_e4_(Inh_Attr *pia)
	{
		delete pia->e4_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e4_.ipTrueList;
	}
	Syn_Attr* init_syn_T1Z_e4_()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e4_.spTrueList=new instr_list();
		ps->e4_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T1Z_e4_(Syn_Attr *psa)
	{
		delete psa->e4_.spTrueList;
		delete psa->e4_.spFalseList;
	}
	Inh_Attr* init_inh_T1Z_e5_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e5_.iSection=s_INVALID;
		pi->e5_.ipFalseList=0;
		pi->e5_.ipTrueList=0;

		return pi;
	}
	void del_inh_T1Z_e5_(Inh_Attr *pia)
	{
		delete pia->e5_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e5_.ipTrueList;
	}
	Syn_Attr* init_syn_T1Z_e5_()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e5_.spTrueList=new instr_list();
		ps->e5_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T1Z_e5_(Syn_Attr *psa)
	{
		delete psa->e5_.spTrueList;
		delete psa->e5_.spFalseList;
	}
	Inh_Attr* init_inh_T1Z_e6_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e6_.iSection=s_INVALID;
		pi->e6_.ipFalseList=0;
		pi->e6_.ipTrueList=0;

		return pi;
	}
	void del_inh_T1Z_e6_(Inh_Attr *pia)
	{
		delete pia->e6_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e6_.ipTrueList;
	}
	Syn_Attr* init_syn_T1Z_e6_()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e6_.spTrueList=new instr_list();
		ps->e6_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T1Z_e6_(Syn_Attr *psa)
	{
		delete psa->e6_.spTrueList;
		delete psa->e6_.spFalseList;
	}
	Inh_Attr* init_inh_T1Z_e7_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e7_.iSection=s_INVALID;
		pi->e7_.ipFalseList=0;
		pi->e7_.ipTrueList=0;

		return pi;
	}
	void del_inh_T1Z_e7_(Inh_Attr *pia)
	{
		delete pia->e7_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e7_.ipTrueList;
	}
	Syn_Attr* init_syn_T1Z_e7_()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e7_.spTrueList=new instr_list();
		ps->e7_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T1Z_e7_(Syn_Attr *psa)
	{
		delete psa->e7_.spTrueList;
		delete psa->e7_.spFalseList;
	}
	Inh_Attr* init_inh_T1Z_e8_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e8_.iSection=s_INVALID;
		pi->e8_.ipFalseList=0;
		pi->e8_.ipTrueList=0;

		return pi;
	}
	void del_inh_T1Z_e8_(Inh_Attr *pia)
	{
		delete pia->e8_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e8_.ipTrueList;
	}
	Syn_Attr* init_syn_T1Z_e8_()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e8_.spTrueList=new instr_list();
		ps->e8_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T1Z_e8_(Syn_Attr *psa)
	{
		delete psa->e8_.spTrueList;
		delete psa->e8_.spFalseList;
	}
	Inh_Attr* init_inh_T1Z_e9_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e9_.iSection=s_INVALID;
		pi->e9_.ipFalseList=0;
		pi->e9_.ipTrueList=0;

		return pi;
	}
	void del_inh_T1Z_e9_(Inh_Attr *pia)
	{
		delete pia->e9_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e9_.ipTrueList;
	}
	Syn_Attr* init_syn_T1Z_e9_()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e9_.spTrueList=new instr_list();
		ps->e9_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T1Z_e9_(Syn_Attr *psa)
	{
		delete psa->e9_.spTrueList;
		delete psa->e9_.spFalseList;
	}
	Inh_Attr* init_inh_T1Z_e10_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e10_.iSection=s_INVALID;
		pi->e10_.ipFalseList=0;
		pi->e10_.ipTrueList=0;

		return pi;
	}
	void del_inh_T1Z_e10_(Inh_Attr *pia)
	{
		delete pia->e10_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e10_.ipTrueList;
	}
	Syn_Attr* init_syn_T1Z_e10_()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e10_.spTrueList=new instr_list();
		ps->e10_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T1Z_e10_(Syn_Attr *psa)
	{
		delete psa->e10_.spTrueList;
		delete psa->e10_.spFalseList;
	}
	Inh_Attr* init_inh_T1Z_e11_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e11_.iSection=s_INVALID;
		pi->e11_.ipFalseList=0;
		pi->e11_.ipTrueList=0;

		return pi;
	}
	void del_inh_T1Z_e11_(Inh_Attr *pia)
	{
		delete pia->e11_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e11_.ipTrueList;
	}
	Syn_Attr* init_syn_T1Z_e11_()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e11_.spTrueList=new instr_list();
		ps->e11_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T1Z_e11_(Syn_Attr *psa)
	{
		delete psa->e11_.spTrueList;
		delete psa->e11_.spFalseList;
	}
	Inh_Attr* init_inh_T1Z_e12_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e12_.iSection=s_INVALID;
		pi->e12_.ipFalseList=0;
		pi->e12_.ipTrueList=0;

		return pi;
	}
	void del_inh_T1Z_e12_(Inh_Attr *pia)
	{
		delete pia->e12_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e12_.ipTrueList;
	}
	Syn_Attr* init_syn_T1Z_e12_()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e12_.spTrueList=new instr_list();
		ps->e12_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T1Z_e12_(Syn_Attr *psa)
	{
		delete psa->e12_.spTrueList;
		delete psa->e12_.spFalseList;
	}



	Inh_Attr* init_inh_T2_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->T2.iSection=s_INVALID;
		pi->T2.iLexime=new string();

		return pi;
	}
	void del_inh_T2_A(Inh_Attr *pia)
	{
		delete pia->T2.iLexime;
	}

	Temp_Var* init_temp_T2C_A()
	{
		Temp_Var *pt=new Temp_Var();

		pt->op_line.tLine=0;

		return pt;
	}
	Inh_Attr* init_inh_T2C_e1()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e1.iSection=s_INVALID;

		return pi;
	}
	Inh_Attr* init_inh_T2C_S()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->T2.iSection=s_INVALID;
		pi->T2.iLexime=new string();

		return pi;
	}
	void del_inh_T2C_S(Inh_Attr *pia)
	{
		delete pia->T2.iLexime;
	}
	Temp_Var* init_temp_T2C_S()
	{
		Temp_Var *pt=new Temp_Var();

		pt->op_line.tLine=0;

		return pt;
	}
	Syn_Attr* init_syn_T2C_S()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e1.spTrueList=new instr_list();
		ps->e1.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T2C_S(Syn_Attr *psa)
	{
		delete psa->e1.spTrueList;
		delete psa->e1.spFalseList;
	}

	Inh_Attr* init_inh_T2X_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->T2.iSection=s_INVALID;
		pi->T2.iLexime=new string();

		return pi;
	}
	void del_inh_T2X_A(Inh_Attr *pia)
	{
		delete pia->T2.iLexime;
	}
	Inh_Attr* init_inh_T2X_e2_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e2_.iSection=s_INVALID;
		pi->e2_.ipFalseList=0;
		pi->e2_.ipTrueList=0;

		return pi;
	}
	void del_inh_T2X_e2_(Inh_Attr *pia)
	{
		delete pia->e2_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e2_.ipTrueList;
	}
	Syn_Attr* init_syn_T2X_e2_()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e2_.spTrueList=new instr_list();
		ps->e2_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T2X_e2_(Syn_Attr *psa)
	{
		delete psa->e2_.spTrueList;
		delete psa->e2_.spFalseList;
	}
	Inh_Attr* init_inh_T2X_e3_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e3_.iSection=s_INVALID;
		pi->e3_.ipFalseList=0;
		pi->e3_.ipTrueList=0;

		return pi;
	}
	void del_inh_T2X_e3_(Inh_Attr *pia)
	{
		delete pia->e3_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e3_.ipTrueList;
	}
	Syn_Attr* init_syn_T2X_e3_()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e3_.spTrueList=new instr_list();
		ps->e3_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T2X_e3_(Syn_Attr *psa)
	{
		delete psa->e3_.spTrueList;
		delete psa->e3_.spFalseList;
	}
	Inh_Attr* init_inh_T2X_e4_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e4_.iSection=s_INVALID;
		pi->e4_.ipFalseList=0;
		pi->e4_.ipTrueList=0;

		return pi;
	}
	void del_inh_T2X_e4_(Inh_Attr *pia)
	{
		delete pia->e4_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e4_.ipTrueList;
	}
	Syn_Attr* init_syn_T2X_e4_()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e4_.spTrueList=new instr_list();
		ps->e4_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T2X_e4_(Syn_Attr *psa)
	{
		delete psa->e4_.spTrueList;
		delete psa->e4_.spFalseList;
	}
	Inh_Attr* init_inh_T2X_e5_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e5_.iSection=s_INVALID;
		pi->e5_.ipFalseList=0;
		pi->e5_.ipTrueList=0;

		return pi;
	}
	void del_inh_T2X_e5_(Inh_Attr *pia)
	{
		delete pia->e5_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e5_.ipTrueList;
	}
	Syn_Attr* init_syn_T2X_e5_()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e5_.spTrueList=new instr_list();
		ps->e5_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T2X_e5_(Syn_Attr *psa)
	{
		delete psa->e5_.spTrueList;
		delete psa->e5_.spFalseList;
	}
	Inh_Attr* init_inh_T2X_e6_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e6_.iSection=s_INVALID;
		pi->e6_.ipFalseList=0;
		pi->e6_.ipTrueList=0;

		return pi;
	}
	void del_inh_T2X_e6_(Inh_Attr *pia)
	{
		delete pia->e6_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e6_.ipTrueList;
	}
	Syn_Attr* init_syn_T2X_e6_()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e6_.spTrueList=new instr_list();
		ps->e6_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T2X_e6_(Syn_Attr *psa)
	{
		delete psa->e6_.spTrueList;
		delete psa->e6_.spFalseList;
	}
	Inh_Attr* init_inh_T2X_e7_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e7_.iSection=s_INVALID;
		pi->e7_.ipFalseList=0;
		pi->e7_.ipTrueList=0;

		return pi;
	}
	void del_inh_T2X_e7_(Inh_Attr *pia)
	{
		delete pia->e7_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e7_.ipTrueList;
	}
	Syn_Attr* init_syn_T2X_e7_()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e7_.spTrueList=new instr_list();
		ps->e7_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T2X_e7_(Syn_Attr *psa)
	{
		delete psa->e7_.spTrueList;
		delete psa->e7_.spFalseList;
	}
	Inh_Attr* init_inh_T2X_e8_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e8_.iSection=s_INVALID;
		pi->e8_.ipFalseList=0;
		pi->e8_.ipTrueList=0;

		return pi;
	}
	void del_inh_T2X_e8_(Inh_Attr *pia)
	{
		delete pia->e8_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e8_.ipTrueList;
	}
	Syn_Attr* init_syn_T2X_e8_()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e8_.spTrueList=new instr_list();
		ps->e8_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T2X_e8_(Syn_Attr *psa)
	{
		delete psa->e8_.spTrueList;
		delete psa->e8_.spFalseList;
	}
	Inh_Attr* init_inh_T2X_e9_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e9_.iSection=s_INVALID;
		pi->e9_.ipFalseList=0;
		pi->e9_.ipTrueList=0;

		return pi;
	}
	void del_inh_T2X_e9_(Inh_Attr *pia)
	{
		delete pia->e9_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e9_.ipTrueList;
	}
	Syn_Attr* init_syn_T2X_e9_()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e9_.spTrueList=new instr_list();
		ps->e9_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T2X_e9_(Syn_Attr *psa)
	{
		delete psa->e9_.spTrueList;
		delete psa->e9_.spFalseList;
	}
	Inh_Attr* init_inh_T2X_e10_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e10_.iSection=s_INVALID;
		pi->e10_.ipFalseList=0;
		pi->e10_.ipTrueList=0;

		return pi;
	}
	void del_inh_T2X_e10_(Inh_Attr *pia)
	{
		delete pia->e10_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e10_.ipTrueList;
	}
	Syn_Attr* init_syn_T2X_e10_()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e10_.spTrueList=new instr_list();
		ps->e10_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T2X_e10_(Syn_Attr *psa)
	{
		delete psa->e10_.spTrueList;
		delete psa->e10_.spFalseList;
	}
	Inh_Attr* init_inh_T2X_e11_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e11_.iSection=s_INVALID;
		pi->e11_.ipFalseList=0;
		pi->e11_.ipTrueList=0;

		return pi;
	}
	void del_inh_T2X_e11_(Inh_Attr *pia)
	{
		delete pia->e11_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e11_.ipTrueList;
	}
	Syn_Attr* init_syn_T2X_e11_()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e11_.spTrueList=new instr_list();
		ps->e11_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T2X_e11_(Syn_Attr *psa)
	{
		delete psa->e11_.spTrueList;
		delete psa->e11_.spFalseList;
	}
	Inh_Attr* init_inh_T2X_e12_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e12_.iSection=s_INVALID;
		pi->e12_.ipFalseList=0;
		pi->e12_.ipTrueList=0;

		return pi;
	}
	void del_inh_T2X_e12_(Inh_Attr *pia)
	{
		delete pia->e12_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e12_.ipTrueList;
	}
	Syn_Attr* init_syn_T2X_e12_()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e12_.spTrueList=new instr_list();
		ps->e12_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T2X_e12_(Syn_Attr *psa)
	{
		delete psa->e12_.spTrueList;
		delete psa->e12_.spFalseList;
	}


	Inh_Attr* init_inh_T5()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->T5.iSection=s_INVALID;

		return pi;
	}
	Syn_Attr* init_syn_T5_S()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->T5.spTrueList=new instr_list();
		ps->T5.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T5_S(Syn_Attr *psa)
	{
		delete psa->T5.spTrueList;
		delete psa->T5.spFalseList;
	}

	Inh_Attr* init_inh_T5_A()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->T5.iSection=s_INVALID;

		return pi;
	}
	Inh_Attr* init_inh_T5_e2_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e2_.iSection=s_INVALID;
		pi->e2_.ipFalseList=0;
		pi->e2_.ipTrueList=0;

		return pi;
	}
	void del_inh_T5_e2_(Inh_Attr *pia)
	{
		delete pia->e2_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e2_.ipTrueList;
	}
	Syn_Attr* init_syn_T5_e2_()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e2_.spTrueList=new instr_list();
		ps->e2_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T5_e2_(Syn_Attr *psa)
	{
		delete psa->e2_.spTrueList;
		delete psa->e2_.spFalseList;
	}
	Inh_Attr* init_inh_T5_e3_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e3_.iSection=s_INVALID;
		pi->e3_.ipFalseList=0;
		pi->e3_.ipTrueList=0;

		return pi;
	}
	void del_inh_T5_e3_(Inh_Attr *pia)
	{
		delete pia->e3_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e3_.ipTrueList;
	}
	Syn_Attr* init_syn_T5_e3_()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e3_.spTrueList=new instr_list();
		ps->e3_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T5_e3_(Syn_Attr *psa)
	{
		delete psa->e3_.spTrueList;
		delete psa->e3_.spFalseList;
	}
	Inh_Attr* init_inh_T5_e4_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e4_.iSection=s_INVALID;
		pi->e4_.ipFalseList=0;
		pi->e4_.ipTrueList=0;

		return pi;
	}
	void del_inh_T5_e4_(Inh_Attr *pia)
	{
		delete pia->e4_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e4_.ipTrueList;
	}
	Syn_Attr* init_syn_T5_e4_()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e4_.spTrueList=new instr_list();
		ps->e4_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T5_e4_(Syn_Attr *psa)
	{
		delete psa->e4_.spTrueList;
		delete psa->e4_.spFalseList;
	}
	Inh_Attr* init_inh_T5_e5_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e5_.iSection=s_INVALID;
		pi->e5_.ipFalseList=0;
		pi->e5_.ipTrueList=0;

		return pi;
	}
	void del_inh_T5_e5_(Inh_Attr *pia)
	{
		delete pia->e5_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e5_.ipTrueList;
	}
	Syn_Attr* init_syn_T5_e5_()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e5_.spTrueList=new instr_list();
		ps->e5_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T5_e5_(Syn_Attr *psa)
	{
		delete psa->e5_.spTrueList;
		delete psa->e5_.spFalseList;
	}
	Inh_Attr* init_inh_T5_e6_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e6_.iSection=s_INVALID;
		pi->e6_.ipFalseList=0;
		pi->e6_.ipTrueList=0;

		return pi;
	}
	void del_inh_T5_e6_(Inh_Attr *pia)
	{
		delete pia->e6_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e6_.ipTrueList;
	}
	Syn_Attr* init_syn_T5_e6_()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e6_.spTrueList=new instr_list();
		ps->e6_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T5_e6_(Syn_Attr *psa)
	{
		delete psa->e6_.spTrueList;
		delete psa->e6_.spFalseList;
	}
	Inh_Attr* init_inh_T5_e7_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e7_.iSection=s_INVALID;
		pi->e7_.ipFalseList=0;
		pi->e7_.ipTrueList=0;

		return pi;
	}
	void del_inh_T5_e7_(Inh_Attr *pia)
	{
		delete pia->e7_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e7_.ipTrueList;
	}
	Syn_Attr* init_syn_T5_e7_()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e7_.spTrueList=new instr_list();
		ps->e7_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T5_e7_(Syn_Attr *psa)
	{
		delete psa->e7_.spTrueList;
		delete psa->e7_.spFalseList;
	}
	Inh_Attr* init_inh_T5_e8_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e8_.iSection=s_INVALID;
		pi->e8_.ipFalseList=0;
		pi->e8_.ipTrueList=0;

		return pi;
	}
	void del_inh_T5_e8_(Inh_Attr *pia)
	{
		delete pia->e8_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e8_.ipTrueList;
	}
	Syn_Attr* init_syn_T5_e8_()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e8_.spTrueList=new instr_list();
		ps->e8_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T5_e8_(Syn_Attr *psa)
	{
		delete psa->e8_.spTrueList;
		delete psa->e8_.spFalseList;
	}
	Inh_Attr* init_inh_T5_e9_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e9_.iSection=s_INVALID;
		pi->e9_.ipFalseList=0;
		pi->e9_.ipTrueList=0;

		return pi;
	}
	void del_inh_T5_e9_(Inh_Attr *pia)
	{
		delete pia->e9_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e9_.ipTrueList;
	}
	Syn_Attr* init_syn_T5_e9_()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e9_.spTrueList=new instr_list();
		ps->e9_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T5_e9_(Syn_Attr *psa)
	{
		delete psa->e9_.spTrueList;
		delete psa->e9_.spFalseList;
	}
	Inh_Attr* init_inh_T5_e10_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e10_.iSection=s_INVALID;
		pi->e10_.ipFalseList=0;
		pi->e10_.ipTrueList=0;

		return pi;
	}
	void del_inh_T5_e10_(Inh_Attr *pia)
	{
		delete pia->e10_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e10_.ipTrueList;
	}
	Syn_Attr* init_syn_T5_e10_()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e10_.spTrueList=new instr_list();
		ps->e10_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T5_e10_(Syn_Attr *psa)
	{
		delete psa->e10_.spTrueList;
		delete psa->e10_.spFalseList;
	}
	Inh_Attr* init_inh_T5_e11_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e11_.iSection=s_INVALID;
		pi->e11_.ipFalseList=0;
		pi->e11_.ipTrueList=0;

		return pi;
	}
	void del_inh_T5_e11_(Inh_Attr *pia)
	{
		delete pia->e11_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e11_.ipTrueList;
	}
	Syn_Attr* init_syn_T5_e11_()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e11_.spTrueList=new instr_list();
		ps->e11_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T5_e11_(Syn_Attr *psa)
	{
		delete psa->e11_.spTrueList;
		delete psa->e11_.spFalseList;
	}
	Inh_Attr* init_inh_T5_e12_()
	{
		Inh_Attr *pi=new Inh_Attr();

		pi->e12_.iSection=s_INVALID;
		pi->e12_.ipFalseList=0;
		pi->e12_.ipTrueList=0;

		return pi;
	}
	void del_inh_T5_e12_(Inh_Attr *pia)
	{
		delete pia->e12_.ipFalseList;	//	避免指针传递过程中的内存空间泄漏,同E的inextlist和ifalselist
		delete pia->e12_.ipTrueList;
	}
	Syn_Attr* init_syn_T5_e12_()
	{
		Syn_Attr *ps=new Syn_Attr();

		ps->e12_.spTrueList=new instr_list();
		ps->e12_.spFalseList=new instr_list();

		return ps;
	}
	void del_syn_T5_e12_(Syn_Attr *psa)
	{
		delete psa->e12_.spTrueList;
		delete psa->e12_.spFalseList;
	}
}