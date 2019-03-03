#include <ncurses.h>
#include <string.h>
#include "piece.h"
#include "game.h"
#include "windowmanager.h"

void init_render() {
    initscr();
}

void get_blank_grid(char grid[17][34]) {
    char end_line[]    = ". . . . . . . . . . . . . . . . .\n\0";
    char data_line[]   = ":   :   :   :   :   :   :   :   :\n\0";
    char spacer_line[] = ": . : . : . : . : . : . : . : . :\n\0";
    strcpy(grid[0], end_line);
    strcpy(grid[1], data_line);
    strcpy(grid[2], spacer_line);
    strcpy(grid[3], data_line);
    strcpy(grid[4], spacer_line);
    strcpy(grid[5], data_line);
    strcpy(grid[6], spacer_line);
    strcpy(grid[7], data_line);
    strcpy(grid[8], spacer_line);
    strcpy(grid[9], data_line);
    strcpy(grid[10], spacer_line);
    strcpy(grid[11], data_line);
    strcpy(grid[12], spacer_line);
    strcpy(grid[13], data_line);
    strcpy(grid[14], spacer_line);
    strcpy(grid[15], data_line);
    strcpy(grid[16], spacer_line);
}

void populate_grid(Piece *pieces, char grid[][34]) {
    const int num_pieces = 24;
    for (int i = 0; i < num_pieces; i++) {
        int x_pos = pieces[i].x_pos;
        int y_pos = pieces[i].y_pos;
        char piece = pieces[i].colour == '0' ? 'x' : 'o';
        grid[(x_pos*2)+1][(y_pos*4)+2] = piece;
    }
}

void draw_grid(WINDOW *board_win, Piece *pieces) {
    int columns = 8;
    int rows = 8;
    char board[2*rows+1][4*columns+2];
    get_blank_grid(board);
    populate_grid(pieces, board);
    wprintw(board_win, board[0]);
}

void render(WINDOW *board_win, Game game, Piece *pieces) {
    werase(board_win);
    draw_grid(board_win, pieces);
    wrefresh(board_win);
}

void quit_render() {
}
