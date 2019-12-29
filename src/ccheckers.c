#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <locale.h>
#include "piece.h"
#include "game.h"
#include "render.h"
#include "input.h"
#include "resource.h"
#include "windowmanager.h"
#include "log.h"

Piece pieces[24];

Game game;

int run_loop() {

    clock_t start_t, end_t, total_t;

    int return_code = 0;

    start_t = clock();

    // get input
    return_code = handle_input();

    // resolve state

    // render
    render(game, pieces);
    render_text();

    end_t = clock();

    total_t = end_t - start_t;

    doupdate();

    //log_fmsg("time: %d", 1, total_t);

    // 30fps = 33300us

    usleep(33300 - total_t);

    return return_code;
}

int main() {

    printf("Checkers in C! \n");

    setlocale(LC_ALL, "");

    Game game = { 0, 0, 0, 0 };

    int exit = 0;

    init_game(&game);

    char *filename = "2";

    int direction = 1;

    init_piece(&game, pieces, filename, direction);

    WINDOW *windows[4];

    init_render(windows);

    get_windows(windows);

    init_input(windows);

    while (exit == 0) {

        exit = run_loop();
    }

    quit_render();

    delete_windows(windows);

    return 0;
}

