#pragma once

namespace Compiler
{	
	//变量信息
	struct VarInfo
	{
		unsigned char type;
		bool is_array;		// type!=void 时有效
		unsigned int length;		// type!=void && is_array==true 时有效
	};

	//分配信息
	struct AllocInfo
	{
		VarInfo var_info;
		size_t line;	//声明位置
		unsigned int offset;
	};
}