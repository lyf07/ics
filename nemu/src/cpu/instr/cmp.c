#include "cpu/instr.h"
/*
Put the implementations of `cmp' instructions here.
*/

static void instr_execute_2op() 
{
	operand_read(&opr_src);
	alu_sub(sign_ext(opr_src.val, opr_src.data_size), sign_ext(opr_dest.val, opr_dest.data_size), opr_src.data_size);
	printf("in cmp: opr_dest = 0x%x", opr_dest);
	operand_write(&opr_dest);
}

make_instr_impl_2op(cmp, i, rm, bv)
make_instr_impl_2op(cmp, i, r, b)