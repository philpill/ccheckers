#ifndef PLAYER_H
#define PLAYER_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int id;
    char* name;
    char marker;
} Player;

char    set_player_marker_by_id(int id);
int     get_num_players();
Player* get_players();
void    destroy_player();
void    each_player(void (*fn)(Player player));
void    get_player_by_id(int id, Player *player);
void    init_player();
void    set_player_name_by_id(int id, char *name);

#endif