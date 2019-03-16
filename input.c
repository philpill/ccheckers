#include <ncurses.h>
#include "game.h"
#include "input.h"
#include "piece.h"

void init_input() {
    keypad(stdscr, TRUE);
    noecho();
}

int  handle_input(WINDOW **windows, Game game, Piece pieces[]) {
    int exit = 0;

    wprintw(windows[2], "test"); 

    if (wgetch(windows[0]) == 27) {
        exit = 1;
    }
    return exit;
}
