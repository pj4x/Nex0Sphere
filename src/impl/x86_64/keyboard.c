#include "keyboard.h"



// Initialization
void ps2_init() {
    // Disable both PS/2 ports
    outb(PS2_COMMAND_PORT, PS2_COMMAND_DISABLE_PORT1);
    outb(PS2_COMMAND_PORT, PS2_COMMAND_DISABLE_PORT2);

    // Flush output buffer
    while (inb(PS2_STATUS_PORT) & PS2_STATUS_OUTPUT_FULL)
        inb(PS2_DATA_PORT);

    // Read controller configuration byte
    outb(PS2_COMMAND_PORT, PS2_COMMAND_READ_CONFIG);
    uint8_t config = inb(PS2_DATA_PORT);

    // Enable PS/2 ports
    config |= 1;    // Enable first port
    config &= ~0x10; // Enable IRQ12 for first port
    outb(PS2_COMMAND_PORT, PS2_COMMAND_WRITE_CONFIG);
    outb(PS2_DATA_PORT, config);

    outb(PS2_COMMAND_PORT, PS2_COMMAND_ENABLE_PORT1); // Enable first port
}

// Read keyboard data
uint8_t ps2_read_data() {
    while (!(inb(PS2_STATUS_PORT) & PS2_STATUS_OUTPUT_FULL))
        ; // Wait until output buffer is full
    return inb(PS2_DATA_PORT);
}
