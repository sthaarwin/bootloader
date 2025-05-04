#include "../cpu/stdint.h"
#include "util.h"
#include "../drivers/display.h"
#include "../drivers/keyboard.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"
#include "../cpu/timer.h"
#include "../drivers/ports.h"
#include "../shell/shell.h"
#include "kernel.h"

void delay(uint32_t count) {
    volatile uint32_t i;
    for (i = 0; i < count * 100000; i++) {
        asm("nop");
    }
}

void display_logo()
{
    char *logo[] = {
        " ==================================== ",
        "|       ##   ##   ##   ##   ###      |",
        "|      #  #   ## ##   #  # #         |",
        "|      ####    ###    #  #  ##       |",
        "|      #  #   ## ##   #  #    #      |",
        "|      #  #  ##   ##   ##  ###       |",
        " ==================================== ",
        "",
        "     [[ A Custom OS ]]     ",
        "",
        "    >> Created by Arwin <<    ",
        "",
        "______________________________________"};

    print_string_centered_color(logo[0], MAKE_COLOR(YELLOW, BLACK));
    print_nl();

    for (int i = 1; i <= 5; i++)
    {
        print_string_centered_color(logo[i], MAKE_COLOR(CYAN, BLACK));
        print_nl();
    }

    print_string_centered_color(logo[6], MAKE_COLOR(YELLOW, BLACK));
    print_nl();
    print_nl();

    print_string_centered_color(logo[8], MAKE_COLOR(LIGHT_GREEN, BLACK));
    print_nl();
    print_nl();

    print_string_centered_color(logo[10], MAKE_COLOR(LIGHT_MAGENTA, BLACK));
    print_nl();
    print_nl();

    print_string_centered_color(logo[12], MAKE_COLOR(YELLOW, BLACK));
    print_nl();
}

void kernel_main()
{
    init_display();
    isr_install();
    display_logo();
    
    delay(2);
    
    irq_install();
    shell_init();

    while (1)
    {
        asm("hlt");
    }
}