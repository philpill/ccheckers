#ifndef PIECE_H
#define PIECE_H

#include <stdbool.h>

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    int colour;
    int is_king;
    int is_active;
    int is_captured;
    int x_pos;
    int y_pos;
    Position position;
    int id;
} Piece;

void init_pieces(Piece pieces[]);

void select_piece(Piece *piece);

void deselect_piece();

Piece *get_selected_piece();

Piece *capture_piece_at_position(Position *pos);

bool select_piece_by_position(Piece *piece, int x, int y);

bool get_piece_by_position(Piece **piece, int x, int y);

bool is_piece_selected();

bool is_piece_at_position(int x, int y);

bool is_piece_selected_by_id(int id);

bool is_valid_move(Position *curr_pos, Position *new_pos, Piece *piece);

bool is_jump_move(Position *curr_pos, Position *new_pos);

void move_piece(Piece *piece, int x, int y);

bool is_player_turn_over(int colour);

bool is_player_dead(int colour);

void set_all_pieces_active(int colour);

#endif
