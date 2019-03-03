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

    Piece pieces[24];

    init_pieces(pieces);

    WINDOW *windows[2];

    init_render();
    
    get_windows(windows);

    init_input();

    render(windows[0], game, pieces);

    while (handle_input(windows[1], game, pieces) != 1) {

       render(windows[0], game, pieces);
    }

    quit_render();

    delete_windows(windows);

    return 0;   
}
