#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "utilities.h"
#include "piece.h"
#include "input.h"
#include "log.h"
#include "core.h"

Game *game;

void init_game(Game *new_game) {
    game = new_game;
}

void end_turn() {
    log_msg("::end turn\n");
    deselect_piece();
    // switch player
    // https://stackoverflow.com/a/4084058
    game->player_colour = 1 - game->player_colour;
    game->turn_counter = game->turn_counter+1;
}

/*
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

        log_msg("piece at position - deselect piece\n");

        deselect_piece();

    } else if (get_piece_by_position(&check_piece, x, y)) {

        log_fmsg("::get_piece_by_position: %d, %d\n", 2, check_piece->colour, game->player_colour);

        if (check_piece->colour == game->player_colour) {

            // select alternative piece
            log_msg("select different piece\n");

            //piece = check_piece;
            deselect_piece();
            select_piece_by_position(piece, x, y);

        } else {

            // not owned - do nothing
            log_msg("piece not owned\n");
        }

    } else {

        if (!piece->is_captured) {

            // log_msg("moving piece...");
            // move selected piece to empty square
            // is move valid?

            Position curr_pos = { piece->x_pos, piece->y_pos };
            Position new_pos = { x, y };

/*
    Position piece_captured_pos;
    Position piece_moved_new_pos;
    Position piece_moved_old_pos;
    bool is_piece_promoted;
    int total_pieces_remaining;
    bool is_error;
    char error_msg[255];
*/
            int state[WIDTH][HEIGHT] = {{0}};
            int result[WIDTH][HEIGHT] = {{0}};
            Report report = { };

            get_state_by_pieces(state);

            if (get_result(curr_pos, new_pos, state, result, &report)) {
                log_msg("awesome!\n");
            } else {
                log_msg(report.error_msg);
            }



            if (is_valid_move(&curr_pos, &new_pos)) {
                // log_msg("valid move");
                move_piece(piece, x, y);
                if (is_piece_at_kings_row(y, piece->direction)) {
                    // log_msg("::is_piece_at_kings_row(): true");
                    piece->is_king = true;
                }
                if (is_jump_move(&curr_pos, &new_pos)) {
                    Position pos;
                    if (get_intervening_position(&pos, &curr_pos, &new_pos)) {
                        capture_piece_at_position(&pos);
                        // need to check if all pieces are captured i.e. win
                        if (is_player_dead(1 - game->player_colour)) {
                            // player win!
                            log_msg("win!\n");
                        }
                    }
                }

                // end move
                end_turn();

            } else {
                log_msg("invalid move\n");
            }
        } else {
            log_msg("piece has already moved\n");
        }
    }

    // free(check_piece);
}

int select_square(int x, int y) {

    char msg[50];

    sprintf(msg, "::select square: %d, %d\n", x+1, y+1);

    log_msg(msg);

    Piece *selected_piece = 0;
    Piece *check_piece = 0;

    if (!is_piece_selected()) {

        // log_msg("no piece currently selected");

        //select piece if owned
        if (get_piece_by_position(&check_piece, x, y)) {

            // log_msg("piece detected");

            log_fmsg("::piece->id: %d\n", 1, check_piece->id);

            // log_fmsg("::colour: %d, %d", 2, check_piece->colour, game->player_colour);

            if (check_piece->colour == game->player_colour) {

                // log_msg("piece owned - selecting");

                select_piece_by_position(selected_piece, x, y);

            } else {

                // piece is not owned - do nothing
                log_msg("piece not owned\n");
            }

        } else {

            log_msg("empty square\n");
        }

    } else {

        // log_msg("piece currently selected");

        selected_piece = get_selected_piece();

        act_on_selected_piece(selected_piece, x, y);
    }

    // free(selected_piece);
    // free(check_piece);
}
