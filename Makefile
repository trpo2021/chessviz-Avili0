CC=gcc
Cflags= -c -Wall -Werror

all: chessviz

chessviz: chessboard.o main.o
	$(CC) main.o chessboard.o -o chessviz
	 
chessboard.o: chessboard.c
	$(CC) $(Cflags) chessboard.c

main.o: main.c
	$(CC) $(Cflags) main.c

clean:
	rm-rf *.o chessviz