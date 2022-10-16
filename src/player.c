#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "player.h"

static int num_players = 2;
static int max_len_player_name = 255;
static int max_len_player_marker = 3;

static Player *players;

void init_player() {
    //players = malloc(num_players*sizeof(Player));
    // for(int i=0;i<num_players;i++) {
        // players[i].id = i+1;
        // players[i].name = malloc(max_len_player_name*sizeof(char));
        // players[i].marker = malloc(max_len_player_marker*sizeof(char));
    // }
}

void get_player_by_id(int id, Player player) {
    for(int i=0;i<num_players;i++){
        if (players[i].id == id){
            player = players[i];
        }
    }
}

void set_player_name_by_id(int id, char *name) {
    for(int i=0;i<num_players;i++){
        if (players[i].id = id) {
            strcpy(players[i].name, name);
        }
    }
}

void set_player_marker_by_id(int id, char *marker) {
    for(int i=0;i<num_players;i++){
        if (players[i].id = id) {
            strcpy(players[i].marker, marker);
        }
    }
}

void destroy_player() {
    for(int i=0;i<num_players;i++){
        free(players[i].name);
        free(players[i].marker);
    }
    free(players);
}

void each_player(void (*fn)(Player player)) {
    for(int i=0;i<num_players;i++){
        fn(players[i]);
    }
}