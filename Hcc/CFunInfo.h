#pragma once

#include "CVarInfo.h"
#include <vector>

namespace Compiler
{	
	//函数信息
	struct FunInfo
	{		
		unsigned short id;	//函数标识
		unsigned char  ret_type;		//返回类型
		size_t line;	//声明位置
		std::vector<VarInfo> param_list;	//参数列表
	};
}