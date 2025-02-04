[bits 16]

switch_to_32bit:
    cli                     ; disable interrupts
    lgdt [gdt_descriptor]   ; load GDT
    mov eax, cr0
    or eax, 0x1            ; set protected mode bit
    mov cr0, eax
    jmp CODE_SEG:init_32bit ; far jump to 32-bit code

[bits 32]
init_32bit:
    mov ax, DATA_SEG       ; update segment registers
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000      ; update stack position
    mov esp, ebp

    jmp BEGIN_32BIT       ; jump to begin_32bit label in bootloader