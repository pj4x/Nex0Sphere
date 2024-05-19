#pragma once
#include <stdint.h>
#include <stddef.h>

#include "print.h"

void handle_unprintable(uint16_t key, char* buffer, uint8_t length);

void hande_ascii(char key, char* buffer, uint8_t length);

void print_prompt(char* buffer, uint8_t length);
