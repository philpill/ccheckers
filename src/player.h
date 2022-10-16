#ifndef PLAYER_H
#define PLAYER_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int id;
    char *name;
    char *marker;
} Player;

void init_player();
void get_player_by_id(int id, Player player);
void set_player_name_by_id(int id, char *name);
void set_player_marker_by_id(int id, char *marker);
void destroy_player();
void each_player(void (*fn)(Player player));

#endif