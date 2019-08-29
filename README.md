sudo apt-get install libc6-dev libncurses5-dev

vim *.c *.h test/*.c
gcc *.c -lncurses

debug
gcc *.c -lncurses -g


cmocka
gcc ./test/*.c -lcmocka -lncurses && ./test/a.out
