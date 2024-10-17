#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        return 1;
    }

    pid_t pid1 = fork();
    if (pid1 == -1) {
        perror("fork failed");
        return 1;
    }

    if (pid1 == 0) {
        // Processus fils 1 : exécute 'ps eaux'
        close(pipefd[0]);  // Fermer la lecture
        dup2(pipefd[1], 1);  // Rediriger STDOUT vers le pipe
        close(pipefd[1]);  // Fermer l'écriture
        execlp("ps", "ps", "eaux", NULL);
        perror("exec ps failed");
        return 1;
    }

    pid_t pid2 = fork();
    if (pid2 == -1) {
        perror("fork failed");
        return 1;
    }

    if (pid2 == 0) {
        // Processus fils 2 : exécute 'grep "^root "'
        close(pipefd[1]);  // Fermer l'écriture
        dup2(pipefd[0], 0);  // Rediriger STDIN depuis le pipe
        close(pipefd[0]);  // Fermer la lecture
        execlp("grep", "grep", "^root", NULL);
        perror("exec grep failed");
        return 1;
    }

    // Processus père
    close(pipefd[0]);
    close(pipefd[1]);

    wait(NULL);  // Attendre les fils
    wait(NULL);

    // Afficher un message si "root" est trouvé
    write(1, "root est connecté\n", 18);
    
    return 0;
}

