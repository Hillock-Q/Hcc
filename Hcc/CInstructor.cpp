#include "CInstructor.h"
#include "CHillock.h"
#include "COperator.h"

Instructor::Instructor(unsigned short opr)
:
	op(opr)
{
	lhs.section=Compiler::s_INVALID;
	lhs.offset=0;
	rhs.section=Compiler::s_INVALID;
	rhs.offset=0;
	val.section=Compiler::s_INVALID;
	val.offset=0;
}
Instructor::Instructor(unsigned short opr,Address arg1)
:
	op(opr),
	lhs(arg1)
{
	rhs.section=Compiler::s_INVALID;
	rhs.offset=0;
	val.section=Compiler::s_INVALID;
	val.offset=0;
}
Instructor::Instructor(unsigned short opr,Address arg1,Address arg2)
:
	op(opr),
	lhs(arg1),
	rhs(arg2)
{
	val.section=Compiler::s_INVALID;
	val.offset=0;
}
Instructor::Instructor(unsigned short opr,Address arg1,Address arg2,Address result)
:
	op(opr),
	lhs(arg1),
	rhs(arg2),
	val(result)
{}
void Instructor::BuildByteCode(byte_cont &c)const
{
	// [instr] format:
	// [op]/[op][a1]/[op][a1][a2]/[op][a1][a2][a3]

	// [op]
	Compiler::Enqueue(c,op);

	switch(op)
	{
	default:

		// [a1]
		BuildByteCode(c,lhs);

		switch(op)
		{
		default:

			// [a2]:
			BuildByteCode(c,rhs);

			switch(op)
			{
			default:

				// [a3]:19
				BuildByteCode(c,val);			
				break;

			case op_assign:			// x = y	
			case op_plus:			// +
			case op_minus:			// -
			case op_bit_not:		// ~
			case op_call:			// call p,n
			case op_if_true_goto:	// if x goto L		
			case op_if_false_goto:	// if false x goto L
				break;
			}
			break;

		case op_goto:			// goto L
		case op_param:			// param x	
		case op_return_value:	// return y	
			break;
		}
		break;

	//no-op:3
	case op_return:			// return	
	case op_no_op:			// no-op
	case op_invalid:		// invalid op
		break;
	}
}
void Instructor::BuildByteCode(byte_cont &c,Address const &addr)const
{
	// [a] format:
	// [section]->unsigned char
	// [offset]->unsigned int

	Compiler::s_INVALID == addr.section ? (void)0 : Compiler::Enqueue(c,addr.section),Compiler::Enqueue(c,unsigned int(addr.offset));
}
unsigned short Instructor::getOpr()const
{
	return op;
}
void Instructor::BackPatch(Address const& addr)
{
	switch(op)
	{
	//back patch lhs
	case op_goto:	
		lhs=addr;
		break;

	//back patch rhs
	case op_if_true_goto:	
	case op_if_false_goto:
		rhs=addr;
		break;

	//no-op
	default:
		break;
	}
}