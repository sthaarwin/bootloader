[extern irq_handler]

irq_common_stub:
    pusha           ; Pushes all registers
    mov ax, ds
    push eax       ; Save data segment
    
    mov ax, 0x10   ; Load kernel data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    push esp       ; Push stack pointer
    call irq_handler
    pop esp
    
    pop ebx        ; Restore data segment
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx
    
    popa           ; Restore registers
    add esp, 8     ; Clean up pushed error code and ISR number
    iret           ; Return from interrupt

; IRQ handlers
global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

; IRQ handlers
irq0:
    push byte 0
    push byte 32
    jmp irq_common_stub

irq1:
    push byte 0
    push byte 33
    jmp irq_common_stub

irq2:
    push byte 0
    push byte 34
    jmp irq_common_stub

irq3:
    push byte 0
    push byte 35
    jmp irq_common_stub

irq4:
    push byte 0
    push byte 36
    jmp irq_common_stub

irq5:
    push byte 0
    push byte 37
    jmp irq_common_stub

irq6:
    push byte 0
    push byte 38
    jmp irq_common_stub

irq7:
    push byte 0
    push byte 39
    jmp irq_common_stub

irq8:
    push byte 0
    push byte 40
    jmp irq_common_stub

irq9:
    push byte 0
    push byte 41
    jmp irq_common_stub

irq10:
    push byte 0
    push byte 42
    jmp irq_common_stub

irq11:
    push byte 0
    push byte 43
    jmp irq_common_stub

irq12:
    push byte 0
    push byte 44
    jmp irq_common_stub

irq13:
    push byte 0
    push byte 45
    jmp irq_common_stub

irq14:
    push byte 0
    push byte 46
    jmp irq_common_stub

irq15:
    push byte 0
    push byte 47
    jmp irq_common_stub
