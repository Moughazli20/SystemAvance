#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "commands.h"

// Parser la commande en arguments
void parse_input(char *input, char **args) {
    int i = 0;
    char *token = strtok(input, " ");

    while (token != NULL) {
        args[i] = token;
        i++;
        token = strtok(NULL, " ");
    }

    args[i] = NULL; 
}

