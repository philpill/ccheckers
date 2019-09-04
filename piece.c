#include "piece.h"
#include <stdlib.h>
#include <stdio.h>
#include "input.h"

Piece *all_pieces;
Piece *selected_piece;

int is_selected = 0;

int is_piece_selected() {
    return is_selected;
}

/*
 * Function: is_valid_jump_move_a
 * ------------------------------
 *
 * Alternative (old) implemntation
 *
 * If move is one of four valid jump moves,
 * check intervening square is occupied
 * by not-owned piece. 
 * (check to be implemented)
 *
 * curr_pos: current piece position
 * new_pos: new piece position 
 * dx: x delta
 * dy: y delta
 * jx: intervening x delta
 * jy: intervening y delta
 *
 * returns: 0 - not valid, 1 - is valid
 *
 */
int is_valid_jump_move_a(Position *curr_pos, Position *new_pos, int dx, int dy, int jx, int jy) {
    Piece *piece;
    if (((curr_pos->x)+dx == new_pos->x) && (((curr_pos->y)+dy == new_pos->y))) {
        if (select_piece_by_position(piece, (curr_pos->x)+jx, (curr_pos->y)+jy) != 0) {
            if (piece->colour == 0) {
                return 0;
            }
        }
    }
	return 1;
}

/*
 * Function: is_jump_move
 * ----------------------
 *
 * Check if new, proposed position is
 * a jump move.
 * Jump moves are two squares up/down
 * and two squares left/right
 *
 * curr_pos: current piece position
 * new_pos: new piece position 
 *
 * returns: 0 - not jump move, 1 - is jump move
 */
int is_jump_move(Position *curr_pos, Position *new_pos) {
    int pos_x = curr_pos->x;
	int pos_y = curr_pos->y;
	int new_x = new_pos->x;
	int new_y = new_pos->y;
	return ((abs(new_x-pos_x) == 2) && (abs(new_y-pos_y) == 2));
}

/*
 * Function: is_valid_jump_move
 * -----------------------------
 *
 * If move is one of four valid jump moves,
 * check intervening square is occupied
 * by not-owned piece. 
 * (check to be implemented)
 *
 * curr_pos: current piece position
 * new_pos: new piece position 
 * dx: x direction - 1 or -1
 * dy: y direction - 1 or -1
 *
 * returns: 0 - not valid, 1 - is valid
 *
 */
int is_valid_jump_move(Position *curr_pos, Position *new_pos, int dx, int dy) {
	int player_colour = 0;
	int adj_x = (curr_pos->x)+dx;
	int adj_y = (curr_pos->y)+dy;
    Piece *piece;
	
	// 2 squares up/down and 2 squares left/right
	if (!is_jump_move(curr_pos, new_pos)) {
		return 0;
	}
	// there must be a piece to jump over
	if (!select_piece_by_position(piece, adj_x, adj_y)) {
		return 0;
	}
	// checked piece is opposing
	// cannot jump over own piece 
	if (piece->colour == player_colour) {
		return 0;
	}
	return 1;
}

// check x+1, y+1 for x+2, y+2
// check x-1 y+1 for x-2 y+2
// check x+1 y-1 for x+2 y-2
// check x-1 y-1 for x-2 y-2
int is_valid_jump(Position *curr_pos, Position *new_pos) {
	
	if (!is_valid_jump_move(curr_pos, new_pos, 1, 1)) {
		return 0;
	}

	if (!is_valid_jump_move(curr_pos, new_pos, 1, -1)) {
		return 0;
	}

	if (!is_valid_jump_move(curr_pos, new_pos, -1, 1)) {
		return 0;
	}

	if (!is_valid_jump_move(curr_pos, new_pos, -1, -1)) {
		return 0;
	}

	return 1;
}

/*
 * Function: is_move
 *
 * Check if proposed move is legal.
 * Pieces can only move:
 * a) diagonally.
 * a) forward left/right one square,
 * b) backwards left/right if king (to be implemented)
 * c) two squares forward, if jumping opposing piece
 * d) two square backwards, to jump opposing piece, if king
 *
 * curr_pos: current piece position
 * new_pos: new piece position 
 *
 * returns: 1 - legal move, 0 - illegal move
 */
int is_move(Position *curr_pos, Position *new_pos) {
	int x_delta = abs(curr_pos->x - new_pos->x);
	int y_delta = abs(curr_pos->y - new_pos->y);
	if ((x_delta == y_delta) 
				&& (x_delta <= 2) 
				&& (y_delta <= 2)) {
		return 1;
	}
	return 0;
}

int is_valid_move(Position *curr_pos, Position *new_pos) {
    // check valid move
	if (!is_move(curr_pos, new_pos)) {
        insert_msg("invalid move");
        return 0;
    }
    // check boundaries
    if ((new_pos->x < 0) || (new_pos->x > 7) || (new_pos->y < 0) || (new_pos->y > 7)) {
        insert_msg("out of bounds");
        return 0;
    }
    // check square is unoccupied
    for (int i = 0; i < 24; i++) {
        if ((all_pieces[i].x_pos == new_pos->x) && (all_pieces[i].y_pos == new_pos->y)) {
            insert_msg("space occupied");
            return 0;
        }
    }
    // check jump squares are not only accessible via own piece 
	if (is_jump_move(curr_pos, new_pos) && !is_valid_jump(curr_pos, new_pos)) {
        insert_msg("invalid jump");
		return 0;
	}

    return 1;
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

int is_piece_selected_by_id(int id) {
    int is_piece_selected = 0;
    if (is_selected == 1) {
        if (id == selected_piece -> id) {
            is_piece_selected = 1;
        }
    }
    return is_piece_selected;
}

int is_piece_at_position(int x, int y) {
    int is_at_position = 0;
    for (int i = 0; i < 24; i++) {
        if ((all_pieces[i].x_pos == x) && (all_pieces[i].y_pos == y)) {
            is_at_position = 1;
        }
    }
    return is_at_position;
}

void move_piece(Piece *piece, int x, int y) {

    char msg[50];
    sprintf(msg, "::move piece: %d, %d", x+1, y+1);
    insert_msg(msg);
    (*piece).x_pos = x;
    (*piece).y_pos = y;
    // deactivate for rest of turn, but need to
    // check for further possible hops
    // (*piece).is_active = false;
}

int select_piece_by_position(Piece *piece, int x, int y) {
    for (int i = 0; i < 24; i++) {
        if ((all_pieces[i].x_pos == x) && (all_pieces[i].y_pos == y)) {
            insert_msg("match");
            piece = &all_pieces[i];
            select_piece(piece);
            return 1;
        }
    }
    return 0;
}

void select_piece(Piece *piece) {
    selected_piece = piece;
    char msg[50];
    sprintf(msg, "pointers: %d, %d", (*piece).x_pos, (*selected_piece).x_pos);
    insert_msg(msg);
    is_selected = 1;
}

void deselect_piece() {
    is_selected = 0;
}

void copy_piece(Piece *source, Piece *dest) {
    dest->id = source->id;
    dest->colour = source->colour;
    dest->is_king = source->is_king;
    dest->is_active = source->is_active;
    dest->x_pos = source->x_pos;
    dest->y_pos = source->y_pos;
}

int get_piece_by_position(Piece *piece, int x, int y) {
    int is_at_position = 0;
    for (int i = 0; i < 24; i++) {
        if ((all_pieces[i].x_pos == x) && (all_pieces[i].y_pos == y)) {
            is_at_position = 1;
            piece = &all_pieces[i];
        }
    }
    return is_at_position;
}

Piece *get_selected_piece() {
    return selected_piece;
}

void init_pieces(Piece *pieces) {

    selected_piece = malloc(sizeof(Piece));

    int i = 0;
    int j = 0;

    all_pieces = pieces;

    for (i = 0; i < 24; i++) {
        pieces[i].is_king = 0;
        pieces[i].is_active = 1;
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

int is_valid_move_xx(int x, int y, int new_x, int new_y) {
    // check valid move
    if (!((x + 1 == new_x) && (y + 1 == new_y) || 
        ((x + 2 == new_x) && (y + 2 == new_y)) ||
        ((x + 1 == new_x) && (y - 1 == new_y)) ||
        ((x + 2 == new_x) && (y - 2 == new_y)) ||
        ((x - 1 == new_x) && (y + 1 == new_y)) ||
        ((x - 2 == new_x) && (y + 2 == new_y)) ||
        ((x - 1 == new_x) && (y - 1 == new_y)) ||
        (x - 2 == new_x) && (y - 2 == new_y))) {
        insert_msg("invalid move");
        return 0;
    }
    // check boundaries
    if ((new_x < 0) || (new_x > 7) || (new_y < 0) || (new_y > 7)) {
        insert_msg("out of bounds");
        return 0;
    }
    // check square is unoccupied
    for (int i = 0; i < 24; i++) {
        if ((all_pieces[i].x_pos == new_x) && (all_pieces[i].y_pos == new_y)) {
            insert_msg("space occupied");
            return 0;
        }
    }
    // check jump squares are not only accessible via own piece 
    // check x+1, y+1 for x+2, y+2
    // check x-1 y+1 for x-2 y+2
    // check x+1 y-1 for x+2 y-2
    // check x-1 y-1 for x-2 y-2

    Piece *piece;

    if ((x + 2 == new_x) && (y + 2 == new_y)) {
        if (select_piece_by_position(piece, x + 1, y + 1) != 0) {
            if (piece->colour == 0) {
                return 0;
            }
        }
    }

    if ((x + 2 == new_x) && (y - 2 == new_y)) {
        if (select_piece_by_position(piece, x + 1, y - 1) != 0) {
            if (piece->colour == 0) {
                return 0;
            }
        }
    }

    if ((x - 2 == new_x) && (y + 2 == new_y)) {
        if (select_piece_by_position(piece, x - 1, y + 1) != 0) {
            if (piece->colour == 0) {
                return 0;
            }
        }
    }

    if ((x - 2 == new_x) && (y - 2 == new_y)) {
        if (select_piece_by_position(piece, x - 1, y - 1) != 0) {
            if (piece->colour == 0) {
                return 0;
            }
        }
    }

    return 1;
}

