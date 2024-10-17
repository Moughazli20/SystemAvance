/*#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <message>\n", argv[0]);
        return 1;
    }
    printf("Message: %s\n", argv[1]);
    return 0;
}*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <programme_a_executer>\n", argv[0]);
        return 1;
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // Processus fils
        printf("Fils : Mon PID est %d\n", getpid());
        
        // Fermer le descripteur STDOUT (1)
        close(1);

        // Créer et ouvrir un fichier temporaire
        int fd = open("/tmp/proc-exercise", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) {
            perror("open failed");
            return 1;
        }
        printf("Descripteur fichier ouvert : %d\n", fd);

        // Rediriger STDOUT vers ce fichier
        dup2(fd, 1);

        // Exécuter le programme passé en argument (argv[1])
        execlp(argv[1], argv[1], NULL);
        // Si execlp échoue
        perror("exec failed");
        return 1;
    } else {
        // Processus père
        printf("Père : Mon PID est %d\n", getpid());

        // Attendre la fin du processus fils
        wait(NULL);
        printf("Père : That's All Folks!\n");
    }

    return 0;
}

