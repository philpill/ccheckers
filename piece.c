#include "piece.h"
#include <stdio.h>

void init_pieces(Piece *pieces) {

    printf("init_pieces()");

    printf("%li", sizeof(pieces));

    int i = 0;
    int j = 0;

    for (i = 0; i < 24; i++) {
        pieces[i].is_king = 0;
        pieces[i].is_active = 1;
    }

        j = 1;
    for (i = 0; i < 4; i++) {
        pieces[i].colour = '1';
        pieces[i].x_pos = 0;
        pieces[i].y_pos = j;
        j += 2;
    }

        j = 0;
    for (i = 4; i < 8; i++) {
        pieces[i].colour = '1';
        pieces[i].x_pos = 1;
        pieces[i].y_pos = j;
        j += 2;
    }

        j = 1;
    for (i = 8; i < 12; i++) {
        pieces[i].colour = '1';
        pieces[i].x_pos = 2;
        pieces[i].y_pos = j;
        j += 2;
    }

        j = 0;
    for (i = 12; i < 16; i++) {
        pieces[i].colour = '0';
        pieces[i].x_pos = 5;
        pieces[i].y_pos = j;
        j += 2;
    }

        j = 1;
    for (i = 16; i < 20; i++) {
        pieces[i].colour = '0';
        pieces[i].x_pos = 6;
        pieces[i].y_pos = j;
        j += 2;
    }

        j = 0;
    for (i = 20; i < 24; i++) {
        pieces[i].colour = '0';
        pieces[i].x_pos = 7;
        pieces[i].y_pos = j;
        j += 2;
    }
}
