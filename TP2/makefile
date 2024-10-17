# Makefile pour le TP Systèmes d'exploitation - Appels systèmes et processus

# Compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -Wextra -std=c99

# Fichiers sources
SRC_FORK = fork_example.c
SRC_REDIRECTION = redirection_example.c
SRC_AFFICHE = affiche.c
SRC_PIPE = pipe_example.c

# Noms des exécutables
EXE_FORK = fork_example
EXE_REDIRECTION = redirection_example
EXE_AFFICHE = affiche
EXE_PIPE = pipe_example

# Cibles par défaut : Compile tout
all: $(EXE_FORK) $(EXE_REDIRECTION) $(EXE_AFFICHE) $(EXE_PIPE)

# Compilation du programme "Fork yourself"
$(EXE_FORK): $(SRC_FORK)
	$(CC) $(CFLAGS) -o $(EXE_FORK) $(SRC_FORK)

# Compilation du programme pour la redirection de flux
$(EXE_REDIRECTION): $(SRC_REDIRECTION)
	$(CC) $(CFLAGS) -o $(EXE_REDIRECTION) $(SRC_REDIRECTION)

# Compilation du programme "affiche"
$(EXE_AFFICHE): $(SRC_AFFICHE)
	$(CC) $(CFLAGS) -o $(EXE_AFFICHE) $(SRC_AFFICHE)

# Compilation du programme pour le pipe et redirection
$(EXE_PIPE): $(SRC_PIPE)
	$(CC) $(CFLAGS) -o $(EXE_PIPE) $(SRC_PIPE)

# Nettoyage des fichiers générés
clean:
	rm -f $(EXE_FORK) $(EXE_REDIRECTION) $(EXE_AFFICHE) $(EXE_PIPE)

# Exécute les tests pour chaque programme
test: all
	@echo "Test Fork Example:"
	./$(EXE_FORK)
	@echo "Test Redirection Example:"
	./$(EXE_REDIRECTION) ./$(EXE_AFFICHE)
	@echo "Vérification du fichier /tmp/proc-exercise:"
	cat /tmp/proc-exercise
	@echo "Test Pipe Example:"
	./$(EXE_PIPE)

# Clean + Rebuild
rebuild: clean all

