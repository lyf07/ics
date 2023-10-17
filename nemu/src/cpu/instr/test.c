#include "cpu/instr.h"
/*
Put the implementations of `test' instructions here.
*/
static void instr_execute_2op() 
{
	operand_read(&opr_src);
	printf("opr_src: %u\n", opr_src.val);
	printf("opr_test: %u\n\n", opr_dest.val);
	alu_and(opr_src.val, opr_dest.val, opr_src.data_size);
	operand_write(&opr_dest);
}



make_instr_impl_2op(test, r, rm, v)