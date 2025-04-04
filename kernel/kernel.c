#include "../cpu/stdint.h"
#include "util.h"
#include "../drivers/display.h"
#include "../drivers/keyboard.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"
#include "../cpu/timer.h"
#include "../drivers/ports.h"
#include "../shell/shell.h"

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

void delay(uint32_t count) {
    for(uint32_t i = 0; i < count; i++) {
        asm volatile("nop");
    }
}

void kernel_main(void)
{
    clear_screen();
    display_logo();

    print_string("Installing Interrupt service routines(ISR)...");
    isr_install();
    print_nl();

    print_string("Enabling eternal interrupts...");
    asm volatile("sti");
    print_nl();

    print_string("Initializing keyboard (IRQ 1)");
    init_keyboard();
    print_nl();

    init_timer(100);

    delay(30000000); 
    
    clear_screen(); 
    print_string_centered_color("System Ready", MAKE_COLOR(LIGHT_GREEN, BLACK));
    print_nl();
    
    shell_init();
    while (1)
    {
        asm volatile("hlt");
    }
}