#include "cpu/instr.h"
/*
Put the implementations of `push' instructions here.
*/


static void instr_execute_1op() 
{
	operand_read(&opr_src);
	cpu.esp -= 4;
	paddr_write(cpu.esp, 4, opr_src.val);
}



make_instr_impl_1op(push, r, v);                        