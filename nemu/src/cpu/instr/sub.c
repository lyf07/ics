#include "cpu/instr.h"
/*
Put the implementations of `sub' instructions here.
*/
static void instr_execute_2op() 
{
	operand_read(&opr_src);
	operand_read(&opr_dest);
	alu_sub(sign_ext(opr_src.val, opr_src.data_size), sign_ext(opr_dest.val, opr_dest.data_size), opr_dest.data_size);
}

make_instr_impl_2op(sub, i, rm, b)