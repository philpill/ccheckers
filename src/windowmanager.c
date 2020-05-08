#include <ncurses.h>
#include "windowmanager.h"
#include "global.h"

WINDOW *get_windows(WINDOW **windows) {

    windows[0] = newwin(0, 0, 0, 0);
    windows[1] = derwin(windows[0], GRID_H, 42, 0, 0);
    windows[2] = derwin(windows[0], GRID_H, 42, 0, 42);
    windows[3] = derwin(windows[0], 5, 22, 5, 33);

    keypad(windows[2], TRUE);
    keypad(windows[3], TRUE);

    // https://stackoverflow.com/a/48277474
    notimeout(windows[2], TRUE);

    nodelay(windows[0], true);
    nodelay(windows[2], true);
}

void show_options_panel() {

}

void hide_options_panel() {

}

void delete_window(WINDOW *window) {

    wborder(window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(window);
    delwin(window);
}

void delete_windows(WINDOW **windows) {

    delete_window(windows[3]);
    delete_window(windows[1]);
    delete_window(windows[2]);
    delete_window(windows[0]);

    endwin();
}

