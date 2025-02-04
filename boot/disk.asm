disk_load:
    pusha           ; Save all registers
    push dx         ; Store DX on stack so we can check number of sectors read later
    
    mov ah, 0x02    ; BIOS read sector function
    mov al, dh      ; Read DH sectors
    mov cl, 0x02    ; Start reading from second sector (after boot sector)
    mov ch, 0x00    ; Select cylinder 0
    mov dh, 0x00    ; Select head 0
    
    int 0x13        ; BIOS interrupt
    jc disk_error   ; Jump if error (if carry flag is set)
    
    pop dx          ; Restore DX from stack
    cmp al, dh      ; Compare sectors read (AL) to sectors expected (DH)
    jne sectors_error ; Display error if they're not equal
    popa            ; Restore all registers
    ret

disk_error:
    mov bx, DISK_ERROR_MSG
    call print16
    mov dh, ah      ; ah = error code from BIOS
    call print16_hex ; Print error code
    call print16_nl
    jmp disk_loop

sectors_error:
    mov bx, SECTORS_ERROR_MSG
    call print16
    jmp disk_loop

disk_loop:
    jmp $

DISK_ERROR_MSG: db "Disk read error! Error code: ", 0
SECTORS_ERROR_MSG: db "Incorrect number of sectors read!", 0