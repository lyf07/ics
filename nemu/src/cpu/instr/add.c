#include "cpu/instr.h"
/*
Put the implementations of `add' instructions here.
*/
static void instr_execute_2op() 
{
	operand_read(&opr_src);
	opr_dest.val = alu_add(sign_ext(opr_src.val, opr_src.data_size), sign_ext(opr_dest.val, opr_dest.data_size), opr_src.data_size);
	operand_write(&opr_dest);
}

make_instr_impl_2op(add, r, rm, v)
