CC = gcc
CFLAGS = -Wall -pedantic -ansi -g
OBJ = main.o map.o game.o terminal.o fileIO.o linkedList.o enemy.o
EXEC = maze


$(EXEC) : $(OBJ)
		$(CC) $(OBJ) -o $(EXEC)

main.o : main.c game.h map.h fileIO.h linkedList.h
			$(CC) -c main.c $(CFLAGS)

game.o : game.c terminal.h game.h map.h linkedList.h enemy.h
			$(CC) -c game.c $(CFLAGS)

map.o : map.c map.h
			$(CC) -c map.c $(CFLAGS)

terminal.o : terminal.c terminal.h
			$(CC) -c terminal.c $(CFLAGS)

fileIO.o : fileIO.c fileIO.h map.h
			$(CC) -c fileIO.c $(CFLAGS)

linkedList.o : linkedList.c linkedList.h
			$(CC) -c linkedList.c $(CFLAGS)

enemy.o : enemy.c enemy.h
			$(CC) -c enemy.c $(CFLAGS)

clean :
			rm -f $(EXEC) $(OBJ)
