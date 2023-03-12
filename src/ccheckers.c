#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <locale.h>
#include <panel.h>
#include <stdlib.h>
#include "pawn.h"
#include "game.h"
#include "render.h"
#include "input.h"
#include "resource.h"
#include "windowmanager.h"
#include "log.h"
#include "file.h"
#include "utilities.h"
#include "options.h"
#include "player.h"

void start(Game *game, Pawn **pawns_ptr) {

    int game_id = get_id();

    log_init(game_id);

    game->turn_counter = 0;
    game->player_colour = rand()%get_num_players();
    game->player_win = 0;
    game->player_positive_move = 0;
    game->app_state = 0;

    game_init(game);

    pawn_init(game, *pawns_ptr, "1", 1);
}

int run_loop(Game *game, Pawn *pawns) {

    clock_t start_t, end_t, total_t;

    int return_code = 0;

    start_t = clock();

    // get input
    return_code = input_handle();

    // resolve state

    // render
    render_board(pawns, game);
    render_text();
    render_menu();

    end_t = clock();

    total_t = end_t - start_t;

    doupdate();

    //log_fmsg("time: %d", 1, total_t);

    // 30fps = 33300us

    usleep(33300 - total_t);

    return return_code;
}

int main() {

    Game game;

    PANEL *panels[4];

    Pawn *pawns_ptr;

    setlocale(LC_ALL, "");

    pawns_ptr = malloc(NUM_PAWNS * sizeof(Pawn));

    init_player();

    start(&game, &pawns_ptr);

    int exit = 0;

    init_render(panels);

    get_panels(panels);

    input_init(&game, panels);

    init_options(&exit);

    while (exit == 0) {

        if (game.app_state == 0) {

            // reset all
            start(&game, &pawns_ptr);
            hide_options_panel(panels[3]);
        }

        exit = run_loop(&game, pawns_ptr);
    }

    quit_render();

    delete_windows(panels);

    destroy_file();
    game_destroy();
    destroy_player();

    return 0;
}

