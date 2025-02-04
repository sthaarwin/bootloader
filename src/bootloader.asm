[bits 16]
[org 0x7c00]

;where to load the kernel
KERNEL_OFFSET equ 0x1000

;BIOS sets boot drive in DL register 
mov  [BOOT_DRIVE], dl

;setup stack
mov  bp,           0x9000
mov  sp,           bp

call load_kernel
call switch_to_32bit

jmp  $

%include "src/disk.asm"
%include "src/gdt.asm"
%include "src/switch-to-32bit.asm"

[bits 16]
load_kernel:
    mov  bx, KERNEL_OFFSET
    mov  dh, 2
    mov  dl, [BOOT_DRIVE]
    call disk_load
    ret

[bits 32]
BEGIN_32BIT:
    call KERNEL_OFFSET ;jump to the kernel
    jmp  $             ;infinite loop

;boot drive variables
BOOT_DRIVE db 0
 
 ;padding and magic number
times 510-($-$$) db 0
dw                  0xaa55