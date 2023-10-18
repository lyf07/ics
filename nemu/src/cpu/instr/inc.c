#include "cpu/instr.h"
/*
Put the implementations of `inc' instructions here.
*/
static void instr_execute_1op(){
    operand_read(&opr_src);
    opr_src.val++;
    printf("in inc, val = 0x%x\n", opr_src.val);
    operand_write(&opr_src);
}


make_instr_impl_1op(inc, rm, w);
make_instr_impl_1op(inc, rm, b);
make_instr_impl_1op(inc, rm, v);