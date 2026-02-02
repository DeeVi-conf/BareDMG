// src/core/gbemu.c
#include <gbemu.h>
#include <core/bus.h>
#include <string.h>
#include <stdio.h>

// Initialize the GameBoy instance
void gb_init(GameBoy *gb) {
    memset(gb, 0, sizeof(GameBoy));
    cpu_init(&gb->cpu, gb);

    // Initialize I/O registers to power-up state
    gb->io.joyp     = 0xCF;

    gb->io.sb       = 0x00;
    gb->io.sc       = 0x7E;

    gb->io.div      = 0xAB;
    gb->io.tima     = 0x00;
    gb->io.tma      = 0x00;
    gb->io.tac      = 0xF8;

    gb->io.if_reg   = 0xE1;
    gb->ie_register = 0x00;

    gb->io.lcdc     = 0x91;
    gb->io.stat     = 0x85;
    gb->io.scy      = 0x00;
    gb->io.scx      = 0x00;
    gb->io.ly       = 0x00;
    gb->io.lyc      = 0x00;
    gb->io.bgp      = 0xFC;
    gb->io.obp0     = 0x00;
    gb->io.obp1     = 0x00;
    gb->io.wy       = 0x00;
    gb->io.wx       = 0x00;

    gb->io.boot     = 0x00;
}

// Load a cartridge into GameBoy
void gb_load_rom(GameBoy *gb, const char *path) {
    // Try to load the cartridge
    // TODO: Might print details about the error (using error codes)
    if (cart_load(&gb->cart, path) != 0) {
        /* fprintf(stderr, "Failed to load ROM\n"); */
        gb->running = false;
        return;
    }

    printf("\n");
    cart_print_header(&gb->cart.header);
    printf("\n");

    cpu_reset(&gb->cpu);
    gb->running = true;
}

// Exeucte a single CPU instruction step
void gb_step(GameBoy *gb) {
    if (!gb->running)
        return;

    u8 cycles = cpu_step(&gb->cpu);
    gb->cycles += cycles;
}

// Run the emulator for the duration of one video frame
void gb_run_frame(GameBoy *gb) {
    if (!gb->running)
        return;

    // GameBoy runs at ~4.19 MHz
    // 1 frame @ 60 Hz = 70224 cycles
    u32 frame_cycles = 0;

    while (frame_cycles < 70224) {
        u8 cycles = cpu_step(&gb->cpu);
        frame_cycles += cycles;
        gb->cycles += cycles;
    }
}
