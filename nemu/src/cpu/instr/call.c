#include "cpu/instr.h"
/*
Put the implementations of `call' instructions here.
*/
make_instr_func(call_i_near) {
    
	cpu.esp -= 4;
	paddr_write(cpu.esp, 4, cpu.eip + 5);   // 5 = 1(call's opcode) + 4(16 immediate)
    
    
    OPERAND opr;
    opr.type = OPR_IMM;
    opr.addr = cpu.eip + 1;
    opr.data_size = 32;
    operand_read(&opr);
    
    cpu.eip += sign_ext(opr.val, opr.data_size);
    
    return 5;
    
}
