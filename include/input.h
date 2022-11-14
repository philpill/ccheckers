#ifndef INPUT_H
#define INPUT_H

#include <ncurses.h>
#include <panel.h>
#include "game.h"
#include "pawn.h"

char* input_get_last_msg();
void  input_insert_msg(char *message);
void  input_init(Game *new_game, PANEL **panels);
int   input_handle();
int   input_get_input();
void  input_output_msg();

#endif
