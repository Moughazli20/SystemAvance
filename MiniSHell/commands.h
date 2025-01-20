#ifndef COMMANDS_H
#define COMMANDS_H

// Prototypes des fonctions
void parse_input(char *input, char **args);
int execute_command(char **args);
int execute_builtin(char **args);

#endif

