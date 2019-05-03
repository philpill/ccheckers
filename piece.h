#ifndef PIECE_H
#define PIECE_H

typedef struct {
    char colour;
    char is_king;
    char is_active;
    int x_pos;
    int y_pos;
    int id;
} Piece;

void init_pieces(Piece pieces[]);

void select_piece(Piece *piece);

void deselect_piece();

void get_selected_piece(Piece *piece);

void select_piece_by_position(Piece *piece, int x, int y);

int is_piece_selected();

int is_piece_selected_by_id(int id);

#endif
