bits 16
org 0x7c00

; Clear the screen
mov ah, 0x00
mov al, 0x03  ; Set text mode 80x25, clears screen
int 0x10

; Step 1: Calculate the length of the string
mov si, hello  ; Point to the string
xor cx, cx     ; CX = 0 (counter)
count_loop:
    mov al, [si]     ; Load character
    cmp al, 0        ; Check if null terminator
    je done_count
    inc si           ; Move to next character
    inc cx           ; Increment length count
    jmp count_loop
done_count:

; Step 2: Compute center column (80 - length) / 2
mov ax, 80     ; Screen width
sub ax, cx     ; 80 - length of string
shr ax, 1      ; Divide by 2
mov dl, al     ; Store center column in DL

; Step 3: Set the cursor position
mov ah, 0x02
mov bh, 0x00   ; Page number
mov dh, 12     ; Row (fixed)
int 0x10

; Step 4: Print the string in red
mov si, hello  ; Reset SI to point to the string
mov bl, 0x0C   ; Light Red text color
mov bh, 0x00   ; Page number

print:
    mov al, [si]     ; Load character
    cmp al, 0        ; Check if null terminator
    je done_print

    mov ah, 0x0E     ; BIOS teletype mode
    int 0x10

    inc si           ; Move to next character
    jmp print

done_print:
; Wait for key press
mov ah, 0x00
int 0x16  ; BIOS keyboard input

jmp $

hello:
    db 'Welcome to AxWare', 0  

times 510 - ($-$$) db 0
dw 0xAA55
