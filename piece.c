#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "piece.h"
#include "input.h"
#include "log.h"

Piece *all_pieces = NULL;
Piece *selected_piece = NULL;

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
 *
 */
bool is_valid_jump_move(Position *curr_pos, Position *new_pos, int dx, int dy) {
	int player_colour = 0;
	int adj_x = (curr_pos->x)+dx;
	int adj_y = (curr_pos->y)+dy;
    Piece *piece = NULL;

	// 2 squares up/down and 2 squares left/right
	if (!is_jump_move(curr_pos, new_pos)) {
		return false;
	}
	// there must be a piece to jump over
	if (!select_piece_by_position(piece, adj_x, adj_y)) {
		return false;
	}
	// checked piece is opposing
	// cannot jump over own piece
	if (piece->colour == player_colour) {
		return false;
	}
	return true;
}

// check x+1, y+1 for x+2, y+2
// check x-1 y+1 for x-2 y+2
// check x+1 y-1 for x+2 y-2
// check x-1 y-1 for x-2 y-2
bool is_valid_jump(Position *curr_pos, Position *new_pos) {

	if (!is_valid_jump_move(curr_pos, new_pos, 1, 1)) {
		return false;
	}

	if (!is_valid_jump_move(curr_pos, new_pos, 1, -1)) {
		return false;
	}

	// king only
	if (!is_valid_jump_move(curr_pos, new_pos, -1, 1)) {
		return false;
	}

	// king only
	if (!is_valid_jump_move(curr_pos, new_pos, -1, -1)) {
		return false;
	}

	return true;
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
    bool is_at_position = false;
    for (int i = 0; i < 24; i++) {
        if ((all_pieces[i].x_pos == x) && (all_pieces[i].y_pos == y)) {
            is_at_position = true;
        }
    }
    return is_at_position;
}

/*
 * Check all piece to see if all pieces have moved
 *
 * @param  colour player to check pieces for
 * @return true - player has no more pieces to move,
 *         false - pieces have moves left
 */
bool is_player_turn_over(int colour) {
    bool is_over = true;
    //int all_pieces_len = sizeof(all_pieces)/sizeof(Piece);
    // log_fmsg("all_pieces_len: %d", 1, all_pieces_len);
    int all_pieces_len = 24;
    for (int i = 0; i < all_pieces_len; i++) {
        if ((all_pieces[i].colour == colour)
            && (!all_pieces[i].is_captured)
            && (all_pieces[i].is_active)) {
                is_over = false;
            }
    }

    return is_over;
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
    // int all_pieces_len = sizeof(all_pieces)/sizeof(Piece);
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
    if ((pos->x < 0) || (pos->x > 7) || (pos->y < 0) || (pos->y > 7)) {
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
bool is_valid_move(Position *curr_pos, Position *new_pos, Piece* piece) {
    // check valid move
	if (!is_move(curr_pos, new_pos)) {
        log_msg("invalid move");
        return false;
    }
    // check boundaries
    if (!is_within_boundary(new_pos)) {
        log_msg("out of bounds");
        return false;
    }
    // check square is unoccupied
	if (is_piece_at_position(new_pos->x, new_pos->y)) {
		log_msg("space occupied");
		return false;
	}
    // check jump squares are not only accessible via own piece
	if (is_jump_move(curr_pos, new_pos)
			&& !is_valid_jump(curr_pos, new_pos)) {
        log_msg("invalid jump");
		return false;
	}

    return true;
}

int get_all_valid_moves(Position *current_pos, Position *valid_pos[8], Piece *piece) {
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
        if (is_valid_move(current_pos, &new_pos, piece)) {
            valid_pos[num_valid_moves++] = &all_pos[i];
        }
    }

    return num_valid_moves;
}

/*
 * Check if piece is currently selected
 *
 * @param  id piece id
 * @return
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

void move_piece(Piece *piece, int x, int y) {
    log_fmsg("::move piece: %d, %d", 2, x+1, y+1);
    piece->x_pos = x;
    piece->y_pos = y;
    // deactivate for rest of turn, but need to
    // check for further possible hops
    piece->is_active = false;
}

bool select_piece_by_position(Piece *piece, int x, int y) {
    for (int i = 0; i < 24; i++) {
        if ((all_pieces[i].x_pos == x) && (all_pieces[i].y_pos == y)) {
            log_msg("match");
            piece = &all_pieces[i];
            select_piece(piece);
            return true;
        }
    }
    return false;
}

void select_piece(Piece *piece) {
    selected_piece = piece;
    log_fmsg("pointers: %d, %d", 2, piece->x_pos, selected_piece->x_pos);
    is_selected = true;
}

void deselect_piece() {
    is_selected = false;
}

void copy_piece(Piece *source, Piece *dest) {
    dest->id = source->id;
    dest->colour = source->colour;
    dest->is_king = source->is_king;
    dest->is_active = source->is_active;
    dest->x_pos = source->x_pos;
    dest->y_pos = source->y_pos;
}

bool get_piece_by_position(Piece *piece, int x, int y) {
    log_msg("get_piece_by_position");
    int is_at_position = false;
    for (int i = 0; i < 24; i++) {
        if ((all_pieces[i].x_pos == x) && (all_pieces[i].y_pos == y)) {
            is_at_position = true;
            log_fmsg("::piece->id: %d", 1, all_pieces[i].id);
            *piece = all_pieces[i];
        }
    }
    return is_at_position;
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
    int x = 0;
    int y = 0;
    Piece *piece = NULL;
    if (get_piece_by_position(piece, x, y)) {
        piece->is_captured = 1;
        piece->x_pos = 0;
        piece->y_pos = 0;
    }
    return piece;
}

void set_all_pieces_active(int colour) {
    // int all_pieces_len = sizeof(all_pieces)/sizeof(Piece);
    int all_pieces_len = 24;
    for (int i = 0; i < all_pieces_len; i++) {
        Piece piece = all_pieces[i];
        if (piece.colour == colour && !piece.is_captured) {
            all_pieces[i].is_active = true;
        } else {
            all_pieces[i].is_active = false;
        }
    }
}

void init_pieces(Piece *pieces) {

    selected_piece = malloc(sizeof(Piece));

    int i = 0;
    int j = 0;

    all_pieces = pieces;

    for (i = 0; i < 24; i++) {
        pieces[i].is_king = 0;
        pieces[i].is_active = 1;
        pieces[i].is_captured = 0;
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
}

