#ifndef PIECE_H
#define PIECE_H

typedef struct {
    char colour;
    char is_king;
    char is_active;
    int x_pos;
    int y_pos;
} Piece;

void init_pieces(Piece pieces[]);

#endif
