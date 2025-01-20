#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"

#define PROMPT "MiniShell> "
#define MAX_INPUT_SIZE 1024

int main() {
    char input[MAX_INPUT_SIZE];
    char *parsed_args[128];

    while (1) {
        printf("%s", PROMPT);
        fflush(stdout);

        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
            printf("\n");
            break; 
        }

        input[strcspn(input, "\n")] = '\0';

        if (strlen(input) == 0) {
            continue;
        }

        parse_input(input, parsed_args);

        // Exécuter la commande
        if (execute_command(parsed_args) == -1) {
            break; 
        }
    }

    return 0;
}

