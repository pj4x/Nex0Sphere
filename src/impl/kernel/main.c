#include <stdint.h>
#include <stddef.h>

#include "print.h"
#include "keyboard.h"
#include "console.h"



void kernel_main() {
    char buffer[78] = {0}; // 80 collums - 2 for the prompt
    uint8_t length = 78;
    uint8_t pointer = 0;

    print_clear();
    print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
    print_str("Welcome to Nex0Sphere");
    print_newline();

    ps2_init();
    outb(PS2_DATA_PORT, 0xF4); // send "enable scanning" command

    while(1){
        uint8_t sc = ps2_read_data();
        uint16_t key = sct1[sc];
        if(key > 127){
            handle_unprintable(key, &buffer, &pointer, length);
        }
        else if(key != 0){
            handle_ascii(key, &buffer, &pointer);
        }
        print_prompt();
        print_buffer(&buffer, length);

        int i = 0; // sleep
        while(i < 5000){
            i++;
        }
    }
}
