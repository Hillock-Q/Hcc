#pragma once

namespace Compiler
{
	const size_t OP_BASE=0;

	//mid-ins set: 32
	enum Operator
	{
		// no-op
		op_no_op=OP_BASE+0,


		//	x = y					copy operator: 1
		op_assign=OP_BASE+1,

		//	x = op y				unary operators: 3
		op_plus=OP_BASE+2,						// +
		op_minus=OP_BASE+3,						// -
		op_bit_not=OP_BASE+4,					// ~

		//	x = y op z				binary operators: 16
		op_mul=OP_BASE+5,						// *
		op_div=OP_BASE+6,						// /
		op_mod=OP_BASE+7,						// %
		op_add=OP_BASE+8,						// +
		op_sub=OP_BASE+9,						// -

		op_lsht=OP_BASE+10,						// <<
		op_rsht=OP_BASE+11,						// >>
		op_bit_and=OP_BASE+12,					// &
		op_bit_xor=OP_BASE+13,					// ^
		op_bit_or=OP_BASE+14,					// |

		op_less=OP_BASE+15,						// <
		op_le=OP_BASE+16,						// <=
		op_greater=OP_BASE+17,					// >
		op_ge=OP_BASE+18,						// >=
		op_eq=OP_BASE+19,						// ==
		op_ne=OP_BASE+20,						// !=


		//	x=y[i]					read array: 1
		op_read_array=OP_BASE+21,

		//	x[i]=y					write array: 1
		op_write_array=OP_BASE+22,


		//	goto L					unconditionally jump operator: 1
		op_goto=OP_BASE+23,

		//	if x goto L				conditionally jump operator: 1
		op_if_true_goto=OP_BASE+24,

		//	if false x goto L		conditionally jump operator: 1
		op_if_false_goto=OP_BASE+25,


		//	param x					pass parameter: 1
		op_param=OP_BASE+26,

		//	call p,n				function call: 1
		op_call=OP_BASE+27,

		//	y=call p,n				function call: 1
		op_call_ass=OP_BASE+28,
		
		//	return					only return: 1
		op_return=OP_BASE+29,

		//	return y				return value: 1
		op_return_value=OP_BASE+30,


		//	invalid op
		op_invalid=OP_BASE+31,
	};
}
