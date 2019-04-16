#include <ncurses.h>
#include "game.h"
#include "input.h"
#include "piece.h"

WINDOW *input_window;

void init_input(WINDOW *window) {
    input_window = window;
    keypad(stdscr, TRUE);
    noecho();
    nodelay(window, true);
}

int handle_input(WINDOW **windows) {
    int exit = 0;

    wprintw(windows[2], "test"); 

    if (wgetch(windows[0]) == 27) {
        exit = 1;
    }
    return exit;
}

int get_input() {
    return wgetch(input_window);
} 
