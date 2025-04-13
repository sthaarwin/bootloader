#include "keyboard.h"

// Modifier flags
static uint8_t shift_pressed = 0;
static uint8_t ctrl_pressed = 0;
static uint8_t alt_pressed = 0;
static uint8_t extended_scancode = 0;

void print_letter(uint8_t scancode) {
    switch (scancode) {
        case 0x0: print_string("ERROR"); break;
        case 0x1: print_string("ESC"); break;
        case 0x2: print_string("1"); break;
        case 0x3: print_string("2"); break;
        case 0x4: print_string("3"); break;
        case 0x5: print_string("4"); break;
        case 0x6: print_string("5"); break;
        case 0x7: print_string("6"); break;
        case 0x8: print_string("7"); break;
        case 0x9: print_string("8"); break;
        case 0xA: print_string("9"); break;
        case 0xB: print_string("0"); break;
        case 0xC: print_string("-"); break;
        case 0xD: print_string("="); break;
        case 0xE: print_string("BACKSPACE"); break;
        case 0xF: print_string("TAB"); break;
        case 0x10: print_string("Q"); break;
        case 0x11: print_string("W"); break;
        case 0x12: print_string("E"); break;
        case 0x13: print_string("R"); break;
        case 0x14: print_string("T"); break;
        case 0x15: print_string("Y"); break;
        case 0x16: print_string("U"); break;
        case 0x17: print_string("I"); break;
        case 0x18: print_string("O"); break;
        case 0x19: print_string("P"); break;
        case 0x1A: print_string("["); break;
        case 0x1B: print_string("]"); break;
        case 0x1C: print_string("ENTER"); break;
        case 0x1D: print_string("CTRL"); break;
        case 0x1E: print_string("A"); break;
        case 0x1F: print_string("S"); break;
        case 0x20: print_string("D"); break;
        case 0x21: print_string("F"); break;
        case 0x22: print_string("G"); break;
        case 0x23: print_string("H"); break;
        case 0x24: print_string("J"); break;
        case 0x25: print_string("K"); break;
        case 0x26: print_string("L"); break;
        case 0x27: print_string(";"); break;
        case 0x28: print_string("'"); break;
        case 0x29: print_string("`"); break;
        case 0x2A: print_string("LSHIFT"); break;
        case 0x2B: print_string("\\"); break;
        case 0x2C: print_string("Z"); break;
        case 0x2D: print_string("X"); break;
        case 0x2E: print_string("C"); break;
        case 0x2F: print_string("V"); break;
        case 0x30: print_string("B"); break;
        case 0x31: print_string("N"); break;
        case 0x32: print_string("M"); break;
        case 0x33: print_string(","); break;
        case 0x34: print_string("."); break;
        case 0x35: print_string("/"); break;
        case 0x36: print_string("RSHIFT"); break;
        case 0x37: print_string("KP*"); break;
        case 0x38: print_string("ALT"); break;
        case 0x39: print_string("SPACE"); break;
        case 0x3A: print_string("CAPSLOCK"); break;
        case 0x3B: print_string("F1"); break;
        case 0x3C: print_string("F2"); break;
        case 0x3D: print_string("F3"); break;
        case 0x3E: print_string("F4"); break;
        case 0x3F: print_string("F5"); break;
        case 0x40: print_string("F6"); break;
        case 0x41: print_string("F7"); break;
        case 0x42: print_string("F8"); break;
        case 0x43: print_string("F9"); break;
        case 0x44: print_string("F10"); break;
        case 0x45: print_string("NUMLOCK"); break;
        case 0x46: print_string("SCROLLLOCK"); break;
        case 0x47: print_string("KP7"); break;
        case 0x48: print_string("KP8"); break;
        case 0x49: print_string("KP9"); break;
        case 0x4A: print_string("KP-"); break;
        case 0x4B: print_string("KP4"); break;
        case 0x4C: print_string("KP5"); break;
        case 0x4D: print_string("KP6"); break;
        case 0x4E: print_string("KP+"); break;
        case 0x4F: print_string("KP1"); break;
        case 0x50: print_string("KP2"); break;
        case 0x51: print_string("KP3"); break;
        case 0x52: print_string("KP0"); break;
        case 0x53: print_string("KP."); break;
        default:
            if (scancode <= 0x7f) {
                print_string("Unknown key down");
            } else if (scancode <= 0x39 + 0x80) {
                print_string("key up ");
                print_letter(scancode - 0x80);
            } else {
                print_string("Unknown key up");
            }
            break;
    }
}

char scancode_to_ascii(uint8_t scancode) {
    static char ascii_normal[] = {
        0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',  
        '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
        0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
        0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
        '*', 0, ' '
    };

    static char ascii_shift[] = {
        0, 0, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
        '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
        0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',
        0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0,
        '*', 0, ' '
    };

    if (scancode == 0x0E) {
        return '\b';
    }
    
    if (scancode == 0x1C) {
        return '\n';
    }

    if (scancode >= sizeof(ascii_normal)) return 0;
    
    return shift_pressed ? ascii_shift[scancode] : ascii_normal[scancode];
}

void handle_special_key(uint8_t scancode) {
    if (extended_scancode) {
        switch (scancode) {
            case ARROW_UP:
                break;
            case ARROW_DOWN:
                break;
            case ARROW_LEFT:
                break;
            case ARROW_RIGHT:
                break;
            default:
                break;
        }
        extended_scancode = 0;
        return;
    }

    if (!(scancode & KEY_RELEASED)) {
        switch (scancode) {
            case 0x2A:
            case 0x36:
                shift_pressed = 1;
                break;
            case 0x1D:
                ctrl_pressed = 1;
                break;
            case 0x38:
                alt_pressed = 1;
                break;
        }
    } else {
        switch (scancode & ~KEY_RELEASED) {
            case 0x2A:
            case 0x36:
                shift_pressed = 0;
                break;
            case 0x1D:
                ctrl_pressed = 0;
                break;
            case 0x38:
                alt_pressed = 0;
                break;
        }
    }
}

static void keyboard_callback(registers_t *regs) {
    uint8_t scancode = port_byte_in(0x60);
    
    if (scancode == EXTENDED_KEY) {
        extended_scancode = 1;
        return;
    }

    handle_special_key(scancode);

    if (!(scancode & KEY_RELEASED)) {
        char key = scancode_to_ascii(scancode);
        if (key) {
            shell_handle_input(key);
        }
    }
}

void init_keyboard() {
    port_byte_out(0x21, port_byte_in(0x21) & ~0x02);
    register_interrupt_handler(IRQ1, keyboard_callback);
}
