disk_load:
    push dx         ; Store DX (containing number of sectors) on stack
    
    mov ah, 0x02    ; BIOS read sector function
    mov al, dh      ; Read DH sectors
    mov ch, 0x00    ; Select cylinder 0
    mov dh, 0x00    ; Select head 0
    mov cl, 0x02    ; Start reading from second sector (after boot sector)
    
    int 0x13        ; BIOS interrupt
    
    jc disk_error   ; Jump if error (if carry flag is set)
    
    pop dx          ; Restore DX from stack
    cmp dh, al      ; Compare sectors read (AL) to sectors expected (DH)
    jne disk_error  ; Display error if they're not equal
    ret

disk_error:
    mov bx, DISK_ERROR_MSG
    call print16
    call print16_nl

    mov dh, al
    call print16_hex
    jmp disk_loop

sector_error:
    mov bx, SECTOR_ERROR_MSG
    call print16

disk_loop:
    jmp $

DISK_ERROR_MSG: db "Disk read error!", 0
SECTOR_ERROR_MSG: db "Sector read error!", 0