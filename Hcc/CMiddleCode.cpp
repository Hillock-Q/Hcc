#include "CMiddleCode.h"
#include "COperator.h"
#include "CHillock.h"

void MiddleCode::Clear()
{
	code.clear();
}
void MiddleCode::Gen(unsigned short opr)
{
	code.push_back(Instructor(opr));
}
void MiddleCode::Gen(unsigned short opr,Address arg1)
{
	code.push_back(Instructor(opr,arg1));
}
void MiddleCode::Gen(unsigned short opr,Address arg1,Address arg2)
{
	code.push_back(Instructor(opr,arg1,arg2));	
}
void MiddleCode::Gen(unsigned short opr,Address arg1,Address arg2,Address result)
{
	code.push_back(Instructor(opr,arg1,arg2,result));	
}
void MiddleCode::BuildByteCode(byte_cont &byte_code)const
{
	// Code format:
	// [Number]:unsigned int
	// [instr]
	// [instr]
	// [instr]
	// ...

	// [Number]
	Compiler::Enqueue(byte_code,unsigned int(code.size()));

	// [instr]
	for(ins_cont::const_iterator citor=code.begin();citor!=code.end();++citor)
		citor->BuildByteCode(byte_code);	
}
size_t MiddleCode::getNextInstr()
{
	return code.size();
}
void MiddleCode::BackPatch(instr_list *pinstrlist,Address const& addr)
{
	if(pinstrlist)
		for(instr_list::const_iterator citor=pinstrlist->begin();citor!=pinstrlist->end();++citor)
			if(*citor<code.size())
				code[*citor].BackPatch(addr);
}
unsigned short MiddleCode::getLastInstr()const
{
	if(code.empty())
		return Compiler::op_invalid;
	else
		return code.back().getOpr();
}