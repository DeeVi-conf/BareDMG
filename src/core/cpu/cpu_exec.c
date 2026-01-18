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
