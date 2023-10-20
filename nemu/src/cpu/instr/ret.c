#include "cpu/instr.h"
/*
Put the implementations of `ret' instructions here.
*/
make_instr_func(ret) {
    OPERAND opr;
    opr.addr = cpu.esp;
    opr.type = OPR_MEM;
    cpu.esp += 4;//push和pop都是按32位
    opr.data_size = 32;
    operand_read(&opr);
    cpu.eip = opr.val - 1;
    return 1;
}