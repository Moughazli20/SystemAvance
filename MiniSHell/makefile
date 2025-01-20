# Variables
CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = 
SRC = main.c commands.c utils.c
OBJ = $(SRC:.c=.o)
TARGET = minishell

# Règles
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

fclean: clean

re: fclean all

# PHONY pour éviter les conflits avec des fichiers du même nom
.PHONY: all clean fclean re

