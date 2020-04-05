#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

typedef struct {
    bool is_visible;
} PANEL_DATA;

PANEL *get_panels(PANEL **panels);

void delete_windows(PANEL **panels);

void delete_window(WINDOW *windows);

void show_settings_panel(PANEL *panel);

void hide_settings_panel(PANEL *panel);

bool is_settings_panel_hidden(PANEL *panel);

#endif
