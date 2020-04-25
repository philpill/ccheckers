#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <stdbool.h>

typedef struct {
    bool is_visible;
} PANEL_DATA;

PANEL *get_panels(PANEL **panels);

void delete_windows(PANEL **panels);

void delete_window(WINDOW *windows);

void show_options_panel();

void hide_options_panel();

bool is_options_panel_hidden(PANEL *panel);

#endif
