# AxWare Bootloader

A bare metal 16/32-bit x86 bootloader implementation with a basic kernel and command-line shell.

## Architecture Overview

The system consists of three main components:
1. Bootloader - Handles system initialization
2. Kernel - Manages hardware and provides basic services 
3. Shell - Provides user interface and command processing

## Features

### Core Features
- Protected mode (32-bit) support
- Interrupt handling (ISR/IRQ)
- Hardware abstraction layer
- Programmable Interval Timer (PIT)
- Memory management

### Display Features
- VGA text mode (80x25)
- Color support
- Screen clearing and scrolling
- Cursor management

### Input/Output
- PS/2 Keyboard support
- Special key handling (Shift, Ctrl, Alt)
- Extended key support (Function keys, arrows)
- Basic I/O ports management

### Shell
- Command-line interface
- Built-in commands:
  - help - Display available commands
  - clear - Clear screen
  - version - Show OS version
- Command history support
- Backspace handling

## Development Environment

### Prerequisites
- NASM assembler (2.15+)
- GCC (for C compilation)
- QEMU emulator
- GNU Make

### Directory Structure
```
bootloader/
├── boot/          # Boot sector and assembly files
├── kernel/        # C kernel source
├── drivers/       # Hardware interface code
├── shell/         # Shell source code and utilities
└── bin/           # Build outputs*
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
