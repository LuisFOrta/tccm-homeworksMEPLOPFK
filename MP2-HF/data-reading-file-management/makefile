CC = gcc
CFLAGS = -Iinclude -I/usr/local/include -L/usr/local/lib -ltrexio -Wall -Wextra -std=c99

SRC = src/data_reader.c main.c
OBJ = $(SRC:.c=.o)
EXEC = main

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(CFLAGS)

clean:
	rm -f $(OBJ) $(EXEC)
