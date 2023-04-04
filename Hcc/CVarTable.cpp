#include "CVarTable.h"
#include "CHillock.h"
#include "CDataType.h"


void VarTable::Clear()
{
	Table::Clear();

	var_table.clear();
}
bool VarTable::isVar(string const &name)const
{
	return var_table.find(name)==var_table.end() ? false : true;
}
void VarTable::defineVar(string const &name,VarInfo const &var_info,size_t line)
{
	if(name.empty())
		return;

	//���ɱ����ڴ������Ϣ
	AllocInfo alloc_info;
	alloc_info.var_info=var_info;
	alloc_info.line=line;
	alloc_info.offset=offset;

	//���������
	if(var_table.insert(make_pair(name,alloc_info)).second)
		offset++;
}
Address VarTable::Temp(VarInfo const &var_info)
{
	//������ʱ�����ڴ������Ϣ
	AllocInfo alloc_info;
	alloc_info.var_info=var_info;
	alloc_info.line=-1;	//��Ч
	alloc_info.offset=offset++;

	//���������(�ڱ�������,��ʱ����������������Ϊ����,�Ӷ��������κ��û��Զ������ֳ�ͻ)
	var_table.insert(make_pair(toString(int(++temp_cnt)),alloc_info));	

	Address addr;
	addr.section=s_INVALID;
	addr.offset=alloc_info.offset;

	return addr;
}
AllocInfo const* VarTable::getAllocInfo(string const &name)const
{
	var_map::const_iterator citor=var_table.find(name);

	//���ر����ڴ������Ϣ
	return citor==var_table.end() ? 0 : &(citor->second);
}
Address VarTable::getAddress(string const &name)const
{	
	var_map::const_iterator citor=var_table.find(name);

	Address addr;

	if(citor==var_table.end())
	{
		addr.section=s_INVALID;
		addr.offset=-1;
	}
	else
	{
		addr.section=section;
		addr.offset=citor->second.offset;
	}

	return addr;
}
void VarTable::getVarSet(var_map2 &vm)const
{
	for(var_map::const_iterator citor=var_table.begin();citor!=var_table.end();++citor)
	{
		//������ʱ����(���ַ�Ϊ����)
		if(isdigit(citor->first[0]))
			continue;

		//׷�ӵ��ɼ���������(�����ظ�,������ǰ������)
		vm.insert(make_pair(citor->first,citor->second.var_info));
	}
}
void VarTable::BuildByteCode(byte_cont &byte_code)const
{
	typedef map<size_t,VarInfo> alloc_map;

	//�˱�����map���Զ�������,��offsetΪkey����,�������յķ���˳��
	alloc_map alloc_table;	

	for(var_map::const_iterator citor=var_table.begin();citor!=var_table.end();++citor)
		alloc_table.insert(std::make_pair(citor->second.offset,citor->second.var_info));

	//	format:
	//	[Number]:unsigned int
	//	[Data]
	//	[Data]
	//	[Data]
	//  ...

	//	[Number]
	Compiler::Enqueue(byte_code,unsigned int(alloc_table.size()));

	//	[Data]
	for(alloc_map::const_iterator citor2=alloc_table.begin();citor2!=alloc_table.end();++citor2)
		BuildByteCode(byte_code,citor2->second);
}
void VarTable::BuildByteCode(byte_cont &c,VarInfo const &var_info)const
{	
	//	[Data] format:
	//	[type-flag]:unsigned char
	//	[array-flag]:bool
	//	[length]:unsigned int

	Compiler::t_VOID==var_info.type ? (void)0 : Compiler::Enqueue(c,var_info.type),Compiler::Enqueue(c,var_info.is_array),Compiler::Enqueue(c,var_info.length);
}