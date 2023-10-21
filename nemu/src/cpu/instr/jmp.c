#include "cpu/instr.h"

make_instr_func(jmp_near)
{
        OPERAND rel;
        rel.type = OPR_IMM;
        rel.sreg = SREG_CS;
        rel.data_size = data_size;
        rel.addr = eip + 1;

        operand_read(&rel);

        int offset = sign_ext(rel.val, data_size);
        // thank Ting Xu from CS'17 for finding this bug
        print_asm_1("jmp", "", 1 + data_size / 8, &rel);

        cpu.eip += offset;

        return 1 + data_size / 8;
}


make_instr_func(jmp_short)
{
        OPERAND rel;
        rel.type = OPR_IMM;
        rel.sreg = SREG_CS;
        rel.data_size = 8;
        rel.addr = eip + 1;
        // printf("data_size = 0x%x\n", data_size);
        operand_read(&rel);

        int offset = sign_ext(rel.val, 8);
        // thank Ting Xu from CS'17 for finding this bug
        print_asm_1("jmp", "", 1 + data_size / 8, &rel);
        cpu.eip += offset;

        return 1 + 8 / 8;
}

make_instr_func(jmp_near_indirect) {
    int len = 1;
    decode_data_size_v
    decode_operand_rm
    operand_read(&opr_src);
    cpu.eip = sign_ext(opr_src.val, opr_src.data_size) - len;
    return len;
    
}












