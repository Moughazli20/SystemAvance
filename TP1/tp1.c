#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>
#include <errno.h>

void copy_file(const char *src, const char *dest) {
    int fd_src, fd_dest;
    char buffer[1024];
    ssize_t bytes_read, bytes_written;

    fd_src = open(src, O_RDONLY);
    if (fd_src < 0) {
        perror("Erreur lors de l'ouverture du fichier source");
        return;
    }

    fd_dest = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_dest < 0) {
        perror("Erreur lors de la création du fichier destination");
        close(fd_src);
        return;
    }

    while ((bytes_read = read(fd_src, buffer, sizeof(buffer))) > 0) {
        bytes_written = write(fd_dest, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Erreur lors de l'écriture dans le fichier destination");
            close(fd_src);
            close(fd_dest);
            return;
        }
    }

    if (bytes_read < 0) {
        perror("Erreur lors de la lecture du fichier source");
    }

    close(fd_src);
    close(fd_dest);
}

void print_reverse(const char *filename) {
    int fd;
    off_t file_size;
    char ch;

    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    file_size = lseek(fd, 0, SEEK_END);
    if (file_size == -1) {
        perror("Erreur lors de l'utilisation de lseek");
        close(fd);
        return;
    }

    for (off_t i = file_size - 1; i >= 0; i--) {
        if (lseek(fd, i, SEEK_SET) == -1) {
            perror("Erreur lors de l'utilisation de lseek");
            close(fd);
            return;
        }
        if (read(fd, &ch, 1) != 1) {
            perror("Erreur lors de la lecture du fichier");
            close(fd);
            return;
        }
        write(STDOUT_FILENO, &ch, 1);
    }
    close(fd);
}

void ls_like(const char *path) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    char full_path[1024];

    dir = opendir(path);
    if (dir == NULL) {
        perror("Erreur lors de l'ouverture du répertoire");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        if (stat(full_path, &file_stat) == -1) {
            perror("Erreur lors de l'obtention des informations sur le fichier");
            continue;
        }

        struct passwd *pw = getpwuid(file_stat.st_uid);
        struct group *gr = getgrgid(file_stat.st_gid);

        char time_buf[64];
        struct tm *tm = localtime(&file_stat.st_mtime);
        strftime(time_buf, sizeof(time_buf), "%d%m%y @ %Hh%M", tm);

        printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
        printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
        printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
        printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
        printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
        printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
        printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
        printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
        printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
        printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");

        printf(" %s : %s - %ld - %s - %s\n",
               pw ? pw->pw_name : "unknown",
               gr ? gr->gr_name : "unknown",
               file_stat.st_size,
               time_buf,
               entry->d_name);
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <commande> <fichier/source> [destination]\n", argv[0]);
        fprintf(stderr, "Commandes disponibles: copy, reverse, ls\n");
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "copy") == 0) {
        if (argc < 4) {
            fprintf(stderr, "Usage: %s copy <source> <destination>\n", argv[0]);
            return EXIT_FAILURE;
        }
        copy_file(argv[2], argv[3]);
    } else if (strcmp(argv[1], "reverse") == 0) {
        print_reverse(argv[2]);
    } else if (strcmp(argv[1], "ls") == 0) {
        ls_like(argv[2]);
    } else {
        fprintf(stderr, "Commande inconnue: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
