[bits 32]
global _start
extern _kernel_main    ; Remove ALL underscores

section .text
_start:
    call _kernel_main  ; Remove ALL underscores
    jmp $