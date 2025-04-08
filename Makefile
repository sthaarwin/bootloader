# $@ = target file
# $< = first dependency
# $^ = all dependencies

# First rule is the one executed when no parameters are fed to the Makefile
all: run

# Detect OS and set format
ifeq ($(OS),Windows_NT)
    INCLUDE_PATH = C:/msys64/ucrt64/include
    LD_FORMAT = i386pe
else
    INCLUDE_PATH = /usr/include
    LD_FORMAT = elf_i386
endif

# Common compiler flags
C_FLAGS = -m32 -fno-builtin -fno-stack-protector -nostdlib -nostdinc \
          -I$(CURDIR) -ffreestanding -fno-pie \
          -fno-asynchronous-unwind-tables -mno-red-zone -fno-exceptions

# Source files
C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c shell/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h shell/*.h)

# Object files
OBJ_FILES = bin/kernel-entry.o \
            $(patsubst %.c,bin/%.o,$(notdir $(C_SOURCES)))

# Final binary
bin/kernel.bin: bin/kernel.elf
	objcopy -O binary $< $@

bin/kernel.elf: bin/kernel-entry.o bin/kernel.o bin/util.o bin/display.o bin/ports.o bin/idt.o bin/isr.o bin/timer.o bin/irq.o bin/isr_asm.o bin/shell.o bin/keyboard.o bin/shell_commands.o
	ld -m $(LD_FORMAT) -Ttext 0x1000 -e _start -o $@ $^

# Assembly files
bin/kernel-entry.o: boot/kernel-entry.asm
	nasm $< -f elf -o $@

bin/irq.o: cpu/irq.asm
	nasm $< -f elf -o $@

bin/isr_asm.o: cpu/isr.asm
	nasm -f elf $< -o $@

# Pattern rules for C files
bin/%.o: kernel/%.c ${HEADERS}
	gcc ${C_FLAGS} -c $< -o $@

bin/%.o: drivers/%.c ${HEADERS}
	gcc ${C_FLAGS} -c $< -o $@

bin/%.o: cpu/%.c ${HEADERS}
	gcc ${C_FLAGS} -c $< -o $@

bin/%.o: shell/%.c ${HEADERS}
	gcc ${C_FLAGS} -c $< -o $@

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
	mkdir -p bin

# Clean up
clean:
	$(RM) -r bin

# Debug rule to print variables
print-%:
	@echo $* = $($*)

# Make sure the bin directory exists before compiling
$(OBJ_FILES): | directories

.PHONY: all clean run directories