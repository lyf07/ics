#include "cpu/instr.h"

instr_func opcode_entry[256] = {
    /* 0x00 - 0x03*/ inv, __ref_add_r2rm_v, inv, inv,
    /* 0x04 - 0x07*/ inv, __ref_add_i2a_v, inv, inv,
    /* 0x08 - 0x0b*/ inv, __ref_or_r2rm_v, __ref_or_rm2r_b, __ref_or_rm2r_v,
    /* 0x0c - 0x0f*/ inv, inv, inv, opcode_2_byte,
    /* 0x10 - 0x13*/ inv, __ref_adc_r2rm_v, inv, inv,
    /* 0x14 - 0x17*/ inv, inv, inv, inv,
    /* 0x18 - 0x1b*/ inv, inv, inv, __ref_sbb_rm2r_v,
    /* 0x1c - 0x1f*/ inv, inv, inv, inv,
    /* 0x20 - 0x23*/ inv, __ref_and_r2rm_v, __ref_and_rm2r_b, inv,
    /* 0x24 - 0x27*/ inv, inv, inv, inv,
    /* 0x28 - 0x2b*/ inv, __ref_sub_r2rm_v, inv, __ref_sub_rm2r_v,
    /* 0x2c - 0x2f*/ inv, inv, inv, inv,
    /* 0x30 - 0x33*/ inv, __ref_xor_r2rm_v, inv, __ref_xor_rm2r_v,
    /* 0x34 - 0x37*/ inv, inv, inv, inv,
    /* 0x38 - 0x3b*/ inv, __ref_cmp_r2rm_v, __ref_cmp_rm2r_b, __ref_cmp_rm2r_v,
    /* 0x3c - 0x3f*/ __ref_cmp_i2a_b, inv, inv, inv,
    /* 0x40 - 0x43*/ __ref_inc_r_v, __ref_inc_r_v, __ref_inc_r_v, __ref_inc_r_v,
    /* 0x44 - 0x47*/ __ref_inc_r_v, __ref_inc_r_v, __ref_inc_r_v, __ref_inc_r_v,
    /* 0x48 - 0x4b*/ __ref_dec_r_v, __ref_dec_r_v, __ref_dec_r_v, __ref_dec_r_v,
    /* 0x4c - 0x4f*/ __ref_dec_r_v, __ref_dec_r_v, __ref_dec_r_v, __ref_dec_r_v,
    /* 0x50 - 0x53*/ __ref_push_r_v, __ref_push_r_v, __ref_push_r_v, __ref_push_r_v,
    /* 0x54 - 0x57*/ __ref_push_r_v, __ref_push_r_v, __ref_push_r_v, __ref_push_r_v,
    /* 0x58 - 0x5b*/ __ref_pop_r_v, __ref_pop_r_v, __ref_pop_r_v, __ref_pop_r_v,
    /* 0x5c - 0x5f*/ __ref_pop_r_v, __ref_pop_r_v, __ref_pop_r_v, __ref_pop_r_v,
    /* 0x60 - 0x63*/ inv, inv, inv, inv,
    /* 0x64 - 0x67*/ inv, inv, data_size_16, inv,
    /* 0x68 - 0x6b*/ __ref_push_i_v, inv, __ref_push_i_b, inv,
    /* 0x6c - 0x6f*/ inv, inv, inv, inv,
    /* 0x70 - 0x73*/ inv, inv, inv, inv,
    /* 0x74 - 0x77*/ __ref_je_short_, __ref_jne_short_, __ref_jna_short_, inv,
    /* 0x78 - 0x7b*/ inv, inv, inv, inv,
    /* 0x7c - 0x7f*/ __ref_jl_short_, __ref_jge_short_, __ref_jle_short_, __ref_jg_short_,
    /* 0x80 - 0x83*/ __ref_group_1_b, __ref_group_1_v, nemu_trap, __ref_group_1_bv,
    /* 0x84 - 0x87*/ __ref_test_r2rm_b, __ref_test_r2rm_v, inv, inv,
    /* 0x88 - 0x8b*/ mov_r2rm_b, mov_r2rm_v, mov_rm2r_b, mov_rm2r_v,
    /* 0x8c - 0x8f*/ inv, __ref_lea, inv, inv,
    /* 0x90 - 0x93*/ nop, inv, inv, inv,
    /* 0x94 - 0x97*/ inv, inv, inv, inv,
    /* 0x98 - 0x9b*/ cbw_a_v, cltd, inv, inv,
    /* 0x9c - 0x9f*/ inv, inv, sahf, inv,
    /* 0xa0 - 0xa3*/ mov_o2a_b, mov_o2a_v, mov_a2o_b, mov_a2o_v,
    /* 0xa4 - 0xa7*/ movs_b, movs_v, inv, inv,
    /* 0xa8 - 0xab*/ inv, __ref_test_i2a_v, inv, inv,
    /* 0xac - 0xaf*/ inv, inv, inv, inv,
    /* 0xb0 - 0xb3*/ mov_i2r_b, mov_i2r_b, mov_i2r_b, mov_i2r_b,
    /* 0xb4 - 0xb7*/ mov_i2r_b, mov_i2r_b, mov_i2r_b, mov_i2r_b,
    /* 0xb8 - 0xbb*/ mov_i2r_v, mov_i2r_v, mov_i2r_v, mov_i2r_v,
    /* 0xbc - 0xbf*/ mov_i2r_v, mov_i2r_v, mov_i2r_v, mov_i2r_v,
    /* 0xc0 - 0xc3*/ group_2_b, group_2_v, ret, ret,
    /* 0xc4 - 0xc7*/ inv, inv, mov_i2rm_b, mov_i2rm_v,
    /* 0xc8 - 0xcb*/ inv, leave, inv, inv,
    /* 0xcc - 0xcf*/ inv, inv, inv, inv,
    /* 0xd0 - 0xd3*/ __ref_group_2_1b, __ref_group_2_1v, __ref_group_2_cb, __ref_group_2_cv,
    /* 0xd4 - 0xd7*/ inv, inv, inv, inv,
    /* 0xd8 - 0xdb*/ group_x87_d8, group_x87_d9, group_x87_da, group_x87_db,
    /* 0xdc - 0xdf*/ group_x87_dc, group_x87_dd, group_x87_de, group_x87_df,
    /* 0xe0 - 0xe3*/ inv, inv, inv, inv,
    /* 0xe4 - 0xe7*/ inv, inv, inv, inv,
    /* 0xe8 - 0xeb*/ call_i_near, __ref_jmp_near, inv, __ref_jmp_short,
    /* 0xec - 0xef*/ inv, inv, inv, inv,
    /* 0xf0 - 0xf3*/ inv, break_point, inv, __ref_rep_repe,
    /* 0xf4 - 0xf7*/ hlt, inv, __ref_group_3_b, __ref_group_3_v,
    /* 0xf8 - 0xfb*/ clc, inv, inv, inv,
    /* 0xfc - 0xff*/ __ref_cld, inv, inv, __ref_group_5_indirect,
};

/* 0x80 */
instr_func group_1_b_entry[8] =
    {inv, inv, inv, inv, inv, inv, inv, cmp_i2rm_b};

/* 0x81 */
instr_func group_1_v_entry[8] =
    {add_i2rm_v, inv, inv, inv, and_i2rm_v, sub_i2rm_v, inv, cmp_i2rm_v};

/* 0x83 */
instr_func group_1_bv_entry[8] =
    {add_i2rm_bv, inv, inv, inv, and_i2rm_bv, sub_i2rm_bv, inv, cmp_i2rm_bv};

/* 0xc0 */
instr_func group_2_b_entry[8] =
    {inv, inv, inv, inv, shl_i2rm_b, shr_i2rm_b, inv, sar_i2rm_b};

/* 0xc1 */
instr_func group_2_v_entry[8] =
    {inv, inv, inv, inv, shl_i2rm_bv, shr_i2rm_bv, inv, sar_i2rm_bv};

/* 0xd0 */
instr_func group_2_1b_entry[8] =
    {inv, inv, inv, inv, shl_rm_b, shr_rm_b, inv, sar_rm_b};

/* 0xd1 */
instr_func group_2_1v_entry[8] =
    {inv, inv, inv, inv, shl_rm_v, shr_rm_v, inv, sar_rm_v};

/* 0xd2 */
instr_func group_2_cb_entry[8] =
    {inv, inv, inv, inv, shl_c2rm_b, inv, shr_c2rm_b, sar_c2rm_b};

/* 0xd3 */
instr_func group_2_cv_entry[8] =
    {inv, inv, inv, inv, shl_c2rm_bv, inv, shr_c2rm_bv, sar_c2rm_bv};

/* 0xf6 */
instr_func group_3_b_entry[8] =
    {inv, inv, inv, inv, inv, inv, inv, inv};

/* 0xf7 */
instr_func group_3_v_entry[8] =
    {__ref_test_i2rm_v, inv, not_rm_v, inv, mul_rm2a_v, imul_rm2a_v, inv, idiv_rm2a_v};

/* 0xff */
instr_func group_5_indirect_entry[8] =
    {inc_rm_w, dec_rm_v, inv, inv, inv, inv, push_rm_v, inv};

instr_func group_7_entry[8] =
    {inv, inv, inv, inv, inv, inv, inv, inv};

/* 0xd8 */
instr_func group_x87_d8_entry[8] =
    {x87_fadds, x87_fmuls, inv, inv, x87_fsubs, inv, x87_fdivs, inv};

/* 0xd9 */
instr_func group_x87_d9_entry[8] =
    {x87_flds, x87_fxch, x87_fsts, x87_fstps, inv, x87_fldx, inv, x87_fnstcw};

/* 0xda */
instr_func group_x87_da_entry[8] =
    {inv, inv, inv, inv, inv, x87_fucompp, inv, inv};

/* 0xdb */
instr_func group_x87_db_entry[8] =
    {x87_fildl, inv, inv, x87_fistpl, inv, x87_fucomi, x87_fcomi, inv};

/* 0xdc */
instr_func group_x87_dc_entry[8] =
    {x87_faddlx, x87_fmullx, inv, inv, inv, inv, inv, inv};

/* 0xdd */
instr_func group_x87_dd_entry[8] =
    {x87_fldl, inv, x87_fstx, x87_fstpx, x87_fucom, x87_fucomp, inv, inv};

/* 0xde */
instr_func group_x87_de_entry[8] =
    {x87_faddx, inv, inv, inv, inv, inv, inv, inv};

/* 0xdf */
instr_func group_x87_df_entry[8] =
    {inv, inv, inv, inv, x87_fnstsw, x87_fucomip, x87_fcomip, inv};

instr_func opcode_2_byte_entry[256] = {
    /* 0x00 - 0x03*/ inv, group_7, inv, inv,
    /* 0x04 - 0x07*/ inv, inv, inv, inv,
    /* 0x08 - 0x0b*/ inv, inv, inv, inv,
    /* 0x0c - 0x0f*/ inv, inv, inv, inv,
    /* 0x10 - 0x13*/ inv, inv, inv, inv,
    /* 0x14 - 0x17*/ inv, inv, inv, inv,
    /* 0x18 - 0x1b*/ inv, inv, inv, inv,
    /* 0x1c - 0x1f*/ inv, inv, inv, inv,
    /* 0x20 - 0x23*/ inv, inv, inv, inv,
    /* 0x24 - 0x27*/ inv, inv, inv, inv,
    /* 0x28 - 0x2b*/ inv, inv, inv, inv,
    /* 0x2c - 0x2f*/ inv, inv, inv, inv,
    /* 0x30 - 0x33*/ inv, inv, inv, inv,
    /* 0x34 - 0x37*/ inv, inv, inv, inv,
    /* 0x38 - 0x3b*/ inv, inv, inv, inv,
    /* 0x3c - 0x3f*/ inv, inv, inv, inv,
    /* 0x40 - 0x43*/ inv, inv, inv, inv,
    /* 0x44 - 0x47*/ cmove_rm2r_v, cmovne_rm2r_v, inv, cmova_rm2r_v,
    /* 0x48 - 0x4b*/ cmovs_rm2r_v, cmovns_rm2r_v, inv, inv,
    /* 0x4c - 0x4f*/ inv, cmovge_rm2r_v, inv, inv,
    /* 0x50 - 0x53*/ inv, inv, inv, inv,
    /* 0x54 - 0x57*/ inv, inv, inv, inv,
    /* 0x58 - 0x5b*/ inv, inv, inv, inv,
    /* 0x5c - 0x5f*/ inv, inv, inv, inv,
    /* 0x60 - 0x63*/ inv, inv, inv, inv,
    /* 0x64 - 0x67*/ inv, inv, inv, inv,
    /* 0x68 - 0x6b*/ inv, inv, inv, inv,
    /* 0x6c - 0x6f*/ inv, inv, inv, inv,
    /* 0x70 - 0x73*/ inv, inv, inv, inv,
    /* 0x74 - 0x77*/ inv, inv, inv, inv,
    /* 0x78 - 0x7b*/ inv, inv, inv, inv,
    /* 0x7c - 0x7f*/ inv, inv, inv, inv,
    /* 0x80 - 0x83*/ inv, inv, inv, inv,
    /* 0x84 - 0x87*/ inv, inv, jna_near, inv,
    /* 0x88 - 0x8b*/ inv, inv, inv, inv,
    /* 0x8c - 0x8f*/ jl_near, inv, jle_near, inv,
    /* 0x90 - 0x93*/ inv, inv, inv, inv,
    /* 0x94 - 0x97*/ inv, __ref_setne_b, inv, inv,
    /* 0x98 - 0x9b*/ inv, inv, inv, inv,
    /* 0x9c - 0x9f*/ inv, inv, inv, inv,
    /* 0xa0 - 0xa3*/ inv, inv, inv, bt_r2rm_v,
    /* 0xa4 - 0xa7*/ inv, inv, inv, inv,
    /* 0xa8 - 0xab*/ inv, inv, inv, inv,
    /* 0xac - 0xaf*/ inv, inv, inv, imul_rm2r_v,
    /* 0xb0 - 0xb3*/ inv, inv, inv, inv,
    /* 0xb4 - 0xb7*/ inv, inv, mov_zrm82r_v, mov_zrm162r_l,
    /* 0xb8 - 0xbb*/ inv, inv, inv, inv,
    /* 0xbc - 0xbf*/ inv, inv, mov_srm82r_v, mov_srm162r_l,
    /* 0xc0 - 0xc3*/ inv, inv, inv, inv,
    /* 0xc4 - 0xc7*/ inv, inv, inv, inv,
    /* 0xc8 - 0xcb*/ inv, inv, inv, inv,
    /* 0xcc - 0xcf*/ inv, inv, inv, inv,
    /* 0xd0 - 0xd3*/ inv, inv, inv, inv,
    /* 0xd4 - 0xd7*/ inv, inv, inv, inv,
    /* 0xd8 - 0xdb*/ inv, inv, inv, inv,
    /* 0xdc - 0xdf*/ inv, inv, inv, inv,
    /* 0xe0 - 0xe3*/ inv, inv, inv, inv,
    /* 0xe4 - 0xe7*/ inv, inv, inv, inv,
    /* 0xe8 - 0xeb*/ inv, inv, inv, inv,
    /* 0xec - 0xef*/ inv, inv, inv, inv,
    /* 0xf0 - 0xf3*/ inv, inv, inv, inv,
    /* 0xf4 - 0xf7*/ inv, inv, inv, inv,
    /* 0xf8 - 0xfb*/ inv, inv, inv, inv,
    /* 0xfc - 0xff*/ inv, inv, inv, inv,
};
