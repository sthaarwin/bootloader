# AxWare Bootloader

This is a simple bootloader that demonstrates basic bootloader functionality, including video mode initialization and text display. 

## Features

- Initializes video mode to 80x25 text mode
- Clears the screen
- Displays a welcome message centered on the screen

## Building

To build the bootloader, you will need an assembler like NASM. Run the following command to assemble the bootloader:

```sh
nasm -f bin -o bin/bootloader.bin src/bootloader.asm
```

## Running

You can run the bootloader using an emulator like QEMU. Use the following command to run the bootloader:

```sh
qemu-system-x86_64 -drive format=raw,file=bin/bootloader.bin
```

## License

This project is licensed under the MIT License.
