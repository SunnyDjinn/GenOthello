# Makefile

# Compiler
CC=gcc -c -g -Wall -std=c99

# Links edition
LD=gcc -o

# Library flags (-lm needed to use the math lib)
LFLAGS=-lm

# Dependencies 

all: othello

# .o files dependencies to make the Othello game (links edition)
othello: ai.o events.o game.o genetic.o graphics.o io.o othellier.o user.o move.o main.o
	$(LD) othello ai.o events.o game.o genetic.o graphics.o io.o othellier.o user.o move.o main.o $(LFLAGS)

# Dependencies to compile all files in .o files

# .c files and .h files dependencies to make ai.o
ai.o: ai.c ai.h constants.h graphics.h move.h othellier.h structures.h user.h 
	$(CC) ai.c

# .c files and .h files dependencies to make io.o
io.o: io.c io.h constants.h game.h move.h structures.h
	$(CC) io.c

# .c files and .h files dependencies to make events.o
events.o: events.c events.h ai.h constants.h graphics.h io.h othellier.h structures.h
	$(CC) events.c

# .c files and .h files dependencies to make genetic.o
genetic.o: genetic.c genetic.h constants.h structures.h
	$(CC) genetic.c
	
# .c files and .h files dependencies to make graphics.o
graphics.o: graphics.c graphics.h
	$(CC) graphics.c
	
# .c files and .h files dependencies to make game.o
game.o: game.c game.h ai.h graphics.h othellier.h  structures.h user.h constants.h
	$(CC) game.c

# .c files and .h files dependencies to make main.o	
main.o: main.c main.h constants.h events.h genetic.h graphics.h structures.h user.h
	$(CC) main.c

# .c files and .h files dependencies to make move.o	
move.o: move.c move.h constants.h io.h othellier.h structures.h
	$(CC) move.c

# .c files and .h files dependencies to make othellier.o	
othellier.o: othellier.c othellier.h constants.h structures.h
	$(CC) othellier.c

# .c files and .h files dependencies to make user.o
user.o: user.c user.h constants.h io.h structures.h
	$(CC) user.c

# .o files and executable deleting command
clean:
	rm -f othello *.o
