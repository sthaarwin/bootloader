#ifndef SHELL_H
#define SHELL_H

void shell_init(void);
void shell_handle_input(char key);
void shell_process_command(char *command);

#endif