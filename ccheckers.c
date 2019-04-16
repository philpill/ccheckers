#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include "piece.h"
#include "game.h"
#include "render.h"
#include "input.h"
#include "windowmanager.h"
#include <ncurses.h>

Piece pieces[24];

Game game;

int run_loop() {

    int return_code = 0;

    // get input
    int user_input = get_input();

    if (user_input == 27) {
        return_code = 1;
    }

    // resolve state

    // render
    render(game, pieces);
    render_text();

    usleep(200000);

    return return_code;
}

int main() {
   
    printf("Checkers in C! \n");

    Game game = { 0, 0, 0 };    

    int exit = 0;

    init_pieces(pieces);

    WINDOW *windows[3];

    init_render(windows);
    
    get_windows(windows);

    init_input(windows[0]);

    while (exit == 0) {

        exit = run_loop();
    }

    quit_render();

    delete_windows(windows);

    return 0;   
}

