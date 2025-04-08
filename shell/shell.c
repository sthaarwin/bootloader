#include "shell.h"
#include "shell_commands.h"
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
            backspace(get_cursor()); 
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
        cmd_help();
    }
    else if (strcmp(command, "clear") == 0)
    {
        cmd_clear();
    }
    else if (strcmp(command, "version") == 0)
    {
        cmd_version();
    }
    else if(strcmp(command, "reboot") == 0)
    {
        cmd_reboot();
    }
    else
    {
        print_string("Unknown command: ");
        print_string(command);
        print_nl();
    }
}