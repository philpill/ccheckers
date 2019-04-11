#include <ncurses.h>
#include <string.h>
#include "piece.h"
#include "game.h"
#include "windowmanager.h"
#include "global.h"

void init_render() {
    initscr();
}

void get_blank_grid(char grid[GRID_H][GRID_W]) {
    char end_line[]    = " . . . . . . . . . . . . . . . . .\n\0";
    char data_line[]   = " :   :   :   :   :   :   :   :   :\n\0";
    char spacer_line[] = " : . : . : . : . : . : . : . : . :\n\0";
    strcpy(grid[0], end_line);
    strcpy(grid[1], end_line);
    strcpy(grid[2], data_line);
    strcpy(grid[3], spacer_line);
    strcpy(grid[4], data_line);
    strcpy(grid[5], spacer_line);
    strcpy(grid[6], data_line);
    strcpy(grid[7], spacer_line);
    strcpy(grid[8], data_line);
    strcpy(grid[9], spacer_line);
    strcpy(grid[10], data_line);
    strcpy(grid[11], spacer_line);
    strcpy(grid[12], data_line);
    strcpy(grid[13], spacer_line);
    strcpy(grid[14], data_line);
    strcpy(grid[15], spacer_line);
    strcpy(grid[16], data_line);
    strcpy(grid[17], spacer_line);
}

void populate_grid(Piece *pieces, char grid[][GRID_W]) {
    const int num_pieces = 24;
    for (int i = 0; i < num_pieces; i++) {
        int x_pos = pieces[i].x_pos;
        int y_pos = pieces[i].y_pos;
        char piece = pieces[i].colour == '0' ? 'x' : 'o';
        grid[(x_pos*2)+2][(y_pos*4)+3] = piece;
    }
}

void draw_grid(WINDOW *board_win, Piece *pieces) {
    int columns = 8;
    int rows = 8;
    char board[2*rows+2][4*columns+3];
    get_blank_grid(board);
    populate_grid(pieces, board);
    wprintw(board_win, board[0]);
}

void render(WINDOW *board_win, Game game, Piece *pieces) {
    werase(board_win);
    draw_grid(board_win, pieces);
    box(board_win, '*', '*');
    wrefresh(board_win);
}

void renderText(WINDOW *text_win) {
    werase(text_win);
    wprintw(text_win, "\n\0");
    wprintw(text_win, " test");
    box(text_win, '*', '*');
    wrefresh(text_win);
}

void quit_render() {
}
