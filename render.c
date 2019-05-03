#include <ncurses.h>
#include <string.h>
#include "piece.h"
#include "game.h"
#include "windowmanager.h"
#include "global.h"
#include "input.h"

WINDOW **windows;

void init_render(WINDOW **render_windows) {
    windows = render_windows;
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
}

void get_blank_grid(char grid[GRID_H][GRID_W]) {
    char end_line[]    = "    . . . . . . . . . . . . . . . . .";
    char data_line[]   = "    :   :   :   :   :   :   :   :   :";
    char spacer_line[] = "    : . : . : . : . : . : . : . : . :";
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

    for (int i = 18; i < GRID_H; i++) {
        char blank_line[GRID_W];
        memset(blank_line, ' ', (GRID_W - 1)*sizeof(char)); 
        strcpy(grid[i], blank_line);
    }
}

void label_grid(char grid[GRID_H][GRID_W]) {
    for (int i = 0; i < 8; i++) {
        grid[(i * 2) + 2][2] = '0' + i + 1;
    }
    for (int i = 0; i < 8; i++) {
        grid[18][(i * 4) + 6] = '0' + i + 1;
    }
}

void populate_grid(Piece *pieces, char grid[][GRID_W]) {
    const int num_pieces = 24;
    for (int i = 0; i < num_pieces; i++) {
        int x_pos = pieces[i].x_pos;
        int y_pos = pieces[i].y_pos;
        char piece = pieces[i].colour == '0' ? 'x' : 'o';
        if (is_piece_selected_by_id(pieces[i].id) == 1) {
            piece = pieces[i].colour == '0' ? 'X' : 'O';
        }
        grid[(x_pos*2)+2][(y_pos*4)+6] = piece;
    }
}

void draw_grid(WINDOW *board_win, Piece *pieces) {
    char board[GRID_H][GRID_W];
    get_blank_grid(board);
    label_grid(board);
    populate_grid(pieces, board);
    for (int i = 0; i < GRID_H; i++) {
        mvwprintw(board_win, i, 1, board[i]);
        // wprintw(board_win, board[0]);
    }
}

void render(Game game, Piece *pieces) {
    WINDOW *window = windows[1];
    wclear(window);
    draw_grid(window, pieces);
    box(window, 0, 0);
    wrefresh(window);
}

void render_text() {
    WINDOW *window = windows[2];
    wclear(window);
    output_msg();
    box(window, 0, 0);
    wrefresh(window);
}

void quit_render() {
}
