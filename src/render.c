#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

#include "pawn.h"
#include "game.h"
#include "windowmanager.h"
#include "global.h"
#include "log.h"
#include "input.h"

WINDOW **windows;

void init_render(WINDOW **render_windows) {

    windows = render_windows;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    if (has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }

    start_color();

    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);

    init_pair(3, COLOR_RED, COLOR_WHITE);
    init_pair(4, COLOR_RED, COLOR_BLACK);
}

// http://www.fileformat.info/info/unicode/char/search.htm?q=box+drawings&preview=entity
// http://yjlv.blogspot.com/2015/10/displaying-unicode-with-ncurses-in-c.html
void get_blank_grid(char grid[GRID_H][GRID_W]) {

    char end_line[]    = "    ┌───┬───┬───┬───┬───┬───┬───┬───┐";
    char data_line[]   = "    │   │   │   │   │   │   │   │   │";
    char spacer_line[] = "    ├───┼───┼───┼───┼───┼───┼───┼───┤";
    char close_line[]  = "    └───┴───┴───┴───┴───┴───┴───┴───┘";
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
    strcpy(grid[17], close_line);

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
    char c = 'A';
    for (int i = 0; c <= 'H'; i++, c++) {
        grid[18][(i * 4) + 6] = c;
    }
}

void render_pawns(Pawn *pawns, WINDOW *board_win) {
    for (int i = 0; i < NUM_PAWNS; i++) {
        if (!pawns[i].is_captured && pawns[i].id != 0) {
            int x_pos = pawns[i].x_pos;
            int y_pos = pawns[i].y_pos;
            int x = (x_pos*4)+6+1;
            int y = (y_pos*2)+2;
            char pawn = pawns[i].colour == 0 ? SYMBOL1 : SYMBOL2;
            if (is_pawn_selected_by_id(pawns[i].id)) {
                if (pawns[i].is_king) {
                    wattron(board_win, COLOR_PAIR(3));
                } else {
                    wattron(board_win, COLOR_PAIR(1));
                }
                mvwaddch(board_win, y, x, pawn);
                mvwaddch(board_win, y, x-1, ' ');
                mvwaddch(board_win, y, x+1, ' ');
                wattroff(board_win, COLOR_PAIR(1));
                wattroff(board_win, COLOR_PAIR(3));
            } else {
                if (pawns[i].is_king) {
                    wattron(board_win, COLOR_PAIR(4));
                } else {
                    wattron(board_win, COLOR_PAIR(2));
                }
                mvwaddch(board_win, y, x, pawn);
                wattroff(board_win, COLOR_PAIR(2));
                wattroff(board_win, COLOR_PAIR(4));
            }
        }
    }
}

void draw_grid(WINDOW *board_win, Pawn *pawns) {
    char board[GRID_H][GRID_W];
    get_blank_grid(board);
    label_grid(board);
    for (int i = 0; i < GRID_H; i++) {
        mvwprintw(board_win, i, 1, board[i]);
    }

    render_pawns(pawns, board_win);
}

void render_menu() {
    WINDOW *window = windows[3];
    /*
    werase(window);
    if (!is_options_panel_hidden(panels[3])) {
        box(window, 0, 0);
        int selected_option = get_selected_option();

        if (selected_option == 0) {
            wattron(window, COLOR_PAIR(1));
        }
        mvwprintw(window, 1, 2, "Resume");
        wattroff(window, COLOR_PAIR(1));

        if (selected_option == 1) {
            wattron(window, COLOR_PAIR(1));
        }
        mvwprintw(window, 2, 2, "New Game");
        wattroff(window, COLOR_PAIR(1));

        if (selected_option == 2) {
            wattron(window, COLOR_PAIR(1));
        }
        mvwprintw(window, 3, 2, "Quit");
        wattroff(window, COLOR_PAIR(1));

        wnoutrefresh(window);
    }
    */
}

void render_board(Pawn *pawns) {
    WINDOW *window = windows[1];
    werase(window);
    draw_grid(window, pawns);
    box(window, 0, 0);
    wnoutrefresh(window);
}

void render_text() {
    WINDOW *window = windows[2];
    werase(window);
    output_msg();
    box(window, 0, 0);
    wnoutrefresh(window);
}

void quit_render() {
}
