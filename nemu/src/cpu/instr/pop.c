#include "cpu/instr.h"
/*
Put the implementations of `pop' instructions here.
*/
static void instr_execute_1op() 
{
	operand_read(&opr_src);
	OPERAND opr;
	opr.type = OPR_MEM;
	opr.addr = cpu.esp;
	operand_read(&opr);
	opr_src.val = opr.val;
	operand_write(&opr_src);
	cpu.esp += 4;
	return 1;
}


make_instr_impl_1op(pop, r, v);