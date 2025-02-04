print16:
    pusha
    
;string will be terminated by 0 byte in memory
print16_loop:
   mov al, [bx]
   cmp al, 0
   je  print16_done
   mov ah, 0x0e
   int 0x10

   add bx, 1
   jmp print16_loop

print16_done:
    popa
    ret

print16_nl:
    pusha
    
    mov ah, 0x0e
    mov al, 0x0a
    int 0x10

    mov al, 0x0d
    int 0x10

    popa
    ret

print16_cls:
    pusha

    mov ah, 0x00
    mov al, 0x03
    int 0x10

    popa
    ret

print16_hex:
    pusha

    mov cx, 0

print16_hex_loop:
    cmp cx, 4
    je  print16_hex_done

    mov ax, dx
    and ax, 0xf000
    add al, 0x30
    cmp al, 0x39
    jle print16_hex_step2
    add al, 0x07

print16_hex_step2:
    mov bx,   PRINT16_HEX_OUT + 5
    sub bx,   cx
    mov [bx], al
    ror dx,   4

    add cx, 1
    jmp print16_hex_loop

print16_hex_done:
    mov  bx, PRINT16_HEX_OUT
    call print16

    popa
    ret

PRINT16_HEX_OUT:
    db '0x0000', 0