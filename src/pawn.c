#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "pawn.h"
#include "input.h"
#include "log.h"
#include "resource.h"
#include "global.h"
#include "core.h"

Pawn *all_pawns = NULL;
Pawn *selected_pawn = NULL;
static Game *game_data = NULL;

bool is_selected = false;

void get_state_by_pawns(int state[WIDTH][HEIGHT]) {
    int pawn = 0;
    for (int i = 0; i < 24; i++) {
        if (!all_pawns[i].is_captured) {
            if (all_pawns[i].is_king) {
                pawn = all_pawns[i].colour == 0 ? 3 : 4;
            } else {
                pawn = all_pawns[i].colour == 0 ? 1 : 2;
            }
            state[all_pawns[i].y_pos][all_pawns[i].x_pos] = pawn;
        }
    }
}

/*
 * Check if a pawn is currently selected.
 * Needs refactoring to use bool type
 *
 * @return true: pawn currently selected, false: nothing selected
 */
bool is_pawn_selected() {
    return is_selected;
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
    int all_pawns_len = 24;
    for (int i = 0; i < all_pawns_len; i++) {
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
    bool is_pawn_selected = false;
    if (is_selected) {
        if (id == selected_pawn->id) {
            is_pawn_selected = true;
        }
    }
    return is_pawn_selected;
}

/*
 * Update pawn position with given values
 *
 * @param pawn pointer to pawn
 * @param x new x position to assign
 * @param y new y position to assign
 */
void move_pawn(Pawn *pawn, int x, int y) {
    log_fmsg("::move pawn: %d, %d\n", 2, x+1, y+1);
    pawn->x_pos = x;
    pawn->y_pos = y;
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
bool select_pawn_by_position(Pawn *pawn, int x, int y) {
    for (int i = 0; i < 24; i++) {
        if ((all_pawns[i].x_pos == x) && (all_pawns[i].y_pos == y)) {
            pawn = &all_pawns[i];
            select_pawn(pawn);
            return true;
        }
    }
    return false;
}

void select_pawn(Pawn *pawn) {
    selected_pawn = pawn;
    // log_fmsg("::pointers: %d, %d", 2, pawn->x_pos, selected_pawn->x_pos);
    is_selected = true;
}

void deselect_pawn() {
    // log_msg("deselect_pawn()");
    selected_pawn = NULL;
    is_selected = false;
}

/*
 * Get pointer to pawn at specified position
 *
 * @param  pawn pointer to pawn if found
 * @param  x x position
 * @param  y y position
 * @return true if pawn is at position
 */
bool get_pawn_by_position(Pawn **pawn, int x, int y) {
    // log_msg("get_pawn_by_position()");
    for (int i = 0; i < 24; i++) {
        if ((all_pawns[i].x_pos == x) && (all_pawns[i].y_pos == y)) {
            // log_fmsg("::all_pawns[i].id: %d", 1, all_pawns[i].id);
            *pawn = &all_pawns[i];
            return true;
        }
    }
    return false;
}

Pawn *get_selected_pawn() {
    return selected_pawn;
}

/*
 * Capture pawn at given position.
 * Possible segfault if there is no pawn
 * at position.
 *
 * @param  pos position of the pawn to capture
 * @return captured pawn
 */
Pawn *capture_pawn_at_position(Position *pos) {
    int x = pos->x;
    int y = pos->y;
    Pawn *pawn = 0;
    if (get_pawn_by_position(&pawn, x, y)) {
        log_fmsg("::capture_pawn_at_position(): %d, [%d, %d]\n", 3, pawn->id, x, y);
        pawn->is_captured = true;
        pawn->x_pos = 0;
        pawn->y_pos = 0;
    }
    return pawn;
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
int init_pawn(Game *game, Pawn *pawns, char *filename, int direction) {

    int map[8][8];

    game_data = game;

    load_file(filename, map);

    //log_fmsg("init_pawns_by_file(): %d", 1, map[5][3]);

    all_pawns = pawns;

    for (int k = 0; k < 24; k++) {

        pawns[k].is_captured = true;
        pawns[k].id = k;
        pawns[k].x_pos = 0;
        pawns[k].y_pos = 0;
        pawns[k].position = (Position){ .x = 0, .y = 0 };

        pawns[k].is_king = false;
        pawns[k].colour = 0;
        pawns[k].direction = 1;
    }

    int id = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            if (map[i][j] != 0) {

                pawns[id].is_captured = false;
                pawns[id].id = id + 1;
                pawns[id].x_pos = j;
                pawns[id].y_pos = i;
                pawns[id].position = (Position){ .x = j, .y = i };

                pawns[id].is_king = (map[i][j] == 3 || map[i][j] == 4);
                pawns[id].colour = (map[i][j] == 1 || map[i][j] == 3) ? 1 : 0;
                pawns[id].direction = pawns[id].colour == 1 ? 1 : -1;

                id++;
            }
        }
    }

    return id;
}