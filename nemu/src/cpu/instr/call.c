#include "cpu/instr.h"
/*
Put the implementations of `call' instructions here.
*/
static void instr_execute_1op() {
    operand_read(&opr_src);

    int offset = sign_ext(opr_src.val, opr_src.data_size);
    cpu.eip += offset;

    return 1 + opr_src.data_size / 8;
}


make_instr_impl_1op(call, i, near) 