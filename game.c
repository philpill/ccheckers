#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "utilities.h"
#include "piece.h"
#include "input.h"
#include "log.h"

Game *game;

void init_game(Game *new_game) {
    game = new_game;
}

void end_turn() {
    log_msg("end turn");
    deselect_piece();
    // switch player
    // https://stackoverflow.com/a/4084058
    game->playerColour = 1 - game->playerColour;
    game->turnCounter = game->turnCounter+1;
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

    Piece *check_piece = 0;

    piece = get_selected_piece();

    //deselect
    if (piece->x_pos == x && piece->y_pos == y) {

        log_msg("piece at position - deselect piece");

        deselect_piece();

    } else if (get_piece_by_position(&check_piece, x, y)) {

        log_fmsg("::get_piece_by_position: %d, %d", 2, check_piece->colour, game->playerColour);

        if (check_piece->colour == game->playerColour) {

            // select alternative piece
            log_msg("select different piece");

            piece = check_piece;

        } else {

            // not owned - do nothing
            log_msg("piece not owned");
        }

    } else {

        if (!piece->is_captured) {

            log_msg("moving piece...");
            // move selected piece to empty square
            // is move valid?

            Position curr_pos = { piece->x_pos, piece->y_pos };
            Position new_pos = { x, y };
            if (is_valid_move(&curr_pos, &new_pos, piece)) {
                log_msg("valid move");
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
                end_turn();

            } else {
                log_msg("invalid move");
            }
        } else {
            log_msg("piece has already moved");
        }
    }

    // free(check_piece);
}

int select_square(int x, int y) {

    char msg[50];

    sprintf(msg, "::select square: %d, %d", x+1, y+1);

    log_msg(msg);

    Piece *selected_piece = 0;
    Piece *check_piece = 0;

    if (!is_piece_selected()) {

        log_msg("no piece currently selected");

        //select piece if owned
        if (get_piece_by_position(&check_piece, x, y)) {

            log_msg("piece detected");

            log_fmsg("::piece->id: %d", 1, check_piece->id);

            log_fmsg("::colour: %d, %d", 2, check_piece->colour, game->playerColour);

            if (check_piece->colour == game->playerColour) {

                log_msg("piece owned - selecting");

                select_piece_by_position(selected_piece, x, y);

            } else {

                // piece is not owned - do nothing
                log_msg("piece not owned");
            }

        } else {

            log_msg("empty square");
        }

    } else {

        log_msg("piece currently selected");

        selected_piece = get_selected_piece();

        act_on_selected_piece(selected_piece, x, y);
    }

    // free(selected_piece);
    // free(check_piece);
}
