#include "CNonTerminal.h"

Produce const* NonTerminal::getProduce(Token const *ptoken)const
{
	//�����÷��ս�������в���ʽ
	for(produce_list::const_iterator citor=ppl->begin();citor!=ppl->end();++citor)
	{
		//�����Ĭ�Ϲ���
		if(citor->second.empty())
			return citor->first;

		//�����ƥ�����
		if(citor->second.count(ptoken->Tag()))
			return citor->first;
	}

	//�޶�Ӧ����
	return 0;
}