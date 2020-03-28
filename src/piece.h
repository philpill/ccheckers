#ifndef PIECE_H
#define PIECE_H

#include <stdbool.h>
#include "game.h"
#include "core.h"

typedef struct {
    int colour;
    bool is_king;
    bool is_captured;
    int x_pos;
    int y_pos;
    Position position;
    int id;
    int direction;
} Piece;

int init_piece(Game *game, Piece pieces[], char *filename, int direction);

void get_state_by_pieces(int state[WIDTH][HEIGHT]);

void select_piece(Piece *piece);

void deselect_piece();

Piece *get_selected_piece();

Piece *capture_piece_at_position(Position *pos);

bool select_piece_by_position(Piece *piece, int x, int y);

bool get_piece_by_position(Piece **piece, int x, int y);

bool is_piece_selected();

bool is_piece_selected_by_id(int id);

void move_piece(Piece *piece, int x, int y);

bool is_player_dead(int colour);

#endif
