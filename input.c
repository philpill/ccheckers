#include <ncurses.h>
#include "game.h"
#include "input.h"
#include "piece.h"

void init_input() {
    keypad(stdscr, TRUE);
    noecho();
}

int handle_input(WINDOW *input_win, Game game, Piece pieces[]) {
    int exit = 0;
    if (wgetch(input_win) == 27) {
        exit = 1;
    }
    return exit;
}
