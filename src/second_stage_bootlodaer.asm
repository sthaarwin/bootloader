bits 16
org 0x1000  ; Start at 0x1000, where the first bootloader loaded it

; Clear the screen
mov ah, 0x00
mov al, 0x03  ; Text mode 80x25
int 0x10

; Print a simple message
mov si, msg
call print_string

; Wait for a key press before halting
mov ah, 0x00
int 0x16  ; BIOS keyboard input

jmp $

; Function to print a null-terminated string
print_string:
    mov ah, 0x0E  ; BIOS teletype mode
print_loop:
    lodsb         ; Load next character into AL
    cmp al, 0     ; Check if null terminator
    je done_print
    int 0x10      ; Print character
    jmp print_loop
done_print:
    ret

msg db "Second-stage bootloader loaded!", 0
