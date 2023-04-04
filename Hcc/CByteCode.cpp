#include "CByteCode.h"
#include "CHillock.h"

void ByteCode::BuildConstTableCode(ConstTable const& c_table)
{
	c_table.BuildByteCode(const_data);
}
void ByteCode::BuildGlobalTableCode(GlobalTable const& g_table)
{
	g_table.BuildByteCode(global_data);
}
void ByteCode::BuildInitCode(MiddleCode const& i_code)
{
	i_code.BuildByteCode(init_code);
}
void ByteCode::BuildLocalCode(size_t id,LocalTable const& l_table,MiddleCode const& f_code)
{
	//首先进行查找
	local_cont::iterator itor=local_list.find(id);
	
	//如果不存在
	if(itor==local_list.end())
	{
		//插入
		pair<local_cont::iterator,bool> pi=local_list.insert(make_pair(id,make_pair(byte_cont(),byte_cont())));

		//生成局部数据字节码
		l_table.BuildByteCode(pi.first->second.first);
	
		//生成函数指令字节码
		f_code.BuildByteCode(pi.first->second.second);
	}
	//如果存在(出现函数重定义情况,表明语法分析已经出错)
	else
	{
		//no-op
	}
}
void ByteCode::MakeByteCode(byte_cont &byte_code)const
{
	//	Byte-code format:
	//	[const table]
	//	[global table]
	//	[init-code]
	//	[number]:unsigned int
	//	[id]:unsigned int
	//	[local table]
	//	[fun-code]	
	//	[id]:unsigned int
	//	[local table]
	//	[fun-code]	
	//	...


	//	[const table]
	for(byte_cont::const_iterator citor=const_data.begin();citor!=const_data.end();++citor)
		byte_code.push_back(*citor);

	//	[global table]
	for(byte_cont::const_iterator citor=global_data.begin();citor!=global_data.end();++citor)
		byte_code.push_back(*citor);

	//	[init-code]
	for(byte_cont::const_iterator citor=init_code.begin();citor!=init_code.end();++citor)
		byte_code.push_back(*citor);

	//get the number of called function
	unsigned int num=0;
	for(local_cont::const_iterator citor=local_list.begin();citor!=local_list.end();++citor)
		if(call_set.count(citor->first))
			num++;

	//	[number]
	Enqueue(byte_code,num);

	//traversal <id, <local_data,fun_code> >
	for(local_cont::const_iterator citor=local_list.begin();citor!=local_list.end();++citor)
		if(call_set.count(citor->first))
		{
			//	[id] 
			Enqueue(byte_code,unsigned int(citor->first));

			//	[local table]
			for(byte_cont::const_iterator citor1=citor->second.first.begin();citor1!=citor->second.first.end();++citor1)
				byte_code.push_back(*citor1);

			//	[fun-code]
			for(byte_cont::const_iterator citor1=citor->second.second.begin();citor1!=citor->second.second.end();++citor1)
				byte_code.push_back(*citor1);
		}
}
ByteCode::fun_set& ByteCode::getCallSet()
{
	return call_set;
}
void ByteCode::Clear()
{	
	init_code.clear();
	const_data.clear();
	global_data.clear();
	local_list.clear();
	call_set.clear();
}
