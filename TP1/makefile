# Nom de l'exécutable
TARGET = tp1

# Compilateur et options de compilation
CC = gcc
CFLAGS = -Wall -Wextra -g

# Fichiers source (all .c files in the current directory)
SRC = $(wildcard *.c)

# Fichiers objets (all corresponding .o files)
OBJ = $(SRC:.c=.o)

# Règle par défaut pour compiler le programme
all: $(TARGET)

# Règle pour créer l'exécutable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Règle pour compiler les fichiers objets
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers générés
clean:
	rm -f $(OBJ) $(TARGET)

# Règle pour forcer la recompilation
.PHONY: all clean
