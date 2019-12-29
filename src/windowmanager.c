#include <ncurses.h>
#include "global.h"

WINDOW *get_windows(WINDOW **windows) {

    windows[0] = newwin(0, 0, 0, 0);

    windows[1] = derwin(windows[0], GRID_H, GRID_W, 0, 0);
    windows[2] = derwin(windows[0], GRID_H, GRID_W, 0, GRID_W+2);

    //windows[3] = derwin(windows[0], GRID_H-2, GRID_W*2-2, 1, 1);
}

void delete_window(WINDOW *window) {

    wborder(window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(window);
    delwin(window);
}

void delete_windows(WINDOW **windows) {

    delete_window(windows[1]);
    delete_window(windows[2]);
    delete_window(windows[3]);
    delete_window(windows[0]);
    endwin();
}

