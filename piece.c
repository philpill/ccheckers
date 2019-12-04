#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "piece.h"
#include "input.h"
#include "log.h"
#include "resource.h"
#include "global.h"

Piece *all_pieces = NULL;
Piece *selected_piece = NULL;
Game *game_data = NULL;

bool is_selected = false;

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
 * Positive/negative refers to grid numbers
 *
 * @param  colour the colour to check
 * @return true: positive/forwards, false: negative/backwards
 */
bool is_positive_movement(int colour) {
    // log_fmsg("is_positive_movement(): %d", 1, colour);
    return colour == game_data->player_positive_move;
}

/*
 * Check if new, proposed position is
 * a jump move.
 * Jump moves are two squares up/down
 * and two squares left/right
 *
 * @param  curr_pos current piece position
 * @param  new_pos  new piece position
 * @return false - not jump move, true - is jump move
 */
bool is_jump_move(Position *curr_pos, Position *new_pos) {
    int pos_x = curr_pos->x;
	int pos_y = curr_pos->y;
	int new_x = new_pos->x;
	int new_y = new_pos->y;
	return ((abs(new_x-pos_x) == 2) && (abs(new_y-pos_y) == 2));
}

/*
 * If move is one of four valid jump moves,
 * check intervening square is occupied
 * by not-owned piece.
 * (check to be implemented)
 *
 * @param  curr_pos current piece position
 * @param  new_pos  new piece position
 * @param  dx       x direction - 1 or -1
 * @param  dy       y direction - 1 or -1
 * @return 0 - not valid, 1 - is valid
 */
bool is_valid_jump_move(Position *curr_pos, Position *new_pos, int dx, int dy) {

    int adj_x = (curr_pos->x+new_pos->x)/2;
	int adj_y = (curr_pos->y+new_pos->y)/2;
    Piece *piece = 0;

	// 2 squares up/down and 2 squares left/right
	if (!is_jump_move(curr_pos, new_pos)) {
        log_msg("::not valid jump move");
		return false;
	}
	// there must be a piece to jump over
	if (!get_piece_by_position(&piece, adj_x, adj_y)) {
        log_fmsg("::no intervening piece: %d, %d", 2, adj_x, adj_y);
		return false;
	}

	// checked piece is opposing
	// cannot jump over own piece
	if (piece->colour == selected_piece->colour) {
        log_msg("::intervening piece is friendly");
		return false;
	}
	return true;
}

// check x+1, y+1 for x+2, y+2
// check x-1 y+1 for x-2 y+2
// check x+1 y-1 for x+2 y-2
// check x-1 y-1 for x-2 y-2
bool is_valid_jump(Position *curr_pos, Position *new_pos) {

    bool jump1 = is_valid_jump_move(curr_pos, new_pos, 1, 1);
    bool jump2 = is_valid_jump_move(curr_pos, new_pos, -1, 1);
    bool jump3 = false;
    bool jump4 = false;

    if (selected_piece->is_king) {
        jump3 = is_valid_jump_move(curr_pos, new_pos, 1, -1);
        jump4 = is_valid_jump_move(curr_pos, new_pos, -1, -1);
    }

	return jump1 || jump2 || jump3 || jump4;
}

/*
 * Check if proposed move is legal.
 * Pieces can only move:
 * a) diagonally.
 * a) forward left/right one square,
 * b) backwards left/right if king (to be implemented)
 * c) two squares forward, if jumping opposing piece
 * d) two square backwards, to jump opposing piece, if king
 *
 * @param  curr_pos current piece position
 * @param  new_pos  new piece position
 * @return true - legal move, false - illegal move
 */
bool is_move(Position *curr_pos, Position *new_pos) {
	int x_delta = abs(curr_pos->x - new_pos->x);
	int y_delta = abs(curr_pos->y - new_pos->y);
	if ((x_delta == y_delta)
				&& (x_delta <= 2)
				&& (y_delta <= 2)) {
		return true;
	}
	return false;
}

/*
 * Check if there is a piece at the given position
 *
 * @param  x x position
 * @param  y y position
 * @return true - piece found, false - no piece
 */
bool is_piece_at_position(int x, int y) {
    for (int i = 0; i < 24; i++) {
        if ((all_pieces[i].x_pos == x) && (all_pieces[i].y_pos == y)) {
            return true;
        }
    }
    return false;
}

/*
 * Check if piece is at position to be promoted to king
 *
 * @param  y piece's y position
 * @param  direction piece's direction of movement
 * @return true - at kings row, else false
 */
bool is_piece_at_kings_row(int y, int direction) {
    // log_fmsg("::is_piece_at_kings_row: %d %d", 2, y, direction);
    if (direction == -1 && y == HEIGHT-1) {
        return true;
    }
    if (direction == 1 && y == 0) {
        return true;
    }
    return false;
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
 * Check position is within game x and y boundaries.
 *
 * @param  pos Position to check
 * @return true if position is within game boundaries
 */
bool is_within_boundary(Position *pos) {
    if ((pos->x < 0) || (pos->x >= WIDTH) || (pos->y < 0) || (pos->y >= HEIGHT)) {
        return false;
    }
	return true;
}

/*
 * Check if proposed move is valid, within bounds,
 * not to an occupied square and if is a jump
 * move, that it is valid for a jump
 *
 * @param  curr_pos
 * @param  new_pos
 * @param  piece
 * @return true if new position is a valid move from current position
 */
bool is_valid_move(Position *curr_pos, Position *new_pos) {

    // check direction
    bool is_forward_move = new_pos->y > curr_pos->y;
    bool is_forward_colour = is_positive_movement(selected_piece->colour);
    if (!selected_piece->is_king && ((is_forward_colour && !is_forward_move)
            || (!is_forward_colour && is_forward_move))) {
        log_msg("::wrong direction");
        return false;
    }

    // check valid move
	if (!is_move(curr_pos, new_pos)) {
        log_msg("::invalid move");
        return false;
    }
    // check boundaries
    if (!is_within_boundary(new_pos)) {
        log_msg("::out of bounds");
        return false;
    }
    // check square is unoccupied
	if (is_piece_at_position(new_pos->x, new_pos->y)) {
		log_msg("::space occupied");
		return false;
	}
    // check jump squares are not only accessible via own piece
	if (is_jump_move(curr_pos, new_pos)
			&& !is_valid_jump(curr_pos, new_pos)) {
        log_msg("::invalid jump");
		return false;
	}

    return true;
}

int get_all_valid_moves(Position *current_pos, Position *valid_pos[8]) {
    int num_valid_moves = 0;

    Position all_pos[] = {
        { .x = (current_pos->x) + 1, .y = (current_pos->y + 1) },
        { .x = (current_pos->x) + 1, .y = (current_pos->y - 1) },
        { .x = (current_pos->x) - 1, .y = (current_pos->y + 1) },
        { .x = (current_pos->x) - 1, .y = (current_pos->y - 1) },
        { .x = (current_pos->x) + 2, .y = (current_pos->y + 2) },
        { .x = (current_pos->x) + 2, .y = (current_pos->y - 2) },
        { .x = (current_pos->x) - 2, .y = (current_pos->y + 2) },
        { .x = (current_pos->x) - 2, .y = (current_pos->y - 2) }
    };

    for (int i = 0; i < 8; i++) {
		Position new_pos = { all_pos[i].x, all_pos[i].y };
        if (is_valid_move(current_pos, &new_pos)) {
            valid_pos[num_valid_moves++] = &all_pos[i];
        }
    }

    return num_valid_moves;
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
    log_fmsg("::move piece: %d, %d", 2, x+1, y+1);
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

void copy_piece(Piece *source, Piece *dest) {
    dest->id = source->id;
    dest->colour = source->colour;
    dest->is_king = source->is_king;
    dest->x_pos = source->x_pos;
    dest->y_pos = source->y_pos;
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
        log_fmsg("::capture_piece_at_position(): %d, [%d, %d]", 3, piece->id, x, y);
        piece->is_captured = true;
        piece->x_pos = 0;
        piece->y_pos = 0;
    }
    return piece;
}

void set_piece_king(Piece *piece) {
    piece->is_king = true;
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

/*
 * @deprecated
 */
void init_pieces_x(Piece *pieces) {

    selected_piece = malloc(sizeof(Piece));

    int i = 0;
    int j = 0;

    all_pieces = pieces;

    for (i = 0; i < 24; i++) {
        pieces[i].is_king = false;
        pieces[i].is_captured = false;
        pieces[i].id = i + 1;
    }

        j = 1;
    for (i = 0; i < 4; i++) {
        pieces[i].colour = 1;
        pieces[i].x_pos = j;
        pieces[i].y_pos = 0;
        j += 2;
    }

        j = 0;
    for (i = 4; i < 8; i++) {
        pieces[i].colour = 1;
        pieces[i].x_pos = j;
        pieces[i].y_pos = 1;
        j += 2;
    }

        j = 1;
    for (i = 8; i < 12; i++) {
        pieces[i].colour = 1;
        pieces[i].x_pos = j;
        pieces[i].y_pos = 2;
        j += 2;
    }

        j = 0;
    for (i = 12; i < 16; i++) {
        pieces[i].colour = 0;
        pieces[i].x_pos = j;
        pieces[i].y_pos = 5;
        j += 2;
    }

        j = 1;
    for (i = 16; i < 20; i++) {
        pieces[i].colour = 0;
        pieces[i].x_pos = j;
        pieces[i].y_pos = 6;
        j += 2;
    }

        j = 0;
    for (i = 20; i < 24; i++) {
        pieces[i].colour = 0;
        pieces[i].x_pos = j;
        pieces[i].y_pos = 7;
        j += 2;
    }

    pieces[10].x_pos = 5;
    pieces[10].y_pos = 4;
}

