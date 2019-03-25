#include <stdio.h>
#include "piece.h"
#include "game.h"
#include "render.h"
#include "input.h"
#include "windowmanager.h"
#include <ncurses.h>

int main() {
   
    printf("Checkers in C! \n");

    Game game = { 0, 0, 0 };    

    int exit = 0;

    Piece pieces[24];

    init_pieces(pieces);

    WINDOW *windows[3];

    init_render();
    
    get_windows(windows);

    init_input();

    render(windows[1], game, pieces);

    renderText(windows[2]);

    while (exit == 0) {

        exit = handle_input(windows, game, pieces);

        render(windows[1], game, pieces);

        renderText(windows[2]);
    }

    quit_render();

    delete_windows(windows);

    return 0;   
}
