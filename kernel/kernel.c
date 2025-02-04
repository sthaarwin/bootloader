#include "util.h"
#include "../drivers/display.h"

void kernel_main(void)
{
    clear_screen();
    char line[20];
    for (int i = 1; i <= 35; ++i) {
        int_to_string(i, line, 50);
        print_string(line);
        print_nl();  
    }
}