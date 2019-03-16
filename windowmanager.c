#include <ncurses.h>

WINDOW *get_windows(WINDOW **windows) {

    windows[0] = newwin(0, 0, 0, 0);

    windows[1] = subwin(windows[0], 20, 40, 2, 2);
    windows[2] = subwin(windows[0], 20, 10, 45, 2);
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

