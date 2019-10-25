#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include "piece.h"
#include "game.h"
#include "render.h"
#include "input.h"
#include "resource.h"
#include "windowmanager.h"

Piece pieces[24];

Game game;

long current_ntime;

int run_loop() {

    int return_code = 0;

    // get input
    return_code = handle_input();

    // resolve state

    // render
    render(game, pieces);
    render_text();

    // 1000000 = 1fps
    // 33333.3 = 30fps
    // 50000 = 20fps
    // 100000 = 10fps
    usleep(100000);

    return return_code;
}

int main() {

    printf("Checkers in C! \n");

    Game game = { 0, 0, 0, 0 };

    int exit = 0;

    init_game(&game);

    char *filename = "2";

    int direction = 1;

    init_piece(&game, pieces, filename, direction);

    WINDOW *windows[3];

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

