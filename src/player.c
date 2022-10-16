#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "player.h"

static int num_players = 2;
static int max_len_player_name = 255;

static Player* players;

void init_player() {
    players = malloc(num_players * sizeof(Player));
    for (int i = 0;i < num_players;i++) {
        players[i].id = i + 1;
        players[i].name = malloc(max_len_player_name * sizeof(char));
    }

    players[0].name = "alex";
    players[0].marker = 'a';
    players[1].name = "ben";
    players[1].marker = 'b';
}

int get_num_players() {
    return num_players;
}

Player* get_players() {
    return players;
}

void get_player_by_id(int id, Player *player) {
    for (int i = 0;i < num_players;i++) {
        if (players[i].id == id) {
            *player = players[i];
        }
    }
}

void set_player_name_by_id(int id, char *name) {
    for (int i = 0;i < num_players;i++) {
        if (players[i].id = id) {
            strcpy(players[i].name, name);
        }
    }
}

char set_player_marker_by_id(int id) {
    for (int i = 0;i < num_players;i++) {
        if (players[i].id = id) {
            return players[i].marker;
        }
    }
    return ' ';
}

void destroy_player() {
    for (int i = 0;i < num_players;i++) {
        players[i].name = NULL;
        free(players[i].name);
    }
    players = NULL;
    free(players);
}

void each_player(void (*fn)(Player player)) {
    for (int i = 0;i < num_players;i++) {
        fn(players[i]);
    }
}