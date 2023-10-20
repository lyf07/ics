#include "cpu/instr.h"
/*
Put the implementations of `call' instructions here.
*/
make_instr_func(call_i_near) {
      // 5 = 1(call's opcode) + 4(16 immediate num)
    
//push eip
        int len = 1;
        len += 32 / 8;
       	cpu.esp -= 4;
	    paddr_write(cpu.esp, 4, cpu.eip + 5); 
    //读取目标地址
        OPERAND opr_src;
        opr_src.type = OPR_IMM;
        opr_src.sreg = SREG_CS;
        opr_src.data_size = data_size;
        opr_src.addr = eip + 1;
        operand_read(&opr_src);
    //跳转
        int offset = sign_ext(opr_src.val, data_size); //读4位
        print_asm_1("call_near", "", len, &opr_src);
        cpu.eip += offset;
    return len;

}
