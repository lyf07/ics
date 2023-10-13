#include "cpu/instr.h"
/*
Put the implementations of `cmp' instructions here.
*/

static void instr_execute_2op() 
{
	operand_read(&opr_src);
	alu_sub(opr_src, opr_dest, data_size);
	operand_write(&opr_dest);
}

make_instr_impl_2op(cmp, i, rm, bv)