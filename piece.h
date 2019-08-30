#ifndef PIECE_H
#define PIECE_H

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    int colour;
    char is_king;
    char is_active;
    int x_pos;
    int y_pos;
    Position position;
    int id;
} Piece;

void init_pieces(Piece pieces[]);

void select_piece(Piece *piece);

void deselect_piece();

Piece *get_selected_piece();

int select_piece_by_position(Piece *piece, int x, int y);

int get_piece_by_position(Piece *piece, int x, int y);

int is_piece_selected();

int is_piece_at_position(int x, int y);

int is_piece_selected_by_id(int id);

int is_valid_move(Position curr_pos, Position new_pos);

void move_piece(Piece *piece, int x, int y);

int is_valid_move_xx(int x, int y, int new_x, int new_y);

#endif
