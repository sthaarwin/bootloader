bits 16
org 0x7c00

;clear the screen
mov ah, 0x00
mov al, 0x03
int 0x10

;calculate the length of the string
mov si, hello ; point to the string
xor cx, cx ; clear cx register
count_loop: ; loop to count the length of the string
    cmp byte [si + cx], 0   ; check if the current character is null
     je done_count  ; if null, we are done counting
     inc cx ; increment the count 
     jmp count_loop ; loop back to count the next character
done_count: 

;calculate the position to print the string
mov ax, 80 ; 80 - width of the screen
sub ax, cx ; 80 - length of string
shr ax, 1  ; divide by 2
mov dl, al  ; save the position to dl

;set the cursor position
mov ah, 0x02
mov bh, 0x00
mov dh, 12
int 0x10

;print the string
print:
    mov ah, 0x0e
    mov al, [hello + si]
    int 0x10

    add si, 1
    cmp byte [hello + si], 0
    jne print

jmp $

hello:
    db 'Booting the bootloader', 0

times 510 - ($-$$) db 0
dw 0xAA55