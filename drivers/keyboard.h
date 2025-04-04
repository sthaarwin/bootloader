#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../cpu/stdint.h"
#include "../shell/shell.h"
#include "ports.h"
#include "display.h"
#include "../kernel/util.h"
#include "../cpu/isr.h"

// Key state tracking
#define KEY_RELEASED 0x80
#define EXTENDED_KEY 0xE0

// Special key scancodes
#define ARROW_UP 0x48
#define ARROW_DOWN 0x50
#define ARROW_LEFT 0x4B
#define ARROW_RIGHT 0x4D
#define KEY_F1 0x3B
#define KEY_F12 0x58

void print_letter(uint8_t scancode);
void handle_special_key(uint8_t scancode);
char scancode_to_ascii(uint8_t scancode);
void init_keyboard(void);

#endif