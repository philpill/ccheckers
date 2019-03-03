#ifndef INPUT_H
#define INPUT_H

#include <ncurses.h>
#include "game.h"
#include "piece.h"

char* get_last_msg();
void insert_msg(char *message);
void init_input(WINDOW **window);
int handle_input();
int get_input();
void output_msg();

#endif
