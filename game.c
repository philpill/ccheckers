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
            
            } else {

                // piece is not owned - do nothing
                insert_msg("piece not owned");
            }

        } else {
            
            insert_msg("empty square");
        }

    } else {

        insert_msg("piece currently selected");

        selected_piece = get_selected_piece();
        
        sprintf(msg, "::position: %d, %d", (*selected_piece).x_pos, (*selected_piece).y_pos);

        insert_msg(msg);
 
        //deselect
        if ((*selected_piece).x_pos == x && (*selected_piece).y_pos == y) {
   
            insert_msg("piece at position - deselect piece");
 
            deselect_piece();
        
        } else if (is_piece_at_position(x, y) == 1) {

            select_piece_by_position(check_piece, x, y);

            if ((*check_piece).colour == game.playerColour) {

                // select alternative piece
                insert_msg("select different piece");

                selected_piece = check_piece;

            } else {

                // not owned - do nothing
                insert_msg("piece not owned");
            }

        } else {

            insert_msg("move piece");
            // move selected piece to empty square
            move_piece(selected_piece, x, y);            
        }
    }

    //free(selected_piece);
    //free(check_piece);
}
