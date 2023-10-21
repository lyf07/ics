#include "cpu/instr.h"
/*
Put the implementations of `and' instructions here.
*/
static void instr_execute_2op() 
{
	operand_read(&opr_src);
	operand_read(&opr_dest);
	opr_dest.val = alu_and(opr_dest.val, sign_ext(opr_src.val, opr_src.data_size), opr_dest.data_size);
	operand_write(&opr_dest);
}


make_instr_impl_2op(and, i, rm, bv)
make_instr_impl_2op(and, r, rm, v)