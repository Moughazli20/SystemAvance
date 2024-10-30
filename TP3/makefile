# Nom de l'exécutable
TARGET = threaded_sort

# Compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -O2
LDFLAGS = -lpthread

# Liste des fichiers source
SRCS = threaded_sort.c

# Règle principale pour construire l'exécutable
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)

# Règle pour exécuter le programme
run: $(TARGET)
	./$(TARGET)

# Règle pour nettoyer les fichiers compilés
clean:
	rm -f $(TARGET)

# Indique que clean et run ne sont pas des fichiers
.PHONY: clean run

