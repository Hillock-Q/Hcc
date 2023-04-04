#include "CCompileManager.h"
#include "CHillock.h"

void const* CompileManager::compile(use_map const &in_use,dev_map const &dev,size_t &len)
{
	//	protocol format:
	//	[number]:unsigned short
	//	[id]:unsigned int
	//	[Byte-code]
	//	[id]:unsigned int
	//	[Byte-code]
	//	[id]:unsigned int
	//	[Byte-code]
	//  ...
	////	[cnt]:unsigned short
	////	[dev]:unsigned short
	////	[cnt2]:unsigned short
	////	[addr-type]:unsigned short
	////	[bit-flag]:bool
	////  ...
	////	[dev]:unsigned short
	////	[cnt2]:unsigned short
	////	[addr-type]:unsigned short
	////	[bit-flag]:bool
	////  ...

	byte_code.clear();		

	//	[number]:placeholder
	unsigned short number=0;
	Enqueue(byte_code,number);

	//为指定的使用集合生成字节码
	for(use_map::const_iterator citor_inuse=in_use.begin();citor_inuse!=in_use.end();++citor_inuse)
	{
		//在字节码集合中查找
		code_map::const_iterator citor_pass=pass_code.find(citor_inuse->first);

		//不存在
		if(citor_pass==pass_code.end())
		{
			//编译通过
			if(parser.parsing(citor_inuse->second,dev))
			{
				//更新计数
				++number;

				//	[id]
				Enqueue(byte_code,citor_inuse->first);

				//	[Byte-code]
				parser.get_byte_code().MakeByteCode(byte_code);

				//更新到字节码集合中
				pass_code[citor_inuse->first]=parser.get_byte_code();
			}
		}
		//存在
		else
		{
			//更新计数
			++number;

			//	[id]
			Enqueue(byte_code,citor_inuse->first);

			//	[Byte-code]
			citor_pass->second.MakeByteCode(byte_code);
		}
	}

	if(0<number)
	{	
		//修改字节码中的计数
		Modify(number);

		
		////加载设备映射表

		////生成临时映射表
		//dev_addt_map temp_map;
		//BuildMap(dev,temp_map);

		////	[cnt]
		//unsigned short cnt=temp_map.size();
		//Enqueue(byte_code,cnt);

		//for(dev_addt_map::const_iterator citor=temp_map.begin();citor!=temp_map.end();++citor)
		//{
		//	//	[dev]
		//	Enqueue(byte_code,citor->first);

		//	//	[cnt2]
		//	cnt=citor->second.size();
		//	Enqueue(byte_code,cnt);

		//	for(map<unsigned short,bool>::const_iterator citor2=citor->second.begin();citor2!=citor->second.end();++citor)
		//	{
		//		//	[addr-type]
		//		Enqueue(byte_code,citor2->first);

		//		//	[bit-flag]
		//		Enqueue(byte_code,citor2->second);
		//	}
		//}
	}

	//更新缓冲区长度
	len=byte_code.size();

	//返回容器数据内存起始指针
	return &(*(byte_code.begin()));
}
//void CompileManager::BuildMap(dev_map const& dm,dev_addt_map &dam)
//{
//	dam.clear();
//
//	using std::make_pair;
//
//	for(dev_map::const_iterator citor=dm.begin();citor!=dm.end();++citor)
//	{
//		map<unsigned short,bool> temp_map;
//
//		for(addt_map::const_iterator citor2=citor->second.second.begin();citor2!=citor->second.second.end();++citor2)
//		{
//			temp_map.insert(make_pair(citor2->second.first,citor2->second.second));
//		}
//
//		dam.insert(make_pair(citor->second.first,temp_map));
//	}
//}
void CompileManager::Modify(unsigned short number)
{
	unsigned char const *p=reinterpret_cast<unsigned char const*>(&number);

	for(size_t i=0;i<sizeof(number);++i)
		byte_code[i]=p[i];
}
bool CompileManager::compile(unsigned int code_id,string const &code,dev_map const &dev)
{
	//如果编译通过
	if(parser.parsing(code,dev))
	{
		//更新到字节码集合中
		pass_code[code_id]=parser.get_byte_code();

		return true;
	}
	else
	{
		return false;
	}
}
CompileManager::ErrorRecord const& CompileManager::getErrorRecord()const
{
	return parser.get_error_record();
}
CompileManager::fun_set const& CompileManager::getFunSet()const
{
	return parser.getFunSet();	
}
FunInfo const* CompileManager::getSignature(string const& name)
{
	//此处为特殊库函数提供优先查找表

	//默认查找
	return parser.getSignature(name);
}
CompileManager::key_word const& CompileManager::getKeyWords()const
{
	return parser.getKeyWord();
}
CompileManager::var_map const& CompileManager::getVars(string const &code,dev_map const &dev)
{
	return parser.getVars(code,dev);
}
