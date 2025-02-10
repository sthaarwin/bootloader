# $@ = target file
# $< = first dependency
# $^ = all dependencies

# First rule is the one executed when no parameters are fed to the Makefile
all: run

# Include paths
INCLUDE_PATH = C:/msys64/ucrt64/include

# Common compiler flags
C_FLAGS = -m32 -fno-builtin -fno-stack-protector -nostdlib -nostdinc \
          -I $(INCLUDE_PATH) -ffreestanding -fno-pie \
          -fno-asynchronous-unwind-tables -mno-red-zone -fno-exceptions

# Source files
C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h)

# Object files
OBJ_FILES = bin/kernel-entry.o \
            $(patsubst %.c,bin/%.o,$(notdir $(C_SOURCES)))

# Final binary
bin/kernel.bin: $(OBJ_FILES)
	ld -m i386pe -Ttext 0x1000 -e _start -o bin/kernel.elf $^
	objcopy -O binary bin/kernel.elf $@

# Compile assembly files
bin/kernel-entry.o: boot/kernel-entry.asm
	nasm $< -f elf -o $@

# Pattern rule for C files
bin/%.o: kernel/%.c ${HEADERS}
	gcc ${C_FLAGS} -c $< -o $@

bin/%.o: drivers/%.c ${HEADERS}
	gcc ${C_FLAGS} -c $< -o $@

bin/%.o: cpu/%.c ${HEADERS}
	gcc ${C_FLAGS} -c $< -o $@

bin/isr.o: cpu/isr.c
	gcc -m32 -c cpu/isr.c -o bin/isr.o

bin/irq.o: cpu/irq.asm
	nasm -f elf cpu/irq.asm -o bin/irq.o

bin/irq.o: cpu/interrupt.asm
	nasm -f elf cpu/interrupt.asm -o bin/irq.o

bin/isr_asm.o: cpu/isr.asm
	nasm -f elf cpu/isr.asm -o bin/isr_asm.o

bin/isr_asm.o: cpu/interrupt.asm
	nasm -f elf cpu/interrupt.asm -o bin/isr_asm.o

bin/kernel.elf: bin/kernel-entry.o bin/kernel.o bin/util.o bin/display.o bin/ports.o bin/idt.o bin/isr.o bin/timer.o bin/irq.o bin/isr_asm.o
	ld -m i386pe -Ttext 0x1000 -e _start -o bin/kernel.elf $^

# Bootloader
bin/bootloader.bin: boot/bootloader.asm
	nasm $< -f bin -o $@

# Final OS image
bin/os-image.bin: bin/bootloader.bin bin/kernel.bin
	cat $^ > $@

# Run in QEMU
run: bin/os-image.bin
	qemu-system-i386 -fda $<

# Make directories if they don't exist
directories:

# Clean up
clean:
	$(RM) bin/*.bin bin/*.o bin/*.elf bin/*.dis

# Debug rule to print variables
print-%:
	@echo $* = $($*)

# Make sure the bin directory exists before compiling
$(OBJ_FILES): | directories

.PHONY: all clean run directories