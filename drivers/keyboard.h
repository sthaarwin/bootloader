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

// New special key defines
#define KEY_TAB 0x0F
#define KEY_LSHIFT 0x2A
#define KEY_RSHIFT 0x36
#define KEY_LCTRL 0x1D
#define KEY_RCTRL 0x1D  // With E0 prefix
#define KEY_LALT 0x38
#define KEY_RALT 0x38   // With E0 prefix
#define KEY_LWIN 0x5B   // With E0 prefix
#define KEY_RWIN 0x5C   // With E0 prefix
#define KEY_APPS 0x5D   // Context menu key, with E0 prefix

void print_letter(uint8_t scancode);
void handle_special_key(uint8_t scancode);
char scancode_to_ascii(uint8_t scancode);
void keyboard_callback(registers_t *regs);
void init_keyboard(void);

#endif