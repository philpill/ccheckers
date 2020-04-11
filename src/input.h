#ifndef INPUT_H
#define INPUT_H

#include <ncurses.h>
#include <panel.h>
#include "game.h"
#include "pawn.h"

char* get_last_msg();
void insert_msg(char *message);
void init_input(Game *new_game, PANEL **panels);
int handle_input();
int get_input();
void output_msg();
int get_selected_option();

#endif
