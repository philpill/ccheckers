
#ifndef RENDER_H
#define RENDER_H

#include <ncurses.h>

void init_render(WINDOW **render_windows);

void render(Game game, Piece *pieces);
void render_text();
void quit_render();

#endif
