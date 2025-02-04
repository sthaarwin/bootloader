[bits 16]
[org 0x7c00]

;where to load the kernel
KERNEL_OFFSET equ 0x1000

;BIOS sets boot drive in DL register 
mov  [BOOT_DRIVE], dl
mov  bp,           0x9000
mov  sp,           bp

mov  bx,           MSG_16BIT_MODE
call print16
call print16_nl


call load_kernel
call switch_to_32bit

jmp  $

%include "boot/disk.asm"
%include "boot/gdt.asm"
%include "boot/switch-to-32bit.asm"
%include "boot/print-16bit.asm"
%include "boot/print-32bit.asm"


[bits 16]
load_kernel:
    mov  bx, MSG_LOAD_KERNEL
    call print16
    call print16_nl

    mov  bx, KERNEL_OFFSET  ; Set-up parameters for disk_load routine
    mov  dh, 15            ; Load 15 sectors (increase if your kernel is bigger)
    mov  dl, [BOOT_DRIVE]  ; Use boot drive number saved earlier
    call disk_load
    ret

[bits 32]
BEGIN_32BIT:
    mov ebx, MSG_32BIT_MODE
    call print32

    call KERNEL_OFFSET ;jump to the kernel
    jmp  $             ;infinite loop

;boot drive variables
BOOT_DRIVE      db 0
MSG_16BIT_MODE  db "Switching to 16-bit real mode...", 0
MSG_32BIT_MODE  db "Switching to 32-bit protected mode...", 0
MSG_LOAD_KERNEL db "Loading kernel...", 0

 ;padding and magic number
times 510-($-$$) db 0
dw 0xaa55