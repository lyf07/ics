#include "cpu/instr.h"
/*
Put the implementations of `cmp' instructions here.
*/
static void instr_execute_2op()
{
    operand_read(&opr_src);
    operand_read(&opr_dest);
    //printf("%x\t%x\n",opr_src.val,opr_dest.val);
    #if 1//8位src需要先ext
        opr_src.val = sign_ext(opr_src.val, opr_src.data_size);
    #endif
    
    #if 1
        alu_sub(opr_src.val, opr_dest.val, opr_dest.data_size);//alu_sub是"2参-1参"，cmp是"dest-src"
        //printf("%x\t%x\n",cpu.eflags.ZF,cpu.eflags.CF);
        //printf("jl(signed):sf%d\tof%d\n", cpu.eflags.SF, cpu.eflags.OF);
    #elif 0
        if(opr_src.val == opr_dest.val){
            cpu.eflags.ZF = 1;
        }
        else if(opr_dest.val < opr_src.val){
            cpu.eflags.ZF = 0;
            cpu.eflags.CF = 1;//借位
        }
        else if(opr_dest.val > opr_src.val){
            cpu.eflags.ZF = 0;
            cpu.eflags.CF = 0;
        }
    #endif
}

make_instr_impl_2op(cmp, i, rm, bv)
make_instr_impl_2op(cmp, i, rm, v)
make_instr_impl_2op(cmp, i, a, b)
make_instr_impl_2op(cmp, i, a, v)
make_instr_impl_2op(cmp, i, rm, b)
make_instr_impl_2op(cmp, rm, r, v)
make_instr_impl_2op(cmp, rm, r, b)
make_instr_impl_2op(cmp, r, rm, b)
make_instr_impl_2op(cmp, r, rm, v)
