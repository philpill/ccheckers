#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "piece.h"
#include "input.h"
#include "log.h"
#include "resource.h"
#include "global.h"
#include "core.h"

Piece *all_pieces = NULL;
Piece *selected_piece = NULL;
Game *game_data = NULL;

bool is_selected = false;

void get_state_by_pieces(int state[WIDTH][HEIGHT]) {
    int piece = 0;
    for (int i = 0; i < 24; i++) {
        if (!all_pieces[i].is_captured) {
            if (all_pieces[i].is_king) {
                piece = all_pieces[i].colour == 0 ? 2 : 4;
            } else {
                piece = all_pieces[i].colour == 0 ? 1 : 3;
            }
        }
        state[all_pieces[i].y_pos][all_pieces[i].x_pos] = piece;
    }
}

/*
 * Check if a piece is currently selected.
 * Needs refactoring to use bool type
 *
 * @return true: piece currently selected, false: nothing selected
 */
bool is_piece_selected() {
    return is_selected;
}

/*
 * For want of a better name ...
 * Check if all of a player's pieces
 * have been captured
 *
 * @param  colour player to check pieces for
 * @return true: all pieces captured, else false
 */
bool is_player_dead(int colour) {
    bool is_dead = true;
    int all_pieces_len = 24;
    for (int i = 0; i < all_pieces_len; i++) {
        if ((all_pieces[i].colour == colour)
            && (!all_pieces[i].is_captured)) {
                is_dead = false;
            }
    }
    return is_dead;
}

/*
 * Check if piece is currently selected
 *
 * @param  id piece id
 * @return true if piece with given id is currently selected
 *
 */
bool is_piece_selected_by_id(int id) {
    bool is_piece_selected = false;
    if (is_selected) {
        if (id == selected_piece->id) {
            is_piece_selected = true;
        }
    }
    return is_piece_selected;
}

/*
 * Update piece position with given values
 *
 * @param piece pointer to piece
 * @param x new x position to assign
 * @param y new y position to assign
 */
void move_piece(Piece *piece, int x, int y) {
    log_fmsg("::move piece: %d, %d\n", 2, x+1, y+1);
    piece->x_pos = x;
    piece->y_pos = y;
}

/*
 * Populate parameter with data if match is found
 * at coordinates
 *
 * @param  piece memory allocated variable to populate with match
 * @param  x position to search
 * @param  y position to search
 * @return true if piece found at given coordinates
 */
bool select_piece_by_position(Piece *piece, int x, int y) {
    for (int i = 0; i < 24; i++) {
        if ((all_pieces[i].x_pos == x) && (all_pieces[i].y_pos == y)) {
            piece = &all_pieces[i];
            select_piece(piece);
            return true;
        }
    }
    return false;
}

void select_piece(Piece *piece) {
    selected_piece = piece;
    // log_fmsg("::pointers: %d, %d", 2, piece->x_pos, selected_piece->x_pos);
    is_selected = true;
}

void deselect_piece() {
    // log_msg("deselect_piece()");
    selected_piece = NULL;
    is_selected = false;
}

/*
 * Get pointer to piece at specified position
 *
 * @param  piece pointer to piece if found
 * @param  x x position
 * @param  y y position
 * @return true if piece is at position
 */
bool get_piece_by_position(Piece **piece, int x, int y) {
    *piece = malloc (sizeof (Piece));
    // log_msg("get_piece_by_position()");
    for (int i = 0; i < 24; i++) {
        if ((all_pieces[i].x_pos == x) && (all_pieces[i].y_pos == y)) {
            // log_fmsg("::all_pieces[i].id: %d", 1, all_pieces[i].id);
            *piece = &all_pieces[i];
            return true;
        }
    }
    return false;
}

Piece *get_selected_piece() {
    return selected_piece;
}

/*
 * Capture piece at given position.
 * Possible segfault if there is no piece
 * at position.
 *
 * @param  pos position of the piece to capture
 * @return captured piece
 */
Piece *capture_piece_at_position(Position *pos) {
    int x = pos->x;
    int y = pos->y;
    Piece *piece = 0;
    if (get_piece_by_position(&piece, x, y)) {
        log_fmsg("::capture_piece_at_position(): %d, [%d, %d]\n", 3, piece->id, x, y);
        piece->is_captured = true;
        piece->x_pos = 0;
        piece->y_pos = 0;
    }
    return piece;
}

/*
 * Load initial piece positions from file
 *
 * @param game struct containing game data including current turn
 * @param pieces memory-allocated array to fill with pieces data
 * @param filename file (without extension) to load piece data
 * @param direction 1: moving down the board, -1: moving up
 */
void init_piece(Game *game, Piece *pieces, char *filename, int direction) {

    int map[8][8];

    game_data = game;

    load_file(filename, map);

    //log_fmsg("init_pieces_by_file(): %d", 1, map[5][3]);

    all_pieces = pieces;

    selected_piece = malloc(sizeof(Piece));

    int id = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            if (map[i][j] != 0) {

                pieces[id].is_captured = false;
                pieces[id].id = id + 1;
                pieces[id].x_pos = j;
                pieces[id].y_pos = i;
                pieces[id].position = (Position){ .x = j, .y = i };

                pieces[id].is_king = (map[i][j] == 3 || map[i][j] == 4);
                pieces[id].colour = (map[i][j] == 1 || map[i][j] == 3) ? 1 : 0;
                pieces[id].direction = pieces[id].colour == 1 ? 1 : -1;

                id++;
            }
        }
    }
}