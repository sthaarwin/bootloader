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
    for (int i = 0; i < MAX_COMMAND_LENGTH; i++) {
        command_buffer[i] = 0;
    }
    command_length = 0;

    print_string("AxOS Shell v0.1");
    print_nl();
    print_string("> ");
    set_cursor(get_cursor());
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

int find_space(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == ' ') {
            return i;
        }
        i++;
    }
    return -1; 
}

void shell_process_command(char *command)
{
    if (command[0] == '\0')
        return;

    int space_pos = find_space(command);
    char *args = 0;  // Using 0 instead of NULL
    
    if (space_pos != -1) {
        // Null-terminate the command at the space
        command[space_pos] = '\0';
        // Point args to the character after the space
        args = &command[space_pos + 1];
    }

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
    else if(strcmp(command, "echo") == 0)
    {
        cmd_echo(args);
    }
    else if(strcmp(command, "shutdown") == 0)
    {
        cmd_shutdown();
    }
    else
    {
        print_string("Unknown command: ");
        print_string(command);
        print_nl();
    }
}