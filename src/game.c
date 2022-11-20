#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "game.h"
#include "utilities.h"
#include "pawn.h"
#include "input.h"
#include "log.h"
#include "core.h"
#include "player.h"

static Game *game_data;
static int num_players;
static Player *player;

void log_next_player(int id) {
    get_player_by_id(id, player);
    char msg[255];
    strcpy(msg, player->name);
    strcat(msg, "'s turn");
    log_msg(msg);
}

void game_init(Game *new_game) {
    game_data = new_game;
    // go straight to game state
    // there currently is no lobby
    game_data->app_state = 2;
    num_players = get_num_players();
    player = malloc(sizeof(Player));
    log_next_player(game_data->player_colour+1);
}

void set_next_player() {
    int current_player = game_data->player_colour;
    int next_player = current_player + 1;
    if (next_player >= num_players) {
        next_player = 0;
    }
    game_data->player_colour = next_player;
    log_next_player(next_player+1);
}

void game_end_turn() {
    log_msg("::end turn\n");
    pawn_deselect_all();
    set_next_player();
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

    Pawn *check_pawn = NULL;

    pawn = pawn_get_selected();

    Position new_pos = { x, y };

    //deselect
    if (pawn_is_at_position(pawn, new_pos)) {

        log_msg("pawn at position - deselect pawn\n");

        pawn_deselect_all();

    } else if (pawn_get_by_position(&check_pawn, x, y)) {

        log_fmsg("::pawn_get_by_position: %d, %d\n", 2, check_pawn->colour, game_data->player_colour);

        if (pawn_is_owned_by_current_player(check_pawn)) {

            // select alternative pawn
            log_msg("select different pawn\n");

            //pawn = check_pawn;
            pawn_deselect_all();
            pawn_select_by_position(pawn, x, y);

        } else {

            // not owned - do nothing
            log_msg("pawn not owned\n");
        }

    } else {

        if (!pawn->is_captured) {

            Position curr_pos = pawn->position;

            int state[WIDTH][HEIGHT] = {{0}};
            int result[WIDTH][HEIGHT] = {{0}};
            Report report = { };

            pawn_get_state(state);

            if (get_result(curr_pos, new_pos, state, result, &report)) {
                
                pawn_move(pawn, new_pos);
                
                if (report.is_pawn_promoted) {
                    log_msg("pawn promoted to king\n");
                    pawn->is_king = true;
                }

                if (report.is_jump && report.is_capture) {
                    pawn_capture_at_position(&report.pawn_captured_pos);
                }

                // end move
                game_end_turn();

                if (pawn_is_player_dead(1 - game_data->player_colour)) {
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

    check_pawn = NULL;
    free(check_pawn);
}

int game_select_square(int x, int y) {

    char msg[50];

    sprintf(msg, "::select square: %d, %d\n", x+1, y+1);

    log_msg(msg);

    Pawn *selected_pawn = 0;
    Pawn *check_pawn = 0;

    if (!pawn_is_selected()) {

        // log_msg("no pawn currently selected");

        //select pawn if owned
        if (pawn_get_by_position(&check_pawn, x, y)) {

            // log_msg("pawn detected");

            log_fmsg("::pawn->id: %d\n", 1, check_pawn->id);

            // log_fmsg("::colour: %d, %d", 2, check_pawn->colour, game->player_colour);

            if (pawn_is_owned_by_current_player(check_pawn)) {

                // log_msg("pawn owned - selecting");

                pawn_select_by_position(selected_pawn, x, y);

            } else {

                // pawn is not owned - do nothing
                log_msg("pawn not owned\n");
            }

        } else {

            log_msg("empty square\n");
        }

    } else {

        // log_msg("pawn currently selected");

        selected_pawn = pawn_get_selected();

        act_on_selected_pawn(selected_pawn, x, y);
    }

    selected_pawn = NULL;
    check_pawn = NULL;

    free(selected_pawn);
    free(check_pawn);
}


void game_destroy() {
    player = NULL;
    free(player);
}