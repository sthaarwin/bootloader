disk_load:
    pusha
    mov ah, 0x02 ;read sectors
    mov al, dh   ;number of sectors to read
    mov cl, 0x02 ;start at second sector
    mov dh, 0x00 ;head number
    mov ch, 0x00 ;cycle number
    
    ;dl = drive number is set as input to diskload
    ;es:bx = buffer pointer is set as input as well

    int 0x13       ;BIOS disk interrupt
    jc  disk_error ;if carry flag is set, there was an error

    pop dx           ;get back to the original number of sectors to read
    cmp al, dh       ;compare the number of sectors read to the number requested
    jne sector_error ;if they are not equal, there was an error

    popa
    ret

disk_error:
    jmp disk_loop

sector_error:
    jmp disk_loop

disk_loop:
    jmp $