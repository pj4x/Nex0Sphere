#include "memory_op.h"

// Implementation of strcmp function
int strcmp(char *str1, char *str2) {
    // Iterate through each character in both strings
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }

    // Return the difference between the first non-matching characters
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

void zero_char(char* buffer, uint8_t length){
    for(int i; i<length; i++){
        buffer[i] = 0;
    }
}
