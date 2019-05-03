#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "piece.h"
#include "input.h"

int select_square(int x, int y) {

    char msg[50];

    sprintf(msg, "::select square: %d, %d", x, y);

    insert_msg(msg);
    
    Piece *selected_piece = malloc(sizeof(Piece));

    if (is_piece_selected() == 0) {

        insert_msg("select");
        //select piece if owned

        select_piece_by_position(selected_piece, x, y);

    } else {

        insert_msg("deselect");

        get_selected_piece(selected_piece);
        
        if ((*selected_piece).x_pos == x && (*selected_piece).y_pos == y) {
    
            insert_msg("deselect match");          

            deselect_piece();
        }

        //deselect
        //move selected piece to empty square
        //capture opponent piece
        //select alternative piece
    }

    free(selected_piece);
}
