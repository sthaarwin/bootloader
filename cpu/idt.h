#ifndef IDT_H
#define IDT_H

#include <stdint.h>
#include "../kernel/util.h"

#define KERNEL_CS 0x08
#define IDT_ENTRIES 256

typedef struct{
    uint16_t low_offset;
    uint16_t sel;
    uint8_t always0;
    uint8_t flags;
    uint16_t high_offset;
} __attribute__((packed)) idt_gate_t;

typedef struct{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_register_t;



void set_idt_gate(int n, uint32_t handler);
void load_idt();

idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;

void set_idt_gate(int n, uint32_t handler){
    idt[n].low_offset = low_16(handler);
    idt[n].sel = KERNEL_CS;
    idt[n].always0 = 0;
    idt[n].flags = 0x8E;
    idt[n].high_offset = high_16(handler);
}

void load_idt(){
    idt_reg.base = (uint32_t)&idt;
    idt_reg.limit = (sizeof(idt_gate_t) * IDT_ENTRIES) - 1;

    asm volatile("lidt (%0)" : : "r" (&idt_reg));
}

#endif