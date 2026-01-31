#include <core/utils.h>
#include <gbemu.h>
#include <stdio.h>

/*
Memory Map:
https://gbdev.io/pandocs/Memory_Map.html#memory-map

0x0000 - 0x00FF : Boot ROM (disabled after boot)
0x0100 - 0x3FFF : ROM Bank 0 (fixed, from cartridge)
0x4000 - 0x7FFF : ROM Bank N (switchable via MBC)

0x8000 - 0x9FFF : Video RAM (VRAM) - 8 KB
0xA000 - 0xBFFF : External RAM (on cartridge, if present)
0xC000 - 0xCFFF : Work RAM Bank 0 (WRAM) - 4 KB
0xD000 - 0xDFFF : Work RAM Bank 1 (WRAM) - 4 KB (in CGB mode, switchange bank 1-7)
0xE000 - 0xFDFF : Echo RAM (mirror of 0xC000-0xDDFF)
0xFE00 - 0xFE9F : Object Attribute Memory (OAM) - Sprite data
0xFEA0 - 0xFEFF : Unusable (reads as 0x00)

0xFF00 - 0xFF7F : I/O Registers (hardware control)
0xFF80 - 0xFFFE : High RAM (HRAM) - 127 bytes
0xFFFF          : Interrupt Enable Register (IE)
*/

// Read one byte from memory
u8 mmu_read(GameBoy *gb, u16 addr) {
    // ---------------------------
    // ROM Bank 0 (0x0000 - 0x3FFF) - Fixed
    // ---------------------------
    if (addr < 0x4000) {
        if (addr < gb->cart.rom_size)
            return gb->cart.rom[addr];
        return 0xFF; // Open bus
    }

    // ---------------------------
    // ROM Bank N (0x4000 - 0x7FFF) - Switchable
    // ---------------------------
    if (addr < 0x8000) {
        // For now, just read from ROM directly
        // TODO: MBC will handle bank switching
        if (addr < gb->cart.rom_size)
            return gb->cart.rom[addr];
        return 0xFF;
    }

    // ---------------------------
    // VRAM (0x8000 - 0x9FFF) - 8 KB
    // ---------------------------
    if (addr < 0xA000) {
        // TODO: Implement when the PPU is ready
        // For now, just return from VRAM array
        return gb->vram[addr - 0x8000];
    }

    // ---------------------------
    // External RAM (0xA000 - 0xBFFF) - Cartridge RAM
    // ---------------------------
    if (addr < 0xC000) {
        // TODO: Implement with MBC (bank switching, enalbe/disable)
        // For now, direct access if RAM exists
        u16 ram_addr = addr - 0xA000;
        if (ram_addr < gb->cart.ram_size)
            return gb->cart.ram[ram_addr];
        return 0xFF;
    }

    // ---------------------------
    // Work RAM (0xC000 - 0xDFFF) - Cartridge RAM
    // ---------------------------
    if (addr < 0xE000) {
        return gb->wram[addr - 0xC000];
    }

    // ---------------------------
    // Echo RAM (0xE000 - 0xFDFF) - Mirror of WRAM
    // ---------------------------
    if (addr < 0xFE00) {
        return gb->wram[addr - 0xE000];
    }

    // ---------------------------
    // OAM (0xFE00 - 0xFE9F) - Sprite Attribute Table
    // ---------------------------
    if (addr < 0xFEA0) {
        // TODO: Implement when PPU is ready
        return gb->oam[addr - 0xFE00];
    }

    // ---------------------------
    // Un-usable (0xFEA0 - 0xFEFF)
    // ---------------------------
    if (addr < 0xFF00) {
        // Writes ignored
        return 0x00;
    }

    // ---------------------------
    // I/O Registers 0xFF00 - 0xFF7F
    // ---------------------------
    if (addr < 0xFF80) {
        return io_read(gb, addr);
    }

    // ---------------------------
    // HRAM 0xFF80 - 0xFFFE 127 bytes
    // ---------------------------
    if (addr < 0xFFFF) {
        return gb->hram[addr - 0xFF80];
    }

    // ---------------------------
    // Interrupt Enable (0xFFFF)
    // ---------------------------
    if (addr == 0xFFFF) {
        return gb->ie_register;
    }

    // Ideally, control must never reach here
    return 0xFF; // Open Bus
}

// Write one Byte to memory
void mmu_write(GameBoy *gb, u16 addr, u8 value) {
    // ---------------------------
    // ROM (0x0000 - 0x7FFF) - MBC Control
    // ---------------------------
    if (addr < 0x8000) {
        // TODO: Implement when MBC is ready
        // Writes to ROM control MBC (bank switching, RAM enable, etc)
        // Ignore writes to ROM for now
        return;
    }

    // ---------------------------
    // VRAM (0x8000 - 0x9FFF) - 8 KB
    // ---------------------------
    if (addr < 0xA000) {
        // TODO: Check if VRAM is accessible (not during PPU mode 3)
        gb->vram[addr - 0x8000] = value;
        return;
    }

    // ---------------------------
    // External RAM (0xA000 - 0xBFFF) - Cartridge RAM
    // ---------------------------
    if (addr < 0xC000) {
        // TODO: Implement with MBC (check if RAM is enabled)
        u16 ram_addr = addr - 0xA000;
        if (ram_addr < gb->cart.ram_size) {
            gb->cart.ram[ram_addr] = value;
        }
        return;
    }

    // ---------------------------
    // Work RAM (0xC000 - 0xDFFF) - Cartridge RAM
    // ---------------------------
    if (addr < 0xE000) {
        gb->wram[addr - 0xC000] = value;
        return;
    }

    // ---------------------------
    // Echo RAM (0xE000 - 0xFDFF) - Mirror of WRAM
    // ---------------------------
    if (addr < 0xFE00) {
        // Write to WRAM (mirrored)
        gb->wram[addr - 0xE000] = value;
        return;
    }

    // ---------------------------
    // OAM (0xFE00 - 0xFE9F) - Sprite Attribute Table
    // ---------------------------
    if (addr < 0xFEA0) {
        // TODO: Check if OAM is accessible (not during PPU mode 2/3)
        gb->oam[addr - 0xFE00] = value;
        return;
    }

    // ---------------------------
    // Un-usable (0xFEA0 - 0xFEFF)
    // ---------------------------
    if (addr < 0xFF00) {
        // Writes ignored
        return;
    }

    // ---------------------------
    // I/O Registers (0xFF00 - 0xFF7F)
    // ---------------------------
    if (addr < 0xFF80) {
        io_write(gb, addr, value);
        return;
    }

    // ---------------------------
    // HRAM 0xFF80 - 0xFFFE 127 bytes
    // ---------------------------
    if (addr < 0xFFFF) {
        gb->hram[addr - 0xFF80] = value;
        return;
    }

    // ---------------------------
    // Interrupt Enable (0xFFFF)
    // ---------------------------
    if (addr == 0xFFFF) {
        gb->ie_register = value;
    }
}

// I/O Register handlers (NOTE: stubbed for now)
u8 io_read(GameBoy *gb, u16 addr) {
    switch (addr) {
        // Joypad
        case 0xFF00:
            return gb->io.joyp;

        // Serial
        case 0xFF01:
            return gb->io.sb;
        case 0xFF02:
            return gb->io.sc;

        // Timer
        case 0xFF04:
            return gb->io.div;
        case 0xFF05:
            return gb->io.tima;
        case 0xFF06:
            return gb->io.tma;
        case 0xFF07:
            return gb->io.tac;

        // Interrupt Flag
        case 0xFF0F:
            return gb->io.if_reg | 0xE0; // Upper bits always 1

        // Sound (stubbed - return 0xFF)
        case 0xFF10 ... 0xFF26:
            return gb->io.sound[addr - 0xFF10];

        // LCD
        case 0xFF40:
            return gb->io.lcdc;
        case 0xFF41:
            return gb->io.stat | 0x80; // Bit 7 always 1
        case 0xFF42:
            return gb->io.scy;
        case 0xFF43:
            return gb->io.scx;
        case 0xFF44:
            return gb->io.ly;
        case 0xFF45:
            return gb->io.lyc;
        case 0xFF46:
            return gb->io.dma;
        case 0xFF47:
            return gb->io.bgp;
        case 0xFF48:
            return gb->io.obp0;
        case 0xFF49:
            return gb->io.obp1;
        case 0xFF4A:
            return gb->io.wy;
        case 0xFF4B:
            return gb->io.wx;

        // Boot ROM
        case 0xFF50:
            return gb->io.boot;

        // Unmapped
        default:
            return 0xFF;
    }
}

void io_write(GameBoy *gb, u16 addr, u8 value) {
    switch (addr) {
        // Joypad
        case 0xFF00:
            gb->io.joyp = (gb->io.joyp & 0xCF) | (value & 0x30);
            break;

        // Serial
        case 0xFF01:
            gb->io.sb = value;
            break;
        case 0xFF02:
            gb->io.sc = value;
            if (value & 0x80) {
                // Serial transfer started - output character
                putchar(gb->io.sb);
                fflush(stdout);
                // Clear transfer flag and set interrupt
                gb->io.sc &= 0x7F;
                gb->io.if_reg |= 0x08; // Serial interrupt
            }
            break;

        // Timer
        case 0xFF04:
            gb->io.div = 0; // Writing any value resets DIV to 0
            break;
        case 0xFF05:
            gb->io.tima = value;
            break;
        case 0xFF06:
            gb->io.tma = value;
            break;
        case 0xFF07:
            gb->io.tac = value & 0x07;
            break; // Only lower 3 bits

        // Interrupt Flag
        case 0xFF0F:
            gb->io.if_reg = value & 0x1F; // Only lower 5 bits writable
            break;

        // Sound (stubbed)
        case 0xFF10 ... 0xFF26:
            gb->io.sound[addr - 0xFF10] = value;
            break;

        // LCD
        case 0xFF40:
            gb->io.lcdc = value;
            break;
        case 0xFF41:
            // Only bits 3-6 are writable
            gb->io.stat = (gb->io.stat & 0x87) | (value & 0x78);
            break;
        case 0xFF42:
            gb->io.scy = value;
            break;
        case 0xFF43:
            gb->io.scx = value;
            break;
        case 0xFF44:
            break; // LY is read-only
        case 0xFF45:
            gb->io.lyc = value;
            break;
        case 0xFF46:
            // DMA transfer - copy 0xA0 bytes from XX00-XX9F to OAM
            gb->io.dma = value;
            u16 src    = value << 8;
            for (int i = 0; i < 0xA0; i++) {
                gb->oam[i] = mmu_read(gb, src + i);
            }
            break;
        case 0xFF47:
            gb->io.bgp = value;
            break;
        case 0xFF48:
            gb->io.obp0 = value;
            break;
        case 0xFF49:
            gb->io.obp1 = value;
            break;
        case 0xFF4A:
            gb->io.wy = value;
            break;
        case 0xFF4B:
            gb->io.wx = value;
            break;

        // Boot ROM
        case 0xFF50:
            gb->io.boot = value;
            break;

        default:
            // Ignore writes to unmapped registers
            break;
    }
}

// Debug Helper: Dump Memory Region
void mmu_dump_region(GameBoy *gb, u16 start, u16 end) {
    printf("Memory Dump [0x%04x - 0x%04x]:\n", start, end);

    for (u16 addr = start; addr <= end; addr += 16) {
        printf("0x%04x: ", addr);

        // Print B in hex
        for (int i = 0; i < 16 && (addr + 1) <= end; i++) {
            printf("%02x ", mmu_read(gb, addr + 1));
        }

        printf("\n");
    }
}
