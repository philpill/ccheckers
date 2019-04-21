#include <string.h>
#include <ncurses.h>
#include "game.h"
#include "input.h"
#include "piece.h"

WINDOW *input_window;

char msg_log[5000][255];

int msg_ctr = 0;

void insert_msg(char *message) {
    strcpy(msg_log[msg_ctr], message);
    msg_ctr++;
}

char* get_last_msg() {
    return msg_log[msg_ctr-1];
}

void init_input(WINDOW *window) {
    input_window = window;
    keypad(stdscr, TRUE);
    noecho();
    nodelay(window, true);
    insert_msg("xtest1");
}

int handle_input(WINDOW **windows) {
    int exit = 0;

    // wprintw(windows[2], "test"); 

    wprintw(windows[2], get_last_msg());

    if (wgetch(windows[0]) == 27) {
        exit = 1;
    }
    return exit;
}

int get_input() {
    return wgetch(input_window);
} 
