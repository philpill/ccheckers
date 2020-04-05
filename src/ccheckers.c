#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <locale.h>
#include <panel.h>
#include "piece.h"
#include "game.h"
#include "render.h"
#include "input.h"
#include "resource.h"
#include "windowmanager.h"
#include "log.h"
#include "file.h"
#include "utilities.h"

Piece pieces[NUM_PIECES] = {0};

int run_loop(Game *game) {

    clock_t start_t, end_t, total_t;

    int return_code = 0;

    start_t = clock();

    // get input
    return_code = handle_input();

    // resolve state

    // render
    render_board(pieces);
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

    setlocale(LC_ALL, "");

    int game_id = get_id();

    init_log(game_id);

    Game game = { 0, 0, 0, 0, 0 };

    int exit = 0;

    init_game(&game);

    char *filename = "1";

    int direction = 1;

    init_piece(&game, pieces, filename, direction);

    PANEL *panels[4];

    init_render(panels);

    get_panels(panels);

    init_input(&game, panels);

    while (exit == 0) {

        exit = run_loop(&game);
    }

    quit_render();

    delete_windows(panels);

    destroy_file();

    return 0;
}

