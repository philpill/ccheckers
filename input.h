#ifndef INPUT_H
#define INPUT_H

#include "game.h"
#include "piece.h"

extern char msg_log[5000][255];

char* get_last_msg();
void insert_msg(char *message);
void init_input(WINDOW **window);
int handle_input();
int get_input();
void output_msg();

#endif
