CFLAGS=-std=gnu99
SHELL = /bin/sh
CC = gcc

all: build run

run:
	./bin/ccheckers

build:
	${CC} $(CFLAGS) src/*.c -Iinclude -lpanel -lncursesw -lcmocka -g -o ./bin/ccheckers

debug:
	${CC} $(CFLAGS) src/*.c -Iinclude -lpanel -lncursesw -lcmocka -g -o ./bin/ccheckers && gdb ./bin/ccheckers -tui

install:
	mkdir log bin; sudo apt-get install libncursesw5-dev libncurses5-dev libcmocka-dev valgrind

memcheck:
	valgrind --leak-check=yes ./bin/ccheckers

clean:
	rm ./*gch ./*swp ./*swo ./bin/* ./log/*

run_test:
	gcc -Iinclude ./src/core.c ./src/file.c ./src/game.c ./src/global.c ./src/input.c ./src/log.c ./src/options.c ./src/pawn.c ./src/player.c ./src/render.c ./src/resource.c ./src/utilities.c ./src/windowmanager.c ./src/test/*.c -lcmocka -lpanel -lncursesw -o ./bin/cc_tests && ./bin/cc_tests
