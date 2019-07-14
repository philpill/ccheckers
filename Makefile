SHELL = /bin/sh
CC = gcc

all: build run

run:
	./a.out

build:
	${CC} *.c -lncurses

debug:
	${CC} *.c -lncurses -g && gdb a.out

install:

clean:
	rm ./*gch ./*swp ./*swo ./a.out
