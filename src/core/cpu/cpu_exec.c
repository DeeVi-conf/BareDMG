// src/core/cpu/cpu_exec.c
#include <core/cpu/cpu.h>
#include <core/cpu/cpu_exec.h>
#include <core/bus.h>
#include <gbemu.h>
#include <core/utils.h>

u8 instr_nop(CPU *cpu) {
    (void)cpu;
    return 0;
}

// ============================================================================
// 8-bit Load Instructions
// ============================================================================

// Immediate loads
u8 instr_ld_b_n(CPU *cpu) {
    cpu->regs.b = mmu_read(cpu->gb, cpu->pc++);
    return 0;
}

u8 instr_ld_c_n(CPU *cpu) {
    cpu->regs.c = mmu_read(cpu->gb, cpu->pc++);
    return 0;
}

u8 instr_ld_d_n(CPU *cpu) {
    cpu->regs.d = mmu_read(cpu->gb, cpu->pc++);
    return 0;
}

u8 instr_ld_e_n(CPU *cpu) {
    cpu->regs.e = mmu_read(cpu->gb, cpu->pc++);
    return 0;
}

u8 instr_ld_h_n(CPU *cpu) {
    cpu->regs.h = mmu_read(cpu->gb, cpu->pc++);
    return 0;
}

u8 instr_ld_l_n(CPU *cpu) {
    cpu->regs.l = mmu_read(cpu->gb, cpu->pc++);
    return 0;
}

u8 instr_ld_a_n(CPU *cpu) {
    cpu->regs.a = mmu_read(cpu->gb, cpu->pc++);
    return 0;
}

// Register <-> Register
u8 instr_ld_b_b(CPU *cpu) {
    cpu->regs.b = cpu->regs.b;
    return 0;
}

u8 instr_ld_b_c(CPU *cpu) {
    cpu->regs.b = cpu->regs.c;
    return 0;
}

u8 instr_ld_b_d(CPU *cpu) {
    cpu->regs.b = cpu->regs.d;
    return 0;
}

u8 instr_ld_b_e(CPU *cpu) {
    cpu->regs.b = cpu->regs.e;
    return 0;
}

u8 instr_ld_b_h(CPU *cpu) {
    cpu->regs.b = cpu->regs.h;
    return 0;
}

u8 instr_ld_b_l(CPU *cpu) {
    cpu->regs.b = cpu->regs.l;
    return 0;
}

u8 instr_ld_b_a(CPU *cpu) {
    cpu->regs.b = cpu->regs.a;
    return 0;
}

u8 instr_ld_c_b(CPU *cpu) {
    cpu->regs.c = cpu->regs.b;
    return 0;
}

u8 instr_ld_c_c(CPU *cpu) {
    cpu->regs.c = cpu->regs.c;
    return 0;
}

u8 instr_ld_c_d(CPU *cpu) {
    cpu->regs.c = cpu->regs.d;
    return 0;
}

u8 instr_ld_c_e(CPU *cpu) {
    cpu->regs.c = cpu->regs.e;
    return 0;
}

u8 instr_ld_c_h(CPU *cpu) {
    cpu->regs.c = cpu->regs.h;
    return 0;
}

u8 instr_ld_c_l(CPU *cpu) {
    cpu->regs.c = cpu->regs.l;
    return 0;
}

u8 instr_ld_c_a(CPU *cpu) {
    cpu->regs.c = cpu->regs.a;
    return 0;
}

u8 instr_ld_d_b(CPU *cpu) {
    cpu->regs.d = cpu->regs.b;
    return 0;
}

u8 instr_ld_d_c(CPU *cpu) {
    cpu->regs.d = cpu->regs.c;
    return 0;
}

u8 instr_ld_d_d(CPU *cpu) {
    cpu->regs.d = cpu->regs.d;
    return 0;
}

u8 instr_ld_d_e(CPU *cpu) {
    cpu->regs.d = cpu->regs.e;
    return 0;
}

u8 instr_ld_d_h(CPU *cpu) {
    cpu->regs.d = cpu->regs.h;
    return 0;
}

u8 instr_ld_d_l(CPU *cpu) {
    cpu->regs.d = cpu->regs.l;
    return 0;
}

u8 instr_ld_d_a(CPU *cpu) {
    cpu->regs.d = cpu->regs.a;
    return 0;
}

u8 instr_ld_e_b(CPU *cpu) {
    cpu->regs.e = cpu->regs.b;
    return 0;
}

u8 instr_ld_e_c(CPU *cpu) {
    cpu->regs.e = cpu->regs.c;
    return 0;
}

u8 instr_ld_e_d(CPU *cpu) {
    cpu->regs.e = cpu->regs.d;
    return 0;
}

u8 instr_ld_e_e(CPU *cpu) {
    cpu->regs.e = cpu->regs.e;
    return 0;
}

u8 instr_ld_e_h(CPU *cpu) {
    cpu->regs.e = cpu->regs.h;
    return 0;
}

u8 instr_ld_e_l(CPU *cpu) {
    cpu->regs.e = cpu->regs.l;
    return 0;
}

u8 instr_ld_e_a(CPU *cpu) {
    cpu->regs.e = cpu->regs.a;
    return 0;
}

u8 instr_ld_h_b(CPU *cpu) {
    cpu->regs.h = cpu->regs.b;
    return 0;
}

u8 instr_ld_h_c(CPU *cpu) {
    cpu->regs.h = cpu->regs.c;
    return 0;
}

u8 instr_ld_h_d(CPU *cpu) {
    cpu->regs.h = cpu->regs.d;
    return 0;
}

u8 instr_ld_h_e(CPU *cpu) {
    cpu->regs.h = cpu->regs.e;
    return 0;
}

u8 instr_ld_h_h(CPU *cpu) {
    cpu->regs.h = cpu->regs.h;
    return 0;
}

u8 instr_ld_h_l(CPU *cpu) {
    cpu->regs.h = cpu->regs.l;
    return 0;
}

u8 instr_ld_h_a(CPU *cpu) {
    cpu->regs.h = cpu->regs.a;
    return 0;
}

u8 instr_ld_l_b(CPU *cpu) {
    cpu->regs.l = cpu->regs.b;
    return 0;
}

u8 instr_ld_l_c(CPU *cpu) {
    cpu->regs.l = cpu->regs.c;
    return 0;
}

u8 instr_ld_l_d(CPU *cpu) {
    cpu->regs.l = cpu->regs.d;
    return 0;
}

u8 instr_ld_l_e(CPU *cpu) {
    cpu->regs.l = cpu->regs.e;
    return 0;
}

u8 instr_ld_l_h(CPU *cpu) {
    cpu->regs.l = cpu->regs.h;
    return 0;
}

u8 instr_ld_l_l(CPU *cpu) {
    cpu->regs.l = cpu->regs.l;
    return 0;
}

u8 instr_ld_l_a(CPU *cpu) {
    cpu->regs.l = cpu->regs.a;
    return 0;
}

u8 instr_ld_a_b(CPU *cpu) {
    cpu->regs.a = cpu->regs.b;
    return 0;
}

u8 instr_ld_a_c(CPU *cpu) {
    cpu->regs.a = cpu->regs.c;
    return 0;
}

u8 instr_ld_a_d(CPU *cpu) {
    cpu->regs.a = cpu->regs.d;
    return 0;
}

u8 instr_ld_a_e(CPU *cpu) {
    cpu->regs.a = cpu->regs.e;
    return 0;
}

u8 instr_ld_a_h(CPU *cpu) {
    cpu->regs.a = cpu->regs.h;
    return 0;
}

u8 instr_ld_a_l(CPU *cpu) {
    cpu->regs.a = cpu->regs.l;
    return 0;
}

u8 instr_ld_a_a(CPU *cpu) {
    cpu->regs.a = cpu->regs.a;
    return 0;
}

// =================================
// Memory via HL
// =================================

// register <- [hl]
u8 instr_ld_b_mem_hl(CPU *cpu) {
    u16 addr    = cpu_read_hl(cpu);
    cpu->regs.b = mmu_read(cpu->gb, addr);
    return 0;
}

u8 instr_ld_c_mem_hl(CPU *cpu) {
    u16 addr    = cpu_read_hl(cpu);
    cpu->regs.c = mmu_read(cpu->gb, addr);
    return 0;
}

u8 instr_ld_d_mem_hl(CPU *cpu) {
    u16 addr    = cpu_read_hl(cpu);
    cpu->regs.d = mmu_read(cpu->gb, addr);
    return 0;
}

u8 instr_ld_e_mem_hl(CPU *cpu) {
    u16 addr    = cpu_read_hl(cpu);
    cpu->regs.e = mmu_read(cpu->gb, addr);
    return 0;
}

u8 instr_ld_h_mem_hl(CPU *cpu) {
    u16 addr    = cpu_read_hl(cpu);
    cpu->regs.h = mmu_read(cpu->gb, addr);
    return 0;
}

u8 instr_ld_l_mem_hl(CPU *cpu) {
    u16 addr    = cpu_read_hl(cpu);
    cpu->regs.l = mmu_read(cpu->gb, addr);
    return 0;
}

u8 instr_ld_a_mem_hl(CPU *cpu) {
    u16 addr    = cpu_read_hl(cpu);
    cpu->regs.a = mmu_read(cpu->gb, addr);
    return 0;
}

// [hl] <- register
u8 instr_ld_mem_hl_b(CPU *cpu) {
    u16 addr = cpu_read_hl(cpu);
    mmu_write(cpu->gb, addr, cpu->regs.b);
    return 0;
}

u8 instr_ld_mem_hl_c(CPU *cpu) {
    u16 addr = cpu_read_hl(cpu);
    mmu_write(cpu->gb, addr, cpu->regs.c);
    return 0;
}

u8 instr_ld_mem_hl_d(CPU *cpu) {
    u16 addr = cpu_read_hl(cpu);
    mmu_write(cpu->gb, addr, cpu->regs.d);
    return 0;
}

u8 instr_ld_mem_hl_e(CPU *cpu) {
    u16 addr = cpu_read_hl(cpu);
    mmu_write(cpu->gb, addr, cpu->regs.e);
    return 0;
}

u8 instr_ld_mem_hl_h(CPU *cpu) {
    u16 addr = cpu_read_hl(cpu);
    mmu_write(cpu->gb, addr, cpu->regs.h);
    return 0;
}

u8 instr_ld_mem_hl_l(CPU *cpu) {
    u16 addr = cpu_read_hl(cpu);
    mmu_write(cpu->gb, addr, cpu->regs.l);
    return 0;
}

u8 instr_ld_mem_hl_a(CPU *cpu) {
    u16 addr = cpu_read_hl(cpu);
    mmu_write(cpu->gb, addr, cpu->regs.a);
    return 0;
}

// [hl] <- immediate (n)
u8 instr_ld_mem_hl_n(CPU *cpu) {
    u16 addr  = cpu_read_hl(cpu);
    u8  value = mmu_read(cpu->gb, cpu->pc++); // Read immediate value
    mmu_write(cpu->gb, addr, value);
    return 0;
}

// ============================================================================
// 16-bit Load Instructions
// ============================================================================

u8 instr_ld_bc_nn(CPU *cpu) {
    u8 lo = mmu_read(cpu->gb, cpu->pc++);
    u8 hi = mmu_read(cpu->gb, cpu->pc++);
    cpu_write_bc(cpu, MAKE_U16(hi, lo));
    return 0;
}

u8 instr_ld_de_nn(CPU *cpu) {
    u8 lo = mmu_read(cpu->gb, cpu->pc++);
    u8 hi = mmu_read(cpu->gb, cpu->pc++);
    cpu_write_de(cpu, MAKE_U16(hi, lo));
    return 0;
}

u8 instr_ld_hl_nn(CPU *cpu) {
    u8 lo = mmu_read(cpu->gb, cpu->pc++);
    u8 hi = mmu_read(cpu->gb, cpu->pc++);
    cpu_write_hl(cpu, MAKE_U16(hi, lo));
    return 0;
}

u8 instr_ld_sp_nn(CPU *cpu) {
    u8 lo   = mmu_read(cpu->gb, cpu->pc++);
    u8 hi   = mmu_read(cpu->gb, cpu->pc++);
    cpu->sp = MAKE_U16(hi, lo);
    return 0;
}

// ============================================================================
// 8-bit Arithmetic & Logic
// https://rgbds.gbdev.io/docs/v1.0.1/gbz80.7#8-bit_arithmetic_instructions
// ============================================================================

// INC r8
// Increment the value in register r8 by 1.
// Flags:
// Z - Set if reselt is zero
// N - 0
// H - Set if overflow from 3rd bit
// ----------------------------------------------
u8 instr_inc_a(CPU *cpu) {
    u8   result    = cpu->regs.a + 1;

    // Preserve carry flag
    bool old_carry = cpu_get_flag(cpu, FLAG_CARRY);

    cpu->regs.f    = 0;

    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;     // Set Z if result = 0
    if ((cpu->regs.a & 0x0F) == 0x0F) // Set H if lower nibble overlfows
        cpu->regs.f |= FLAG_HF_CARRY;
    if (old_carry)
        cpu->regs.f |= FLAG_CARRY; // Restore C (if it was set)

    cpu->regs.a = result;
    return 0;
}

u8 instr_inc_b(CPU *cpu) {
    u8   result    = cpu->regs.b + 1;

    bool old_carry = cpu_get_flag(cpu, FLAG_CARRY);

    cpu->regs.f    = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if ((cpu->regs.b & 0x0F) == 0x0F)
        cpu->regs.f |= FLAG_HF_CARRY;
    if (old_carry)
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.b = result;
    return 0;
}

u8 instr_dec_a(CPU *cpu) {
    u8   result    = cpu->regs.a - 1;

    bool old_carry = cpu_get_flag(cpu, FLAG_CARRY);

    cpu->regs.f    = FLAG_SUBT;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if ((cpu->regs.a & 0x0F) == 0)
        cpu->regs.f |= FLAG_HF_CARRY;
    if (old_carry)
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

u8 instr_dec_b(CPU *cpu) {
    u8   result    = cpu->regs.b - 1;

    bool old_carry = cpu_get_flag(cpu, FLAG_CARRY);

    cpu->regs.f    = FLAG_SUBT;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if ((cpu->regs.b & 0x0F) == 0)
        cpu->regs.f |= FLAG_HF_CARRY;
    if (old_carry)
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.b = result;
    return 0;
}

u8 instr_add_a_b(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 b        = cpu->regs.b;
    u8 result   = a + b;

    cpu->regs.f = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_add(a, b))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_add(a, b))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

u8 instr_add_a_c(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 c        = cpu->regs.c;
    u8 result   = a + c;

    cpu->regs.f = 0;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_add(a, c))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_add(a, c))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

u8 instr_sub_a_b(CPU *cpu) {
    u8 a        = cpu->regs.a;
    u8 b        = cpu->regs.b;
    u8 result   = a - b;

    cpu->regs.f = FLAG_SUBT;
    if (result == 0)
        cpu->regs.f |= FLAG_ZERO;
    if (check_half_carry_sub(a, b))
        cpu->regs.f |= FLAG_HF_CARRY;
    if (check_carry_sub(a, b))
        cpu->regs.f |= FLAG_CARRY;

    cpu->regs.a = result;
    return 0;
}

// ============================================================================
// Control Flow
// ============================================================================

u8 instr_jp_nn(CPU *cpu) {
    u8 lo   = mmu_read(cpu->gb, cpu->pc++);
    u8 hi   = mmu_read(cpu->gb, cpu->pc++);
    cpu->pc = MAKE_U16(hi, lo);
    return 0;
}

u8 instr_jr_n(CPU *cpu) {
    i8 offset = (i8)mmu_read(cpu->gb, cpu->pc++);
    cpu->pc += offset;
    return 0;
}
