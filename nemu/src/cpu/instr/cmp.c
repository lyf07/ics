#include "cpu/instr.h"
/*
Put the implementations of `cmp' instructions here.
*/

static void instr_execute_2op() 
{
	operand_read(&opr_src);
	printf("in cmp, src = 0x%x, dest = 0x%x\n", opr_src.val, opr_dest.val);
	alu_sub(sign_ext(opr_src.val, opr_src.data_size), sign_ext(opr_dest.val, opr_dest.data_size), opr_src.data_size);
}

make_instr_impl_2op(cmp, i, rm, bv)
make_instr_impl_2op(cmp, i, r, b)
make_instr_impl_2op(cmp, i, rm, v)