bits 16
org 0x7c00

; Clear the screen
mov ah, 0x00
mov al, 0x03  ; Text mode 80x25, clears screen
int 0x10

; Load the second stage (sector 2) into memory at 0x1000
mov ah, 0x02     ; BIOS read disk function
mov al, 0x01     ; Read one sector
mov ch, 0        ; Cylinder 0
mov cl, 2        ; Sector 2 (first sector after bootloader)
mov dh, 0        ; Head 0
mov dl, 0x80     ; Drive 0 (floppy)

; Load the second stage at 0x1000 (segment:offset)
mov es, 0x00     ; Segment part of the destination address
mov bx, 0x1000   ; Offset part of the destination address

int 0x13         ; Call BIOS disk read

; Jump to the second stage (which is loaded at 0x1000)
jmp 0x1000

times 510 - ($ - $$) db 0  ; Fill the remaining space with zeros
dw 0xAA55                 ; Boot signature
