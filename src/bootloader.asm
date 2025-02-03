bits 16
org 0x7c00

; Clear the screen
mov ah, 0x00
mov al, 0x03  ; Set text mode 80x25, clears screen
int 0x10

; Calculate the length of the string
mov si, hello
xor cx, cx
count_loop:
    mov al, [si]
    cmp al, 0
    je done_count
    inc si
    inc cx
    jmp count_loop
done_count:

; Compute center column (80 - length) / 2
mov ax, 80
sub ax, cx
shr ax, 1
mov dl, al

; Set the cursor position
mov ah, 0x02
mov bh, 0x00
mov dh, 12     ; Row (fixed)
int 0x10

; Print the string in red
mov si, hello
mov bl, 0x0C   ; Light Red text color
mov bh, 0x00

print:
    mov al, [si]
    cmp al, 0
    je done_print

    mov ah, 0x0E
    int 0x10

    inc si
    jmp print

done_print:
; Wait for key press
mov ah, 0x00
int 0x16

jmp $

hello:
    db 'Welcome to AxWare', 0  

times 510 - ($-$$) db 0
dw 0xAA55