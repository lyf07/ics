#include "cpu/instr.h"
/*
Put the implementations of `xor' instructions here.
*/


static void instr_execute_2op() 
{
	operand_read(&opr_src);
	operand_read(&opr_dest);
// 	printf("in cmp, dest.datasize = %u\n", opr_dest.data_size);
// 	printf("before, in cmp, src = 0x%x, dest = 0x%x\n", opr_src.val, opr_dest.val);
// 	printf("in cmp, src.type = %i, dest.type = %i\n", opr_src.type, opr_dest.type);
	opr_dest.val = alu_xor(opr_src.val,  opr_dest.val, opr_dest.data_size);
	operand_write(&opr_dest);
// 	printf("after, in cmp, src = 0x%x, dest = 0x%x\n", opr_src.val, opr_dest.val);
}



make_instr_impl_2op(xor, r, rm, v)
make_instr_impl_2op(xor, rm, r, v)