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

int is_valid_move(int x, int y, int new_x, int new_y) {
    // check valid move
    if ((x + 1 != new_x) && (y + 1 != new_y) || 
        (x + 2 != new_x) && (y + 2 != new_y)) {
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

    return 1;
}

int get_all_valid_moves(Position *current_pos, Position *valid_pos[64]) {
    int num_valid_moves = 0;

    

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

void select_piece_by_position(Piece *piece, int x, int y) {
    for (int i = 0; i < 24; i++) {
        if ((all_pieces[i].x_pos == x) && (all_pieces[i].y_pos == y)) {
            insert_msg("match");
            piece = &all_pieces[i];
            select_piece(piece);
        }
    }
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
