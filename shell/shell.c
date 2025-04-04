#include "shell.h"
#include "../drivers/display.h"
#include "../drivers/keyboard.h"
#include "../cpu/timer.h"
#include "../kernel/util.h"

#define MAX_COMMAND_LENGTH 256
static char command_buffer[MAX_COMMAND_LENGTH];
static int command_length = 0;

void shell_init(void)
{
    print_string("AxOS Shell v0.1");
    print_nl();
    print_string("> ");
}

void shell_handle_input(char key)
{
    if (key == '\n')
    {
        command_buffer[command_length] = '\0';
        print_nl();
        shell_process_command(command_buffer);
        command_length = 0;
        print_string("> ");
    }
    else if (key == '\b')
    {
        if (command_length > 0)
        {
            command_length--;
            backspace(get_cursor());  // Use new backspace function
        }
    }
    else if (command_length < MAX_COMMAND_LENGTH - 1)
    {
        command_buffer[command_length++] = key;
        char str[2] = {key, '\0'};
        print_string(str);
    }
}

void shell_process_command(char *command)
{
    if (command[0] == '\0')
        return;

    if (strcmp(command, "help") == 0)
    {
        print_string("Available commands:");
        print_nl();
        print_string("  help     - Show this help message");
        print_nl();
        print_string("  clear    - Clear the screen");
        print_nl();
        print_string("  version  - Show OS version");
        print_nl();
    }
    else if (strcmp(command, "clear") == 0)
    {
        clear_screen();
    }
    else if (strcmp(command, "version") == 0)
    {
        print_string("AxOS v0.1");
        print_nl();
    }
    else
    {
        print_string("Unknown command: ");
        print_string(command);
        print_nl();
    }
}