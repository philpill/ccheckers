#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "piece.h"
#include "input.h"

Game game;

void init_game(Game *game) {

    
}

int select_square(int x, int y) {

    char msg[50];

    sprintf(msg, "::select square: %d, %d", x+1, y+1);

    insert_msg(msg);
    
    Piece *selected_piece = malloc(sizeof(Piece));
    Piece *check_piece = malloc(sizeof(Piece));

    if (is_piece_selected() == 0) {

        insert_msg("no piece currently selected");

        //select piece if owned
        if (get_piece_by_position(check_piece, x, y) == 1) {

            insert_msg("piece detected");
           
            sprintf(msg, "::colour: %d, %d", (*check_piece).colour, game.playerColour);

            insert_msg(msg);
    
            if ((*check_piece).colour == game.playerColour) {

                insert_msg("piece owned - selecting");
                
                select_piece_by_position(selected_piece, x, y);
            }
        } else {
            
            insert_msg("empty square");
        }

    } else {

        insert_msg("piece currently selected");

        get_selected_piece(selected_piece);
        
        //deselect
        if ((*selected_piece).x_pos == x && (*selected_piece).y_pos == y) {
    
            deselect_piece();
        }

        if (is_piece_at_position(x, y) == 1) {

            select_piece_by_position(check_piece, x, y);

            if ((*check_piece).colour == game.playerColour) {

                selected_piece = check_piece;

            } else {


            }

            // if owned
                // select alternative piece
                // select_piece_by_position(selected_piece, x, y);
            // else
                // capture opponent piece
                // deactivate captured piece
                // move piece to vacated square
                // move_piece(selected_piece, x, y);            

        } else {

            // move selected piece to empty square
            move_piece(selected_piece, x, y);            
        }
    }

    free(selected_piece);
    free(check_piece);
}
