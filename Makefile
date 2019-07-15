SHELL = /bin/sh
CC = gcc

all: build run

run:
	./a.out

build:
	${CC} *.c -lncursesw

debug:
	${CC} *.c -lncursesw -g && gdb a.out

install:

clean:
	rm ./*gch ./*swp ./*swo ./a.out
