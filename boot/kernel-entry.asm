[bits 32]
global _start
extern _kernel_main    ; Note the underscore prefix

section .text
_start:
    call _kernel_main  ; Call with underscore prefix
    jmp $