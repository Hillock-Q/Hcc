#include "CNonTerminal.h"

Produce const* NonTerminal::getProduce(Token const *ptoken)const
{
	//遍历该非终结符的所有产生式
	for(produce_list::const_iterator citor=ppl->begin();citor!=ppl->end();++citor)
	{
		//如果是默认规则
		if(citor->second.empty())
			return citor->first;

		//如果是匹配规则
		if(citor->second.count(ptoken->Tag()))
			return citor->first;
	}

	//无对应规则
	return 0;
}