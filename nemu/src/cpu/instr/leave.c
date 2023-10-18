#include "cpu/instr.h"
/*
Put the implementations of `leave' instructions here.
*/
make_instr_func(leave) {
    cpu.esp = cpu.ebp;
    cpu.esp += 4;
    return 1;
}