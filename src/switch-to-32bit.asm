[bits 16]

switch_to_32bit:
    cli                       ;disable interrupts
    lgdt [gdt_descriptor]     ;load the gdt
    mov  eax, cr0             ;get the current value of cr0
    or   eax, 0x1             ;set the protected mode bit
    mov  cr0, eax             ;write the new value of cr0
    jmp  CODE_SEG:BEGIN_32BIT ;jump to the 32-bit code

[bits 32]
init_32bit:
    mov ax,  DATA_SEG ;set the data segment registers
    mov ds,  ax
    mov ss,  ax
    mov es,  ax
    mov fs,  ax
    mov gs,  ax
    mov ebp, 0x90000  ;set the stack pointer
    mov esp, ebp
    
    call BEGIN_32BIT ;jump to the 32-bit code