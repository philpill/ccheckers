SHELL = /bin/sh
CC = gcc

all: compile run

run:
	./a.out

compile:
	${CC} *.c -lncurses -g

install:

clean:
	rm ./*gch ./*swp ./*swo ./a.out
