# AxWare Bootloader

A bare metal 16/32-bit x86 bootloader implementation that demonstrates the transition from real mode to protected mode, with basic OS kernel loading capabilities.

## Architecture Overview

The bootloader follows a two-stage design:
1. Stage 1: 16-bit real mode initialization
2. Stage 2: Protected mode transition and kernel loading

## Features

- BIOS Parameter Block (BPB) implementation
- Two-stage boot process
- Protected mode (32-bit) support
- Memory management features:
  - GDT (Global Descriptor Table) setup
  - Basic memory mapping
- Disk operations:
  - Sector reading
  - Basic error handling
- Display capabilities:
  - VGA text mode (80x25)
  - Color support
  - Screen clearing and scrolling
- Kernel loading support

## Development Environment

### Prerequisites
- NASM assembler (2.15+)
- GCC (for kernel compilation)
- QEMU emulator
- GNU Make

### Directory Structure
```
bootloader/
├── boot/          # Boot sector and assembly files
├── kernel/        # C kernel source
├── drivers/       # Hardware interface code
└── bin/          # Build outputs
```

## Building

```sh
# Build the entire project
make all

# Build only the bootloader
make bin/bootloader.bin

# Build only the kernel
make bin/kernel.bin
```

## Running and Testing

```sh
# Run with QEMU
make run

# Debug with QEMU monitor
qemu-system-i386 -fda bin/os-image.bin -monitor stdio

# Clean build files
make clean
```

## Debugging

For debugging, you can use QEMU's monitor capabilities:
1. Start QEMU with `-monitor stdio`
2. Use `info registers` to view CPU state
3. Use `x/10i $pc` to disassemble around current instruction

## License

This project is licensed under the MIT License.
