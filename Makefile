CFLAGS=-std=gnu99
SHELL = /bin/sh
CC = gcc

all: build run

run:
	./a.out

build:
	${CC} $(CFLAGS) *.c -lncursesw -lcmocka

debug:
	${CC} $(CFLAGS) *.c -lncursesw -lcmocka -g && gdb a.out

install:
	sudo apt-get install libncursesw5-dev libcmocka-dev valgrind

memcheck:
	valgrind --leak-check=yes ./a.out

clean:
	rm ./*gch ./*swp ./*swo ./a.out

run_test:
	gcc ./test/*.c -lcmocka -lncurses && ./a.out