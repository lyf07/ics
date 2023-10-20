#include "cpu/instr.h"
/*
Put the implementations of `sub' instructions here.
*/
static void instr_execute_2op() 
{
	operand_read(&opr_src);
	operand_read(&opr_dest);
	opr_dest.val = alu_sub(sign_ext(opr_src.val, opr_src.data_size), opr_dest.val, opr_dest.data_size);
	operand_write(&opr_dest);
}

make_instr_impl_2op(sub, i, rm, b)
make_instr_impl_2op(sub, r, rm, v)
make_instr_impl_2op(sub, i, rm, bv)
make_instr_impl_2op(sub, rm, r, v)

// make_instr_func(sub_i2rm_bv)
// {
//     OPERAND i, rm;
//     i.data_size = 8;
//     i.type = OPR_IMM;
//     i.addr = eip + 2;
//     operand_read(&i);
    
//     rm.data_size = data_size;
//     rm.type = OPR_REG;
//     rm.addr = REG_AH;
//     operand_read(&rm);

//     rm.val -= i.val;
//     operand_write(&rm);
// 	print_asm_2("sub", "", 3, &rm, &i);
//     return 3;
// }


