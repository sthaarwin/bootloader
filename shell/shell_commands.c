#include "shell.h"
#include "shell_commands.h"
#include "../drivers/display.h"
#include "../drivers/ports.h"
#include "../cpu/stdint.h"

#define REBOOT_DELAY 1000

void cmd_help(void) {
    print_string("Available commands:");
    print_nl();
    print_string("  help     - Show this help message");
    print_nl();
    print_string("  clear    - Clear the screen");
    print_nl();
    print_string("  version  - Show OS version");
    print_nl();
    print_string("  reboot   - Restart the system");
    print_nl();
}

void cmd_clear(void) {
    clear_screen();
}

void cmd_version(void) {
    print_string("AxOS v0.1");
    print_nl();
}

void cmd_reboot(void) {
    print_string("System is rebooting...");
    print_nl();
    
    for(int i = 0; i < 10000; i++) {
        asm volatile("nop");
    }

    asm volatile("cli");
    
    uint8_t temp;
    do {
        temp = port_byte_in(0x64);    
        if (temp & 1) {              
            port_byte_in(0x60);     
            continue;
        }
    } while (temp & 2);             
    
    port_byte_out(0x64, 0xFE);
    
    for(int i = 0; i < 10; i++) {
        asm volatile("nop");
    }
    
    asm volatile(
        "lidt [0]    \n"
        "int $0x3    \n"
    );
    asm volatile("hlt");
}