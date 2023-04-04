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
	typedef vector<StackRecord*> PPS;	//Ԥ�����ջ
	typedef multimap<size_t,string> ErrorRecord;
	
	static bool Value2ControlFlow(Env &context,Syn_Attr *ps,unsigned char sec=s_LOCAL)
	{
		//�����ǰ��value
		if(ps->expr.sValFlag)
		{
			//���ɼ�������,ֱ�ӷ���ʧ��
			if(!Computable(ps->expr.sType))
				return false;

			//���´������ɲ���valueֵ�����ݲ�������������ת��ָ��
			if(ps->expr.spTrueList)
				ps->expr.spTrueList->push_back(context.getNextInstr(sec));		//����Ϊ��
			context.Gen(op_if_true_goto,ps->expr.sAddr,sec);	//��תĿ���ַ������
			if(ps->expr.spFalseList)
				ps->expr.spFalseList->push_back(context.getNextInstr(sec));		//����Ϊ��
			context.Gen(op_goto,sec);	//��תĿ���ַ������

			//����ֵ��־
			ps->expr.sValFlag=false;
		}

		return true;
	}

	static bool Value2ControlFlow(Env &context,Inh_Attr *pi,unsigned char sec=s_LOCAL)
	{
		//�����ǰ��value
		if(pi->expr_.iValFlag)
		{
			//���ɼ�������,ֱ�ӷ���ʧ��
			if(!Computable(pi->expr_.iType))
				return false;

			//���´������ɲ���valueֵ�����ݲ�������������ת��ָ��
			if(!pi->expr_.ipTrueList)
				pi->expr_.ipTrueList=new instr_list();
			pi->expr_.ipTrueList->push_back(context.getNextInstr(sec));		//����Ϊ��
			context.Gen(op_if_true_goto,pi->expr_.iAddr,sec);	//��תĿ���ַ������

			if(!pi->expr_.ipFalseList)
				pi->expr_.ipFalseList=new instr_list();
			pi->expr_.ipFalseList->push_back(context.getNextInstr(sec));		//����Ϊ��
			context.Gen(op_goto,sec);	//��תĿ���ַ������

			//����ֵ��־
			pi->expr_.iValFlag=false;
		}

		return true;
	}

	static void ControlFlow2Value(Env &context,Syn_Attr *ps,unsigned char sec=s_LOCAL)
	{
		//�����ǰ��control flow
		if(!ps->expr.sValFlag)
		{
			//����ֵ��־
			ps->expr.sValFlag=true;

			//��������ָ��Ϊbool��
			ps->expr.sType.type=t_BOOL;
			ps->expr.sType.is_array=false;

			//������ʱ������ַ
			ps->expr.sAddr=context.Temp(ps->expr.sType,sec);

			//�Ը�������control flow����ٳ��ڽ���ʱ������ֵ����Ϊtrue��false
			context.BackPatch(ps->expr.spTrueList,context.getNextInstr(sec),sec);	//���������
			context.Gen(op_assign,ps->expr.sAddr,context.getAddress(true),sec);	//��ʱ��������Ϊtrueֵ
			instr_list *ptruelist=new instr_list();
			ptruelist->push_back(context.getNextInstr(sec));	//�����������תָ���±�
			context.Gen(op_goto,sec);	//��ת���ٳ���֮��,Ŀ���ַ������
			context.BackPatch(ps->expr.spFalseList,context.getNextInstr(sec),sec);	//����ٳ���
			context.Gen(op_assign,ps->expr.sAddr,context.getAddress(false),sec);	//��ʱ��������Ϊfalseֵ
			context.BackPatch(ptruelist,context.getNextInstr(sec),sec);		//������������תָ��
			context.Gen(op_no_op,sec);		//����һ��no-opָ��,һ����������Ŀ��
			delete ptruelist;
		}
	}

	static void ControlFlow2Value(Env &context,Inh_Attr *pi,unsigned char sec=s_LOCAL)
	{
		//�����ǰ��control flow
		if(!pi->expr_.iValFlag)
		{
			//����ֵ��־
			pi->expr_.iValFlag=true;

			//��������ָ��Ϊbool��
			pi->expr_.iType.type=t_BOOL;
			pi->expr_.iType.is_array=false;

			//������ʱ������ַ
			pi->expr_.iAddr=context.Temp(pi->expr_.iType,sec);

			//�Ը�������control flow����ٳ��ڽ���ʱ������ֵ����Ϊtrue��false
			context.BackPatch(pi->expr_.ipTrueList,context.getNextInstr(sec),sec);	//���������
			context.Gen(op_assign,pi->expr_.iAddr,context.getAddress(true),sec);	//��ʱ��������Ϊtrueֵ
			instr_list *ptruelist=new instr_list();
			ptruelist->push_back(context.getNextInstr(sec));	//�����������תָ���±�
			context.Gen(op_goto,sec);	//��ת���ٳ���֮��,Ŀ���ַ������
			context.BackPatch(pi->expr_.ipFalseList,context.getNextInstr(sec),sec);	//����ٳ���
			context.Gen(op_assign,pi->expr_.iAddr,context.getAddress(false),sec);	//��ʱ��������Ϊfalseֵ
			context.BackPatch(ptruelist,context.getNextInstr(sec),sec);		//������������תָ��
			context.Gen(op_no_op,sec);		//����һ��no-opָ��,һ����������Ŀ��
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

		//���������
		context.Clear();

		//���������ĺ�����
		context.ReName("main");
	}
	static void act_program_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//����stmts.nextlist
		context.BackPatch(
			pps.back()->getSynAttr()->stmts.spNextList,
			context.getNextInstr()
			);

		//����Ĭ�ϵķ���ָ��
		context.Gen(op_return);
	}
	static void act_program_A2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//��ȡmain����id
		size_t id=context.getFunInfo("main")->id;

		//����main�������ֽ���
		byte_code.BuildLocalCode(
			id,
			context.getLocalTable(),
			context.getFunCode()
			);

		//�ڳ�ʼ�����������ɵ���main������ָ��
		context.Gen(
			op_call,
			context.getAddress(int(id)),
			context.getAddress(0),
			s_GLOBAL
			);

		//main����������ü���
		byte_code.getCallSet().insert(id);

		//���ɳ�ʼ��������ֽ���
		byte_code.BuildInitCode(Env::getInitCode());

		//���ɳ�������ֽ���
		byte_code.BuildConstTableCode(Env::getConstTable());

		//����ȫ�ַ��ű���ֽ���
		byte_code.BuildGlobalTableCode(Env::getGlobalTable());

		//���������
		context.Clear();

		//�ÿ������ĺ�����
		context.ReName("");
	}



	static void act_option1_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Temp_Var *pt=pps.back()->getTempVar();

		//id��Ϊȫ�����ֱ���Ψһ
		string name(*(pt->option_id.tLexime));

		//�����Ѿ�����Ϊ����
		if(context.isVar(name))
		{
			//�״ζ���λ��
			size_t def=context.getAllocInfo(name)->line;

			//�ض���λ��
			size_t redef=pt->option_id.tLine;

			//���󱨸�
			string str="�ظ�����:����\""+name+"\"�ڵ�"+toString(int(def))+"��������Ϊ���������顣";

			//׷�ӵ���¼
			err_record.insert(make_pair(redef,str));
		}
		//�����Ѿ�����Ϊ����
		else if(context.isFun(name))
		{
			//�״ζ���λ��
			size_t def=context.getFunInfo(name)->line;

			//�ض���λ��
			size_t redef=pt->option_id.tLine;

			//���󱨸�
			string str;
			
			if(def)
				str="�ظ�����:����\""+name+"\"�ڵ�"+toString(int(def))+"��������Ϊ������";
			else
				str="���ֳ�ͻ:"+name+"�Ѿ���Ϊ�⺯����ʹ�á�";

			//׷�ӵ���¼
			err_record.insert(make_pair(redef,str));
		}

		//��F����void����
		pps[pps.size()-2]->getInhAttr()->F.iType.type=t_VOID;

		//��F����id����
		pps[pps.size()-2]->getInhAttr()->F.iLine=pt->option_id.tLine;
		pps[pps.size()-2]->getInhAttr()->F.iLexime->swap(*(pt->option_id.tLexime));
	}

	static void act_option2_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//��option'����B����
		pps[pps.size()-4]->getInhAttr()->option_.iType=pps.back()->getSynAttr()->B.sType;
	}
	static void act_option2_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Temp_Var *pt=pps.back()->getTempVar();

		//id��Ϊȫ�����ֱ���Ψһ
		string name(*(pt->option_id.tLexime));

		//�����Ѿ�����Ϊ����
		if(context.isVar(name))
		{
			//�״ζ���λ��
			size_t def=context.getAllocInfo(name)->line;

			//�ض���λ��
			size_t redef=pt->option_id.tLine;

			//���󱨸�
			string str="�ظ�����:����\""+name+"\"�ڵ�"+toString(int(def))+"��������Ϊ���������顣";

			//׷�ӵ���¼
			err_record.insert(make_pair(redef,str));
		}
		//�����Ѿ�����Ϊ����
		else if(context.isFun(name))
		{
			//�״ζ���λ��
			size_t def=context.getFunInfo(name)->line;

			//�ض���λ��
			size_t redef=pt->option_id.tLine;

			//���󱨸�
			string str;

			if(def)
				str="�ظ�����:����\""+name+"\"�ڵ�"+toString(int(def))+"��������Ϊ������";
			else
				str="���ֳ�ͻ:"+name+"�Ѿ���Ϊ�⺯����ʹ�á�";

			//׷�ӵ���¼
			err_record.insert(make_pair(redef,str));
		}

		//��option'����id����
		pps[pps.size()-2]->getInhAttr()->option_.iLine=pt->option_id.tLine;
		pps[pps.size()-2]->getInhAttr()->option_.iLexime->swap(*(pt->option_id.tLexime));	
	}



	static void act_decl_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//��decl'����B����
		pps[pps.size()-4]->getInhAttr()->decl_.iType=pps.back()->getSynAttr()->B.sType;
	}
	static void act_decl_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Temp_Var *pt=pps.back()->getTempVar();

		//id��Ϊȫ�����ֱ���Ψһ
		string name(*(pt->decl_id.tLexime));

		//�����Ѿ�����Ϊ����
		if(context.isVar(name))
		{
			//�״ζ���λ��
			size_t def=context.getAllocInfo(name)->line;

			//�ض���λ��
			size_t redef=pt->decl_id.tLine;

			//���󱨸�
			string str="�ظ�����:����\""+name+"\"�ڵ�"+toString(int(def))+"��������Ϊ���������顣";

			//׷�ӵ���¼
			err_record.insert(make_pair(redef,str));
		}
		//�����Ѿ�����Ϊ����
		else if(context.isFun(name))
		{
			//�״ζ���λ��
			size_t def=context.getFunInfo(name)->line;

			//�ض���λ��
			size_t redef=pt->decl_id.tLine;

			//���󱨸�
			string str;

			if(def)
				str="�ظ�����:����\""+name+"\"�ڵ�"+toString(int(def))+"��������Ϊ������";
			else
				str="���ֳ�ͻ:"+name+"�Ѿ���Ϊ�⺯����ʹ�á�";

			//׷�ӵ���¼
			err_record.insert(make_pair(redef,str));
		}

		//��decl'����id����
		pps[pps.size()-2]->getInhAttr()->decl_.iLine=pt->decl_id.tLine;
		pps[pps.size()-2]->getInhAttr()->decl_.iLexime->swap(*(pt->decl_id.tLexime));	
	}

	static void act_A_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//��������СӦ�ô���0
		if(!(0<ps->size.tValue))
		{
			string str="����"+*(pi->A.iLexime)+"��СӦ�ô���0��";

			//���ɴ��󱨸�
			err_record.insert(make_pair(pi->A.iLine,str));
		}
		//else
		{
			//������������
			pi->A.iType.is_array=true;
			pi->A.iType.length=ps->size.tValue;

			//��������
			context.defineVar(*(pi->A.iLexime),pi->A.iType,pi->A.iLine,pi->A.iSection);
		}
	}

	static void act_L__S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Syn_Attr *ps=pps.back()->getSynAttr();
		string name=*(pi->L_.iLexime);

		//��ȡ����������Ϣ
		AllocInfo const* pa=context.getAllocInfo(name);

		//�����ʼ��ֵ�����������С
		if(pi->L_.iIndex < pa->var_info.length)
		{
			//ת����value
			ControlFlow2Value(context,ps,pi->L_.iSection);

			//�ɼ�������
			if(Computable(ps->e1.sType))
			{
				//����������Ԫ�ظ�ֵ��ָ��
				context.Gen(op_write_array,context.getAddress(name),context.getAddress(int(pi->L_.iIndex)),ps->e1.sAddr,pi->L_.iSection);
			}
			else
			{
				size_t def=context.getAllocInfo(name)->line;

				//���󱨸�
				string str="����\""+name+"\"�ĵ�"+toString(int(pi->L_.iIndex+1))+"����ʼ��ֵ���ʹ���";

				//׷�ӵ���¼
				err_record.insert(make_pair(def,str));
			}
		}
		else
		{
			size_t def=context.getAllocInfo(name)->line;

			//���󱨸�
			string str="����\""+name+"\"�ĳ�ʼ��ֵ���ࡣ";

			//׷�ӵ���¼
			err_record.insert(make_pair(def,str));
		}
	}

	static void act_V_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//���ɱ�������
		pi->V.iType.is_array=false;

		//�������
		context.defineVar(*(pi->V.iLexime),pi->V.iType,pi->V.iLine,pi->V.iSection);		
	}

	static void act_V_1_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Temp_Var *pt=pps.back()->getTempVar();

		//id��Ϊȫ�����ֱ���Ψһ
		string name(*(pt->V__id.tLexime));

		//�����Ѿ�����Ϊ����
		if(context.isVar(name))
		{
			//�״ζ���λ��
			size_t def=context.getAllocInfo(name)->line;

			//�ض���λ��
			size_t redef=pt->V__id.tLine;

			//���󱨸�
			string str="�ظ�����:����\""+name+"\"�ڵ�"+toString(int(def))+"��������Ϊ���������顣";

			//׷�ӵ���¼
			err_record.insert(make_pair(redef,str));
		}
		//�����Ѿ�����Ϊ����
		else if(context.isFun(name))
		{
			//�״ζ���λ��
			size_t def=context.getFunInfo(name)->line;

			//�ض���λ��
			size_t redef=pt->V__id.tLine;

			//���󱨸�
			string str;

			if(def)
				str="�ظ�����:����\""+name+"\"�ڵ�"+toString(int(def))+"��������Ϊ������";
			else
				str="���ֳ�ͻ:"+name+"�Ѿ���Ϊ�⺯����ʹ�á�";

			//׷�ӵ���¼
			err_record.insert(make_pair(redef,str));
		}

		Inh_Attr *pi=pps.back()->getInhAttr();

		//���ɱ�������
		pi->V_.iType.is_array=false;

		//�������
		context.defineVar(*(pt->V__id.tLexime),pi->V_.iType,pt->V__id.tLine,pi->V_.iSection);			
		
		//id���Դ��ݸ�opt2
		pps[pps.size()-2]->getInhAttr()->opt2.iLexime->swap(*(pt->V__id.tLexime));
	}

	static void act_opt2A_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Syn_Attr *ps=pps.back()->getSynAttr();
		string name=*(pi->opt2.iLexime);

		//ת����value
		ControlFlow2Value(context,ps,pi->opt2.iSection);

		//�ɼ�������
		if(Computable(ps->e1.sType))
		{
			//�����������ֵ��ָ��
			context.Gen(op_assign,context.getAddress(name),ps->e1.sAddr,pi->opt2.iSection);
		}
		else
		{
			size_t def=context.getAllocInfo(name)->line;

			//���󱨸�
			string str="����\""+name+"\"�ĳ�ʼ��ֵ���ʹ���";

			//׷�ӵ���¼
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
			vector<VarInfo>(),	//�����б��ʼ��Ϊ��
			pi->F.iLine
			);

		//���������
		context.Clear();

		//���������ĺ�����
		context.ReName(*(pi->F.iLexime));
	}
	static void act_F_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����stmts.nextlist
		context.BackPatch(
			ps->stmts.spNextList,
			context.getNextInstr()
			);

		//��ȡ�����ĺ�����Ϣ
		FunInfo const& fun_info=*context.getFunInfo(context.getName());

		//�����޷�������
		if(t_VOID==fun_info.ret_type)
		{
			//����Ĭ�ϵķ���ָ��
			context.Gen(op_return);
		}
		//�����з�������
		else
		{
			//��麯���Ƿ����ɷ���ָ��/���һ��ָ���Ƿ񷵻�ָ��
			if(0==ps->stmts.sRetCnt || op_return_value!=context.getLastInstr())
			{
				//���󱨸�
				string str="����\""+context.getName()+"\"���뷵��һ��ֵ��";

				//׷�ӵ���¼
				err_record.insert(make_pair(fun_info.line,str));
			}
			//����
			else
			{
				//����no-opָ��,�������Ŀ�겻����
				context.Gen(op_no_op,s_LOCAL);
			}
		}
	}
	static void act_F_A2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//���ɺ������ֽ���
		byte_code.BuildLocalCode(
			context.getFunInfo(context.getName())->id,
			context.getLocalTable(),
			context.getFunCode()
			);

		//���������
		context.Clear();

		//�ÿ������ĺ�����
		context.ReName("");
	}

	static void act_param_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//��tail����B����
		pps[pps.size()-4]->getInhAttr()->tail.iType=pps.back()->getSynAttr()->B.sType;
	}
	static void act_param_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Temp_Var *pt=pps.back()->getTempVar();

		//id��Ϊ�������ֱ���Ψһ
		string name(*(pt->param_id.tLexime));

		//�����Ѿ�����Ϊ����
		if(context.isVar(name))
		{
			//�״ζ���λ��
			size_t def=context.getAllocInfo(name)->line;

			//�ض���λ��
			size_t redef=pt->param_id.tLine;

			//���󱨸�
			string str="�ظ�����:����\""+name+"\"�ڵ�"+toString(int(def))+"��������Ϊ���������顣";

			//׷�ӵ���¼
			err_record.insert(make_pair(redef,str));
		}
		//�����Ѿ�����Ϊ����
		else if(context.isFun(name))
		{
			//�״ζ���λ��
			size_t def=context.getFunInfo(name)->line;

			//�ض���λ��
			size_t redef=pt->param_id.tLine;

			//���󱨸�
			string str;

			if(def)
				str="�ظ�����:����\""+name+"\"�ڵ�"+toString(int(def))+"��������Ϊ������";
			else
				str="���ֳ�ͻ:"+name+"�Ѿ���Ϊ�⺯����ʹ�á�";

			//׷�ӵ���¼
			err_record.insert(make_pair(redef,str));
		}

		//��option'����id����
		pps[pps.size()-2]->getInhAttr()->tail.iLine=pt->param_id.tLine;
		pps[pps.size()-2]->getInhAttr()->tail.iLexime->swap(*(pt->param_id.tLexime));
	}

	static void act_tail1_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//������������
		pi->tail.iType.is_array=true;
		pi->tail.iType.length=0;

		//����������Ϊ�ֲ����鶨��
		context.defineVar(*(pi->tail.iLexime),pi->tail.iType,pi->tail.iLine);

		//�β����ͼ��뺯���β��б�
		context.getFunInfo(context.getName())->param_list.push_back(pi->tail.iType);
	}
	static void act_tail2_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//���ɱ�������
		pi->tail.iType.is_array=false;

		//����������Ϊ�ֲ���������
		context.defineVar(*(pi->tail.iLexime),pi->tail.iType,pi->tail.iLine);

		//�β����ͼ��뺯���β��б�
		context.getFunInfo(context.getName())->param_list.push_back(pi->tail.iType);
	}

	static void act_size_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//��S(size)����A(const)����
		pps[pps.size()-2]->getSynAttr()->size.tLine=pps.back()->getTempVar()->A_const.tLine;
		pps[pps.size()-2]->getSynAttr()->size.tValue=pps.back()->getTempVar()->A_const.tValue;
	}

	static void act_stmt2_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//ת����value
		ControlFlow2Value(context,pps.back()->getSynAttr());
	}

	static void act_stmt3_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//ת����control flow
		bool yes=Value2ControlFlow(context,ps);

		//ת���ɹ�
		if(yes)
		{
			//����true��֧
			context.BackPatch(ps->expr.spTrueList,context.getNextInstr());

			//��expr.falselist���Դ��ݸ�E
			pps[pps.size()-5]->getInhAttr()->E.ipFalseList=ps->expr.spFalseList;

			//expr.falselistָ�븳��
			ps->expr.spFalseList=0;
		}
		else
		{
			//���󱨸�
			string str="if����������ʽ���ʹ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pps.back()->getTempVar()->if_line.tLine,str));
		}
	}
	static void act_stmt3_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//��S2(stmt)��nextlist���Դ��ݸ�E
		pps[pps.size()-2]->getInhAttr()->E.ipNextList=ps->stmt.spNextList;

		//S2(stmt)��nextlistָ�븳��
		ps->stmt.spNextList=0;

		//S2(stmt)��ret_cnt����stmt3
		pps[pps.size()-4]->getSynAttr()->stmt.sRetCnt=ps->stmt.sRetCnt;
	}
	static void act_stmt3_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S3(E)��nextlist����stmt3��nextlist
		if(ps->E.spNextList)
			pps[pps.size()-2]->getSynAttr()->stmt.spNextList->swap(*(ps->E.spNextList));	//ʹ�ý������渳ֵ,�����ִ��Ч��

		//S3(E)��ret_cnt�ۼӵ�stmt3
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

		//ת����control flow
		bool yes=Value2ControlFlow(context,ps);

		//ת���ɹ�
		if(yes)
		{
			//����true��֧
			context.BackPatch(ps->expr.spTrueList,context.getNextInstr());

			//��expr.falselist���Ը���stmt4��nextlist
			if(ps->expr.spFalseList)
				pps[pps.size()-5]->getSynAttr()->stmt.spNextList->swap(*(ps->expr.spFalseList));
		}
		else
		{
			//���󱨸�
			string str="while����������ʽ���ʹ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pps.back()->getTempVar()->while_line.tLine,str));
		}	

		//stmt4��nextlist��Ϊibreaklist���ݸ�stmt
		pps[pps.size()-3]->getInhAttr()->stmt.ipBreakList=pps[pps.size()-5]->getSynAttr()->stmt.spNextList;

		//S2(stmt)��icontinuelist���ݸ�stmt
		pps[pps.size()-3]->getInhAttr()->stmt.ipContinueList=pps[pps.size()-4]->getTempVar()->while_begin_continue_list.tpContinueList;
	}
	static void act_stmt4_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//ѭ����ʼ���
		instr begin=pt->while_begin_continue_list.tBegin;

		//����icontinuelist��nextlist
		context.BackPatch(pt->while_begin_continue_list.tpContinueList,begin);
		context.BackPatch(ps->stmt.spNextList,begin);

		//��ת��ѭ����ʼ��
		context.Gen(op_goto,context.getAddress(int(begin)));

		//S2(stmt)��ret_cnt����stmt4
		pps[pps.size()-2]->getSynAttr()->stmt.sRetCnt=ps->stmt.sRetCnt;
	}

	static void act_stmt5_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//nextinstr->S2:begin
		pps[pps.size()-7]->getTempVar()->do_expr.tBegin=context.getNextInstr();

		//stmt5��nextlist��Ϊibreaklist���ݸ�stmt
		pps[pps.size()-2]->getInhAttr()->stmt.ipBreakList=pps[pps.size()-10]->getSynAttr()->stmt.spNextList;

		//S1(stmt)��icontinuelist���ݸ�stmt
		pps[pps.size()-2]->getInhAttr()->stmt.ipContinueList=pps[pps.size()-3]->getTempVar()->do_stmt_continue_list.tpContinueList;
	}
	static void act_stmt5_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//����icontinuelist��nextlist
		instr next=context.getNextInstr();
		context.BackPatch(pt->do_stmt_continue_list.tpContinueList,next);
		context.BackPatch(ps->stmt.spNextList,next);

		//S1(stmt)��ret_cnt����stmt5
		pps[pps.size()-8]->getSynAttr()->stmt.sRetCnt=ps->stmt.sRetCnt;
	}
	static void act_stmt5_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//ת����control flow
		bool yes=Value2ControlFlow(context,ps);

		//ת���ɹ�
		if(yes)
		{
			//����true��֧
			context.BackPatch(ps->expr.spTrueList,pt->do_expr.tBegin);

			//��expr.falselist����׷�ӵ�stmt5��nextlist
			Append(&(pps[pps.size()-4]->getSynAttr()->stmt.spNextList),&(ps->expr.spFalseList));
		}
		else
		{
			//���󱨸�
			string str="do-while����������ʽ���ʹ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->do_expr.tLine,str));
		}
	}

	static void act_stmt6_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		if(pi->stmt.ipBreakList)
		{
			//��һ��ָ�����break�����б�
			pi->stmt.ipBreakList->push_back(context.getNextInstr());

			//������תָ��
			context.Gen(op_goto);	//��תĿ���ַ������
		}
		else
		{
			//���󱨸�
			string str="�Ƿ���break��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pps.back()->getTempVar()->break_line.tLine,str));
		}
	}

	static void act_stmt7_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		if(pi->stmt.ipContinueList)
		{
			//��һ��ָ�����continue�����б�
			pi->stmt.ipContinueList->push_back(context.getNextInstr());

			//������תָ��
			context.Gen(op_goto);	//��תĿ���ַ������
		}
		else
		{
			//���󱨸�
			string str="�Ƿ���continue��";

			//׷�ӵ���¼
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

		//optexpr2.falselist���Ը���stmt9��nextlist
		if(ps->optexpr2.spFalseList)
			pps[pps.size()-8]->getSynAttr()->stmt.spNextList->swap(*(ps->optexpr2.spFalseList));

		//optexpr2.truelist���Ը���A2
		pps[pps.size()-4]->getTempVar()->for_expr.tpOptexpr2TrueList=ps->optexpr2.spTrueList;
		ps->optexpr2.spTrueList=0;

		//nextinstr->S2:continue
		pps[pps.size()-7]->getTempVar()->for_stmt_continue_continue_list.tContinue=context.getNextInstr();
	}
	static void act_stmt9_A2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Temp_Var *pt=pps.back()->getTempVar();

		//������ת��begin��ָ��
		context.Gen(op_goto,context.getAddress(int(pps.back()->getTempVar()->for_expr.tBegin)));

		//�����������ʽ�������
		context.BackPatch(pt->for_expr.tpOptexpr2TrueList,context.getNextInstr());

		//stmt9��nextlist��Ϊibreaklist���ݸ�stmt
		pps[pps.size()-3]->getInhAttr()->stmt.ipBreakList=pps[pps.size()-5]->getSynAttr()->stmt.spNextList;

		//S2(stmt)��icontinuelist���ݸ�stmt
		pps[pps.size()-3]->getInhAttr()->stmt.ipContinueList=pps[pps.size()-4]->getTempVar()->for_stmt_continue_continue_list.tpContinueList;
	}
	static void act_stmt9_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//ѭ��continue���
		instr continue_label=pt->for_stmt_continue_continue_list.tContinue;

		//����icontinuelist��nextlist
		context.BackPatch(pt->for_stmt_continue_continue_list.tpContinueList,continue_label);
		context.BackPatch(ps->stmt.spNextList,continue_label);

		//��ת��ѭ��continue��
		context.Gen(op_goto,context.getAddress(int(continue_label)));

		//S2(stmt)��ret_cnt����stmt4
		pps[pps.size()-2]->getSynAttr()->stmt.sRetCnt=ps->stmt.sRetCnt;
	}

	static void act_stmt10_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//ת����value
		ControlFlow2Value(context,ps);

		if(ps->expr.sType.is_array)
		{
			//���󱨸�
			string str="switch�ı��ʽ���������顣";

			//׷�ӵ���¼
			err_record.insert(make_pair(pps.back()->getTempVar()->switch_expr_line.tLine,str));
		}
		//���Ϊ����
		else if(isInteger(ps->expr.sType.type))
		{
			//��һ����תָ�����S2��testlist�����б�
			pps[pps.size()-4]->getTempVar()->swtich_stmt_testlist_var_instr_list.tpTestList->push_back(context.getNextInstr());

			//������תָ��
			context.Gen(op_goto);	//��תĿ���ַ������

			//stmt10��nextlist��Ϊibreaklist���ݸ�stmt
			pps[pps.size()-3]->getInhAttr()->stmt.ipBreakList=pps[pps.size()-5]->getSynAttr()->stmt.spNextList;

			//expr.addr���ݸ�stmt.iaddr
			pps[pps.size()-3]->getInhAttr()->stmt.iAddr=ps->expr.sAddr;

			//S2��var_instr_list���ݸ�stmt
			pps[pps.size()-3]->getInhAttr()->stmt.ipVarInstrList=pps[pps.size()-4]->getTempVar()->swtich_stmt_testlist_var_instr_list.tpVarInstrList;
		
			//expr.addrͬʱ���ݸ�S2
			pps[pps.size()-4]->getTempVar()->swtich_stmt_testlist_var_instr_list.tAddr=ps->expr.sAddr;
		}
		else
		{
			//���󱨸�
			string str="switch�ı��ʽ�������͡�";

			//׷�ӵ���¼
			err_record.insert(make_pair(pps.back()->getTempVar()->switch_expr_line.tLine,str));
		}
	}
	static void act_stmt10_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//��һ����תָ�����nextlist�����б�
		ps->stmt.spNextList->push_back(context.getNextInstr());

		//������תָ��
		context.Gen(op_goto);	//��תĿ���ַ������

		//����testlist
		context.BackPatch(pt->swtich_stmt_testlist_var_instr_list.tpTestList,context.getNextInstr());

		//������ʱ��������
		VarInfo vi;
		vi.type=t_INT;
		vi.is_array=false;

		//��ʱ������ַ
		Address temp_addr;

		//���ʽ��ַ
		Address expr_addr=pt->swtich_stmt_testlist_var_instr_list.tAddr;

		//case/default��֧��ŵ�ַ
		Address label_addr;

		//case/default��֧��תĿ��
		instr target;

		//���ɸ�case/default��֧�Ĳ��Դ���
		while(!pt->swtich_stmt_testlist_var_instr_list.tpVarInstrList->empty())
		{
			//default��ű���������
			if(pt->swtich_stmt_testlist_var_instr_list.tpVarInstrList->front().first && 1<pt->swtich_stmt_testlist_var_instr_list.tpVarInstrList->size())
			{
				pt->swtich_stmt_testlist_var_instr_list.tpVarInstrList->push_back(pt->swtich_stmt_testlist_var_instr_list.tpVarInstrList->front());
			}
			else
			{			
				//������ʱ������ַ
				temp_addr=context.Temp(vi);

				//��ȡ��֧��ŵ�ַ
				label_addr=pt->swtich_stmt_testlist_var_instr_list.tpVarInstrList->front().second.first;

				//��ȡ��֧��תĿ��
				target=pt->swtich_stmt_testlist_var_instr_list.tpVarInstrList->front().second.second;

				//�������ʽ���űȽ�ָ��
				context.Gen(op_sub,expr_addr,label_addr,temp_addr);

				//�������Բ���תָ��
				context.Gen(op_if_false_goto,temp_addr,context.getAddress(int(target)));
			}

			pt->swtich_stmt_testlist_var_instr_list.tpVarInstrList->pop_front();
		}

		//��S2(stmt)��nextlist����׷�ӵ�stmt10��nextlist
		Append(&(pps[pps.size()-2]->getSynAttr()->stmt.spNextList),&(ps->stmt.spNextList));

		//S2(stmt)��ret_cnt����stmt10
		pps[pps.size()-2]->getSynAttr()->stmt.sRetCnt=ps->stmt.sRetCnt;
	}

	static void act_stmt11_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Syn_Attr *ps=pps.back()->getSynAttr();

		if(pi->stmt.ipBreakList && pi->stmt.ipVarInstrList)
		{
			//�����ŵ�ַ
			Address label_addr=context.getAddress(int(ps->label.tValue));

			//��ű���Ψһ
			if(isExist(pi->stmt.ipVarInstrList,label_addr))
			{
				//���󱨸�
				string str="case���ֵ\""+toString(int(ps->label.tValue))+"\"��ʹ�á�";

				//׷�ӵ���¼
				err_record.insert(make_pair(ps->label.tLine,str));
			}
			else
			{
				//��ŵ�ַ�ʹ����ַ�����б�
				pi->stmt.ipVarInstrList->push_back(make_pair(false,make_pair(label_addr,context.getNextInstr())));
			}
		}
		else
		{
			//���󱨸�
			string str="�Ƿ���case��";

			//׷�ӵ���¼
			err_record.insert(make_pair(ps->label.tLine,str));
		}
	}
	static void act_stmt11_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S2(stmt)��nextlist����stmt11��nextlist
		if(ps->stmt.spNextList)
			pps[pps.size()-2]->getSynAttr()->stmt.spNextList->swap(*(ps->stmt.spNextList));	//ʹ�ý������渳ֵ,�����ִ��Ч��

		//S2(stmt)��ret_cnt����stmt11
		pps[pps.size()-2]->getSynAttr()->stmt.sRetCnt=ps->stmt.sRetCnt;
	}

	static void act_stmt12_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{	
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		if(pi->stmt.ipBreakList && pi->stmt.ipVarInstrList && s_INVALID!=pi->stmt.iAddr.section)
		{
			//default����Ψһ
			if(isExist(pi->stmt.ipVarInstrList,pi->stmt.iAddr))
			{
				//���󱨸�
				string str="default����һ����";

				//׷�ӵ���¼
				err_record.insert(make_pair(pt->op_line.tLine,str));
			}
			else
			{
				//��ŵ�ַ�ʹ����ַ�����б�
				pi->stmt.ipVarInstrList->push_back(make_pair(true,make_pair(pi->stmt.iAddr,context.getNextInstr())));
			}
		}
		else
		{
			//���󱨸�
			string str="�Ƿ���default��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}

	}
	static void act_stmt12_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(stmt)��nextlist����stmt12��nextlist
		if(ps->stmt.spNextList)
			pps[pps.size()-2]->getSynAttr()->stmt.spNextList->swap(*(ps->stmt.spNextList));	//ʹ�ý������渳ֵ,�����ִ��Ч��

		//S(stmt)��ret_cnt����stmt12
		pps[pps.size()-2]->getSynAttr()->stmt.sRetCnt=ps->stmt.sRetCnt;
	}

	static void act_stmt13_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(stmts)��nextlist����stmt13��nextlist
		if(ps->stmts.spNextList)
			pps[pps.size()-3]->getSynAttr()->stmt.spNextList->swap(*(ps->stmts.spNextList));	//ʹ�ý������渳ֵ,�����ִ��Ч��

		//S(stmts)��ret_cnt����stmt13
		pps[pps.size()-3]->getSynAttr()->stmt.sRetCnt=ps->stmts.sRetCnt;
	}

	static void act_E1_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();	
		
		//��һ����תָ�����E��inextlist�����б�
		if(pi->E.ipNextList)
			pi->E.ipNextList->push_back(context.getNextInstr());

		//������תָ��
		context.Gen(op_goto);	//��תĿ���ַ������

		//����E��ifalselist�б�
		context.BackPatch(pi->E.ipFalseList,context.getNextInstr());

		//����E��inextlist��S(stmt)
		pps[pps.size()-3]->getInhAttr()->E.ipNextList=pi->E.ipNextList;

		//����A��inextlist
		pi->E.ipNextList=0;
	}
	static void act_E1_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//E��inextlist��S(stmt)��nextlist�ϲ���E��nextlist
		Append(&(ps->stmt.spNextList),&(pi->E.ipNextList));
		if(ps->stmt.spNextList)
			pps[pps.size()-2]->getSynAttr()->E.spNextList->swap(*(ps->stmt.spNextList));

		//S(stmt)��ret_cnt����E
		pps[pps.size()-2]->getSynAttr()->E.sRetCnt=ps->stmt.sRetCnt;
	}
	static void act_E2_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();	

		//E��inextlist��ifalselist�ϲ���E��nextlist
		Append(&(pps[pps.size()-2]->getSynAttr()->E.spNextList),&(pi->E.ipNextList));
		Append(&(pps[pps.size()-2]->getSynAttr()->E.spNextList),&(pi->E.ipFalseList));
	}

	static void act_stmts1_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S1(stmt)��nextlist
		context.BackPatch(ps->stmt.spNextList,context.getNextInstr());

		//S1(stmt)��ret_cnt����stmts
		pps[pps.size()-4]->getSynAttr()->stmts.sRetCnt=ps->stmt.sRetCnt;
	}
	static void act_stmts1_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S2(stmts)��nextlist����stmts
		if(ps->stmts.spNextList)
			pps[pps.size()-2]->getSynAttr()->stmts.spNextList->swap(*(ps->stmts.spNextList));

		//S2(stmts)��ret_cnt�ۼӵ�stmts
		pps[pps.size()-2]->getSynAttr()->stmts.sRetCnt+=ps->stmts.sRetCnt;
	}

	static void act_optexpr2A_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();	
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�������ֵ���ʽ
		if(pi->optexpr2.iValFlag)
		{
			//ת����value��ʽ
			ControlFlow2Value(context,ps);
		}
		//����ǿ�����
		else
		{
			//ת����control flow
			bool yes=Value2ControlFlow(context,ps);

			//ת���ɹ�
			if(yes)
			{
				//S(expr)�Ļ����б���optexpr2
				if(ps->expr.spTrueList)
					pps[pps.size()-2]->getSynAttr()->optexpr2.spTrueList->swap(*(ps->expr.spTrueList));
				if(ps->expr.spFalseList)
					pps[pps.size()-2]->getSynAttr()->optexpr2.spFalseList->swap(*(ps->expr.spFalseList));
			}
			else
			{
				//���󱨸�
				string str="for����������ʽ���ʹ���";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->optexpr2.iLine,str));
			}
		}
	}
	static void act_optexpr2B_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//����ǿ�����
		if(!pps.back()->getInhAttr()->optexpr2.iValFlag)
		{
			//Ĭ�Ͽյı��ʽ��ʾ��ԶΪ��
			pps[pps.size()-2]->getSynAttr()->optexpr2.spTrueList->push_back(context.getNextInstr());

			//����ֱ����ת������ڵ�ָ��
			context.Gen(op_goto);	//��תĿ���ַ������
		}
	}

	static void act_optexpr3A_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();	
		Syn_Attr *ps=pps.back()->getSynAttr();

		//ת����value��ʽ
		ControlFlow2Value(context,ps);

		//��ȡ�����ĺ�����
		string name=context.getName();

		//��ȡ�����ĺ�����Ϣ
		FunInfo const& fun_info=*context.getFunInfo(name);

		//�����޷�������
		if(t_VOID==fun_info.ret_type)
		{
			if(t_VOID==ps->expr.sType.type)
			{
				//���ɷ���ָ��
				context.Gen(op_return);
			}
			else
			{
				//���󱨸�
				string str="\"void\"����"+name+"����ֵ��";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->optexpr3.iLine,str));
			}
		}
		//�����з�������
		else
		{
			//�ɼ�������
			if(Computable(ps->expr.sType))
			{				
				//���ɷ���ָ��
				context.Gen(op_return_value,ps->expr.sAddr);
			}
			else
			{
				//���󱨸�
				string str="����"+name+"�������ʹ���";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->optexpr3.iLine,str));
			}
		}
	}
	static void act_optexpr3B_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();	

		//��ȡ�����ĺ�����
		string name=context.getName();

		//��ȡ�����ĺ�����Ϣ
		FunInfo const& fun_info=*context.getFunInfo(name);

		//�����޷�������
		if(t_VOID==fun_info.ret_type)
		{
			//���ɷ���ָ��
			context.Gen(op_return);
		}
		//�����з�������
		else
		{
			//���󱨸�
			string str="����"+name+"���뷵��ֵ��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->optexpr3.iLine,str));
		}
	}

	static void act_label_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//��S(label)����A(const)����
		pps[pps.size()-2]->getSynAttr()->label.tLine=pps.back()->getTempVar()->case_const.tLine;
		pps[pps.size()-2]->getSynAttr()->label.tValue=pps.back()->getTempVar()->case_const.tValue;
	}
	static void act_label_A2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//��S(label)����A(const)����
		pps[pps.size()-2]->getSynAttr()->label.tLine=pps.back()->getTempVar()->case_const.tLine;
		pps[pps.size()-2]->getSynAttr()->label.tValue=-(pps.back()->getTempVar()->case_const.tValue);
	}

	static void act_expr_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//��expr'����e1
		pps[pps.size()-2]->getInhAttr()->expr_.iValFlag=ps->e1.sValFlag;
		pps[pps.size()-2]->getInhAttr()->expr_.iType=ps->e1.sType;
		pps[pps.size()-2]->getInhAttr()->expr_.iAddr=ps->e1.sAddr;
		pps[pps.size()-2]->getInhAttr()->expr_.ipTrueList=ps->e1.spTrueList;	//ʹ��ǳ����
		pps[pps.size()-2]->getInhAttr()->expr_.ipFalseList=ps->e1.spFalseList;

		//����e1��̬�ڴ�ָ��
		ps->e1.spTrueList=0;
		ps->e1.spFalseList=0;
	}
	static void act_expr_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();
		
		//expr'���ۺ����Ը���expr
		pps[pps.size()-2]->getSynAttr()->expr.sValFlag=ps->expr_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->expr.sType=ps->expr_.sType;
		pps[pps.size()-2]->getSynAttr()->expr.sAddr=ps->expr_.sAddr;
		if(ps->expr_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->expr.spTrueList->swap(*(ps->expr_.spTrueList));	//����ʹ��ǳ����
		if(ps->expr_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->expr.spFalseList->swap(*(ps->expr_.spFalseList));	
	}

	static void act_expr_1_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//expr'ת����value��ʽ
		ControlFlow2Value(context,pi);
	}
	static void act_expr_1_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//e1ת����value��ʽ
		ControlFlow2Value(context,ps);

		//��expr'1����e1
		pps[pps.size()-2]->getInhAttr()->expr_.iValFlag=true;
		pps[pps.size()-2]->getInhAttr()->expr_.iType=ps->e1.sType;
		pps[pps.size()-2]->getInhAttr()->expr_.iAddr=ps->e1.sAddr;
	}
	static void act_expr_1_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//expr'1���ۺ����Ը���expr'
		pps[pps.size()-2]->getSynAttr()->expr_=ps->expr_;	//ʹ��ǳ����

		//����expr'1��̬�ڴ�ָ��
		ps->expr_.spTrueList=0;
		ps->expr_.spFalseList=0;		
	}
	static void act_expr_2_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//A(expr')�ļ̳����Դ��ظ�expr'���ۺ�����
		pps[pps.size()-2]->getSynAttr()->expr_.sValFlag=pi->expr_.iValFlag;	
		pps[pps.size()-2]->getSynAttr()->expr_.sType=pi->expr_.iType;
		pps[pps.size()-2]->getSynAttr()->expr_.sAddr=pi->expr_.iAddr;

		Append(&(pps[pps.size()-2]->getSynAttr()->expr_.spTrueList),&(pi->expr_.ipTrueList));
		Append(&(pps[pps.size()-2]->getSynAttr()->expr_.spFalseList),&(pi->expr_.ipFalseList));

		//����ָ��
		//pi->expr_.ipTrueList=0;
		//pi->expr_.ipFalseList=0;
	}

	static void act_e1A_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Temp_Var *pt=pps.back()->getTempVar();

		//id���Դ��ݸ�T1
		pps[pps.size()-2]->getInhAttr()->T1.iLine=pt->e1_id.tLine;
		pps[pps.size()-2]->getInhAttr()->T1.iLexime->swap(*(pt->e1_id.tLexime));
	}
	static void act_e1A_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//T1���ۺ����Ը���e1
		pps[pps.size()-2]->getSynAttr()->e1.sValFlag=pps.back()->getSynAttr()->T1.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e1.sType=pps.back()->getSynAttr()->T1.sType;
		pps[pps.size()-2]->getSynAttr()->e1.sAddr=pps.back()->getSynAttr()->T1.sAddr;
		if(ps->T1.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e1.spTrueList->swap(*(ps->T1.spTrueList));	//����ʹ��ǳ����
		if(ps->T1.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e1.spFalseList->swap(*(ps->T1.spFalseList));
	}
	static void act_e1B_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//e2���ۺ����Ը���e1
		pps[pps.size()-2]->getSynAttr()->e1.sValFlag=pps.back()->getSynAttr()->e2.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e1.sType=pps.back()->getSynAttr()->e2.sType;
		pps[pps.size()-2]->getSynAttr()->e1.sAddr=pps.back()->getSynAttr()->e2.sAddr;
		if(ps->e2.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e1.spTrueList->swap(*(ps->e2.spTrueList));	//����ʹ��ǳ����
		if(ps->e2.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e1.spFalseList->swap(*(ps->e2.spFalseList));
	}

	static void act_e2_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//��e2'����e3
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3.spTrueList;	//ʹ��ǳ����
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3.spFalseList;

		//����e3��̬�ڴ�ָ��
		ps->e3.spTrueList=0;
		ps->e3.spFalseList=0;
	}
	static void act_e2_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//e2'���ۺ����Ը���e2
		pps[pps.size()-2]->getSynAttr()->e2.sValFlag=ps->e2_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e2.sType=ps->e2_.sType;
		pps[pps.size()-2]->getSynAttr()->e2.sAddr=ps->e2_.sAddr;
		if(ps->e2_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e2.spTrueList->swap(*(ps->e2_.spTrueList));	//����ʹ��ǳ����
		if(ps->e2_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e2.spFalseList->swap(*(ps->e2_.spFalseList));	
	}

	static void act_e2_1_A1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//ת����control flow
		bool yes=Value2ControlFlow(context,pi,pi->e2_.iSection);

		//ת���ɹ�
		if(yes)
		{
			//����true��֧
			context.BackPatch(pi->e2_.ipTrueList,context.getNextInstr(pi->e2_.iSection),pi->e2_.iSection);

			//��e2'.falselist���Դ��ݸ�S1
			pps[pps.size()-3]->getInhAttr()->e2_.ipFalseList=pi->e2_.ipFalseList;

			//e2'.falselistָ�븳��
			pi->e2_.ipFalseList=0;
		}
		else
		{
			//���󱨸�
			string str="�������ʽ�ĵ�һ���ӱ��ʽ���ʹ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pps.back()->getTempVar()->op_line.tLine,str));
		}
	}
	static void act_e2_1_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//ת����value
		ControlFlow2Value(context,ps,pi->e2_.iSection);

		//��һ��ָ�����S2��truelist�����б�
		if(pps[pps.size()-5]->getInhAttr()->e2_.ipTrueList)
			pps[pps.size()-5]->getInhAttr()->e2_.ipTrueList->push_back(context.getNextInstr(pi->e2_.iSection));

		//������תָ��
		context.Gen(op_goto,pi->e2_.iSection);	//��תĿ���ַ������

		//����false��֧
		context.BackPatch(pi->e2_.ipFalseList,context.getNextInstr(pi->e2_.iSection),pi->e2_.iSection);

		//e3��type��addr���ݸ�S2
		pps[pps.size()-5]->getInhAttr()->e2_.iType=ps->e3.sType;
		pps[pps.size()-5]->getInhAttr()->e2_.iAddr=ps->e3.sAddr;
	}
	static void act_e2_1_A2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//A2��line���ݸ�S2
		pps[pps.size()-3]->getTempVar()->op_line.tLine=pps.back()->getTempVar()->op_line.tLine;
	}
	static void act_e2_1_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//ת����value
		ControlFlow2Value(context,ps,pi->e2_.iSection);

		//�����ӱ��ʽͬʱΪvoid����
		if(t_VOID==ps->e2.sType.type && t_VOID==pi->e2_.iType.type)
		{
			//����e2'����
			pps[pps.size()-2]->getSynAttr()->e2_.sType.type=t_VOID;

			//�޸�e2'ֵ��־
			pps[pps.size()-2]->getSynAttr()->e2_.sValFlag=true;
		}
		//�����ӱ��ʽͬʱ��Ϊvoid����,��ͬʱ��Ϊ����
		else if(t_VOID!=ps->e2.sType.type && t_VOID!=pi->e2_.iType.type && !ps->e2.sType.is_array && !pi->e2_.iType.is_array)
		{
			//����e2'����
			pps[pps.size()-2]->getSynAttr()->e2_.sType.type=Advance(ps->e2.sType.type,pi->e2_.iType.type);
			pps[pps.size()-2]->getSynAttr()->e2_.sType.is_array=false;

			//����e2'��ַ
			pps[pps.size()-2]->getSynAttr()->e2_.sAddr=context.Temp(pps[pps.size()-2]->getSynAttr()->e2_.sType,pi->e2_.iSection);

			//�޸�e2'ֵ��־
			pps[pps.size()-2]->getSynAttr()->e2_.sValFlag=true;

			//����e2��value����e2'�Ĵ���
			context.Gen(op_assign,pps[pps.size()-2]->getSynAttr()->e2_.sAddr,ps->e2.sAddr,pi->e2_.iSection);

			//��һ��ָ�����S2��falselist�����б�
			if(pi->e2_.ipFalseList)
				pi->e2_.ipFalseList->push_back(context.getNextInstr(pi->e2_.iSection));

			//������תָ��
			context.Gen(op_goto,pi->e2_.iSection);	//��תĿ���ַ������

			//����S2��truelist
			context.BackPatch(pi->e2_.ipTrueList,context.getNextInstr(pi->e2_.iSection));

			//����e3��value����e2'�Ĵ���
			context.Gen(op_assign,pps[pps.size()-2]->getSynAttr()->e2_.sAddr,pi->e2_.iAddr,pi->e2_.iSection);

			//����S2��falselist
			context.BackPatch(pi->e2_.ipFalseList,context.getNextInstr(pi->e2_.iSection));

			//����no-opָ��
			context.Gen(op_no_op,pi->e2_.iSection);
		}
		else
		{
			//���󱨸�
			string str="�������ʽ�ĵ�2���ӱ��ʽ�͵�3���ӱ��ʽ�����Ͳ����ݡ�";

			//׷�ӵ���¼
			err_record.insert(make_pair(pps.back()->getTempVar()->op_line.tLine,str));
		}
	}
	static void act_e2_2_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//A(e2')�ļ̳����Դ��ظ�e2'���ۺ�����
		pps[pps.size()-2]->getSynAttr()->e2_.sValFlag=pi->e2_.iValFlag;	
		pps[pps.size()-2]->getSynAttr()->e2_.sType=pi->e2_.iType;
		pps[pps.size()-2]->getSynAttr()->e2_.sAddr=pi->e2_.iAddr;
		Append(&(pps[pps.size()-2]->getSynAttr()->e2_.spTrueList),&(pi->e2_.ipTrueList));
		Append(&(pps[pps.size()-2]->getSynAttr()->e2_.spFalseList),&(pi->e2_.ipFalseList));

		//����ָ��
		//pi->e2_.ipTrueList=0;		
		//pi->e2_.ipFalseList=0;	
	}

	static void act_e3_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//��e3'����e4
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4.spTrueList;		//ʹ��ǳ����
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4.spFalseList;

		//����e4��̬�ڴ�ָ��
		ps->e4.spTrueList=0;
		ps->e4.spFalseList=0;	
	}
	static void act_e3_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//e3'���ۺ����Ը���e3
		pps[pps.size()-2]->getSynAttr()->e3.sValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e3.sType=ps->e3_.sType;
		pps[pps.size()-2]->getSynAttr()->e3.sAddr=ps->e3_.sAddr;
		if(ps->e3_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e3.spTrueList->swap(*(ps->e3_.spTrueList));	//����ʹ��ǳ����
		if(ps->e3_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e3.spFalseList->swap(*(ps->e3_.spFalseList));			
	}

	static void act_e3_1_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//ת����control flow
		bool yes=Value2ControlFlow(context,pi,pi->e3_.iSection);

		//ת���ɹ�
		if(yes)
		{
			//����false��֧
			context.BackPatch(pi->e3_.ipFalseList,context.getNextInstr(pi->e3_.iSection),pi->e3_.iSection);

			//��e3'.truelist���Դ��ݸ�S1
			pps[pps.size()-3]->getInhAttr()->e3_.ipTrueList=pi->e3_.ipTrueList;

			//e3'.truelistָ�븳��
			pi->e3_.ipTrueList=0;
		}
		else
		{
			//���󱨸�
			string str="|| ����������ʹ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}

		//��op���Դ��ݸ�S1	
		pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
	}
	static void act_e3_1_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//ת����control flow
		bool yes=Value2ControlFlow(context,ps,pi->e3_.iSection);

		//ת���ɹ�
		if(yes)
		{
			//�̳����Դ��ݸ�S�����e3'
			pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=false;
			pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4.spFalseList;
			Append(&(ps->e4.spTrueList),&(pi->e3_.ipTrueList));
			pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4.spTrueList;

			//ָ�븳��
			ps->e4.spTrueList=0;
			ps->e4.spFalseList=0;
		}
		else
		{
			//���󱨸�
			string str="|| �Ҳ��������ʹ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e3_1_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(e3')���ۺ����Ը���e3'
		pps[pps.size()-2]->getSynAttr()->e3_.sValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e3_.sType=ps->e3_.sType;
		pps[pps.size()-2]->getSynAttr()->e3_.sAddr=ps->e3_.sAddr;
		if(ps->e3_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e3_.spTrueList->swap(*(ps->e3_.spTrueList));	//����ʹ��ǳ����
		if(ps->e3_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e3_.spFalseList->swap(*(ps->e3_.spFalseList));
	}
	static void act_e3_2_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//A(e3')�ļ̳����Դ��ظ�e3'���ۺ�����
		pps[pps.size()-2]->getSynAttr()->e3_.sValFlag=pi->e3_.iValFlag;	
		pps[pps.size()-2]->getSynAttr()->e3_.sType=pi->e3_.iType;
		pps[pps.size()-2]->getSynAttr()->e3_.sAddr=pi->e3_.iAddr;
		Append(&(pps[pps.size()-2]->getSynAttr()->e3_.spTrueList),&(pi->e3_.ipTrueList));
		Append(&(pps[pps.size()-2]->getSynAttr()->e3_.spFalseList),&(pi->e3_.ipFalseList));

		//����ָ��
		//pi->e3_.ipTrueList=0;
		//pi->e3_.ipFalseList=0;
	}

	static void act_e4_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//��e4'����e5
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5.spTrueList;		//ʹ��ǳ����
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5.spFalseList;

		//����e5��̬�ڴ�ָ��
		ps->e5.spTrueList=0;
		ps->e5.spFalseList=0;	
	}
	static void act_e4_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//e4'���ۺ����Ը���e4
		pps[pps.size()-2]->getSynAttr()->e4.sValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e4.sType=ps->e4_.sType;
		pps[pps.size()-2]->getSynAttr()->e4.sAddr=ps->e4_.sAddr;
		if(ps->e4_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e4.spTrueList->swap(*(ps->e4_.spTrueList));	//����ʹ��ǳ����
		if(ps->e4_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e4.spFalseList->swap(*(ps->e4_.spFalseList));	
	}

	static void act_e4_1_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//ת����control flow
		bool yes=Value2ControlFlow(context,pi,pi->e4_.iSection);

		//ת���ɹ�
		if(yes)
		{
			//����true��֧
			context.BackPatch(pi->e4_.ipTrueList,context.getNextInstr(pi->e4_.iSection),pi->e4_.iSection);

			//��e4'.falselist���Դ��ݸ�S1
			pps[pps.size()-3]->getInhAttr()->e4_.ipFalseList=pi->e4_.ipFalseList;

			//e4'.falselistָ�븳��
			pi->e4_.ipFalseList=0;
		}
		else
		{
			//���󱨸�
			string str="&& ����������ʹ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}			
		
		//��op���Դ��ݸ�S1
		pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
	}
	static void act_e4_1_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//ת����control flow
		bool yes=Value2ControlFlow(context,ps,pi->e4_.iSection);

		//ת���ɹ�
		if(yes)
		{
			//�̳����Դ��ݸ�S�����e4'
			pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=false;
			Append(&(ps->e5.spFalseList),&(pi->e4_.ipFalseList));
			pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5.spFalseList;
			pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5.spTrueList;

			//ָ�븳��
			ps->e5.spTrueList=0;
			ps->e5.spFalseList=0;
		}
		else
		{
			//���󱨸�
			string str="&& �Ҳ��������ʹ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e4_1_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(e4')���ۺ����Ը���e4'
		pps[pps.size()-2]->getSynAttr()->e4_.sValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e4_.sType=ps->e4_.sType;
		pps[pps.size()-2]->getSynAttr()->e4_.sAddr=ps->e4_.sAddr;
		if(ps->e4_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e4_.spTrueList->swap(*(ps->e4_.spTrueList));	//����ʹ��ǳ����
		if(ps->e4_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e4_.spFalseList->swap(*(ps->e4_.spFalseList));
	}
	static void act_e4_2_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//A(e4')�ļ̳����Դ��ظ�e4'���ۺ�����
		pps[pps.size()-2]->getSynAttr()->e4_.sValFlag=pi->e4_.iValFlag;	
		pps[pps.size()-2]->getSynAttr()->e4_.sType=pi->e4_.iType;
		pps[pps.size()-2]->getSynAttr()->e4_.sAddr=pi->e4_.iAddr;
		Append(&(pps[pps.size()-2]->getSynAttr()->e4_.spTrueList),&(pi->e4_.ipTrueList));
		Append(&(pps[pps.size()-2]->getSynAttr()->e4_.spFalseList),&(pi->e4_.ipFalseList));

		//����ָ��
		//pi->e4_.ipTrueList=0;
		//pi->e4_.ipFalseList=0;
	}

	static void act_e5_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//��e5'����e6
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6.spTrueList;		//ʹ��ǳ����
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6.spFalseList;

		//����e6��̬�ڴ�ָ��
		ps->e6.spTrueList=0;
		ps->e6.spFalseList=0;	
	}
	static void act_e5_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//e5'���ۺ����Ը���e5
		pps[pps.size()-2]->getSynAttr()->e5.sValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e5.sType=ps->e5_.sType;
		pps[pps.size()-2]->getSynAttr()->e5.sAddr=ps->e5_.sAddr;
		if(ps->e5_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e5.spTrueList->swap(*(ps->e5_.spTrueList));	//����ʹ��ǳ����
		if(ps->e5_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e5.spFalseList->swap(*(ps->e5_.spFalseList));
	}

	static void act_e5_1_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//ת����value
		ControlFlow2Value(context,pi,pi->e5_.iSection);

		//��������������������
		if(isInteger(pi->e5_.iType.type))
		{
			//��e5'.addr���Դ��ݸ�S1
			pps[pps.size()-3]->getInhAttr()->e5_.iAddr=pi->e5_.iAddr;

			//��op���Դ��ݸ�S1
			pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
		}
		else
		{
			//���󱨸�
			string str="| ����������ͱ��������͡�";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e5_1_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//ת����value
		ControlFlow2Value(context,ps,pi->e5_.iSection);

		if(ps->e6.sType.is_array)
		{
			//���󱨸�
			string str="| �Ҳ��������������顣";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
		//����Ҳ���������������
		else if(isInteger(ps->e6.sType.type))
		{
			//�̳����Դ��ݸ�S�����e5'
			pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e5_.iType.type=t_INT;
			pps[pps.size()-2]->getInhAttr()->e5_.iType.is_array=false;
			pps[pps.size()-2]->getInhAttr()->e5_.iAddr=context.Temp(pps[pps.size()-2]->getInhAttr()->e5_.iType,pi->e5_.iSection);

			//���ɲ���ָ�����
			context.Gen(op_bit_or,pi->e5_.iAddr,ps->e6.sAddr,pps[pps.size()-2]->getInhAttr()->e5_.iAddr,pi->e5_.iSection);
		}
		else
		{
			//���󱨸�
			string str="| �Ҳ��������ͱ��������͡�";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e5_1_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(e5')���ۺ����Ը���e5'
		pps[pps.size()-2]->getSynAttr()->e5_.sValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e5_.sType=ps->e5_.sType;
		pps[pps.size()-2]->getSynAttr()->e5_.sAddr=ps->e5_.sAddr;
		if(ps->e5_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e5_.spTrueList->swap(*(ps->e5_.spTrueList));	//����ʹ��ǳ����
		if(ps->e5_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e5_.spFalseList->swap(*(ps->e5_.spFalseList));
	}
	static void act_e5_2_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//A(e5')�ļ̳����Դ��ظ�e5'���ۺ�����
		pps[pps.size()-2]->getSynAttr()->e5_.sValFlag=pi->e5_.iValFlag;	
		pps[pps.size()-2]->getSynAttr()->e5_.sType=pi->e5_.iType;
		pps[pps.size()-2]->getSynAttr()->e5_.sAddr=pi->e5_.iAddr;
		Append(&(pps[pps.size()-2]->getSynAttr()->e5_.spTrueList),&(pi->e5_.ipTrueList));
		Append(&(pps[pps.size()-2]->getSynAttr()->e5_.spFalseList),&(pi->e5_.ipFalseList));
	
		//����ָ��
		//pi->e5_.ipTrueList=0;
		//pi->e5_.ipFalseList=0;
	}

	static void act_e6_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//��e6'����e7
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7.spTrueList;		//ʹ��ǳ����
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7.spFalseList;

		//����e7��̬�ڴ�ָ��
		ps->e7.spTrueList=0;
		ps->e7.spFalseList=0;	
	}
	static void act_e6_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//e6'���ۺ����Ը���e6
		pps[pps.size()-2]->getSynAttr()->e6.sValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e6.sType=ps->e6_.sType;
		pps[pps.size()-2]->getSynAttr()->e6.sAddr=ps->e6_.sAddr;
		if(ps->e6_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e6.spTrueList->swap(*(ps->e6_.spTrueList));	//����ʹ��ǳ����
		if(ps->e6_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e6.spFalseList->swap(*(ps->e6_.spFalseList));
	}

	static void act_e6_1_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//ת����value
		ControlFlow2Value(context,pi,pi->e6_.iSection);

		//��������������������
		if(isInteger(pi->e6_.iType.type))
		{
			//��e6'.addr���Դ��ݸ�S1
			pps[pps.size()-3]->getInhAttr()->e6_.iAddr=pi->e6_.iAddr;

			//��op���Դ��ݸ�S1
			pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
		}
		else
		{
			//���󱨸�
			string str="^ ����������ͱ��������͡�";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e6_1_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//ת����value
		ControlFlow2Value(context,ps,pi->e6_.iSection);

		if(ps->e7.sType.is_array)
		{
			//���󱨸�
			string str="^ �Ҳ��������������顣";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
		//����Ҳ���������������
		else if(isInteger(ps->e7.sType.type))
		{
			//�̳����Դ��ݸ�S�����e6'
			pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e6_.iType.type=t_INT;
			pps[pps.size()-2]->getInhAttr()->e6_.iType.is_array=false;
			pps[pps.size()-2]->getInhAttr()->e6_.iAddr=context.Temp(pps[pps.size()-2]->getInhAttr()->e6_.iType,pi->e6_.iSection);

			//���ɲ���ָ�����
			context.Gen(op_bit_xor,pi->e6_.iAddr,ps->e7.sAddr,pps[pps.size()-2]->getInhAttr()->e6_.iAddr,pi->e6_.iSection);
		}
		else
		{
			//���󱨸�
			string str="^ �Ҳ��������ͱ��������͡�";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e6_1_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(e6')���ۺ����Ը���e6'
		pps[pps.size()-2]->getSynAttr()->e6_.sValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e6_.sType=ps->e6_.sType;
		pps[pps.size()-2]->getSynAttr()->e6_.sAddr=ps->e6_.sAddr;
		if(ps->e6_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e6_.spTrueList->swap(*(ps->e6_.spTrueList));	//����ʹ��ǳ����
		if(ps->e6_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e6_.spFalseList->swap(*(ps->e6_.spFalseList));
	}
	static void act_e6_2_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//A(e6')�ļ̳����Դ��ظ�e6'���ۺ�����
		pps[pps.size()-2]->getSynAttr()->e6_.sValFlag=pi->e6_.iValFlag;	
		pps[pps.size()-2]->getSynAttr()->e6_.sType=pi->e6_.iType;
		pps[pps.size()-2]->getSynAttr()->e6_.sAddr=pi->e6_.iAddr;
		Append(&(pps[pps.size()-2]->getSynAttr()->e6_.spTrueList),&(pi->e6_.ipTrueList));
		Append(&(pps[pps.size()-2]->getSynAttr()->e6_.spFalseList),&(pi->e6_.ipFalseList));

		//����ָ��
		//pi->e6_.ipTrueList=0;
		//pi->e6_.ipFalseList=0;
	}

	static void act_e7_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//��e7'����e8
		pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=ps->e8.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e7_.iType=ps->e8.sType;
		pps[pps.size()-2]->getInhAttr()->e7_.iAddr=ps->e8.sAddr;
		pps[pps.size()-2]->getInhAttr()->e7_.ipTrueList=ps->e8.spTrueList;		//ʹ��ǳ����
		pps[pps.size()-2]->getInhAttr()->e7_.ipFalseList=ps->e8.spFalseList;

		//����e8��̬�ڴ�ָ��
		ps->e8.spTrueList=0;
		ps->e8.spFalseList=0;	
	}
	static void act_e7_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//e7'���ۺ����Ը���e7
		pps[pps.size()-2]->getSynAttr()->e7.sValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e7.sType=ps->e7_.sType;
		pps[pps.size()-2]->getSynAttr()->e7.sAddr=ps->e7_.sAddr;
		if(ps->e7_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e7.spTrueList->swap(*(ps->e7_.spTrueList));	//����ʹ��ǳ����
		if(ps->e7_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e7.spFalseList->swap(*(ps->e7_.spFalseList));
	}

	static void act_e7_1_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//ת����value
		ControlFlow2Value(context,pi,pi->e7_.iSection);

		//��������������������
		if(isInteger(pi->e7_.iType.type))
		{
			//��e7'.addr���Դ��ݸ�S1
			pps[pps.size()-3]->getInhAttr()->e7_.iAddr=pi->e7_.iAddr;

			//��op���Դ��ݸ�S1
			pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
		}
		else
		{
			//���󱨸�
			string str="& ����������ͱ��������͡�";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e7_1_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//ת����value
		ControlFlow2Value(context,ps,pi->e7_.iSection);

		if(ps->e8.sType.is_array)
		{
			//���󱨸�
			string str="& �Ҳ��������������顣";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
		//����Ҳ���������������
		else if(isInteger(ps->e8.sType.type))
		{
			//�̳����Դ��ݸ�S�����e7'
			pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e7_.iType.type=t_INT;
			pps[pps.size()-2]->getInhAttr()->e7_.iType.is_array=false;
			pps[pps.size()-2]->getInhAttr()->e7_.iAddr=context.Temp(pps[pps.size()-2]->getInhAttr()->e7_.iType,pi->e7_.iSection);

			//���ɲ���ָ�����
			context.Gen(op_bit_and,pi->e7_.iAddr,ps->e8.sAddr,pps[pps.size()-2]->getInhAttr()->e7_.iAddr,pi->e7_.iSection);
		}
		else
		{
			//���󱨸�
			string str="& �Ҳ��������ͱ��������͡�";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e7_1_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(e7')���ۺ����Ը���e7'
		pps[pps.size()-2]->getSynAttr()->e7_.sValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e7_.sType=ps->e7_.sType;
		pps[pps.size()-2]->getSynAttr()->e7_.sAddr=ps->e7_.sAddr;
		if(ps->e7_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e7_.spTrueList->swap(*(ps->e7_.spTrueList));	//����ʹ��ǳ����
		if(ps->e7_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e7_.spFalseList->swap(*(ps->e7_.spFalseList));
	}
	static void act_e7_2_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//A(e7')�ļ̳����Դ��ظ�e7'���ۺ�����
		pps[pps.size()-2]->getSynAttr()->e7_.sValFlag=pi->e7_.iValFlag;	
		pps[pps.size()-2]->getSynAttr()->e7_.sType=pi->e7_.iType;
		pps[pps.size()-2]->getSynAttr()->e7_.sAddr=pi->e7_.iAddr;
		Append(&(pps[pps.size()-2]->getSynAttr()->e7_.spTrueList),&(pi->e7_.ipTrueList));
		Append(&(pps[pps.size()-2]->getSynAttr()->e7_.spFalseList),&(pi->e7_.ipFalseList));

		//����ָ��
		//pi->e7_.ipTrueList=0;	
		//pi->e7_.ipFalseList=0;
	}

	static void act_e8_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//��e8'����e9
		pps[pps.size()-2]->getInhAttr()->e8_.iValFlag=ps->e9.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e8_.iType=ps->e9.sType;
		pps[pps.size()-2]->getInhAttr()->e8_.iAddr=ps->e9.sAddr;
		pps[pps.size()-2]->getInhAttr()->e8_.ipTrueList=ps->e9.spTrueList;		//ʹ��ǳ����
		pps[pps.size()-2]->getInhAttr()->e8_.ipFalseList=ps->e9.spFalseList;

		//����e9��̬�ڴ�ָ��
		ps->e9.spTrueList=0;
		ps->e9.spFalseList=0;	
	}
	static void act_e8_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//e8'���ۺ����Ը���e8
		pps[pps.size()-2]->getSynAttr()->e8.sValFlag=ps->e8_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e8.sType=ps->e8_.sType;
		pps[pps.size()-2]->getSynAttr()->e8.sAddr=ps->e8_.sAddr;
		if(ps->e8_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e8.spTrueList->swap(*(ps->e8_.spTrueList));	//����ʹ��ǳ����
		if(ps->e8_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e8.spFalseList->swap(*(ps->e8_.spFalseList));
	}

	static void act_e8_1_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//ת����value
		ControlFlow2Value(context,pi,pi->e8_.iSection);

		//�������������Ϳɼ���
		if(Computable(pi->e8_.iType))
		{
			//��e8'.addr���Դ��ݸ�S1
			pps[pps.size()-3]->getInhAttr()->e8_.iAddr=pi->e8_.iAddr;

			//��op���Դ��ݸ�S1
			pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
		}
		else
		{
			//���󱨸�
			string str="== ����������ʹ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e8_1_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//ת����value
		ControlFlow2Value(context,ps,pi->e8_.iSection);

		//����Ҳ��������Ϳɼ���
		if(Computable(ps->e9.sType))
		{
			//�̳����Դ��ݸ�S�����e8'
			pps[pps.size()-2]->getInhAttr()->e8_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e8_.iType.type=t_BOOL;
			pps[pps.size()-2]->getInhAttr()->e8_.iType.is_array=false;
			pps[pps.size()-2]->getInhAttr()->e8_.iAddr=context.Temp(pps[pps.size()-2]->getInhAttr()->e8_.iType,pi->e8_.iSection);

			//���ɲ���ָ�����
			context.Gen(op_eq,pi->e8_.iAddr,ps->e9.sAddr,pps[pps.size()-2]->getInhAttr()->e8_.iAddr,pi->e8_.iSection);
		}
		else
		{
			//���󱨸�
			string str="== �Ҳ��������ʹ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e8_1_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(e8')���ۺ����Ը���e8'
		pps[pps.size()-2]->getSynAttr()->e8_.sValFlag=ps->e8_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e8_.sType=ps->e8_.sType;
		pps[pps.size()-2]->getSynAttr()->e8_.sAddr=ps->e8_.sAddr;
		if(ps->e8_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e8_.spTrueList->swap(*(ps->e8_.spTrueList));	//����ʹ��ǳ����
		if(ps->e8_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e8_.spFalseList->swap(*(ps->e8_.spFalseList));
	}
	static void act_e8_2_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//ת����value
		ControlFlow2Value(context,pi,pi->e8_.iSection);

		//�������������Ϳɼ���
		if(Computable(pi->e8_.iType))
		{
			//��e8'.addr���Դ��ݸ�S1
			pps[pps.size()-3]->getInhAttr()->e8_.iAddr=pi->e8_.iAddr;

			//��op���Դ��ݸ�S1
			pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
		}
		else
		{
			//���󱨸�
			string str="!= ����������ʹ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e8_2_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//ת����value
		ControlFlow2Value(context,ps,pi->e8_.iSection);

		//����Ҳ��������Ϳɼ���
		if(Computable(ps->e9.sType))
		{
			//�̳����Դ��ݸ�S�����e8'
			pps[pps.size()-2]->getInhAttr()->e8_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e8_.iType.type=t_BOOL;
			pps[pps.size()-2]->getInhAttr()->e8_.iType.is_array=false;
			pps[pps.size()-2]->getInhAttr()->e8_.iAddr=context.Temp(pps[pps.size()-2]->getInhAttr()->e8_.iType,pi->e8_.iSection);

			//���ɲ���ָ�����
			context.Gen(op_ne,pi->e8_.iAddr,ps->e9.sAddr,pps[pps.size()-2]->getInhAttr()->e8_.iAddr,pi->e8_.iSection);
		}
		else
		{
			//���󱨸�
			string str="!= �Ҳ��������ʹ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e8_2_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(e8')���ۺ����Ը���e8'
		pps[pps.size()-2]->getSynAttr()->e8_.sValFlag=ps->e8_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e8_.sType=ps->e8_.sType;
		pps[pps.size()-2]->getSynAttr()->e8_.sAddr=ps->e8_.sAddr;
		if(ps->e8_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e8_.spTrueList->swap(*(ps->e8_.spTrueList));	//����ʹ��ǳ����
		if(ps->e8_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e8_.spFalseList->swap(*(ps->e8_.spFalseList));
	}
	static void act_e8_3_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//A(e8')�ļ̳����Դ��ظ�e8'���ۺ�����
		pps[pps.size()-2]->getSynAttr()->e8_.sValFlag=pi->e8_.iValFlag;	
		pps[pps.size()-2]->getSynAttr()->e8_.sType=pi->e8_.iType;
		pps[pps.size()-2]->getSynAttr()->e8_.sAddr=pi->e8_.iAddr;
		Append(&(pps[pps.size()-2]->getSynAttr()->e8_.spTrueList),&(pi->e8_.ipTrueList));
		Append(&(pps[pps.size()-2]->getSynAttr()->e8_.spFalseList),&(pi->e8_.ipFalseList));

		//����ָ��
		//pi->e8_.ipTrueList=0;
		//pi->e8_.ipFalseList=0;
	}

	static void act_e9_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//��e9'����e10
		pps[pps.size()-2]->getInhAttr()->e9_.iValFlag=ps->e10.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e9_.iType=ps->e10.sType;
		pps[pps.size()-2]->getInhAttr()->e9_.iAddr=ps->e10.sAddr;
		pps[pps.size()-2]->getInhAttr()->e9_.ipTrueList=ps->e10.spTrueList;		//ʹ��ǳ����
		pps[pps.size()-2]->getInhAttr()->e9_.ipFalseList=ps->e10.spFalseList;

		//����e10��̬�ڴ�ָ��
		ps->e10.spTrueList=0;
		ps->e10.spFalseList=0;	
	}
	static void act_e9_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//e9'���ۺ����Ը���e9
		pps[pps.size()-2]->getSynAttr()->e9.sValFlag=ps->e9_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e9.sType=ps->e9_.sType;
		pps[pps.size()-2]->getSynAttr()->e9.sAddr=ps->e9_.sAddr;
		if(ps->e9_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e9.spTrueList->swap(*(ps->e9_.spTrueList));	//����ʹ��ǳ����
		if(ps->e9_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e9.spFalseList->swap(*(ps->e9_.spFalseList));
	}

	static void act_e9_1_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//ת����value
		ControlFlow2Value(context,pi,pi->e9_.iSection);

		//�������������Ϳɼ���
		if(Computable(pi->e9_.iType))
		{
			//��e9'.addr���Դ��ݸ�S1
			pps[pps.size()-3]->getInhAttr()->e9_.iAddr=pi->e9_.iAddr;

			//��op���Դ��ݸ�S1
			pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
		}
		else
		{
			//���󱨸�
			string str="< ����������ʹ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e9_1_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//ת����value
		ControlFlow2Value(context,ps,pi->e9_.iSection);

		//����Ҳ��������Ϳɼ���
		if(Computable(ps->e10.sType))
		{
			//�̳����Դ��ݸ�S�����e9'
			pps[pps.size()-2]->getInhAttr()->e9_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e9_.iType.type=t_BOOL;
			pps[pps.size()-2]->getInhAttr()->e9_.iType.is_array=false;
			pps[pps.size()-2]->getInhAttr()->e9_.iAddr=context.Temp(pps[pps.size()-2]->getInhAttr()->e9_.iType,pi->e9_.iSection);

			//���ɲ���ָ�����
			context.Gen(op_less,pi->e9_.iAddr,ps->e10.sAddr,pps[pps.size()-2]->getInhAttr()->e9_.iAddr,pi->e9_.iSection);
		}
		else
		{
			//���󱨸�
			string str="< �Ҳ��������ʹ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e9_1_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(e9')���ۺ����Ը���e9'
		pps[pps.size()-2]->getSynAttr()->e9_.sValFlag=ps->e9_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e9_.sType=ps->e9_.sType;
		pps[pps.size()-2]->getSynAttr()->e9_.sAddr=ps->e9_.sAddr;
		if(ps->e9_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e9_.spTrueList->swap(*(ps->e9_.spTrueList));	//����ʹ��ǳ����
		if(ps->e9_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e9_.spFalseList->swap(*(ps->e9_.spFalseList));
	}
	static void act_e9_2_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//ת����value
		ControlFlow2Value(context,pi,pi->e9_.iSection);

		//�������������Ϳɼ���
		if(Computable(pi->e9_.iType))
		{
			//��e9'.addr���Դ��ݸ�S1
			pps[pps.size()-3]->getInhAttr()->e9_.iAddr=pi->e9_.iAddr;

			//��op���Դ��ݸ�S1
			pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
		}
		else
		{
			//���󱨸�
			string str="<= ����������ʹ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e9_2_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//ת����value
		ControlFlow2Value(context,ps,pi->e9_.iSection);

		//����Ҳ��������Ϳɼ���
		if(Computable(ps->e10.sType))
		{
			//�̳����Դ��ݸ�S�����e9'
			pps[pps.size()-2]->getInhAttr()->e9_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e9_.iType.type=t_BOOL;
			pps[pps.size()-2]->getInhAttr()->e9_.iType.is_array=false;
			pps[pps.size()-2]->getInhAttr()->e9_.iAddr=context.Temp(pps[pps.size()-2]->getInhAttr()->e9_.iType,pi->e9_.iSection);

			//���ɲ���ָ�����
			context.Gen(op_le,pi->e9_.iAddr,ps->e10.sAddr,pps[pps.size()-2]->getInhAttr()->e9_.iAddr,pi->e9_.iSection);
		}
		else
		{
			//���󱨸�
			string str="<= �Ҳ��������ʹ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e9_2_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(e9')���ۺ����Ը���e9'
		pps[pps.size()-2]->getSynAttr()->e9_.sValFlag=ps->e9_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e9_.sType=ps->e9_.sType;
		pps[pps.size()-2]->getSynAttr()->e9_.sAddr=ps->e9_.sAddr;
		if(ps->e9_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e9_.spTrueList->swap(*(ps->e9_.spTrueList));	//����ʹ��ǳ����
		if(ps->e9_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e9_.spFalseList->swap(*(ps->e9_.spFalseList));
	}
	static void act_e9_3_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//ת����value
		ControlFlow2Value(context,pi,pi->e9_.iSection);

		//�������������Ϳɼ���
		if(Computable(pi->e9_.iType))
		{
			//��e9'.addr���Դ��ݸ�S1
			pps[pps.size()-3]->getInhAttr()->e9_.iAddr=pi->e9_.iAddr;

			//��op���Դ��ݸ�S1
			pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
		}
		else
		{
			//���󱨸�
			string str="> ����������ʹ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e9_3_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//ת����value
		ControlFlow2Value(context,ps,pi->e9_.iSection);

		//����Ҳ��������Ϳɼ���
		if(Computable(ps->e10.sType))
		{
			//�̳����Դ��ݸ�S�����e9'
			pps[pps.size()-2]->getInhAttr()->e9_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e9_.iType.type=t_BOOL;
			pps[pps.size()-2]->getInhAttr()->e9_.iType.is_array=false;
			pps[pps.size()-2]->getInhAttr()->e9_.iAddr=context.Temp(pps[pps.size()-2]->getInhAttr()->e9_.iType,pi->e9_.iSection);

			//���ɲ���ָ�����
			context.Gen(op_greater,pi->e9_.iAddr,ps->e10.sAddr,pps[pps.size()-2]->getInhAttr()->e9_.iAddr,pi->e9_.iSection);
		}
		else
		{
			//���󱨸�
			string str="> �Ҳ��������ʹ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e9_3_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(e9')���ۺ����Ը���e9'
		pps[pps.size()-2]->getSynAttr()->e9_.sValFlag=ps->e9_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e9_.sType=ps->e9_.sType;
		pps[pps.size()-2]->getSynAttr()->e9_.sAddr=ps->e9_.sAddr;
		if(ps->e9_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e9_.spTrueList->swap(*(ps->e9_.spTrueList));	//����ʹ��ǳ����
		if(ps->e9_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e9_.spFalseList->swap(*(ps->e9_.spFalseList));
	}
	static void act_e9_4_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//ת����value
		ControlFlow2Value(context,pi,pi->e9_.iSection);

		//�������������Ϳɼ���
		if(Computable(pi->e9_.iType))
		{
			//��e9'.addr���Դ��ݸ�S1
			pps[pps.size()-3]->getInhAttr()->e9_.iAddr=pi->e9_.iAddr;

			//��op���Դ��ݸ�S1
			pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
		}
		else
		{
			//���󱨸�
			string str=">= ����������ʹ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e9_4_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//ת����value
		ControlFlow2Value(context,ps,pi->e9_.iSection);

		//����Ҳ��������Ϳɼ���
		if(Computable(ps->e10.sType))
		{
			//�̳����Դ��ݸ�S�����e9'
			pps[pps.size()-2]->getInhAttr()->e9_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e9_.iType.type=t_BOOL;
			pps[pps.size()-2]->getInhAttr()->e9_.iType.is_array=false;
			pps[pps.size()-2]->getInhAttr()->e9_.iAddr=context.Temp(pps[pps.size()-2]->getInhAttr()->e9_.iType,pi->e9_.iSection);

			//���ɲ���ָ�����
			context.Gen(op_ge,pi->e9_.iAddr,ps->e10.sAddr,pps[pps.size()-2]->getInhAttr()->e9_.iAddr,pi->e9_.iSection);
		}
		else
		{
			//���󱨸�
			string str=">= �Ҳ��������ʹ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e9_4_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(e9')���ۺ����Ը���e9'
		pps[pps.size()-2]->getSynAttr()->e9_.sValFlag=ps->e9_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e9_.sType=ps->e9_.sType;
		pps[pps.size()-2]->getSynAttr()->e9_.sAddr=ps->e9_.sAddr;
		if(ps->e9_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e9_.spTrueList->swap(*(ps->e9_.spTrueList));	//����ʹ��ǳ����
		if(ps->e9_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e9_.spFalseList->swap(*(ps->e9_.spFalseList));
	}
	static void act_e9_5_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//A(e9')�ļ̳����Դ��ظ�e9'���ۺ�����
		pps[pps.size()-2]->getSynAttr()->e9_.sValFlag=pi->e9_.iValFlag;	
		pps[pps.size()-2]->getSynAttr()->e9_.sType=pi->e9_.iType;
		pps[pps.size()-2]->getSynAttr()->e9_.sAddr=pi->e9_.iAddr;
		Append(&(pps[pps.size()-2]->getSynAttr()->e9_.spTrueList),&(pi->e9_.ipTrueList));
		Append(&(pps[pps.size()-2]->getSynAttr()->e9_.spFalseList),&(pi->e9_.ipFalseList));

		//����ָ��
		//pi->e9_.ipTrueList=0;
		//pi->e9_.ipFalseList=0;
	}

	static void act_e10_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//��e10'����e11
		pps[pps.size()-2]->getInhAttr()->e10_.iValFlag=ps->e11.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e10_.iType=ps->e11.sType;
		pps[pps.size()-2]->getInhAttr()->e10_.iAddr=ps->e11.sAddr;
		pps[pps.size()-2]->getInhAttr()->e10_.ipTrueList=ps->e11.spTrueList;		//ʹ��ǳ����
		pps[pps.size()-2]->getInhAttr()->e10_.ipFalseList=ps->e11.spFalseList;

		//����e11��̬�ڴ�ָ��
		ps->e11.spTrueList=0;
		ps->e11.spFalseList=0;	
	}
	static void act_e10_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//e10'���ۺ����Ը���e10
		pps[pps.size()-2]->getSynAttr()->e10.sValFlag=ps->e10_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e10.sType=ps->e10_.sType;
		pps[pps.size()-2]->getSynAttr()->e10.sAddr=ps->e10_.sAddr;
		if(ps->e10_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e10.spTrueList->swap(*(ps->e10_.spTrueList));	//����ʹ��ǳ����
		if(ps->e10_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e10.spFalseList->swap(*(ps->e10_.spFalseList));
	}

	static void act_e10_1_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//ת����value
		ControlFlow2Value(context,pi,pi->e10_.iSection);

		//��������������������
		if(isInteger(pi->e10_.iType.type))
		{
			//��e10'.addr���Դ��ݸ�S1
			pps[pps.size()-3]->getInhAttr()->e10_.iAddr=pi->e10_.iAddr;

			//��op���Դ��ݸ�S1
			pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
		}
		else
		{
			//���󱨸�
			string str="<< ����������ͱ��������͡�";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e10_1_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//ת����value
		ControlFlow2Value(context,ps,pi->e10_.iSection);

		if(ps->e11.sType.is_array)
		{
			//���󱨸�
			string str="<< �Ҳ��������������顣";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
		//����Ҳ���������������
		else if(isInteger(ps->e11.sType.type))
		{
			//�̳����Դ��ݸ�S�����e10'
			pps[pps.size()-2]->getInhAttr()->e10_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e10_.iType.type=t_INT;
			pps[pps.size()-2]->getInhAttr()->e10_.iType.is_array=false;
			pps[pps.size()-2]->getInhAttr()->e10_.iAddr=context.Temp(pps[pps.size()-2]->getInhAttr()->e10_.iType,pi->e10_.iSection);

			//���ɲ���ָ�����
			context.Gen(op_lsht,pi->e10_.iAddr,ps->e11.sAddr,pps[pps.size()-2]->getInhAttr()->e10_.iAddr,pi->e10_.iSection);
		}
		else
		{
			//���󱨸�
			string str="<< �Ҳ��������ͱ��������͡�";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e10_1_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(e10')���ۺ����Ը���e10'
		pps[pps.size()-2]->getSynAttr()->e10_.sValFlag=ps->e10_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e10_.sType=ps->e10_.sType;
		pps[pps.size()-2]->getSynAttr()->e10_.sAddr=ps->e10_.sAddr;
		if(ps->e10_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e10_.spTrueList->swap(*(ps->e10_.spTrueList));	//����ʹ��ǳ����
		if(ps->e10_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e10_.spFalseList->swap(*(ps->e10_.spFalseList));
	}
	static void act_e10_2_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//ת����value
		ControlFlow2Value(context,pi,pi->e10_.iSection);

		//��������������������
		if(isInteger(pi->e10_.iType.type))
		{
			//��e10'.addr���Դ��ݸ�S1
			pps[pps.size()-3]->getInhAttr()->e10_.iAddr=pi->e10_.iAddr;

			//��op���Դ��ݸ�S1
			pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
		}
		else
		{
			//���󱨸�
			string str=">> ����������ͱ��������͡�";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e10_2_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//ת����value
		ControlFlow2Value(context,ps,pi->e10_.iSection);

		if(ps->e11.sType.is_array)
		{
			//���󱨸�
			string str=">> �Ҳ��������������顣";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
		//����Ҳ���������������
		else if(isInteger(ps->e11.sType.type))
		{
			//�̳����Դ��ݸ�S�����e10'
			pps[pps.size()-2]->getInhAttr()->e10_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e10_.iType.type=t_INT;
			pps[pps.size()-2]->getInhAttr()->e10_.iType.is_array=false;
			pps[pps.size()-2]->getInhAttr()->e10_.iAddr=context.Temp(pps[pps.size()-2]->getInhAttr()->e10_.iType,pi->e10_.iSection);

			//���ɲ���ָ�����
			context.Gen(op_rsht,pi->e10_.iAddr,ps->e11.sAddr,pps[pps.size()-2]->getInhAttr()->e10_.iAddr,pi->e10_.iSection);
		}
		else
		{
			//���󱨸�
			string str=">> �Ҳ��������ͱ��������͡�";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e10_2_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(e10')���ۺ����Ը���e10'
		pps[pps.size()-2]->getSynAttr()->e10_.sValFlag=ps->e10_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e10_.sType=ps->e10_.sType;
		pps[pps.size()-2]->getSynAttr()->e10_.sAddr=ps->e10_.sAddr;
		if(ps->e10_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e10_.spTrueList->swap(*(ps->e10_.spTrueList));	//����ʹ��ǳ����
		if(ps->e10_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e10_.spFalseList->swap(*(ps->e10_.spFalseList));
	}
	static void act_e10_3_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//A(e10')�ļ̳����Դ��ظ�e10'���ۺ�����
		pps[pps.size()-2]->getSynAttr()->e10_.sValFlag=pi->e10_.iValFlag;	
		pps[pps.size()-2]->getSynAttr()->e10_.sType=pi->e10_.iType;
		pps[pps.size()-2]->getSynAttr()->e10_.sAddr=pi->e10_.iAddr;
		Append(&(pps[pps.size()-2]->getSynAttr()->e10_.spTrueList),&(pi->e10_.ipTrueList));
		Append(&(pps[pps.size()-2]->getSynAttr()->e10_.spFalseList),&(pi->e10_.ipFalseList));

		//����ָ��
		//pi->e10_.ipTrueList=0;
		//pi->e10_.ipFalseList=0;
	}

	static void act_e11_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//��e11'����e12
		pps[pps.size()-2]->getInhAttr()->e11_.iValFlag=ps->e12.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e11_.iType=ps->e12.sType;
		pps[pps.size()-2]->getInhAttr()->e11_.iAddr=ps->e12.sAddr;
		pps[pps.size()-2]->getInhAttr()->e11_.ipTrueList=ps->e12.spTrueList;		//ʹ��ǳ����
		pps[pps.size()-2]->getInhAttr()->e11_.ipFalseList=ps->e12.spFalseList;

		//����e12��̬�ڴ�ָ��
		ps->e12.spTrueList=0;
		ps->e12.spFalseList=0;
	}
	static void act_e11_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//e11'���ۺ����Ը���e11
		pps[pps.size()-2]->getSynAttr()->e11.sValFlag=ps->e11_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e11.sType=ps->e11_.sType;
		pps[pps.size()-2]->getSynAttr()->e11.sAddr=ps->e11_.sAddr;
		if(ps->e11_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e11.spTrueList->swap(*(ps->e11_.spTrueList));	//����ʹ��ǳ����
		if(ps->e11_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e11.spFalseList->swap(*(ps->e11_.spFalseList));
	}

	static void act_e11_1_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//ת����value
		ControlFlow2Value(context,pi,pi->e11_.iSection);

		//�������������Ϳɼ���
		if(Computable(pi->e11_.iType))
		{
			//��e11'.addr���Դ��ݸ�S1
			pps[pps.size()-3]->getInhAttr()->e11_.iAddr=pi->e11_.iAddr;

			//��e11'.type���Դ��ݸ�S1
			pps[pps.size()-3]->getInhAttr()->e11_.iType=pi->e11_.iType;

			//��op���Դ��ݸ�S1
			pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
		}
		else
		{
			//���󱨸�
			string str="+ ����������ʹ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e11_1_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//ת����value
		ControlFlow2Value(context,ps,pi->e11_.iSection);

		//����Ҳ��������Ϳɼ���
		if(Computable(ps->e12.sType))
		{
			//�̳����Դ��ݸ�S�����e11'
			pps[pps.size()-2]->getInhAttr()->e11_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e11_.iType.type=Advance(pi->e11_.iType.type,ps->e12.sType.type);
			pps[pps.size()-2]->getInhAttr()->e11_.iType.is_array=false;
			pps[pps.size()-2]->getInhAttr()->e11_.iAddr=context.Temp(pps[pps.size()-2]->getInhAttr()->e11_.iType,pi->e11_.iSection);

			//���ɲ���ָ�����
			context.Gen(op_add,pi->e11_.iAddr,ps->e12.sAddr,pps[pps.size()-2]->getInhAttr()->e11_.iAddr,pi->e11_.iSection);
		}
		else
		{
			//���󱨸�
			string str="+ �Ҳ��������ʹ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e11_1_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(e11')���ۺ����Ը���e11'
		pps[pps.size()-2]->getSynAttr()->e11_.sValFlag=ps->e11_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e11_.sType=ps->e11_.sType;
		pps[pps.size()-2]->getSynAttr()->e11_.sAddr=ps->e11_.sAddr;
		if(ps->e11_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e11_.spTrueList->swap(*(ps->e11_.spTrueList));	//����ʹ��ǳ����
		if(ps->e11_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e11_.spFalseList->swap(*(ps->e11_.spFalseList));
	}
	static void act_e11_2_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//ת����value
		ControlFlow2Value(context,pi,pi->e11_.iSection);

		//�������������Ϳɼ���
		if(Computable(pi->e11_.iType))
		{
			//��e11'.addr���Դ��ݸ�S1
			pps[pps.size()-3]->getInhAttr()->e11_.iAddr=pi->e11_.iAddr;

			//��e11'.type���Դ��ݸ�S1
			pps[pps.size()-3]->getInhAttr()->e11_.iType=pi->e11_.iType;

			//��op���Դ��ݸ�S1
			pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
		}
		else
		{
			//���󱨸�
			string str="- ����������ʹ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e11_2_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//ת����value
		ControlFlow2Value(context,ps,pi->e11_.iSection);

		//����Ҳ��������Ϳɼ���
		if(Computable(ps->e12.sType))
		{
			//�̳����Դ��ݸ�S�����e11'
			pps[pps.size()-2]->getInhAttr()->e11_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e11_.iType.type=Advance(pi->e11_.iType.type,ps->e12.sType.type);
			pps[pps.size()-2]->getInhAttr()->e11_.iType.is_array=false;
			pps[pps.size()-2]->getInhAttr()->e11_.iAddr=context.Temp(pps[pps.size()-2]->getInhAttr()->e11_.iType,pi->e11_.iSection);

			//���ɲ���ָ�����
			context.Gen(op_sub,pi->e11_.iAddr,ps->e12.sAddr,pps[pps.size()-2]->getInhAttr()->e11_.iAddr,pi->e11_.iSection);
		}
		else
		{
			//���󱨸�
			string str="- �Ҳ��������ʹ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e11_2_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(e11')���ۺ����Ը���e11'
		pps[pps.size()-2]->getSynAttr()->e11_.sValFlag=ps->e11_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e11_.sType=ps->e11_.sType;
		pps[pps.size()-2]->getSynAttr()->e11_.sAddr=ps->e11_.sAddr;
		if(ps->e11_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e11_.spTrueList->swap(*(ps->e11_.spTrueList));	//����ʹ��ǳ����
		if(ps->e11_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e11_.spFalseList->swap(*(ps->e11_.spFalseList));
	}
	static void act_e11_3_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//A(e11')�ļ̳����Դ��ظ�e11'���ۺ�����
		pps[pps.size()-2]->getSynAttr()->e11_.sValFlag=pi->e11_.iValFlag;	
		pps[pps.size()-2]->getSynAttr()->e11_.sType=pi->e11_.iType;
		pps[pps.size()-2]->getSynAttr()->e11_.sAddr=pi->e11_.iAddr;
		Append(&(pps[pps.size()-2]->getSynAttr()->e11_.spTrueList),&(pi->e11_.ipTrueList));
		Append(&(pps[pps.size()-2]->getSynAttr()->e11_.spFalseList),&(pi->e11_.ipFalseList));

		//����ָ��
		//pi->e11_.ipTrueList=0;
		//pi->e11_.ipFalseList=0;
	}

	static void act_e12_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//��e12'����e13
		pps[pps.size()-2]->getInhAttr()->e12_.iValFlag=ps->e13.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e12_.iType=ps->e13.sType;
		pps[pps.size()-2]->getInhAttr()->e12_.iAddr=ps->e13.sAddr;
		pps[pps.size()-2]->getInhAttr()->e12_.ipTrueList=ps->e13.spTrueList;		//ʹ��ǳ����
		pps[pps.size()-2]->getInhAttr()->e12_.ipFalseList=ps->e13.spFalseList;

		//����e13��̬�ڴ�ָ��
		ps->e13.spTrueList=0;
		ps->e13.spFalseList=0;
	}
	static void act_e12_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//e12'���ۺ����Ը���e12
		pps[pps.size()-2]->getSynAttr()->e12.sValFlag=ps->e12_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e12.sType=ps->e12_.sType;
		pps[pps.size()-2]->getSynAttr()->e12.sAddr=ps->e12_.sAddr;
		if(ps->e12_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e12.spTrueList->swap(*(ps->e12_.spTrueList));	//����ʹ��ǳ����
		if(ps->e12_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e12.spFalseList->swap(*(ps->e12_.spFalseList));
	}

	static void act_e12_1_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//ת����value
		ControlFlow2Value(context,pi,pi->e12_.iSection);

		//�������������Ϳɼ���
		if(Computable(pi->e12_.iType))
		{
			//��e12'.addr���Դ��ݸ�S1
			pps[pps.size()-3]->getInhAttr()->e12_.iAddr=pi->e12_.iAddr;

			//��e12'.type���Դ��ݸ�S1
			pps[pps.size()-3]->getInhAttr()->e12_.iType=pi->e12_.iType;

			//��op���Դ��ݸ�S1
			pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
		}
		else
		{
			//���󱨸�
			string str="* ����������ʹ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e12_1_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//ת����value
		ControlFlow2Value(context,ps,pi->e12_.iSection);

		//����Ҳ��������Ϳɼ���
		if(Computable(ps->e13.sType))
		{
			//�̳����Դ��ݸ�S�����e12'
			pps[pps.size()-2]->getInhAttr()->e12_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e12_.iType.type=Advance(pi->e12_.iType.type,ps->e13.sType.type);
			pps[pps.size()-2]->getInhAttr()->e12_.iType.is_array=false;
			pps[pps.size()-2]->getInhAttr()->e12_.iAddr=context.Temp(pps[pps.size()-2]->getInhAttr()->e12_.iType,pi->e12_.iSection);

			//���ɲ���ָ�����
			context.Gen(op_mul,pi->e12_.iAddr,ps->e13.sAddr,pps[pps.size()-2]->getInhAttr()->e12_.iAddr,pi->e12_.iSection);
		}
		else
		{
			//���󱨸�
			string str="* �Ҳ��������ʹ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e12_1_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(e12')���ۺ����Ը���e12'
		pps[pps.size()-2]->getSynAttr()->e12_.sValFlag=ps->e12_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e12_.sType=ps->e12_.sType;
		pps[pps.size()-2]->getSynAttr()->e12_.sAddr=ps->e12_.sAddr;
		if(ps->e12_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e12_.spTrueList->swap(*(ps->e12_.spTrueList));	//����ʹ��ǳ����
		if(ps->e12_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e12_.spFalseList->swap(*(ps->e12_.spFalseList));
	}
	static void act_e12_2_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//ת����value
		ControlFlow2Value(context,pi,pi->e12_.iSection);

		//�������������Ϳɼ���
		if(Computable(pi->e12_.iType))
		{
			//��e12'.addr���Դ��ݸ�S1
			pps[pps.size()-3]->getInhAttr()->e12_.iAddr=pi->e12_.iAddr;

			//��e12'.type���Դ��ݸ�S1
			pps[pps.size()-3]->getInhAttr()->e12_.iType=pi->e12_.iType;

			//��op���Դ��ݸ�S1
			pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
		}
		else
		{
			//���󱨸�
			string str="/ ����������ʹ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e12_2_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//ת����value
		ControlFlow2Value(context,ps,pi->e12_.iSection);

		//����Ҳ��������Ϳɼ���
		if(Computable(ps->e13.sType))
		{
			//�̳����Դ��ݸ�S�����e12'
			pps[pps.size()-2]->getInhAttr()->e12_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e12_.iType.type=Advance(pi->e12_.iType.type,ps->e13.sType.type);
			pps[pps.size()-2]->getInhAttr()->e12_.iType.is_array=false;
			pps[pps.size()-2]->getInhAttr()->e12_.iAddr=context.Temp(pps[pps.size()-2]->getInhAttr()->e12_.iType,pi->e12_.iSection);

			//���ɲ���ָ�����
			context.Gen(op_div,pi->e12_.iAddr,ps->e13.sAddr,pps[pps.size()-2]->getInhAttr()->e12_.iAddr,pi->e12_.iSection);
		}
		else
		{
			//���󱨸�
			string str="/ �Ҳ��������ʹ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e12_2_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(e12')���ۺ����Ը���e12'
		pps[pps.size()-2]->getSynAttr()->e12_.sValFlag=ps->e12_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e12_.sType=ps->e12_.sType;
		pps[pps.size()-2]->getSynAttr()->e12_.sAddr=ps->e12_.sAddr;
		if(ps->e12_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e12_.spTrueList->swap(*(ps->e12_.spTrueList));	//����ʹ��ǳ����
		if(ps->e12_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e12_.spFalseList->swap(*(ps->e12_.spFalseList));
	}
	static void act_e12_3_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//ת����value
		ControlFlow2Value(context,pi,pi->e12_.iSection);

		//��������������������
		if(isInteger(pi->e12_.iType.type))
		{
			//��e12'.addr���Դ��ݸ�S1
			pps[pps.size()-3]->getInhAttr()->e12_.iAddr=pi->e12_.iAddr;

			//��e12'.type���Դ��ݸ�S1
			pps[pps.size()-3]->getInhAttr()->e12_.iType=pi->e12_.iType;

			//��op���Դ��ݸ�S1
			pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
		}
		else
		{
			//���󱨸�
			string str="% ����������ͱ��������͡�";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e12_3_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//ת����value
		ControlFlow2Value(context,ps,pi->e12_.iSection);

		//����Ҳ�����������
		if(ps->e13.sType.is_array)
		{
			//���󱨸�
			string str="% �Ҳ��������������顣";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
		//����Ҳ���������������
		else if(isInteger(ps->e13.sType.type))
		{
			//�̳����Դ��ݸ�S�����e12'
			pps[pps.size()-2]->getInhAttr()->e12_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e12_.iType.type=Advance(pi->e12_.iType.type,ps->e13.sType.type);
			pps[pps.size()-2]->getInhAttr()->e12_.iType.is_array=false;
			pps[pps.size()-2]->getInhAttr()->e12_.iAddr=context.Temp(pps[pps.size()-2]->getInhAttr()->e12_.iType,pi->e12_.iSection);

			//���ɲ���ָ�����
			context.Gen(op_mod,pi->e12_.iAddr,ps->e13.sAddr,pps[pps.size()-2]->getInhAttr()->e12_.iAddr,pi->e12_.iSection);
		}
		else
		{
			//���󱨸�
			string str="% �Ҳ��������ͱ��������͡�";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e12_3_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//S(e12')���ۺ����Ը���e12'
		pps[pps.size()-2]->getSynAttr()->e12_.sValFlag=ps->e12_.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e12_.sType=ps->e12_.sType;
		pps[pps.size()-2]->getSynAttr()->e12_.sAddr=ps->e12_.sAddr;
		if(ps->e12_.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e12_.spTrueList->swap(*(ps->e12_.spTrueList));	//����ʹ��ǳ����
		if(ps->e12_.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e12_.spFalseList->swap(*(ps->e12_.spFalseList));
	}
	static void act_e12_4_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//A(e12')�ļ̳����Դ��ظ�e12'���ۺ�����
		pps[pps.size()-2]->getSynAttr()->e12_.sValFlag=pi->e12_.iValFlag;	
		pps[pps.size()-2]->getSynAttr()->e12_.sType=pi->e12_.iType;
		pps[pps.size()-2]->getSynAttr()->e12_.sAddr=pi->e12_.iAddr;
		Append(&(pps[pps.size()-2]->getSynAttr()->e12_.spTrueList),&(pi->e12_.ipTrueList));
		Append(&(pps[pps.size()-2]->getSynAttr()->e12_.spFalseList),&(pi->e12_.ipFalseList));

		//����ָ��
		//pi->e12_.ipTrueList=0;
		//pi->e12_.ipFalseList=0;
	}

	static void act_e13_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//��op���Դ��ݸ�S
		pps[pps.size()-3]->getTempVar()->op_line.tLine=pps.back()->getTempVar()->op_line.tLine;
	}
	static void act_e13A_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//ת����value
		ControlFlow2Value(context,ps,pi->e13.iSection);

		if(ps->e13.sType.is_array)
		{
			//���󱨸�
			string str="~ ���������������顣";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
		//�������������������
		else if(isInteger(ps->e13.sType.type))
		{
			//����S�����e13����
			pps[pps.size()-2]->getSynAttr()->e13.sValFlag=true;
			pps[pps.size()-2]->getSynAttr()->e13.sType.type=t_INT;
			pps[pps.size()-2]->getSynAttr()->e13.sType.is_array=false;
			pps[pps.size()-2]->getSynAttr()->e13.sAddr=context.Temp(pps[pps.size()-2]->getSynAttr()->e13.sType,pi->e13.iSection);

			//���ɲ���ָ�����
			context.Gen(op_bit_not,pps[pps.size()-2]->getSynAttr()->e13.sAddr,ps->e13.sAddr,pi->e13.iSection);
		}
		else
		{
			//���󱨸�
			string str="~ ���������ͱ��������͡�";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e13B_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//ת����control flow
		bool yes=Value2ControlFlow(context,ps,pi->e13.iSection);

		//ת���ɹ�
		if(yes)
		{
			//����S�����e13����
			pps[pps.size()-2]->getSynAttr()->e13.sValFlag=false;
			if(ps->e13.spFalseList)
				pps[pps.size()-2]->getSynAttr()->e13.spTrueList->swap(*(ps->e13.spFalseList));	//����ʹ��ǳ����
			if(ps->e13.spTrueList)
				pps[pps.size()-2]->getSynAttr()->e13.spFalseList->swap(*(ps->e13.spTrueList));
		}
		else
		{
			//���󱨸�
			string str="! ���������ʹ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e13C_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//ת����value
		ControlFlow2Value(context,ps,pi->e13.iSection);

		//����Ҳ��������Ϳɼ���
		if(Computable(ps->e13.sType))
		{
			//����S�����e13����
			pps[pps.size()-2]->getSynAttr()->e13.sValFlag=true;
			pps[pps.size()-2]->getSynAttr()->e13.sType.type=Advance(ps->e13.sType.type);
			pps[pps.size()-2]->getSynAttr()->e13.sType.is_array=false;
			pps[pps.size()-2]->getSynAttr()->e13.sAddr=context.Temp(pps[pps.size()-2]->getSynAttr()->e13.sType,pi->e13.iSection);

			//���ɲ���ָ�����
			context.Gen(op_minus,pps[pps.size()-2]->getSynAttr()->e13.sAddr,ps->e13.sAddr,pi->e13.iSection);
		}
		else
		{
			//���󱨸�
			string str="��Ŀ- ���������ʹ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e13D_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//ת����value
		ControlFlow2Value(context,ps,pi->e13.iSection);

		//����Ҳ��������Ϳɼ���
		if(Computable(ps->e13.sType))
		{
			//����S�����e13����
			pps[pps.size()-2]->getSynAttr()->e13.sValFlag=true;
			pps[pps.size()-2]->getSynAttr()->e13.sType.type=Advance(ps->e13.sType.type);
			pps[pps.size()-2]->getSynAttr()->e13.sType.is_array=false;
			pps[pps.size()-2]->getSynAttr()->e13.sAddr=context.Temp(pps[pps.size()-2]->getSynAttr()->e13.sType,pi->e13.iSection);

			//���ɲ���ָ�����
			context.Gen(op_plus,pps[pps.size()-2]->getSynAttr()->e13.sAddr,ps->e13.sAddr,pi->e13.iSection);
		}
		else
		{
			//���󱨸�
			string str="��Ŀ+ ���������ʹ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_e13E_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{	
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����e13����
		pps[pps.size()-2]->getSynAttr()->e13.sValFlag=ps->e14.sValFlag;
		pps[pps.size()-2]->getSynAttr()->e13.sType=ps->e14.sType;
		pps[pps.size()-2]->getSynAttr()->e13.sAddr=ps->e14.sAddr;
		if(ps->e14.spTrueList)
			pps[pps.size()-2]->getSynAttr()->e13.spTrueList->swap(*(ps->e14.spTrueList));	//����ʹ��ǳ����
		if(ps->e14.spFalseList)
			pps[pps.size()-2]->getSynAttr()->e13.spFalseList->swap(*(ps->e14.spFalseList));
	}

	static void act_e14A_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//����S�����e14����
		pps[pps.size()-2]->getSynAttr()->e14.sValFlag=true;
		pps[pps.size()-2]->getSynAttr()->e14.sType.type=t_BOOL;
		pps[pps.size()-2]->getSynAttr()->e14.sType.is_array=false;
		pps[pps.size()-2]->getSynAttr()->e14.sAddr=context.getAddress(true);
	}
	static void act_e14B_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//����S�����e14����
		pps[pps.size()-2]->getSynAttr()->e14.sValFlag=true;
		pps[pps.size()-2]->getSynAttr()->e14.sType.type=t_BOOL;
		pps[pps.size()-2]->getSynAttr()->e14.sType.is_array=false;
		pps[pps.size()-2]->getSynAttr()->e14.sAddr=context.getAddress(false);
	}
	static void act_e14C_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//����S�����e14����
		pps[pps.size()-2]->getSynAttr()->e14.sValFlag=true;
		pps[pps.size()-2]->getSynAttr()->e14.sType.type=t_CHAR;
		pps[pps.size()-2]->getSynAttr()->e14.sType.is_array=false;
		pps[pps.size()-2]->getSynAttr()->e14.sAddr=context.getAddress(unsigned char(pps.back()->getTempVar()->e14_const.tValue));
	}
	static void act_e14D_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//����S�����e14����
		pps[pps.size()-2]->getSynAttr()->e14.sValFlag=true;
		pps[pps.size()-2]->getSynAttr()->e14.sType.type=t_INT;
		pps[pps.size()-2]->getSynAttr()->e14.sType.is_array=false;
		pps[pps.size()-2]->getSynAttr()->e14.sAddr=context.getAddress(pps.back()->getTempVar()->e14_const.tValue);
	}
	static void act_e14E_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//����S�����e14����
		pps[pps.size()-2]->getSynAttr()->e14.sValFlag=true;
		pps[pps.size()-2]->getSynAttr()->e14.sType.type=t_DOUBLE;
		pps[pps.size()-2]->getSynAttr()->e14.sType.is_array=false;
		pps[pps.size()-2]->getSynAttr()->e14.sAddr=context.getAddress(pps.back()->getTempVar()->e14_real.tValue);
	}
	static void act_e14FG_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����e14����
		pps[pps.size()-2]->getSynAttr()->e14.sValFlag=true;
		pps[pps.size()-2]->getSynAttr()->e14.sType=ps->loc.sType;
		pps[pps.size()-2]->getSynAttr()->e14.sAddr=ps->loc.sAddr;
	}
	static void act_e14H_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����e14����
		pps[pps.size()-3]->getSynAttr()->e14.sValFlag=ps->expr.sValFlag;
		pps[pps.size()-3]->getSynAttr()->e14.sType=ps->expr.sType;
		pps[pps.size()-3]->getSynAttr()->e14.sAddr=ps->expr.sAddr;
		if(ps->expr.spTrueList)
			pps[pps.size()-3]->getSynAttr()->e14.spTrueList->swap(*(ps->expr.spTrueList));	//����ʹ��ǳ����
		if(ps->expr.spFalseList)
			pps[pps.size()-3]->getSynAttr()->e14.spFalseList->swap(*(ps->expr.spFalseList));
	}
	static void act_e14I_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Temp_Var *pt=pps.back()->getTempVar();

		//A(id)�����Դ��ݸ�T3
		pps[pps.size()-2]->getInhAttr()->T3.iLine=pt->e14_id.tLine;
		pps[pps.size()-2]->getInhAttr()->T3.iLexime->swap(*(pt->e14_id.tLexime));
	}
	static void act_e14I_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����e14����
		pps[pps.size()-2]->getSynAttr()->e14.sValFlag=true;
		pps[pps.size()-2]->getSynAttr()->e14.sType=ps->T3.sType;
		pps[pps.size()-2]->getSynAttr()->e14.sAddr=ps->T3.sAddr;
	}

	static void act_T3A_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//��ȡid����
		const string name(*(pi->T3.iLexime));

		//�������Ϊ����/����
		if(context.isVar(name))
		{
			//��ȡ����/������Ϣ
			AllocInfo const &vi=*context.getAllocInfo(name);

			//�������Ϊ����
			if(vi.var_info.is_array)
			{
				//���󱨸�
				string str="++ ������������һ�����顣";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->T3.iLine,str));	
			}
			else
			{
				//����S�����T3����
				pps[pps.size()-2]->getSynAttr()->T3.sType=vi.var_info;
				pps[pps.size()-2]->getSynAttr()->T3.sAddr=context.Temp(vi.var_info,pi->T3.iSection);

				//��ȡid��ַ
				Address id_addr=context.getAddress(name);

				//Ϊ��׺++����ָ�����
				context.Gen(op_assign,pps[pps.size()-2]->getSynAttr()->T3.sAddr,id_addr,pi->T3.iSection);
				context.Gen(op_add,id_addr,context.getAddress(1),id_addr,pi->T3.iSection);
			}
		}
		//�������Ϊ����
		else if(context.isFun(name))
		{
			//���󱨸�
			string str="++ ������������һ��������";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T3.iLine,str));	
		}
		//δ����������
		else
		{
			//���󱨸�
			string str="δ����������"+name+"��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T3.iLine,str));
		}
	}
	static void act_T3B_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//��ȡid����
		const string name(*(pi->T3.iLexime));

		//�������Ϊ����/����
		if(context.isVar(name))
		{
			//��ȡ����/������Ϣ
			AllocInfo const &vi=*context.getAllocInfo(name);

			//�������Ϊ����
			if(vi.var_info.is_array)
			{
				//���󱨸�
				string str="-- ������������һ�����顣";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->T3.iLine,str));	
			}
			else
			{
				//����S�����T3����
				pps[pps.size()-2]->getSynAttr()->T3.sType=vi.var_info;
				pps[pps.size()-2]->getSynAttr()->T3.sAddr=context.Temp(vi.var_info,pi->T3.iSection);

				//��ȡid��ַ
				Address id_addr=context.getAddress(name);

				//Ϊ��׺--����ָ�����
				context.Gen(op_assign,pps[pps.size()-2]->getSynAttr()->T3.sAddr,id_addr,pi->T3.iSection);
				context.Gen(op_sub,id_addr,context.getAddress(1),id_addr,pi->T3.iSection);
			}
		}
		//�������Ϊ����
		else if(context.isFun(name))
		{
			//���󱨸�
			string str="-- ������������һ��������";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T3.iLine,str));	
		}
		//δ����������
		else
		{
			//���󱨸�
			string str="δ����������"+name+"��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T3.iLine,str));
		}
	}
	static void act_T3C_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//��ȡid����
		const string name(*(pi->T3.iLexime));

		//�������Ϊ����/����
		if(context.isVar(name))
		{
			//�������Ϊ����
			if(context.getAllocInfo(name)->var_info.is_array)
			{
				//���󱨸�
				string str="���ܶ�������ʹ�õ��ò�����";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->T3.iLine,str));	
			}
			else
			{
				//���󱨸�
				string str="���ܶԱ�����ʹ�õ��ò�����";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->T3.iLine,str));	
			}
		}
		//�������Ϊ����
		else if(context.isFun(name))
		{
			//no-op	
		}
		//δ����������
		else
		{
			//���󱨸�
			string str="δ����������"+name+"��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T3.iLine,str));
		}
	}
	static void act_T3C_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����T3����:
		pps[pps.size()-3]->getSynAttr()->T3.sType=ps->args.sType;
		pps[pps.size()-3]->getSynAttr()->T3.sAddr=ps->args.sAddr;
	}
	static void act_T3D_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//��ȡid����
		const string name(*(pi->T3.iLexime));

		//�������Ϊ����/����
		if(context.isVar(name))
		{
			//�������Ϊ����
			if(!context.getAllocInfo(name)->var_info.is_array)
			{
				//���󱨸�
				string str="���ܶԱ�����ʹ���±���ʲ�����";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->T3.iLine,str));	
			}
		}
		//�������Ϊ����
		else if(context.isFun(name))
		{
			//���󱨸�
			string str="���ܶԺ�����ʹ���±���ʲ�����";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T3.iLine,str));	
		}
		//δ����������
		else
		{
			//���󱨸�
			string str="δ����������"+name+"��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T3.iLine,str));
		}
	}
	static void act_T3D_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//ת����value
		ControlFlow2Value(context,ps,pi->T3.iSection);

		if(ps->expr.sType.is_array)
		{
			//���󱨸�
			string str="����"+*(pi->T3.iLexime)+"�±���ʽ���������顣";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T3.iLine,str));
		}
		//����±���ʽ����������
		else if(isInteger(ps->expr.sType.type))
		{
			//addr���Դ��ݸ�T4
			pps[pps.size()-3]->getInhAttr()->T4.iAddr=ps->expr.sAddr;
		}
		else
		{
			//���󱨸�
			string str="����"+*(pi->T3.iLexime)+"�±���ʽ���ͱ��������͡�";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T3.iLine,str));
		}
	}
	static void act_T3D_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����T3����:
		pps[pps.size()-2]->getSynAttr()->T3.sType=ps->T4.sType;
		pps[pps.size()-2]->getSynAttr()->T3.sAddr=ps->T4.sAddr;
	}
	static void act_T3E_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//��ȡid����
		const string name(*(pi->T3.iLexime));

		//�������Ϊ����/����
		if(context.isVar(name))
		{
			//����S�����T3����:�������������Ϊʵ�δ��ݸ�����
			pps[pps.size()-2]->getSynAttr()->T3.sType=context.getAllocInfo(name)->var_info;
			pps[pps.size()-2]->getSynAttr()->T3.sAddr=context.getAddress(name);
		}
		//�������Ϊ����
		else if(context.isFun(name))
		{
			//���󱨸�
			string str="����"+name+"���÷Ƿ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T3.iLine,str));	
		}
		//δ����������
		else
		{
			//���󱨸�
			string str="δ����������"+name+"��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T3.iLine,str));
		}
	}

	static void act_T4A_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		AllocInfo const* pai=context.getAllocInfo(*(pi->T4.iLexime));

		//�������������
		if(pai)
		{
			//����A�����T4����:
			pps[pps.size()-2]->getSynAttr()->T4.sType.type=pai->var_info.type;
			pps[pps.size()-2]->getSynAttr()->T4.sType.is_array=false;
			Address temp_addr=context.Temp(pps[pps.size()-2]->getSynAttr()->T4.sType,pi->T4.iSection);
			pps[pps.size()-2]->getSynAttr()->T4.sAddr=temp_addr;

			//��ȡ�����ַ
			Address array_addr=context.getAddress(*(pi->T4.iLexime));

			//Ϊ��׺++����ָ�����
			context.Gen(op_read_array,array_addr,pi->T4.iAddr,temp_addr,pi->T4.iSection);	//ȡֵ
			context.Gen(op_add,temp_addr,context.getAddress(1),temp_addr,pi->T4.iSection);	//�ۼ�
			context.Gen(op_write_array,array_addr,pi->T4.iAddr,temp_addr,pi->T4.iSection);	//д��
			context.Gen(op_sub,temp_addr,context.getAddress(1),temp_addr,pi->T4.iSection);	//��ԭ
		}
	}
	static void act_T4B_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		AllocInfo const* pai=context.getAllocInfo(*(pi->T4.iLexime));

		//�������������
		if(pai)
		{
			//����A�����T4����:
			pps[pps.size()-2]->getSynAttr()->T4.sType.type=pai->var_info.type;
			pps[pps.size()-2]->getSynAttr()->T4.sType.is_array=false;
			Address temp_addr=context.Temp(pps[pps.size()-2]->getSynAttr()->T4.sType,pi->T4.iSection);
			pps[pps.size()-2]->getSynAttr()->T4.sAddr=temp_addr;

			//��ȡ�����ַ
			Address array_addr=context.getAddress(*(pi->T4.iLexime));

			//Ϊ��׺--����ָ�����
			context.Gen(op_read_array,array_addr,pi->T4.iAddr,temp_addr,pi->T4.iSection);	//ȡֵ
			context.Gen(op_sub,temp_addr,context.getAddress(1),temp_addr,pi->T4.iSection);	//�ݼ�
			context.Gen(op_write_array,array_addr,pi->T4.iAddr,temp_addr,pi->T4.iSection);	//д��
			context.Gen(op_add,temp_addr,context.getAddress(1),temp_addr,pi->T4.iSection);	//��ԭ
		}
	}
	static void act_T4C_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		AllocInfo const* pai=context.getAllocInfo(*(pi->T4.iLexime));

		//�������������
		if(pai)
		{
			//����A�����T4����:
			pps[pps.size()-2]->getSynAttr()->T4.sType.type=pai->var_info.type;
			pps[pps.size()-2]->getSynAttr()->T4.sType.is_array=false;
			pps[pps.size()-2]->getSynAttr()->T4.sAddr=context.Temp(pps[pps.size()-2]->getSynAttr()->T4.sType,pi->T4.iSection);

			//Ϊ�����������ָ�����:�����Բ�û��lvalue��rvalue�ĸ���(��Ϊû��ָ���ȡ��ַ����),���Բ�����Ҫ��������Ԫ�ص�����,ֻ�践��ֵ�������ɡ�
			context.Gen(op_read_array,context.getAddress(*(pi->T4.iLexime)),pi->T4.iAddr,pps[pps.size()-2]->getSynAttr()->T4.sAddr,pi->T4.iSection);	//ȡֵ
		}
	}

	static void act_loc_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Temp_Var *pt=pps.back()->getTempVar();

		//id���Դ��ݸ�loc'
		pps[pps.size()-2]->getInhAttr()->loc_.iLine=pt->loc_id.tLine;
		pps[pps.size()-2]->getInhAttr()->loc_.iLexime->swap(*(pt->loc_id.tLexime));
	}
	static void act_loc_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����loc����:
		pps[pps.size()-2]->getSynAttr()->loc.sType=ps->loc_.sType;
		pps[pps.size()-2]->getSynAttr()->loc.sAddr=ps->loc_.sAddr;
	}

	static void act_loc_1_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//��ȡid����
		const string name(*(pi->loc_.iLexime));

		//�������Ϊ����/����
		if(context.isVar(name))
		{
			//�������Ϊ����
			if(!context.getAllocInfo(name)->var_info.is_array)
			{
				//���󱨸�
				string str="���ܶԱ�����ʹ���±���ʲ�����";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->loc_.iLine,str));	
			}
		}
		//�������Ϊ����
		else if(context.isFun(name))
		{
			//���󱨸�
			string str="���ܶԺ�����ʹ���±���ʲ�����";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->loc_.iLine,str));	
		}
		//δ����������
		else
		{
			//���󱨸�
			string str="δ����������"+name+"��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->loc_.iLine,str));
		}
	}
	static void act_loc_1_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//ת����value
		ControlFlow2Value(context,ps,pi->loc_.iSection);

		if(ps->expr.sType.is_array)
		{
			//���󱨸�
			string str="����"+*(pi->loc_.iLexime)+"�±���ʽ���������顣";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->loc_.iLine,str));
		}
		//����±���ʽ����������
		else if(isInteger(ps->expr.sType.type))
		{
			AllocInfo const* pai=context.getAllocInfo(*(pi->loc_.iLexime));

			//�������������
			if(pai)
			{
				//����loc'����:
				pps[pps.size()-3]->getSynAttr()->loc_.sType.type=pai->var_info.type;
				pps[pps.size()-3]->getSynAttr()->loc_.sType.is_array=false;
				Address temp_addr=context.Temp(pps[pps.size()-3]->getSynAttr()->loc_.sType,pi->loc_.iSection);
				pps[pps.size()-3]->getSynAttr()->loc_.sAddr=temp_addr;

				//��ȡ�����ַ
				Address array_addr=context.getAddress(*(pi->loc_.iLexime));

				//Ϊǰ׺++/--����ָ�����
				context.Gen(op_read_array,array_addr,ps->expr.sAddr,temp_addr,pi->loc_.iSection);	//ȡֵ
				if(pi->loc_.i_Inc)
					context.Gen(op_add,temp_addr,context.getAddress(1),temp_addr,pi->loc_.iSection);	//�ۼ�
				else
					context.Gen(op_sub,temp_addr,context.getAddress(1),temp_addr,pi->loc_.iSection);	//�ݼ�
				context.Gen(op_write_array,array_addr,ps->expr.sAddr,temp_addr,pi->loc_.iSection);	//д��
			}
		}
		else
		{
			//���󱨸�
			string str="����"+*(pi->loc_.iLexime)+"�±���ʽ���ͱ��������͡�";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->loc_.iLine,str));
		}
	}
	static void act_loc_2_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//��ȡid����
		const string name(*(pi->loc_.iLexime));

		//�������Ϊ����/����
		if(context.isVar(name))
		{
			//��ȡ����/������Ϣ
			AllocInfo const &vi=*context.getAllocInfo(name);

			//�������Ϊ����
			if(vi.var_info.is_array)
			{
				//���󱨸�
				string str;

				if(pi->loc_.i_Inc)				
					str="++ ������������һ�����顣";
				else
					str="-- ������������һ�����顣";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->loc_.iLine,str));	
			}
			else
			{				
				//��ȡid��ַ
				Address id_addr=context.getAddress(name);

				//����S�����loc_����
				pps[pps.size()-2]->getSynAttr()->loc_.sType=vi.var_info;
				pps[pps.size()-2]->getSynAttr()->loc_.sAddr=id_addr;

				//Ϊǰ׺++/--����ָ�����
				if(pi->loc_.i_Inc)
					context.Gen(op_add,id_addr,context.getAddress(1),id_addr,pi->loc_.iSection);
				else
					context.Gen(op_sub,id_addr,context.getAddress(1),id_addr,pi->loc_.iSection);
			}
		}
		//�������Ϊ����
		else if(context.isFun(name))
		{
			//���󱨸�
			string str;

			if(pi->loc_.i_Inc)				
				str="++ ������������һ��������";
			else
				str="-- ������������һ��������";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->loc_.iLine,str));	
		}
		//δ����������
		else
		{
			//���󱨸�
			string str="δ����������"+name+"��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->loc_.iLine,str));
		}
	}

	static void act_args1_A1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//��A2��arglistָ�봫�ݸ�args'
		pps[pps.size()-2]->getInhAttr()->args_.ipArgList=pps[pps.size()-3]->getTempVar()->args.ipArgList;
	}
	static void act_args1_A2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();

		//��ȡ����������������Ϣ
		const FunInfo* pfi=context.getFunInfo(*(pi->args.iLexime));

		//�������������
		if(pfi)
		{
			//���ò������ٴ���
			if(pt->args.ipArgList->size()<pfi->param_list.size())
			{
				//���󱨸�
				string str="����"+*(pi->args.iLexime)+"ȱ�ٵ��ò�����";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->args.iLine,str));
			}
			else
			{
				//˳�����ɴ��ݵ��ò�����ָ��
				for(arg_list::const_iterator citor=pt->args.ipArgList->begin();citor!=pt->args.ipArgList->end();++citor)
					context.Gen(op_param,*citor,pi->args.iSection);

				//����args����
				pps[pps.size()-2]->getSynAttr()->args.sType.type=pfi->ret_type;
				pps[pps.size()-2]->getSynAttr()->args.sType.is_array=false;

				//��ȡ�����ĺ�����Ϣ
				const FunInfo* pcf=context.getFunInfo(context.getName());

				//�������������void
				if(t_VOID==pfi->ret_type)
				{
					//args��ַ��Ϊ��Ч
					pps[pps.size()-2]->getSynAttr()->args.sAddr.section=s_INVALID;

					//���ɺ�������ָ��:	������ֵ
					context.Gen(op_call,context.getAddress(int(pfi->id)),context.getAddress(int(pfi->param_list.size())),pi->args.iSection);
				
					//����������ü���,���ֱ�ӵݹ����
					if(!pcf || pcf->id!=pfi->id)
						byte_code.getCallSet().insert(pfi->id);
				}
				else
				{
					//����args��ַ
					pps[pps.size()-2]->getSynAttr()->args.sAddr=context.Temp(pps[pps.size()-2]->getSynAttr()->args.sType,pi->args.iSection);

					//���ɺ�������ָ��:	����ֵ
					context.Gen(op_call_ass,context.getAddress(int(pfi->id)),context.getAddress(int(pfi->param_list.size())),pps[pps.size()-2]->getSynAttr()->args.sAddr,pi->args.iSection);
				
					//����������ü���,���ֱ�ӵݹ����
					if(!pcf || pcf->id!=pfi->id)
						byte_code.getCallSet().insert(pfi->id);
				}
			}
		}
	}
	static void act_args2_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//��ȡ����������������Ϣ
		const FunInfo* pfi=context.getFunInfo(*(pi->args.iLexime));

		//�������������
		if(pfi)
		{
			//���ò������ٴ���
			if(0<pfi->param_list.size())
			{
				//���󱨸�
				string str="����"+*(pi->args.iLexime)+"ȱ�ٵ��ò�����";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->args.iLine,str));
			}
			else
			{
				//����args����
				pps[pps.size()-2]->getSynAttr()->args.sType.type=pfi->ret_type;
				pps[pps.size()-2]->getSynAttr()->args.sType.is_array=false;					
				
				//��ȡ�����ĺ�����Ϣ
				const FunInfo* pcf=context.getFunInfo(context.getName());

				//�������������void
				if(t_VOID==pfi->ret_type)
				{
					//args��ַ��Ϊ��Ч
					pps[pps.size()-2]->getSynAttr()->args.sAddr.section=s_INVALID;

					//���ɺ�������ָ��:	0�ε���,������ֵ
					context.Gen(op_call,context.getAddress(int(pfi->id)),context.getAddress(int(0)),pi->args.iSection);

					//����������ü���,���ֱ�ӵݹ����
					if(!pcf || pcf->id!=pfi->id)
						byte_code.getCallSet().insert(pfi->id);
				}
				else
				{
					//����args��ַ
					pps[pps.size()-2]->getSynAttr()->args.sAddr=context.Temp(pps[pps.size()-2]->getSynAttr()->args.sType,pi->args.iSection);

					//���ɺ�������ָ��:	0�ε���,����ֵ
					context.Gen(op_call_ass,context.getAddress(int(pfi->id)),context.getAddress(int(0)),pps[pps.size()-2]->getSynAttr()->args.sAddr,pi->args.iSection);
				
					//����������ü���,���ֱ�ӵݹ����
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

		//ת����value
		ControlFlow2Value(context,ps,pi->arg.iSection);

		//��ȡ����������������Ϣ
		const FunInfo* pfi=context.getFunInfo(*(pi->arg.iLexime));

		//�������������
		if(pfi)
		{
			//�������ʵ�ι���
			if(pfi->param_list.size()<pi->arg.iCnt)
			{
				//���󱨸�
				string str="���ݸ�����"+*(pi->arg.iLexime)+"��ʵ�ι��ࡣ";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->arg.iLine,str));			
			}
			else
			{	
				//ʵ�α��ʽ��ַ����ʵ���б�
				pi->arg.ipArgList->push_back(ps->e1.sAddr);

				bool compatiable;

				//��������⺯��
				if(context.especial(*(pi->arg.iLexime)))
				{
					//ʹ������Ĳ���������
					compatiable=esCompatible(ps->e1.sType,pfi->param_list[pi->arg.iCnt-1]);
				}
				else
				{
					//ʹ����ͨ�Ĳ���������
					compatiable=Compatible(ps->e1.sType,pfi->param_list[pi->arg.iCnt-1]);
				}

				//���ʵ�����β������Ƿ����
				if(!compatiable)
				{
					//���󱨸�
					string str="���ݸ�����"+*(pi->arg.iLexime)+"�ĵ�"+toString(int(pi->arg.iCnt))+"��ʵ�α��ʽ���Ͳ����ݡ�";

					//׷�ӵ���¼
					err_record.insert(make_pair(pi->arg.iLine,str));
				}
			}
		}
	}

	static void act_T1A_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//��ȡid����
		const string name(*(pi->T1.iLexime));

		//�������Ϊ����/����
		if(context.isVar(name))
		{
			//��ȡ����/������Ϣ
			AllocInfo const &vi=*context.getAllocInfo(name);

			//�������Ϊ����
			if(vi.var_info.is_array)
			{
				//���󱨸�
				string str="++ ������������һ�����顣";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				////����S�����T1����
				//pps[pps.size()-2]->getSynAttr()->T1.sValFlag=true;
				//pps[pps.size()-2]->getSynAttr()->T1.sType=vi.var_info;
				//pps[pps.size()-2]->getSynAttr()->T1.sAddr=context.Temp(vi.var_info,pi->T1.iSection);

				//���ݸ������T5
				pps[pps.size()-2]->getInhAttr()->T5.iType=vi.var_info;
				pps[pps.size()-2]->getInhAttr()->T5.iAddr=context.Temp(vi.var_info,pi->T1.iSection);

				//��ȡid��ַ
				Address id_addr=context.getAddress(name);

				//Ϊ��׺++����ָ�����
				context.Gen(op_assign,pps[pps.size()-2]->getInhAttr()->T5.iAddr,id_addr,pi->T1.iSection);
				context.Gen(op_add,id_addr,context.getAddress(1),id_addr,pi->T1.iSection);
			}
		}
		//�������Ϊ����
		else if(context.isFun(name))
		{
			//���󱨸�
			string str="++ ������������һ��������";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//δ����������
		else
		{
			//���󱨸�
			string str="δ����������"+name+"��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1B_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//��ȡid����
		const string name(*(pi->T1.iLexime));

		//�������Ϊ����/����
		if(context.isVar(name))
		{
			//��ȡ����/������Ϣ
			AllocInfo const &vi=*context.getAllocInfo(name);

			//�������Ϊ����
			if(vi.var_info.is_array)
			{
				//���󱨸�
				string str="-- ������������һ�����顣";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				////����S�����T1����
				//pps[pps.size()-2]->getSynAttr()->T1.sValFlag=true;
				//pps[pps.size()-2]->getSynAttr()->T1.sType=vi.var_info;
				//pps[pps.size()-2]->getSynAttr()->T1.sAddr=context.Temp(vi.var_info,pi->T1.iSection);

				//���ݸ������T5
				pps[pps.size()-2]->getInhAttr()->T5.iType=vi.var_info;
				pps[pps.size()-2]->getInhAttr()->T5.iAddr=context.Temp(vi.var_info,pi->T1.iSection);

				//��ȡid��ַ
				Address id_addr=context.getAddress(name);

				//Ϊ��׺--����ָ�����
				context.Gen(op_assign,pps[pps.size()-2]->getInhAttr()->T5.iAddr,id_addr,pi->T1.iSection);
				context.Gen(op_sub,id_addr,context.getAddress(1),id_addr,pi->T1.iSection);
			}
		}
		//�������Ϊ����
		else if(context.isFun(name))
		{
			//���󱨸�
			string str="-- ������������һ��������";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//δ����������
		else
		{
			//���󱨸�
			string str="δ����������"+name+"��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1C_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//��ȡid����
		const string name(*(pi->T1.iLexime));

		//�������Ϊ����/����
		if(context.isVar(name))
		{
			//�������Ϊ����
			if(context.getAllocInfo(name)->var_info.is_array)
			{
				//���󱨸�
				string str="���ܶ�������ʹ�õ��ò�����";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//���󱨸�
				string str="���ܶԱ�����ʹ�õ��ò�����";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
		}
		//�������Ϊ����
		else if(context.isFun(name))
		{
			//no-op	
		}
		//δ����������
		else
		{
			//���󱨸�
			string str="δ����������"+name+"��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1C_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		////����T1����:
		//pps[pps.size()-3]->getSynAttr()->T1.sValFlag=true;
		//pps[pps.size()-3]->getSynAttr()->T1.sType=ps->args.sType;
		//pps[pps.size()-3]->getSynAttr()->T1.sAddr=ps->args.sAddr;

		//���ݸ������T5
		pps[pps.size()-3]->getInhAttr()->T5.iType=ps->args.sType;
		pps[pps.size()-3]->getInhAttr()->T5.iAddr=ps->args.sAddr;
	}
	static void act_T1D_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//��ȡid����
		const string name(*(pi->T1.iLexime));

		//�������Ϊ����/����
		if(context.isVar(name))
		{
			//�������Ϊ����
			if(!context.getAllocInfo(name)->var_info.is_array)
			{
				//���󱨸�
				string str="���ܶԱ�����ʹ���±���ʲ�����";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
		}
		//�������Ϊ����
		else if(context.isFun(name))
		{
			//���󱨸�
			string str="���ܶԺ�����ʹ���±���ʲ�����";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//δ����������
		else
		{
			//���󱨸�
			string str="δ����������"+name+"��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1D_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//ת����value
		ControlFlow2Value(context,ps,pi->T1.iSection);

		if(ps->expr.sType.is_array)
		{
			//���󱨸�
			string str="����"+*(pi->T1.iLexime)+"�±���ʽ���������顣";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
		//����±���ʽ����������
		else if(isInteger(ps->expr.sType.type))
		{
			//addr���Դ��ݸ�T2
			pps[pps.size()-3]->getInhAttr()->T2.iAddr=ps->expr.sAddr;
		}
		else
		{
			//���󱨸�
			string str="����"+*(pi->T1.iLexime)+"�±���ʽ���ͱ��������͡�";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1D_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����T1����:		
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

		//op���Դ��ݸ�S
		pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
	}
	static void act_T1E_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//��ȡid����
		const string name(*(pi->T1.iLexime));

		//�������Ϊ����/����
		if(context.isVar(name))
		{
			//��ȡ����/������Ϣ
			AllocInfo const &vi=*context.getAllocInfo(name);

			//�������Ϊ����
			if(vi.var_info.is_array)
			{
				//���󱨸�
				string str="���ܶ�һ�����鸳ֵ��";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//ת����value
				ControlFlow2Value(context,ps,pi->T1.iSection);

				//����ɼ���
				if(Computable(ps->e1.sType))
				{
					//��ȡid��ַ
					Address id_addr=context.getAddress(name);

					//����S�����T1����
					pps[pps.size()-2]->getSynAttr()->T1.sValFlag=true;
					pps[pps.size()-2]->getSynAttr()->T1.sType=vi.var_info;
					pps[pps.size()-2]->getSynAttr()->T1.sAddr=id_addr;

					//�����������ֵ��ָ��
					context.Gen(op_assign,id_addr,ps->e1.sAddr,pi->T1.iSection);
				}
				else
				{
					//���󱨸�
					string str="= �ұ߱��ʽ���ʹ���";

					//׷�ӵ���¼
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
			}
		}
		//�������Ϊ����
		else if(context.isFun(name))
		{
			//���󱨸�
			string str="���ܶ�һ��������ֵ��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//δ����������
		else
		{
			//���󱨸�
			string str="δ����������"+name+"��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));
		}	
	}
	static void act_T1F_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//��ȡid����
		const string name(*(pi->T1.iLexime));

		//�������Ϊ����/����
		if(context.isVar(name))
		{
			//��ȡ����/������Ϣ
			AllocInfo const &vi=*context.getAllocInfo(name);

			//�������Ϊ����
			if(vi.var_info.is_array)
			{
				//���󱨸�
				string str="���ܶ�һ�����鸳ֵ��";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//ת����value
				ControlFlow2Value(context,ps,pi->T1.iSection);

				//������Ϳɼ���
				if(Computable(ps->e1.sType))
				{
					//��ȡid��ַ
					Address id_addr=context.getAddress(name);

					//����S�����T1����
					pps[pps.size()-2]->getSynAttr()->T1.sValFlag=true;
					pps[pps.size()-2]->getSynAttr()->T1.sType=vi.var_info;
					pps[pps.size()-2]->getSynAttr()->T1.sAddr=id_addr;

					//�����������ֵ��ָ��
					context.Gen(op_mul,id_addr,ps->e1.sAddr,id_addr,pi->T1.iSection);
				}
				else
				{
					//���󱨸�
					string str="*= �ұ߱��ʽ���ʹ���";

					//׷�ӵ���¼
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
			}
		}
		//�������Ϊ����
		else if(context.isFun(name))
		{
			//���󱨸�
			string str="���ܶ�һ��������ֵ��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//δ����������
		else
		{
			//���󱨸�
			string str="δ����������"+name+"��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));
		}	
	}
	static void act_T1G_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//��ȡid����
		const string name(*(pi->T1.iLexime));

		//�������Ϊ����/����
		if(context.isVar(name))
		{
			//��ȡ����/������Ϣ
			AllocInfo const &vi=*context.getAllocInfo(name);

			//�������Ϊ����
			if(vi.var_info.is_array)
			{
				//���󱨸�
				string str="���ܶ�һ�����鸳ֵ��";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//ת����value
				ControlFlow2Value(context,ps,pi->T1.iSection);

				//������Ϳɼ���
				if(Computable(ps->e1.sType))
				{
					//��ȡid��ַ
					Address id_addr=context.getAddress(name);

					//����S�����T1����
					pps[pps.size()-2]->getSynAttr()->T1.sValFlag=true;
					pps[pps.size()-2]->getSynAttr()->T1.sType=vi.var_info;
					pps[pps.size()-2]->getSynAttr()->T1.sAddr=id_addr;

					//�����������ֵ��ָ��
					context.Gen(op_div,id_addr,ps->e1.sAddr,id_addr,pi->T1.iSection);
				}
				else
				{
					//���󱨸�
					string str="/= �ұ߱��ʽ���ʹ���";

					//׷�ӵ���¼
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
			}
		}
		//�������Ϊ����
		else if(context.isFun(name))
		{
			//���󱨸�
			string str="���ܶ�һ��������ֵ��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//δ����������
		else
		{
			//���󱨸�
			string str="δ����������"+name+"��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1H_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//��ȡid����
		const string name(*(pi->T1.iLexime));

		//�������Ϊ����/����
		if(context.isVar(name))
		{
			//��ȡ����/������Ϣ
			AllocInfo const &vi=*context.getAllocInfo(name);

			//�������Ϊ����
			if(vi.var_info.is_array)
			{
				//���󱨸�
				string str="���ܶ�һ�����鸳ֵ��";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//ת����value
				ControlFlow2Value(context,ps,pi->T1.iSection);

				//������Ϳɼ���
				if(Computable(ps->e1.sType))
				{
					//��ȡid��ַ
					Address id_addr=context.getAddress(name);

					//����S�����T1����
					pps[pps.size()-2]->getSynAttr()->T1.sValFlag=true;
					pps[pps.size()-2]->getSynAttr()->T1.sType=vi.var_info;
					pps[pps.size()-2]->getSynAttr()->T1.sAddr=id_addr;

					//�����������ֵ��ָ��
					context.Gen(op_mod,id_addr,ps->e1.sAddr,id_addr,pi->T1.iSection);
				}
				else
				{
					//���󱨸�
					string str="%= �ұ߱��ʽ���ʹ���";

					//׷�ӵ���¼
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
			}
		}
		//�������Ϊ����
		else if(context.isFun(name))
		{
			//���󱨸�
			string str="���ܶ�һ��������ֵ��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//δ����������
		else
		{
			//���󱨸�
			string str="δ����������"+name+"��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1I_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//��ȡid����
		const string name(*(pi->T1.iLexime));

		//�������Ϊ����/����
		if(context.isVar(name))
		{
			//��ȡ����/������Ϣ
			AllocInfo const &vi=*context.getAllocInfo(name);

			//�������Ϊ����
			if(vi.var_info.is_array)
			{
				//���󱨸�
				string str="���ܶ�һ�����鸳ֵ��";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//ת����value
				ControlFlow2Value(context,ps,pi->T1.iSection);

				//������Ϳɼ���
				if(Computable(ps->e1.sType))
				{
					//��ȡid��ַ
					Address id_addr=context.getAddress(name);

					//����S�����T1����
					pps[pps.size()-2]->getSynAttr()->T1.sValFlag=true;
					pps[pps.size()-2]->getSynAttr()->T1.sType=vi.var_info;
					pps[pps.size()-2]->getSynAttr()->T1.sAddr=id_addr;

					//�����������ֵ��ָ��
					context.Gen(op_add,id_addr,ps->e1.sAddr,id_addr,pi->T1.iSection);
				}
				else
				{
					//���󱨸�
					string str="+= �ұ߱��ʽ���ʹ���";

					//׷�ӵ���¼
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
			}
		}
		//�������Ϊ����
		else if(context.isFun(name))
		{
			//���󱨸�
			string str="���ܶ�һ��������ֵ��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//δ����������
		else
		{
			//���󱨸�
			string str="δ����������"+name+"��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1J_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//��ȡid����
		const string name(*(pi->T1.iLexime));

		//�������Ϊ����/����
		if(context.isVar(name))
		{
			//��ȡ����/������Ϣ
			AllocInfo const &vi=*context.getAllocInfo(name);

			//�������Ϊ����
			if(vi.var_info.is_array)
			{
				//���󱨸�
				string str="���ܶ�һ�����鸳ֵ��";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//ת����value
				ControlFlow2Value(context,ps,pi->T1.iSection);

				//������Ϳɼ���
				if(Computable(ps->e1.sType))
				{
					//��ȡid��ַ
					Address id_addr=context.getAddress(name);

					//����S�����T1����
					pps[pps.size()-2]->getSynAttr()->T1.sValFlag=true;
					pps[pps.size()-2]->getSynAttr()->T1.sType=vi.var_info;
					pps[pps.size()-2]->getSynAttr()->T1.sAddr=id_addr;

					//�����������ֵ��ָ��
					context.Gen(op_sub,id_addr,ps->e1.sAddr,id_addr,pi->T1.iSection);
				}
				else
				{
					//���󱨸�
					string str="-= �ұ߱��ʽ���ʹ���";

					//׷�ӵ���¼
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
			}
		}
		//�������Ϊ����
		else if(context.isFun(name))
		{
			//���󱨸�
			string str="���ܶ�һ��������ֵ��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//δ����������
		else
		{
			//���󱨸�
			string str="δ����������"+name+"��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1K_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//��ȡid����
		const string name(*(pi->T1.iLexime));

		//�������Ϊ����/����
		if(context.isVar(name))
		{
			//��ȡ����/������Ϣ
			AllocInfo const &vi=*context.getAllocInfo(name);

			//�������Ϊ����
			if(vi.var_info.is_array)
			{
				//���󱨸�
				string str="���ܶ�һ�����鸳ֵ��";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//��������������������
				if(isInteger(vi.var_info.type))
				{
					//ת����value
					ControlFlow2Value(context,ps,pi->T1.iSection);

					if(ps->e1.sType.is_array)
					{
						//���󱨸�
						string str="<<= �Ҳ��������������顣";

						//׷�ӵ���¼
						err_record.insert(make_pair(pt->op_line.tLine,str));
					}
					//����Ҳ���������������
					else if(isInteger(ps->e1.sType.type))
					{
						//��ȡid��ַ
						Address id_addr=context.getAddress(name);

						//����S�����T1����
						pps[pps.size()-2]->getSynAttr()->T1.sValFlag=true;
						pps[pps.size()-2]->getSynAttr()->T1.sType=vi.var_info;
						pps[pps.size()-2]->getSynAttr()->T1.sAddr=id_addr;

						//�����������ֵ��ָ��
						context.Gen(op_lsht,id_addr,ps->e1.sAddr,id_addr,pi->T1.iSection);
					}
					else
					{
						//���󱨸�
						string str="<<= �Ҳ��������ͱ��������͡�";

						//׷�ӵ���¼
						err_record.insert(make_pair(pt->op_line.tLine,str));
					}
				}
				else
				{
					//���󱨸�
					string str="<<= ����������ͱ��������͡�";

					//׷�ӵ���¼
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
			}
		}
		//�������Ϊ����
		else if(context.isFun(name))
		{
			//���󱨸�
			string str="���ܶ�һ��������ֵ��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//δ����������
		else
		{
			//���󱨸�
			string str="δ����������"+name+"��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1L_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//��ȡid����
		const string name(*(pi->T1.iLexime));

		//�������Ϊ����/����
		if(context.isVar(name))
		{
			//��ȡ����/������Ϣ
			AllocInfo const &vi=*context.getAllocInfo(name);

			//�������Ϊ����
			if(vi.var_info.is_array)
			{
				//���󱨸�
				string str="���ܶ�һ�����鸳ֵ��";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//��������������������
				if(isInteger(vi.var_info.type))
				{
					//ת����value
					ControlFlow2Value(context,ps,pi->T1.iSection);

					if(ps->e1.sType.is_array)
					{
						//���󱨸�
						string str=">>= �Ҳ��������������顣";

						//׷�ӵ���¼
						err_record.insert(make_pair(pt->op_line.tLine,str));
					}
					//����Ҳ���������������
					else if(isInteger(ps->e1.sType.type))
					{
						//��ȡid��ַ
						Address id_addr=context.getAddress(name);

						//����S�����T1����
						pps[pps.size()-2]->getSynAttr()->T1.sValFlag=true;
						pps[pps.size()-2]->getSynAttr()->T1.sType=vi.var_info;
						pps[pps.size()-2]->getSynAttr()->T1.sAddr=id_addr;

						//�����������ֵ��ָ��
						context.Gen(op_rsht,id_addr,ps->e1.sAddr,id_addr,pi->T1.iSection);
					}
					else
					{
						//���󱨸�
						string str=">>= �Ҳ��������ͱ��������͡�";

						//׷�ӵ���¼
						err_record.insert(make_pair(pt->op_line.tLine,str));
					}
				}
				else
				{
					//���󱨸�
					string str=">>= ����������ͱ��������͡�";

					//׷�ӵ���¼
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
			}
		}
		//�������Ϊ����
		else if(context.isFun(name))
		{
			//���󱨸�
			string str="���ܶ�һ��������ֵ��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//δ����������
		else
		{
			//���󱨸�
			string str="δ����������"+name+"��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1M_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//��ȡid����
		const string name(*(pi->T1.iLexime));

		//�������Ϊ����/����
		if(context.isVar(name))
		{
			//��ȡ����/������Ϣ
			AllocInfo const &vi=*context.getAllocInfo(name);

			//�������Ϊ����
			if(vi.var_info.is_array)
			{
				//���󱨸�
				string str="���ܶ�һ�����鸳ֵ��";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//��������������������
				if(isInteger(vi.var_info.type))
				{
					//ת����value
					ControlFlow2Value(context,ps,pi->T1.iSection);

					if(ps->e1.sType.is_array)
					{
						//���󱨸�
						string str="&= �Ҳ��������������顣";

						//׷�ӵ���¼
						err_record.insert(make_pair(pt->op_line.tLine,str));
					}
					//����Ҳ���������������
					else if(isInteger(ps->e1.sType.type))
					{
						//��ȡid��ַ
						Address id_addr=context.getAddress(name);

						//����S�����T1����
						pps[pps.size()-2]->getSynAttr()->T1.sValFlag=true;
						pps[pps.size()-2]->getSynAttr()->T1.sType=vi.var_info;
						pps[pps.size()-2]->getSynAttr()->T1.sAddr=id_addr;

						//�����������ֵ��ָ��
						context.Gen(op_bit_and,id_addr,ps->e1.sAddr,id_addr,pi->T1.iSection);
					}
					else
					{
						//���󱨸�
						string str="&= �Ҳ��������ͱ��������͡�";

						//׷�ӵ���¼
						err_record.insert(make_pair(pt->op_line.tLine,str));
					}
				}
				else
				{
					//���󱨸�
					string str="&= ����������ͱ��������͡�";

					//׷�ӵ���¼
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
			}
		}
		//�������Ϊ����
		else if(context.isFun(name))
		{
			//���󱨸�
			string str="���ܶ�һ��������ֵ��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//δ����������
		else
		{
			//���󱨸�
			string str="δ����������"+name+"��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1N_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//��ȡid����
		const string name(*(pi->T1.iLexime));

		//�������Ϊ����/����
		if(context.isVar(name))
		{
			//��ȡ����/������Ϣ
			AllocInfo const &vi=*context.getAllocInfo(name);

			//�������Ϊ����
			if(vi.var_info.is_array)
			{
				//���󱨸�
				string str="���ܶ�һ�����鸳ֵ��";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//��������������������
				if(isInteger(vi.var_info.type))
				{
					//ת����value
					ControlFlow2Value(context,ps,pi->T1.iSection);

					if(ps->e1.sType.is_array)
					{
						//���󱨸�
						string str="|= �Ҳ��������������顣";

						//׷�ӵ���¼
						err_record.insert(make_pair(pt->op_line.tLine,str));
					}
					//����Ҳ���������������
					else if(isInteger(ps->e1.sType.type))
					{
						//��ȡid��ַ
						Address id_addr=context.getAddress(name);

						//����S�����T1����
						pps[pps.size()-2]->getSynAttr()->T1.sValFlag=true;
						pps[pps.size()-2]->getSynAttr()->T1.sType=vi.var_info;
						pps[pps.size()-2]->getSynAttr()->T1.sAddr=id_addr;

						//�����������ֵ��ָ��
						context.Gen(op_bit_or,id_addr,ps->e1.sAddr,id_addr,pi->T1.iSection);
					}
					else
					{
						//���󱨸�
						string str="|= �Ҳ��������ͱ��������͡�";

						//׷�ӵ���¼
						err_record.insert(make_pair(pt->op_line.tLine,str));
					}
				}
				else
				{
					//���󱨸�
					string str="|= ����������ͱ��������͡�";

					//׷�ӵ���¼
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
			}
		}
		//�������Ϊ����
		else if(context.isFun(name))
		{
			//���󱨸�
			string str="���ܶ�һ��������ֵ��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//δ����������
		else
		{
			//���󱨸�
			string str="δ����������"+name+"��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1O_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//��ȡid����
		const string name(*(pi->T1.iLexime));

		//�������Ϊ����/����
		if(context.isVar(name))
		{
			//��ȡ����/������Ϣ
			AllocInfo const &vi=*context.getAllocInfo(name);

			//�������Ϊ����
			if(vi.var_info.is_array)
			{
				//���󱨸�
				string str="���ܶ�һ�����鸳ֵ��";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//��������������������
				if(isInteger(vi.var_info.type))
				{
					//ת����value
					ControlFlow2Value(context,ps,pi->T1.iSection);

					if(ps->e1.sType.is_array)
					{
						//���󱨸�
						string str="^= �Ҳ��������������顣";

						//׷�ӵ���¼
						err_record.insert(make_pair(pt->op_line.tLine,str));
					}
					//����Ҳ���������������
					else if(isInteger(ps->e1.sType.type))
					{
						//��ȡid��ַ
						Address id_addr=context.getAddress(name);

						//����S�����T1����
						pps[pps.size()-2]->getSynAttr()->T1.sValFlag=true;
						pps[pps.size()-2]->getSynAttr()->T1.sType=vi.var_info;
						pps[pps.size()-2]->getSynAttr()->T1.sAddr=id_addr;

						//�����������ֵ��ָ��
						context.Gen(op_bit_xor,id_addr,ps->e1.sAddr,id_addr,pi->T1.iSection);
					}
					else
					{
						//���󱨸�
						string str="^= �Ҳ��������ͱ��������͡�";

						//׷�ӵ���¼
						err_record.insert(make_pair(pt->op_line.tLine,str));
					}
				}
				else
				{
					//���󱨸�
					string str="^= ����������ͱ��������͡�";

					//׷�ӵ���¼
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
			}
		}
		//�������Ϊ����
		else if(context.isFun(name))
		{
			//���󱨸�
			string str="���ܶ�һ��������ֵ��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//δ����������
		else
		{
			//���󱨸�
			string str="δ����������"+name+"��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}

	static void act_T1P_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//��ȡid����
		const string name(*(pi->T1.iLexime));

		//�������Ϊ����/����
		if(context.isVar(name))
		{
			//��ȡ����/������Ϣ
			AllocInfo const &vi=*context.getAllocInfo(name);

			//�������Ϊ����
			if(vi.var_info.is_array)
			{
				//���󱨸�
				string str="����"+name+"������Ϊ����������( ? : )���㡣";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//����id����
				pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=true;
				pps[pps.size()-2]->getInhAttr()->e2_.iType=vi.var_info;
				pps[pps.size()-2]->getInhAttr()->e2_.iAddr=context.getAddress(name);
			}
		}
		//�������Ϊ����
		else if(context.isFun(name))
		{
			//���󱨸�
			string str="����"+name+"���÷Ƿ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//δ����������
		else
		{
			//���󱨸�
			string str="δ����������"+name+"��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1P_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����T1����: e2'(control flow->value)
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

		//��ȡid����
		const string name(*(pi->T1.iLexime));

		//�������Ϊ����/����
		if(context.isVar(name))
		{
			//��ȡ����/������Ϣ
			AllocInfo const &vi=*context.getAllocInfo(name);

			//�������Ϊ����
			if(vi.var_info.is_array)
			{
				//���󱨸�
				string str="����"+name+"������Ϊ���������� || ���㡣";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//����id����
				pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=true;
				pps[pps.size()-2]->getInhAttr()->e3_.iType=vi.var_info;
				pps[pps.size()-2]->getInhAttr()->e3_.iAddr=context.getAddress(name);
			}
		}
		//�������Ϊ����
		else if(context.isFun(name))
		{
			//���󱨸�
			string str="����"+name+"���÷Ƿ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//δ����������
		else
		{
			//���󱨸�
			string str="δ����������"+name+"��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1Q_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//����ָ��
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T1Q_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����T1����: e2'(control flow->value)
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

		//��ȡid����
		const string name(*(pi->T1.iLexime));

		//�������Ϊ����/����
		if(context.isVar(name))
		{
			//��ȡ����/������Ϣ
			AllocInfo const &vi=*context.getAllocInfo(name);

			//�������Ϊ����
			if(vi.var_info.is_array)
			{
				//���󱨸�
				string str="����"+name+"������Ϊ���������� && ���㡣";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//����id����
				pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=true;
				pps[pps.size()-2]->getInhAttr()->e4_.iType=vi.var_info;
				pps[pps.size()-2]->getInhAttr()->e4_.iAddr=context.getAddress(name);
			}
		}
		//�������Ϊ����
		else if(context.isFun(name))
		{
			//���󱨸�
			string str="����"+name+"���÷Ƿ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//δ����������
		else
		{
			//���󱨸�
			string str="δ����������"+name+"��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1R_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//����ָ��
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T1R_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//����ָ��
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T1R_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����T1����: e2'(control flow->value)
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

		//��ȡid����
		const string name(*(pi->T1.iLexime));

		//�������Ϊ����/����
		if(context.isVar(name))
		{
			//��ȡ����/������Ϣ
			AllocInfo const &vi=*context.getAllocInfo(name);

			//�������Ϊ����
			if(vi.var_info.is_array)
			{
				//���󱨸�
				string str="����"+name+"������Ϊ���������� | ���㡣";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//����id����
				pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=true;
				pps[pps.size()-2]->getInhAttr()->e5_.iType=vi.var_info;
				pps[pps.size()-2]->getInhAttr()->e5_.iAddr=context.getAddress(name);
			}
		}
		//�������Ϊ����
		else if(context.isFun(name))
		{
			//���󱨸�
			string str="����"+name+"���÷Ƿ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//δ����������
		else
		{
			//���󱨸�
			string str="δ����������"+name+"��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1S_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e4': e5'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//����ָ��
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T1S_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//����ָ��
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T1S_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//����ָ��
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T1S_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����T1����: e2'(control flow->value)
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

		//��ȡid����
		const string name(*(pi->T1.iLexime));

		//�������Ϊ����/����
		if(context.isVar(name))
		{
			//��ȡ����/������Ϣ
			AllocInfo const &vi=*context.getAllocInfo(name);

			//�������Ϊ����
			if(vi.var_info.is_array)
			{
				//���󱨸�
				string str="����"+name+"������Ϊ���������� ^ ���㡣";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//����id����
				pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=true;
				pps[pps.size()-2]->getInhAttr()->e6_.iType=vi.var_info;
				pps[pps.size()-2]->getInhAttr()->e6_.iAddr=context.getAddress(name);
			}
		}
		//�������Ϊ����
		else if(context.isFun(name))
		{
			//���󱨸�
			string str="����"+name+"���÷Ƿ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//δ����������
		else
		{
			//���󱨸�
			string str="δ����������"+name+"��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1T_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e5': e6'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//����ָ��
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T1T_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e4': e5'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//����ָ��
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T1T_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//����ָ��
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T1T_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//����ָ��
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T1T_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����T1����: e2'(control flow->value)
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

		//��ȡid����
		const string name(*(pi->T1.iLexime));

		//�������Ϊ����/����
		if(context.isVar(name))
		{
			//��ȡ����/������Ϣ
			AllocInfo const &vi=*context.getAllocInfo(name);

			//�������Ϊ����
			if(vi.var_info.is_array)
			{
				//���󱨸�
				string str="����"+name+"������Ϊ���������� & ���㡣";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//����id����
				pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=true;
				pps[pps.size()-2]->getInhAttr()->e7_.iType=vi.var_info;
				pps[pps.size()-2]->getInhAttr()->e7_.iAddr=context.getAddress(name);
			}
		}
		//�������Ϊ����
		else if(context.isFun(name))
		{
			//���󱨸�
			string str="����"+name+"���÷Ƿ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//δ����������
		else
		{
			//���󱨸�
			string str="δ����������"+name+"��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1U_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e6': e7'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7_.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7_.spFalseList;

		//����ָ��
		ps->e7_.spTrueList=0;
		ps->e7_.spFalseList=0;
	}
	static void act_T1U_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e5': e6'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//����ָ��
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T1U_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e4': e5'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//����ָ��
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T1U_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//����ָ��
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T1U_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//����ָ��
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T1U_S6(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����T1����: e2'(control flow->value)
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

		//��ȡid����
		const string name(*(pi->T1.iLexime));

		//�������Ϊ����/����
		if(context.isVar(name))
		{
			//��ȡ����/������Ϣ
			AllocInfo const &vi=*context.getAllocInfo(name);

			//�������Ϊ����
			if(vi.var_info.is_array)
			{
				//���󱨸�
				string str="����"+name+"������Ϊ���������� ==,!= ���㡣";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//����id����
				pps[pps.size()-2]->getInhAttr()->e8_.iValFlag=true;
				pps[pps.size()-2]->getInhAttr()->e8_.iType=vi.var_info;
				pps[pps.size()-2]->getInhAttr()->e8_.iAddr=context.getAddress(name);
			}
		}
		//�������Ϊ����
		else if(context.isFun(name))
		{
			//���󱨸�
			string str="����"+name+"���÷Ƿ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//δ����������
		else
		{
			//���󱨸�
			string str="δ����������"+name+"��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1V_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e7': e8'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=ps->e8_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e7_.iType=ps->e8_.sType;
		pps[pps.size()-2]->getInhAttr()->e7_.iAddr=ps->e8_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e7_.ipTrueList=ps->e8_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e7_.ipFalseList=ps->e8_.spFalseList;

		//����ָ��
		ps->e8_.spTrueList=0;
		ps->e8_.spFalseList=0;
	}
	static void act_T1V_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e6': e7'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7_.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7_.spFalseList;

		//����ָ��
		ps->e7_.spTrueList=0;
		ps->e7_.spFalseList=0;
	}
	static void act_T1V_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e5': e6'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//����ָ��
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T1V_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e4': e5'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//����ָ��
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T1V_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//����ָ��
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T1V_S6(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//����ָ��
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T1V_S7(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����T1����: e2'(control flow->value)
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

		//��ȡid����
		const string name(*(pi->T1.iLexime));

		//�������Ϊ����/����
		if(context.isVar(name))
		{
			//��ȡ����/������Ϣ
			AllocInfo const &vi=*context.getAllocInfo(name);

			//�������Ϊ����
			if(vi.var_info.is_array)
			{
				//���󱨸�
				string str="����"+name+"������Ϊ���������� <,<=,>,>= ���㡣";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//����id����
				pps[pps.size()-2]->getInhAttr()->e9_.iValFlag=true;
				pps[pps.size()-2]->getInhAttr()->e9_.iType=vi.var_info;
				pps[pps.size()-2]->getInhAttr()->e9_.iAddr=context.getAddress(name);
			}
		}
		//�������Ϊ����
		else if(context.isFun(name))
		{
			//���󱨸�
			string str="����"+name+"���÷Ƿ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//δ����������
		else
		{
			//���󱨸�
			string str="δ����������"+name+"��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1W_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e8': e9'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e8_.iValFlag=ps->e9_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e8_.iType=ps->e9_.sType;
		pps[pps.size()-2]->getInhAttr()->e8_.iAddr=ps->e9_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e8_.ipTrueList=ps->e9_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e8_.ipFalseList=ps->e9_.spFalseList;

		//����ָ��
		ps->e9_.spTrueList=0;
		ps->e9_.spFalseList=0;
	}
	static void act_T1W_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e7': e8'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=ps->e8_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e7_.iType=ps->e8_.sType;
		pps[pps.size()-2]->getInhAttr()->e7_.iAddr=ps->e8_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e7_.ipTrueList=ps->e8_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e7_.ipFalseList=ps->e8_.spFalseList;

		//����ָ��
		ps->e8_.spTrueList=0;
		ps->e8_.spFalseList=0;
	}
	static void act_T1W_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e6': e7'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7_.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7_.spFalseList;

		//����ָ��
		ps->e7_.spTrueList=0;
		ps->e7_.spFalseList=0;
	}
	static void act_T1W_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e5': e6'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//����ָ��
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T1W_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e4': e5'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//����ָ��
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T1W_S6(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//����ָ��
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T1W_S7(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//����ָ��
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T1W_S8(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����T1����: e2'(control flow->value)
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

		//��ȡid����
		const string name(*(pi->T1.iLexime));

		//�������Ϊ����/����
		if(context.isVar(name))
		{
			//��ȡ����/������Ϣ
			AllocInfo const &vi=*context.getAllocInfo(name);

			//�������Ϊ����
			if(vi.var_info.is_array)
			{
				//���󱨸�
				string str="����"+name+"������Ϊ���������� <<,>> ���㡣";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//����id����
				pps[pps.size()-2]->getInhAttr()->e10_.iValFlag=true;
				pps[pps.size()-2]->getInhAttr()->e10_.iType=vi.var_info;
				pps[pps.size()-2]->getInhAttr()->e10_.iAddr=context.getAddress(name);
			}
		}
		//�������Ϊ����
		else if(context.isFun(name))
		{
			//���󱨸�
			string str="����"+name+"���÷Ƿ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//δ����������
		else
		{
			//���󱨸�
			string str="δ����������"+name+"��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1X_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e9': e10'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e9_.iValFlag=ps->e10_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e9_.iType=ps->e10_.sType;
		pps[pps.size()-2]->getInhAttr()->e9_.iAddr=ps->e10_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e9_.ipTrueList=ps->e10_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e9_.ipFalseList=ps->e10_.spFalseList;

		//����ָ��
		ps->e10_.spTrueList=0;
		ps->e10_.spFalseList=0;
	}
	static void act_T1X_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e8': e9'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e8_.iValFlag=ps->e9_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e8_.iType=ps->e9_.sType;
		pps[pps.size()-2]->getInhAttr()->e8_.iAddr=ps->e9_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e8_.ipTrueList=ps->e9_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e8_.ipFalseList=ps->e9_.spFalseList;

		//����ָ��
		ps->e9_.spTrueList=0;
		ps->e9_.spFalseList=0;
	}
	static void act_T1X_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e7': e8'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=ps->e8_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e7_.iType=ps->e8_.sType;
		pps[pps.size()-2]->getInhAttr()->e7_.iAddr=ps->e8_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e7_.ipTrueList=ps->e8_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e7_.ipFalseList=ps->e8_.spFalseList;

		//����ָ��
		ps->e8_.spTrueList=0;
		ps->e8_.spFalseList=0;
	}
	static void act_T1X_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e6': e7'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7_.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7_.spFalseList;

		//����ָ��
		ps->e7_.spTrueList=0;
		ps->e7_.spFalseList=0;
	}
	static void act_T1X_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e5': e6'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//����ָ��
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T1X_S6(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e4': e5'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//����ָ��
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T1X_S7(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//����ָ��
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T1X_S8(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//����ָ��
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T1X_S9(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����T1����: e2'(control flow->value)
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

		//��ȡid����
		const string name(*(pi->T1.iLexime));

		//�������Ϊ����/����
		if(context.isVar(name))
		{
			//��ȡ����/������Ϣ
			AllocInfo const &vi=*context.getAllocInfo(name);

			//�������Ϊ����
			if(vi.var_info.is_array)
			{
				//���󱨸�
				string str="����"+name+"������Ϊ���������� +,- ���㡣";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//����id����
				pps[pps.size()-2]->getInhAttr()->e11_.iValFlag=true;
				pps[pps.size()-2]->getInhAttr()->e11_.iType=vi.var_info;
				pps[pps.size()-2]->getInhAttr()->e11_.iAddr=context.getAddress(name);
			}
		}
		//�������Ϊ����
		else if(context.isFun(name))
		{
			//���󱨸�
			string str="����"+name+"���÷Ƿ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//δ����������
		else
		{
			//���󱨸�
			string str="δ����������"+name+"��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1Y_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e10': e11'(value->value)
		pps[pps.size()-2]->getInhAttr()->e10_.iValFlag=ps->e11_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e10_.iType=ps->e11_.sType;
		pps[pps.size()-2]->getInhAttr()->e10_.iAddr=ps->e11_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e10_.ipTrueList=ps->e11_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e10_.ipFalseList=ps->e11_.spFalseList;

		//����ָ��
		ps->e11_.spTrueList=0;
		ps->e11_.spFalseList=0;
	}
	static void act_T1Y_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e9': e10'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e9_.iValFlag=ps->e10_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e9_.iType=ps->e10_.sType;
		pps[pps.size()-2]->getInhAttr()->e9_.iAddr=ps->e10_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e9_.ipTrueList=ps->e10_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e9_.ipFalseList=ps->e10_.spFalseList;

		//����ָ��
		ps->e10_.spTrueList=0;
		ps->e10_.spFalseList=0;
	}
	static void act_T1Y_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e8': e9'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e8_.iValFlag=ps->e9_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e8_.iType=ps->e9_.sType;
		pps[pps.size()-2]->getInhAttr()->e8_.iAddr=ps->e9_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e8_.ipTrueList=ps->e9_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e8_.ipFalseList=ps->e9_.spFalseList;

		//����ָ��
		ps->e9_.spTrueList=0;
		ps->e9_.spFalseList=0;
	}
	static void act_T1Y_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e7': e8'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=ps->e8_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e7_.iType=ps->e8_.sType;
		pps[pps.size()-2]->getInhAttr()->e7_.iAddr=ps->e8_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e7_.ipTrueList=ps->e8_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e7_.ipFalseList=ps->e8_.spFalseList;

		//����ָ��
		ps->e8_.spTrueList=0;
		ps->e8_.spFalseList=0;
	}
	static void act_T1Y_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e6': e7'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7_.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7_.spFalseList;

		//����ָ��
		ps->e7_.spTrueList=0;
		ps->e7_.spFalseList=0;
	}
	static void act_T1Y_S6(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e5': e6'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//����ָ��
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T1Y_S7(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e4': e5'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//����ָ��
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T1Y_S8(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//����ָ��
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T1Y_S9(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//����ָ��
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T1Y_S10(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����T1����: e2'(control flow->value)
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

		//��ȡid����
		const string name(*(pi->T1.iLexime));

		//�������Ϊ����/����
		if(context.isVar(name))
		{
			//��ȡ����/������Ϣ
			AllocInfo const &vi=*context.getAllocInfo(name);

			//�������Ϊ����
			if(vi.var_info.is_array)
			{
				//���󱨸�
				string str="����"+name+"������Ϊ���������� *,/,% ���㡣";

				//׷�ӵ���¼
				err_record.insert(make_pair(pi->T1.iLine,str));	
			}
			else
			{
				//����id����
				pps[pps.size()-2]->getInhAttr()->e12_.iValFlag=true;
				pps[pps.size()-2]->getInhAttr()->e12_.iType=vi.var_info;
				pps[pps.size()-2]->getInhAttr()->e12_.iAddr=context.getAddress(name);
			}
		}
		//�������Ϊ����
		else if(context.isFun(name))
		{
			//���󱨸�
			string str="����"+name+"���÷Ƿ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//δ����������
		else
		{
			//���󱨸�
			string str="δ����������"+name+"��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}
	static void act_T1Z_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e11': e12'(value->value)
		pps[pps.size()-2]->getInhAttr()->e11_.iValFlag=ps->e12_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e11_.iType=ps->e12_.sType;
		pps[pps.size()-2]->getInhAttr()->e11_.iAddr=ps->e12_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e11_.ipTrueList=ps->e12_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e11_.ipFalseList=ps->e12_.spFalseList;

		//����ָ��
		ps->e12_.spTrueList=0;
		ps->e12_.spFalseList=0;
	}
	static void act_T1Z_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e10': e11'(value->value)
		pps[pps.size()-2]->getInhAttr()->e10_.iValFlag=ps->e11_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e10_.iType=ps->e11_.sType;
		pps[pps.size()-2]->getInhAttr()->e10_.iAddr=ps->e11_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e10_.ipTrueList=ps->e11_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e10_.ipFalseList=ps->e11_.spFalseList;

		//����ָ��
		ps->e11_.spTrueList=0;
		ps->e11_.spFalseList=0;
	}
	static void act_T1Z_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e9': e10'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e9_.iValFlag=ps->e10_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e9_.iType=ps->e10_.sType;
		pps[pps.size()-2]->getInhAttr()->e9_.iAddr=ps->e10_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e9_.ipTrueList=ps->e10_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e9_.ipFalseList=ps->e10_.spFalseList;

		//����ָ��
		ps->e10_.spTrueList=0;
		ps->e10_.spFalseList=0;
	}
	static void act_T1Z_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e8': e9'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e8_.iValFlag=ps->e9_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e8_.iType=ps->e9_.sType;
		pps[pps.size()-2]->getInhAttr()->e8_.iAddr=ps->e9_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e8_.ipTrueList=ps->e9_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e8_.ipFalseList=ps->e9_.spFalseList;

		//����ָ��
		ps->e9_.spTrueList=0;
		ps->e9_.spFalseList=0;
	}
	static void act_T1Z_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e7': e8'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=ps->e8_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e7_.iType=ps->e8_.sType;
		pps[pps.size()-2]->getInhAttr()->e7_.iAddr=ps->e8_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e7_.ipTrueList=ps->e8_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e7_.ipFalseList=ps->e8_.spFalseList;

		//����ָ��
		ps->e8_.spTrueList=0;
		ps->e8_.spFalseList=0;
	}
	static void act_T1Z_S6(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e6': e7'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7_.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7_.spFalseList;

		//����ָ��
		ps->e7_.spTrueList=0;
		ps->e7_.spFalseList=0;
	}
	static void act_T1Z_S7(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e5': e6'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//����ָ��
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T1Z_S8(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e4': e5'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//����ָ��
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T1Z_S9(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//����ָ��
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T1Z_S10(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//����ָ��
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T1Z_S11(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����T1����: e2'(control flow->value)
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

		//��ȡid����
		const string name(*(pi->T1.iLexime));

		//�������Ϊ����/����
		if(context.isVar(name))
		{
			//����S�����T1����:�������������Ϊʵ�δ��ݸ�����
			pps[pps.size()-2]->getSynAttr()->T1.sValFlag=true;	
			pps[pps.size()-2]->getSynAttr()->T1.sType=context.getAllocInfo(name)->var_info;
			pps[pps.size()-2]->getSynAttr()->T1.sAddr=context.getAddress(name);
		}
		//�������Ϊ����
		else if(context.isFun(name))
		{
			//���󱨸�
			string str="����"+name+"���÷Ƿ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));	
		}
		//δ����������
		else
		{
			//���󱨸�
			string str="δ����������"+name+"��";

			//׷�ӵ���¼
			err_record.insert(make_pair(pi->T1.iLine,str));
		}
	}

	static void act_T2A_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		AllocInfo const* pai=context.getAllocInfo(*(pi->T2.iLexime));

		//�������������
		if(pai)
		{
			////����A�����T2����:
			//pps[pps.size()-2]->getSynAttr()->T2.sValFlag=true;
			//pps[pps.size()-2]->getSynAttr()->T2.sType.type=pai->var_info.type;
			//pps[pps.size()-2]->getSynAttr()->T2.sType.is_array=false;
			//Address temp_addr=context.Temp(pps[pps.size()-2]->getSynAttr()->T2.sType,pi->T2.iSection);
			//pps[pps.size()-2]->getSynAttr()->T2.sAddr=temp_addr;

			//���ݸ������T5
			pps[pps.size()-2]->getInhAttr()->T5.iType.type=pai->var_info.type;
			pps[pps.size()-2]->getInhAttr()->T5.iType.is_array=false;
			Address temp_addr=context.Temp(pps[pps.size()-2]->getInhAttr()->T5.iType,pi->T2.iSection);
			pps[pps.size()-2]->getInhAttr()->T5.iAddr=temp_addr;

			//��ȡ�����ַ
			Address array_addr=context.getAddress(*(pi->T2.iLexime));

			//Ϊ��׺++����ָ�����
			context.Gen(op_read_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//ȡֵ
			context.Gen(op_add,temp_addr,context.getAddress(1),temp_addr,pi->T2.iSection);	//�ۼ�
			context.Gen(op_write_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//д��
			context.Gen(op_sub,temp_addr,context.getAddress(1),temp_addr,pi->T2.iSection);	//��ԭ
		}
	}
	static void act_T2B_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		AllocInfo const* pai=context.getAllocInfo(*(pi->T2.iLexime));

		//�������������
		if(pai)
		{
			////����A�����T2����:
			//pps[pps.size()-2]->getSynAttr()->T2.sValFlag=true;
			//pps[pps.size()-2]->getSynAttr()->T2.sType.type=pai->var_info.type;
			//pps[pps.size()-2]->getSynAttr()->T2.sType.is_array=false;
			//Address temp_addr=context.Temp(pps[pps.size()-2]->getSynAttr()->T2.sType,pi->T2.iSection);
			//pps[pps.size()-2]->getSynAttr()->T2.sAddr=temp_addr;

			//���ݸ������T5
			pps[pps.size()-2]->getInhAttr()->T5.iType.type=pai->var_info.type;
			pps[pps.size()-2]->getInhAttr()->T5.iType.is_array=false;
			Address temp_addr=context.Temp(pps[pps.size()-2]->getInhAttr()->T5.iType,pi->T2.iSection);
			pps[pps.size()-2]->getInhAttr()->T5.iAddr=temp_addr;

			//��ȡ�����ַ
			Address array_addr=context.getAddress(*(pi->T2.iLexime));

			//Ϊ��׺--����ָ�����
			context.Gen(op_read_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//ȡֵ
			context.Gen(op_sub,temp_addr,context.getAddress(1),temp_addr,pi->T2.iSection);	//�ݼ�
			context.Gen(op_write_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//д��
			context.Gen(op_add,temp_addr,context.getAddress(1),temp_addr,pi->T2.iSection);	//��ԭ
		}
	}

	static void act_T2C_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Temp_Var *pt=pps.back()->getTempVar();

		//op���Դ��ݸ�S
		pps[pps.size()-3]->getTempVar()->op_line.tLine=pt->op_line.tLine;
	}
	static void act_T2C_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//��ȡid����
		const string name(*(pi->T2.iLexime));

		//ת����value
		ControlFlow2Value(context,ps,pi->T2.iSection);

		//������Ϳɼ���
		if(Computable(ps->e1.sType))
		{
			AllocInfo const* pai=context.getAllocInfo(name);

			//�������������
			if(pai)
			{
				//����S�����T2����
				pps[pps.size()-2]->getSynAttr()->T2.sValFlag=true;
				pps[pps.size()-2]->getSynAttr()->T2.sType.type=pai->var_info.type;
				pps[pps.size()-2]->getSynAttr()->T2.sType.is_array=false;
				Address temp_addr=context.Temp(pps[pps.size()-2]->getSynAttr()->T2.sType,pi->T2.iSection);
				pps[pps.size()-2]->getSynAttr()->T2.sAddr=temp_addr;

				//��ȡ�����ַ
				Address array_addr=context.getAddress(name);

				//����ָ�����
				context.Gen(op_assign,temp_addr,ps->e1.sAddr,pi->T2.iSection);	//��ֵ����ʱ����
				context.Gen(op_write_array,array_addr,pi->T2.iAddr,ps->e1.sAddr,pi->T2.iSection);	//��ֵ������Ԫ��
			}
		}
		else 
		{
			//���󱨸�
			string str="= �ұ߱��ʽ���ʹ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_T2D_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//��ȡid����
		const string name(*(pi->T2.iLexime));

		//ת����value
		ControlFlow2Value(context,ps,pi->T2.iSection);

		//������Ϳɼ���
		if(Computable(ps->e1.sType))
		{
			AllocInfo const* pai=context.getAllocInfo(name);

			//�������������
			if(pai)
			{
				//����S�����T2����
				pps[pps.size()-2]->getSynAttr()->T2.sValFlag=true;
				pps[pps.size()-2]->getSynAttr()->T2.sType.type=pai->var_info.type;
				pps[pps.size()-2]->getSynAttr()->T2.sType.is_array=false;
				Address temp_addr=context.Temp(pps[pps.size()-2]->getSynAttr()->T2.sType,pi->T2.iSection);
				pps[pps.size()-2]->getSynAttr()->T2.sAddr=temp_addr;

				//��ȡ�����ַ
				Address array_addr=context.getAddress(name);

				//����ָ�����
				context.Gen(op_read_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//ȡֵ
				context.Gen(op_mul,temp_addr,ps->e1.sAddr,temp_addr,pi->T2.iSection);			// *
				context.Gen(op_write_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//д��
			}
		}
		else
		{
			//���󱨸�
			string str="*= �ұ߱��ʽ���ʹ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_T2E_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//��ȡid����
		const string name(*(pi->T2.iLexime));

		//ת����value
		ControlFlow2Value(context,ps,pi->T2.iSection);

		//������Ϳɼ���
		if(Computable(ps->e1.sType))
		{
			AllocInfo const* pai=context.getAllocInfo(name);

			//�������������
			if(pai)
			{
				//����S�����T2����
				pps[pps.size()-2]->getSynAttr()->T2.sValFlag=true;
				pps[pps.size()-2]->getSynAttr()->T2.sType.type=pai->var_info.type;
				pps[pps.size()-2]->getSynAttr()->T2.sType.is_array=false;
				Address temp_addr=context.Temp(pps[pps.size()-2]->getSynAttr()->T2.sType,pi->T2.iSection);
				pps[pps.size()-2]->getSynAttr()->T2.sAddr=temp_addr;

				//��ȡ�����ַ
				Address array_addr=context.getAddress(name);

				//����ָ�����
				context.Gen(op_read_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//ȡֵ
				context.Gen(op_div,temp_addr,ps->e1.sAddr,temp_addr,pi->T2.iSection);			// /
				context.Gen(op_write_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//д��
			}
		}
		else
		{
			//���󱨸�
			string str="/= �ұ߱��ʽ���ʹ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_T2F_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//��ȡid����
		const string name(*(pi->T2.iLexime));

		//ת����value
		ControlFlow2Value(context,ps,pi->T2.iSection);

		//������Ϳɼ���
		if(Computable(ps->e1.sType))
		{
			AllocInfo const* pai=context.getAllocInfo(name);

			//�������������
			if(pai)
			{
				//����S�����T2����
				pps[pps.size()-2]->getSynAttr()->T2.sValFlag=true;
				pps[pps.size()-2]->getSynAttr()->T2.sType.type=pai->var_info.type;
				pps[pps.size()-2]->getSynAttr()->T2.sType.is_array=false;
				Address temp_addr=context.Temp(pps[pps.size()-2]->getSynAttr()->T2.sType,pi->T2.iSection);
				pps[pps.size()-2]->getSynAttr()->T2.sAddr=temp_addr;

				//��ȡ�����ַ
				Address array_addr=context.getAddress(name);

				//����ָ�����
				context.Gen(op_read_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//ȡֵ
				context.Gen(op_mod,temp_addr,ps->e1.sAddr,temp_addr,pi->T2.iSection);			// %
				context.Gen(op_write_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//д��
			}
		}
		else
		{
			//���󱨸�
			string str="%= �ұ߱��ʽ���ʹ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_T2G_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//��ȡid����
		const string name(*(pi->T2.iLexime));

		//ת����value
		ControlFlow2Value(context,ps,pi->T2.iSection);

		//������Ϳɼ���
		if(Computable(ps->e1.sType))
		{
			AllocInfo const* pai=context.getAllocInfo(name);

			//�������������
			if(pai)
			{
				//����S�����T2����
				pps[pps.size()-2]->getSynAttr()->T2.sValFlag=true;
				pps[pps.size()-2]->getSynAttr()->T2.sType.type=pai->var_info.type;
				pps[pps.size()-2]->getSynAttr()->T2.sType.is_array=false;
				Address temp_addr=context.Temp(pps[pps.size()-2]->getSynAttr()->T2.sType,pi->T2.iSection);
				pps[pps.size()-2]->getSynAttr()->T2.sAddr=temp_addr;

				//��ȡ�����ַ
				Address array_addr=context.getAddress(name);

				//����ָ�����
				context.Gen(op_read_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//ȡֵ
				context.Gen(op_add,temp_addr,ps->e1.sAddr,temp_addr,pi->T2.iSection);			// +
				context.Gen(op_write_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//д��
			}
		}
		else
		{
			//���󱨸�
			string str="+= �ұ߱��ʽ���ʹ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_T2H_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//��ȡid����
		const string name(*(pi->T2.iLexime));

		//ת����value
		ControlFlow2Value(context,ps,pi->T2.iSection);

		//������Ϳɼ���
		if(Computable(ps->e1.sType))
		{
			AllocInfo const* pai=context.getAllocInfo(name);

			//�������������
			if(pai)
			{
				//����S�����T2����
				pps[pps.size()-2]->getSynAttr()->T2.sValFlag=true;
				pps[pps.size()-2]->getSynAttr()->T2.sType.type=pai->var_info.type;
				pps[pps.size()-2]->getSynAttr()->T2.sType.is_array=false;
				Address temp_addr=context.Temp(pps[pps.size()-2]->getSynAttr()->T2.sType,pi->T2.iSection);
				pps[pps.size()-2]->getSynAttr()->T2.sAddr=temp_addr;

				//��ȡ�����ַ
				Address array_addr=context.getAddress(name);

				//����ָ�����
				context.Gen(op_read_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//ȡֵ
				context.Gen(op_sub,temp_addr,ps->e1.sAddr,temp_addr,pi->T2.iSection);			// -
				context.Gen(op_write_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//д��
			}
		}
		else
		{
			//���󱨸�
			string str="-= �ұ߱��ʽ���ʹ���";

			//׷�ӵ���¼
			err_record.insert(make_pair(pt->op_line.tLine,str));
		}
	}
	static void act_T2I_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//��ȡid����
		const string name(*(pi->T2.iLexime));

		//��ȡ����/������Ϣ
		AllocInfo const *pai=context.getAllocInfo(name);

		//�������������
		if(pai)
		{
			//��������������������
			if(isInteger(pai->var_info.type))
			{
				//ת����value
				ControlFlow2Value(context,ps,pi->T2.iSection);

				if(ps->e1.sType.is_array)
				{
					//���󱨸�
					string str="<<= �Ҳ��������������顣";

					//׷�ӵ���¼
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
				//����Ҳ���������������
				else if(isInteger(ps->e1.sType.type))
				{
					//����S�����T2����
					pps[pps.size()-2]->getSynAttr()->T2.sValFlag=true;
					pps[pps.size()-2]->getSynAttr()->T2.sType.type=pai->var_info.type;
					pps[pps.size()-2]->getSynAttr()->T2.sType.is_array=false;
					Address temp_addr=context.Temp(pps[pps.size()-2]->getSynAttr()->T2.sType,pi->T2.iSection);
					pps[pps.size()-2]->getSynAttr()->T2.sAddr=temp_addr;

					//��ȡ�����ַ
					Address array_addr=context.getAddress(name);

					//����ָ�����
					context.Gen(op_read_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//ȡֵ
					context.Gen(op_lsht,temp_addr,ps->e1.sAddr,temp_addr,pi->T2.iSection);			// <<
					context.Gen(op_write_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//д��
				}
				else
				{
					//���󱨸�
					string str="<<= �Ҳ��������ͱ��������͡�";

					//׷�ӵ���¼
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
			}
			else
			{
				//���󱨸�
				string str="<<= ����������ͱ��������͡�";

				//׷�ӵ���¼
				err_record.insert(make_pair(pt->op_line.tLine,str));
			}
		}
	}
	static void act_T2J_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//��ȡid����
		const string name(*(pi->T2.iLexime));

		//��ȡ����/������Ϣ
		AllocInfo const *pai=context.getAllocInfo(name);

		//�������������
		if(pai)
		{
			//��������������������
			if(isInteger(pai->var_info.type))
			{
				//ת����value
				ControlFlow2Value(context,ps,pi->T2.iSection);

				if(ps->e1.sType.is_array)
				{
					//���󱨸�
					string str=">>= �Ҳ��������������顣";

					//׷�ӵ���¼
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
				//����Ҳ���������������
				else if(isInteger(ps->e1.sType.type))
				{
					//����S�����T2����
					pps[pps.size()-2]->getSynAttr()->T2.sValFlag=true;
					pps[pps.size()-2]->getSynAttr()->T2.sType.type=pai->var_info.type;
					pps[pps.size()-2]->getSynAttr()->T2.sType.is_array=false;
					Address temp_addr=context.Temp(pps[pps.size()-2]->getSynAttr()->T2.sType,pi->T2.iSection);
					pps[pps.size()-2]->getSynAttr()->T2.sAddr=temp_addr;

					//��ȡ�����ַ
					Address array_addr=context.getAddress(name);

					//����ָ�����
					context.Gen(op_read_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//ȡֵ
					context.Gen(op_rsht,temp_addr,ps->e1.sAddr,temp_addr,pi->T2.iSection);			// >>
					context.Gen(op_write_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//д��
				}
				else
				{
					//���󱨸�
					string str=">>= �Ҳ��������ͱ��������͡�";

					//׷�ӵ���¼
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
			}
			else
			{
				//���󱨸�
				string str=">>= ����������ͱ��������͡�";

				//׷�ӵ���¼
				err_record.insert(make_pair(pt->op_line.tLine,str));
			}
		}
	}
	static void act_T2K_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//��ȡid����
		const string name(*(pi->T2.iLexime));

		//��ȡ����/������Ϣ
		AllocInfo const *pai=context.getAllocInfo(name);

		//�������������
		if(pai)
		{
			//��������������������
			if(isInteger(pai->var_info.type))
			{
				//ת����value
				ControlFlow2Value(context,ps,pi->T2.iSection);

				if(ps->e1.sType.is_array)
				{
					//���󱨸�
					string str="&= �Ҳ��������������顣";

					//׷�ӵ���¼
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
				//����Ҳ���������������
				else if(isInteger(ps->e1.sType.type))
				{
					//����S�����T2����
					pps[pps.size()-2]->getSynAttr()->T2.sValFlag=true;
					pps[pps.size()-2]->getSynAttr()->T2.sType.type=pai->var_info.type;
					pps[pps.size()-2]->getSynAttr()->T2.sType.is_array=false;
					Address temp_addr=context.Temp(pps[pps.size()-2]->getSynAttr()->T2.sType,pi->T2.iSection);
					pps[pps.size()-2]->getSynAttr()->T2.sAddr=temp_addr;

					//��ȡ�����ַ
					Address array_addr=context.getAddress(name);

					//����ָ�����
					context.Gen(op_read_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//ȡֵ
					context.Gen(op_bit_and,temp_addr,ps->e1.sAddr,temp_addr,pi->T2.iSection);		// &
					context.Gen(op_write_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//д��
				}
				else
				{
					//���󱨸�
					string str="&= �Ҳ��������ͱ��������͡�";

					//׷�ӵ���¼
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
			}
			else
			{
				//���󱨸�
				string str="&= ����������ͱ��������͡�";

				//׷�ӵ���¼
				err_record.insert(make_pair(pt->op_line.tLine,str));
			}
		}
	}
	static void act_T2L_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//��ȡid����
		const string name(*(pi->T2.iLexime));

		//��ȡ����/������Ϣ
		AllocInfo const *pai=context.getAllocInfo(name);

		//�������������
		if(pai)
		{
			//��������������������
			if(isInteger(pai->var_info.type))
			{
				//ת����value
				ControlFlow2Value(context,ps,pi->T2.iSection);

				if(ps->e1.sType.is_array)
				{
					//���󱨸�
					string str="|= �Ҳ��������������顣";

					//׷�ӵ���¼
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
				//����Ҳ���������������
				else if(isInteger(ps->e1.sType.type))
				{
					//����S�����T2����
					pps[pps.size()-2]->getSynAttr()->T2.sValFlag=true;
					pps[pps.size()-2]->getSynAttr()->T2.sType.type=pai->var_info.type;
					pps[pps.size()-2]->getSynAttr()->T2.sType.is_array=false;
					Address temp_addr=context.Temp(pps[pps.size()-2]->getSynAttr()->T2.sType,pi->T2.iSection);
					pps[pps.size()-2]->getSynAttr()->T2.sAddr=temp_addr;

					//��ȡ�����ַ
					Address array_addr=context.getAddress(name);

					//����ָ�����
					context.Gen(op_read_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//ȡֵ
					context.Gen(op_bit_or,temp_addr,ps->e1.sAddr,temp_addr,pi->T2.iSection);		// |
					context.Gen(op_write_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//д��
				}
				else
				{
					//���󱨸�
					string str="|= �Ҳ��������ͱ��������͡�";

					//׷�ӵ���¼
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
			}
			else
			{
				//���󱨸�
				string str="|= ����������ͱ��������͡�";

				//׷�ӵ���¼
				err_record.insert(make_pair(pt->op_line.tLine,str));
			}
		}
	}
	static void act_T2M_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();
		Temp_Var *pt=pps.back()->getTempVar();
		Syn_Attr *ps=pps.back()->getSynAttr();

		//��ȡid����
		const string name(*(pi->T2.iLexime));

		//��ȡ����/������Ϣ
		AllocInfo const *pai=context.getAllocInfo(name);

		//�������������
		if(pai)
		{
			//��������������������
			if(isInteger(pai->var_info.type))
			{
				//ת����value
				ControlFlow2Value(context,ps,pi->T2.iSection);

				if(ps->e1.sType.is_array)
				{
					//���󱨸�
					string str="^= �Ҳ��������������顣";

					//׷�ӵ���¼
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
				//����Ҳ���������������
				else if(isInteger(ps->e1.sType.type))
				{
					//����S�����T2����
					pps[pps.size()-2]->getSynAttr()->T2.sValFlag=true;
					pps[pps.size()-2]->getSynAttr()->T2.sType.type=pai->var_info.type;
					pps[pps.size()-2]->getSynAttr()->T2.sType.is_array=false;
					Address temp_addr=context.Temp(pps[pps.size()-2]->getSynAttr()->T2.sType,pi->T2.iSection);
					pps[pps.size()-2]->getSynAttr()->T2.sAddr=temp_addr;

					//��ȡ�����ַ
					Address array_addr=context.getAddress(name);

					//����ָ�����
					context.Gen(op_read_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//ȡֵ
					context.Gen(op_bit_xor,temp_addr,ps->e1.sAddr,temp_addr,pi->T2.iSection);		// ^
					context.Gen(op_write_array,array_addr,pi->T2.iAddr,temp_addr,pi->T2.iSection);	//д��
				}
				else
				{
					//���󱨸�
					string str="^= �Ҳ��������ͱ��������͡�";

					//׷�ӵ���¼
					err_record.insert(make_pair(pt->op_line.tLine,str));
				}
			}
			else
			{
				//���󱨸�
				string str="^= ����������ͱ��������͡�";

				//׷�ӵ���¼
				err_record.insert(make_pair(pt->op_line.tLine,str));
			}
		}
	}

	static void act_T2N_A(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Inh_Attr *pi=pps.back()->getInhAttr();

		//��ȡid����
		const string name(*(pi->T2.iLexime));

		//��ȡ����/������Ϣ
		AllocInfo const *pai=context.getAllocInfo(name);

		//�������������
		if(pai)
		{
			//����id���Բ�������ʱ����
			pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e2_.iType.type=pai->var_info.type;
			pps[pps.size()-2]->getInhAttr()->e2_.iType.is_array=false;
			Address temp_addr=context.Temp(pps[pps.size()-2]->getInhAttr()->e2_.iType,pi->T2.iSection);
			pps[pps.size()-2]->getInhAttr()->e2_.iAddr=temp_addr;

			//���ɷ�������Ԫ�ص�ָ��
			context.Gen(op_read_array,context.getAddress(name),pi->T2.iAddr,temp_addr);
		}
	}
	static void act_T2N_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����T2����: e2'(control flow->value)
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

		//��ȡid����
		const string name(*(pi->T2.iLexime));

		//��ȡ����/������Ϣ
		AllocInfo const *pai=context.getAllocInfo(name);

		//�������������
		if(pai)
		{
			//����id���Բ�������ʱ����
			pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e3_.iType.type=pai->var_info.type;
			pps[pps.size()-2]->getInhAttr()->e3_.iType.is_array=false;
			Address temp_addr=context.Temp(pps[pps.size()-2]->getInhAttr()->e3_.iType,pi->T2.iSection);
			pps[pps.size()-2]->getInhAttr()->e3_.iAddr=temp_addr;

			//���ɷ�������Ԫ�ص�ָ��
			context.Gen(op_read_array,context.getAddress(name),pi->T2.iAddr,temp_addr);
		}
	}
	static void act_T2O_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//����ָ��
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T2O_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����T2����: e2'(control flow->value)
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

		//��ȡid����
		const string name(*(pi->T2.iLexime));

		//��ȡ����/������Ϣ
		AllocInfo const *pai=context.getAllocInfo(name);

		//�������������
		if(pai)
		{
			//����id���Բ�������ʱ����
			pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e4_.iType.type=pai->var_info.type;
			pps[pps.size()-2]->getInhAttr()->e4_.iType.is_array=false;
			Address temp_addr=context.Temp(pps[pps.size()-2]->getInhAttr()->e4_.iType,pi->T2.iSection);
			pps[pps.size()-2]->getInhAttr()->e4_.iAddr=temp_addr;

			//���ɷ�������Ԫ�ص�ָ��
			context.Gen(op_read_array,context.getAddress(name),pi->T2.iAddr,temp_addr);
		}
	}
	static void act_T2P_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//����ָ��
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T2P_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//����ָ��
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T2P_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����T2����: e2'(control flow->value)
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

		//��ȡid����
		const string name(*(pi->T2.iLexime));

		//��ȡ����/������Ϣ
		AllocInfo const *pai=context.getAllocInfo(name);

		//�������������
		if(pai)
		{
			//����id���Բ�������ʱ����
			pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e5_.iType.type=pai->var_info.type;
			pps[pps.size()-2]->getInhAttr()->e5_.iType.is_array=false;
			Address temp_addr=context.Temp(pps[pps.size()-2]->getInhAttr()->e5_.iType,pi->T2.iSection);
			pps[pps.size()-2]->getInhAttr()->e5_.iAddr=temp_addr;

			//���ɷ�������Ԫ�ص�ָ��
			context.Gen(op_read_array,context.getAddress(name),pi->T2.iAddr,temp_addr);
		}
	}
	static void act_T2Q_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e4': e5'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//����ָ��
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T2Q_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//����ָ��
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T2Q_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//����ָ��
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T2Q_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����T2����: e2'(control flow->value)
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

		//��ȡid����
		const string name(*(pi->T2.iLexime));

		//��ȡ����/������Ϣ
		AllocInfo const *pai=context.getAllocInfo(name);

		//�������������
		if(pai)
		{
			//����id���Բ�������ʱ����
			pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e6_.iType.type=pai->var_info.type;
			pps[pps.size()-2]->getInhAttr()->e6_.iType.is_array=false;
			Address temp_addr=context.Temp(pps[pps.size()-2]->getInhAttr()->e6_.iType,pi->T2.iSection);
			pps[pps.size()-2]->getInhAttr()->e6_.iAddr=temp_addr;

			//���ɷ�������Ԫ�ص�ָ��
			context.Gen(op_read_array,context.getAddress(name),pi->T2.iAddr,temp_addr);
		}
	}
	static void act_T2R_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e5': e6'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//����ָ��
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T2R_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e4': e5'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//����ָ��
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T2R_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//����ָ��
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T2R_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//����ָ��
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T2R_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����T2����: e2'(control flow->value)
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

		//��ȡid����
		const string name(*(pi->T2.iLexime));

		//��ȡ����/������Ϣ
		AllocInfo const *pai=context.getAllocInfo(name);

		//�������������
		if(pai)
		{
			//����id���Բ�������ʱ����
			pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e7_.iType.type=pai->var_info.type;
			pps[pps.size()-2]->getInhAttr()->e7_.iType.is_array=false;
			Address temp_addr=context.Temp(pps[pps.size()-2]->getInhAttr()->e7_.iType,pi->T2.iSection);
			pps[pps.size()-2]->getInhAttr()->e7_.iAddr=temp_addr;

			//���ɷ�������Ԫ�ص�ָ��
			context.Gen(op_read_array,context.getAddress(name),pi->T2.iAddr,temp_addr);
		}
	}
	static void act_T2S_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e6': e7'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7_.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7_.spFalseList;

		//����ָ��
		ps->e7_.spTrueList=0;
		ps->e7_.spFalseList=0;
	}
	static void act_T2S_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e5': e6'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//����ָ��
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T2S_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e4': e5'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//����ָ��
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T2S_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//����ָ��
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T2S_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//����ָ��
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T2S_S6(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����T2����: e2'(control flow->value)
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

		//��ȡid����
		const string name(*(pi->T2.iLexime));

		//��ȡ����/������Ϣ
		AllocInfo const *pai=context.getAllocInfo(name);

		//�������������
		if(pai)
		{
			//����id���Բ�������ʱ����
			pps[pps.size()-2]->getInhAttr()->e8_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e8_.iType.type=pai->var_info.type;
			pps[pps.size()-2]->getInhAttr()->e8_.iType.is_array=false;
			Address temp_addr=context.Temp(pps[pps.size()-2]->getInhAttr()->e8_.iType,pi->T2.iSection);
			pps[pps.size()-2]->getInhAttr()->e8_.iAddr=temp_addr;

			//���ɷ�������Ԫ�ص�ָ��
			context.Gen(op_read_array,context.getAddress(name),pi->T2.iAddr,temp_addr);
		}
	}
	static void act_T2T_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e7': e8'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=ps->e8_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e7_.iType=ps->e8_.sType;
		pps[pps.size()-2]->getInhAttr()->e7_.iAddr=ps->e8_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e7_.ipTrueList=ps->e8_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e7_.ipFalseList=ps->e8_.spFalseList;

		//����ָ��
		ps->e8_.spTrueList=0;
		ps->e8_.spFalseList=0;
	}
	static void act_T2T_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e6': e7'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7_.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7_.spFalseList;

		//����ָ��
		ps->e7_.spTrueList=0;
		ps->e7_.spFalseList=0;
	}
	static void act_T2T_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e5': e6'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//����ָ��
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T2T_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e4': e5'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//����ָ��
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T2T_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//����ָ��
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T2T_S6(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//����ָ��
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T2T_S7(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����T2����: e2'(control flow->value)
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
		
		//��ȡid����
		const string name(*(pi->T2.iLexime));

		//��ȡ����/������Ϣ
		AllocInfo const *pai=context.getAllocInfo(name);

		//�������������
		if(pai)
		{
			//����id���Բ�������ʱ����
			pps[pps.size()-2]->getInhAttr()->e9_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e9_.iType.type=pai->var_info.type;
			pps[pps.size()-2]->getInhAttr()->e9_.iType.is_array=false;
			Address temp_addr=context.Temp(pps[pps.size()-2]->getInhAttr()->e9_.iType,pi->T2.iSection);
			pps[pps.size()-2]->getInhAttr()->e9_.iAddr=temp_addr;

			//���ɷ�������Ԫ�ص�ָ��
			context.Gen(op_read_array,context.getAddress(name),pi->T2.iAddr,temp_addr);
		}
	}
	static void act_T2U_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e8': e9'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e8_.iValFlag=ps->e9_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e8_.iType=ps->e9_.sType;
		pps[pps.size()-2]->getInhAttr()->e8_.iAddr=ps->e9_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e8_.ipTrueList=ps->e9_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e8_.ipFalseList=ps->e9_.spFalseList;

		//����ָ��
		ps->e9_.spTrueList=0;
		ps->e9_.spFalseList=0;
	}
	static void act_T2U_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e7': e8'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=ps->e8_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e7_.iType=ps->e8_.sType;
		pps[pps.size()-2]->getInhAttr()->e7_.iAddr=ps->e8_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e7_.ipTrueList=ps->e8_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e7_.ipFalseList=ps->e8_.spFalseList;

		//����ָ��
		ps->e8_.spTrueList=0;
		ps->e8_.spFalseList=0;
	}
	static void act_T2U_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e6': e7'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7_.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7_.spFalseList;

		//����ָ��
		ps->e7_.spTrueList=0;
		ps->e7_.spFalseList=0;
	}
	static void act_T2U_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e5': e6'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//����ָ��
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T2U_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e4': e5'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//����ָ��
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T2U_S6(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//����ָ��
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T2U_S7(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//����ָ��
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T2U_S8(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����T2����: e2'(control flow->value)
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

		//��ȡid����
		const string name(*(pi->T2.iLexime));

		//��ȡ����/������Ϣ
		AllocInfo const *pai=context.getAllocInfo(name);

		//�������������
		if(pai)
		{
			//����id���Բ�������ʱ����
			pps[pps.size()-2]->getInhAttr()->e10_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e10_.iType.type=pai->var_info.type;
			pps[pps.size()-2]->getInhAttr()->e10_.iType.is_array=false;
			Address temp_addr=context.Temp(pps[pps.size()-2]->getInhAttr()->e10_.iType,pi->T2.iSection);
			pps[pps.size()-2]->getInhAttr()->e10_.iAddr=temp_addr;

			//���ɷ�������Ԫ�ص�ָ��
			context.Gen(op_read_array,context.getAddress(name),pi->T2.iAddr,temp_addr);
		}
	}
	static void act_T2V_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e9': e10'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e9_.iValFlag=ps->e10_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e9_.iType=ps->e10_.sType;
		pps[pps.size()-2]->getInhAttr()->e9_.iAddr=ps->e10_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e9_.ipTrueList=ps->e10_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e9_.ipFalseList=ps->e10_.spFalseList;

		//����ָ��
		ps->e10_.spTrueList=0;
		ps->e10_.spFalseList=0;
	}
	static void act_T2V_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e8': e9'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e8_.iValFlag=ps->e9_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e8_.iType=ps->e9_.sType;
		pps[pps.size()-2]->getInhAttr()->e8_.iAddr=ps->e9_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e8_.ipTrueList=ps->e9_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e8_.ipFalseList=ps->e9_.spFalseList;

		//����ָ��
		ps->e9_.spTrueList=0;
		ps->e9_.spFalseList=0;
	}
	static void act_T2V_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e7': e8'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=ps->e8_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e7_.iType=ps->e8_.sType;
		pps[pps.size()-2]->getInhAttr()->e7_.iAddr=ps->e8_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e7_.ipTrueList=ps->e8_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e7_.ipFalseList=ps->e8_.spFalseList;

		//����ָ��
		ps->e8_.spTrueList=0;
		ps->e8_.spFalseList=0;
	}
	static void act_T2V_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e6': e7'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7_.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7_.spFalseList;

		//����ָ��
		ps->e7_.spTrueList=0;
		ps->e7_.spFalseList=0;
	}
	static void act_T2V_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e5': e6'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//����ָ��
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T2V_S6(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e4': e5'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//����ָ��
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T2V_S7(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//����ָ��
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T2V_S8(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//����ָ��
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T2V_S9(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����T2����: e2'(control flow->value)
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

		//��ȡid����
		const string name(*(pi->T2.iLexime));

		//��ȡ����/������Ϣ
		AllocInfo const *pai=context.getAllocInfo(name);

		//�������������
		if(pai)
		{
			//����id���Բ�������ʱ����
			pps[pps.size()-2]->getInhAttr()->e11_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e11_.iType.type=pai->var_info.type;
			pps[pps.size()-2]->getInhAttr()->e11_.iType.is_array=false;
			Address temp_addr=context.Temp(pps[pps.size()-2]->getInhAttr()->e11_.iType,pi->T2.iSection);
			pps[pps.size()-2]->getInhAttr()->e11_.iAddr=temp_addr;

			//���ɷ�������Ԫ�ص�ָ��
			context.Gen(op_read_array,context.getAddress(name),pi->T2.iAddr,temp_addr);
		}
	}
	static void act_T2W_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e10': e11'(value->value)
		pps[pps.size()-2]->getInhAttr()->e10_.iValFlag=ps->e11_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e10_.iType=ps->e11_.sType;
		pps[pps.size()-2]->getInhAttr()->e10_.iAddr=ps->e11_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e10_.ipTrueList=ps->e11_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e10_.ipFalseList=ps->e11_.spFalseList;

		//����ָ��
		ps->e11_.spTrueList=0;
		ps->e11_.spFalseList=0;
	}
	static void act_T2W_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e9': e10'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e9_.iValFlag=ps->e10_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e9_.iType=ps->e10_.sType;
		pps[pps.size()-2]->getInhAttr()->e9_.iAddr=ps->e10_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e9_.ipTrueList=ps->e10_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e9_.ipFalseList=ps->e10_.spFalseList;

		//����ָ��
		ps->e10_.spTrueList=0;
		ps->e10_.spFalseList=0;
	}
	static void act_T2W_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e8': e9'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e8_.iValFlag=ps->e9_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e8_.iType=ps->e9_.sType;
		pps[pps.size()-2]->getInhAttr()->e8_.iAddr=ps->e9_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e8_.ipTrueList=ps->e9_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e8_.ipFalseList=ps->e9_.spFalseList;

		//����ָ��
		ps->e9_.spTrueList=0;
		ps->e9_.spFalseList=0;
	}
	static void act_T2W_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e7': e8'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=ps->e8_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e7_.iType=ps->e8_.sType;
		pps[pps.size()-2]->getInhAttr()->e7_.iAddr=ps->e8_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e7_.ipTrueList=ps->e8_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e7_.ipFalseList=ps->e8_.spFalseList;

		//����ָ��
		ps->e8_.spTrueList=0;
		ps->e8_.spFalseList=0;
	}
	static void act_T2W_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e6': e7'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7_.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7_.spFalseList;

		//����ָ��
		ps->e7_.spTrueList=0;
		ps->e7_.spFalseList=0;
	}
	static void act_T2W_S6(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e5': e6'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//����ָ��
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T2W_S7(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e4': e5'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//����ָ��
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T2W_S8(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//����ָ��
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T2W_S9(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//����ָ��
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T2W_S10(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����T2����: e2'(control flow->value)
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

		//��ȡid����
		const string name(*(pi->T2.iLexime));

		//��ȡ����/������Ϣ
		AllocInfo const *pai=context.getAllocInfo(name);

		//�������������
		if(pai)
		{
			//����id���Բ�������ʱ����
			pps[pps.size()-2]->getInhAttr()->e12_.iValFlag=true;
			pps[pps.size()-2]->getInhAttr()->e12_.iType.type=pai->var_info.type;
			pps[pps.size()-2]->getInhAttr()->e12_.iType.is_array=false;
			Address temp_addr=context.Temp(pps[pps.size()-2]->getInhAttr()->e12_.iType,pi->T2.iSection);
			pps[pps.size()-2]->getInhAttr()->e12_.iAddr=temp_addr;

			//���ɷ�������Ԫ�ص�ָ��
			context.Gen(op_read_array,context.getAddress(name),pi->T2.iAddr,temp_addr);
		}
	}
	static void act_T2X_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e11': e12'(value->value)
		pps[pps.size()-2]->getInhAttr()->e11_.iValFlag=ps->e12_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e11_.iType=ps->e12_.sType;
		pps[pps.size()-2]->getInhAttr()->e11_.iAddr=ps->e12_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e11_.ipTrueList=ps->e12_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e11_.ipFalseList=ps->e12_.spFalseList;

		//����ָ��
		ps->e12_.spTrueList=0;
		ps->e12_.spFalseList=0;
	}
	static void act_T2X_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e10': e11'(value->value)
		pps[pps.size()-2]->getInhAttr()->e10_.iValFlag=ps->e11_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e10_.iType=ps->e11_.sType;
		pps[pps.size()-2]->getInhAttr()->e10_.iAddr=ps->e11_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e10_.ipTrueList=ps->e11_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e10_.ipFalseList=ps->e11_.spFalseList;

		//����ָ��
		ps->e11_.spTrueList=0;
		ps->e11_.spFalseList=0;
	}
	static void act_T2X_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e9': e10'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e9_.iValFlag=ps->e10_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e9_.iType=ps->e10_.sType;
		pps[pps.size()-2]->getInhAttr()->e9_.iAddr=ps->e10_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e9_.ipTrueList=ps->e10_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e9_.ipFalseList=ps->e10_.spFalseList;

		//����ָ��
		ps->e10_.spTrueList=0;
		ps->e10_.spFalseList=0;
	}
	static void act_T2X_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e8': e9'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e8_.iValFlag=ps->e9_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e8_.iType=ps->e9_.sType;
		pps[pps.size()-2]->getInhAttr()->e8_.iAddr=ps->e9_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e8_.ipTrueList=ps->e9_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e8_.ipFalseList=ps->e9_.spFalseList;

		//����ָ��
		ps->e9_.spTrueList=0;
		ps->e9_.spFalseList=0;
	}
	static void act_T2X_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e7': e8'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=ps->e8_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e7_.iType=ps->e8_.sType;
		pps[pps.size()-2]->getInhAttr()->e7_.iAddr=ps->e8_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e7_.ipTrueList=ps->e8_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e7_.ipFalseList=ps->e8_.spFalseList;

		//����ָ��
		ps->e8_.spTrueList=0;
		ps->e8_.spFalseList=0;
	}
	static void act_T2X_S6(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e6': e7'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7_.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7_.spFalseList;

		//����ָ��
		ps->e7_.spTrueList=0;
		ps->e7_.spFalseList=0;
	}
	static void act_T2X_S7(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e5': e6'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//����ָ��
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T2X_S8(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e4': e5'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//����ָ��
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T2X_S9(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//����ָ��
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T2X_S10(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//����ָ��
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T2X_S11(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����T2����: e2'(control flow->value)
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

		//��ȡ����/������Ϣ
		AllocInfo const *pai=context.getAllocInfo(*(pi->T2.iLexime));

		//�������������
		if(pai)
		{
			//����A�����T2����:
			pps[pps.size()-2]->getSynAttr()->T2.sValFlag=true;
			pps[pps.size()-2]->getSynAttr()->T2.sType.type=pai->var_info.type;
			pps[pps.size()-2]->getSynAttr()->T2.sType.is_array=false;
			pps[pps.size()-2]->getSynAttr()->T2.sAddr=context.Temp(pps[pps.size()-2]->getSynAttr()->T2.sType,pi->T2.iSection);

			//Ϊ�����������ָ�����:�����Բ�û��lvalue��rvalue�ĸ���(��Ϊû��ָ���ȡ��ַ����),���Բ�����Ҫ��������Ԫ�ص�����,ֻ�践��ֵ�������ɡ�
			context.Gen(op_read_array,context.getAddress(*(pi->T2.iLexime)),pi->T2.iAddr,pps[pps.size()-2]->getSynAttr()->T2.sAddr,pi->T2.iSection);	//ȡֵ
		}
	}

	static void act_T5_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����T1/T2����: T5
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
	
		//����T5����
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=true;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=pi->T5.iType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=pi->T5.iAddr;
	}
	static void act_T5A_S(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����T5����: e2'(control flow->value)
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

		//����T5����
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=true;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=pi->T5.iType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=pi->T5.iAddr;
	}
	static void act_T5B_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//����ָ��
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T5B_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����T5����: e2'(control flow->value)
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

		//����T5����
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=true;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=pi->T5.iType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=pi->T5.iAddr;
	}
	static void act_T5C_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//����ָ��
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T5C_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//����ָ��
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T5C_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����T5����: e2'(control flow->value)
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

		//����T5����
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=true;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=pi->T5.iType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=pi->T5.iAddr;
	}
	static void act_T5D_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e4': e5'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//����ָ��
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T5D_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//����ָ��
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T5D_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//����ָ��
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T5D_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����T5����: e2'(control flow->value)
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

		//����T5����
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=true;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=pi->T5.iType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=pi->T5.iAddr;
	}
	static void act_T5E_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e5': e6'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//����ָ��
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T5E_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e4': e5'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//����ָ��
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T5E_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//����ָ��
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T5E_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//����ָ��
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T5E_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����T5����: e2'(control flow->value)
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

		//����T5����
		pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=true;
		pps[pps.size()-2]->getInhAttr()->e7_.iType=pi->T5.iType;
		pps[pps.size()-2]->getInhAttr()->e7_.iAddr=pi->T5.iAddr;
	}
	static void act_T5F_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e6': e7'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7_.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7_.spFalseList;

		//����ָ��
		ps->e7_.spTrueList=0;
		ps->e7_.spFalseList=0;
	}
	static void act_T5F_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e5': e6'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//����ָ��
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T5F_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e4': e5'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//����ָ��
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T5F_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//����ָ��
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T5F_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//����ָ��
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T5F_S6(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����T5����: e2'(control flow->value)
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

		//����T5����
		pps[pps.size()-2]->getInhAttr()->e8_.iValFlag=true;
		pps[pps.size()-2]->getInhAttr()->e8_.iType=pi->T5.iType;
		pps[pps.size()-2]->getInhAttr()->e8_.iAddr=pi->T5.iAddr;
	}
	static void act_T5G_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e7': e8'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=ps->e8_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e7_.iType=ps->e8_.sType;
		pps[pps.size()-2]->getInhAttr()->e7_.iAddr=ps->e8_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e7_.ipTrueList=ps->e8_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e7_.ipFalseList=ps->e8_.spFalseList;

		//����ָ��
		ps->e8_.spTrueList=0;
		ps->e8_.spFalseList=0;
	}
	static void act_T5G_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e6': e7'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7_.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7_.spFalseList;

		//����ָ��
		ps->e7_.spTrueList=0;
		ps->e7_.spFalseList=0;
	}
	static void act_T5G_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e5': e6'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//����ָ��
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T5G_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e4': e5'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//����ָ��
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T5G_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//����ָ��
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T5G_S6(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//����ָ��
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T5G_S7(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����T5����: e2'(control flow->value)
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

		//����T5����
		pps[pps.size()-2]->getInhAttr()->e9_.iValFlag=true;
		pps[pps.size()-2]->getInhAttr()->e9_.iType=pi->T5.iType;
		pps[pps.size()-2]->getInhAttr()->e9_.iAddr=pi->T5.iAddr;
	}
	static void act_T5H_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e8': e9'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e8_.iValFlag=ps->e9_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e8_.iType=ps->e9_.sType;
		pps[pps.size()-2]->getInhAttr()->e8_.iAddr=ps->e9_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e8_.ipTrueList=ps->e9_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e8_.ipFalseList=ps->e9_.spFalseList;

		//����ָ��
		ps->e9_.spTrueList=0;
		ps->e9_.spFalseList=0;
	}
	static void act_T5H_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e7': e8'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=ps->e8_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e7_.iType=ps->e8_.sType;
		pps[pps.size()-2]->getInhAttr()->e7_.iAddr=ps->e8_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e7_.ipTrueList=ps->e8_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e7_.ipFalseList=ps->e8_.spFalseList;

		//����ָ��
		ps->e8_.spTrueList=0;
		ps->e8_.spFalseList=0;
	}
	static void act_T5H_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e6': e7'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7_.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7_.spFalseList;

		//����ָ��
		ps->e7_.spTrueList=0;
		ps->e7_.spFalseList=0;
	}
	static void act_T5H_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e5': e6'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//����ָ��
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T5H_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e4': e5'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//����ָ��
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T5H_S6(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//����ָ��
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T5H_S7(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//����ָ��
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T5H_S8(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����T5����: e2'(control flow->value)
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

		//����T5����
		pps[pps.size()-2]->getInhAttr()->e10_.iValFlag=true;
		pps[pps.size()-2]->getInhAttr()->e10_.iType=pi->T5.iType;
		pps[pps.size()-2]->getInhAttr()->e10_.iAddr=pi->T5.iAddr;
	}
	static void act_T5I_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e9': e10'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e9_.iValFlag=ps->e10_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e9_.iType=ps->e10_.sType;
		pps[pps.size()-2]->getInhAttr()->e9_.iAddr=ps->e10_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e9_.ipTrueList=ps->e10_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e9_.ipFalseList=ps->e10_.spFalseList;

		//����ָ��
		ps->e10_.spTrueList=0;
		ps->e10_.spFalseList=0;
	}
	static void act_T5I_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e8': e9'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e8_.iValFlag=ps->e9_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e8_.iType=ps->e9_.sType;
		pps[pps.size()-2]->getInhAttr()->e8_.iAddr=ps->e9_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e8_.ipTrueList=ps->e9_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e8_.ipFalseList=ps->e9_.spFalseList;

		//����ָ��
		ps->e9_.spTrueList=0;
		ps->e9_.spFalseList=0;
	}
	static void act_T5I_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e7': e8'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=ps->e8_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e7_.iType=ps->e8_.sType;
		pps[pps.size()-2]->getInhAttr()->e7_.iAddr=ps->e8_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e7_.ipTrueList=ps->e8_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e7_.ipFalseList=ps->e8_.spFalseList;

		//����ָ��
		ps->e8_.spTrueList=0;
		ps->e8_.spFalseList=0;
	}
	static void act_T5I_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e6': e7'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7_.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7_.spFalseList;

		//����ָ��
		ps->e7_.spTrueList=0;
		ps->e7_.spFalseList=0;
	}
	static void act_T5I_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e5': e6'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//����ָ��
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T5I_S6(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e4': e5'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//����ָ��
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T5I_S7(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//����ָ��
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T5I_S8(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//����ָ��
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T5I_S9(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����T5����: e2'(control flow->value)
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

		//����T5����
		pps[pps.size()-2]->getInhAttr()->e11_.iValFlag=true;
		pps[pps.size()-2]->getInhAttr()->e11_.iType=pi->T5.iType;
		pps[pps.size()-2]->getInhAttr()->e11_.iAddr=pi->T5.iAddr;
	}
	static void act_T5J_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e10': e11'(value->value)
		pps[pps.size()-2]->getInhAttr()->e10_.iValFlag=ps->e11_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e10_.iType=ps->e11_.sType;
		pps[pps.size()-2]->getInhAttr()->e10_.iAddr=ps->e11_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e10_.ipTrueList=ps->e11_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e10_.ipFalseList=ps->e11_.spFalseList;

		//����ָ��
		ps->e11_.spTrueList=0;
		ps->e11_.spFalseList=0;
	}
	static void act_T5J_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e9': e10'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e9_.iValFlag=ps->e10_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e9_.iType=ps->e10_.sType;
		pps[pps.size()-2]->getInhAttr()->e9_.iAddr=ps->e10_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e9_.ipTrueList=ps->e10_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e9_.ipFalseList=ps->e10_.spFalseList;

		//����ָ��
		ps->e10_.spTrueList=0;
		ps->e10_.spFalseList=0;
	}
	static void act_T5J_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e8': e9'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e8_.iValFlag=ps->e9_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e8_.iType=ps->e9_.sType;
		pps[pps.size()-2]->getInhAttr()->e8_.iAddr=ps->e9_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e8_.ipTrueList=ps->e9_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e8_.ipFalseList=ps->e9_.spFalseList;

		//����ָ��
		ps->e9_.spTrueList=0;
		ps->e9_.spFalseList=0;
	}
	static void act_T5J_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e7': e8'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=ps->e8_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e7_.iType=ps->e8_.sType;
		pps[pps.size()-2]->getInhAttr()->e7_.iAddr=ps->e8_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e7_.ipTrueList=ps->e8_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e7_.ipFalseList=ps->e8_.spFalseList;

		//����ָ��
		ps->e8_.spTrueList=0;
		ps->e8_.spFalseList=0;
	}
	static void act_T5J_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e6': e7'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7_.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7_.spFalseList;

		//����ָ��
		ps->e7_.spTrueList=0;
		ps->e7_.spFalseList=0;
	}
	static void act_T5J_S6(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e5': e6'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//����ָ��
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T5J_S7(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e4': e5'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//����ָ��
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T5J_S8(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//����ָ��
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T5J_S9(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//����ָ��
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T5J_S10(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����T5����: e2'(control flow->value)
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

		//����T5����
		pps[pps.size()-2]->getInhAttr()->e12_.iValFlag=true;
		pps[pps.size()-2]->getInhAttr()->e12_.iType=pi->T5.iType;
		pps[pps.size()-2]->getInhAttr()->e12_.iAddr=pi->T5.iAddr;
	}
	static void act_T5K_S1(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e11': e12'(value->value)
		pps[pps.size()-2]->getInhAttr()->e11_.iValFlag=ps->e12_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e11_.iType=ps->e12_.sType;
		pps[pps.size()-2]->getInhAttr()->e11_.iAddr=ps->e12_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e11_.ipTrueList=ps->e12_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e11_.ipFalseList=ps->e12_.spFalseList;

		//����ָ��
		ps->e12_.spTrueList=0;
		ps->e12_.spFalseList=0;
	}
	static void act_T5K_S2(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e10': e11'(value->value)
		pps[pps.size()-2]->getInhAttr()->e10_.iValFlag=ps->e11_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e10_.iType=ps->e11_.sType;
		pps[pps.size()-2]->getInhAttr()->e10_.iAddr=ps->e11_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e10_.ipTrueList=ps->e11_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e10_.ipFalseList=ps->e11_.spFalseList;

		//����ָ��
		ps->e11_.spTrueList=0;
		ps->e11_.spFalseList=0;
	}
	static void act_T5K_S3(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e9': e10'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e9_.iValFlag=ps->e10_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e9_.iType=ps->e10_.sType;
		pps[pps.size()-2]->getInhAttr()->e9_.iAddr=ps->e10_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e9_.ipTrueList=ps->e10_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e9_.ipFalseList=ps->e10_.spFalseList;

		//����ָ��
		ps->e10_.spTrueList=0;
		ps->e10_.spFalseList=0;
	}
	static void act_T5K_S4(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e8': e9'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e8_.iValFlag=ps->e9_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e8_.iType=ps->e9_.sType;
		pps[pps.size()-2]->getInhAttr()->e8_.iAddr=ps->e9_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e8_.ipTrueList=ps->e9_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e8_.ipFalseList=ps->e9_.spFalseList;

		//����ָ��
		ps->e9_.spTrueList=0;
		ps->e9_.spFalseList=0;
	}
	static void act_T5K_S5(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e7': e8'(value->value(bool))
		pps[pps.size()-2]->getInhAttr()->e7_.iValFlag=ps->e8_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e7_.iType=ps->e8_.sType;
		pps[pps.size()-2]->getInhAttr()->e7_.iAddr=ps->e8_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e7_.ipTrueList=ps->e8_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e7_.ipFalseList=ps->e8_.spFalseList;

		//����ָ��
		ps->e8_.spTrueList=0;
		ps->e8_.spFalseList=0;
	}
	static void act_T5K_S6(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e6': e7'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e6_.iValFlag=ps->e7_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e6_.iType=ps->e7_.sType;
		pps[pps.size()-2]->getInhAttr()->e6_.iAddr=ps->e7_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e6_.ipTrueList=ps->e7_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e6_.ipFalseList=ps->e7_.spFalseList;

		//����ָ��
		ps->e7_.spTrueList=0;
		ps->e7_.spFalseList=0;
	}
	static void act_T5K_S7(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e5': e6'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e5_.iValFlag=ps->e6_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e5_.iType=ps->e6_.sType;
		pps[pps.size()-2]->getInhAttr()->e5_.iAddr=ps->e6_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e5_.ipTrueList=ps->e6_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e5_.ipFalseList=ps->e6_.spFalseList;

		//����ָ��
		ps->e6_.spTrueList=0;
		ps->e6_.spFalseList=0;
	}
	static void act_T5K_S8(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e4': e5'(value(����)->value(int))
		pps[pps.size()-2]->getInhAttr()->e4_.iValFlag=ps->e5_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e4_.iType=ps->e5_.sType;
		pps[pps.size()-2]->getInhAttr()->e4_.iAddr=ps->e5_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e4_.ipTrueList=ps->e5_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e4_.ipFalseList=ps->e5_.spFalseList;

		//����ָ��
		ps->e5_.spTrueList=0;
		ps->e5_.spFalseList=0;
	}
	static void act_T5K_S9(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e3': e4'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e3_.iValFlag=ps->e4_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e3_.iType=ps->e4_.sType;
		pps[pps.size()-2]->getInhAttr()->e3_.iAddr=ps->e4_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e3_.ipTrueList=ps->e4_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e3_.ipFalseList=ps->e4_.spFalseList;

		//����ָ��
		ps->e4_.spTrueList=0;
		ps->e4_.spFalseList=0;
	}
	static void act_T5K_S10(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//�ۺ����Դ��ݸ������e2': e3'(control flow->control flow)
		pps[pps.size()-2]->getInhAttr()->e2_.iValFlag=ps->e3_.sValFlag;
		pps[pps.size()-2]->getInhAttr()->e2_.iType=ps->e3_.sType;
		pps[pps.size()-2]->getInhAttr()->e2_.iAddr=ps->e3_.sAddr;
		pps[pps.size()-2]->getInhAttr()->e2_.ipTrueList=ps->e3_.spTrueList;		//ǳ����
		pps[pps.size()-2]->getInhAttr()->e2_.ipFalseList=ps->e3_.spFalseList;

		//����ָ��
		ps->e3_.spTrueList=0;
		ps->e3_.spFalseList=0;
	}
	static void act_T5K_S11(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		Syn_Attr *ps=pps.back()->getSynAttr();

		//����S�����T5����: e2'(control flow->value)
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

		//����S�����T5����
		pps[pps.size()-2]->getSynAttr()->T5.sValFlag=true;	
		pps[pps.size()-2]->getSynAttr()->T5.sType=pi->T5.iType;
		pps[pps.size()-2]->getSynAttr()->T5.sAddr=pi->T5.iAddr;
	}



	// Terminal action

	static void act_main(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//����main����
		pps[pps.size()-2]->getTempVar()->main_line.tLine=cpToken->Line();
	}

	static void act_id(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//����id����
		pps[pps.size()-2]->getTempVar()->option_id.tLine=cpToken->Line();
		*(pps[pps.size()-2]->getTempVar()->option_id.tLexime)=cpToken->toString();
	}

	static void act_bool(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//����bool����
		pps[pps.size()-2]->getSynAttr()->B.sType.type=t_BOOL;
	}

	static void act_char(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//����char����
		pps[pps.size()-2]->getSynAttr()->B.sType.type=t_CHAR;
	}

	static void act_short(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//����short����
		pps[pps.size()-2]->getSynAttr()->B.sType.type=t_SHORT;
	}

	static void act_int(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//����int����
		pps[pps.size()-2]->getSynAttr()->B.sType.type=t_INT;
	}

	static void act_float(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//����float����
		pps[pps.size()-2]->getSynAttr()->B.sType.type=t_FLOAT;
	}

	static void act_double(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//����double����
		pps[pps.size()-2]->getSynAttr()->B.sType.type=t_DOUBLE;
	}

	static void act_op(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//����operator����
		pps[pps.size()-2]->getTempVar()->op_line.tLine=cpToken->Line();
	}

	static void act_real(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//����real����
		pps[pps.size()-2]->getTempVar()->e14_real.tValue=dynamic_cast<Real const*>(cpToken)->getValue();
	}

	static void act_number(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//����number����
		pps[pps.size()-2]->getTempVar()->A_const.tLine=cpToken->Line();
		pps[pps.size()-2]->getTempVar()->A_const.tValue=dynamic_cast<Number const*>(cpToken)->getValue();
	}

	static void act_ascii(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//����ascii����
		pps[pps.size()-2]->getTempVar()->A_const.tLine=cpToken->Line();
		pps[pps.size()-2]->getTempVar()->A_const.tValue=dynamic_cast<Character const*>(cpToken)->getValue();
	}

	static void act_false(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//����false����
		pps[pps.size()-2]->getTempVar()->A_const.tLine=cpToken->Line();
		pps[pps.size()-2]->getTempVar()->A_const.tValue=false;
	}

	static void act_true(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//����true����
		pps[pps.size()-2]->getTempVar()->A_const.tLine=cpToken->Line();
		pps[pps.size()-2]->getTempVar()->A_const.tValue=true;
	}

	static void act_if(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//����if����
		pps[pps.size()-4]->getTempVar()->if_line.tLine=cpToken->Line();
	}

	static void act_while(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//����while����: do-while���
		if(pps[pps.size()-5]->isTerminal())
		{
			pps[pps.size()-4]->getTempVar()->do_expr.tLine=cpToken->Line();
		}
		//����while����: while���
		else
		{
			pps[pps.size()-5]->getTempVar()->while_line.tLine=cpToken->Line();
		}
	}

	static void act_break(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//����break����
		pps[pps.size()-2]->getTempVar()->break_line.tLine=cpToken->Line();
	}

	static void act_continue(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//����conntinue����
		pps[pps.size()-2]->getTempVar()->continue_line.tLine=cpToken->Line();
	}

	static void act_return(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//����return����
		pps[pps.size()-2]->getInhAttr()->optexpr3.iLine=cpToken->Line();

		//����ۺ�����sRetCnt�ļ���
		pps[pps.size()-4]->getSynAttr()->stmt.sRetCnt=1;
	}

	static void act_for(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//����for����
		pps[pps.size()-3]->getInhAttr()->optexpr2.iLine=cpToken->Line();		
		pps[pps.size()-6]->getInhAttr()->optexpr2.iLine=cpToken->Line();				
		pps[pps.size()-9]->getInhAttr()->optexpr2.iLine=cpToken->Line();
	}

	static void act_switch(PPS &pps,ErrorRecord &err_record,Env &context,ByteCode &byte_code,Token const* cpToken)
	{
		//����switch����
		pps[pps.size()-4]->getTempVar()->switch_expr_line.tLine=cpToken->Line();
	}
}