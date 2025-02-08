#include "timer.h"

static void timer_callback(registers_t *regs)
{
    tick++;
    print_string("Tick: ");
    char tick_ascii[256];
    int_to_string(tick, tick_ascii, 10);
    print_string(tick_ascii);
    print_nl();
}

void init_timer(uint32_t freq)
{
    register_interrupt_handler(32, &timer_callback);

    uint32_t divisor = 1193180 / freq;
    uint8_t low = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)((divisor >> 8) & 0xFF);

    port_byte_out(0x43, 0x36);
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);
}