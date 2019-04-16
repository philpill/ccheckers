#ifndef INPUT_H
#define INPUT_H

#include "game.h"
#include "piece.h"

extern char *msg_log[255];

void init_input(WINDOW *window);
int handle_input(WINDOW **windows);
int get_input();

#endif
