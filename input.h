#ifndef INPUT_H
#define INPUT_H

#include "game.h"
#include "piece.h"

void init_input();
int handle_input(WINDOW **windows, Game game, Piece pieces[]);

#endif
