# $@ = target file
# $< = first dependency
# $^ = all dependencies

# First rule is the one executed when no parameters are fed to the Makefile
all: run

bin/kernel.bin: bin/kernel-entry.o bin/kernel.o
	ld -m i386pe -Ttext 0x1000 -e _start -o bin/kernel.elf $^
	objcopy -O binary bin/kernel.elf $@

bin/kernel-entry.o: boot/kernel-entry.asm
	nasm $< -f elf -o $@

bin/kernel.o: kernel/kernel.c
	gcc -m32 -fno-builtin -fno-stack-protector -nostdlib -nostdinc -c $< -o $@ -ffreestanding -fno-pie -fno-asynchronous-unwind-tables

bin/bootloader.bin: boot/bootloader.asm
	nasm $< -f bin -o $@

bin/os-image.bin: bin/bootloader.bin bin/kernel.bin
	cat $^ > $@

run: bin/os-image.bin
	qemu-system-i386 -fda $<

clean:
	$(RM) bin/*.bin bin/*.o bin/*.elf bin/*.dis