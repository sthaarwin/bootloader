#ifndef DISPLAY_H
#define DISPLAY_H

#include "ports.h"
#include "../kernel/util.h"

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

// Color definitions
#define BLACK 0x0
#define BLUE 0x1
#define GREEN 0x2
#define CYAN 0x3
#define RED 0x4
#define MAGENTA 0x5
#define BROWN 0x6
#define LIGHT_GRAY 0x7
#define DARK_GRAY 0x8
#define LIGHT_BLUE 0x9
#define LIGHT_GREEN 0xA
#define LIGHT_CYAN 0xB
#define LIGHT_RED 0xC
#define LIGHT_MAGENTA 0xD
#define YELLOW 0xE
#define WHITE 0xF

// Create color attribute byte
#define MAKE_COLOR(fg, bg) ((bg << 4) | fg)
#define WHITE_ON_BLACK MAKE_COLOR(WHITE, BLACK)

// Screen device I/O ports
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

// Function declarations
extern void set_cursor(int offset);
extern int get_cursor();
extern int get_offset(int col, int row);
extern int get_row_from_offset(int offset);
extern int move_offset_to_new_line(int offset);
extern void set_char_at_video_memory(char character, int offset);
extern int scroll_ln(int cursor_offset);
extern void print_string(char *string);
extern void print_nl();
extern void clear_screen();
extern int get_padding(int string_length);
extern void print_string_centered(char *string);
extern void print_string_color(char *string, char color_attr);
extern void print_string_centered_color(char *string, char color_attr);
extern void backspace(int offset);

#endif