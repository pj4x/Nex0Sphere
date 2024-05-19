#include "console.h"

void handle_unprintable(uint16_t key, char* buffer, uint8_t* pointer, uint8_t length){
    switch(key){
        case BACKSPACE:
            if(*pointer == 0){
                buffer[*pointer] = 0;
                set_col(2+(*pointer));
                print_char(' ');
            }
            else{
                (*pointer)--;
                buffer[*pointer] = 0;
                set_col(2+(*pointer));
                print_char(' ');
            }
            break;
        case ENTER:
            do_buffer(buffer, length, pointer);
            break;
    }
}

void handle_ascii(char key, char* buffer, uint8_t* pointer){
    if(*pointer < 78){
        buffer[*pointer] = key;
        (*pointer)++;
    }
}

void print_prompt(){
    set_col(0);
    print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
    print_str("$ ");
}

void print_buffer(char* buffer, uint8_t length){
    print_set_color(PRINT_COLOR_GREEN, PRINT_COLOR_BLACK);
    set_col(2); // after the prompt
    for(int i; i<length; i++){
        if(buffer[i] == 0){
            break;
        }
        print_char(buffer[i]);
    }
}

void do_buffer(char* buffer, uint8_t length, uint8_t* pointer){
    if(strcmp(buffer, "ver") == 0){
        print_newline();
        print_str("Version: Nex0.3");
        zero_char(buffer, length);
        *pointer = 0;
        print_newline();
    }
    else if(strcmp(buffer, "clear") == 0){
        print_clear();
        zero_char(buffer, length);
        *pointer = 0;
    }
    else {
        print_newline();
        print_str("command not found");
        zero_char(buffer, length);
        *pointer = 0;
        print_newline();
    }
}
