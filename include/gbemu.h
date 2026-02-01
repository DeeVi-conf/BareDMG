// include/gbemu.h
#ifndef GBEMU_H
#define GBEMU_H

#include <core/cpu/cpu.h>
#include <core/cartridge.h>
#include <core/utils.h>

// ---------------------------------------------
// Hardware Registers
// https://gbdev.io/pandocs/Hardware_Reg_List.html
// ---------------------------------------------
typedef struct {
    // Joypad (0xFF00)
    u8 joyp; // 0xFF00 - Joypad

    // Serial Communication
    u8 sb; // 0xFF01 - Serial Data
    u8 sc; // 0xFF02 - Serial Control

    // Timer & Divider (0xFF04 - 0xFF07)
    u8 div;  // 0xFF04 - Divider (auto-increments @ 16384 Hz)
    u8 tima; // 0xFF05 - Timer Counter
    u8 tma;  // 0xFF06 - Timer Modulo
    u8 tac;  // 0xFF07 - Timer Control

    // Interrupt Flags (0xFF0F, 0xFFFF handled separately)
    u8 if_reg; // 0xFF0F - Interrupt Flags (VBlank, LCD, Timer, Serial, Joypad)

    // Sound (0xFF10-0xFF26)
    // NOTE: Stubbed
    u8 sound[0x17]; // Sound registers (stubbed for now)

    // LCD (0xFF40 - 0xFF48)
    u8 lcdc; // 0xFF40 - LCD Control
    u8 stat; // 0xFF41 - LCD Status
    u8 scy;  // 0xFF42 - Scroll Y
    u8 scx;  // 0xFF43 - Scroll X
    u8 ly;   // 0xFF44 - LCD Y-Coordinate (read-only, written by PPU)
    u8 lyc;  // 0xFF45 - LY Compare
    u8 dma;  // 0xFF46 - DMA Transfer
    u8 bgp;  // 0xFF47 - BG Palette Data
    u8 obp0; // 0xFF48 - Object Palette
    u8 obp1; // 0xFF49 - Object Palette 1
    u8 wy;   // 0xFF4A - Window Y Position
    u8 wx;   // 0xFF4B - Window X Position

    // Boot ROM disable (0xFF50)
    u8 boot; // 0xFF50 - Boot ROM disable flag
} IORegisters;

// ---------------------------------------------
// Main GameBoy Struct
// ---------------------------------------------
typedef struct GameBoy {
    // Components will be added as they are implemented.
    CPU         cpu;
    Cartridge   cart;

    // Memory
    // https://gbdev.io/pandocs/Memory_Map.html#memory-map
    u8          vram[0x2000]; // Video RAM - 8 KB (0x8000 - 0x9FFF)
    u8          wram[0x2000]; // Work RAM - 8 KB (0xC000 - 0xDFFF)
    u8          oam[0xA0];    // Object Attribute Memory - 160 B (0xFE00 - 0xFE9E)
    u8          hram[0x7F];   // High RAM - 127 B (0xFF88 - 0xFFFE)

    // I/O Registers
    IORegisters io;
    u8          ie_register; // Interrupt Enable Register (0xFFFF)

    // System state
    u64         cycles;
    bool        running;
} GameBoy;

// ---------------------------------------------
// Emulator Functions
// ---------------------------------------------
void gb_init(GameBoy *gb);
void gb_load_rom(GameBoy *gb, const char *path);
void gb_step(GameBoy *gb);
void gb_run_frame(GameBoy *gb);

// ---------------------------------------------
// I/O Handlers (called by MMU)
// ---------------------------------------------
u8   io_read(GameBoy *gb, u16 addr);
void io_write(GameBoy *gb, u16 addr, u8 value);

#endif // !GBEMU_H
