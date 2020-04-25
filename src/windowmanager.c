#include <ncurses.h>
#include <panel.h>
#include "windowmanager.h"
#include "global.h"

PANEL_DATA panel_data[3];

PANEL *options_panel;

PANEL *get_panels(PANEL **panels) {

    WINDOW *windows[4];

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

    panels[0] = new_panel(windows[0]);
    panels[1] = new_panel(windows[1]);
    panels[2] = new_panel(windows[2]);
    panels[3] = new_panel(windows[3]);

    options_panel = panels[3];

    panel_data[0].is_visible = true;
    panel_data[1].is_visible = true;
    panel_data[2].is_visible = true;
    panel_data[3].is_visible = false;

    set_panel_userptr(panels[0], &panel_data[0]);
    set_panel_userptr(panels[1], &panel_data[1]);
    set_panel_userptr(panels[2], &panel_data[2]);
    set_panel_userptr(panels[3], &panel_data[3]);

    hide_panel(panels[3]);

    update_panels();
}

void show_options_panel() {
    panel_data[3].is_visible = true;
    show_panel(options_panel);
    update_panels();
    curs_set(0);
}

void hide_options_panel() {
    panel_data[3].is_visible = false;
    hide_panel(options_panel);
    update_panels();
    curs_set(1);
}

bool is_options_panel_hidden(PANEL *panel) {
    return panel_hidden(panel);
}

void delete_window(WINDOW *window) {

    wborder(window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(window);
    delwin(window);
}

void delete_windows(PANEL **panels) {

    delete_window(panels[3]->win);
    delete_window(panels[1]->win);
    delete_window(panels[2]->win);
    delete_window(panels[0]->win);

    del_panel(panels[0]);
    del_panel(panels[1]);
    del_panel(panels[2]);
    del_panel(panels[3]);

    endwin();
}

