#include "../../include/cpu/cpu.h"
#include "../../include/cpu/alu.h"
#include <stdio.h>
extern CPU_STATE cpu;



void set_PF(uint32_t res) {
    int cnt1 = 8, cnt2 = 0;
    uint8_t temp = sign_ext(res, 8);
    while (cnt1--) {
        uint8_t temp2 = temp << cnt1;
        temp2 = temp2 >> 7;
        if (temp2) {
            cnt2++;
        }
    }
    cpu.eflags.PF = cnt2 % 2 ? 0 : 1;
}

void set_ZF(uint32_t res, size_t data_size) {
    res = res & (0xFFFFFFFF >> (32 - data_size));
    cpu.eflags.ZF = (res == 0);
}
	
void set_SF(uint32_t res, size_t data_size) {
    res = sign_ext(res & (0xFFFFFFFF >> (32 - data_size)), data_size);
    cpu.eflags.SF = sign(res);
}

void set_OF_add(uint32_t res, uint32_t src, uint32_t dest, size_t data_size) {
    res = sign_ext(res & (0xFFFFFFFF >> (32 - data_size)), data_size);
    src = sign_ext(src & (0xFFFFFFFF >> (32 - data_size)), data_size);
    dest = sign_ext(dest & (0xFFFFFFFF >> (32 - data_size)), data_size);
    if (sign(src) != sign(dest)) {
        cpu.eflags.OF = 0;
    }
    else {
        cpu.eflags.OF = sign(res) != sign(src) ?  1 : 0;
    }
}

void set_OF_sub(uint32_t res, uint32_t src, uint32_t dest, size_t data_size) {
    res = sign_ext(res & (0xFFFFFFFF >> (32 - data_size)), data_size);
    src = sign_ext(src & (0xFFFFFFFF >> (32 - data_size)), data_size);
    dest = sign_ext(dest & (0xFFFFFFFF >> (32 - data_size)), data_size);
    if (sign(src) == sign(dest)) {
        cpu.eflags.OF = 0;
    }
    else {
        cpu.eflags.OF = sign(res) != sign(dest) ?  1 : 0;
    }
}

void set_OF_sbb(uint32_t res, uint32_t src, uint32_t dest, size_t data_size) {
    res = sign_ext(res & (0xFFFFFFFF >> (32 - data_size)), data_size);
    src = sign_ext(src & (0xFFFFFFFF >> (32 - data_size)), data_size);
    dest = sign_ext(dest & (0xFFFFFFFF >> (32 - data_size)), data_size);
    if (sign(src) == sign(dest)) {
        cpu.eflags.OF = 0;
    }
    else {
        cpu.eflags.OF = sign(res) != sign(dest) ?  1 : 0;
    }
}

void set_CF_add(uint32_t res, uint32_t src, size_t data_size) {
    res = sign_ext(res & (0xFFFFFFFF >> (32 - data_size)), data_size);
    src = sign_ext(src & (0xFFFFFFFF >> (32 - data_size)), data_size);
    cpu.eflags.CF = res < src;
}

void set_CF_adc(uint32_t res, uint32_t src, size_t data_size) {
    res = sign_ext(res & (0xFFFFFFFF >> (32 - data_size)), data_size);
    src = sign_ext(src & (0xFFFFFFFF >> (32 - data_size)), data_size);
    cpu.eflags.CF = (cpu.eflags.CF == 1) ? res <= src : res < src;
}

void set_CF_sub(uint32_t res, uint32_t src, size_t data_size) {
    res = sign_ext(res & (0xFFFFFFFF >> (32 - data_size)), data_size);
    src = sign_ext(src & (0xFFFFFFFF >> (32 - data_size)), data_size);
    cpu.eflags.CF = (res > src) ? 1 : 0;
}

void set_CF_sbb(uint32_t res, uint32_t src, size_t data_size) {
    res = sign_ext(res & (0xFFFFFFFF >> (32 - data_size)), data_size);
    src = sign_ext(src & (0xFFFFFFFF >> (32 - data_size)), data_size);
    cpu.eflags.CF = (cpu.eflags.CF == 1) ? res >= src : res > src;
}

void set_CF_mvl(uint32_t res, uint32_t src, uint32_t dest, size_t data_size) {
    if (src == 0) {
        cpu.eflags.CF = 0;
        return;
    }
    dest = sign_ext(dest << (src - 1), data_size);
    cpu.eflags.CF = sign(dest);
}

void set_CF_mvr(uint32_t res, uint32_t src, uint32_t dest, size_t data_size) {
    if (src == 0) {
        cpu.eflags.CF = 0;
        return;
    }
    dest = (dest >> (src - 1)) & 0x00000001;
    cpu.eflags.CF = (dest == 1) ? 1 : 0;
}


// ================= my personal define above =================

// ================= real code below ====================
uint32_t alu_add(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_add(src, dest, data_size);
#else
    uint32_t res = src + dest;
    set_CF_add(res, src, data_size);   // 设置标志位
	set_PF(res);                       // 偶数个1时，置1 
	set_ZF(res, data_size);
	set_SF(res, data_size);
	set_OF_add(res, src, dest, data_size);
    return res & (0xFFFFFFFF >> (32 - data_size)); // 高位清零
#endif
}

uint32_t alu_adc(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_adc(src, dest, data_size);
#else
    uint32_t res = src + dest + cpu.eflags.CF;
    set_CF_adc(res, src, data_size);   // 设置标志位
    set_PF(res);                       // 偶数个1时，置1
    set_ZF(res, data_size);
    set_SF(res, data_size);
    set_OF_add(res, src, dest, data_size);
    return res & (0xFFFFFFFF >> (32 - data_size));
#endif
}

uint32_t alu_sub(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sub(src, dest, data_size);
#else
    uint32_t res = dest - src;
    // printf("0:res = 0x%x\n", res);
    set_CF_sub(res, dest, data_size);   // 设置标志位
    // printf("1:res = 0x%x\n", res);
	set_PF(res);                       // 偶数个1时，置1 
	set_ZF(res, data_size);
	set_SF(res, data_size);
	set_OF_sub(res, src, dest, data_size);
    return res & (0xFFFFFFFF >> (32 - data_size)); // 高位清零
#endif
}


uint32_t alu_sbb(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sbb(src, dest, data_size);
#else
    uint32_t res = dest - src - cpu.eflags.CF;
    // printf("0:res = 0x%x\n", res);
    set_CF_sbb(res, dest, data_size);   // 设置标志位
    // printf("1:res = 0x%x\n", res);
	set_PF(res);                       // 偶数个1时，置1 
	set_ZF(res, data_size);
	set_SF(res, data_size);
	set_OF_sub(res, src, dest, data_size);
    return res & (0xFFFFFFFF >> (32 - data_size)); // 高位清零
#endif
}

uint64_t alu_mul(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_mul(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

int64_t alu_imul(int32_t src, int32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_imul(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

// need to implement alu_mod before testing
uint32_t alu_div(uint64_t src, uint64_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_div(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

// need to implement alu_imod before testing
int32_t alu_idiv(int64_t src, int64_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_idiv(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

uint32_t alu_mod(uint64_t src, uint64_t dest)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_mod(src, dest);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

int32_t alu_imod(int64_t src, int64_t dest)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_imod(src, dest);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

uint32_t alu_and(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_and(src, dest, data_size);
#else
    uint32_t res = dest & src;
    set_PF(res);                       // 偶数个1时，置1 
	set_ZF(res, data_size);
	set_SF(res, data_size);
	return res & (0xFFFFFFFF >> (32 - data_size));
#endif
}

uint32_t alu_xor(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_xor(src, dest, data_size);
#else
    uint32_t res = dest ^ src;
    set_PF(res);                       // 偶数个1时，置1 
	set_ZF(res, data_size);
	set_SF(res, data_size);
	return res & (0xFFFFFFFF >> (32 - data_size));
#endif
}

uint32_t alu_or(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_or(src, dest, data_size);
#else
    uint32_t res = dest | src;
    set_PF(res);                       // 偶数个1时，置1 
	set_ZF(res, data_size);
	set_SF(res, data_size);
	return res & (0xFFFFFFFF >> (32 - data_size));
#endif
}

uint32_t alu_shl(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_shl(src, dest, data_size);
#else
    dest = dest & (0xFFFFFFFF >> (32 - data_size));
    uint32_t res = dest << src;
    set_CF_mvl(res, src, dest, data_size);
    set_PF(res);                       // 偶数个1时，置1 
	set_ZF(res, data_size);
	set_SF(res, data_size);
    return res & (0xFFFFFFFF >> (32 - data_size));
#endif
}

uint32_t alu_shr(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_shr(src, dest, data_size);
#else
    dest = dest & (0xFFFFFFFF >> (32 - data_size));
    uint32_t res = dest >> src;
    set_CF_mvr(res, src, dest, data_size);
    set_PF(res);                       // 偶数个1时，置1 
	set_ZF(res, data_size);
	set_SF(res, data_size);
    return res & (0xFFFFFFFF >> (32 - data_size));
#endif
}

uint32_t alu_sar(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sar(src, dest, data_size);
#else

    int32_t temp = dest << (32 - data_size);
    temp = temp >> src;
    uint32_t temp2 = (uint32_t)temp >> (32 - data_size);
    printf("src = 0x%x\n", src);
    printf("dest = 0x%x\n", dest);
    printf("data_size = 0x%x\n", data_size);
    printf("temp = 0x%x\n", temp);
    printf("temp2 = 0x%x\n", temp2);
    printf("0: res = 0x%x\n", res);
    set_CF_mvr(res, src, dest, data_size);
    set_PF(res);                       // 偶数个1时，置1 
	set_ZF(res, data_size);
	set_SF(res, data_size);
	printf("1: res = 0x%x\n", res);
    return temp2;
#endif
}

uint32_t alu_sal(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sal(src, dest, data_size);
#else
    return alu_shl(src, dest, data_size);
#endif
}
