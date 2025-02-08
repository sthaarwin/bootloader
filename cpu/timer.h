#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include "../kernel/util.h"
#include "../drivers/display.h"
#include "../drivers/ports.h"
#include "isr.h"
#include "idt.h"

uint32_t tick = 0;
void init_timer(uint32_t freq);
static void timer_callback(registers_t *regs);

#endif