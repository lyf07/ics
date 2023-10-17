#include "cpu/instr.h"
/*
Put the implementations of `cmp' instructions here.
*/

static void instr_execute_2op() 
{
	operand_read(&opr_src);
	alu_sub(sign_ext(opr_src.val, 32), sign_ext(opr_dest.val, 32), 32);
	operand_write(&opr_dest);
}

make_instr_impl_2op(cmp, i, rm, bv)
make_instr_impl_2op(cmp, i, r, b)