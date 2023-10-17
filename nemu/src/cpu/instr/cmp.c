#include "cpu/instr.h"
/*
Put the implementations of `cmp' instructions here.
*/

static void instr_execute_2op() 
{
	operand_read(&opr_src);
	printf("cur data_size is: %u \n", data_size);
	alu_sub(sign_ext(opr_src.val, data_size), sign_ext(opr_dest.val, data_size), data_size);
	operand_write(&opr_dest);
}

make_instr_impl_2op(cmp, i, rm, bv)
make_instr_impl_2op(cmp, i, r, b)