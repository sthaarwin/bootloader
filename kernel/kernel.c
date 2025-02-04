#include "util.h"
#include "../drivers/display.h"

void kernel_main(void) 
{
    // Direct write to video memory first
    char* video_memory = (char*)0xb8000;
    for(int i = 0; i < 10; i++) {
        video_memory[i*2] = 'X';
        video_memory[i*2 + 1] = 0x0f;
    }

    // Then try the display functions
    clear_screen();
    print_string("Hello world!");
}