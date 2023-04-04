#pragma once

#include "CVarInfo.h"
#include <vector>

namespace Compiler
{	
	//������Ϣ
	struct FunInfo
	{		
		unsigned short id;	//������ʶ
		unsigned char  ret_type;		//��������
		size_t line;	//����λ��
		std::vector<VarInfo> param_list;	//�����б�
	};
}