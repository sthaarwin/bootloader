#include "ports.h"
#include "../kernel/util.h"
#include "display.h"

void set_cursor(int offset) {
    offset /= 2;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

int get_cursor() {
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8;
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset * 2;
}

int get_offset(int col, int row) {
    return 2 * (row * MAX_COLS + col);
}

int get_row_from_offset(int offset) {
    return offset / (2 * MAX_COLS);
}

int move_offset_to_new_line(int offset) {
    return get_offset(0, get_row_from_offset(offset) + 1);
}

void set_char_at_video_memory(char character, int offset) {
    char *video_memory = (char *)VIDEO_ADDRESS;
    video_memory[offset] = character;
    video_memory[offset + 1] = WHITE_ON_BLACK;
}

int scroll_ln(int cursor_offset) {
    memory_copy((char *)(VIDEO_ADDRESS + 2 * MAX_COLS),
                (char *)VIDEO_ADDRESS,
                MAX_COLS * (MAX_ROWS - 1) * 2);

    int last_line = get_offset(0, MAX_ROWS - 1);
    for (int i = 0; i < MAX_COLS * 2; i += 2) {
        set_char_at_video_memory(' ', last_line + i);
    }

    return last_line;
}

void print_string(char *string) {
    int offset = get_cursor();
    int i = 0;
    
    while(string[i] != 0) {
        if (offset >= MAX_ROWS * MAX_COLS * 2) {
            offset = scroll_ln(offset);
        }
        set_char_at_video_memory(string[i], offset);
        offset += 2;
        i++;
    }
    
    set_cursor(offset);
}

void print_nl() {
    int offset = move_offset_to_new_line(get_cursor());
    if(offset >= MAX_ROWS * MAX_COLS * 2) {
        offset = scroll_ln(offset);
    }
    set_cursor(offset);
}

void clear_screen() {
    int screen_size = MAX_COLS * MAX_ROWS;
    for(int i = 0; i < screen_size; i++) {
        char* video_memory = (char*)VIDEO_ADDRESS;
        video_memory[i * 2] = ' ';
        video_memory[i * 2 + 1] = WHITE_ON_BLACK;
    }
    set_cursor(0);
}

int get_padding(int string_length) {
    return (MAX_COLS - string_length) / 2;
}

void print_string_centered(char *string) {
    int len = 0;
    while(string[len] != 0) len++;
    
    int padding = get_padding(len);
    for(int i = 0; i < padding; i++) {
        print_string(" ");
    }
    print_string(string);
}

// New color functions
void set_char_at_video_memory_color(char character, int offset, char color_attr) {
    char *video_memory = (char *)VIDEO_ADDRESS;
    video_memory[offset] = character;
    video_memory[offset + 1] = color_attr;
}

void print_string_color(char *string, char color_attr) {
    int offset = get_cursor();
    int i = 0;
    
    while(string[i] != 0) {
        if (offset >= MAX_ROWS * MAX_COLS * 2) {
            offset = scroll_ln(offset);
        }
        set_char_at_video_memory_color(string[i], offset, color_attr);
        offset += 2;
        i++;
    }
    
    set_cursor(offset);
}

void print_string_centered_color(char *string, char color_attr) {
    int len = 0;
    while(string[len] != 0) len++;
    
    int padding = get_padding(len);
    for(int i = 0; i < padding; i++) {
        print_string_color(" ", color_attr);
    }
    print_string_color(string, color_attr);
}