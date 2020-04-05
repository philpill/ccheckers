
#ifndef RENDER_H
#define RENDER_H

#include <ncurses.h>
#include <panel.h>

void init_render(PANEL **render_panels);

void render_board(Piece *pieces);
void render_text();
void render_menu();
void quit_render();

#endif
