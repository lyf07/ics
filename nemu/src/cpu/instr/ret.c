#include "cpu/instr.h"
/*
Put the implementations of `ret' instructions here.
*/
make_instr_func(ret) {
    OPERAND opr;
    opr.addr = cpu.esp;
    opr.type = OPR_MEM;
    opr.data_size = data_size;
    operand_read(&opr);
    cpu.eip = opr.val - 1;
    return 1;
}