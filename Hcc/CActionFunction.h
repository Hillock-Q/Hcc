#pragma once
#include "CEnv.h"
#include "CByteCode.h"
#include "CHillock.h"
#include "CDataType.h"
#include "COperator.h"
#include "CNumber.h"
#include "CReal.h"
#include "CCharacter.h"
using std::make_pair;

namespace Compiler
{
	typedef vector<StackRecord*> PPS;	//预测分析栈
	typedef multimap<size_t,string> ErrorRecord;
	
	static bool Value2ControlFlow(Env &context,Syn_Attr *ps,unsigned char sec=s_LOCAL)
	{
		//如果当前是value
		if(ps->expr.sValFlag)
		{
			//不可计算类型,直接返回失败
			if(!Computable(ps->expr.sType))
				return false;

			//以下代码生成测试value值及根据测试条件进行跳转的指令
			if(ps->expr.spTrueList)
				ps->expr.spTrueList->push_back(context.getNextInstr(sec));		//测试为真
			context.Gen(op_if_true_goto,ps->expr.sAddr,sec);	//跳转目标地址待回填
			if(ps->expr.spFalseList)
				ps->expr.spFalseList->push_back(context.getNextInstr(sec));		//测试为假
			context.Gen(op_goto,sec);	//跳转目标地址待回填

			//更新值标志
			ps->expr.sValFlag=false;
		}

		return true;
	}

	static bool Value2ControlFlow(Env &context,Inh_Attr *pi,unsigned char sec=s_LOCAL)
	{
		//如果当前是value
		if(pi->expr_.iValFlag)
		{
			//不可计算类型,直接返回失败
			if(!Computable(pi->expr_.iType))
				return false;

			//以下代码生成测试value值及根据测试条件进行跳转的指令
			if(!pi->expr_.ipTrueList)
				pi->expr_.ipTrueList=new instr_list();
			pi->expr_.ipTrueList->push_back(context.getNextInstr(sec));		//测试为真
			context.Gen(op_if_true_goto,pi->expr_.iAddr,sec);	//跳转目标地址待回填

			if(!pi->expr_.ipFalseList)
				pi->expr_.ipFalseList=new instr_list();
			pi->expr_.ipFalseList->push_back(context.getNextInstr(sec));		//测试为假
			context.Gen(op_goto,sec);	//跳转目标地址待回填

			//更新值标志
			pi->expr_.iValFlag=false;
		}

		return true;
	}

	static void ControlFlow2Value(Env &context,Syn_Attr *ps,unsigned char sec=s_LOCAL)
	{
		//如果当前是control flow
		if(!ps->expr.sValFlag)
		{
			//更新值标志
			ps->expr.sValFlag=true;

			//数据类型指定为bool型
			ps->expr.sType.type=t_BOOL;
			ps->expr.sType.is_array=false;

			//生成临时变量地址
			ps->expr.sAddr=context.Temp(ps->expr.sType,sec);

			//以个代码在control flow的真假出口将临时变量的值设置为true或false
			context.BackPatch(ps->expr.spTrueList,context.getNextInstr(sec),sec);	//回填真出口
			context.Gen(op_assign,ps->expr.sAddr,context.getAddress(true),sec);	//临时变量设置为true值
			instr_list *ptruelist=new instr_list();
			ptruelist->push_back(context.getNextInstr(sec));	//保存待回填跳转指令下标
			context.Gen(op_goto,sec);	//跳转到假出口之后,目标地址待回填
			context.BackPatch(ps->expr.spFalseList,context.getNextInstr(sec),sec);	//回填假出口
			context.Gen(op_assign,ps->expr.sAddr,context.getAddress(false),sec);	//临时变量设置为false值
			context.BackPatch(ptruelist,context.getNextInstr(sec),sec);		//回填无条件跳转指令
			context.Gen(op_no_op,sec);		//产生一条no-op指令,一般用作回填目标
			delete ptruelist;
		}
	}

	static void ControlFlow2Value(Env &context,Inh_Attr *pi,unsigned char sec=s_LOCAL)
	{
		//如果当前是control flow
		if(!pi->expr_.iValFlag)
		{
			//更新值标志
			pi->expr_.iValFlag=true;

			//数据类型指定为bool型
			pi->expr_.iType.type=t_BOOL;
			pi->expr_.iType.is_array=false;

			//生成临时变量地址
			pi->expr_.iAddr=context.Temp(pi->expr_.iType,sec);

			//以个代码在control flow的真假出口将临时变量的值设置为true或false
			context.BackPatch(pi->expr_.ipTrueList,context.getNextInstr(sec),sec);	//回填真出口
			context.Gen(op_assign,pi->expr_.iAddr,context.getAddress(true),sec);	//临时变量设置为true值
			instr_list *ptruelist=new instr_list();
			ptruelist->push_back(context.getNextInstr(sec));	//保存待回填跳转指令下标
			context.Gen(op_goto,sec);	//跳转到假出口之后,目标地址待回填
			context.BackPatch(pi->expr_.ipFalseList,context.getNextInstr(sec),sec);	//回填假出口
			context.Gen(op_assign,pi->expr_.iAddr,context.getAddress(false),sec);	//临时变量设置为false值
			context.BackPatch(ptruelist,context.getNextInstr(sec),sec);		//回填无条件跳转指令
			context.Gen(op_no_op,sec);		//产生一条no-op指令,一般用作回填目标
			delete ptruelist;
		}
	}

	static void act_program_A1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//define main
		context.defineFun(
			"main",
			t_VOID,
			vector<VarInfo>(),
			pps.back()->getTempVar()->main_line.tLine
			);

		//清空上下文
		context.Clear();

		//重置上下文函数名
		context.ReName("main");
	}
	static void act_program_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//回填stmts.nextlist
		context.BackPatch(
			pps.back()->getSynAttr()->stmts.spNextList,
			context.getNextInstr()
			);

		//生成默认的返回指令
		context.Gen(op_return);
	}
	static void act_program_A2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//获取main函数id
		size_t id=context.getFunInfo("main")->id;

		//生成main函数的字节码
		byte_code.BuildLocalCode(
			id,
			context.getLocalTable(),
			context.getFunCode()
			);

		//在初始化代码中生成调用main函数的指令
		context.Gen(
			op_call,
			context.getAddress(int(id)),
			context.getAddress(0),
			s_GLOBAL
			);

		//main函数加入调用集合
		byte_code.getCallSet().insert(id);

		//生成初始化代码的字节码
		byte_code.BuildInitCode(Env::getInitCode());

		//生成常量表的字节码
		byte_code.BuildConstTableCode(Env::getConstTable());

		//生成全局符号表的字节码
		byte_code.BuildGlobalTableCode(Env::getGlobalTable());

		//清空上下文
		context.Clear();

		//置空上下文函数名
		context.ReName("");
	}



	static void act_option1_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Temp_Var *pt=pps.back()->getTempVar();

		//id作为全局名字必须唯一
		string name(*(pt->option_id.tLexime));

		//名字已经声明为变量
		if(context.isVar(name))
		{
			//首次定义位置
			size_t def=context.getAllocInfo(name)->line;

			//重定义位置
			size_t redef=pt->option_id.tLine;

			//错误报告
			string str="重复声明:名字\""+name+"\"在第"+toString(int(def))+"行已声明为变量或数组。";

			//追加到记录
			err_record.insert(make_pair(redef,str));
		}
		//名字已经声明为函数
		else if(context.isFun(name))
		{
			//首次定义位置
			size_t def=context.getFunInfo(name)->line;

			//重定义位置
			size_t redef=pt->option_id.tLine;

			//错误报告
			string str;
			
			if(def)
				str="重复声明:名字\""+name+"\"在第"+toString(int(def))+"行已声明为函数。";
			else
				str="名字冲突:"+name+"已经作为库函数名使用。";

			//追加到记录
			err_record.insert(make_pair(redef,str));
		}

		//向F传递void属性
		pps[pps.size()-2]->getInhAttr()->F.iType.type=t_VOID;

		//向F传递id属性
		pps[pps.size()-2]->getInhAttr()->F.iLine=pt->option_id.tLine;
		pps[pps.size()-2]->getInhAttr()->F.iLexime->swap(*(pt->option_id.tLexime));
	}

	static void act_option2_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//向option'传递B属性
		pps[pps.size()-4]->getInhAttr()->option_.iType=pps.back()->getSynAttr()->B.sType;
	}
	static void act_option2_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Temp_Var *pt=pps.back()->getTempVar();

		//id作为全局名字必须唯一
		string name(*(pt->option_id.tLexime));

		//名字已经声明为变量
		if(context.isVar(name))
		{
			//首次定义位置
			size_t def=context.getAllocInfo(name)->line;

			//重定义位置
			size_t redef=pt->option_id.tLine;

			//错误报告
			string str="重复声明:名字\""+name+"\"在第"+toString(int(def))+"行已声明为变量或数组。";

			//追加到记录
			err_record.insert(make_pair(redef,str));
		}
		//名字已经声明为函数
		else if(context.isFun(name))
		{
			//首次定义位置
			size_t def=context.getFunInfo(name)->line;

			//重定义位置
			size_t redef=pt->option_id.tLine;

			//错误报告
			string str;

			if(def)
				str="重复声明:名字\""+name+"\"在第"+toString(int(def))+"行已声明为函数。";
			else
				str="名字冲突:"+name+"已经作为库函数名使用。";

			//追加到记录
			err_record.insert(make_pair(redef,str));
		}

		//向option'传递id属性
		pps[pps.size()-2]->getInhAttr()->option_.iLine=pt->option_id.tLine;
		pps[pps.size()-2]->getInhAttr()->option_.iLexime->swap(*(pt->option_id.tLexime));	
	}



	static void act_decl_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//向decl'传递B属性
		pps[pps.size()-4]->getInhAttr()->decl_.iType=pps.back()->getSynAttr()->B.sType;
	}
	static void act_decl_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Temp_Var *pt=pps.back()->getTempVar();

		//id作为全局名字必须唯一
		string name(*(pt->decl_id.tLexime));

		//名字已经声明为变量
		if(context.isVar(name))
		{
			//首次定义位置
			size_t def=context.getAllocInfo(name)->line;

			//重定义位置
			size_t redef=pt->decl_id.tLine;

			//错误报告
			string str="重复声明:名字\""+name+"\"在第"+toString(int(def))+"行已声明为变量或数组。";

			//追加到记录
			err_record.insert(make_pair(redef,str));
		}
		//名字已经声明为函数
		else if(context.isFun(name))
		{
			//首次定义位置
			size_t def=context.getFunInfo(name)->line;

			//重定义位置
			size_t redef=pt->decl_id.tLine;

			//错误报告
			string str;

			if(def)
				str="重复声明:名字\""+name+"\"在第"+toString(int(def))+"行已声明为函数。";
			else
				str="名字冲突:"+name+"已经作为库函数名使用。";

			//追加到记录
			err_record.insert(make_pair(redef,str));
		}

		//向decl'传递id属性
		pps[pps.size()-2]->getInhAttr()->decl_.iLine=pt->decl_id.tLine;
		pps[pps.size()-2]->getInhAttr()->decl_.iLexime->swap(*(pt->decl_id.tLexime));	
	}

	static void act_A_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//检查数组大小应该大于0
		if(!(0<ps->size.tValue))
		{
			string str="数组"+*(pi->A.iLexime)+"大小应该大于0。";

			//生成错误报告
			err_record.insert(make_pair(pi->A.iLine,str));
		}
		//else
		{
			//生成数组类型
			pi->A.iType.is_array=true;
			pi->A.iType.length=ps->size.tValue;

			//定义数组
			context.defineVar(*(pi->A.iLexime),pi->A.iType,pi->A.iLine,pi->A.iSection);
		}
	}

	static void act_L__S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Syn_Attr *ps=pps.back()->getSynAttr();
		string name=*(pi->L_.iLexime);

		//获取数组声明信息
		AllocInfo const* pa=context.getAllocInfo(name);

		//如果初始化值不超过数组大小
		if(pi->L_.iIndex < pa->var_info.length)
		{
			//转换成value
			ControlFlow2Value(context,ps,pi->L_.iSection);

			//可计算类型
			if(Computable(ps->e1.sType))
			{
				//生成向数组元素赋值的指令
				context.Gen(op_write_array,context.getAddress(name),context.getAddress(int(pi->L_.iIndex)),ps->e1.sAddr,pi->L_.iSection);
			}
			else
			{
				size_t def=context.getAllocInfo(name)->line;

				//错误报告
				string str="数组\""+name+"\"的第"+toString(int(pi->L_.iIndex+1))+"个初始化值类型错误。";

				//追加到记录
				err_record.insert(make_pair(def,str));
			}
		}
		else
		{
			size_t def=context.getAllocInfo(name)->line;

			//错误报告
			string str="数组\""+name+"\"的初始化值过多。";

			//追加到记录
			err_record.insert(make_pair(def,str));
		}
	}

	static void act_V_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//生成变量类型
		pi->V.iType.is_array=false;

		//定义变量
		context.defineVar(*(pi->V.iLexime),pi->V.iType,pi->V.iLine,pi->V.iSection);		
	}

	static void act_V_1_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Temp_Var *pt=pps.back()->getTempVar();

		//id作为全局名字必须唯一
		string name(*(pt->V__id.tLexime));

		//名字已经声明为变量
		if(context.isVar(name))
		{
			//首次定义位置
			size_t def=context.getAllocInfo(name)->line;

			//重定义位置
			size_t redef=pt->V__id.tLine;

			//错误报告
			string str="重复声明:名字\""+name+"\"在第"+toString(int(def))+"行已声明为变量或数组。";

			//追加到记录
			err_record.insert(make_pair(redef,str));
		}
		//名字已经声明为函数
		else if(context.isFun(name))
		{
			//首次定义位置
			size_t def=context.getFunInfo(name)->line;

			//重定义位置
			size_t redef=pt->V__id.tLine;

			//错误报告
			string str;

			if(def)
				str="重复声明:名字\""+name+"\"在第"+toString(int(def))+"行已声明为函数。";
			else
				str="名字冲突:"+name+"已经作为库函数名使用。";

			//追加到记录
			err_record.insert(make_pair(redef,str));
		}

		Inh_Attr *pi=pps.back()->getInhAttr();

		//生成变量类型
		pi->V_.iType.is_array=false;

		//定义变量
		context.defineVar(*(pt->V__id.tLexime),pi->V_.iType,pt->V__id.tLine,pi->V_.iSection);			
		
		//id属性传递给opt2
		pps[pps.size()-2]->getInhAttr()->opt2.iLexime->swap(*(pt->V__id.tLexime));
	}

	static void act_opt2A_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Syn_Attr *ps=pps.back()->getSynAttr();
		string name=*(pi->opt2.iLexime);

		//转换成value
		ControlFlow2Value(context,ps,pi->opt2.iSection);

		//可计算类型
		if(Computable(ps->e1.sType))
		{
			//生成向变量赋值的指令
			context.Gen(op_assign,context.getAddress(name),ps->e1.sAddr,pi->opt2.iSection);
		}
		else
		{
			size_t def=context.getAllocInfo(name)->line;

			//错误报告
			string str="变量\""+name+"\"的初始化值类型错误。";

			//追加到记录
			err_record.insert(make_pair(def,str));
		}
	}

	static void act_F_A1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//define function
		context.defineFun(
			*(pi->F.iLexime),
			pi->F.iType.type,
			vector<VarInfo>(),	//参数列表初始化为空
			pi->F.iLine
			);

		//清空上下文
		context.Clear();

		//重置上下文函数名
		context.ReName(*(pi->F.iLexime));
	}
	static void act_F_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//回填stmts.nextlist
		context.BackPatch(
			ps->stmts.spNextList,
			context.getNextInstr()
			);

		//获取上下文函数信息
		FunInfo const& fun_info=*context.getFunInfo(context.getName());

		//函数无返回类型
		if(t_VOID==fun_info.ret_type)
		{
			//生成默认的返回指令
			context.Gen(op_return);
		}
		//函数有返回类型
		else
		{
			//检查函数是否生成返回指令/最后一条指令是否返回指令
			if(0==ps->stmts.sRetCnt || op_return_value!=context.getLastInstr())
			{
				//错误报告
				string str="函数\""+context.getName()+"\"必须返回一个值。";

				//追加到记录
				err_record.insert(make_pair(fun_info.line,str));
			}
			//否则
			else
			{
				//生成no-op指令,避免回填目标不存在
				context.Gen(op_no_op,s_LOCAL);
			}
		}
	}
	static void act_F_A2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//生成函数的字节码
		byte_code.BuildLocalCode(
			context.getFunInfo(context.getName())->id,
			context.getLocalTable(),
			context.getFunCode()
			);

		//清空上下文
		context.Clear();

		//置空上下文函数名
		context.ReName("");
	}

	static void act_param_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//向tail传递B属性
		pps[pps.size()-4]->getInhAttr()->tail.iType=pps.back()->getSynAttr()->B.sType;
	}
	static void act_param_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Temp_Var *pt=pps.back()->getTempVar();

		//id作为参数名字必须唯一
		string name(*(pt->param_id.tLexime));

		//名字已经声明为变量
		if(context.isVar(name))
		{
			//首次定义位置
			size_t def=context.getAllocInfo(name)->line;

			//重定义位置
			size_t redef=pt->param_id.tLine;

			//错误报告
			string str="重复声明:名字\""+name+"\"在第"+toString(int(def))+"行已声明为变量或数组。";

			//追加到记录
			err_record.insert(make_pair(redef,str));
		}
		//名字已经声明为函数
		else if(context.isFun(name))
		{
			//首次定义位置
			size_t def=context.getFunInfo(name)->line;

			//重定义位置
			size_t redef=pt->param_id.tLine;

			//错误报告
			string str;

			if(def)
				str="重复声明:名字\""+name+"\"在第"+toString(int(def))+"行已声明为函数。";
			else
				str="名字冲突:"+name+"已经作为库函数名使用。";

			//追加到记录
			err_record.insert(make_pair(redef,str));
		}

		//向option'传递id属性
		pps[pps.size()-2]->getInhAttr()->tail.iLine=pt->param_id.tLine;
		pps[pps.size()-2]->getInhAttr()->tail.iLexime->swap(*(pt->param_id.tLexime));
	}

	static void act_tail1_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//生成数组类型
		pi->tail.iType.is_array=true;
		pi->tail.iType.length=0;

		//函数参数作为局部数组定义
		context.defineVar(*(pi->tail.iLexime),pi->tail.iType,pi->tail.iLine);

		//形参类型加入函数形参列表
		context.getFunInfo(context.getName())->param_list.push_back(pi->tail.iType);
	}
	static void act_tail2_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//生成变量类型
		pi->tail.iType.is_array=false;

		//函数参数作为局部变量定义
		context.defineVar(*(pi->tail.iLexime),pi->tail.iType,pi->tail.iLine);

		//形参类型加入函数形参列表
		context.getFunInfo(context.getName())->param_list.push_back(pi->tail.iType);
	}

	static void act_size_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//向S(size)传递A(const)属性
		pps[pps.size()-2]->getSynAttr()->size.tLine=pps.back()->getTempVar()->A_const.tLine;
		pps[pps.size()-2]->getSynAttr()->size.tValue=pps.back()->getTempVar()->A_const.tValue;
	}

	static void act_stmt2_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//转换成value
		ControlFlow2Value(context,pps.back()->getSynAttr());
	}

	static void act_stmt3_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//转换成control flow
		bool yes=Value2ControlFlow(context,ps);

		//转换成功
		if(yes)
		{
			//回填true分支
			context.BackPatch(ps->expr.spTrueList,context.getNextInstr());

			//将expr.falselist属性传递给E
			pps[pps.size()-5]->getInhAttr()->E.ipFalseList=ps->expr.spFalseList;

			//expr.falselist指针赋空
			ps->expr.spFalseList=0;
		}
		else
		{
			//错误报告
			string str="if语句条件表达式类型错误。";

			//追加到记录
			err_record.insert(make_pair(pps.back()->getTempVar()->if_line.tLine,str));
		}
	}
	static void act_stmt3_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//将S2(stmt)的nextlist属性传递给E
		pps[pps.size()-2]->getInhAttr()->E.ipNextList=ps->stmt.spNextList;

		//S2(stmt)的nextlist指针赋空
		ps->stmt.spNextList=0;

		//S2(stmt)的ret_cnt赋给stmt3
		pps[pps.size()-4]->getSynAttr()->stmt.sRetCnt=ps->stmt.sRetCnt;
	}
	static void act_stmt3_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S3(E)的nextlist赋给stmt3的nextlist
		if(ps->E.spNextList)
			pps[pps.size()-2]->getSynAttr()->stmt.spNextList->swap(*(ps->E.spNextList));	//使用交换代替赋值,以提高执行效率

		//S3(E)的ret_cnt累加到stmt3
		pps[pps.size()-2]->getSynAttr()->stmt.sRetCnt+=ps->E.sRetCnt;
	}

	static void act_stmt4_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//nextinstr->S2:begin
		pps[pps.size()-7]->getTempVar()->while_begin_continue_list.tBegin=context.getNextInstr();
	}
	static void act_stmt4_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//转换成control flow
		bool yes=Value2ControlFlow(context,ps);

		//转换成功
		if(yes)
		{
			//回填true分支
			context.BackPatch(ps->expr.spTrueList,context.getNextInstr());

			//将expr.falselist属性赋给stmt4的nextlist
			if(ps->expr.spFalseList)
				pps[pps.size()-5]->getSynAttr()->stmt.spNextList->swap(*(ps->expr.spFalseList));
		}
		else
		{
			//错误报告
			string str="while语句条件表达式类型错误。";

			//追加到记录
			err_record.insert(make_pair(pps.back()->getTempVar()->while_line.tLine,str));
		}	

		//stmt4的nextlist作为ibreaklist传递给stmt
		pps[pps.size()-3]->getInhAttr()->stmt.ipBreakList=pps[pps.size()-5]->getSynAttr()->stmt.spNextList;

		//S2(stmt)的icontinuelist传递给stmt
		pps[pps.size()-3]->getInhAttr()->stmt.ipContinueList=pps[pps.size()-4]->getTempVar()->while_begin_continue_list.tpContinueList;
	}
	static void act_stmt4_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//循环开始标号
		instr begin=pt->while_begin_continue_list.tBegin;

		//回填icontinuelist和nextlist
		context.BackPatch(pt->while_begin_continue_list.tpContinueList,begin);
		context.BackPatch(ps->stmt.spNextList,begin);

		//跳转到循环开始处
		context.Gen(op_goto,context.getAddress(int(begin)));

		//S2(stmt)的ret_cnt赋给stmt4
		pps[pps.size()-2]->getSynAttr()->stmt.sRetCnt=ps->stmt.sRetCnt;
	}

	static void act_stmt5_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//nextinstr->S2:begin
		pps[pps.size()-7]->getTempVar()->do_expr.tBegin=context.getNextInstr();

		//stmt5的nextlist作为ibreaklist传递给stmt
		pps[pps.size()-2]->getInhAttr()->stmt.ipBreakList=pps[pps.size()-10]->getSynAttr()->stmt.spNextList;

		//S1(stmt)的icontinuelist传递给stmt
		pps[pps.size()-2]->getInhAttr()->stmt.ipContinueList=pps[pps.size()-3]->getTempVar()->do_stmt_continue_list.tpContinueList;
	}
	static void act_stmt5_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//回填icontinuelist和nextlist
		instr next=context.getNextInstr();
		context.BackPatch(pt->do_stmt_continue_list.tpContinueList,next);
		context.BackPatch(ps->stmt.spNextList,next);

		//S1(stmt)的ret_cnt赋给stmt5
		pps[pps.size()-8]->getSynAttr()->stmt.sRetCnt=ps->stmt.sRetCnt;
	}
	static void act_stmt5_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//转换成control flow
		bool yes=Value2ControlFlow(context,ps);

		//转换成功
		if(yes)
		{
			//回填true分支
			context.BackPatch(ps->expr.spTrueList,pt->do_expr.tBegin);

			//将expr.falselist属性追加到stmt5的nextlist
			Append(&(pps[pps.size()-4]->getSynAttr()->stmt.spNextList),&(ps->expr.spFalseList));
		}
		else
		{
			//错误报告
			string str="do-while语句条件表达式类型错误。";

			//追加到记录
			err_record.insert(make_pair(pt->do_expr.tLine,str));
		}
	}

	static void act_stmt6_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		if(pi->stmt.ipBreakList)
		{
			//下一条指令加入break回填列表
			pi->stmt.ipBreakList->push_back(context.getNextInstr());

			//产生跳转指令
			context.Gen(op_goto);	//跳转目标地址待回填
		}
		else
		{
			//错误报告
			string str="非法的break。";

			//追加到记录
			err_record.insert(make_pair(pps.back()->getTempVar()->break_line.tLine,str));
		}
	}

	static void act_stmt7_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		if(pi->stmt.ipContinueList)
		{
			//下一条指令加入continue回填列表
			pi->stmt.ipContinueList->push_back(context.getNextInstr());

			//产生跳转指令
			context.Gen(op_goto);	//跳转目标地址待回填
		}
		else
		{
			//错误报告
			string str="非法的continue。";

			//追加到记录
			err_record.insert(make_pair(pps.back()->getTempVar()->continue_line.tLine,str));
		}
	}

	static void act_stmt9_A1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//nextinstr->A2:begin
		pps[pps.size()-7]->getTempVar()->for_expr.tBegin=context.getNextInstr();
	}
	static void act_stmt9_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//optexpr2.falselist属性赋给stmt9的nextlist
		if(ps->optexpr2.spFalseList)
			pps[pps.size()-8]->getSynAttr()->stmt.spNextList->swap(*(ps->optexpr2.spFalseList));

		//optexpr2.truelist属性赋给A2
		pps[pps.size()-4]->getTempVar()->for_expr.tpOptexpr2TrueList=ps->optexpr2.spTrueList;
		ps->optexpr2.spTrueList=0;

		//nextinstr->S2:continue
		pps[pps.size()-7]->getTempVar()->for_stmt_continue_continue_list.tContinue=context.getNextInstr();
	}
	static void act_stmt9_A2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Temp_Var *pt=pps.back()->getTempVar();

		//生成跳转到begin的指令
		context.Gen(op_goto,context.getAddress(int(pps.back()->getTempVar()->for_expr.tBegin)));

		//回真条件表达式的真出口
		context.BackPatch(pt->for_expr.tpOptexpr2TrueList,context.getNextInstr());

		//stmt9的nextlist作为ibreaklist传递给stmt
		pps[pps.size()-3]->getInhAttr()->stmt.ipBreakList=pps[pps.size()-5]->getSynAttr()->stmt.spNextList;

		//S2(stmt)的icontinuelist传递给stmt
		pps[pps.size()-3]->getInhAttr()->stmt.ipContinueList=pps[pps.size()-4]->getTempVar()->for_stmt_continue_continue_list.tpContinueList;
	}
	static void act_stmt9_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//循环continue标号
		instr continue_label=pt->for_stmt_continue_continue_list.tContinue;

		//回填icontinuelist和nextlist
		context.BackPatch(pt->for_stmt_continue_continue_list.tpContinueList,continue_label);
		context.BackPatch(ps->stmt.spNextList,continue_label);

		//跳转到循环continue处
		context.Gen(op_goto,context.getAddress(int(continue_label)));

		//S2(stmt)的ret_cnt赋给stmt4
		pps[pps.size()-2]->getSynAttr()->stmt.sRetCnt=ps->stmt.sRetCnt;
	}

	static void act_stmt10_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//转换成value
		ControlFlow2Value(context,ps);

		if(ps->expr.sType.is_array)
		{
			//错误报告
			string str="switch的表达式不能是数组。";

			//追加到记录
			err_record.insert(make_pair(pps.back()->getTempVar()->switch_expr_line.tLine,str));
		}
		//如果为整型
		else if(isInteger(ps->expr.sType.type))
		{
			//下一条跳转指令加入S2的testlist回填列表
			pps[pps.size()-4]->getTempVar()->swtich_stmt_testlist_var_instr_list.tpTestList->push_back(context.getNextInstr());

			//产生跳转指令
			context.Gen(op_goto);	//跳转目标地址待回填

			//stmt10的nextlist作为ibreaklist传递给stmt
			pps[pps.size()-3]->getInhAttr()->stmt.ipBreakList=pps[pps.size()-5]->getSynAttr()->stmt.spNextList;

			//expr.addr传递给stmt.iaddr
			pps[pps.size()-3]->getInhAttr()->stmt.iAddr=ps->expr.sAddr;

			//S2的var_instr_list传递给stmt
			pps[pps.size()-3]->getInhAttr()->stmt.ipVarInstrList=pps[pps.size()-4]->getTempVar()->swtich_stmt_testlist_var_instr_list.tpVarInstrList;
		
			//expr.addr同时传递给S2
			pps[pps.size()-4]->getTempVar()->swtich_stmt_testlist_var_instr_list.tAddr=ps->expr.sAddr;
		}
		else
		{
			//错误报告
			string str="switch的表达式不是整型。";

			//追加到记录
			err_record.insert(make_pair(pps.back()->getTempVar()->switch_expr_line.tLine,str));
		}
	}
	static void act_stmt10_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//下一条跳转指令加入nextlist回填列表
		ps->stmt.spNextList->push_back(context.getNextInstr());

		//产生跳转指令
		context.Gen(op_goto);	//跳转目标地址待回填

		//回填testlist
		context.BackPatch(pt->swtich_stmt_testlist_var_instr_list.tpTestList,context.getNextInstr());

		//构造临时变量类型
		VarInfo vi;
		vi.type=t_INT;
		vi.is_array=false;

		//临时变量地址
		Address temp_addr;

		//表达式地址
		Address expr_addr=pt->swtich_stmt_testlist_var_instr_list.tAddr;

		//case/default分支标号地址
		Address label_addr;

		//case/default分支跳转目标
		instr target;

		//生成各case/default分支的测试代码
		while(!pt->swtich_stmt_testlist_var_instr_list.tpVarInstrList->empty())
		{
			//default标号必须放在最后
			if(pt->swtich_stmt_testlist_var_instr_list.tpVarInstrList->front().first && 1<pt->swtich_stmt_testlist_var_instr_list.tpVarInstrList->size())
			{
				pt->swtich_stmt_testlist_var_instr_list.tpVarInstrList->push_back(pt->swtich_stmt_testlist_var_instr_list.tpVarInstrList->front());
			}
			else
			{			
				//构造临时变量地址
				temp_addr=context.Temp(vi);

				//获取分支标号地址
				label_addr=pt->swtich_stmt_testlist_var_instr_list.tpVarInstrList->front().second.first;

				//获取分支跳转目标
				target=pt->swtich_stmt_testlist_var_instr_list.tpVarInstrList->front().second.second;

				//产生表达式与标号比较指令
				context.Gen(op_sub,expr_addr,label_addr,temp_addr);

				//产生测试并跳转指令
				context.Gen(op_if_false_goto,temp_addr,context.getAddress(int(target)));
			}

			pt->swtich_stmt_testlist_var_instr_list.tpVarInstrList->pop_front();
		}

		//将S2(stmt)的nextlist属性追加到stmt10的nextlist
		Append(&(pps[pps.size()-2]->getSynAttr()->stmt.spNextList),&(ps->stmt.spNextList));

		//S2(stmt)的ret_cnt赋给stmt10
		pps[pps.size()-2]->getSynAttr()->stmt.sRetCnt=ps->stmt.sRetCnt;
	}

	static void act_stmt11_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Syn_Attr *ps=pps.back()->getSynAttr();

		if(pi->stmt.ipBreakList && pi->stmt.ipVarInstrList)
		{
			//构造标号地址
			Address label_addr=context.getAddress(int(ps->label.tValue));

			//标号必须唯一
			if(isExist(pi->stmt.ipVarInstrList,label_addr))
			{
				//错误报告
				string str="case标号值\""+toString(int(ps->label.tValue))+"\"已使用。";

				//追加到记录
				err_record.insert(make_pair(ps->label.tLine,str));
			}
			else
			{
				//标号地址和代码地址加入列表
				pi->stmt.ipVarInstrList->push_back(make_pair(false,make_pair(label_addr,context.getNextInstr())));
			}
		}
		else
		{
			//错误报告
			string str="非法的case。";

			//追加到记录
			err_record.insert(make_pair(ps->label.tLine,str));
		}
	}
	static void act_stmt11_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S2(stmt)的nextlist赋给stmt11的nextlist
		if(ps->stmt.spNextList)
			pps[pps.size()-2]->getSynAttr()->stmt.spNextList->swap(*(ps->stmt.spNextList));	//使用交换代替赋值,以提高执行效率

		//S2(stmt)的ret_cnt赋给stmt11
		pps[pps.size()-2]->getSynAttr()->stmt.sRetCnt=ps->stmt.sRetCnt;
	}

	static void act_stmt12_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{	
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		if(pi->stmt.ipBreakList && pi->stmt.ipVarInstrList && s_INVALID!=pi->stmt.iAddr.section)
		{
			//default必须唯一
			if(isExist(pi->stmt.ipVarInstrList,pi->stmt.iAddr))
			{
				//错误报告
				string str="default多于一个。";

				//追加到记录
				err_record.insert(make_pair(pt->op_line.tLine,str));
			}
			else
			{
				//标号地址和代码地址加入列表
				pi->stmt.ipVarInstrList->push_back(make_pair(true,make_pair(pi->stmt.iAddr,context.getNextInstr())));
			}
		}
		else
		{
			//错误报告
			string str="非法的default。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}

	}
	static void act_stmt12_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(stmt)的nextlist赋给stmt12的nextlist
		if(ps->stmt.spNextList)
			pps[pps.size()-2]->getSynAttr()->stmt.spNextList->swap(*(ps->stmt.spNextList));	//使用交换代替赋值,以提高执行效率

		//S(stmt)的ret_cnt赋给stmt12
		pps[pps.size()-2]->getSynAttr()->stmt.sRetCnt=ps->stmt.sRetCnt;
	}

	static void act_stmt13_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(stmts)的nextlist赋给stmt13的nextlist
		if(ps->stmts.spNextList)
			pps[pps.size()-3]->getSynAttr()->stmt.spNextList->swap(*(ps->stmts.spNextList));	//使用交换代替赋值,以提高执行效率

		//S(stmts)的ret_cnt赋给stmt13
		pps[pps.size()-3]->getSynAttr()->stmt.sRetCnt=ps->stmts.sRetCnt;
	}

	static void act_E1_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();	
		
		//下一条跳转指令加入E的inextlist回填列表
		if(pi->E.ipNextList)
			pi->E.ipNextList->push_back(context.getNextInstr());

		//产生跳转指令
		context.Gen(op_goto);	//跳转目标地址待回填

		//回填E的ifalselist列表
		context.BackPatch(pi->E.ipFalseList,context.getNextInstr());

		//传递E的inextlist给S(stmt)
		pps[pps.size()-3]->getInhAttr()->E.ipNextList=pi->E.ipNextList;

		//赋空A的inextlist
		pi->E.ipNextList=0;
	}
	static void act_E1_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//E的inextlist和S(stmt)的nextlist合并到E的nextlist
		Append(&(ps->stmt.spNextList),&(pi->E.ipNextList));
		if(ps->stmt.spNextList)
			pps[pps.size()-2]->getSynAttr()->E.spNextList->swap(*(ps->stmt.spNextList));

		//S(stmt)的ret_cnt赋给E
		pps[pps.size()-2]->getSynAttr()->E.sRetCnt=ps->stmt.sRetCnt;
	}
	static void act_E2_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();	

		//E的inextlist和ifalselist合并到E的nextlist
		Append(&(pps[pps.size()-2]->getSynAttr()->E.spNextList),&(pi->E.ipNextList));
		Append(&(pps[pps.size()-2]->getSynAttr()->E.spNextList),&(pi->E.ipFalseList));
	}

	static void act_stmts1_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//回填S1(stmt)的nextlist
		context.BackPatch(ps->stmt.spNextList,context.getNextInstr());

		//S1(stmt)的ret_cnt赋给stmts
		pps[pps.size()-4]->getSynAttr()->stmts.sRetCnt=ps->stmt.sRetCnt;
	}
	static void act_stmts1_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S2(stmts)的nextlist赋给stmts
		if(ps->stmts.spNextList)
			pps[pps.size()-2]->getSynAttr()->stmts.spNextList->swap(*(ps->stmts.spNextList));

		//S2(stmts)的ret_cnt累加到stmts
		pps[pps.size()-2]->getSynAttr()->stmts.sRetCnt+=ps->stmts.sRetCnt;
	}

	static void act_optexpr2A_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();	
		Syn_Attr *ps=pps.back()->getSynAttr();

		//如果是求值表达式
		if(pi->optexpr2.iValFlag)
		{
			//转换成value形式
			ControlFlow2Value(context,ps);
		}
		//如果是控制流
		else
		{
			//转换成control flow
			bool yes=Value2ControlFlow(context,ps);

			//转换成功
			if(yes)
			{
				//S(expr)的回填列表赋给optexpr2
				if(ps->expr.spTrueList)
					pps[pps.size()-2]->getSynAttr()->optexpr2.spTrueList->swap(*(ps->expr.spTrueList));
				if(ps->expr.spFalseList)
					pps[pps.size()-2]->getSynAttr()->optexpr2.spFalseList->swap(*(ps->expr.spFalseList));
			}
			else
			{
				//错误报告
				string str="for语句条件表达式类型错误。";

				//追加到记录
				err_record.insert(make_pair(pi->optexpr2.iLine,str));
			}
		}
	}
	static void act_optexpr2B_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//如果是控制流
		if(!pps.back()->getInhAttr()->optexpr2.iValFlag)
		{
			//默认空的表达式表示永远为真
			pps[pps.size()-2]->getSynAttr()->optexpr2.spTrueList->push_back(context.getNextInstr());

			//产生直接跳转到真出口的指令
			context.Gen(op_goto);	//跳转目标地址待回填
		}
	}

	static void act_optexpr3A_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();	
		Syn_Attr *ps=pps.back()->getSynAttr();

		//转换成value形式
		ControlFlow2Value(context,ps);

		//获取上下文函数名
		string name=context.getName();

		//获取上下文函数信息
		FunInfo const& fun_info=*context.getFunInfo(name);

		//函数无返回类型
		if(t_VOID==fun_info.ret_type)
		{
			if(t_VOID==ps->expr.sType.type)
			{
				//生成返回指令
				context.Gen(op_return);
			}
			else
			{
				//错误报告
				string str="\"void\"函数"+name+"返回值。";

				//追加到记录
				err_record.insert(make_pair(pi->optexpr3.iLine,str));
			}
		}
		//函数有返回类型
		else
		{
			//可计算类型
			if(Computable(ps->expr.sType))
			{				
				//生成返回指令
				context.Gen(op_return_value,ps->expr.sAddr);
			}
			else
			{
				//错误报告
				string str="函数"+name+"返回类型错误。";

				//追加到记录
				err_record.insert(make_pair(pi->optexpr3.iLine,str));
			}
		}
	}
	static void act_optexpr3B_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();	

		//获取上下文函数名
		string name=context.getName();

		//获取上下文函数信息
		FunInfo const& fun_info=*context.getFunInfo(name);

		//函数无返回类型
		if(t_VOID==fun_info.ret_type)
		{
			//生成返回指令
			context.Gen(op_return);
		}
		//函数有返回类型
		else
		{
			//错误报告
			string str="函数"+name+"必须返回值。";

			//追加到记录
			err_record.insert(make_pair(pi->optexpr3.iLine,str));
		}
	}

	static void act_label_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//向S(label)传递A(const)属性
		pps[pps.size()-2]->getSynAttr()->label.tLine=pps.back()->getTempVar()->case_const.tLine;
		pps[pps.size()-2]->getSynAttr()->label.tValue=pps.back()->getTempVar()->case_const.tValue;
	}
	static void act_label_A2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//向S(label)传递A(const)属性
		pps[pps.size()-2]->getSynAttr()->label.tLine=pps.back()->getTempVar()->case_const.tLine;
		pps[pps.size()-2]->getSynAttr()->label.tValue=-(pps.back()->getTempVar()->case_const.tValue);
	}

	static void act_expr_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//向expr'传递e1
		pps[pps.size()-2]->getInhAttr()->expr_.iValFlag=ps->e1.sValFlag;
		pps[pps.size()-2]->getInhAttr()->expr_.iType=ps->e1.sType;
		pps[pps.size()-2]->getInhAttr()->expr_.iAddr=ps->e1.sAddr;
		pps[pps.size()-2]->getInhAttr()->expr_.ipTrueList=ps->e1.spTrueList;	//使用浅拷贝
		pps[pps.size()-2]->getInhAttr()->expr_.ipFalseList=ps->e1.spFalseList;

		//赋空e1动态内存指针
		ps->e1.spTrueList=0;
		ps->e1.spFalseList=0;
	}
	static void act_expr_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();
		
		//expr'的综合属性赋给expr
		pps[pps.size()-2]->getSynAttr()->expr.sValFlag=ps->expr_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->expr.sType=ps->expr_.sType;
		pps[pps.size()-2]->getSynAttr()->expr.sAddr=ps->expr_.sAddr;
		if(ps->expr_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->expr.spTrueList->swap(*(ps->expr_.spTrueList));	//不能使用浅拷贝
		if(ps->expr_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->expr.spFalseList->swap(*(ps->expr_.spFalseList));	
	}

	static void act_expr_1_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//expr'转换成value形式
		ControlFlow2Value(context,pi);
	}
	static void act_expr_1_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//e1转换成value形式
		ControlFlow2Value(context,ps);

		//向expr'1传递e1
		pps[pps.size()-2]->getInhAttr()->expr_.iValFlag=true;
		pps[pps.size()-2]->getInhAttr()->expr_.iType=ps->e1.sType;
		pps[pps.size()-2]->getInhAttr()->expr_.iAddr=ps->e1.sAddr;
	}
	static void act_expr_1_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//expr'1的综合属性赋给expr'
		pps[pps.size()-2]->getSynAttr()->expr_=ps->expr_;	//使用浅拷贝

		//赋空expr'1动态内存指针
		ps->expr_.spTrueList=0;
		ps->expr_.spFalseList=0;		
	}
	static void act_expr_2_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//A(expr')的继承属性传回给expr'的综合属性
		pps[pps.size()-2]->getSynAttr()->expr_.sValFlag=pi->expr_.iValFlag;	
		pps[pps.size()-2]->getSynAttr()->expr_.sType=pi->expr_.iType;
		pps[pps.size()-2]->getSynAttr()->expr_.sAddr=pi->expr_.iAddr;

		Append(&(pps[pps.size()-2]->getSynAttr()->expr_.spTrueList),&(pi->expr_.ipTrueList));
		Append(&(pps[pps.size()-2]->getSynAttr()->expr_.spFalseList),&(pi->expr_.ipFalseList));

		//赋空指针
		//pi->expr_.ipTrueList=0;
		//pi->expr_.ipFalseList=0;
	}

	static void act_e1A_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Temp_Var *pt=pps.back()->getTempVar();

		//id属性传递给T1
		pps[pps.size()-2]->getInhAttr()->T1.iLine=pt->e1_id.tLine;
		pps[pps.size()-2]->getInhAttr()->T1.iLexime->swap(*(pt->e1_id.tLexime));
	}
	static void act_e1A_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//T1的综合属性赋给e1
		pps[pps.size()-2]->getSynAttr()->e1.sValFlag=pps.back()->getSynAttr()->T1.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e1.sType=pps.back()->getSynAttr()->T1.sType;
		pps[pps.size()-2]->getSynAttr()->e1.sAddr=pps.back()->getSynAttr()->T1.sAddr;
		if(ps->T1.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e1.spTrueList->swap(*(ps->T1.spTrueList));	//不能使用浅拷贝
		if(ps->T1.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e1.spFalseList->swap(*(ps->T1.spFalseList));
	}
	static void act_e1B_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//e2的综合属性赋给e1
		pps[pps.size()-2]->getSynAttr()->e1.sValFlag=pps.back()->getSynAttr()->e2.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e1.sType=pps.back()->getSynAttr()->e2.sType;
		pps[pps.size()-2]->getSynAttr()->e1.sAddr=pps.back()->getSynAttr()->e2.sAddr;
		if(ps->e2.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e1.spTrueList->swap(*(ps->e2.spTrueList));	//不能使用浅拷贝
		if(ps->e2.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e1.spFalseList->swap(*(ps->e2.spFalseList));
	}

	static void act_e2_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//向e2'传递e3
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3.spTrueList;	//使用浅拷贝
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3.spFalseList;

		//赋空e3动态内存指针
		ps->e3.spTrueList=0;
		ps->e3.spFalseList=0;
	}
	static void act_e2_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//e2'的综合属性赋给e2
		pps[pps.size()-2]->getSynAttr()->e2.sValFlag=ps->e2_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e2.sType=ps->e2_.sType;
		pps[pps.size()-2]->getSynAttr()->e2.sAddr=ps->e2_.sAddr;
		if(ps->e2_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e2.spTrueList->swap(*(ps->e2_.spTrueList));	//不能使用浅拷贝
		if(ps->e2_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e2.spFalseList->swap(*(ps->e2_.spFalseList));	
	}

	static void act_e2_1_A1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//转换成control flow
		bool yes=Value2ControlFlow(context,pi,pi->e2_.iSection);

		//转换成功
		if(yes)
		{
			//回填true分支
			context.BackPatch(pi->e2_.ipTrueList,context.getNextInstr(pi->e2_.iSection),pi->e2_.iSection);

			//将e2'.falselist属性传递给S1
			pps[pps.size()-3]->getInhAttr()->e2_.ipFalseList=pi->e2_.ipFalseList;

			//e2'.falselist指针赋空
			pi->e2_.ipFalseList=0;
		}
		else
		{
			//错误报告
			string str="条件表达式的第一个子表达式类型错误。";

			//追加到记录
			err_record.insert(make_pair(pps.back()->getTempVar()->op_line.tLine,str));
		}
	}
	static void act_e2_1_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//转换成value
		ControlFlow2Value(context,ps,pi->e2_.iSection);

		//下一条指令加入S2的truelist回填列表
		if(pps[pps.size()-5]->getInhAttr()->e2_.ipTrueList)
			pps[pps.size()-5]->getInhAttr()->e2_.ipTrueList->push_back(context.getNextInstr(pi->e2_.iSection));

		//产生跳转指令
		context.Gen(op_goto,pi->e2_.iSection);	//跳转目标地址待回填

		//回填false分支
		context.BackPatch(pi->e2_.ipFalseList,context.getNextInstr(pi->e2_.iSection),pi->e2_.iSection);

		//e3的type和addr传递给S2
		pps[pps.size()-5]->getInhAttr()->e2_.iType=ps->e3.sType;
		pps[pps.size()-5]->getInhAttr()->e2_.iAddr=ps->e3.sAddr;
	}
	static void act_e2_1_A2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//A2的line传递给S2
		pps[pps.size()-3]->getTempVar()->op_line.tLine=pps.back()->getTempVar()->op_line.tLine;
	}
	static void act_e2_1_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//转换成value
		ControlFlow2Value(context,ps,pi->e2_.iSection);

		//两个子表达式同时为void类型
		if(t_VOID==ps->e2.sType.type && t_VOID==pi->e2_.iType.type)
		{
			//生成e2'类型
			pps[pps.size()-2]->getSynAttr()->e2_.sType.type=t_VOID;

			//修改e2'值标志
			pps[pps.size()-2]->getSynAttr()->e2_.sValFlag=true;
		}
		//两个子表达式同时不为void类型,且同时不为数组
		else if(t_VOID!=ps->e2.sType.type && t_VOID!=pi->e2_.iType.type && !ps->e2.sType.is_array && !pi->e2_.iType.is_array)
		{
			//生成e2'类型
			pps[pps.size()-2]->getSynAttr()->e2_.sType.type=Advance(ps->e2.sType.type,pi->e2_.iType.type);
			pps[pps.size()-2]->getSynAttr()->e2_.sType.is_array=false;

			//生成e2'地址
			pps[pps.size()-2]->getSynAttr()->e2_.sAddr=context.Temp(pps[pps.size()-2]->getSynAttr()->e2_.sType,pi->e2_.iSection);

			//修改e2'值标志
			pps[pps.size()-2]->getSynAttr()->e2_.sValFlag=true;

			//生成e2的value赋给e2'的代码
			context.Gen(op_assign,pps[pps.size()-2]->getSynAttr()->e2_.sAddr,ps->e2.sAddr,pi->e2_.iSection);

			//下一条指令加入S2的falselist回填列表
			if(pi->e2_.ipFalseList)
				pi->e2_.ipFalseList->push_back(context.getNextInstr(pi->e2_.iSection));

			//产生跳转指令
			context.Gen(op_goto,pi->e2_.iSection);	//跳转目标地址待回填

			//回填S2的truelist
			context.BackPatch(pi->e2_.ipTrueList,context.getNextInstr(pi->e2_.iSection));

			//生成e3的value赋给e2'的代码
			context.Gen(op_assign,pps[pps.size()-2]->getSynAttr()->e2_.sAddr,pi->e2_.iAddr,pi->e2_.iSection);

			//回填S2的falselist
			context.BackPatch(pi->e2_.ipFalseList,context.getNextInstr(pi->e2_.iSection));

			//生成no-op指令
			context.Gen(op_no_op,pi->e2_.iSection);
		}
		else
		{
			//错误报告
			string str="条件表达式的第2个子表达式和第3个子表达式的类型不兼容。";

			//追加到记录
			err_record.insert(make_pair(pps.back()->getTempVar()->op_line.tLine,str));
		}
	}
	static void act_e2_2_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//A(e2')的继承属性传回给e2'的综合属性
		pps[pps.size()-2]->getSynAttr()->e2_.sValFlag=pi->e2_.iValFlag;	
		pps[pps.size()-2]->getSynAttr()->e2_.sType=pi->e2_.iType;
		pps[pps.size()-2]->getSynAttr()->e2_.sAddr=pi->e2_.iAddr;
		Append(&(pps[pps.size()-2]->getSynAttr()->e2_.spTrueList),&(pi->e2_.ipTrueList));
		Append(&(pps[pps.size()-2]->getSynAttr()->e2_.spFalseList),&(pi->e2_.ipFalseList));

		//赋空指针
		//pi->e2_.ipTrueList=0;		
		//pi->e2_.ipFalseList=0;	
	}

	static void act_e3_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//向e3'传递e4
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4.spTrueList;		//使用浅拷贝
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4.spFalseList;

		//赋空e4动态内存指针
		ps->e4.spTrueList=0;
		ps->e4.spFalseList=0;	
	}
	static void act_e3_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//e3'的综合属性赋给e3
		pps[pps.size()-2]->getSynAttr()->e3.sValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e3.sType=ps->e3_.sType;
		pps[pps.size()-2]->getSynAttr()->e3.sAddr=ps->e3_.sAddr;
		if(ps->e3_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e3.spTrueList->swap(*(ps->e3_.spTrueList));	//不能使用浅拷贝
		if(ps->e3_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e3.spFalseList->swap(*(ps->e3_.spFalseList));			
	}

	static void act_e3_1_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//转换成control flow
		bool yes=Value2ControlFlow(context,pi,pi->e3_.iSection);

		//转换成功
		if(yes)
		{
			//回填false分支
			context.BackPatch(pi->e3_.ipFalseList,context.getNextInstr(pi->e3_.iSection),pi->e3_.iSection);

			//将e3'.truelist属性传递给S1
			pps[pps.size()-3]->getInhAttr()->e3_.ipTrueList=pi->e3_.ipTrueList;

			//e3'.truelist指针赋空
			pi->e3_.ipTrueList=0;
		}
		else
		{
			//错误报告
			string str="|| 左操作数类型错误。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}

		//将op属性传递给S1	
		pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
	}
	static void act_e3_1_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//转换成control flow
		bool yes=Value2ControlFlow(context,ps,pi->e3_.iSection);

		//转换成功
		if(yes)
		{
			//继承属性传递给S后面的e3'
			pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=false;
			pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4.spFalseList;
			Append(&(ps->e4.spTrueList),&(pi->e3_.ipTrueList));
			pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4.spTrueList;

			//指针赋空
			ps->e4.spTrueList=0;
			ps->e4.spFalseList=0;
		}
		else
		{
			//错误报告
			string str="|| 右操作数类型错误。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e3_1_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(e3')的综合属性赋给e3'
		pps[pps.size()-2]->getSynAttr()->e3_.sValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e3_.sType=ps->e3_.sType;
		pps[pps.size()-2]->getSynAttr()->e3_.sAddr=ps->e3_.sAddr;
		if(ps->e3_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e3_.spTrueList->swap(*(ps->e3_.spTrueList));	//不能使用浅拷贝
		if(ps->e3_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e3_.spFalseList->swap(*(ps->e3_.spFalseList));
	}
	static void act_e3_2_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//A(e3')的继承属性传回给e3'的综合属性
		pps[pps.size()-2]->getSynAttr()->e3_.sValFlag=pi->e3_.iValFlag;	
		pps[pps.size()-2]->getSynAttr()->e3_.sType=pi->e3_.iType;
		pps[pps.size()-2]->getSynAttr()->e3_.sAddr=pi->e3_.iAddr;
		Append(&(pps[pps.size()-2]->getSynAttr()->e3_.spTrueList),&(pi->e3_.ipTrueList));
		Append(&(pps[pps.size()-2]->getSynAttr()->e3_.spFalseList),&(pi->e3_.ipFalseList));

		//赋空指针
		//pi->e3_.ipTrueList=0;
		//pi->e3_.ipFalseList=0;
	}

	static void act_e4_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//向e4'传递e5
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5.spTrueList;		//使用浅拷贝
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5.spFalseList;

		//赋空e5动态内存指针
		ps->e5.spTrueList=0;
		ps->e5.spFalseList=0;	
	}
	static void act_e4_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//e4'的综合属性赋给e4
		pps[pps.size()-2]->getSynAttr()->e4.sValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e4.sType=ps->e4_.sType;
		pps[pps.size()-2]->getSynAttr()->e4.sAddr=ps->e4_.sAddr;
		if(ps->e4_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e4.spTrueList->swap(*(ps->e4_.spTrueList));	//不能使用浅拷贝
		if(ps->e4_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e4.spFalseList->swap(*(ps->e4_.spFalseList));	
	}

	static void act_e4_1_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//转换成control flow
		bool yes=Value2ControlFlow(context,pi,pi->e4_.iSection);

		//转换成功
		if(yes)
		{
			//回填true分支
			context.BackPatch(pi->e4_.ipTrueList,context.getNextInstr(pi->e4_.iSection),pi->e4_.iSection);

			//将e4'.falselist属性传递给S1
			pps[pps.size()-3]->getInhAttr()->e4_.ipFalseList=pi->e4_.ipFalseList;

			//e4'.falselist指针赋空
			pi->e4_.ipFalseList=0;
		}
		else
		{
			//错误报告
			string str="&& 左操作数类型错误。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}			
		
		//将op属性传递给S1
		pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
	}
	static void act_e4_1_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//转换成control flow
		bool yes=Value2ControlFlow(context,ps,pi->e4_.iSection);

		//转换成功
		if(yes)
		{
			//继承属性传递给S后面的e4'
			pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=false;
			Append(&(ps->e5.spFalseList),&(pi->e4_.ipFalseList));
			pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5.spFalseList;
			pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5.spTrueList;

			//指针赋空
			ps->e5.spTrueList=0;
			ps->e5.spFalseList=0;
		}
		else
		{
			//错误报告
			string str="&& 右操作数类型错误。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e4_1_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(e4')的综合属性赋给e4'
		pps[pps.size()-2]->getSynAttr()->e4_.sValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e4_.sType=ps->e4_.sType;
		pps[pps.size()-2]->getSynAttr()->e4_.sAddr=ps->e4_.sAddr;
		if(ps->e4_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e4_.spTrueList->swap(*(ps->e4_.spTrueList));	//不能使用浅拷贝
		if(ps->e4_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e4_.spFalseList->swap(*(ps->e4_.spFalseList));
	}
	static void act_e4_2_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//A(e4')的继承属性传回给e4'的综合属性
		pps[pps.size()-2]->getSynAttr()->e4_.sValFlag=pi->e4_.iValFlag;	
		pps[pps.size()-2]->getSynAttr()->e4_.sType=pi->e4_.iType;
		pps[pps.size()-2]->getSynAttr()->e4_.sAddr=pi->e4_.iAddr;
		Append(&(pps[pps.size()-2]->getSynAttr()->e4_.spTrueList),&(pi->e4_.ipTrueList));
		Append(&(pps[pps.size()-2]->getSynAttr()->e4_.spFalseList),&(pi->e4_.ipFalseList));

		//赋空指针
		//pi->e4_.ipTrueList=0;
		//pi->e4_.ipFalseList=0;
	}

	static void act_e5_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//向e5'传递e6
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6.spTrueList;		//使用浅拷贝
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6.spFalseList;

		//赋空e6动态内存指针
		ps->e6.spTrueList=0;
		ps->e6.spFalseList=0;	
	}
	static void act_e5_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//e5'的综合属性赋给e5
		pps[pps.size()-2]->getSynAttr()->e5.sValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e5.sType=ps->e5_.sType;
		pps[pps.size()-2]->getSynAttr()->e5.sAddr=ps->e5_.sAddr;
		if(ps->e5_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e5.spTrueList->swap(*(ps->e5_.spTrueList));	//不能使用浅拷贝
		if(ps->e5_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e5.spFalseList->swap(*(ps->e5_.spFalseList));
	}

	static void act_e5_1_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//转换成value
		ControlFlow2Value(context,pi,pi->e5_.iSection);

		//如果左操作数类型是整型
		if(isInteger(pi->e5_.iType.type))
		{
			//将e5'.addr属性传递给S1
			pps[pps.size()-3]->getInhAttr()->e5_.iAddr=pi->e5_.iAddr;

			//将op属性传递给S1
			pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
		}
		else
		{
			//错误报告
			string str="| 左操作数类型必须是整型。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e5_1_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//转换成value
		ControlFlow2Value(context,ps,pi->e5_.iSection);

		if(ps->e6.sType.is_array)
		{
			//错误报告
			string str="| 右操作数不能是数组。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
		//如果右操作数类型是整型
		else if(isInteger(ps->e6.sType.type))
		{
			//继承属性传递给S后面的e5'
			pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e5_.iType.type=t_INT;
			pps[pps.size()-2]->getInhAttr()->e5_.iType.is_array=false;
			pps[pps.size()-2]->getInhAttr()->e5_.iAddr=context.Temp(pps[pps.size()-2]->getInhAttr()->e5_.iType,pi->e5_.iSection);

			//生成操作指令代码
			context.Gen(op_bit_or,pi->e5_.iAddr,ps->e6.sAddr,pps[pps.size()-2]->getInhAttr()->e5_.iAddr,pi->e5_.iSection);
		}
		else
		{
			//错误报告
			string str="| 右操作数类型必须是整型。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e5_1_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(e5')的综合属性赋给e5'
		pps[pps.size()-2]->getSynAttr()->e5_.sValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e5_.sType=ps->e5_.sType;
		pps[pps.size()-2]->getSynAttr()->e5_.sAddr=ps->e5_.sAddr;
		if(ps->e5_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e5_.spTrueList->swap(*(ps->e5_.spTrueList));	//不能使用浅拷贝
		if(ps->e5_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e5_.spFalseList->swap(*(ps->e5_.spFalseList));
	}
	static void act_e5_2_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//A(e5')的继承属性传回给e5'的综合属性
		pps[pps.size()-2]->getSynAttr()->e5_.sValFlag=pi->e5_.iValFlag;	
		pps[pps.size()-2]->getSynAttr()->e5_.sType=pi->e5_.iType;
		pps[pps.size()-2]->getSynAttr()->e5_.sAddr=pi->e5_.iAddr;
		Append(&(pps[pps.size()-2]->getSynAttr()->e5_.spTrueList),&(pi->e5_.ipTrueList));
		Append(&(pps[pps.size()-2]->getSynAttr()->e5_.spFalseList),&(pi->e5_.ipFalseList));
	
		//赋空指针
		//pi->e5_.ipTrueList=0;
		//pi->e5_.ipFalseList=0;
	}

	static void act_e6_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//向e6'传递e7
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7.spTrueList;		//使用浅拷贝
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7.spFalseList;

		//赋空e7动态内存指针
		ps->e7.spTrueList=0;
		ps->e7.spFalseList=0;	
	}
	static void act_e6_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//e6'的综合属性赋给e6
		pps[pps.size()-2]->getSynAttr()->e6.sValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e6.sType=ps->e6_.sType;
		pps[pps.size()-2]->getSynAttr()->e6.sAddr=ps->e6_.sAddr;
		if(ps->e6_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e6.spTrueList->swap(*(ps->e6_.spTrueList));	//不能使用浅拷贝
		if(ps->e6_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e6.spFalseList->swap(*(ps->e6_.spFalseList));
	}

	static void act_e6_1_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//转换成value
		ControlFlow2Value(context,pi,pi->e6_.iSection);

		//如果左操作数类型是整型
		if(isInteger(pi->e6_.iType.type))
		{
			//将e6'.addr属性传递给S1
			pps[pps.size()-3]->getInhAttr()->e6_.iAddr=pi->e6_.iAddr;

			//将op属性传递给S1
			pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
		}
		else
		{
			//错误报告
			string str="^ 左操作数类型必须是整型。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e6_1_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//转换成value
		ControlFlow2Value(context,ps,pi->e6_.iSection);

		if(ps->e7.sType.is_array)
		{
			//错误报告
			string str="^ 右操作数不能是数组。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
		//如果右操作数类型是整型
		else if(isInteger(ps->e7.sType.type))
		{
			//继承属性传递给S后面的e6'
			pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e6_.iType.type=t_INT;
			pps[pps.size()-2]->getInhAttr()->e6_.iType.is_array=false;
			pps[pps.size()-2]->getInhAttr()->e6_.iAddr=context.Temp(pps[pps.size()-2]->getInhAttr()->e6_.iType,pi->e6_.iSection);

			//生成操作指令代码
			context.Gen(op_bit_xor,pi->e6_.iAddr,ps->e7.sAddr,pps[pps.size()-2]->getInhAttr()->e6_.iAddr,pi->e6_.iSection);
		}
		else
		{
			//错误报告
			string str="^ 右操作数类型必须是整型。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e6_1_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(e6')的综合属性赋给e6'
		pps[pps.size()-2]->getSynAttr()->e6_.sValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e6_.sType=ps->e6_.sType;
		pps[pps.size()-2]->getSynAttr()->e6_.sAddr=ps->e6_.sAddr;
		if(ps->e6_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e6_.spTrueList->swap(*(ps->e6_.spTrueList));	//不能使用浅拷贝
		if(ps->e6_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e6_.spFalseList->swap(*(ps->e6_.spFalseList));
	}
	static void act_e6_2_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//A(e6')的继承属性传回给e6'的综合属性
		pps[pps.size()-2]->getSynAttr()->e6_.sValFlag=pi->e6_.iValFlag;	
		pps[pps.size()-2]->getSynAttr()->e6_.sType=pi->e6_.iType;
		pps[pps.size()-2]->getSynAttr()->e6_.sAddr=pi->e6_.iAddr;
		Append(&(pps[pps.size()-2]->getSynAttr()->e6_.spTrueList),&(pi->e6_.ipTrueList));
		Append(&(pps[pps.size()-2]->getSynAttr()->e6_.spFalseList),&(pi->e6_.ipFalseList));

		//赋空指针
		//pi->e6_.ipTrueList=0;
		//pi->e6_.ipFalseList=0;
	}

	static void act_e7_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//向e7'传递e8
		pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=ps->e8.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e7_.iType=ps->e8.sType;
		pps[pps.size()-2]->getInhAttr()->e7_.iAddr=ps->e8.sAddr;
		pps[pps.size()-2]->getInhAttr()->e7_.ipTrueList=ps->e8.spTrueList;		//使用浅拷贝
		pps[pps.size()-2]->getInhAttr()->e7_.ipFalseList=ps->e8.spFalseList;

		//赋空e8动态内存指针
		ps->e8.spTrueList=0;
		ps->e8.spFalseList=0;	
	}
	static void act_e7_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//e7'的综合属性赋给e7
		pps[pps.size()-2]->getSynAttr()->e7.sValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e7.sType=ps->e7_.sType;
		pps[pps.size()-2]->getSynAttr()->e7.sAddr=ps->e7_.sAddr;
		if(ps->e7_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e7.spTrueList->swap(*(ps->e7_.spTrueList));	//不能使用浅拷贝
		if(ps->e7_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e7.spFalseList->swap(*(ps->e7_.spFalseList));
	}

	static void act_e7_1_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//转换成value
		ControlFlow2Value(context,pi,pi->e7_.iSection);

		//如果左操作数类型是整型
		if(isInteger(pi->e7_.iType.type))
		{
			//将e7'.addr属性传递给S1
			pps[pps.size()-3]->getInhAttr()->e7_.iAddr=pi->e7_.iAddr;

			//将op属性传递给S1
			pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
		}
		else
		{
			//错误报告
			string str="& 左操作数类型必须是整型。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e7_1_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//转换成value
		ControlFlow2Value(context,ps,pi->e7_.iSection);

		if(ps->e8.sType.is_array)
		{
			//错误报告
			string str="& 右操作数不能是数组。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
		//如果右操作数类型是整型
		else if(isInteger(ps->e8.sType.type))
		{
			//继承属性传递给S后面的e7'
			pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e7_.iType.type=t_INT;
			pps[pps.size()-2]->getInhAttr()->e7_.iType.is_array=false;
			pps[pps.size()-2]->getInhAttr()->e7_.iAddr=context.Temp(pps[pps.size()-2]->getInhAttr()->e7_.iType,pi->e7_.iSection);

			//生成操作指令代码
			context.Gen(op_bit_and,pi->e7_.iAddr,ps->e8.sAddr,pps[pps.size()-2]->getInhAttr()->e7_.iAddr,pi->e7_.iSection);
		}
		else
		{
			//错误报告
			string str="& 右操作数类型必须是整型。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e7_1_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(e7')的综合属性赋给e7'
		pps[pps.size()-2]->getSynAttr()->e7_.sValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e7_.sType=ps->e7_.sType;
		pps[pps.size()-2]->getSynAttr()->e7_.sAddr=ps->e7_.sAddr;
		if(ps->e7_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e7_.spTrueList->swap(*(ps->e7_.spTrueList));	//不能使用浅拷贝
		if(ps->e7_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e7_.spFalseList->swap(*(ps->e7_.spFalseList));
	}
	static void act_e7_2_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//A(e7')的继承属性传回给e7'的综合属性
		pps[pps.size()-2]->getSynAttr()->e7_.sValFlag=pi->e7_.iValFlag;	
		pps[pps.size()-2]->getSynAttr()->e7_.sType=pi->e7_.iType;
		pps[pps.size()-2]->getSynAttr()->e7_.sAddr=pi->e7_.iAddr;
		Append(&(pps[pps.size()-2]->getSynAttr()->e7_.spTrueList),&(pi->e7_.ipTrueList));
		Append(&(pps[pps.size()-2]->getSynAttr()->e7_.spFalseList),&(pi->e7_.ipFalseList));

		//赋空指针
		//pi->e7_.ipTrueList=0;	
		//pi->e7_.ipFalseList=0;
	}

	static void act_e8_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//向e8'传递e9
		pps[pps.size()-2]->getInhAttr()->e8_.iValFlag=ps->e9.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e8_.iType=ps->e9.sType;
		pps[pps.size()-2]->getInhAttr()->e8_.iAddr=ps->e9.sAddr;
		pps[pps.size()-2]->getInhAttr()->e8_.ipTrueList=ps->e9.spTrueList;		//使用浅拷贝
		pps[pps.size()-2]->getInhAttr()->e8_.ipFalseList=ps->e9.spFalseList;

		//赋空e9动态内存指针
		ps->e9.spTrueList=0;
		ps->e9.spFalseList=0;	
	}
	static void act_e8_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//e8'的综合属性赋给e8
		pps[pps.size()-2]->getSynAttr()->e8.sValFlag=ps->e8_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e8.sType=ps->e8_.sType;
		pps[pps.size()-2]->getSynAttr()->e8.sAddr=ps->e8_.sAddr;
		if(ps->e8_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e8.spTrueList->swap(*(ps->e8_.spTrueList));	//不能使用浅拷贝
		if(ps->e8_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e8.spFalseList->swap(*(ps->e8_.spFalseList));
	}

	static void act_e8_1_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//转换成value
		ControlFlow2Value(context,pi,pi->e8_.iSection);

		//如果左操作数类型可计算
		if(Computable(pi->e8_.iType))
		{
			//将e8'.addr属性传递给S1
			pps[pps.size()-3]->getInhAttr()->e8_.iAddr=pi->e8_.iAddr;

			//将op属性传递给S1
			pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
		}
		else
		{
			//错误报告
			string str="== 左操作数类型错误。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e8_1_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//转换成value
		ControlFlow2Value(context,ps,pi->e8_.iSection);

		//如果右操作数类型可计算
		if(Computable(ps->e9.sType))
		{
			//继承属性传递给S后面的e8'
			pps[pps.size()-2]->getInhAttr()->e8_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e8_.iType.type=t_BOOL;
			pps[pps.size()-2]->getInhAttr()->e8_.iType.is_array=false;
			pps[pps.size()-2]->getInhAttr()->e8_.iAddr=context.Temp(pps[pps.size()-2]->getInhAttr()->e8_.iType,pi->e8_.iSection);

			//生成操作指令代码
			context.Gen(op_eq,pi->e8_.iAddr,ps->e9.sAddr,pps[pps.size()-2]->getInhAttr()->e8_.iAddr,pi->e8_.iSection);
		}
		else
		{
			//错误报告
			string str="== 右操作数类型错误。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e8_1_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(e8')的综合属性赋给e8'
		pps[pps.size()-2]->getSynAttr()->e8_.sValFlag=ps->e8_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e8_.sType=ps->e8_.sType;
		pps[pps.size()-2]->getSynAttr()->e8_.sAddr=ps->e8_.sAddr;
		if(ps->e8_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e8_.spTrueList->swap(*(ps->e8_.spTrueList));	//不能使用浅拷贝
		if(ps->e8_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e8_.spFalseList->swap(*(ps->e8_.spFalseList));
	}
	static void act_e8_2_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//转换成value
		ControlFlow2Value(context,pi,pi->e8_.iSection);

		//如果左操作数类型可计算
		if(Computable(pi->e8_.iType))
		{
			//将e8'.addr属性传递给S1
			pps[pps.size()-3]->getInhAttr()->e8_.iAddr=pi->e8_.iAddr;

			//将op属性传递给S1
			pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
		}
		else
		{
			//错误报告
			string str="!= 左操作数类型错误。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e8_2_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//转换成value
		ControlFlow2Value(context,ps,pi->e8_.iSection);

		//如果右操作数类型可计算
		if(Computable(ps->e9.sType))
		{
			//继承属性传递给S后面的e8'
			pps[pps.size()-2]->getInhAttr()->e8_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e8_.iType.type=t_BOOL;
			pps[pps.size()-2]->getInhAttr()->e8_.iType.is_array=false;
			pps[pps.size()-2]->getInhAttr()->e8_.iAddr=context.Temp(pps[pps.size()-2]->getInhAttr()->e8_.iType,pi->e8_.iSection);

			//生成操作指令代码
			context.Gen(op_ne,pi->e8_.iAddr,ps->e9.sAddr,pps[pps.size()-2]->getInhAttr()->e8_.iAddr,pi->e8_.iSection);
		}
		else
		{
			//错误报告
			string str="!= 右操作数类型错误。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e8_2_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(e8')的综合属性赋给e8'
		pps[pps.size()-2]->getSynAttr()->e8_.sValFlag=ps->e8_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e8_.sType=ps->e8_.sType;
		pps[pps.size()-2]->getSynAttr()->e8_.sAddr=ps->e8_.sAddr;
		if(ps->e8_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e8_.spTrueList->swap(*(ps->e8_.spTrueList));	//不能使用浅拷贝
		if(ps->e8_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e8_.spFalseList->swap(*(ps->e8_.spFalseList));
	}
	static void act_e8_3_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//A(e8')的继承属性传回给e8'的综合属性
		pps[pps.size()-2]->getSynAttr()->e8_.sValFlag=pi->e8_.iValFlag;	
		pps[pps.size()-2]->getSynAttr()->e8_.sType=pi->e8_.iType;
		pps[pps.size()-2]->getSynAttr()->e8_.sAddr=pi->e8_.iAddr;
		Append(&(pps[pps.size()-2]->getSynAttr()->e8_.spTrueList),&(pi->e8_.ipTrueList));
		Append(&(pps[pps.size()-2]->getSynAttr()->e8_.spFalseList),&(pi->e8_.ipFalseList));

		//赋空指针
		//pi->e8_.ipTrueList=0;
		//pi->e8_.ipFalseList=0;
	}

	static void act_e9_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//向e9'传递e10
		pps[pps.size()-2]->getInhAttr()->e9_.iValFlag=ps->e10.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e9_.iType=ps->e10.sType;
		pps[pps.size()-2]->getInhAttr()->e9_.iAddr=ps->e10.sAddr;
		pps[pps.size()-2]->getInhAttr()->e9_.ipTrueList=ps->e10.spTrueList;		//使用浅拷贝
		pps[pps.size()-2]->getInhAttr()->e9_.ipFalseList=ps->e10.spFalseList;

		//赋空e10动态内存指针
		ps->e10.spTrueList=0;
		ps->e10.spFalseList=0;	
	}
	static void act_e9_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//e9'的综合属性赋给e9
		pps[pps.size()-2]->getSynAttr()->e9.sValFlag=ps->e9_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e9.sType=ps->e9_.sType;
		pps[pps.size()-2]->getSynAttr()->e9.sAddr=ps->e9_.sAddr;
		if(ps->e9_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e9.spTrueList->swap(*(ps->e9_.spTrueList));	//不能使用浅拷贝
		if(ps->e9_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e9.spFalseList->swap(*(ps->e9_.spFalseList));
	}

	static void act_e9_1_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//转换成value
		ControlFlow2Value(context,pi,pi->e9_.iSection);

		//如果左操作数类型可计算
		if(Computable(pi->e9_.iType))
		{
			//将e9'.addr属性传递给S1
			pps[pps.size()-3]->getInhAttr()->e9_.iAddr=pi->e9_.iAddr;

			//将op属性传递给S1
			pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
		}
		else
		{
			//错误报告
			string str="< 左操作数类型错误。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e9_1_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//转换成value
		ControlFlow2Value(context,ps,pi->e9_.iSection);

		//如果右操作数类型可计算
		if(Computable(ps->e10.sType))
		{
			//继承属性传递给S后面的e9'
			pps[pps.size()-2]->getInhAttr()->e9_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e9_.iType.type=t_BOOL;
			pps[pps.size()-2]->getInhAttr()->e9_.iType.is_array=false;
			pps[pps.size()-2]->getInhAttr()->e9_.iAddr=context.Temp(pps[pps.size()-2]->getInhAttr()->e9_.iType,pi->e9_.iSection);

			//生成操作指令代码
			context.Gen(op_less,pi->e9_.iAddr,ps->e10.sAddr,pps[pps.size()-2]->getInhAttr()->e9_.iAddr,pi->e9_.iSection);
		}
		else
		{
			//错误报告
			string str="< 右操作数类型错误。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e9_1_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(e9')的综合属性赋给e9'
		pps[pps.size()-2]->getSynAttr()->e9_.sValFlag=ps->e9_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e9_.sType=ps->e9_.sType;
		pps[pps.size()-2]->getSynAttr()->e9_.sAddr=ps->e9_.sAddr;
		if(ps->e9_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e9_.spTrueList->swap(*(ps->e9_.spTrueList));	//不能使用浅拷贝
		if(ps->e9_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e9_.spFalseList->swap(*(ps->e9_.spFalseList));
	}
	static void act_e9_2_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//转换成value
		ControlFlow2Value(context,pi,pi->e9_.iSection);

		//如果左操作数类型可计算
		if(Computable(pi->e9_.iType))
		{
			//将e9'.addr属性传递给S1
			pps[pps.size()-3]->getInhAttr()->e9_.iAddr=pi->e9_.iAddr;

			//将op属性传递给S1
			pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
		}
		else
		{
			//错误报告
			string str="<= 左操作数类型错误。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e9_2_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//转换成value
		ControlFlow2Value(context,ps,pi->e9_.iSection);

		//如果右操作数类型可计算
		if(Computable(ps->e10.sType))
		{
			//继承属性传递给S后面的e9'
			pps[pps.size()-2]->getInhAttr()->e9_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e9_.iType.type=t_BOOL;
			pps[pps.size()-2]->getInhAttr()->e9_.iType.is_array=false;
			pps[pps.size()-2]->getInhAttr()->e9_.iAddr=context.Temp(pps[pps.size()-2]->getInhAttr()->e9_.iType,pi->e9_.iSection);

			//生成操作指令代码
			context.Gen(op_le,pi->e9_.iAddr,ps->e10.sAddr,pps[pps.size()-2]->getInhAttr()->e9_.iAddr,pi->e9_.iSection);
		}
		else
		{
			//错误报告
			string str="<= 右操作数类型错误。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e9_2_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(e9')的综合属性赋给e9'
		pps[pps.size()-2]->getSynAttr()->e9_.sValFlag=ps->e9_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e9_.sType=ps->e9_.sType;
		pps[pps.size()-2]->getSynAttr()->e9_.sAddr=ps->e9_.sAddr;
		if(ps->e9_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e9_.spTrueList->swap(*(ps->e9_.spTrueList));	//不能使用浅拷贝
		if(ps->e9_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e9_.spFalseList->swap(*(ps->e9_.spFalseList));
	}
	static void act_e9_3_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//转换成value
		ControlFlow2Value(context,pi,pi->e9_.iSection);

		//如果左操作数类型可计算
		if(Computable(pi->e9_.iType))
		{
			//将e9'.addr属性传递给S1
			pps[pps.size()-3]->getInhAttr()->e9_.iAddr=pi->e9_.iAddr;

			//将op属性传递给S1
			pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
		}
		else
		{
			//错误报告
			string str="> 左操作数类型错误。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e9_3_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//转换成value
		ControlFlow2Value(context,ps,pi->e9_.iSection);

		//如果右操作数类型可计算
		if(Computable(ps->e10.sType))
		{
			//继承属性传递给S后面的e9'
			pps[pps.size()-2]->getInhAttr()->e9_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e9_.iType.type=t_BOOL;
			pps[pps.size()-2]->getInhAttr()->e9_.iType.is_array=false;
			pps[pps.size()-2]->getInhAttr()->e9_.iAddr=context.Temp(pps[pps.size()-2]->getInhAttr()->e9_.iType,pi->e9_.iSection);

			//生成操作指令代码
			context.Gen(op_greater,pi->e9_.iAddr,ps->e10.sAddr,pps[pps.size()-2]->getInhAttr()->e9_.iAddr,pi->e9_.iSection);
		}
		else
		{
			//错误报告
			string str="> 右操作数类型错误。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e9_3_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(e9')的综合属性赋给e9'
		pps[pps.size()-2]->getSynAttr()->e9_.sValFlag=ps->e9_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e9_.sType=ps->e9_.sType;
		pps[pps.size()-2]->getSynAttr()->e9_.sAddr=ps->e9_.sAddr;
		if(ps->e9_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e9_.spTrueList->swap(*(ps->e9_.spTrueList));	//不能使用浅拷贝
		if(ps->e9_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e9_.spFalseList->swap(*(ps->e9_.spFalseList));
	}
	static void act_e9_4_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//转换成value
		ControlFlow2Value(context,pi,pi->e9_.iSection);

		//如果左操作数类型可计算
		if(Computable(pi->e9_.iType))
		{
			//将e9'.addr属性传递给S1
			pps[pps.size()-3]->getInhAttr()->e9_.iAddr=pi->e9_.iAddr;

			//将op属性传递给S1
			pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
		}
		else
		{
			//错误报告
			string str=">= 左操作数类型错误。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e9_4_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//转换成value
		ControlFlow2Value(context,ps,pi->e9_.iSection);

		//如果右操作数类型可计算
		if(Computable(ps->e10.sType))
		{
			//继承属性传递给S后面的e9'
			pps[pps.size()-2]->getInhAttr()->e9_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e9_.iType.type=t_BOOL;
			pps[pps.size()-2]->getInhAttr()->e9_.iType.is_array=false;
			pps[pps.size()-2]->getInhAttr()->e9_.iAddr=context.Temp(pps[pps.size()-2]->getInhAttr()->e9_.iType,pi->e9_.iSection);

			//生成操作指令代码
			context.Gen(op_ge,pi->e9_.iAddr,ps->e10.sAddr,pps[pps.size()-2]->getInhAttr()->e9_.iAddr,pi->e9_.iSection);
		}
		else
		{
			//错误报告
			string str=">= 右操作数类型错误。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e9_4_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(e9')的综合属性赋给e9'
		pps[pps.size()-2]->getSynAttr()->e9_.sValFlag=ps->e9_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e9_.sType=ps->e9_.sType;
		pps[pps.size()-2]->getSynAttr()->e9_.sAddr=ps->e9_.sAddr;
		if(ps->e9_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e9_.spTrueList->swap(*(ps->e9_.spTrueList));	//不能使用浅拷贝
		if(ps->e9_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e9_.spFalseList->swap(*(ps->e9_.spFalseList));
	}
	static void act_e9_5_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//A(e9')的继承属性传回给e9'的综合属性
		pps[pps.size()-2]->getSynAttr()->e9_.sValFlag=pi->e9_.iValFlag;	
		pps[pps.size()-2]->getSynAttr()->e9_.sType=pi->e9_.iType;
		pps[pps.size()-2]->getSynAttr()->e9_.sAddr=pi->e9_.iAddr;
		Append(&(pps[pps.size()-2]->getSynAttr()->e9_.spTrueList),&(pi->e9_.ipTrueList));
		Append(&(pps[pps.size()-2]->getSynAttr()->e9_.spFalseList),&(pi->e9_.ipFalseList));

		//赋空指针
		//pi->e9_.ipTrueList=0;
		//pi->e9_.ipFalseList=0;
	}

	static void act_e10_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//向e10'传递e11
		pps[pps.size()-2]->getInhAttr()->e10_.iValFlag=ps->e11.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e10_.iType=ps->e11.sType;
		pps[pps.size()-2]->getInhAttr()->e10_.iAddr=ps->e11.sAddr;
		pps[pps.size()-2]->getInhAttr()->e10_.ipTrueList=ps->e11.spTrueList;		//使用浅拷贝
		pps[pps.size()-2]->getInhAttr()->e10_.ipFalseList=ps->e11.spFalseList;

		//赋空e11动态内存指针
		ps->e11.spTrueList=0;
		ps->e11.spFalseList=0;	
	}
	static void act_e10_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//e10'的综合属性赋给e10
		pps[pps.size()-2]->getSynAttr()->e10.sValFlag=ps->e10_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e10.sType=ps->e10_.sType;
		pps[pps.size()-2]->getSynAttr()->e10.sAddr=ps->e10_.sAddr;
		if(ps->e10_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e10.spTrueList->swap(*(ps->e10_.spTrueList));	//不能使用浅拷贝
		if(ps->e10_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e10.spFalseList->swap(*(ps->e10_.spFalseList));
	}

	static void act_e10_1_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//转换成value
		ControlFlow2Value(context,pi,pi->e10_.iSection);

		//如果左操作数类型是整型
		if(isInteger(pi->e10_.iType.type))
		{
			//将e10'.addr属性传递给S1
			pps[pps.size()-3]->getInhAttr()->e10_.iAddr=pi->e10_.iAddr;

			//将op属性传递给S1
			pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
		}
		else
		{
			//错误报告
			string str="<< 左操作数类型必须是整型。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e10_1_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//转换成value
		ControlFlow2Value(context,ps,pi->e10_.iSection);

		if(ps->e11.sType.is_array)
		{
			//错误报告
			string str="<< 右操作数不能是数组。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
		//如果右操作数类型是整型
		else if(isInteger(ps->e11.sType.type))
		{
			//继承属性传递给S后面的e10'
			pps[pps.size()-2]->getInhAttr()->e10_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e10_.iType.type=t_INT;
			pps[pps.size()-2]->getInhAttr()->e10_.iType.is_array=false;
			pps[pps.size()-2]->getInhAttr()->e10_.iAddr=context.Temp(pps[pps.size()-2]->getInhAttr()->e10_.iType,pi->e10_.iSection);

			//生成操作指令代码
			context.Gen(op_lsht,pi->e10_.iAddr,ps->e11.sAddr,pps[pps.size()-2]->getInhAttr()->e10_.iAddr,pi->e10_.iSection);
		}
		else
		{
			//错误报告
			string str="<< 右操作数类型必须是整型。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e10_1_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(e10')的综合属性赋给e10'
		pps[pps.size()-2]->getSynAttr()->e10_.sValFlag=ps->e10_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e10_.sType=ps->e10_.sType;
		pps[pps.size()-2]->getSynAttr()->e10_.sAddr=ps->e10_.sAddr;
		if(ps->e10_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e10_.spTrueList->swap(*(ps->e10_.spTrueList));	//不能使用浅拷贝
		if(ps->e10_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e10_.spFalseList->swap(*(ps->e10_.spFalseList));
	}
	static void act_e10_2_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//转换成value
		ControlFlow2Value(context,pi,pi->e10_.iSection);

		//如果左操作数类型是整型
		if(isInteger(pi->e10_.iType.type))
		{
			//将e10'.addr属性传递给S1
			pps[pps.size()-3]->getInhAttr()->e10_.iAddr=pi->e10_.iAddr;

			//将op属性传递给S1
			pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
		}
		else
		{
			//错误报告
			string str=">> 左操作数类型必须是整型。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e10_2_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//转换成value
		ControlFlow2Value(context,ps,pi->e10_.iSection);

		if(ps->e11.sType.is_array)
		{
			//错误报告
			string str=">> 右操作数不能是数组。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
		//如果右操作数类型是整型
		else if(isInteger(ps->e11.sType.type))
		{
			//继承属性传递给S后面的e10'
			pps[pps.size()-2]->getInhAttr()->e10_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e10_.iType.type=t_INT;
			pps[pps.size()-2]->getInhAttr()->e10_.iType.is_array=false;
			pps[pps.size()-2]->getInhAttr()->e10_.iAddr=context.Temp(pps[pps.size()-2]->getInhAttr()->e10_.iType,pi->e10_.iSection);

			//生成操作指令代码
			context.Gen(op_rsht,pi->e10_.iAddr,ps->e11.sAddr,pps[pps.size()-2]->getInhAttr()->e10_.iAddr,pi->e10_.iSection);
		}
		else
		{
			//错误报告
			string str=">> 右操作数类型必须是整型。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e10_2_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(e10')的综合属性赋给e10'
		pps[pps.size()-2]->getSynAttr()->e10_.sValFlag=ps->e10_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e10_.sType=ps->e10_.sType;
		pps[pps.size()-2]->getSynAttr()->e10_.sAddr=ps->e10_.sAddr;
		if(ps->e10_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e10_.spTrueList->swap(*(ps->e10_.spTrueList));	//不能使用浅拷贝
		if(ps->e10_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e10_.spFalseList->swap(*(ps->e10_.spFalseList));
	}
	static void act_e10_3_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//A(e10')的继承属性传回给e10'的综合属性
		pps[pps.size()-2]->getSynAttr()->e10_.sValFlag=pi->e10_.iValFlag;	
		pps[pps.size()-2]->getSynAttr()->e10_.sType=pi->e10_.iType;
		pps[pps.size()-2]->getSynAttr()->e10_.sAddr=pi->e10_.iAddr;
		Append(&(pps[pps.size()-2]->getSynAttr()->e10_.spTrueList),&(pi->e10_.ipTrueList));
		Append(&(pps[pps.size()-2]->getSynAttr()->e10_.spFalseList),&(pi->e10_.ipFalseList));

		//赋空指针
		//pi->e10_.ipTrueList=0;
		//pi->e10_.ipFalseList=0;
	}

	static void act_e11_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//向e11'传递e12
		pps[pps.size()-2]->getInhAttr()->e11_.iValFlag=ps->e12.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e11_.iType=ps->e12.sType;
		pps[pps.size()-2]->getInhAttr()->e11_.iAddr=ps->e12.sAddr;
		pps[pps.size()-2]->getInhAttr()->e11_.ipTrueList=ps->e12.spTrueList;		//使用浅拷贝
		pps[pps.size()-2]->getInhAttr()->e11_.ipFalseList=ps->e12.spFalseList;

		//赋空e12动态内存指针
		ps->e12.spTrueList=0;
		ps->e12.spFalseList=0;
	}
	static void act_e11_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//e11'的综合属性赋给e11
		pps[pps.size()-2]->getSynAttr()->e11.sValFlag=ps->e11_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e11.sType=ps->e11_.sType;
		pps[pps.size()-2]->getSynAttr()->e11.sAddr=ps->e11_.sAddr;
		if(ps->e11_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e11.spTrueList->swap(*(ps->e11_.spTrueList));	//不能使用浅拷贝
		if(ps->e11_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e11.spFalseList->swap(*(ps->e11_.spFalseList));
	}

	static void act_e11_1_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//转换成value
		ControlFlow2Value(context,pi,pi->e11_.iSection);

		//如果左操作数类型可计算
		if(Computable(pi->e11_.iType))
		{
			//将e11'.addr属性传递给S1
			pps[pps.size()-3]->getInhAttr()->e11_.iAddr=pi->e11_.iAddr;

			//将e11'.type属性传递给S1
			pps[pps.size()-3]->getInhAttr()->e11_.iType=pi->e11_.iType;

			//将op属性传递给S1
			pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
		}
		else
		{
			//错误报告
			string str="+ 左操作数类型错误。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e11_1_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//转换成value
		ControlFlow2Value(context,ps,pi->e11_.iSection);

		//如果右操作数类型可计算
		if(Computable(ps->e12.sType))
		{
			//继承属性传递给S后面的e11'
			pps[pps.size()-2]->getInhAttr()->e11_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e11_.iType.type=Advance(pi->e11_.iType.type,ps->e12.sType.type);
			pps[pps.size()-2]->getInhAttr()->e11_.iType.is_array=false;
			pps[pps.size()-2]->getInhAttr()->e11_.iAddr=context.Temp(pps[pps.size()-2]->getInhAttr()->e11_.iType,pi->e11_.iSection);

			//生成操作指令代码
			context.Gen(op_add,pi->e11_.iAddr,ps->e12.sAddr,pps[pps.size()-2]->getInhAttr()->e11_.iAddr,pi->e11_.iSection);
		}
		else
		{
			//错误报告
			string str="+ 右操作数类型错误。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e11_1_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(e11')的综合属性赋给e11'
		pps[pps.size()-2]->getSynAttr()->e11_.sValFlag=ps->e11_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e11_.sType=ps->e11_.sType;
		pps[pps.size()-2]->getSynAttr()->e11_.sAddr=ps->e11_.sAddr;
		if(ps->e11_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e11_.spTrueList->swap(*(ps->e11_.spTrueList));	//不能使用浅拷贝
		if(ps->e11_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e11_.spFalseList->swap(*(ps->e11_.spFalseList));
	}
	static void act_e11_2_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//转换成value
		ControlFlow2Value(context,pi,pi->e11_.iSection);

		//如果左操作数类型可计算
		if(Computable(pi->e11_.iType))
		{
			//将e11'.addr属性传递给S1
			pps[pps.size()-3]->getInhAttr()->e11_.iAddr=pi->e11_.iAddr;

			//将e11'.type属性传递给S1
			pps[pps.size()-3]->getInhAttr()->e11_.iType=pi->e11_.iType;

			//将op属性传递给S1
			pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
		}
		else
		{
			//错误报告
			string str="- 左操作数类型错误。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e11_2_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//转换成value
		ControlFlow2Value(context,ps,pi->e11_.iSection);

		//如果右操作数类型可计算
		if(Computable(ps->e12.sType))
		{
			//继承属性传递给S后面的e11'
			pps[pps.size()-2]->getInhAttr()->e11_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e11_.iType.type=Advance(pi->e11_.iType.type,ps->e12.sType.type);
			pps[pps.size()-2]->getInhAttr()->e11_.iType.is_array=false;
			pps[pps.size()-2]->getInhAttr()->e11_.iAddr=context.Temp(pps[pps.size()-2]->getInhAttr()->e11_.iType,pi->e11_.iSection);

			//生成操作指令代码
			context.Gen(op_sub,pi->e11_.iAddr,ps->e12.sAddr,pps[pps.size()-2]->getInhAttr()->e11_.iAddr,pi->e11_.iSection);
		}
		else
		{
			//错误报告
			string str="- 右操作数类型错误。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e11_2_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(e11')的综合属性赋给e11'
		pps[pps.size()-2]->getSynAttr()->e11_.sValFlag=ps->e11_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e11_.sType=ps->e11_.sType;
		pps[pps.size()-2]->getSynAttr()->e11_.sAddr=ps->e11_.sAddr;
		if(ps->e11_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e11_.spTrueList->swap(*(ps->e11_.spTrueList));	//不能使用浅拷贝
		if(ps->e11_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e11_.spFalseList->swap(*(ps->e11_.spFalseList));
	}
	static void act_e11_3_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//A(e11')的继承属性传回给e11'的综合属性
		pps[pps.size()-2]->getSynAttr()->e11_.sValFlag=pi->e11_.iValFlag;	
		pps[pps.size()-2]->getSynAttr()->e11_.sType=pi->e11_.iType;
		pps[pps.size()-2]->getSynAttr()->e11_.sAddr=pi->e11_.iAddr;
		Append(&(pps[pps.size()-2]->getSynAttr()->e11_.spTrueList),&(pi->e11_.ipTrueList));
		Append(&(pps[pps.size()-2]->getSynAttr()->e11_.spFalseList),&(pi->e11_.ipFalseList));

		//赋空指针
		//pi->e11_.ipTrueList=0;
		//pi->e11_.ipFalseList=0;
	}

	static void act_e12_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//向e12'传递e13
		pps[pps.size()-2]->getInhAttr()->e12_.iValFlag=ps->e13.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e12_.iType=ps->e13.sType;
		pps[pps.size()-2]->getInhAttr()->e12_.iAddr=ps->e13.sAddr;
		pps[pps.size()-2]->getInhAttr()->e12_.ipTrueList=ps->e13.spTrueList;		//使用浅拷贝
		pps[pps.size()-2]->getInhAttr()->e12_.ipFalseList=ps->e13.spFalseList;

		//赋空e13动态内存指针
		ps->e13.spTrueList=0;
		ps->e13.spFalseList=0;
	}
	static void act_e12_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//e12'的综合属性赋给e12
		pps[pps.size()-2]->getSynAttr()->e12.sValFlag=ps->e12_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e12.sType=ps->e12_.sType;
		pps[pps.size()-2]->getSynAttr()->e12.sAddr=ps->e12_.sAddr;
		if(ps->e12_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e12.spTrueList->swap(*(ps->e12_.spTrueList));	//不能使用浅拷贝
		if(ps->e12_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e12.spFalseList->swap(*(ps->e12_.spFalseList));
	}

	static void act_e12_1_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//转换成value
		ControlFlow2Value(context,pi,pi->e12_.iSection);

		//如果左操作数类型可计算
		if(Computable(pi->e12_.iType))
		{
			//将e12'.addr属性传递给S1
			pps[pps.size()-3]->getInhAttr()->e12_.iAddr=pi->e12_.iAddr;

			//将e12'.type属性传递给S1
			pps[pps.size()-3]->getInhAttr()->e12_.iType=pi->e12_.iType;

			//将op属性传递给S1
			pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
		}
		else
		{
			//错误报告
			string str="* 左操作数类型错误。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e12_1_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//转换成value
		ControlFlow2Value(context,ps,pi->e12_.iSection);

		//如果右操作数类型可计算
		if(Computable(ps->e13.sType))
		{
			//继承属性传递给S后面的e12'
			pps[pps.size()-2]->getInhAttr()->e12_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e12_.iType.type=Advance(pi->e12_.iType.type,ps->e13.sType.type);
			pps[pps.size()-2]->getInhAttr()->e12_.iType.is_array=false;
			pps[pps.size()-2]->getInhAttr()->e12_.iAddr=context.Temp(pps[pps.size()-2]->getInhAttr()->e12_.iType,pi->e12_.iSection);

			//生成操作指令代码
			context.Gen(op_mul,pi->e12_.iAddr,ps->e13.sAddr,pps[pps.size()-2]->getInhAttr()->e12_.iAddr,pi->e12_.iSection);
		}
		else
		{
			//错误报告
			string str="* 右操作数类型错误。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e12_1_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(e12')的综合属性赋给e12'
		pps[pps.size()-2]->getSynAttr()->e12_.sValFlag=ps->e12_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e12_.sType=ps->e12_.sType;
		pps[pps.size()-2]->getSynAttr()->e12_.sAddr=ps->e12_.sAddr;
		if(ps->e12_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e12_.spTrueList->swap(*(ps->e12_.spTrueList));	//不能使用浅拷贝
		if(ps->e12_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e12_.spFalseList->swap(*(ps->e12_.spFalseList));
	}
	static void act_e12_2_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//转换成value
		ControlFlow2Value(context,pi,pi->e12_.iSection);

		//如果左操作数类型可计算
		if(Computable(pi->e12_.iType))
		{
			//将e12'.addr属性传递给S1
			pps[pps.size()-3]->getInhAttr()->e12_.iAddr=pi->e12_.iAddr;

			//将e12'.type属性传递给S1
			pps[pps.size()-3]->getInhAttr()->e12_.iType=pi->e12_.iType;

			//将op属性传递给S1
			pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
		}
		else
		{
			//错误报告
			string str="/ 左操作数类型错误。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e12_2_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//转换成value
		ControlFlow2Value(context,ps,pi->e12_.iSection);

		//如果右操作数类型可计算
		if(Computable(ps->e13.sType))
		{
			//继承属性传递给S后面的e12'
			pps[pps.size()-2]->getInhAttr()->e12_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e12_.iType.type=Advance(pi->e12_.iType.type,ps->e13.sType.type);
			pps[pps.size()-2]->getInhAttr()->e12_.iType.is_array=false;
			pps[pps.size()-2]->getInhAttr()->e12_.iAddr=context.Temp(pps[pps.size()-2]->getInhAttr()->e12_.iType,pi->e12_.iSection);

			//生成操作指令代码
			context.Gen(op_div,pi->e12_.iAddr,ps->e13.sAddr,pps[pps.size()-2]->getInhAttr()->e12_.iAddr,pi->e12_.iSection);
		}
		else
		{
			//错误报告
			string str="/ 右操作数类型错误。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e12_2_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(e12')的综合属性赋给e12'
		pps[pps.size()-2]->getSynAttr()->e12_.sValFlag=ps->e12_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e12_.sType=ps->e12_.sType;
		pps[pps.size()-2]->getSynAttr()->e12_.sAddr=ps->e12_.sAddr;
		if(ps->e12_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e12_.spTrueList->swap(*(ps->e12_.spTrueList));	//不能使用浅拷贝
		if(ps->e12_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e12_.spFalseList->swap(*(ps->e12_.spFalseList));
	}
	static void act_e12_3_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//转换成value
		ControlFlow2Value(context,pi,pi->e12_.iSection);

		//如果左操作数类型是整型
		if(isInteger(pi->e12_.iType.type))
		{
			//将e12'.addr属性传递给S1
			pps[pps.size()-3]->getInhAttr()->e12_.iAddr=pi->e12_.iAddr;

			//将e12'.type属性传递给S1
			pps[pps.size()-3]->getInhAttr()->e12_.iType=pi->e12_.iType;

			//将op属性传递给S1
			pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
		}
		else
		{
			//错误报告
			string str="% 左操作数类型必须是整型。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e12_3_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//转换成value
		ControlFlow2Value(context,ps,pi->e12_.iSection);

		//如果右操作数是数组
		if(ps->e13.sType.is_array)
		{
			//错误报告
			string str="% 右操作数不能是数组。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
		//如果右操作数类型是整型
		else if(isInteger(ps->e13.sType.type))
		{
			//继承属性传递给S后面的e12'
			pps[pps.size()-2]->getInhAttr()->e12_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e12_.iType.type=Advance(pi->e12_.iType.type,ps->e13.sType.type);
			pps[pps.size()-2]->getInhAttr()->e12_.iType.is_array=false;
			pps[pps.size()-2]->getInhAttr()->e12_.iAddr=context.Temp(pps[pps.size()-2]->getInhAttr()->e12_.iType,pi->e12_.iSection);

			//生成操作指令代码
			context.Gen(op_mod,pi->e12_.iAddr,ps->e13.sAddr,pps[pps.size()-2]->getInhAttr()->e12_.iAddr,pi->e12_.iSection);
		}
		else
		{
			//错误报告
			string str="% 右操作数类型必须是整型。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e12_3_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(e12')的综合属性赋给e12'
		pps[pps.size()-2]->getSynAttr()->e12_.sValFlag=ps->e12_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e12_.sType=ps->e12_.sType;
		pps[pps.size()-2]->getSynAttr()->e12_.sAddr=ps->e12_.sAddr;
		if(ps->e12_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e12_.spTrueList->swap(*(ps->e12_.spTrueList));	//不能使用浅拷贝
		if(ps->e12_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e12_.spFalseList->swap(*(ps->e12_.spFalseList));
	}
	static void act_e12_4_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//A(e12')的继承属性传回给e12'的综合属性
		pps[pps.size()-2]->getSynAttr()->e12_.sValFlag=pi->e12_.iValFlag;	
		pps[pps.size()-2]->getSynAttr()->e12_.sType=pi->e12_.iType;
		pps[pps.size()-2]->getSynAttr()->e12_.sAddr=pi->e12_.iAddr;
		Append(&(pps[pps.size()-2]->getSynAttr()->e12_.spTrueList),&(pi->e12_.ipTrueList));
		Append(&(pps[pps.size()-2]->getSynAttr()->e12_.spFalseList),&(pi->e12_.ipFalseList));

		//赋空指针
		//pi->e12_.ipTrueList=0;
		//pi->e12_.ipFalseList=0;
	}

	static void act_e13_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//将op属性传递给S
		pps[pps.size()-3]->getTempVar()->op_line.tLine=pps.back()->getTempVar()->op_line.tLine;
	}
	static void act_e13A_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//转换成value
		ControlFlow2Value(context,ps,pi->e13.iSection);

		if(ps->e13.sType.is_array)
		{
			//错误报告
			string str="~ 操作数不能是数组。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
		//如果操作数类型是整型
		else if(isInteger(ps->e13.sType.type))
		{
			//计算S后面的e13属性
			pps[pps.size()-2]->getSynAttr()->e13.sValFlag=true;
			pps[pps.size()-2]->getSynAttr()->e13.sType.type=t_INT;
			pps[pps.size()-2]->getSynAttr()->e13.sType.is_array=false;
			pps[pps.size()-2]->getSynAttr()->e13.sAddr=context.Temp(pps[pps.size()-2]->getSynAttr()->e13.sType,pi->e13.iSection);

			//生成操作指令代码
			context.Gen(op_bit_not,pps[pps.size()-2]->getSynAttr()->e13.sAddr,ps->e13.sAddr,pi->e13.iSection);
		}
		else
		{
			//错误报告
			string str="~ 操作数类型必须是整型。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e13B_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//转换成control flow
		bool yes=Value2ControlFlow(context,ps,pi->e13.iSection);

		//转换成功
		if(yes)
		{
			//计算S后面的e13属性
			pps[pps.size()-2]->getSynAttr()->e13.sValFlag=false;
			if(ps->e13.spFalseList)
				pps[pps.size()-2]->getSynAttr()->e13.spTrueList->swap(*(ps->e13.spFalseList));	//不能使用浅拷贝
			if(ps->e13.spTrueList)
				pps[pps.size()-2]->getSynAttr()->e13.spFalseList->swap(*(ps->e13.spTrueList));
		}
		else
		{
			//错误报告
			string str="! 操作数类型错误。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e13C_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//转换成value
		ControlFlow2Value(context,ps,pi->e13.iSection);

		//如果右操作数类型可计算
		if(Computable(ps->e13.sType))
		{
			//计算S后面的e13属性
			pps[pps.size()-2]->getSynAttr()->e13.sValFlag=true;
			pps[pps.size()-2]->getSynAttr()->e13.sType.type=Advance(ps->e13.sType.type);
			pps[pps.size()-2]->getSynAttr()->e13.sType.is_array=false;
			pps[pps.size()-2]->getSynAttr()->e13.sAddr=context.Temp(pps[pps.size()-2]->getSynAttr()->e13.sType,pi->e13.iSection);

			//生成操作指令代码
			context.Gen(op_minus,pps[pps.size()-2]->getSynAttr()->e13.sAddr,ps->e13.sAddr,pi->e13.iSection);
		}
		else
		{
			//错误报告
			string str="单目- 操作数类型错误。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e13D_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//转换成value
		ControlFlow2Value(context,ps,pi->e13.iSection);

		//如果右操作数类型可计算
		if(Computable(ps->e13.sType))
		{
			//计算S后面的e13属性
			pps[pps.size()-2]->getSynAttr()->e13.sValFlag=true;
			pps[pps.size()-2]->getSynAttr()->e13.sType.type=Advance(ps->e13.sType.type);
			pps[pps.size()-2]->getSynAttr()->e13.sType.is_array=false;
			pps[pps.size()-2]->getSynAttr()->e13.sAddr=context.Temp(pps[pps.size()-2]->getSynAttr()->e13.sType,pi->e13.iSection);

			//生成操作指令代码
			context.Gen(op_plus,pps[pps.size()-2]->getSynAttr()->e13.sAddr,ps->e13.sAddr,pi->e13.iSection);
		}
		else
		{
			//错误报告
			string str="单目+ 操作数类型错误。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e13E_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{	
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的e13属性
		pps[pps.size()-2]->getSynAttr()->e13.sValFlag=ps->e14.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e13.sType=ps->e14.sType;
		pps[pps.size()-2]->getSynAttr()->e13.sAddr=ps->e14.sAddr;
		if(ps->e14.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e13.spTrueList->swap(*(ps->e14.spTrueList));	//不能使用浅拷贝
		if(ps->e14.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e13.spFalseList->swap(*(ps->e14.spFalseList));
	}

	static void act_e14A_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//计算S后面的e14属性
		pps[pps.size()-2]->getSynAttr()->e14.sValFlag=true;
		pps[pps.size()-2]->getSynAttr()->e14.sType.type=t_BOOL;
		pps[pps.size()-2]->getSynAttr()->e14.sType.is_array=false;
		pps[pps.size()-2]->getSynAttr()->e14.sAddr=context.getAddress(true);
	}
	static void act_e14B_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//计算S后面的e14属性
		pps[pps.size()-2]->getSynAttr()->e14.sValFlag=true;
		pps[pps.size()-2]->getSynAttr()->e14.sType.type=t_BOOL;
		pps[pps.size()-2]->getSynAttr()->e14.sType.is_array=false;
		pps[pps.size()-2]->getSynAttr()->e14.sAddr=context.getAddress(false);
	}
	static void act_e14C_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//计算S后面的e14属性
		pps[pps.size()-2]->getSynAttr()->e14.sValFlag=true;
		pps[pps.size()-2]->getSynAttr()->e14.sType.type=t_CHAR;
		pps[pps.size()-2]->getSynAttr()->e14.sType.is_array=false;
		pps[pps.size()-2]->getSynAttr()->e14.sAddr=context.getAddress(unsigned char(pps.back()->getTempVar()->e14_const.tValue));
	}
	static void act_e14D_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//计算S后面的e14属性
		pps[pps.size()-2]->getSynAttr()->e14.sValFlag=true;
		pps[pps.size()-2]->getSynAttr()->e14.sType.type=t_INT;
		pps[pps.size()-2]->getSynAttr()->e14.sType.is_array=false;
		pps[pps.size()-2]->getSynAttr()->e14.sAddr=context.getAddress(pps.back()->getTempVar()->e14_const.tValue);
	}
	static void act_e14E_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//计算S后面的e14属性
		pps[pps.size()-2]->getSynAttr()->e14.sValFlag=true;
		pps[pps.size()-2]->getSynAttr()->e14.sType.type=t_DOUBLE;
		pps[pps.size()-2]->getSynAttr()->e14.sType.is_array=false;
		pps[pps.size()-2]->getSynAttr()->e14.sAddr=context.getAddress(pps.back()->getTempVar()->e14_real.tValue);
	}
	static void act_e14FG_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的e14属性
		pps[pps.size()-2]->getSynAttr()->e14.sValFlag=true;
		pps[pps.size()-2]->getSynAttr()->e14.sType=ps->loc.sType;
		pps[pps.size()-2]->getSynAttr()->e14.sAddr=ps->loc.sAddr;
	}
	static void act_e14H_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的e14属性
		pps[pps.size()-3]->getSynAttr()->e14.sValFlag=ps->expr.sValFlag;
		pps[pps.size()-3]->getSynAttr()->e14.sType=ps->expr.sType;
		pps[pps.size()-3]->getSynAttr()->e14.sAddr=ps->expr.sAddr;
		if(ps->expr.spTrueList)
			pps[pps.size()-3]->getSynAttr()->e14.spTrueList->swap(*(ps->expr.spTrueList));	//不能使用浅拷贝
		if(ps->expr.spFalseList)
			pps[pps.size()-3]->getSynAttr()->e14.spFalseList->swap(*(ps->expr.spFalseList));
	}
	static void act_e14I_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Temp_Var *pt=pps.back()->getTempVar();

		//A(id)的属性传递给T3
		pps[pps.size()-2]->getInhAttr()->T3.iLine=pt->e14_id.tLine;
		pps[pps.size()-2]->getInhAttr()->T3.iLexime->swap(*(pt->e14_id.tLexime));
	}
	static void act_e14I_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的e14属性
		pps[pps.size()-2]->getSynAttr()->e14.sValFlag=true;
		pps[pps.size()-2]->getSynAttr()->e14.sType=ps->T3.sType;
		pps[pps.size()-2]->getSynAttr()->e14.sAddr=ps->T3.sAddr;
	}

	static void act_T3A_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//获取id词素
		const string name(*(pi->T3.iLexime));

		//如果声明为变量/数组
		if(context.isVar(name))
		{
			//获取变量/数组信息
			AllocInfo const &vi=*context.getAllocInfo(name);

			//如果声明为数组
			if(vi.var_info.is_array)
			{
				//错误报告
				string str="++ 操作数不能是一个数组。";

				//追加到记录
				err_record.insert(make_pair(pi->T3.iLine,str));	
			}
			else
			{
				//计算S后面的T3属性
				pps[pps.size()-2]->getSynAttr()->T3.sType=vi.var_info;
				pps[pps.size()-2]->getSynAttr()->T3.sAddr=context.Temp(vi.var_info,pi->T3.iSection);

				//获取id地址
				Address id_addr=context.getAddress(name);

				//为后缀++生成指令代码
				context.Gen(op_assign,pps[pps.size()-2]->getSynAttr()->T3.sAddr,id_addr,pi->T3.iSection);
				context.Gen(op_add,id_addr,context.getAddress(1),id_addr,pi->T3.iSection);
			}
		}
		//如果声明为函数
		else if(context.isFun(name))
		{
			//错误报告
			string str="++ 操作数不能是一个函数。";

			//追加到记录
			err_record.insert(make_pair(pi->T3.iLine,str));	
		}
		//未声明的名字
		else
		{
			//错误报告
			string str="未声明的名字"+name+"。";

			//追加到记录
			err_record.insert(make_pair(pi->T3.iLine,str));
		}
	}
	static void act_T3B_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//获取id词素
		const string name(*(pi->T3.iLexime));

		//如果声明为变量/数组
		if(context.isVar(name))
		{
			//获取变量/数组信息
			AllocInfo const &vi=*context.getAllocInfo(name);

			//如果声明为数组
			if(vi.var_info.is_array)
			{
				//错误报告
				string str="-- 操作数不能是一个数组。";

				//追加到记录
				err_record.insert(make_pair(pi->T3.iLine,str));	
			}
			else
			{
				//计算S后面的T3属性
				pps[pps.size()-2]->getSynAttr()->T3.sType=vi.var_info;
				pps[pps.size()-2]->getSynAttr()->T3.sAddr=context.Temp(vi.var_info,pi->T3.iSection);

				//获取id地址
				Address id_addr=context.getAddress(name);

				//为后缀--生成指令代码
				context.Gen(op_assign,pps[pps.size()-2]->getSynAttr()->T3.sAddr,id_addr,pi->T3.iSection);
				context.Gen(op_sub,id_addr,context.getAddress(1),id_addr,pi->T3.iSection);
			}
		}
		//如果声明为函数
		else if(context.isFun(name))
		{
			//错误报告
			string str="-- 操作数不能是一个函数。";

			//追加到记录
			err_record.insert(make_pair(pi->T3.iLine,str));	
		}
		//未声明的名字
		else
		{
			//错误报告
			string str="未声明的名字"+name+"。";

			//追加到记录
			err_record.insert(make_pair(pi->T3.iLine,str));
		}
	}
	static void act_T3C_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//获取id词素
		const string name(*(pi->T3.iLexime));

		//如果声明为变量/数组
		if(context.isVar(name))
		{
			//如果声明为数组
			if(context.getAllocInfo(name)->var_info.is_array)
			{
				//错误报告
				string str="不能对数组名使用调用操作。";

				//追加到记录
				err_record.insert(make_pair(pi->T3.iLine,str));	
			}
			else
			{
				//错误报告
				string str="不能对变量名使用调用操作。";

				//追加到记录
				err_record.insert(make_pair(pi->T3.iLine,str));	
			}
		}
		//如果声明为函数
		else if(context.isFun(name))
		{
			//no-op	
		}
		//未声明的名字
		else
		{
			//错误报告
			string str="未声明的名字"+name+"。";

			//追加到记录
			err_record.insert(make_pair(pi->T3.iLine,str));
		}
	}
	static void act_T3C_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算T3属性:
		pps[pps.size()-3]->getSynAttr()->T3.sType=ps->args.sType;
		pps[pps.size()-3]->getSynAttr()->T3.sAddr=ps->args.sAddr;
	}
	static void act_T3D_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//获取id词素
		const string name(*(pi->T3.iLexime));

		//如果声明为变量/数组
		if(context.isVar(name))
		{
			//如果声明为变量
			if(!context.getAllocInfo(name)->var_info.is_array)
			{
				//错误报告
				string str="不能对变量名使用下标访问操作。";

				//追加到记录
				err_record.insert(make_pair(pi->T3.iLine,str));	
			}
		}
		//如果声明为函数
		else if(context.isFun(name))
		{
			//错误报告
			string str="不能对函数名使用下标访问操作。";

			//追加到记录
			err_record.insert(make_pair(pi->T3.iLine,str));	
		}
		//未声明的名字
		else
		{
			//错误报告
			string str="未声明的名字"+name+"。";

			//追加到记录
			err_record.insert(make_pair(pi->T3.iLine,str));
		}
	}
	static void act_T3D_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//转换成value
		ControlFlow2Value(context,ps,pi->T3.iSection);

		if(ps->expr.sType.is_array)
		{
			//错误报告
			string str="数组"+*(pi->T3.iLexime)+"下标表达式不能是数组。";

			//追加到记录
			err_record.insert(make_pair(pi->T3.iLine,str));
		}
		//如果下标表达式类型是整型
		else if(isInteger(ps->expr.sType.type))
		{
			//addr属性传递给T4
			pps[pps.size()-3]->getInhAttr()->T4.iAddr=ps->expr.sAddr;
		}
		else
		{
			//错误报告
			string str="数组"+*(pi->T3.iLexime)+"下标表达式类型必须是整型。";

			//追加到记录
			err_record.insert(make_pair(pi->T3.iLine,str));
		}
	}
	static void act_T3D_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的T3属性:
		pps[pps.size()-2]->getSynAttr()->T3.sType=ps->T4.sType;
		pps[pps.size()-2]->getSynAttr()->T3.sAddr=ps->T4.sAddr;
	}
	static void act_T3E_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//获取id词素
		const string name(*(pi->T3.iLexime));

		//如果声明为变量/数组
		if(context.isVar(name))
		{
			//计算S后面的T3属性:数组仅仅可以作为实参传递给函数
			pps[pps.size()-2]->getSynAttr()->T3.sType=context.getAllocInfo(name)->var_info;
			pps[pps.size()-2]->getSynAttr()->T3.sAddr=context.getAddress(name);
		}
		//如果声明为函数
		else if(context.isFun(name))
		{
			//错误报告
			string str="函数"+name+"调用非法。";

			//追加到记录
			err_record.insert(make_pair(pi->T3.iLine,str));	
		}
		//未声明的名字
		else
		{
			//错误报告
			string str="未声明的名字"+name+"。";

			//追加到记录
			err_record.insert(make_pair(pi->T3.iLine,str));
		}
	}

	static void act_T4A_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		AllocInfo const* pai=context.getAllocInfo(*(pi->T4.iLexime));

		//如果数组已声明
		if(pai)
		{
			//计算A后面的T4属性:
			pps[pps.size()-2]->getSynAttr()->T4.sType.type=pai->var_info.type;
			pps[pps.size()-2]->getSynAttr()->T4.sType.is_array=false;
			Address temp_addr=context.Temp(pps[pps.size()-2]->getSynAttr()->T4.sType,pi->T4.iSection);
			pps[pps.size()-2]->getSynAttr()->T4.sAddr=temp_addr;

			//获取数组地址
			Address array_addr=context.getAddress(*(pi->T4.iLexime));

			//为后缀++生成指令代码
			context.Gen(op_read_array,array_addr,pi->T4.iAddr,temp_addr,pi->T4.iSection);	//取值
			context.Gen(op_add,temp_addr,context.getAddress(1),temp_addr,pi->T4.iSection);	//累加
			context.Gen(op_write_array,array_addr,pi->T4.iAddr,temp_addr,pi->T4.iSection);	//写回
			context.Gen(op_sub,temp_addr,context.getAddress(1),temp_addr,pi->T4.iSection);	//复原
		}
	}
	static void act_T4B_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		AllocInfo const* pai=context.getAllocInfo(*(pi->T4.iLexime));

		//如果数组已声明
		if(pai)
		{
			//计算A后面的T4属性:
			pps[pps.size()-2]->getSynAttr()->T4.sType.type=pai->var_info.type;
			pps[pps.size()-2]->getSynAttr()->T4.sType.is_array=false;
			Address temp_addr=context.Temp(pps[pps.size()-2]->getSynAttr()->T4.sType,pi->T4.iSection);
			pps[pps.size()-2]->getSynAttr()->T4.sAddr=temp_addr;

			//获取数组地址
			Address array_addr=context.getAddress(*(pi->T4.iLexime));

			//为后缀--生成指令代码
			context.Gen(op_read_array,array_addr,pi->T4.iAddr,temp_addr,pi->T4.iSection);	//取值
			context.Gen(op_sub,temp_addr,context.getAddress(1),temp_addr,pi->T4.iSection);	//递减
			context.Gen(op_write_array,array_addr,pi->T4.iAddr,temp_addr,pi->T4.iSection);	//写回
			context.Gen(op_add,temp_addr,context.getAddress(1),temp_addr,pi->T4.iSection);	//复原
		}
	}
	static void act_T4C_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		AllocInfo const* pai=context.getAllocInfo(*(pi->T4.iLexime));

		//如果数组已声明
		if(pai)
		{
			//计算A后面的T4属性:
			pps[pps.size()-2]->getSynAttr()->T4.sType.type=pai->var_info.type;
			pps[pps.size()-2]->getSynAttr()->T4.sType.is_array=false;
			pps[pps.size()-2]->getSynAttr()->T4.sAddr=context.Temp(pps[pps.size()-2]->getSynAttr()->T4.sType,pi->T4.iSection);

			//为数组访问生成指令代码:本语言并没有lvalue和rvalue的概念(因为没有指针和取地址操作),所以并不需要返回数组元素的引用,只需返回值拷贝即可。
			context.Gen(op_read_array,context.getAddress(*(pi->T4.iLexime)),pi->T4.iAddr,pps[pps.size()-2]->getSynAttr()->T4.sAddr,pi->T4.iSection);	//取值
		}
	}

	static void act_loc_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Temp_Var *pt=pps.back()->getTempVar();

		//id属性传递给loc'
		pps[pps.size()-2]->getInhAttr()->loc_.iLine=pt->loc_id.tLine;
		pps[pps.size()-2]->getInhAttr()->loc_.iLexime->swap(*(pt->loc_id.tLexime));
	}
	static void act_loc_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的loc属性:
		pps[pps.size()-2]->getSynAttr()->loc.sType=ps->loc_.sType;
		pps[pps.size()-2]->getSynAttr()->loc.sAddr=ps->loc_.sAddr;
	}

	static void act_loc_1_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//获取id词素
		const string name(*(pi->loc_.iLexime));

		//如果声明为变量/数组
		if(context.isVar(name))
		{
			//如果声明为变量
			if(!context.getAllocInfo(name)->var_info.is_array)
			{
				//错误报告
				string str="不能对变量名使用下标访问操作。";

				//追加到记录
				err_record.insert(make_pair(pi->loc_.iLine,str));	
			}
		}
		//如果声明为函数
		else if(context.isFun(name))
		{
			//错误报告
			string str="不能对函数名使用下标访问操作。";

			//追加到记录
			err_record.insert(make_pair(pi->loc_.iLine,str));	
		}
		//未声明的名字
		else
		{
			//错误报告
			string str="未声明的名字"+name+"。";

			//追加到记录
			err_record.insert(make_pair(pi->loc_.iLine,str));
		}
	}
	static void act_loc_1_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//转换成value
		ControlFlow2Value(context,ps,pi->loc_.iSection);

		if(ps->expr.sType.is_array)
		{
			//错误报告
			string str="数组"+*(pi->loc_.iLexime)+"下标表达式不能是数组。";

			//追加到记录
			err_record.insert(make_pair(pi->loc_.iLine,str));
		}
		//如果下标表达式类型是整型
		else if(isInteger(ps->expr.sType.type))
		{
			AllocInfo const* pai=context.getAllocInfo(*(pi->loc_.iLexime));

			//如果数组已声明
			if(pai)
			{
				//计算loc'属性:
				pps[pps.size()-3]->getSynAttr()->loc_.sType.type=pai->var_info.type;
				pps[pps.size()-3]->getSynAttr()->loc_.sType.is_array=false;
				Address temp_addr=context.Temp(pps[pps.size()-3]->getSynAttr()->loc_.sType,pi->loc_.iSection);
				pps[pps.size()-3]->getSynAttr()->loc_.sAddr=temp_addr;

				//获取数组地址
				Address array_addr=context.getAddress(*(pi->loc_.iLexime));

				//为前缀++/--生成指令代码
				context.Gen(op_read_array,array_addr,ps->expr.sAddr,temp_addr,pi->loc_.iSection);	//取值
				if(pi->loc_.i_Inc)
					context.Gen(op_add,temp_addr,context.getAddress(1),temp_addr,pi->loc_.iSection);	//累加
				else
					context.Gen(op_sub,temp_addr,context.getAddress(1),temp_addr,pi->loc_.iSection);	//递减
				context.Gen(op_write_array,array_addr,ps->expr.sAddr,temp_addr,pi->loc_.iSection);	//写回
			}
		}
		else
		{
			//错误报告
			string str="数组"+*(pi->loc_.iLexime)+"下标表达式类型必须是整型。";

			//追加到记录
			err_record.insert(make_pair(pi->loc_.iLine,str));
		}
	}
	static void act_loc_2_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//获取id词素
		const string name(*(pi->loc_.iLexime));

		//如果声明为变量/数组
		if(context.isVar(name))
		{
			//获取变量/数组信息
			AllocInfo const &vi=*context.getAllocInfo(name);

			//如果声明为数组
			if(vi.var_info.is_array)
			{
				//错误报告
				string str;

				if(pi->loc_.i_Inc)				
					str="++ 操作数不能是一个数组。";
				else
					str="-- 操作数不能是一个数组。";

				//追加到记录
				err_record.insert(make_pair(pi->loc_.iLine,str));	
			}
			else
			{				
				//获取id地址
				Address id_addr=context.getAddress(name);

				//计算S后面的loc_属性
				pps[pps.size()-2]->getSynAttr()->loc_.sType=vi.var_info;
				pps[pps.size()-2]->getSynAttr()->loc_.sAddr=id_addr;

				//为前缀++/--生成指令代码
				if(pi->loc_.i_Inc)
					context.Gen(op_add,id_addr,context.getAddress(1),id_addr,pi->loc_.iSection);
				else
					context.Gen(op_sub,id_addr,context.getAddress(1),id_addr,pi->loc_.iSection);
			}
		}
		//如果声明为函数
		else if(context.isFun(name))
		{
			//错误报告
			string str;

			if(pi->loc_.i_Inc)				
				str="++ 操作数不能是一个函数。";
			else
				str="-- 操作数不能是一个函数。";

			//追加到记录
			err_record.insert(make_pair(pi->loc_.iLine,str));	
		}
		//未声明的名字
		else
		{
			//错误报告
			string str="未声明的名字"+name+"。";

			//追加到记录
			err_record.insert(make_pair(pi->loc_.iLine,str));
		}
	}

	static void act_args1_A1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//将A2的arglist指针传递给args'
		pps[pps.size()-2]->getInhAttr()->args_.ipArgList=pps[pps.size()-3]->getTempVar()->args.ipArgList;
	}
	static void act_args1_A2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//获取被调函数的声明信息
		const FunInfo* pfi=context.getFunInfo(*(pi->args.iLexime));

		//如果函数已声明
		if(pfi)
		{
			//调用参数过少错误
			if(pt->args.ipArgList->size()<pfi->param_list.size())
			{
				//错误报告
				string str="函数"+*(pi->args.iLexime)+"缺少调用参数。";

				//追加到记录
				err_record.insert(make_pair(pi->args.iLine,str));
			}
			else
			{
				//顺序生成传递调用参数的指令
				for(arg_list::const_iterator citor=pt->args.ipArgList->begin();citor!=pt->args.ipArgList->end();++citor)
					context.Gen(op_param,*citor,pi->args.iSection);

				//计算args属性
				pps[pps.size()-2]->getSynAttr()->args.sType.type=pfi->ret_type;
				pps[pps.size()-2]->getSynAttr()->args.sType.is_array=false;

				//获取上下文函数信息
				const FunInfo* pcf=context.getFunInfo(context.getName());

				//如果返回类型是void
				if(t_VOID==pfi->ret_type)
				{
					//args地址置为无效
					pps[pps.size()-2]->getSynAttr()->args.sAddr.section=s_INVALID;

					//生成函数调用指令:	不返回值
					context.Gen(op_call,context.getAddress(int(pfi->id)),context.getAddress(int(pfi->param_list.size())),pi->args.iSection);
				
					//函数加入调用集合,掦除直接递归调用
					if(!pcf || pcf->id!=pfi->id)
						byte_code.getCallSet().insert(pfi->id);
				}
				else
				{
					//生成args地址
					pps[pps.size()-2]->getSynAttr()->args.sAddr=context.Temp(pps[pps.size()-2]->getSynAttr()->args.sType,pi->args.iSection);

					//生成函数调用指令:	返回值
					context.Gen(op_call_ass,context.getAddress(int(pfi->id)),context.getAddress(int(pfi->param_list.size())),pps[pps.size()-2]->getSynAttr()->args.sAddr,pi->args.iSection);
				
					//函数加入调用集合,掦除直接递归调用
					if(!pcf || pcf->id!=pfi->id)
						byte_code.getCallSet().insert(pfi->id);
				}
			}
		}
	}
	static void act_args2_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//获取被调函数的声明信息
		const FunInfo* pfi=context.getFunInfo(*(pi->args.iLexime));

		//如果函数已声明
		if(pfi)
		{
			//调用参数过少错误
			if(0<pfi->param_list.size())
			{
				//错误报告
				string str="函数"+*(pi->args.iLexime)+"缺少调用参数。";

				//追加到记录
				err_record.insert(make_pair(pi->args.iLine,str));
			}
			else
			{
				//计算args属性
				pps[pps.size()-2]->getSynAttr()->args.sType.type=pfi->ret_type;
				pps[pps.size()-2]->getSynAttr()->args.sType.is_array=false;					
				
				//获取上下文函数信息
				const FunInfo* pcf=context.getFunInfo(context.getName());

				//如果返回类型是void
				if(t_VOID==pfi->ret_type)
				{
					//args地址置为无效
					pps[pps.size()-2]->getSynAttr()->args.sAddr.section=s_INVALID;

					//生成函数调用指令:	0参调用,不返回值
					context.Gen(op_call,context.getAddress(int(pfi->id)),context.getAddress(int(0)),pi->args.iSection);

					//函数加入调用集合,掦除直接递归调用
					if(!pcf || pcf->id!=pfi->id)
						byte_code.getCallSet().insert(pfi->id);
				}
				else
				{
					//生成args地址
					pps[pps.size()-2]->getSynAttr()->args.sAddr=context.Temp(pps[pps.size()-2]->getSynAttr()->args.sType,pi->args.iSection);

					//生成函数调用指令:	0参调用,返回值
					context.Gen(op_call_ass,context.getAddress(int(pfi->id)),context.getAddress(int(0)),pps[pps.size()-2]->getSynAttr()->args.sAddr,pi->args.iSection);
				
					//函数加入调用集合,掦除直接递归调用
					if(!pcf || pcf->id!=pfi->id)
						byte_code.getCallSet().insert(pfi->id);
				}
			}
		}
	}

	static void act_arg_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//转换成value
		ControlFlow2Value(context,ps,pi->arg.iSection);

		//获取被调函数的声明信息
		const FunInfo* pfi=context.getFunInfo(*(pi->arg.iLexime));

		//如果函数已声明
		if(pfi)
		{
			//如果调用实参过多
			if(pfi->param_list.size()<pi->arg.iCnt)
			{
				//错误报告
				string str="传递给函数"+*(pi->arg.iLexime)+"的实参过多。";

				//追加到记录
				err_record.insert(make_pair(pi->arg.iLine,str));			
			}
			else
			{	
				//实参表达式地址加入实参列表
				pi->arg.ipArgList->push_back(ps->e1.sAddr);

				bool compatiable;

				//调用特殊库函数
				if(context.especial(*(pi->arg.iLexime)))
				{
					//使用特殊的参数检查策略
					compatiable=esCompatible(ps->e1.sType,pfi->param_list[pi->arg.iCnt-1]);
				}
				else
				{
					//使用普通的参数检查策略
					compatiable=Compatible(ps->e1.sType,pfi->param_list[pi->arg.iCnt-1]);
				}

				//检查实参与形参类型是否兼容
				if(!compatiable)
				{
					//错误报告
					string str="传递给函数"+*(pi->arg.iLexime)+"的第"+toString(int(pi->arg.iCnt))+"个实参表达式类型不兼容。";

					//追加到记录
					err_record.insert(make_pair(pi->arg.iLine,str));
				}
			}
		}
	}

	static void act_T1A_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//获取id词素
		const string name(*(pi->T1.iLexime));

		//如果声明为变量/数组
		if(context.isVar(name))
		{
			//获取变量/数组信息
			AllocInfo const &vi=*context.getAllocInfo(name);

			//如果声明为数组
			if(vi.var_info.is_array)
			{
				//错误报告
				string str="++ 操作数不能是一个数组。";

				//追加到记录
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				////计算S后面的T1属性
				//pps[pps.size()-2]->getSynAttr()->T1.sValFlag=true;
				//pps[pps.size()-2]->getSynAttr()->T1.sType=vi.var_info;
				//pps[pps.size()-2]->getSynAttr()->T1.sAddr=context.Temp(vi.var_info,pi->T1.iSection);

				//传递给后面的T5
				pps[pps.size()-2]->getInhAttr()->T5.iType=vi.var_info;
				pps[pps.size()-2]->getInhAttr()->T5.iAddr=context.Temp(vi.var_info,pi->T1.iSection);

				//获取id地址
				Address id_addr=context.getAddress(name);

				//为后缀++生成指令代码
				context.Gen(op_assign,pps[pps.size()-2]->getInhAttr()->T5.iAddr,id_addr,pi->T1.iSection);
				context.Gen(op_add,id_addr,context.getAddress(1),id_addr,pi->T1.iSection);
			}
		}
		//如果声明为函数
		else if(context.isFun(name))
		{
			//错误报告
			string str="++ 操作数不能是一个函数。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//未声明的名字
		else
		{
			//错误报告
			string str="未声明的名字"+name+"。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1B_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//获取id词素
		const string name(*(pi->T1.iLexime));

		//如果声明为变量/数组
		if(context.isVar(name))
		{
			//获取变量/数组信息
			AllocInfo const &vi=*context.getAllocInfo(name);

			//如果声明为数组
			if(vi.var_info.is_array)
			{
				//错误报告
				string str="-- 操作数不能是一个数组。";

				//追加到记录
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				////计算S后面的T1属性
				//pps[pps.size()-2]->getSynAttr()->T1.sValFlag=true;
				//pps[pps.size()-2]->getSynAttr()->T1.sType=vi.var_info;
				//pps[pps.size()-2]->getSynAttr()->T1.sAddr=context.Temp(vi.var_info,pi->T1.iSection);

				//传递给后面的T5
				pps[pps.size()-2]->getInhAttr()->T5.iType=vi.var_info;
				pps[pps.size()-2]->getInhAttr()->T5.iAddr=context.Temp(vi.var_info,pi->T1.iSection);

				//获取id地址
				Address id_addr=context.getAddress(name);

				//为后缀--生成指令代码
				context.Gen(op_assign,pps[pps.size()-2]->getInhAttr()->T5.iAddr,id_addr,pi->T1.iSection);
				context.Gen(op_sub,id_addr,context.getAddress(1),id_addr,pi->T1.iSection);
			}
		}
		//如果声明为函数
		else if(context.isFun(name))
		{
			//错误报告
			string str="-- 操作数不能是一个函数。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//未声明的名字
		else
		{
			//错误报告
			string str="未声明的名字"+name+"。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1C_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//获取id词素
		const string name(*(pi->T1.iLexime));

		//如果声明为变量/数组
		if(context.isVar(name))
		{
			//如果声明为数组
			if(context.getAllocInfo(name)->var_info.is_array)
			{
				//错误报告
				string str="不能对数组名使用调用操作。";

				//追加到记录
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//错误报告
				string str="不能对变量名使用调用操作。";

				//追加到记录
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
		}
		//如果声明为函数
		else if(context.isFun(name))
		{
			//no-op	
		}
		//未声明的名字
		else
		{
			//错误报告
			string str="未声明的名字"+name+"。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1C_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		////计算T1属性:
		//pps[pps.size()-3]->getSynAttr()->T1.sValFlag=true;
		//pps[pps.size()-3]->getSynAttr()->T1.sType=ps->args.sType;
		//pps[pps.size()-3]->getSynAttr()->T1.sAddr=ps->args.sAddr;

		//传递给后面的T5
		pps[pps.size()-3]->getInhAttr()->T5.iType=ps->args.sType;
		pps[pps.size()-3]->getInhAttr()->T5.iAddr=ps->args.sAddr;
	}
	static void act_T1D_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//获取id词素
		const string name(*(pi->T1.iLexime));

		//如果声明为变量/数组
		if(context.isVar(name))
		{
			//如果声明为变量
			if(!context.getAllocInfo(name)->var_info.is_array)
			{
				//错误报告
				string str="不能对变量名使用下标访问操作。";

				//追加到记录
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
		}
		//如果声明为函数
		else if(context.isFun(name))
		{
			//错误报告
			string str="不能对函数名使用下标访问操作。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//未声明的名字
		else
		{
			//错误报告
			string str="未声明的名字"+name+"。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1D_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//转换成value
		ControlFlow2Value(context,ps,pi->T1.iSection);

		if(ps->expr.sType.is_array)
		{
			//错误报告
			string str="数组"+*(pi->T1.iLexime)+"下标表达式不能是数组。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
		//如果下标表达式类型是整型
		else if(isInteger(ps->expr.sType.type))
		{
			//addr属性传递给T2
			pps[pps.size()-3]->getInhAttr()->T2.iAddr=ps->expr.sAddr;
		}
		else
		{
			//错误报告
			string str="数组"+*(pi->T1.iLexime)+"下标表达式类型必须是整型。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1D_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的T1属性:		
		pps[pps.size()-2]->getSynAttr()->T1.sValFlag=ps->T2.sValFlag;
		pps[pps.size()-2]->getSynAttr()->T1.sType=ps->T2.sType;
		pps[pps.size()-2]->getSynAttr()->T1.sAddr=ps->T2.sAddr;
		if(ps->T2.spTrueList)
			pps[pps.size()-2]->getSynAttr()->T1.spTrueList->swap(*(ps->T2.spTrueList));
		if(ps->T2.spFalseList)
			pps[pps.size()-2]->getSynAttr()->T1.spFalseList->swap(*(ps->T2.spFalseList));
	}

	static void act_T1E_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Temp_Var *pt=pps.back()->getTempVar();

		//op属性传递给S
		pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
	}
	static void act_T1E_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//获取id词素
		const string name(*(pi->T1.iLexime));

		//如果声明为变量/数组
		if(context.isVar(name))
		{
			//获取变量/数组信息
			AllocInfo const &vi=*context.getAllocInfo(name);

			//如果声明为数组
			if(vi.var_info.is_array)
			{
				//错误报告
				string str="不能对一个数组赋值。";

				//追加到记录
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//转换成value
				ControlFlow2Value(context,ps,pi->T1.iSection);

				//如果可计算
				if(Computable(ps->e1.sType))
				{
					//获取id地址
					Address id_addr=context.getAddress(name);

					//计算S后面的T1属性
					pps[pps.size()-2]->getSynAttr()->T1.sValFlag=true;
					pps[pps.size()-2]->getSynAttr()->T1.sType=vi.var_info;
					pps[pps.size()-2]->getSynAttr()->T1.sAddr=id_addr;

					//生成向变量赋值的指令
					context.Gen(op_assign,id_addr,ps->e1.sAddr,pi->T1.iSection);
				}
				else
				{
					//错误报告
					string str="= 右边表达式类型错误。";

					//追加到记录
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
			}
		}
		//如果声明为函数
		else if(context.isFun(name))
		{
			//错误报告
			string str="不能对一个函数赋值。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//未声明的名字
		else
		{
			//错误报告
			string str="未声明的名字"+name+"。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));
		}	
	}
	static void act_T1F_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//获取id词素
		const string name(*(pi->T1.iLexime));

		//如果声明为变量/数组
		if(context.isVar(name))
		{
			//获取变量/数组信息
			AllocInfo const &vi=*context.getAllocInfo(name);

			//如果声明为数组
			if(vi.var_info.is_array)
			{
				//错误报告
				string str="不能对一个数组赋值。";

				//追加到记录
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//转换成value
				ControlFlow2Value(context,ps,pi->T1.iSection);

				//如果类型可计算
				if(Computable(ps->e1.sType))
				{
					//获取id地址
					Address id_addr=context.getAddress(name);

					//计算S后面的T1属性
					pps[pps.size()-2]->getSynAttr()->T1.sValFlag=true;
					pps[pps.size()-2]->getSynAttr()->T1.sType=vi.var_info;
					pps[pps.size()-2]->getSynAttr()->T1.sAddr=id_addr;

					//生成向变量赋值的指令
					context.Gen(op_mul,id_addr,ps->e1.sAddr,id_addr,pi->T1.iSection);
				}
				else
				{
					//错误报告
					string str="*= 右边表达式类型错误。";

					//追加到记录
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
			}
		}
		//如果声明为函数
		else if(context.isFun(name))
		{
			//错误报告
			string str="不能对一个函数赋值。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//未声明的名字
		else
		{
			//错误报告
			string str="未声明的名字"+name+"。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));
		}	
	}
	static void act_T1G_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//获取id词素
		const string name(*(pi->T1.iLexime));

		//如果声明为变量/数组
		if(context.isVar(name))
		{
			//获取变量/数组信息
			AllocInfo const &vi=*context.getAllocInfo(name);

			//如果声明为数组
			if(vi.var_info.is_array)
			{
				//错误报告
				string str="不能对一个数组赋值。";

				//追加到记录
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//转换成value
				ControlFlow2Value(context,ps,pi->T1.iSection);

				//如果类型可计算
				if(Computable(ps->e1.sType))
				{
					//获取id地址
					Address id_addr=context.getAddress(name);

					//计算S后面的T1属性
					pps[pps.size()-2]->getSynAttr()->T1.sValFlag=true;
					pps[pps.size()-2]->getSynAttr()->T1.sType=vi.var_info;
					pps[pps.size()-2]->getSynAttr()->T1.sAddr=id_addr;

					//生成向变量赋值的指令
					context.Gen(op_div,id_addr,ps->e1.sAddr,id_addr,pi->T1.iSection);
				}
				else
				{
					//错误报告
					string str="/= 右边表达式类型错误。";

					//追加到记录
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
			}
		}
		//如果声明为函数
		else if(context.isFun(name))
		{
			//错误报告
			string str="不能对一个函数赋值。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//未声明的名字
		else
		{
			//错误报告
			string str="未声明的名字"+name+"。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1H_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//获取id词素
		const string name(*(pi->T1.iLexime));

		//如果声明为变量/数组
		if(context.isVar(name))
		{
			//获取变量/数组信息
			AllocInfo const &vi=*context.getAllocInfo(name);

			//如果声明为数组
			if(vi.var_info.is_array)
			{
				//错误报告
				string str="不能对一个数组赋值。";

				//追加到记录
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//转换成value
				ControlFlow2Value(context,ps,pi->T1.iSection);

				//如果类型可计算
				if(Computable(ps->e1.sType))
				{
					//获取id地址
					Address id_addr=context.getAddress(name);

					//计算S后面的T1属性
					pps[pps.size()-2]->getSynAttr()->T1.sValFlag=true;
					pps[pps.size()-2]->getSynAttr()->T1.sType=vi.var_info;
					pps[pps.size()-2]->getSynAttr()->T1.sAddr=id_addr;

					//生成向变量赋值的指令
					context.Gen(op_mod,id_addr,ps->e1.sAddr,id_addr,pi->T1.iSection);
				}
				else
				{
					//错误报告
					string str="%= 右边表达式类型错误。";

					//追加到记录
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
			}
		}
		//如果声明为函数
		else if(context.isFun(name))
		{
			//错误报告
			string str="不能对一个函数赋值。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//未声明的名字
		else
		{
			//错误报告
			string str="未声明的名字"+name+"。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1I_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//获取id词素
		const string name(*(pi->T1.iLexime));

		//如果声明为变量/数组
		if(context.isVar(name))
		{
			//获取变量/数组信息
			AllocInfo const &vi=*context.getAllocInfo(name);

			//如果声明为数组
			if(vi.var_info.is_array)
			{
				//错误报告
				string str="不能对一个数组赋值。";

				//追加到记录
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//转换成value
				ControlFlow2Value(context,ps,pi->T1.iSection);

				//如果类型可计算
				if(Computable(ps->e1.sType))
				{
					//获取id地址
					Address id_addr=context.getAddress(name);

					//计算S后面的T1属性
					pps[pps.size()-2]->getSynAttr()->T1.sValFlag=true;
					pps[pps.size()-2]->getSynAttr()->T1.sType=vi.var_info;
					pps[pps.size()-2]->getSynAttr()->T1.sAddr=id_addr;

					//生成向变量赋值的指令
					context.Gen(op_add,id_addr,ps->e1.sAddr,id_addr,pi->T1.iSection);
				}
				else
				{
					//错误报告
					string str="+= 右边表达式类型错误。";

					//追加到记录
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
			}
		}
		//如果声明为函数
		else if(context.isFun(name))
		{
			//错误报告
			string str="不能对一个函数赋值。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//未声明的名字
		else
		{
			//错误报告
			string str="未声明的名字"+name+"。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1J_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//获取id词素
		const string name(*(pi->T1.iLexime));

		//如果声明为变量/数组
		if(context.isVar(name))
		{
			//获取变量/数组信息
			AllocInfo const &vi=*context.getAllocInfo(name);

			//如果声明为数组
			if(vi.var_info.is_array)
			{
				//错误报告
				string str="不能对一个数组赋值。";

				//追加到记录
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//转换成value
				ControlFlow2Value(context,ps,pi->T1.iSection);

				//如果类型可计算
				if(Computable(ps->e1.sType))
				{
					//获取id地址
					Address id_addr=context.getAddress(name);

					//计算S后面的T1属性
					pps[pps.size()-2]->getSynAttr()->T1.sValFlag=true;
					pps[pps.size()-2]->getSynAttr()->T1.sType=vi.var_info;
					pps[pps.size()-2]->getSynAttr()->T1.sAddr=id_addr;

					//生成向变量赋值的指令
					context.Gen(op_sub,id_addr,ps->e1.sAddr,id_addr,pi->T1.iSection);
				}
				else
				{
					//错误报告
					string str="-= 右边表达式类型错误。";

					//追加到记录
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
			}
		}
		//如果声明为函数
		else if(context.isFun(name))
		{
			//错误报告
			string str="不能对一个函数赋值。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//未声明的名字
		else
		{
			//错误报告
			string str="未声明的名字"+name+"。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1K_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//获取id词素
		const string name(*(pi->T1.iLexime));

		//如果声明为变量/数组
		if(context.isVar(name))
		{
			//获取变量/数组信息
			AllocInfo const &vi=*context.getAllocInfo(name);

			//如果声明为数组
			if(vi.var_info.is_array)
			{
				//错误报告
				string str="不能对一个数组赋值。";

				//追加到记录
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//如果左操作数类型是整型
				if(isInteger(vi.var_info.type))
				{
					//转换成value
					ControlFlow2Value(context,ps,pi->T1.iSection);

					if(ps->e1.sType.is_array)
					{
						//错误报告
						string str="<<= 右操作数不是能数组。";

						//追加到记录
						err_record.insert(make_pair(pt->op_line.tLine,str));
					}
					//如果右操作数类型是整型
					else if(isInteger(ps->e1.sType.type))
					{
						//获取id地址
						Address id_addr=context.getAddress(name);

						//计算S后面的T1属性
						pps[pps.size()-2]->getSynAttr()->T1.sValFlag=true;
						pps[pps.size()-2]->getSynAttr()->T1.sType=vi.var_info;
						pps[pps.size()-2]->getSynAttr()->T1.sAddr=id_addr;

						//生成向变量赋值的指令
						context.Gen(op_lsht,id_addr,ps->e1.sAddr,id_addr,pi->T1.iSection);
					}
					else
					{
						//错误报告
						string str="<<= 右操作数类型必须是整型。";

						//追加到记录
						err_record.insert(make_pair(pt->op_line.tLine,str));
					}
				}
				else
				{
					//错误报告
					string str="<<= 左操作数类型必须是整型。";

					//追加到记录
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
			}
		}
		//如果声明为函数
		else if(context.isFun(name))
		{
			//错误报告
			string str="不能对一个函数赋值。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//未声明的名字
		else
		{
			//错误报告
			string str="未声明的名字"+name+"。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1L_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//获取id词素
		const string name(*(pi->T1.iLexime));

		//如果声明为变量/数组
		if(context.isVar(name))
		{
			//获取变量/数组信息
			AllocInfo const &vi=*context.getAllocInfo(name);

			//如果声明为数组
			if(vi.var_info.is_array)
			{
				//错误报告
				string str="不能对一个数组赋值。";

				//追加到记录
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//如果左操作数类型是整型
				if(isInteger(vi.var_info.type))
				{
					//转换成value
					ControlFlow2Value(context,ps,pi->T1.iSection);

					if(ps->e1.sType.is_array)
					{
						//错误报告
						string str=">>= 右操作数不能是数组。";

						//追加到记录
						err_record.insert(make_pair(pt->op_line.tLine,str));
					}
					//如果右操作数类型是整型
					else if(isInteger(ps->e1.sType.type))
					{
						//获取id地址
						Address id_addr=context.getAddress(name);

						//计算S后面的T1属性
						pps[pps.size()-2]->getSynAttr()->T1.sValFlag=true;
						pps[pps.size()-2]->getSynAttr()->T1.sType=vi.var_info;
						pps[pps.size()-2]->getSynAttr()->T1.sAddr=id_addr;

						//生成向变量赋值的指令
						context.Gen(op_rsht,id_addr,ps->e1.sAddr,id_addr,pi->T1.iSection);
					}
					else
					{
						//错误报告
						string str=">>= 右操作数类型必须是整型。";

						//追加到记录
						err_record.insert(make_pair(pt->op_line.tLine,str));
					}
				}
				else
				{
					//错误报告
					string str=">>= 左操作数类型必须是整型。";

					//追加到记录
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
			}
		}
		//如果声明为函数
		else if(context.isFun(name))
		{
			//错误报告
			string str="不能对一个函数赋值。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//未声明的名字
		else
		{
			//错误报告
			string str="未声明的名字"+name+"。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1M_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//获取id词素
		const string name(*(pi->T1.iLexime));

		//如果声明为变量/数组
		if(context.isVar(name))
		{
			//获取变量/数组信息
			AllocInfo const &vi=*context.getAllocInfo(name);

			//如果声明为数组
			if(vi.var_info.is_array)
			{
				//错误报告
				string str="不能对一个数组赋值。";

				//追加到记录
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//如果左操作数类型是整型
				if(isInteger(vi.var_info.type))
				{
					//转换成value
					ControlFlow2Value(context,ps,pi->T1.iSection);

					if(ps->e1.sType.is_array)
					{
						//错误报告
						string str="&= 右操作数不能是数组。";

						//追加到记录
						err_record.insert(make_pair(pt->op_line.tLine,str));
					}
					//如果右操作数类型是整型
					else if(isInteger(ps->e1.sType.type))
					{
						//获取id地址
						Address id_addr=context.getAddress(name);

						//计算S后面的T1属性
						pps[pps.size()-2]->getSynAttr()->T1.sValFlag=true;
						pps[pps.size()-2]->getSynAttr()->T1.sType=vi.var_info;
						pps[pps.size()-2]->getSynAttr()->T1.sAddr=id_addr;

						//生成向变量赋值的指令
						context.Gen(op_bit_and,id_addr,ps->e1.sAddr,id_addr,pi->T1.iSection);
					}
					else
					{
						//错误报告
						string str="&= 右操作数类型必须是整型。";

						//追加到记录
						err_record.insert(make_pair(pt->op_line.tLine,str));
					}
				}
				else
				{
					//错误报告
					string str="&= 左操作数类型必须是整型。";

					//追加到记录
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
			}
		}
		//如果声明为函数
		else if(context.isFun(name))
		{
			//错误报告
			string str="不能对一个函数赋值。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//未声明的名字
		else
		{
			//错误报告
			string str="未声明的名字"+name+"。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1N_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//获取id词素
		const string name(*(pi->T1.iLexime));

		//如果声明为变量/数组
		if(context.isVar(name))
		{
			//获取变量/数组信息
			AllocInfo const &vi=*context.getAllocInfo(name);

			//如果声明为数组
			if(vi.var_info.is_array)
			{
				//错误报告
				string str="不能对一个数组赋值。";

				//追加到记录
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//如果左操作数类型是整型
				if(isInteger(vi.var_info.type))
				{
					//转换成value
					ControlFlow2Value(context,ps,pi->T1.iSection);

					if(ps->e1.sType.is_array)
					{
						//错误报告
						string str="|= 右操作数不能是数组。";

						//追加到记录
						err_record.insert(make_pair(pt->op_line.tLine,str));
					}
					//如果右操作数类型是整型
					else if(isInteger(ps->e1.sType.type))
					{
						//获取id地址
						Address id_addr=context.getAddress(name);

						//计算S后面的T1属性
						pps[pps.size()-2]->getSynAttr()->T1.sValFlag=true;
						pps[pps.size()-2]->getSynAttr()->T1.sType=vi.var_info;
						pps[pps.size()-2]->getSynAttr()->T1.sAddr=id_addr;

						//生成向变量赋值的指令
						context.Gen(op_bit_or,id_addr,ps->e1.sAddr,id_addr,pi->T1.iSection);
					}
					else
					{
						//错误报告
						string str="|= 右操作数类型必须是整型。";

						//追加到记录
						err_record.insert(make_pair(pt->op_line.tLine,str));
					}
				}
				else
				{
					//错误报告
					string str="|= 左操作数类型必须是整型。";

					//追加到记录
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
			}
		}
		//如果声明为函数
		else if(context.isFun(name))
		{
			//错误报告
			string str="不能对一个函数赋值。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//未声明的名字
		else
		{
			//错误报告
			string str="未声明的名字"+name+"。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1O_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//获取id词素
		const string name(*(pi->T1.iLexime));

		//如果声明为变量/数组
		if(context.isVar(name))
		{
			//获取变量/数组信息
			AllocInfo const &vi=*context.getAllocInfo(name);

			//如果声明为数组
			if(vi.var_info.is_array)
			{
				//错误报告
				string str="不能对一个数组赋值。";

				//追加到记录
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//如果左操作数类型是整型
				if(isInteger(vi.var_info.type))
				{
					//转换成value
					ControlFlow2Value(context,ps,pi->T1.iSection);

					if(ps->e1.sType.is_array)
					{
						//错误报告
						string str="^= 右操作数不能是数组。";

						//追加到记录
						err_record.insert(make_pair(pt->op_line.tLine,str));
					}
					//如果右操作数类型是整型
					else if(isInteger(ps->e1.sType.type))
					{
						//获取id地址
						Address id_addr=context.getAddress(name);

						//计算S后面的T1属性
						pps[pps.size()-2]->getSynAttr()->T1.sValFlag=true;
						pps[pps.size()-2]->getSynAttr()->T1.sType=vi.var_info;
						pps[pps.size()-2]->getSynAttr()->T1.sAddr=id_addr;

						//生成向变量赋值的指令
						context.Gen(op_bit_xor,id_addr,ps->e1.sAddr,id_addr,pi->T1.iSection);
					}
					else
					{
						//错误报告
						string str="^= 右操作数类型必须是整型。";

						//追加到记录
						err_record.insert(make_pair(pt->op_line.tLine,str));
					}
				}
				else
				{
					//错误报告
					string str="^= 左操作数类型必须是整型。";

					//追加到记录
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
			}
		}
		//如果声明为函数
		else if(context.isFun(name))
		{
			//错误报告
			string str="不能对一个函数赋值。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//未声明的名字
		else
		{
			//错误报告
			string str="未声明的名字"+name+"。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}

	static void act_T1P_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//获取id词素
		const string name(*(pi->T1.iLexime));

		//如果声明为变量/数组
		if(context.isVar(name))
		{
			//获取变量/数组信息
			AllocInfo const &vi=*context.getAllocInfo(name);

			//如果声明为数组
			if(vi.var_info.is_array)
			{
				//错误报告
				string str="数组"+name+"不能作为操作数参与( ? : )运算。";

				//追加到记录
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//传递id属性
				pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=true;
				pps[pps.size()-2]->getInhAttr()->e2_.iType=vi.var_info;
				pps[pps.size()-2]->getInhAttr()->e2_.iAddr=context.getAddress(name);
			}
		}
		//如果声明为函数
		else if(context.isFun(name))
		{
			//错误报告
			string str="函数"+name+"调用非法。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//未声明的名字
		else
		{
			//错误报告
			string str="未声明的名字"+name+"。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1P_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的T1属性: e2'(control flow->value)
		pps[pps.size()-2]->getSynAttr()->T1.sValFlag=ps->e2_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->T1.sType=ps->e2_.sType;
		pps[pps.size()-2]->getSynAttr()->T1.sAddr=ps->e2_.sAddr;
		if(ps->e2_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->T1.spTrueList->swap(*(ps->e2_.spTrueList));
		if(ps->e2_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->T1.spFalseList->swap(*(ps->e2_.spFalseList));
	}

	static void act_T1Q_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//获取id词素
		const string name(*(pi->T1.iLexime));

		//如果声明为变量/数组
		if(context.isVar(name))
		{
			//获取变量/数组信息
			AllocInfo const &vi=*context.getAllocInfo(name);

			//如果声明为数组
			if(vi.var_info.is_array)
			{
				//错误报告
				string str="数组"+name+"不能作为操作数参与 || 运算。";

				//追加到记录
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//传递id属性
				pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=true;
				pps[pps.size()-2]->getInhAttr()->e3_.iType=vi.var_info;
				pps[pps.size()-2]->getInhAttr()->e3_.iAddr=context.getAddress(name);
			}
		}
		//如果声明为函数
		else if(context.isFun(name))
		{
			//错误报告
			string str="函数"+name+"调用非法。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//未声明的名字
		else
		{
			//错误报告
			string str="未声明的名字"+name+"。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1Q_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//赋空指针
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T1Q_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的T1属性: e2'(control flow->value)
		pps[pps.size()-2]->getSynAttr()->T1.sValFlag=ps->e2_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->T1.sType=ps->e2_.sType;
		pps[pps.size()-2]->getSynAttr()->T1.sAddr=ps->e2_.sAddr;
		if(ps->e2_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->T1.spTrueList->swap(*(ps->e2_.spTrueList));
		if(ps->e2_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->T1.spFalseList->swap(*(ps->e2_.spFalseList));
	}

	static void act_T1R_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//获取id词素
		const string name(*(pi->T1.iLexime));

		//如果声明为变量/数组
		if(context.isVar(name))
		{
			//获取变量/数组信息
			AllocInfo const &vi=*context.getAllocInfo(name);

			//如果声明为数组
			if(vi.var_info.is_array)
			{
				//错误报告
				string str="数组"+name+"不能作为操作数参与 && 运算。";

				//追加到记录
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//传递id属性
				pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=true;
				pps[pps.size()-2]->getInhAttr()->e4_.iType=vi.var_info;
				pps[pps.size()-2]->getInhAttr()->e4_.iAddr=context.getAddress(name);
			}
		}
		//如果声明为函数
		else if(context.isFun(name))
		{
			//错误报告
			string str="函数"+name+"调用非法。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//未声明的名字
		else
		{
			//错误报告
			string str="未声明的名字"+name+"。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1R_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//赋空指针
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T1R_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//赋空指针
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T1R_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的T1属性: e2'(control flow->value)
		pps[pps.size()-2]->getSynAttr()->T1.sValFlag=ps->e2_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->T1.sType=ps->e2_.sType;
		pps[pps.size()-2]->getSynAttr()->T1.sAddr=ps->e2_.sAddr;
		if(ps->e2_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->T1.spTrueList->swap(*(ps->e2_.spTrueList));
		if(ps->e2_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->T1.spFalseList->swap(*(ps->e2_.spFalseList));
	}

	static void act_T1S_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//获取id词素
		const string name(*(pi->T1.iLexime));

		//如果声明为变量/数组
		if(context.isVar(name))
		{
			//获取变量/数组信息
			AllocInfo const &vi=*context.getAllocInfo(name);

			//如果声明为数组
			if(vi.var_info.is_array)
			{
				//错误报告
				string str="数组"+name+"不能作为操作数参与 | 运算。";

				//追加到记录
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//传递id属性
				pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=true;
				pps[pps.size()-2]->getInhAttr()->e5_.iType=vi.var_info;
				pps[pps.size()-2]->getInhAttr()->e5_.iAddr=context.getAddress(name);
			}
		}
		//如果声明为函数
		else if(context.isFun(name))
		{
			//错误报告
			string str="函数"+name+"调用非法。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//未声明的名字
		else
		{
			//错误报告
			string str="未声明的名字"+name+"。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1S_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e4': e5'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//赋空指针
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T1S_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//赋空指针
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T1S_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//赋空指针
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T1S_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的T1属性: e2'(control flow->value)
		pps[pps.size()-2]->getSynAttr()->T1.sValFlag=ps->e2_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->T1.sType=ps->e2_.sType;
		pps[pps.size()-2]->getSynAttr()->T1.sAddr=ps->e2_.sAddr;
		if(ps->e2_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->T1.spTrueList->swap(*(ps->e2_.spTrueList));
		if(ps->e2_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->T1.spFalseList->swap(*(ps->e2_.spFalseList));
	}

	static void act_T1T_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//获取id词素
		const string name(*(pi->T1.iLexime));

		//如果声明为变量/数组
		if(context.isVar(name))
		{
			//获取变量/数组信息
			AllocInfo const &vi=*context.getAllocInfo(name);

			//如果声明为数组
			if(vi.var_info.is_array)
			{
				//错误报告
				string str="数组"+name+"不能作为操作数参与 ^ 运算。";

				//追加到记录
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//传递id属性
				pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=true;
				pps[pps.size()-2]->getInhAttr()->e6_.iType=vi.var_info;
				pps[pps.size()-2]->getInhAttr()->e6_.iAddr=context.getAddress(name);
			}
		}
		//如果声明为函数
		else if(context.isFun(name))
		{
			//错误报告
			string str="函数"+name+"调用非法。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//未声明的名字
		else
		{
			//错误报告
			string str="未声明的名字"+name+"。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1T_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e5': e6'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//赋空指针
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T1T_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e4': e5'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//赋空指针
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T1T_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//赋空指针
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T1T_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//赋空指针
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T1T_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的T1属性: e2'(control flow->value)
		pps[pps.size()-2]->getSynAttr()->T1.sValFlag=ps->e2_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->T1.sType=ps->e2_.sType;
		pps[pps.size()-2]->getSynAttr()->T1.sAddr=ps->e2_.sAddr;
		if(ps->e2_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->T1.spTrueList->swap(*(ps->e2_.spTrueList));
		if(ps->e2_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->T1.spFalseList->swap(*(ps->e2_.spFalseList));
	}

	static void act_T1U_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//获取id词素
		const string name(*(pi->T1.iLexime));

		//如果声明为变量/数组
		if(context.isVar(name))
		{
			//获取变量/数组信息
			AllocInfo const &vi=*context.getAllocInfo(name);

			//如果声明为数组
			if(vi.var_info.is_array)
			{
				//错误报告
				string str="数组"+name+"不能作为操作数参与 & 运算。";

				//追加到记录
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//传递id属性
				pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=true;
				pps[pps.size()-2]->getInhAttr()->e7_.iType=vi.var_info;
				pps[pps.size()-2]->getInhAttr()->e7_.iAddr=context.getAddress(name);
			}
		}
		//如果声明为函数
		else if(context.isFun(name))
		{
			//错误报告
			string str="函数"+name+"调用非法。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//未声明的名字
		else
		{
			//错误报告
			string str="未声明的名字"+name+"。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1U_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e6': e7'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7_.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7_.spFalseList;

		//赋空指针
		ps->e7_.spTrueList=0;
		ps->e7_.spFalseList=0;
	}
	static void act_T1U_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e5': e6'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//赋空指针
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T1U_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e4': e5'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//赋空指针
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T1U_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//赋空指针
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T1U_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//赋空指针
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T1U_S6(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的T1属性: e2'(control flow->value)
		pps[pps.size()-2]->getSynAttr()->T1.sValFlag=ps->e2_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->T1.sType=ps->e2_.sType;
		pps[pps.size()-2]->getSynAttr()->T1.sAddr=ps->e2_.sAddr;
		if(ps->e2_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->T1.spTrueList->swap(*(ps->e2_.spTrueList));
		if(ps->e2_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->T1.spFalseList->swap(*(ps->e2_.spFalseList));
	}

	static void act_T1V_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//获取id词素
		const string name(*(pi->T1.iLexime));

		//如果声明为变量/数组
		if(context.isVar(name))
		{
			//获取变量/数组信息
			AllocInfo const &vi=*context.getAllocInfo(name);

			//如果声明为数组
			if(vi.var_info.is_array)
			{
				//错误报告
				string str="数组"+name+"不能作为操作数参与 ==,!= 运算。";

				//追加到记录
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//传递id属性
				pps[pps.size()-2]->getInhAttr()->e8_.iValFlag=true;
				pps[pps.size()-2]->getInhAttr()->e8_.iType=vi.var_info;
				pps[pps.size()-2]->getInhAttr()->e8_.iAddr=context.getAddress(name);
			}
		}
		//如果声明为函数
		else if(context.isFun(name))
		{
			//错误报告
			string str="函数"+name+"调用非法。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//未声明的名字
		else
		{
			//错误报告
			string str="未声明的名字"+name+"。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1V_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e7': e8'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=ps->e8_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e7_.iType=ps->e8_.sType;
		pps[pps.size()-2]->getInhAttr()->e7_.iAddr=ps->e8_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e7_.ipTrueList=ps->e8_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e7_.ipFalseList=ps->e8_.spFalseList;

		//赋空指针
		ps->e8_.spTrueList=0;
		ps->e8_.spFalseList=0;
	}
	static void act_T1V_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e6': e7'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7_.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7_.spFalseList;

		//赋空指针
		ps->e7_.spTrueList=0;
		ps->e7_.spFalseList=0;
	}
	static void act_T1V_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e5': e6'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//赋空指针
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T1V_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e4': e5'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//赋空指针
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T1V_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//赋空指针
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T1V_S6(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//赋空指针
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T1V_S7(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的T1属性: e2'(control flow->value)
		pps[pps.size()-2]->getSynAttr()->T1.sValFlag=ps->e2_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->T1.sType=ps->e2_.sType;
		pps[pps.size()-2]->getSynAttr()->T1.sAddr=ps->e2_.sAddr;
		if(ps->e2_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->T1.spTrueList->swap(*(ps->e2_.spTrueList));
		if(ps->e2_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->T1.spFalseList->swap(*(ps->e2_.spFalseList));
	}

	static void act_T1W_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//获取id词素
		const string name(*(pi->T1.iLexime));

		//如果声明为变量/数组
		if(context.isVar(name))
		{
			//获取变量/数组信息
			AllocInfo const &vi=*context.getAllocInfo(name);

			//如果声明为数组
			if(vi.var_info.is_array)
			{
				//错误报告
				string str="数组"+name+"不能作为操作数参与 <,<=,>,>= 运算。";

				//追加到记录
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//传递id属性
				pps[pps.size()-2]->getInhAttr()->e9_.iValFlag=true;
				pps[pps.size()-2]->getInhAttr()->e9_.iType=vi.var_info;
				pps[pps.size()-2]->getInhAttr()->e9_.iAddr=context.getAddress(name);
			}
		}
		//如果声明为函数
		else if(context.isFun(name))
		{
			//错误报告
			string str="函数"+name+"调用非法。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//未声明的名字
		else
		{
			//错误报告
			string str="未声明的名字"+name+"。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1W_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e8': e9'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e8_.iValFlag=ps->e9_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e8_.iType=ps->e9_.sType;
		pps[pps.size()-2]->getInhAttr()->e8_.iAddr=ps->e9_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e8_.ipTrueList=ps->e9_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e8_.ipFalseList=ps->e9_.spFalseList;

		//赋空指针
		ps->e9_.spTrueList=0;
		ps->e9_.spFalseList=0;
	}
	static void act_T1W_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e7': e8'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=ps->e8_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e7_.iType=ps->e8_.sType;
		pps[pps.size()-2]->getInhAttr()->e7_.iAddr=ps->e8_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e7_.ipTrueList=ps->e8_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e7_.ipFalseList=ps->e8_.spFalseList;

		//赋空指针
		ps->e8_.spTrueList=0;
		ps->e8_.spFalseList=0;
	}
	static void act_T1W_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e6': e7'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7_.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7_.spFalseList;

		//赋空指针
		ps->e7_.spTrueList=0;
		ps->e7_.spFalseList=0;
	}
	static void act_T1W_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e5': e6'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//赋空指针
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T1W_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e4': e5'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//赋空指针
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T1W_S6(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//赋空指针
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T1W_S7(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//赋空指针
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T1W_S8(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的T1属性: e2'(control flow->value)
		pps[pps.size()-2]->getSynAttr()->T1.sValFlag=ps->e2_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->T1.sType=ps->e2_.sType;
		pps[pps.size()-2]->getSynAttr()->T1.sAddr=ps->e2_.sAddr;
		if(ps->e2_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->T1.spTrueList->swap(*(ps->e2_.spTrueList));
		if(ps->e2_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->T1.spFalseList->swap(*(ps->e2_.spFalseList));
	}

	static void act_T1X_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//获取id词素
		const string name(*(pi->T1.iLexime));

		//如果声明为变量/数组
		if(context.isVar(name))
		{
			//获取变量/数组信息
			AllocInfo const &vi=*context.getAllocInfo(name);

			//如果声明为数组
			if(vi.var_info.is_array)
			{
				//错误报告
				string str="数组"+name+"不能作为操作数参与 <<,>> 运算。";

				//追加到记录
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//传递id属性
				pps[pps.size()-2]->getInhAttr()->e10_.iValFlag=true;
				pps[pps.size()-2]->getInhAttr()->e10_.iType=vi.var_info;
				pps[pps.size()-2]->getInhAttr()->e10_.iAddr=context.getAddress(name);
			}
		}
		//如果声明为函数
		else if(context.isFun(name))
		{
			//错误报告
			string str="函数"+name+"调用非法。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//未声明的名字
		else
		{
			//错误报告
			string str="未声明的名字"+name+"。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1X_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e9': e10'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e9_.iValFlag=ps->e10_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e9_.iType=ps->e10_.sType;
		pps[pps.size()-2]->getInhAttr()->e9_.iAddr=ps->e10_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e9_.ipTrueList=ps->e10_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e9_.ipFalseList=ps->e10_.spFalseList;

		//赋空指针
		ps->e10_.spTrueList=0;
		ps->e10_.spFalseList=0;
	}
	static void act_T1X_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e8': e9'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e8_.iValFlag=ps->e9_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e8_.iType=ps->e9_.sType;
		pps[pps.size()-2]->getInhAttr()->e8_.iAddr=ps->e9_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e8_.ipTrueList=ps->e9_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e8_.ipFalseList=ps->e9_.spFalseList;

		//赋空指针
		ps->e9_.spTrueList=0;
		ps->e9_.spFalseList=0;
	}
	static void act_T1X_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e7': e8'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=ps->e8_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e7_.iType=ps->e8_.sType;
		pps[pps.size()-2]->getInhAttr()->e7_.iAddr=ps->e8_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e7_.ipTrueList=ps->e8_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e7_.ipFalseList=ps->e8_.spFalseList;

		//赋空指针
		ps->e8_.spTrueList=0;
		ps->e8_.spFalseList=0;
	}
	static void act_T1X_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e6': e7'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7_.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7_.spFalseList;

		//赋空指针
		ps->e7_.spTrueList=0;
		ps->e7_.spFalseList=0;
	}
	static void act_T1X_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e5': e6'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//赋空指针
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T1X_S6(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e4': e5'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//赋空指针
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T1X_S7(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//赋空指针
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T1X_S8(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//赋空指针
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T1X_S9(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的T1属性: e2'(control flow->value)
		pps[pps.size()-2]->getSynAttr()->T1.sValFlag=ps->e2_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->T1.sType=ps->e2_.sType;
		pps[pps.size()-2]->getSynAttr()->T1.sAddr=ps->e2_.sAddr;
		if(ps->e2_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->T1.spTrueList->swap(*(ps->e2_.spTrueList));
		if(ps->e2_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->T1.spFalseList->swap(*(ps->e2_.spFalseList));
	}

	static void act_T1Y_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//获取id词素
		const string name(*(pi->T1.iLexime));

		//如果声明为变量/数组
		if(context.isVar(name))
		{
			//获取变量/数组信息
			AllocInfo const &vi=*context.getAllocInfo(name);

			//如果声明为数组
			if(vi.var_info.is_array)
			{
				//错误报告
				string str="数组"+name+"不能作为操作数参与 +,- 运算。";

				//追加到记录
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//传递id属性
				pps[pps.size()-2]->getInhAttr()->e11_.iValFlag=true;
				pps[pps.size()-2]->getInhAttr()->e11_.iType=vi.var_info;
				pps[pps.size()-2]->getInhAttr()->e11_.iAddr=context.getAddress(name);
			}
		}
		//如果声明为函数
		else if(context.isFun(name))
		{
			//错误报告
			string str="函数"+name+"调用非法。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//未声明的名字
		else
		{
			//错误报告
			string str="未声明的名字"+name+"。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1Y_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e10': e11'(value->value)
		pps[pps.size()-2]->getInhAttr()->e10_.iValFlag=ps->e11_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e10_.iType=ps->e11_.sType;
		pps[pps.size()-2]->getInhAttr()->e10_.iAddr=ps->e11_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e10_.ipTrueList=ps->e11_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e10_.ipFalseList=ps->e11_.spFalseList;

		//赋空指针
		ps->e11_.spTrueList=0;
		ps->e11_.spFalseList=0;
	}
	static void act_T1Y_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e9': e10'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e9_.iValFlag=ps->e10_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e9_.iType=ps->e10_.sType;
		pps[pps.size()-2]->getInhAttr()->e9_.iAddr=ps->e10_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e9_.ipTrueList=ps->e10_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e9_.ipFalseList=ps->e10_.spFalseList;

		//赋空指针
		ps->e10_.spTrueList=0;
		ps->e10_.spFalseList=0;
	}
	static void act_T1Y_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e8': e9'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e8_.iValFlag=ps->e9_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e8_.iType=ps->e9_.sType;
		pps[pps.size()-2]->getInhAttr()->e8_.iAddr=ps->e9_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e8_.ipTrueList=ps->e9_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e8_.ipFalseList=ps->e9_.spFalseList;

		//赋空指针
		ps->e9_.spTrueList=0;
		ps->e9_.spFalseList=0;
	}
	static void act_T1Y_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e7': e8'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=ps->e8_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e7_.iType=ps->e8_.sType;
		pps[pps.size()-2]->getInhAttr()->e7_.iAddr=ps->e8_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e7_.ipTrueList=ps->e8_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e7_.ipFalseList=ps->e8_.spFalseList;

		//赋空指针
		ps->e8_.spTrueList=0;
		ps->e8_.spFalseList=0;
	}
	static void act_T1Y_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e6': e7'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7_.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7_.spFalseList;

		//赋空指针
		ps->e7_.spTrueList=0;
		ps->e7_.spFalseList=0;
	}
	static void act_T1Y_S6(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e5': e6'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//赋空指针
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T1Y_S7(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e4': e5'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//赋空指针
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T1Y_S8(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//赋空指针
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T1Y_S9(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//赋空指针
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T1Y_S10(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的T1属性: e2'(control flow->value)
		pps[pps.size()-2]->getSynAttr()->T1.sValFlag=ps->e2_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->T1.sType=ps->e2_.sType;
		pps[pps.size()-2]->getSynAttr()->T1.sAddr=ps->e2_.sAddr;
		if(ps->e2_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->T1.spTrueList->swap(*(ps->e2_.spTrueList));
		if(ps->e2_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->T1.spFalseList->swap(*(ps->e2_.spFalseList));
	}

	static void act_T1Z_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//获取id词素
		const string name(*(pi->T1.iLexime));

		//如果声明为变量/数组
		if(context.isVar(name))
		{
			//获取变量/数组信息
			AllocInfo const &vi=*context.getAllocInfo(name);

			//如果声明为数组
			if(vi.var_info.is_array)
			{
				//错误报告
				string str="数组"+name+"不能作为操作数参与 *,/,% 运算。";

				//追加到记录
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//传递id属性
				pps[pps.size()-2]->getInhAttr()->e12_.iValFlag=true;
				pps[pps.size()-2]->getInhAttr()->e12_.iType=vi.var_info;
				pps[pps.size()-2]->getInhAttr()->e12_.iAddr=context.getAddress(name);
			}
		}
		//如果声明为函数
		else if(context.isFun(name))
		{
			//错误报告
			string str="函数"+name+"调用非法。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//未声明的名字
		else
		{
			//错误报告
			string str="未声明的名字"+name+"。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1Z_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e11': e12'(value->value)
		pps[pps.size()-2]->getInhAttr()->e11_.iValFlag=ps->e12_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e11_.iType=ps->e12_.sType;
		pps[pps.size()-2]->getInhAttr()->e11_.iAddr=ps->e12_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e11_.ipTrueList=ps->e12_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e11_.ipFalseList=ps->e12_.spFalseList;

		//赋空指针
		ps->e12_.spTrueList=0;
		ps->e12_.spFalseList=0;
	}
	static void act_T1Z_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e10': e11'(value->value)
		pps[pps.size()-2]->getInhAttr()->e10_.iValFlag=ps->e11_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e10_.iType=ps->e11_.sType;
		pps[pps.size()-2]->getInhAttr()->e10_.iAddr=ps->e11_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e10_.ipTrueList=ps->e11_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e10_.ipFalseList=ps->e11_.spFalseList;

		//赋空指针
		ps->e11_.spTrueList=0;
		ps->e11_.spFalseList=0;
	}
	static void act_T1Z_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e9': e10'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e9_.iValFlag=ps->e10_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e9_.iType=ps->e10_.sType;
		pps[pps.size()-2]->getInhAttr()->e9_.iAddr=ps->e10_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e9_.ipTrueList=ps->e10_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e9_.ipFalseList=ps->e10_.spFalseList;

		//赋空指针
		ps->e10_.spTrueList=0;
		ps->e10_.spFalseList=0;
	}
	static void act_T1Z_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e8': e9'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e8_.iValFlag=ps->e9_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e8_.iType=ps->e9_.sType;
		pps[pps.size()-2]->getInhAttr()->e8_.iAddr=ps->e9_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e8_.ipTrueList=ps->e9_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e8_.ipFalseList=ps->e9_.spFalseList;

		//赋空指针
		ps->e9_.spTrueList=0;
		ps->e9_.spFalseList=0;
	}
	static void act_T1Z_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e7': e8'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=ps->e8_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e7_.iType=ps->e8_.sType;
		pps[pps.size()-2]->getInhAttr()->e7_.iAddr=ps->e8_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e7_.ipTrueList=ps->e8_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e7_.ipFalseList=ps->e8_.spFalseList;

		//赋空指针
		ps->e8_.spTrueList=0;
		ps->e8_.spFalseList=0;
	}
	static void act_T1Z_S6(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e6': e7'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7_.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7_.spFalseList;

		//赋空指针
		ps->e7_.spTrueList=0;
		ps->e7_.spFalseList=0;
	}
	static void act_T1Z_S7(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e5': e6'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//赋空指针
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T1Z_S8(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e4': e5'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//赋空指针
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T1Z_S9(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//赋空指针
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T1Z_S10(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//赋空指针
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T1Z_S11(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的T1属性: e2'(control flow->value)
		pps[pps.size()-2]->getSynAttr()->T1.sValFlag=ps->e2_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->T1.sType=ps->e2_.sType;
		pps[pps.size()-2]->getSynAttr()->T1.sAddr=ps->e2_.sAddr;
		if(ps->e2_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->T1.spTrueList->swap(*(ps->e2_.spTrueList));
		if(ps->e2_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->T1.spFalseList->swap(*(ps->e2_.spFalseList));
	}

	static void act_T1A1_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//获取id词素
		const string name(*(pi->T1.iLexime));

		//如果声明为变量/数组
		if(context.isVar(name))
		{
			//计算S后面的T1属性:数组仅仅可以作为实参传递给函数
			pps[pps.size()-2]->getSynAttr()->T1.sValFlag=true;	
			pps[pps.size()-2]->getSynAttr()->T1.sType=context.getAllocInfo(name)->var_info;
			pps[pps.size()-2]->getSynAttr()->T1.sAddr=context.getAddress(name);
		}
		//如果声明为函数
		else if(context.isFun(name))
		{
			//错误报告
			string str="函数"+name+"调用非法。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//未声明的名字
		else
		{
			//错误报告
			string str="未声明的名字"+name+"。";

			//追加到记录
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}

	static void act_T2A_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		AllocInfo const* pai=context.getAllocInfo(*(pi->T2.iLexime));

		//如果数组已声明
		if(pai)
		{
			////计算A后面的T2属性:
			//pps[pps.size()-2]->getSynAttr()->T2.sValFlag=true;
			//pps[pps.size()-2]->getSynAttr()->T2.sType.type=pai->var_info.type;
			//pps[pps.size()-2]->getSynAttr()->T2.sType.is_array=false;
			//Address temp_addr=context.Temp(pps[pps.size()-2]->getSynAttr()->T2.sType,pi->T2.iSection);
			//pps[pps.size()-2]->getSynAttr()->T2.sAddr=temp_addr;

			//传递给后面的T5
			pps[pps.size()-2]->getInhAttr()->T5.iType.type=pai->var_info.type;
			pps[pps.size()-2]->getInhAttr()->T5.iType.is_array=false;
			Address temp_addr=context.Temp(pps[pps.size()-2]->getInhAttr()->T5.iType,pi->T2.iSection);
			pps[pps.size()-2]->getInhAttr()->T5.iAddr=temp_addr;

			//获取数组地址
			Address array_addr=context.getAddress(*(pi->T2.iLexime));

			//为后缀++生成指令代码
			context.Gen(op_read_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//取值
			context.Gen(op_add,temp_addr,context.getAddress(1),temp_addr,pi->T2.iSection);	//累加
			context.Gen(op_write_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//写回
			context.Gen(op_sub,temp_addr,context.getAddress(1),temp_addr,pi->T2.iSection);	//复原
		}
	}
	static void act_T2B_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		AllocInfo const* pai=context.getAllocInfo(*(pi->T2.iLexime));

		//如果数组已声明
		if(pai)
		{
			////计算A后面的T2属性:
			//pps[pps.size()-2]->getSynAttr()->T2.sValFlag=true;
			//pps[pps.size()-2]->getSynAttr()->T2.sType.type=pai->var_info.type;
			//pps[pps.size()-2]->getSynAttr()->T2.sType.is_array=false;
			//Address temp_addr=context.Temp(pps[pps.size()-2]->getSynAttr()->T2.sType,pi->T2.iSection);
			//pps[pps.size()-2]->getSynAttr()->T2.sAddr=temp_addr;

			//传递给后面的T5
			pps[pps.size()-2]->getInhAttr()->T5.iType.type=pai->var_info.type;
			pps[pps.size()-2]->getInhAttr()->T5.iType.is_array=false;
			Address temp_addr=context.Temp(pps[pps.size()-2]->getInhAttr()->T5.iType,pi->T2.iSection);
			pps[pps.size()-2]->getInhAttr()->T5.iAddr=temp_addr;

			//获取数组地址
			Address array_addr=context.getAddress(*(pi->T2.iLexime));

			//为后缀--生成指令代码
			context.Gen(op_read_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//取值
			context.Gen(op_sub,temp_addr,context.getAddress(1),temp_addr,pi->T2.iSection);	//递减
			context.Gen(op_write_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//写回
			context.Gen(op_add,temp_addr,context.getAddress(1),temp_addr,pi->T2.iSection);	//复原
		}
	}

	static void act_T2C_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Temp_Var *pt=pps.back()->getTempVar();

		//op属性传递给S
		pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
	}
	static void act_T2C_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//获取id词素
		const string name(*(pi->T2.iLexime));

		//转换成value
		ControlFlow2Value(context,ps,pi->T2.iSection);

		//如果类型可计算
		if(Computable(ps->e1.sType))
		{
			AllocInfo const* pai=context.getAllocInfo(name);

			//如果数组已声明
			if(pai)
			{
				//计算S后面的T2属性
				pps[pps.size()-2]->getSynAttr()->T2.sValFlag=true;
				pps[pps.size()-2]->getSynAttr()->T2.sType.type=pai->var_info.type;
				pps[pps.size()-2]->getSynAttr()->T2.sType.is_array=false;
				Address temp_addr=context.Temp(pps[pps.size()-2]->getSynAttr()->T2.sType,pi->T2.iSection);
				pps[pps.size()-2]->getSynAttr()->T2.sAddr=temp_addr;

				//获取数组地址
				Address array_addr=context.getAddress(name);

				//生成指令代码
				context.Gen(op_assign,temp_addr,ps->e1.sAddr,pi->T2.iSection);	//赋值给临时变量
				context.Gen(op_write_array,array_addr,pi->T2.iAddr,ps->e1.sAddr,pi->T2.iSection);	//赋值给数组元素
			}
		}
		else 
		{
			//错误报告
			string str="= 右边表达式类型错误。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_T2D_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//获取id词素
		const string name(*(pi->T2.iLexime));

		//转换成value
		ControlFlow2Value(context,ps,pi->T2.iSection);

		//如果类型可计算
		if(Computable(ps->e1.sType))
		{
			AllocInfo const* pai=context.getAllocInfo(name);

			//如果数组已声明
			if(pai)
			{
				//计算S后面的T2属性
				pps[pps.size()-2]->getSynAttr()->T2.sValFlag=true;
				pps[pps.size()-2]->getSynAttr()->T2.sType.type=pai->var_info.type;
				pps[pps.size()-2]->getSynAttr()->T2.sType.is_array=false;
				Address temp_addr=context.Temp(pps[pps.size()-2]->getSynAttr()->T2.sType,pi->T2.iSection);
				pps[pps.size()-2]->getSynAttr()->T2.sAddr=temp_addr;

				//获取数组地址
				Address array_addr=context.getAddress(name);

				//生成指令代码
				context.Gen(op_read_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//取值
				context.Gen(op_mul,temp_addr,ps->e1.sAddr,temp_addr,pi->T2.iSection);			// *
				context.Gen(op_write_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//写回
			}
		}
		else
		{
			//错误报告
			string str="*= 右边表达式类型错误。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_T2E_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//获取id词素
		const string name(*(pi->T2.iLexime));

		//转换成value
		ControlFlow2Value(context,ps,pi->T2.iSection);

		//如果类型可计算
		if(Computable(ps->e1.sType))
		{
			AllocInfo const* pai=context.getAllocInfo(name);

			//如果数组已声明
			if(pai)
			{
				//计算S后面的T2属性
				pps[pps.size()-2]->getSynAttr()->T2.sValFlag=true;
				pps[pps.size()-2]->getSynAttr()->T2.sType.type=pai->var_info.type;
				pps[pps.size()-2]->getSynAttr()->T2.sType.is_array=false;
				Address temp_addr=context.Temp(pps[pps.size()-2]->getSynAttr()->T2.sType,pi->T2.iSection);
				pps[pps.size()-2]->getSynAttr()->T2.sAddr=temp_addr;

				//获取数组地址
				Address array_addr=context.getAddress(name);

				//生成指令代码
				context.Gen(op_read_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//取值
				context.Gen(op_div,temp_addr,ps->e1.sAddr,temp_addr,pi->T2.iSection);			// /
				context.Gen(op_write_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//写回
			}
		}
		else
		{
			//错误报告
			string str="/= 右边表达式类型错误。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_T2F_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//获取id词素
		const string name(*(pi->T2.iLexime));

		//转换成value
		ControlFlow2Value(context,ps,pi->T2.iSection);

		//如果类型可计算
		if(Computable(ps->e1.sType))
		{
			AllocInfo const* pai=context.getAllocInfo(name);

			//如果数组已声明
			if(pai)
			{
				//计算S后面的T2属性
				pps[pps.size()-2]->getSynAttr()->T2.sValFlag=true;
				pps[pps.size()-2]->getSynAttr()->T2.sType.type=pai->var_info.type;
				pps[pps.size()-2]->getSynAttr()->T2.sType.is_array=false;
				Address temp_addr=context.Temp(pps[pps.size()-2]->getSynAttr()->T2.sType,pi->T2.iSection);
				pps[pps.size()-2]->getSynAttr()->T2.sAddr=temp_addr;

				//获取数组地址
				Address array_addr=context.getAddress(name);

				//生成指令代码
				context.Gen(op_read_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//取值
				context.Gen(op_mod,temp_addr,ps->e1.sAddr,temp_addr,pi->T2.iSection);			// %
				context.Gen(op_write_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//写回
			}
		}
		else
		{
			//错误报告
			string str="%= 右边表达式类型错误。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_T2G_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//获取id词素
		const string name(*(pi->T2.iLexime));

		//转换成value
		ControlFlow2Value(context,ps,pi->T2.iSection);

		//如果类型可计算
		if(Computable(ps->e1.sType))
		{
			AllocInfo const* pai=context.getAllocInfo(name);

			//如果数组已声明
			if(pai)
			{
				//计算S后面的T2属性
				pps[pps.size()-2]->getSynAttr()->T2.sValFlag=true;
				pps[pps.size()-2]->getSynAttr()->T2.sType.type=pai->var_info.type;
				pps[pps.size()-2]->getSynAttr()->T2.sType.is_array=false;
				Address temp_addr=context.Temp(pps[pps.size()-2]->getSynAttr()->T2.sType,pi->T2.iSection);
				pps[pps.size()-2]->getSynAttr()->T2.sAddr=temp_addr;

				//获取数组地址
				Address array_addr=context.getAddress(name);

				//生成指令代码
				context.Gen(op_read_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//取值
				context.Gen(op_add,temp_addr,ps->e1.sAddr,temp_addr,pi->T2.iSection);			// +
				context.Gen(op_write_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//写回
			}
		}
		else
		{
			//错误报告
			string str="+= 右边表达式类型错误。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_T2H_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//获取id词素
		const string name(*(pi->T2.iLexime));

		//转换成value
		ControlFlow2Value(context,ps,pi->T2.iSection);

		//如果类型可计算
		if(Computable(ps->e1.sType))
		{
			AllocInfo const* pai=context.getAllocInfo(name);

			//如果数组已声明
			if(pai)
			{
				//计算S后面的T2属性
				pps[pps.size()-2]->getSynAttr()->T2.sValFlag=true;
				pps[pps.size()-2]->getSynAttr()->T2.sType.type=pai->var_info.type;
				pps[pps.size()-2]->getSynAttr()->T2.sType.is_array=false;
				Address temp_addr=context.Temp(pps[pps.size()-2]->getSynAttr()->T2.sType,pi->T2.iSection);
				pps[pps.size()-2]->getSynAttr()->T2.sAddr=temp_addr;

				//获取数组地址
				Address array_addr=context.getAddress(name);

				//生成指令代码
				context.Gen(op_read_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//取值
				context.Gen(op_sub,temp_addr,ps->e1.sAddr,temp_addr,pi->T2.iSection);			// -
				context.Gen(op_write_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//写回
			}
		}
		else
		{
			//错误报告
			string str="-= 右边表达式类型错误。";

			//追加到记录
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_T2I_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//获取id词素
		const string name(*(pi->T2.iLexime));

		//获取变量/数组信息
		AllocInfo const *pai=context.getAllocInfo(name);

		//如果数组已声明
		if(pai)
		{
			//如果左操作数类型是整型
			if(isInteger(pai->var_info.type))
			{
				//转换成value
				ControlFlow2Value(context,ps,pi->T2.iSection);

				if(ps->e1.sType.is_array)
				{
					//错误报告
					string str="<<= 右操作数不能是数组。";

					//追加到记录
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
				//如果右操作数类型是整型
				else if(isInteger(ps->e1.sType.type))
				{
					//计算S后面的T2属性
					pps[pps.size()-2]->getSynAttr()->T2.sValFlag=true;
					pps[pps.size()-2]->getSynAttr()->T2.sType.type=pai->var_info.type;
					pps[pps.size()-2]->getSynAttr()->T2.sType.is_array=false;
					Address temp_addr=context.Temp(pps[pps.size()-2]->getSynAttr()->T2.sType,pi->T2.iSection);
					pps[pps.size()-2]->getSynAttr()->T2.sAddr=temp_addr;

					//获取数组地址
					Address array_addr=context.getAddress(name);

					//生成指令代码
					context.Gen(op_read_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//取值
					context.Gen(op_lsht,temp_addr,ps->e1.sAddr,temp_addr,pi->T2.iSection);			// <<
					context.Gen(op_write_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//写回
				}
				else
				{
					//错误报告
					string str="<<= 右操作数类型必须是整型。";

					//追加到记录
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
			}
			else
			{
				//错误报告
				string str="<<= 左操作数类型必须是整型。";

				//追加到记录
				err_record.insert(make_pair(pt->op_line.tLine,str));
			}
		}
	}
	static void act_T2J_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//获取id词素
		const string name(*(pi->T2.iLexime));

		//获取变量/数组信息
		AllocInfo const *pai=context.getAllocInfo(name);

		//如果数组已声明
		if(pai)
		{
			//如果左操作数类型是整型
			if(isInteger(pai->var_info.type))
			{
				//转换成value
				ControlFlow2Value(context,ps,pi->T2.iSection);

				if(ps->e1.sType.is_array)
				{
					//错误报告
					string str=">>= 右操作数不能是数组。";

					//追加到记录
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
				//如果右操作数类型是整型
				else if(isInteger(ps->e1.sType.type))
				{
					//计算S后面的T2属性
					pps[pps.size()-2]->getSynAttr()->T2.sValFlag=true;
					pps[pps.size()-2]->getSynAttr()->T2.sType.type=pai->var_info.type;
					pps[pps.size()-2]->getSynAttr()->T2.sType.is_array=false;
					Address temp_addr=context.Temp(pps[pps.size()-2]->getSynAttr()->T2.sType,pi->T2.iSection);
					pps[pps.size()-2]->getSynAttr()->T2.sAddr=temp_addr;

					//获取数组地址
					Address array_addr=context.getAddress(name);

					//生成指令代码
					context.Gen(op_read_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//取值
					context.Gen(op_rsht,temp_addr,ps->e1.sAddr,temp_addr,pi->T2.iSection);			// >>
					context.Gen(op_write_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//写回
				}
				else
				{
					//错误报告
					string str=">>= 右操作数类型必须是整型。";

					//追加到记录
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
			}
			else
			{
				//错误报告
				string str=">>= 左操作数类型必须是整型。";

				//追加到记录
				err_record.insert(make_pair(pt->op_line.tLine,str));
			}
		}
	}
	static void act_T2K_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//获取id词素
		const string name(*(pi->T2.iLexime));

		//获取变量/数组信息
		AllocInfo const *pai=context.getAllocInfo(name);

		//如果数组已声明
		if(pai)
		{
			//如果左操作数类型是整型
			if(isInteger(pai->var_info.type))
			{
				//转换成value
				ControlFlow2Value(context,ps,pi->T2.iSection);

				if(ps->e1.sType.is_array)
				{
					//错误报告
					string str="&= 右操作数不能是数组。";

					//追加到记录
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
				//如果右操作数类型是整型
				else if(isInteger(ps->e1.sType.type))
				{
					//计算S后面的T2属性
					pps[pps.size()-2]->getSynAttr()->T2.sValFlag=true;
					pps[pps.size()-2]->getSynAttr()->T2.sType.type=pai->var_info.type;
					pps[pps.size()-2]->getSynAttr()->T2.sType.is_array=false;
					Address temp_addr=context.Temp(pps[pps.size()-2]->getSynAttr()->T2.sType,pi->T2.iSection);
					pps[pps.size()-2]->getSynAttr()->T2.sAddr=temp_addr;

					//获取数组地址
					Address array_addr=context.getAddress(name);

					//生成指令代码
					context.Gen(op_read_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//取值
					context.Gen(op_bit_and,temp_addr,ps->e1.sAddr,temp_addr,pi->T2.iSection);		// &
					context.Gen(op_write_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//写回
				}
				else
				{
					//错误报告
					string str="&= 右操作数类型必须是整型。";

					//追加到记录
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
			}
			else
			{
				//错误报告
				string str="&= 左操作数类型必须是整型。";

				//追加到记录
				err_record.insert(make_pair(pt->op_line.tLine,str));
			}
		}
	}
	static void act_T2L_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//获取id词素
		const string name(*(pi->T2.iLexime));

		//获取变量/数组信息
		AllocInfo const *pai=context.getAllocInfo(name);

		//如果数组已声明
		if(pai)
		{
			//如果左操作数类型是整型
			if(isInteger(pai->var_info.type))
			{
				//转换成value
				ControlFlow2Value(context,ps,pi->T2.iSection);

				if(ps->e1.sType.is_array)
				{
					//错误报告
					string str="|= 右操作数不能是数组。";

					//追加到记录
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
				//如果右操作数类型是整型
				else if(isInteger(ps->e1.sType.type))
				{
					//计算S后面的T2属性
					pps[pps.size()-2]->getSynAttr()->T2.sValFlag=true;
					pps[pps.size()-2]->getSynAttr()->T2.sType.type=pai->var_info.type;
					pps[pps.size()-2]->getSynAttr()->T2.sType.is_array=false;
					Address temp_addr=context.Temp(pps[pps.size()-2]->getSynAttr()->T2.sType,pi->T2.iSection);
					pps[pps.size()-2]->getSynAttr()->T2.sAddr=temp_addr;

					//获取数组地址
					Address array_addr=context.getAddress(name);

					//生成指令代码
					context.Gen(op_read_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//取值
					context.Gen(op_bit_or,temp_addr,ps->e1.sAddr,temp_addr,pi->T2.iSection);		// |
					context.Gen(op_write_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//写回
				}
				else
				{
					//错误报告
					string str="|= 右操作数类型必须是整型。";

					//追加到记录
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
			}
			else
			{
				//错误报告
				string str="|= 左操作数类型必须是整型。";

				//追加到记录
				err_record.insert(make_pair(pt->op_line.tLine,str));
			}
		}
	}
	static void act_T2M_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//获取id词素
		const string name(*(pi->T2.iLexime));

		//获取变量/数组信息
		AllocInfo const *pai=context.getAllocInfo(name);

		//如果数组已声明
		if(pai)
		{
			//如果左操作数类型是整型
			if(isInteger(pai->var_info.type))
			{
				//转换成value
				ControlFlow2Value(context,ps,pi->T2.iSection);

				if(ps->e1.sType.is_array)
				{
					//错误报告
					string str="^= 右操作数不能是数组。";

					//追加到记录
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
				//如果右操作数类型是整型
				else if(isInteger(ps->e1.sType.type))
				{
					//计算S后面的T2属性
					pps[pps.size()-2]->getSynAttr()->T2.sValFlag=true;
					pps[pps.size()-2]->getSynAttr()->T2.sType.type=pai->var_info.type;
					pps[pps.size()-2]->getSynAttr()->T2.sType.is_array=false;
					Address temp_addr=context.Temp(pps[pps.size()-2]->getSynAttr()->T2.sType,pi->T2.iSection);
					pps[pps.size()-2]->getSynAttr()->T2.sAddr=temp_addr;

					//获取数组地址
					Address array_addr=context.getAddress(name);

					//生成指令代码
					context.Gen(op_read_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//取值
					context.Gen(op_bit_xor,temp_addr,ps->e1.sAddr,temp_addr,pi->T2.iSection);		// ^
					context.Gen(op_write_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//写回
				}
				else
				{
					//错误报告
					string str="^= 右操作数类型必须是整型。";

					//追加到记录
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
			}
			else
			{
				//错误报告
				string str="^= 左操作数类型必须是整型。";

				//追加到记录
				err_record.insert(make_pair(pt->op_line.tLine,str));
			}
		}
	}

	static void act_T2N_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//获取id词素
		const string name(*(pi->T2.iLexime));

		//获取变量/数组信息
		AllocInfo const *pai=context.getAllocInfo(name);

		//如果数组已声明
		if(pai)
		{
			//传递id属性并生成临时变量
			pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e2_.iType.type=pai->var_info.type;
			pps[pps.size()-2]->getInhAttr()->e2_.iType.is_array=false;
			Address temp_addr=context.Temp(pps[pps.size()-2]->getInhAttr()->e2_.iType,pi->T2.iSection);
			pps[pps.size()-2]->getInhAttr()->e2_.iAddr=temp_addr;

			//生成访问数组元素的指令
			context.Gen(op_read_array,context.getAddress(name),pi->T2.iAddr,temp_addr);
		}
	}
	static void act_T2N_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的T2属性: e2'(control flow->value)
		pps[pps.size()-2]->getSynAttr()->T2.sValFlag=ps->e2_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->T2.sType=ps->e2_.sType;
		pps[pps.size()-2]->getSynAttr()->T2.sAddr=ps->e2_.sAddr;
		if(ps->e2_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->T2.spTrueList->swap(*(ps->e2_.spTrueList));
		if(ps->e2_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->T2.spFalseList->swap(*(ps->e2_.spFalseList));
	}

	static void act_T2O_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//获取id词素
		const string name(*(pi->T2.iLexime));

		//获取变量/数组信息
		AllocInfo const *pai=context.getAllocInfo(name);

		//如果数组已声明
		if(pai)
		{
			//传递id属性并生成临时变量
			pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e3_.iType.type=pai->var_info.type;
			pps[pps.size()-2]->getInhAttr()->e3_.iType.is_array=false;
			Address temp_addr=context.Temp(pps[pps.size()-2]->getInhAttr()->e3_.iType,pi->T2.iSection);
			pps[pps.size()-2]->getInhAttr()->e3_.iAddr=temp_addr;

			//生成访问数组元素的指令
			context.Gen(op_read_array,context.getAddress(name),pi->T2.iAddr,temp_addr);
		}
	}
	static void act_T2O_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//赋空指针
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T2O_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的T2属性: e2'(control flow->value)
		pps[pps.size()-2]->getSynAttr()->T2.sValFlag=ps->e2_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->T2.sType=ps->e2_.sType;
		pps[pps.size()-2]->getSynAttr()->T2.sAddr=ps->e2_.sAddr;
		if(ps->e2_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->T2.spTrueList->swap(*(ps->e2_.spTrueList));
		if(ps->e2_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->T2.spFalseList->swap(*(ps->e2_.spFalseList));
	}

	static void act_T2P_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//获取id词素
		const string name(*(pi->T2.iLexime));

		//获取变量/数组信息
		AllocInfo const *pai=context.getAllocInfo(name);

		//如果数组已声明
		if(pai)
		{
			//传递id属性并生成临时变量
			pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e4_.iType.type=pai->var_info.type;
			pps[pps.size()-2]->getInhAttr()->e4_.iType.is_array=false;
			Address temp_addr=context.Temp(pps[pps.size()-2]->getInhAttr()->e4_.iType,pi->T2.iSection);
			pps[pps.size()-2]->getInhAttr()->e4_.iAddr=temp_addr;

			//生成访问数组元素的指令
			context.Gen(op_read_array,context.getAddress(name),pi->T2.iAddr,temp_addr);
		}
	}
	static void act_T2P_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//赋空指针
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T2P_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//赋空指针
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T2P_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的T2属性: e2'(control flow->value)
		pps[pps.size()-2]->getSynAttr()->T2.sValFlag=ps->e2_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->T2.sType=ps->e2_.sType;
		pps[pps.size()-2]->getSynAttr()->T2.sAddr=ps->e2_.sAddr;
		if(ps->e2_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->T2.spTrueList->swap(*(ps->e2_.spTrueList));
		if(ps->e2_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->T2.spFalseList->swap(*(ps->e2_.spFalseList));
	}

	static void act_T2Q_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//获取id词素
		const string name(*(pi->T2.iLexime));

		//获取变量/数组信息
		AllocInfo const *pai=context.getAllocInfo(name);

		//如果数组已声明
		if(pai)
		{
			//传递id属性并生成临时变量
			pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e5_.iType.type=pai->var_info.type;
			pps[pps.size()-2]->getInhAttr()->e5_.iType.is_array=false;
			Address temp_addr=context.Temp(pps[pps.size()-2]->getInhAttr()->e5_.iType,pi->T2.iSection);
			pps[pps.size()-2]->getInhAttr()->e5_.iAddr=temp_addr;

			//生成访问数组元素的指令
			context.Gen(op_read_array,context.getAddress(name),pi->T2.iAddr,temp_addr);
		}
	}
	static void act_T2Q_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e4': e5'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//赋空指针
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T2Q_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//赋空指针
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T2Q_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//赋空指针
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T2Q_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的T2属性: e2'(control flow->value)
		pps[pps.size()-2]->getSynAttr()->T2.sValFlag=ps->e2_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->T2.sType=ps->e2_.sType;
		pps[pps.size()-2]->getSynAttr()->T2.sAddr=ps->e2_.sAddr;
		if(ps->e2_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->T2.spTrueList->swap(*(ps->e2_.spTrueList));
		if(ps->e2_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->T2.spFalseList->swap(*(ps->e2_.spFalseList));
	}

	static void act_T2R_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//获取id词素
		const string name(*(pi->T2.iLexime));

		//获取变量/数组信息
		AllocInfo const *pai=context.getAllocInfo(name);

		//如果数组已声明
		if(pai)
		{
			//传递id属性并生成临时变量
			pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e6_.iType.type=pai->var_info.type;
			pps[pps.size()-2]->getInhAttr()->e6_.iType.is_array=false;
			Address temp_addr=context.Temp(pps[pps.size()-2]->getInhAttr()->e6_.iType,pi->T2.iSection);
			pps[pps.size()-2]->getInhAttr()->e6_.iAddr=temp_addr;

			//生成访问数组元素的指令
			context.Gen(op_read_array,context.getAddress(name),pi->T2.iAddr,temp_addr);
		}
	}
	static void act_T2R_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e5': e6'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//赋空指针
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T2R_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e4': e5'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//赋空指针
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T2R_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//赋空指针
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T2R_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//赋空指针
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T2R_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的T2属性: e2'(control flow->value)
		pps[pps.size()-2]->getSynAttr()->T2.sValFlag=ps->e2_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->T2.sType=ps->e2_.sType;
		pps[pps.size()-2]->getSynAttr()->T2.sAddr=ps->e2_.sAddr;
		if(ps->e2_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->T2.spTrueList->swap(*(ps->e2_.spTrueList));
		if(ps->e2_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->T2.spFalseList->swap(*(ps->e2_.spFalseList));
	}

	static void act_T2S_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//获取id词素
		const string name(*(pi->T2.iLexime));

		//获取变量/数组信息
		AllocInfo const *pai=context.getAllocInfo(name);

		//如果数组已声明
		if(pai)
		{
			//传递id属性并生成临时变量
			pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e7_.iType.type=pai->var_info.type;
			pps[pps.size()-2]->getInhAttr()->e7_.iType.is_array=false;
			Address temp_addr=context.Temp(pps[pps.size()-2]->getInhAttr()->e7_.iType,pi->T2.iSection);
			pps[pps.size()-2]->getInhAttr()->e7_.iAddr=temp_addr;

			//生成访问数组元素的指令
			context.Gen(op_read_array,context.getAddress(name),pi->T2.iAddr,temp_addr);
		}
	}
	static void act_T2S_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e6': e7'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7_.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7_.spFalseList;

		//赋空指针
		ps->e7_.spTrueList=0;
		ps->e7_.spFalseList=0;
	}
	static void act_T2S_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e5': e6'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//赋空指针
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T2S_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e4': e5'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//赋空指针
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T2S_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//赋空指针
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T2S_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//赋空指针
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T2S_S6(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的T2属性: e2'(control flow->value)
		pps[pps.size()-2]->getSynAttr()->T2.sValFlag=ps->e2_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->T2.sType=ps->e2_.sType;
		pps[pps.size()-2]->getSynAttr()->T2.sAddr=ps->e2_.sAddr;
		if(ps->e2_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->T2.spTrueList->swap(*(ps->e2_.spTrueList));
		if(ps->e2_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->T2.spFalseList->swap(*(ps->e2_.spFalseList));
	}

	static void act_T2T_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//获取id词素
		const string name(*(pi->T2.iLexime));

		//获取变量/数组信息
		AllocInfo const *pai=context.getAllocInfo(name);

		//如果数组已声明
		if(pai)
		{
			//传递id属性并生成临时变量
			pps[pps.size()-2]->getInhAttr()->e8_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e8_.iType.type=pai->var_info.type;
			pps[pps.size()-2]->getInhAttr()->e8_.iType.is_array=false;
			Address temp_addr=context.Temp(pps[pps.size()-2]->getInhAttr()->e8_.iType,pi->T2.iSection);
			pps[pps.size()-2]->getInhAttr()->e8_.iAddr=temp_addr;

			//生成访问数组元素的指令
			context.Gen(op_read_array,context.getAddress(name),pi->T2.iAddr,temp_addr);
		}
	}
	static void act_T2T_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e7': e8'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=ps->e8_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e7_.iType=ps->e8_.sType;
		pps[pps.size()-2]->getInhAttr()->e7_.iAddr=ps->e8_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e7_.ipTrueList=ps->e8_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e7_.ipFalseList=ps->e8_.spFalseList;

		//赋空指针
		ps->e8_.spTrueList=0;
		ps->e8_.spFalseList=0;
	}
	static void act_T2T_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e6': e7'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7_.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7_.spFalseList;

		//赋空指针
		ps->e7_.spTrueList=0;
		ps->e7_.spFalseList=0;
	}
	static void act_T2T_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e5': e6'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//赋空指针
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T2T_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e4': e5'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//赋空指针
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T2T_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//赋空指针
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T2T_S6(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//赋空指针
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T2T_S7(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的T2属性: e2'(control flow->value)
		pps[pps.size()-2]->getSynAttr()->T2.sValFlag=ps->e2_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->T2.sType=ps->e2_.sType;
		pps[pps.size()-2]->getSynAttr()->T2.sAddr=ps->e2_.sAddr;
		if(ps->e2_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->T2.spTrueList->swap(*(ps->e2_.spTrueList));
		if(ps->e2_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->T2.spFalseList->swap(*(ps->e2_.spFalseList));
	}

	static void act_T2U_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();			
		
		//获取id词素
		const string name(*(pi->T2.iLexime));

		//获取变量/数组信息
		AllocInfo const *pai=context.getAllocInfo(name);

		//如果数组已声明
		if(pai)
		{
			//传递id属性并生成临时变量
			pps[pps.size()-2]->getInhAttr()->e9_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e9_.iType.type=pai->var_info.type;
			pps[pps.size()-2]->getInhAttr()->e9_.iType.is_array=false;
			Address temp_addr=context.Temp(pps[pps.size()-2]->getInhAttr()->e9_.iType,pi->T2.iSection);
			pps[pps.size()-2]->getInhAttr()->e9_.iAddr=temp_addr;

			//生成访问数组元素的指令
			context.Gen(op_read_array,context.getAddress(name),pi->T2.iAddr,temp_addr);
		}
	}
	static void act_T2U_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e8': e9'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e8_.iValFlag=ps->e9_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e8_.iType=ps->e9_.sType;
		pps[pps.size()-2]->getInhAttr()->e8_.iAddr=ps->e9_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e8_.ipTrueList=ps->e9_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e8_.ipFalseList=ps->e9_.spFalseList;

		//赋空指针
		ps->e9_.spTrueList=0;
		ps->e9_.spFalseList=0;
	}
	static void act_T2U_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e7': e8'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=ps->e8_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e7_.iType=ps->e8_.sType;
		pps[pps.size()-2]->getInhAttr()->e7_.iAddr=ps->e8_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e7_.ipTrueList=ps->e8_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e7_.ipFalseList=ps->e8_.spFalseList;

		//赋空指针
		ps->e8_.spTrueList=0;
		ps->e8_.spFalseList=0;
	}
	static void act_T2U_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e6': e7'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7_.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7_.spFalseList;

		//赋空指针
		ps->e7_.spTrueList=0;
		ps->e7_.spFalseList=0;
	}
	static void act_T2U_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e5': e6'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//赋空指针
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T2U_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e4': e5'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//赋空指针
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T2U_S6(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//赋空指针
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T2U_S7(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//赋空指针
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T2U_S8(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的T2属性: e2'(control flow->value)
		pps[pps.size()-2]->getSynAttr()->T2.sValFlag=ps->e2_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->T2.sType=ps->e2_.sType;
		pps[pps.size()-2]->getSynAttr()->T2.sAddr=ps->e2_.sAddr;
		if(ps->e2_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->T2.spTrueList->swap(*(ps->e2_.spTrueList));
		if(ps->e2_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->T2.spFalseList->swap(*(ps->e2_.spFalseList));
	}

	static void act_T2V_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//获取id词素
		const string name(*(pi->T2.iLexime));

		//获取变量/数组信息
		AllocInfo const *pai=context.getAllocInfo(name);

		//如果数组已声明
		if(pai)
		{
			//传递id属性并生成临时变量
			pps[pps.size()-2]->getInhAttr()->e10_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e10_.iType.type=pai->var_info.type;
			pps[pps.size()-2]->getInhAttr()->e10_.iType.is_array=false;
			Address temp_addr=context.Temp(pps[pps.size()-2]->getInhAttr()->e10_.iType,pi->T2.iSection);
			pps[pps.size()-2]->getInhAttr()->e10_.iAddr=temp_addr;

			//生成访问数组元素的指令
			context.Gen(op_read_array,context.getAddress(name),pi->T2.iAddr,temp_addr);
		}
	}
	static void act_T2V_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e9': e10'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e9_.iValFlag=ps->e10_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e9_.iType=ps->e10_.sType;
		pps[pps.size()-2]->getInhAttr()->e9_.iAddr=ps->e10_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e9_.ipTrueList=ps->e10_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e9_.ipFalseList=ps->e10_.spFalseList;

		//赋空指针
		ps->e10_.spTrueList=0;
		ps->e10_.spFalseList=0;
	}
	static void act_T2V_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e8': e9'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e8_.iValFlag=ps->e9_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e8_.iType=ps->e9_.sType;
		pps[pps.size()-2]->getInhAttr()->e8_.iAddr=ps->e9_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e8_.ipTrueList=ps->e9_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e8_.ipFalseList=ps->e9_.spFalseList;

		//赋空指针
		ps->e9_.spTrueList=0;
		ps->e9_.spFalseList=0;
	}
	static void act_T2V_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e7': e8'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=ps->e8_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e7_.iType=ps->e8_.sType;
		pps[pps.size()-2]->getInhAttr()->e7_.iAddr=ps->e8_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e7_.ipTrueList=ps->e8_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e7_.ipFalseList=ps->e8_.spFalseList;

		//赋空指针
		ps->e8_.spTrueList=0;
		ps->e8_.spFalseList=0;
	}
	static void act_T2V_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e6': e7'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7_.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7_.spFalseList;

		//赋空指针
		ps->e7_.spTrueList=0;
		ps->e7_.spFalseList=0;
	}
	static void act_T2V_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e5': e6'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//赋空指针
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T2V_S6(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e4': e5'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//赋空指针
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T2V_S7(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//赋空指针
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T2V_S8(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//赋空指针
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T2V_S9(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的T2属性: e2'(control flow->value)
		pps[pps.size()-2]->getSynAttr()->T2.sValFlag=ps->e2_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->T2.sType=ps->e2_.sType;
		pps[pps.size()-2]->getSynAttr()->T2.sAddr=ps->e2_.sAddr;
		if(ps->e2_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->T2.spTrueList->swap(*(ps->e2_.spTrueList));
		if(ps->e2_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->T2.spFalseList->swap(*(ps->e2_.spFalseList));
	}

	static void act_T2W_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//获取id词素
		const string name(*(pi->T2.iLexime));

		//获取变量/数组信息
		AllocInfo const *pai=context.getAllocInfo(name);

		//如果数组已声明
		if(pai)
		{
			//传递id属性并生成临时变量
			pps[pps.size()-2]->getInhAttr()->e11_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e11_.iType.type=pai->var_info.type;
			pps[pps.size()-2]->getInhAttr()->e11_.iType.is_array=false;
			Address temp_addr=context.Temp(pps[pps.size()-2]->getInhAttr()->e11_.iType,pi->T2.iSection);
			pps[pps.size()-2]->getInhAttr()->e11_.iAddr=temp_addr;

			//生成访问数组元素的指令
			context.Gen(op_read_array,context.getAddress(name),pi->T2.iAddr,temp_addr);
		}
	}
	static void act_T2W_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e10': e11'(value->value)
		pps[pps.size()-2]->getInhAttr()->e10_.iValFlag=ps->e11_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e10_.iType=ps->e11_.sType;
		pps[pps.size()-2]->getInhAttr()->e10_.iAddr=ps->e11_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e10_.ipTrueList=ps->e11_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e10_.ipFalseList=ps->e11_.spFalseList;

		//赋空指针
		ps->e11_.spTrueList=0;
		ps->e11_.spFalseList=0;
	}
	static void act_T2W_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e9': e10'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e9_.iValFlag=ps->e10_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e9_.iType=ps->e10_.sType;
		pps[pps.size()-2]->getInhAttr()->e9_.iAddr=ps->e10_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e9_.ipTrueList=ps->e10_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e9_.ipFalseList=ps->e10_.spFalseList;

		//赋空指针
		ps->e10_.spTrueList=0;
		ps->e10_.spFalseList=0;
	}
	static void act_T2W_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e8': e9'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e8_.iValFlag=ps->e9_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e8_.iType=ps->e9_.sType;
		pps[pps.size()-2]->getInhAttr()->e8_.iAddr=ps->e9_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e8_.ipTrueList=ps->e9_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e8_.ipFalseList=ps->e9_.spFalseList;

		//赋空指针
		ps->e9_.spTrueList=0;
		ps->e9_.spFalseList=0;
	}
	static void act_T2W_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e7': e8'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=ps->e8_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e7_.iType=ps->e8_.sType;
		pps[pps.size()-2]->getInhAttr()->e7_.iAddr=ps->e8_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e7_.ipTrueList=ps->e8_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e7_.ipFalseList=ps->e8_.spFalseList;

		//赋空指针
		ps->e8_.spTrueList=0;
		ps->e8_.spFalseList=0;
	}
	static void act_T2W_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e6': e7'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7_.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7_.spFalseList;

		//赋空指针
		ps->e7_.spTrueList=0;
		ps->e7_.spFalseList=0;
	}
	static void act_T2W_S6(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e5': e6'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//赋空指针
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T2W_S7(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e4': e5'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//赋空指针
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T2W_S8(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//赋空指针
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T2W_S9(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//赋空指针
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T2W_S10(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的T2属性: e2'(control flow->value)
		pps[pps.size()-2]->getSynAttr()->T2.sValFlag=ps->e2_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->T2.sType=ps->e2_.sType;
		pps[pps.size()-2]->getSynAttr()->T2.sAddr=ps->e2_.sAddr;
		if(ps->e2_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->T2.spTrueList->swap(*(ps->e2_.spTrueList));
		if(ps->e2_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->T2.spFalseList->swap(*(ps->e2_.spFalseList));
	}

	static void act_T2X_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//获取id词素
		const string name(*(pi->T2.iLexime));

		//获取变量/数组信息
		AllocInfo const *pai=context.getAllocInfo(name);

		//如果数组已声明
		if(pai)
		{
			//传递id属性并生成临时变量
			pps[pps.size()-2]->getInhAttr()->e12_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e12_.iType.type=pai->var_info.type;
			pps[pps.size()-2]->getInhAttr()->e12_.iType.is_array=false;
			Address temp_addr=context.Temp(pps[pps.size()-2]->getInhAttr()->e12_.iType,pi->T2.iSection);
			pps[pps.size()-2]->getInhAttr()->e12_.iAddr=temp_addr;

			//生成访问数组元素的指令
			context.Gen(op_read_array,context.getAddress(name),pi->T2.iAddr,temp_addr);
		}
	}
	static void act_T2X_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e11': e12'(value->value)
		pps[pps.size()-2]->getInhAttr()->e11_.iValFlag=ps->e12_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e11_.iType=ps->e12_.sType;
		pps[pps.size()-2]->getInhAttr()->e11_.iAddr=ps->e12_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e11_.ipTrueList=ps->e12_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e11_.ipFalseList=ps->e12_.spFalseList;

		//赋空指针
		ps->e12_.spTrueList=0;
		ps->e12_.spFalseList=0;
	}
	static void act_T2X_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e10': e11'(value->value)
		pps[pps.size()-2]->getInhAttr()->e10_.iValFlag=ps->e11_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e10_.iType=ps->e11_.sType;
		pps[pps.size()-2]->getInhAttr()->e10_.iAddr=ps->e11_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e10_.ipTrueList=ps->e11_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e10_.ipFalseList=ps->e11_.spFalseList;

		//赋空指针
		ps->e11_.spTrueList=0;
		ps->e11_.spFalseList=0;
	}
	static void act_T2X_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e9': e10'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e9_.iValFlag=ps->e10_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e9_.iType=ps->e10_.sType;
		pps[pps.size()-2]->getInhAttr()->e9_.iAddr=ps->e10_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e9_.ipTrueList=ps->e10_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e9_.ipFalseList=ps->e10_.spFalseList;

		//赋空指针
		ps->e10_.spTrueList=0;
		ps->e10_.spFalseList=0;
	}
	static void act_T2X_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e8': e9'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e8_.iValFlag=ps->e9_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e8_.iType=ps->e9_.sType;
		pps[pps.size()-2]->getInhAttr()->e8_.iAddr=ps->e9_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e8_.ipTrueList=ps->e9_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e8_.ipFalseList=ps->e9_.spFalseList;

		//赋空指针
		ps->e9_.spTrueList=0;
		ps->e9_.spFalseList=0;
	}
	static void act_T2X_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e7': e8'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=ps->e8_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e7_.iType=ps->e8_.sType;
		pps[pps.size()-2]->getInhAttr()->e7_.iAddr=ps->e8_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e7_.ipTrueList=ps->e8_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e7_.ipFalseList=ps->e8_.spFalseList;

		//赋空指针
		ps->e8_.spTrueList=0;
		ps->e8_.spFalseList=0;
	}
	static void act_T2X_S6(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e6': e7'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7_.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7_.spFalseList;

		//赋空指针
		ps->e7_.spTrueList=0;
		ps->e7_.spFalseList=0;
	}
	static void act_T2X_S7(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e5': e6'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//赋空指针
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T2X_S8(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e4': e5'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//赋空指针
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T2X_S9(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//赋空指针
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T2X_S10(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//赋空指针
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T2X_S11(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的T2属性: e2'(control flow->value)
		pps[pps.size()-2]->getSynAttr()->T2.sValFlag=ps->e2_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->T2.sType=ps->e2_.sType;
		pps[pps.size()-2]->getSynAttr()->T2.sAddr=ps->e2_.sAddr;
		if(ps->e2_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->T2.spTrueList->swap(*(ps->e2_.spTrueList));
		if(ps->e2_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->T2.spFalseList->swap(*(ps->e2_.spFalseList));
	}

	static void act_T2Y_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//获取变量/数组信息
		AllocInfo const *pai=context.getAllocInfo(*(pi->T2.iLexime));

		//如果数组已声明
		if(pai)
		{
			//计算A后面的T2属性:
			pps[pps.size()-2]->getSynAttr()->T2.sValFlag=true;
			pps[pps.size()-2]->getSynAttr()->T2.sType.type=pai->var_info.type;
			pps[pps.size()-2]->getSynAttr()->T2.sType.is_array=false;
			pps[pps.size()-2]->getSynAttr()->T2.sAddr=context.Temp(pps[pps.size()-2]->getSynAttr()->T2.sType,pi->T2.iSection);

			//为数组访问生成指令代码:本语言并没有lvalue和rvalue的概念(因为没有指针和取地址操作),所以并不需要返回数组元素的引用,只需返回值拷贝即可。
			context.Gen(op_read_array,context.getAddress(*(pi->T2.iLexime)),pi->T2.iAddr,pps[pps.size()-2]->getSynAttr()->T2.sAddr,pi->T2.iSection);	//取值
		}
	}

	static void act_T5_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的T1/T2属性: T5
		pps[pps.size()-2]->getSynAttr()->T1.sValFlag=ps->T5.sValFlag;
		pps[pps.size()-2]->getSynAttr()->T1.sType=ps->T5.sType;
		pps[pps.size()-2]->getSynAttr()->T1.sAddr=ps->T5.sAddr;
		if(ps->T5.spTrueList)
			pps[pps.size()-2]->getSynAttr()->T1.spTrueList->swap(*(ps->T5.spTrueList));
		if(ps->T5.spFalseList)
			pps[pps.size()-2]->getSynAttr()->T1.spFalseList->swap(*(ps->T5.spFalseList));
	}

	static void act_T5A_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
	
		//传递T5属性
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=true;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=pi->T5.iType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=pi->T5.iAddr;
	}
	static void act_T5A_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的T5属性: e2'(control flow->value)
		pps[pps.size()-2]->getSynAttr()->T5.sValFlag=ps->e2_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->T5.sType=ps->e2_.sType;
		pps[pps.size()-2]->getSynAttr()->T5.sAddr=ps->e2_.sAddr;
		if(ps->e2_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->T5.spTrueList->swap(*(ps->e2_.spTrueList));
		if(ps->e2_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->T5.spFalseList->swap(*(ps->e2_.spFalseList));
	}

	static void act_T5B_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//传递T5属性
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=true;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=pi->T5.iType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=pi->T5.iAddr;
	}
	static void act_T5B_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//赋空指针
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T5B_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的T5属性: e2'(control flow->value)
		pps[pps.size()-2]->getSynAttr()->T5.sValFlag=ps->e2_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->T5.sType=ps->e2_.sType;
		pps[pps.size()-2]->getSynAttr()->T5.sAddr=ps->e2_.sAddr;
		if(ps->e2_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->T5.spTrueList->swap(*(ps->e2_.spTrueList));
		if(ps->e2_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->T5.spFalseList->swap(*(ps->e2_.spFalseList));
	}

	static void act_T5C_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//传递T5属性
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=true;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=pi->T5.iType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=pi->T5.iAddr;
	}
	static void act_T5C_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//赋空指针
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T5C_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//赋空指针
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T5C_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的T5属性: e2'(control flow->value)
		pps[pps.size()-2]->getSynAttr()->T5.sValFlag=ps->e2_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->T5.sType=ps->e2_.sType;
		pps[pps.size()-2]->getSynAttr()->T5.sAddr=ps->e2_.sAddr;
		if(ps->e2_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->T5.spTrueList->swap(*(ps->e2_.spTrueList));
		if(ps->e2_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->T5.spFalseList->swap(*(ps->e2_.spFalseList));
	}

	static void act_T5D_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//传递T5属性
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=true;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=pi->T5.iType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=pi->T5.iAddr;
	}
	static void act_T5D_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e4': e5'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//赋空指针
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T5D_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//赋空指针
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T5D_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//赋空指针
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T5D_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的T5属性: e2'(control flow->value)
		pps[pps.size()-2]->getSynAttr()->T5.sValFlag=ps->e2_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->T5.sType=ps->e2_.sType;
		pps[pps.size()-2]->getSynAttr()->T5.sAddr=ps->e2_.sAddr;
		if(ps->e2_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->T5.spTrueList->swap(*(ps->e2_.spTrueList));
		if(ps->e2_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->T5.spFalseList->swap(*(ps->e2_.spFalseList));
	}

	static void act_T5E_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//传递T5属性
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=true;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=pi->T5.iType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=pi->T5.iAddr;
	}
	static void act_T5E_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e5': e6'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//赋空指针
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T5E_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e4': e5'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//赋空指针
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T5E_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//赋空指针
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T5E_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//赋空指针
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T5E_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的T5属性: e2'(control flow->value)
		pps[pps.size()-2]->getSynAttr()->T5.sValFlag=ps->e2_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->T5.sType=ps->e2_.sType;
		pps[pps.size()-2]->getSynAttr()->T5.sAddr=ps->e2_.sAddr;
		if(ps->e2_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->T5.spTrueList->swap(*(ps->e2_.spTrueList));
		if(ps->e2_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->T5.spFalseList->swap(*(ps->e2_.spFalseList));
	}

	static void act_T5F_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//传递T5属性
		pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=true;
		pps[pps.size()-2]->getInhAttr()->e7_.iType=pi->T5.iType;
		pps[pps.size()-2]->getInhAttr()->e7_.iAddr=pi->T5.iAddr;
	}
	static void act_T5F_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e6': e7'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7_.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7_.spFalseList;

		//赋空指针
		ps->e7_.spTrueList=0;
		ps->e7_.spFalseList=0;
	}
	static void act_T5F_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e5': e6'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//赋空指针
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T5F_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e4': e5'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//赋空指针
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T5F_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//赋空指针
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T5F_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//赋空指针
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T5F_S6(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的T5属性: e2'(control flow->value)
		pps[pps.size()-2]->getSynAttr()->T5.sValFlag=ps->e2_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->T5.sType=ps->e2_.sType;
		pps[pps.size()-2]->getSynAttr()->T5.sAddr=ps->e2_.sAddr;
		if(ps->e2_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->T5.spTrueList->swap(*(ps->e2_.spTrueList));
		if(ps->e2_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->T5.spFalseList->swap(*(ps->e2_.spFalseList));
	}

	static void act_T5G_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//传递T5属性
		pps[pps.size()-2]->getInhAttr()->e8_.iValFlag=true;
		pps[pps.size()-2]->getInhAttr()->e8_.iType=pi->T5.iType;
		pps[pps.size()-2]->getInhAttr()->e8_.iAddr=pi->T5.iAddr;
	}
	static void act_T5G_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e7': e8'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=ps->e8_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e7_.iType=ps->e8_.sType;
		pps[pps.size()-2]->getInhAttr()->e7_.iAddr=ps->e8_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e7_.ipTrueList=ps->e8_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e7_.ipFalseList=ps->e8_.spFalseList;

		//赋空指针
		ps->e8_.spTrueList=0;
		ps->e8_.spFalseList=0;
	}
	static void act_T5G_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e6': e7'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7_.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7_.spFalseList;

		//赋空指针
		ps->e7_.spTrueList=0;
		ps->e7_.spFalseList=0;
	}
	static void act_T5G_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e5': e6'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//赋空指针
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T5G_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e4': e5'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//赋空指针
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T5G_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//赋空指针
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T5G_S6(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//赋空指针
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T5G_S7(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的T5属性: e2'(control flow->value)
		pps[pps.size()-2]->getSynAttr()->T5.sValFlag=ps->e2_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->T5.sType=ps->e2_.sType;
		pps[pps.size()-2]->getSynAttr()->T5.sAddr=ps->e2_.sAddr;
		if(ps->e2_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->T5.spTrueList->swap(*(ps->e2_.spTrueList));
		if(ps->e2_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->T5.spFalseList->swap(*(ps->e2_.spFalseList));
	}

	static void act_T5H_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//传递T5属性
		pps[pps.size()-2]->getInhAttr()->e9_.iValFlag=true;
		pps[pps.size()-2]->getInhAttr()->e9_.iType=pi->T5.iType;
		pps[pps.size()-2]->getInhAttr()->e9_.iAddr=pi->T5.iAddr;
	}
	static void act_T5H_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e8': e9'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e8_.iValFlag=ps->e9_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e8_.iType=ps->e9_.sType;
		pps[pps.size()-2]->getInhAttr()->e8_.iAddr=ps->e9_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e8_.ipTrueList=ps->e9_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e8_.ipFalseList=ps->e9_.spFalseList;

		//赋空指针
		ps->e9_.spTrueList=0;
		ps->e9_.spFalseList=0;
	}
	static void act_T5H_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e7': e8'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=ps->e8_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e7_.iType=ps->e8_.sType;
		pps[pps.size()-2]->getInhAttr()->e7_.iAddr=ps->e8_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e7_.ipTrueList=ps->e8_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e7_.ipFalseList=ps->e8_.spFalseList;

		//赋空指针
		ps->e8_.spTrueList=0;
		ps->e8_.spFalseList=0;
	}
	static void act_T5H_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e6': e7'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7_.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7_.spFalseList;

		//赋空指针
		ps->e7_.spTrueList=0;
		ps->e7_.spFalseList=0;
	}
	static void act_T5H_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e5': e6'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//赋空指针
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T5H_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e4': e5'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//赋空指针
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T5H_S6(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//赋空指针
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T5H_S7(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//赋空指针
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T5H_S8(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的T5属性: e2'(control flow->value)
		pps[pps.size()-2]->getSynAttr()->T5.sValFlag=ps->e2_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->T5.sType=ps->e2_.sType;
		pps[pps.size()-2]->getSynAttr()->T5.sAddr=ps->e2_.sAddr;
		if(ps->e2_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->T5.spTrueList->swap(*(ps->e2_.spTrueList));
		if(ps->e2_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->T5.spFalseList->swap(*(ps->e2_.spFalseList));
	}

	static void act_T5I_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//传递T5属性
		pps[pps.size()-2]->getInhAttr()->e10_.iValFlag=true;
		pps[pps.size()-2]->getInhAttr()->e10_.iType=pi->T5.iType;
		pps[pps.size()-2]->getInhAttr()->e10_.iAddr=pi->T5.iAddr;
	}
	static void act_T5I_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e9': e10'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e9_.iValFlag=ps->e10_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e9_.iType=ps->e10_.sType;
		pps[pps.size()-2]->getInhAttr()->e9_.iAddr=ps->e10_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e9_.ipTrueList=ps->e10_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e9_.ipFalseList=ps->e10_.spFalseList;

		//赋空指针
		ps->e10_.spTrueList=0;
		ps->e10_.spFalseList=0;
	}
	static void act_T5I_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e8': e9'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e8_.iValFlag=ps->e9_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e8_.iType=ps->e9_.sType;
		pps[pps.size()-2]->getInhAttr()->e8_.iAddr=ps->e9_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e8_.ipTrueList=ps->e9_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e8_.ipFalseList=ps->e9_.spFalseList;

		//赋空指针
		ps->e9_.spTrueList=0;
		ps->e9_.spFalseList=0;
	}
	static void act_T5I_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e7': e8'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=ps->e8_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e7_.iType=ps->e8_.sType;
		pps[pps.size()-2]->getInhAttr()->e7_.iAddr=ps->e8_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e7_.ipTrueList=ps->e8_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e7_.ipFalseList=ps->e8_.spFalseList;

		//赋空指针
		ps->e8_.spTrueList=0;
		ps->e8_.spFalseList=0;
	}
	static void act_T5I_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e6': e7'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7_.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7_.spFalseList;

		//赋空指针
		ps->e7_.spTrueList=0;
		ps->e7_.spFalseList=0;
	}
	static void act_T5I_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e5': e6'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//赋空指针
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T5I_S6(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e4': e5'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//赋空指针
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T5I_S7(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//赋空指针
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T5I_S8(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//赋空指针
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T5I_S9(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的T5属性: e2'(control flow->value)
		pps[pps.size()-2]->getSynAttr()->T5.sValFlag=ps->e2_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->T5.sType=ps->e2_.sType;
		pps[pps.size()-2]->getSynAttr()->T5.sAddr=ps->e2_.sAddr;
		if(ps->e2_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->T5.spTrueList->swap(*(ps->e2_.spTrueList));
		if(ps->e2_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->T5.spFalseList->swap(*(ps->e2_.spFalseList));
	}

	static void act_T5J_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//传递T5属性
		pps[pps.size()-2]->getInhAttr()->e11_.iValFlag=true;
		pps[pps.size()-2]->getInhAttr()->e11_.iType=pi->T5.iType;
		pps[pps.size()-2]->getInhAttr()->e11_.iAddr=pi->T5.iAddr;
	}
	static void act_T5J_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e10': e11'(value->value)
		pps[pps.size()-2]->getInhAttr()->e10_.iValFlag=ps->e11_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e10_.iType=ps->e11_.sType;
		pps[pps.size()-2]->getInhAttr()->e10_.iAddr=ps->e11_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e10_.ipTrueList=ps->e11_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e10_.ipFalseList=ps->e11_.spFalseList;

		//赋空指针
		ps->e11_.spTrueList=0;
		ps->e11_.spFalseList=0;
	}
	static void act_T5J_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e9': e10'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e9_.iValFlag=ps->e10_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e9_.iType=ps->e10_.sType;
		pps[pps.size()-2]->getInhAttr()->e9_.iAddr=ps->e10_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e9_.ipTrueList=ps->e10_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e9_.ipFalseList=ps->e10_.spFalseList;

		//赋空指针
		ps->e10_.spTrueList=0;
		ps->e10_.spFalseList=0;
	}
	static void act_T5J_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e8': e9'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e8_.iValFlag=ps->e9_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e8_.iType=ps->e9_.sType;
		pps[pps.size()-2]->getInhAttr()->e8_.iAddr=ps->e9_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e8_.ipTrueList=ps->e9_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e8_.ipFalseList=ps->e9_.spFalseList;

		//赋空指针
		ps->e9_.spTrueList=0;
		ps->e9_.spFalseList=0;
	}
	static void act_T5J_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e7': e8'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=ps->e8_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e7_.iType=ps->e8_.sType;
		pps[pps.size()-2]->getInhAttr()->e7_.iAddr=ps->e8_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e7_.ipTrueList=ps->e8_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e7_.ipFalseList=ps->e8_.spFalseList;

		//赋空指针
		ps->e8_.spTrueList=0;
		ps->e8_.spFalseList=0;
	}
	static void act_T5J_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e6': e7'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7_.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7_.spFalseList;

		//赋空指针
		ps->e7_.spTrueList=0;
		ps->e7_.spFalseList=0;
	}
	static void act_T5J_S6(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e5': e6'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//赋空指针
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T5J_S7(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e4': e5'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//赋空指针
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T5J_S8(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//赋空指针
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T5J_S9(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//赋空指针
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T5J_S10(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的T5属性: e2'(control flow->value)
		pps[pps.size()-2]->getSynAttr()->T5.sValFlag=ps->e2_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->T5.sType=ps->e2_.sType;
		pps[pps.size()-2]->getSynAttr()->T5.sAddr=ps->e2_.sAddr;
		if(ps->e2_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->T5.spTrueList->swap(*(ps->e2_.spTrueList));
		if(ps->e2_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->T5.spFalseList->swap(*(ps->e2_.spFalseList));
	}

	static void act_T5K_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//传递T5属性
		pps[pps.size()-2]->getInhAttr()->e12_.iValFlag=true;
		pps[pps.size()-2]->getInhAttr()->e12_.iType=pi->T5.iType;
		pps[pps.size()-2]->getInhAttr()->e12_.iAddr=pi->T5.iAddr;
	}
	static void act_T5K_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e11': e12'(value->value)
		pps[pps.size()-2]->getInhAttr()->e11_.iValFlag=ps->e12_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e11_.iType=ps->e12_.sType;
		pps[pps.size()-2]->getInhAttr()->e11_.iAddr=ps->e12_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e11_.ipTrueList=ps->e12_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e11_.ipFalseList=ps->e12_.spFalseList;

		//赋空指针
		ps->e12_.spTrueList=0;
		ps->e12_.spFalseList=0;
	}
	static void act_T5K_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e10': e11'(value->value)
		pps[pps.size()-2]->getInhAttr()->e10_.iValFlag=ps->e11_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e10_.iType=ps->e11_.sType;
		pps[pps.size()-2]->getInhAttr()->e10_.iAddr=ps->e11_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e10_.ipTrueList=ps->e11_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e10_.ipFalseList=ps->e11_.spFalseList;

		//赋空指针
		ps->e11_.spTrueList=0;
		ps->e11_.spFalseList=0;
	}
	static void act_T5K_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e9': e10'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e9_.iValFlag=ps->e10_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e9_.iType=ps->e10_.sType;
		pps[pps.size()-2]->getInhAttr()->e9_.iAddr=ps->e10_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e9_.ipTrueList=ps->e10_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e9_.ipFalseList=ps->e10_.spFalseList;

		//赋空指针
		ps->e10_.spTrueList=0;
		ps->e10_.spFalseList=0;
	}
	static void act_T5K_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e8': e9'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e8_.iValFlag=ps->e9_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e8_.iType=ps->e9_.sType;
		pps[pps.size()-2]->getInhAttr()->e8_.iAddr=ps->e9_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e8_.ipTrueList=ps->e9_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e8_.ipFalseList=ps->e9_.spFalseList;

		//赋空指针
		ps->e9_.spTrueList=0;
		ps->e9_.spFalseList=0;
	}
	static void act_T5K_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e7': e8'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=ps->e8_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e7_.iType=ps->e8_.sType;
		pps[pps.size()-2]->getInhAttr()->e7_.iAddr=ps->e8_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e7_.ipTrueList=ps->e8_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e7_.ipFalseList=ps->e8_.spFalseList;

		//赋空指针
		ps->e8_.spTrueList=0;
		ps->e8_.spFalseList=0;
	}
	static void act_T5K_S6(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e6': e7'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7_.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7_.spFalseList;

		//赋空指针
		ps->e7_.spTrueList=0;
		ps->e7_.spFalseList=0;
	}
	static void act_T5K_S7(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e5': e6'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//赋空指针
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T5K_S8(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e4': e5'(value(整型)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//赋空指针
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T5K_S9(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//赋空指针
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T5K_S10(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//综合属性传递给后面的e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//浅拷贝
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//赋空指针
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T5K_S11(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//计算S后面的T5属性: e2'(control flow->value)
		pps[pps.size()-2]->getSynAttr()->T5.sValFlag=ps->e2_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->T5.sType=ps->e2_.sType;
		pps[pps.size()-2]->getSynAttr()->T5.sAddr=ps->e2_.sAddr;
		if(ps->e2_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->T5.spTrueList->swap(*(ps->e2_.spTrueList));
		if(ps->e2_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->T5.spFalseList->swap(*(ps->e2_.spFalseList));
	}

	static void act_T5L_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//计算S后面的T5属性
		pps[pps.size()-2]->getSynAttr()->T5.sValFlag=true;	
		pps[pps.size()-2]->getSynAttr()->T5.sType=pi->T5.iType;
		pps[pps.size()-2]->getSynAttr()->T5.sAddr=pi->T5.iAddr;
	}



	// Terminal action

	static void act_main(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//传递main属性
		pps[pps.size()-2]->getTempVar()->main_line.tLine=cpToken->Line();
	}

	static void act_id(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//传递id属性
		pps[pps.size()-2]->getTempVar()->option_id.tLine=cpToken->Line();
		*(pps[pps.size()-2]->getTempVar()->option_id.tLexime)=cpToken->toString();
	}

	static void act_bool(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//传递bool属性
		pps[pps.size()-2]->getSynAttr()->B.sType.type=t_BOOL;
	}

	static void act_char(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//传递char属性
		pps[pps.size()-2]->getSynAttr()->B.sType.type=t_CHAR;
	}

	static void act_short(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//传递short属性
		pps[pps.size()-2]->getSynAttr()->B.sType.type=t_SHORT;
	}

	static void act_int(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//传递int属性
		pps[pps.size()-2]->getSynAttr()->B.sType.type=t_INT;
	}

	static void act_float(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//传递float属性
		pps[pps.size()-2]->getSynAttr()->B.sType.type=t_FLOAT;
	}

	static void act_double(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//传递double属性
		pps[pps.size()-2]->getSynAttr()->B.sType.type=t_DOUBLE;
	}

	static void act_op(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//传递operator属性
		pps[pps.size()-2]->getTempVar()->op_line.tLine=cpToken->Line();
	}

	static void act_real(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//传递real属性
		pps[pps.size()-2]->getTempVar()->e14_real.tValue=dynamic_cast<Real const*>(cpToken)->getValue();
	}

	static void act_number(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//传递number属性
		pps[pps.size()-2]->getTempVar()->A_const.tLine=cpToken->Line();
		pps[pps.size()-2]->getTempVar()->A_const.tValue=dynamic_cast<Number const*>(cpToken)->getValue();
	}

	static void act_ascii(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//传递ascii属性
		pps[pps.size()-2]->getTempVar()->A_const.tLine=cpToken->Line();
		pps[pps.size()-2]->getTempVar()->A_const.tValue=dynamic_cast<Character const*>(cpToken)->getValue();
	}

	static void act_false(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//传递false属性
		pps[pps.size()-2]->getTempVar()->A_const.tLine=cpToken->Line();
		pps[pps.size()-2]->getTempVar()->A_const.tValue=false;
	}

	static void act_true(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//传递true属性
		pps[pps.size()-2]->getTempVar()->A_const.tLine=cpToken->Line();
		pps[pps.size()-2]->getTempVar()->A_const.tValue=true;
	}

	static void act_if(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//传递if属性
		pps[pps.size()-4]->getTempVar()->if_line.tLine=cpToken->Line();
	}

	static void act_while(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//传递while属性: do-while语句
		if(pps[pps.size()-5]->isTerminal())
		{
			pps[pps.size()-4]->getTempVar()->do_expr.tLine=cpToken->Line();
		}
		//传递while属性: while语句
		else
		{
			pps[pps.size()-5]->getTempVar()->while_line.tLine=cpToken->Line();
		}
	}

	static void act_break(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//传递break属性
		pps[pps.size()-2]->getTempVar()->break_line.tLine=cpToken->Line();
	}

	static void act_continue(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//传递conntinue属性
		pps[pps.size()-2]->getTempVar()->continue_line.tLine=cpToken->Line();
	}

	static void act_return(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//传递return属性
		pps[pps.size()-2]->getInhAttr()->optexpr3.iLine=cpToken->Line();

		//完成综合属性sRetCnt的计算
		pps[pps.size()-4]->getSynAttr()->stmt.sRetCnt=1;
	}

	static void act_for(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//传递for属性
		pps[pps.size()-3]->getInhAttr()->optexpr2.iLine=cpToken->Line();		
		pps[pps.size()-6]->getInhAttr()->optexpr2.iLine=cpToken->Line();				
		pps[pps.size()-9]->getInhAttr()->optexpr2.iLine=cpToken->Line();
	}

	static void act_switch(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//传递switch属性
		pps[pps.size()-4]->getTempVar()->switch_expr_line.tLine=cpToken->Line();
	}
}