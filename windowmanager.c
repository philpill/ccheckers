#include <ncurses.h>

WINDOW *get_windows(WINDOW **windows) {

    windows[0] = newwin(0, 0, 0, 0);

    windows[1] = derwin(windows[0], 18, 36, 0, 0);
    windows[2] = derwin(windows[0], 3, 36, 18, 0);
}

void delete_window(WINDOW *window) {

    wborder(window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(window);
    delwin(window);
}

void delete_windows(WINDOW **windows) {

    delete_window(windows[1]);
    delete_window(windows[2]);
    delete_window(windows[0]);
    endwin();
}

