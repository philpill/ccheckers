
#ifndef RENDER_H
#define RENDER_H

#include <ncurses.h>

void init_render(WINDOW **render_windows);

void render_board(Pawn *pawns);
void render_text();
void render_menu();
void quit_render();

#endif
