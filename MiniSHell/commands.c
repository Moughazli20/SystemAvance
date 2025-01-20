#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "commands.h"

// Implémentation des commandes internes
int execute_builtin(char **args) {
    if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            fprintf(stderr, "MiniShell: cd: argument manquant\n");
        } else if (chdir(args[1]) != 0) {
            perror("MiniShell: cd");
        }
        return 1; 
    }

    if (strcmp(args[0], "pwd") == 0) {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s\n", cwd);
        } else {
            perror("MiniShell: pwd");
        }
        return 1; 
    }

    if (strcmp(args[0], "exit") == 0) {
        return -1; 
    }

    return 0; 
}

// Exécution des commandes
int execute_command(char **args) {
    int builtin_status = execute_builtin(args);
    if (builtin_status != 0) {
        return builtin_status;
    }

    pid_t pid = fork();
    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("MiniShell");
        }
        exit(EXIT_FAILURE); 
    } else if (pid < 0) {
        perror("MiniShell");
    } else {
        int status;
        waitpid(pid, &status, 0);
    }

    return 1;
}

