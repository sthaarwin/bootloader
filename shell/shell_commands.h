#ifndef SHELL_COMMANDS_H
#define SHELL_COMMANDS_H

void cmd_help(void);
void cmd_clear(void);
void cmd_version(void);
void cmd_reboot(void);
void cmd_echo(char *args);
void cmd_shutdown(void);

#endif