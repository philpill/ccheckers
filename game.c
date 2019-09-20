#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "utilities.h"
#include "piece.h"
#include "input.h"

Game *game;

void init_game(Game *game) {
    game = game;
}


/*
 * Function: act_on_selected_piece
 *
 * Attempt to break down and refactor massive
 * nested 'if' statement.
 *
 * piece: selected piece
 * x: user input x position
 * y: user input y position
 */
void act_on_selected_piece(Piece *piece, int x, int y) {

    char msg[50];

    sprintf(msg, "::select square: %d, %d", x+1, y+1);

    insert_msg(msg);

    Piece *check_piece = malloc(sizeof(Piece));

    insert_msg("piece currently selected");

    piece = get_selected_piece();

    sprintf(msg, "::position: %d, %d", (*piece).x_pos, (*piece).y_pos);

    insert_msg(msg);

    //deselect
    if ((*piece).x_pos == x && (*piece).y_pos == y) {

        insert_msg("piece at position - deselect piece");

        deselect_piece();

    } else if (select_piece_by_position(check_piece, x, y)) {

        if ((*check_piece).colour == game->playerColour) {

            // select alternative piece
            insert_msg("select different piece");

            piece = check_piece;

        } else {

            // not owned - do nothing
            insert_msg("piece not owned");
        }

    } else {

        if (piece->is_active && !piece->is_captured) {

            insert_msg("moving piece...");
            // move selected piece to empty square
            // is move valid?

            Position curr_pos = { piece->x_pos, piece->y_pos };
            Position new_pos = { x, y };
            if (is_valid_move(&curr_pos, &new_pos, piece)) {
                insert_msg("valid move");
                move_piece(piece, x, y);
                if (is_jump_move(&curr_pos, &new_pos)) {
                    Position pos;
                    if (get_intervening_position(&pos, &curr_pos, &new_pos)) {
                        capture_piece_at_position(&pos);
                        // need to check if all pieces are captured i.e. win
                        if (is_player_dead(1 - game->playerColour)) {
                            // player win!
                        }
                    }
                }

                // end move
                piece->is_active = false;

                // check if all pieces have moved
                if (is_player_turn_over(game->playerColour)) {
                    // switch player
                    // https://stackoverflow.com/a/4084058
                    game->playerColour = 1 - game->playerColour;
                    // set all pieces active
                    set_all_pieces_active(game->playerColour);
                }

            } else {
                insert_msg("invalid move");
            }
        } else {
            insert_msg("piece has already moved");
        }
    }

    free(check_piece);
}

int select_square(int x, int y) {

    char msg[50];

    sprintf(msg, "::select square: %d, %d", x+1, y+1);

    insert_msg(msg);

    Piece *selected_piece = malloc(sizeof(Piece));
    Piece *check_piece = malloc(sizeof(Piece));

    if (is_piece_selected()) {

        insert_msg("no piece currently selected");

        //select piece if owned
        if (get_piece_by_position(check_piece, x, y)) {

            insert_msg("piece detected");

            sprintf(msg, "::colour: %d, %d", (*check_piece).colour, game->playerColour);

            insert_msg(msg);

            if ((*check_piece).colour == game->playerColour) {

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

        act_on_selected_piece(selected_piece, x, y);
    }

    //free(selected_piece);
    free(check_piece);
}
