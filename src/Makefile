
# Vars
CC = gcc 
CFLAGS = -Wall -pedantic -ansi -Werror -std=c89 -g
EXEC = game
OBJS = main.o file_io.o game.o ui.o linked_list.o log.o
BIN_DIR = ../bin

$(EXEC) : $(OBJS) $(BIN_DIR)
	$(CC) $(OBJS) -o $(BIN_DIR)/$(EXEC)

$(BIN_DIR) :
	mkdir $(BIN_DIR)

main.o : main.c
	$(CC) -c main.c $(CFLAGS)

file_io.o : file_io.c file_io.h
	$(CC) -c file_io.c $(CFLAGS)

game.o : game.c game.h 
	$(CC) -c game.c $(CFLAGS)

ui.o : ui.c ui.h 
	$(CC) -c ui.c $(CFLAGS)

linked_list.o : linked_list.c linked_list.h
	$(CC) -c linked_list.c $(CFLAGS)

log.o : log.c log.h 
	$(CC) -c log.c $(CFLAGS)

clean :
	rm -f $(OBJS) $(BIN_DIR)/$(EXEC)
