#include "cpu/instr.h"
/*
Put the implementations of `cmp' instructions here.
*/

static void instr_execute_2op() 
{
	operand_read(&opr_src);
	operand_read(&opr_dest);
// 	printf("in cmp, dest.datasize = %u\n", opr_dest.data_size);
// 	printf("before, in cmp, src = 0x%x, dest = 0x%x\n", opr_src.val, opr_dest.val);
// 	printf("in cmp, src.type = %i, dest.type = %i\n", opr_src.type, opr_dest.type);
	alu_sub(sign_ext(opr_src.val, opr_src.data_size), opr_dest.val, opr_dest.data_size);
// 	printf("after, in cmp, src = 0x%x, dest = 0x%x\n", opr_src.val, opr_dest.val);
}

make_instr_impl_2op(cmp, i, rm, bv)
make_instr_impl_2op(cmp, i, rm, b)
make_instr_impl_2op(cmp, r, rm, v)
make_instr_impl_2op(cmp, i, a, b)
make_instr_impl_2op(cmp, i, r, b)
make_instr_impl_2op(cmp, i, rm, v)
make_instr_impl_2op(cmp, rm, r, v)
make_instr_impl_2op(cmp, rm, r, b)