#pragma once

#include <stdint.h>
#include <stddef.h>


// I/O Ports
#define PS2_DATA_PORT   0x60    // PS/2 Data port
#define PS2_STATUS_PORT 0x64    // PS/2 Status port
#define PS2_COMMAND_PORT 0x64   // PS/2 Command port

// Status Register Bits
#define PS2_STATUS_OUTPUT_FULL 0x01
#define PS2_STATUS_INPUT_FULL  0x02

// Commands
#define PS2_COMMAND_READ_CONFIG 0x20
#define PS2_COMMAND_WRITE_CONFIG 0x60
#define PS2_COMMAND_ENABLE_PORT1 0xAE
#define PS2_COMMAND_DISABLE_PORT1 0xAD
#define PS2_COMMAND_ENABLE_PORT2 0xA8
#define PS2_COMMAND_DISABLE_PORT2 0xA7
#define PS2_COMMAND_READ_OUTPUT 0xD0
#define PS2_COMMAND_WRITE_OUTPUT 0xD1



// Initialization
void ps2_init();

// Read keyboard data
uint8_t ps2_read_data();

// Read a byte from an I/O port
static inline uint8_t inb(uint16_t port) {
    uint8_t data;
    asm volatile ("inb %1, %0" : "=a" (data) : "Nd" (port));
    return data;
}

// Write a byte to an I/O port
static inline void outb(uint16_t port, uint8_t data) {
    asm volatile ("outb %0, %1" : : "a" (data), "Nd" (port));
}

//array containing ascii values(if unprintable -> starting at 0x0100 increasing in order of table) indexable by scancodes from table 1
uint16_t sct1[] = {
    0, 0x0100, 49, 50, // unprintable = escape
    51, 52, 53, 54,
    55, 56, 57, 48,
    45, 61, 0x0200, 9,  // unprintable = backspace
    113, 119, 101, 114,
    116, 121, 117, 105,
    111, 112, 91, 93,
    0x0400, 0x0500, 97, 115, // unprintable = enter, control
    100, 102, 103, 104,
    106, 107, 108, 59,
    39, 96, 0x0600, 92, // unprintable = shift
    122, 120, 99, 118,
    98, 110, 109, 44,
    46, 47, 0x0600, 42, // unprintable = shift
    0x0700, 32, 0x0800, 0x0900, // unprintable = alt, CapsLock, f1
    0x0A00, 0x0B00, 0x0C00, 0x0D00, // unprintable = f2, f3, f4, f5
    0x0E00, 0x0F00, 0x1000, 0x1100, // unprintable = f6, f7, f8, f9
    0x1200, 0x1500, 0x1600, 55, // unprintable = f10, NumLock, ScrollLock  (rule broken here to make Funvtion keys more logical)
    56, 57, 45, 52,
    53, 54, 43, 49,
    50, 51, 48, 46,
    0, 0, 0, 0x1300,
    0x1400
};
