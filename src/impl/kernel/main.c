#include <stdint.h>
#include <stddef.h>

#include "print.h"
#include "keyboard.h"



void kernel_main() {
    print_clear();
    print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
    print_str("Welcome to Nex0Sphere");

    ps2_init();
    outb(PS2_DATA_PORT, 0xF4); // send "enable scanning" command

    while(1){
        uint8_t sc = ps2_read_data();
        uint16_t key = sct1[sc];
        if(key > 127){
            key = key >> 2;
        }
        else if(key != 0){
            char ascii = (char)(key & 0xFF);
            print_clear();
            print_char(ascii);
        }
    }
}
