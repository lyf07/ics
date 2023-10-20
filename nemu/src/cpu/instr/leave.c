#include "cpu/instr.h"
/*
Put the implementations of `leave' instructions here.
*/
make_instr_func(leave) {
    cpu.esp = cpu.ebp;
    OPERAND opr;
    opr.type = OPR_MEM;
    opr.addr = cpu.ebp;
    operand_read(&opr);
    cpu.ebp = opr.val;
    cpu.esp += 4;
    return 1;
}