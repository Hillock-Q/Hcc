#pragma once

namespace Compiler
{	
	//������Ϣ
	struct VarInfo
	{
		unsigned char type;
		bool is_array;		// type!=void ʱ��Ч
		unsigned int length;		// type!=void && is_array==true ʱ��Ч
	};

	//������Ϣ
	struct AllocInfo
	{
		VarInfo var_info;
		size_t line;	//����λ��
		unsigned int offset;
	};
}