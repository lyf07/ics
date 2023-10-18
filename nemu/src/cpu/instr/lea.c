#include "cpu/instr.h"
/*
Put the implementations of `lea' instructions here.
*/
static void instr_execute_2op() 
{
	operand_read(&opr_src);
	operand_read(&opr_dest);
    printf("src: val = 0x%x, addr = 0x%x, type = %i\n", opr_src.val, opr_src.addr, opr_src.type);
    printf("dest: val = 0x%x, addr = 0x%x, type = %i\n\n\n", opr_dest.val, opr_dest.addr, opr_dest.type);
    opr_dest.val = opr_src.addr;
    operand_write(&opr_dest);
}

make_instr_impl_2op(lea, rm, r, v)
