#include "cpu/instr.h"
/*
Put the implementations of `add' instructions here.
*/
static void instr_execute_2op() 
{
	 operand_read(&opr_src);
    operand_read(&opr_dest);
    //opr_dest.val += opr_src.val;
    opr_src.val = sign_ext(opr_src.val, opr_src.data_size);
    opr_dest.val = alu_add(opr_dest.val, opr_src.val, opr_dest.data_size);
	operand_write(&opr_dest);//ebp的值存到esp指向的内存区域

}

make_instr_impl_2op(add, r, rm, v)
