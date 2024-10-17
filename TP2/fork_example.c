#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();  // Crée un processus fils

    if (pid == -1) {
        // Gestion d'erreur si fork échoue
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // Processus fils
        printf("Fils : Mon PID est %d, le PID de mon père est %d\n", getpid(), getppid());
        int last_digit = getpid() % 10;  // Récupérer le dernier chiffre du PID
        exit(last_digit);
    } else {
        // Processus père
        int status;
        wait(&status);  // Attend la fin du fils
        if (WIFEXITED(status)) {
            printf("Père : Mon fils avait le PID %d et il s'est terminé avec le code %d\n", pid, WEXITSTATUS(status));
        }
    }
    return 0;
}

