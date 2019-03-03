
#ifndef RENDER_H
#define RENDER_H

#include <ncurses.h>

WINDOW *init_render();

void render(WINDOW *board_win, Game game, Piece pieces[]);

void quit_render();

#endif
