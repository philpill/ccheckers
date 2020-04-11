#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "utilities.h"
#include "pawn.h"
#include "input.h"
#include "log.h"
#include "core.h"

static Game *game_data;

void init_game(Game *new_game) {
    game_data = new_game;
    // go straight to game state
    // there currently is no lobby
    game_data->app_state = 2;
}

void end_turn() {
    log_msg("::end turn\n");
    deselect_pawn();
    // switch player
    // https://stackoverflow.com/a/4084058
    game_data->player_colour = 1 - game_data->player_colour;
    game_data->turn_counter = game_data->turn_counter+1;
}

/*
 * Attempt to break down and refactor massive
 * nested 'if' statement.
 *
 * pawn: selected pawn
 * x: user input x position
 * y: user input y position
 */
void act_on_selected_pawn(Pawn *pawn, int x, int y) {

    Pawn *check_pawn = 0;

    pawn = get_selected_pawn();

    //deselect
    if (pawn->x_pos == x && pawn->y_pos == y) {

        log_msg("pawn at position - deselect pawn\n");

        deselect_pawn();

    } else if (get_pawn_by_position(&check_pawn, x, y)) {

        log_fmsg("::get_pawn_by_position: %d, %d\n", 2, check_pawn->colour, game_data->player_colour);

        if (check_pawn->colour == game_data->player_colour) {

            // select alternative pawn
            log_msg("select different pawn\n");

            //pawn = check_pawn;
            deselect_pawn();
            select_pawn_by_position(pawn, x, y);

        } else {

            // not owned - do nothing
            log_msg("pawn not owned\n");
        }

    } else {

        if (!pawn->is_captured) {

            Position curr_pos = { pawn->x_pos, pawn->y_pos };
            Position new_pos = { x, y };

            int state[WIDTH][HEIGHT] = {{0}};
            int result[WIDTH][HEIGHT] = {{0}};
            Report report = { };

            get_state_by_pawns(state);

            if (get_result(curr_pos, new_pos, state, result, &report)) {
                
                move_pawn(pawn, x, y);
                
                if (report.is_pawn_promoted) {
                    log_msg("pawn promoted to king\n");
                    pawn->is_king = true;
                }

                if (report.is_jump && report.is_capture) {
                    capture_pawn_at_position(&report.pawn_captured_pos);
                }

                // end move
                end_turn();

                if (is_player_dead(1 - game_data->player_colour)) {
                    // player win!
                    log_msg("win!\n");
                }

            } else {

                log_msg(report.error_msg);
            }

        } else {

            log_msg("pawn has already moved\n");
        }
    }

    // free(check_pawn);
}

int select_square(int x, int y) {

    char msg[50];

    sprintf(msg, "::select square: %d, %d\n", x+1, y+1);

    log_msg(msg);

    Pawn *selected_pawn = 0;
    Pawn *check_pawn = 0;

    if (!is_pawn_selected()) {

        // log_msg("no pawn currently selected");

        //select pawn if owned
        if (get_pawn_by_position(&check_pawn, x, y)) {

            // log_msg("pawn detected");

            log_fmsg("::pawn->id: %d\n", 1, check_pawn->id);

            // log_fmsg("::colour: %d, %d", 2, check_pawn->colour, game->player_colour);

            if (check_pawn->colour == game_data->player_colour) {

                // log_msg("pawn owned - selecting");

                select_pawn_by_position(selected_pawn, x, y);

            } else {

                // pawn is not owned - do nothing
                log_msg("pawn not owned\n");
            }

        } else {

            log_msg("empty square\n");
        }

    } else {

        // log_msg("pawn currently selected");

        selected_pawn = get_selected_pawn();

        act_on_selected_pawn(selected_pawn, x, y);
    }

    // free(selected_pawn);
    // free(check_pawn);
}
