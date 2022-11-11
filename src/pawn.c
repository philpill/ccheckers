#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "pawn.h"
#include "input.h"
#include "log.h"
#include "resource.h"
#include "global.h"
#include "core.h"
#include "player.h"

Pawn* all_pawns = NULL;
static Game* game_data = NULL;

void get_state_by_pawns(int state[WIDTH][HEIGHT]) {
    int pawn = 0;
    for (int i = 0; i < NUM_PAWNS; i++) {
        if (!all_pawns[i].is_captured) {
            if (all_pawns[i].is_king) {
                pawn = all_pawns[i].colour == 0 ? 3 : 4;
            }
            else {
                pawn = all_pawns[i].colour == 0 ? 1 : 2;
            }
            state[all_pawns[i].position.y][all_pawns[i].position.x] = pawn;
        }
    }
}

/*
 * Check if a pawn is currently selected.
 *
 * @return true: pawn currently selected, false: nothing selected
 */
bool is_pawn_selected() {
    for (int i = 0; i < NUM_PAWNS; i++) {
        if (all_pawns[i].is_selected) {
            return true;
        }
    }
    return false;
}

/*
 * For want of a better name ...
 * Check if all of a player's pawns
 * have been captured
 *
 * @param  colour player to check pawns for
 * @return true: all pawns captured, else false
 */
bool is_player_dead(int colour) {
    bool is_dead = true;
    for (int i = 0; i < NUM_PAWNS; i++) {
        if ((all_pawns[i].colour == colour)
            && (!all_pawns[i].is_captured)) {
            is_dead = false;
        }
    }
    return is_dead;
}

/*
 * Check if pawn is currently selected
 *
 * @param  id pawn id
 * @return true if pawn with given id is currently selected
 *
 */
bool is_pawn_selected_by_id(int id) {
    for (int i = 0; i < NUM_PAWNS; i++) {
        if (all_pawns[i].id == id) {
            return all_pawns[i].is_selected;
        }
    }
    return false;
}

/*
 * Update pawn position with given values
 *
 * @param pawn pointer to pawn
 * @param x new x position to assign
 * @param y new y position to assign
 */
void move_pawn(Pawn* pawn, int x, int y) {
    log_fmsg("::move pawn: %d, %d\n", 2, x + 1, y + 1);
    pawn->x_pos = x;
    pawn->y_pos = y;
    pawn->position.x = x;
    pawn->position.y = y;
}

/*
 * Populate parameter with data if match is found
 * at coordinates
 *
 * @param  pawn memory allocated variable to populate with match
 * @param  x position to search
 * @param  y position to search
 * @return true if pawn found at given coordinates
 */
bool select_pawn_by_position(Pawn* pawn, int x, int y) {
    for (int i = 0; i < NUM_PAWNS; i++) {
        if ((all_pawns[i].x_pos == x) && (all_pawns[i].y_pos == y)) {
            pawn = &all_pawns[i];
            select_pawn(pawn);
            return true;
        }
    }
    return false;
}

/*
 * Get pointer to pawn at specified position
 *
 * @deprecated
 * @param  pawn pointer to pawn if found
 * @param  pos position
 * @return true if pawn is at position
 */
bool pawn_get_by_position(Pawn** pawn, Position pos) {
    // log_msg("get_pawn_by_position()");
    for (int i = 0; i < NUM_PAWNS; i++) {
        if ((all_pawns[i].x_pos == pos.x) && (all_pawns[i].y_pos == pos.y)) {
            // log_fmsg("::all_pawns[i].id: %d", 1, all_pawns[i].id);
            *pawn = &all_pawns[i];
            return true;
        }
    }
    return false;
}

/*
 * Get pointer to pawn at specified position
 *
 * @deprecated
 * @param  pawn pointer to pawn if found
 * @param  x x position
 * @param  y y position
 * @return true if pawn is at position
 */
bool get_pawn_by_position(Pawn** pawn, int x, int y) {
    Position pos;
    pos.x = x;
    pos.y = y;
    return pawn_get_by_position(pawn, pos);
}

/*
 * Select pawn and deselect all others
 *
 * @param pointer to pawn to select
 */
void select_pawn(Pawn* pawn) {
    // log_fmsg("::pointers: %d, %d", 2, pawn->x_pos, selected_pawn->x_pos);
    deselect_pawn();
    pawn->is_selected = true;
}

/*
 * Deselect all pawns
 */
void deselect_pawn() {
    // log_msg("deselect_pawn()");
    for (int i = 0; i < NUM_PAWNS; i++) {
        all_pawns[i].is_selected = false;
    }
}

/*
 * get pointer to last pawn in collection with selected flag set to true
 * or if no pawns are selected, return null pointer
 * @return Pawn
 */
Pawn* get_selected_pawn() {
    for (int i = 0; i < NUM_PAWNS; i++) {
        if (all_pawns[i].is_selected) {
            return &all_pawns[i];
        }
    }
    return NULL;
}

/*
 * Capture pawn at given position.
 * Possible segfault if there is no pawn
 * at position.
 *
 * @param  pos position of the pawn to capture
 * @return captured pawn
 */
Pawn* capture_pawn_at_position(Position* pos) {
    int x = pos->x;
    int y = pos->y;
    Pawn* pawn = NULL;
    if (get_pawn_by_position(&pawn, x, y)) {
        log_fmsg("::capture_pawn_at_position(): %d, [%d, %d]\n", 3, pawn->id, x, y);
        pawn->is_captured = true;
        pawn->x_pos = 0;
        pawn->y_pos = 0;
    }
    return pawn;
}


/*
 * Generate pawns from map data
 *
 * @param  map 2d array of map
 * @return number of pawns
 */
int load_pawns_from_map_data(int map[8][8]) {

    for (int k = 0; k < NUM_PAWNS; k++) {

        all_pawns[k].is_selected = false;
        all_pawns[k].is_captured = true;
        all_pawns[k].id = k;
        all_pawns[k].x_pos = 0;
        all_pawns[k].y_pos = 0;
        all_pawns[k].position = (Position){ .x = 0, .y = 0 };

        all_pawns[k].is_king = false;
        all_pawns[k].colour = 0;
        all_pawns[k].direction = 1;
    }

    int id = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            if (map[i][j] != 0) {

                all_pawns[id].is_captured = false;
                all_pawns[id].id = id + 1;
                all_pawns[id].x_pos = j;
                all_pawns[id].y_pos = i;
                all_pawns[id].position = (Position){ .x = j, .y = i };

                all_pawns[id].is_king = (map[i][j] == 3 || map[i][j] == 4);
                all_pawns[id].colour = (map[i][j] == 1 || map[i][j] == 3) ? 1 : 0;
                all_pawns[id].direction = all_pawns[id].colour == 1 ? 1 : -1;

                id++;
            }
        }
    }

    return id;
}

/*
 * Load initial pawn positions from file
 *
 * @param game struct containing game data including current turn
 * @param pawns memory-allocated array to fill with pawns data
 * @param filename file (without extension) to load pawn data
 * @param direction 1: moving down the board, -1: moving up
 * @return pawns count
 */
int init_pawn(Game* game, Pawn* pawns, char* filename, int direction) {
    int map[8][8];
    game_data = game;
    load_file(filename, map);
    //log_fmsg("init_pawns_by_file(): %d", 1, map[5][3]);
    all_pawns = pawns;
    int pawn_count = load_pawns_from_map_data(map);
    return pawn_count;
}

bool pawn_is_playable(Pawn* pawn) {
    return false;   
}

/*
 * Get all pawns which currently have a move
 *
 * @param pawns memory-allocated array to fill with pawns data
 * @return number of pawns which can be moved this turn
 */
int pawn_get_all_playable(Pawn* pawns) {
    int count = 0;
    for (int i = 0; i < NUM_PAWNS; i++) {
        if (pawn_is_playable(&(all_pawns[i]))) {
            pawns[count++] = all_pawns[i];
        }
    }
    return count;
}

bool pawn_can_move(Pawn* pawn) {
    return false;
}

bool pawn_is_owned_by_current_player(Pawn* pawn) {
    int current = game_data->player_colour;
    if (pawn->colour == current) {
        return true;
    }
    return false;
}

bool pawn_is_position_within_boundary(Position pos) {
    bool is_within = false;
    if ((pos.x > -1) 
        && (pos.x < 8)
        && (pos.y > -1)
        && (pos.y < 8)) {
        is_within = true;
    }
    return is_within;
}

bool pawn_is_position_valid(Position pos) {
    bool is_valid;
    Pawn **tmp = malloc(sizeof(Pawn));
    if (!pawn_is_position_within_boundary(pos)) {
        is_valid = false;
    }
    if (pawn_get_by_position(tmp, pos)) {
        is_valid = false;
    }
    free(tmp);
    return is_valid;
}

bool pawn_can_move_forward_right(Pawn* pawn) {
    bool can_move = true;
    Position proposed_pos;
    if (pawn->direction > 0) {
        proposed_pos.x = pawn->position.x - 1;
        proposed_pos.y = pawn->position.y + 1;
    }
    if (pawn->direction < 0) {
        proposed_pos.x = pawn->position.x + 1;
        proposed_pos.y = pawn->position.y - 1;
    }
    if (!pawn_is_position_valid(proposed_pos)) {
        can_move = false;
    }
    return can_move;
}

bool pawn_can_move_forward_left(Pawn* pawn) {
    bool can_move = true;
    Position proposed_pos;
    if (pawn->direction > 0) {
        proposed_pos.x = pawn->position.x + 1;
        proposed_pos.y = pawn->position.y + 1;
    }
    if (pawn->direction < 0) {
        proposed_pos.x = pawn->position.x - 1;
        proposed_pos.y = pawn->position.y - 1;
    }
    if (!pawn_is_position_valid(proposed_pos)) {
        can_move = false;
    }
    return can_move;
}







