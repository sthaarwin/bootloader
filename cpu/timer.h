#ifndef TIMER_H
#define TIMER_H

#include "stdint.h"
#include "isr.h"

extern uint32_t tick;
void init_timer(uint32_t freq);
void timer_callback(registers_t *regs);

#endif