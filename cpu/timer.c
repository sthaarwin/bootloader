#include "timer.h"
#include "isr.h"
#include "idt.h"
#include "../drivers/ports.h"
#include "../drivers/display.h"
#include "../kernel/util.h"
uint32_t tick = 0;

void timer_callback(registers_t *regs)
{
    tick++;
    /*
    print_string("Tick: ");
    char tick_ascii[256];
    int_to_string(tick, tick_ascii, 10);
    print_string(tick_ascii);
    print_nl();
    */
}

void init_timer(uint32_t freq)
{
    register_interrupt_handler(IRQ0, &timer_callback);

    uint32_t divisor = (freq > 0) ? (1193180 / freq) : 1193180;
    
    port_byte_out(0x43, 0x36); 
    port_byte_out(0x40, (uint8_t)(divisor & 0xFF));         // Low byte
    port_byte_out(0x40, (uint8_t)((divisor >> 8) & 0xFF)); // High byte
}