#include "../cpu/stdint.h"
#pragma once

#define low_16(address) (uint16_t)((address)&0xFFFF)
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)

#ifndef UTIL_H
#define UTIL_H

void memory_copy(char *source, char *dest, int nbytes);
int string_length(char s[]);
void reverse(char s[]);
char *int_to_string(int v, char *buffer, int radix_base);
int strcmp(const char *s1, const char *s2);

#endif