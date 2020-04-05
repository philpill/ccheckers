#include <string.h>
#include <ncurses.h>
#include <panel.h>
#include <ctype.h>
#include "game.h"
#include "input.h"
#include "piece.h"
#include "log.h"
#include "windowmanager.h"

static WINDOW *input_window;
static WINDOW *output_window;

static PANEL *settings_panel;

static Game *game_data = NULL;

static char msg_log[5000][255];

static int msg_ctr = 0;
static int char_ctr = 0;

static int input_buffer;

static int selected_option = 0;

int get_selected_option() {
    return selected_option;
}

int select_previous_option() {
    selected_option = selected_option > 0 ? selected_option - 1: 0;
}

int select_next_option() {
    selected_option = selected_option < 2 ? selected_option + 1: 2;
}

void output_msg() {
    int x = 0;
    int y = 0;
    getmaxyx(output_window, y, x);

    int log_count = get_log_count();
    char *logs[log_count];
    get_logs(logs, log_count);

    int start_msg_ctr = log_count - 1 - y + 3;
    if (start_msg_ctr < 0) { start_msg_ctr = 0; }
    for (int i = 0; i < log_count - 1 && i < y + 3; i++) {
        mvwprintw(output_window, i+1, 1, logs[start_msg_ctr+i]);
    }
    mvwprintw(output_window, y-2, 1, msg_log[msg_ctr]);
}

void insert_msg(char *message) {
    strcpy(msg_log[msg_ctr], message);
    msg_ctr++;
    char_ctr = 0;
}

static void delete_char() {
    char_ctr = char_ctr < 1 ? 0 : char_ctr - 1;
    msg_log[msg_ctr][char_ctr] = '\0';
}

static void insert_char(char ch) {
    msg_log[msg_ctr][char_ctr] = ch;
    msg_log[msg_ctr][char_ctr+1] = '\0';
    char_ctr++;
}

char* get_last_msg() {
    return msg_log[msg_ctr-1];
}

void init_input(Game *new_game, PANEL **panels) {
    game_data = new_game;
    settings_panel = panels[3];
    input_window = panels[0]->win;
    output_window = panels[2]->win;
    log_msg("Checkers in C!\n");
}

/*
 * Get corresponding int value for letter for
 * square on board
 * e.g.
 * a == 1, B == 2, d == 4
 * TODO use enum here?
 *
 * @param  x_char_pos x position letter
 * @return 0 if not valid, else corresponding position
 */
static int get_int_x_pos(char x_char_pos) {

    int x_int_pos = 0;

    switch (x_char_pos) {
        case 'A':
        case 'a':
            x_int_pos = 1;
            break;
        case 'B':
        case 'b':
            x_int_pos = 2;
            break;
        case 'C':
        case 'c':
            x_int_pos = 3;
            break;
        case 'D':
        case 'd':
            x_int_pos = 4;
            break;
        case 'E':
        case 'e':
            x_int_pos = 5;
            break;
        case 'F':
        case 'f':
            x_int_pos = 6;
            break;
        case 'G':
        case 'g':
            x_int_pos = 7;
            break;
        case 'H':
        case 'h':
            x_int_pos = 8;
            break;

        default:
            x_int_pos = 0;
    }

    return x_int_pos;
}

static void parse_command(char *command) {
    if (strlen(command) == 2) {
        char x = command[0];
        int y = command[1];
        bool is_y_digit = isdigit(y) != 0;
        bool is_x_alpha = isalpha(x) != 0;
        if (is_y_digit && is_x_alpha) {
            int x_pos = get_int_x_pos(x);
            select_square(x_pos - 1, (y - '0') - 1);
        }
    }
}

static bool is_exit(char *command) {
    bool is_exit = false;
    if ((strcmp(msg_log[msg_ctr], "quit") == 0) || strcmp(msg_log[msg_ctr], "exit") == 0) {
        is_exit = true;
    }
    return is_exit;
}

static bool is_debug1(char *command) {
    bool is_debug1 = false;
    if (strcmp(msg_log[msg_ctr], "debug1") == 0) {
        is_debug1 = true;
    }
    return is_debug1;
}

static bool is_end_turn(char *command) {
    bool is_end_turn = false;
    if (strcmp(msg_log[msg_ctr], "end") == 0) {
        is_end_turn = true;
    }
    return is_end_turn;
}

void clear_buffer() {
    char_ctr = 0;
    msg_log[msg_ctr][char_ctr] = '\0';
}

// https://stackoverflow.com/a/11432632
int handle_input() {

    int exit = 0;

    if (!is_settings_panel_hidden(settings_panel)) {

        input_buffer = wgetch(settings_panel->win);

        switch(input_buffer) {
            case -1:
            break;
            case 10:
                //return 
                if (get_selected_option() == 0) {
                    game_data->app_state = 2;
                    hide_settings_panel(settings_panel);
                }

                if (get_selected_option() == 1) {
                    // new game
                }

                if (get_selected_option() == 2) {
                    exit = 1;
                }                
            break;
            case KEY_UP:
                select_previous_option();
            break;
            case KEY_DOWN:
                select_next_option();
            break;
            default:
            break;
        }
    } else {

        // printf("%d", input_buffer);

        input_buffer = wgetch(input_window);

        switch(input_buffer) {
            case -1:
            break;
            case 127:
                //backspace
                delete_char();
            break;
            case 10:
                //return 
                if (is_end_turn(msg_log[msg_ctr])) {
                    end_turn();
                    clear_buffer();
                }
                
                if (is_exit(msg_log[msg_ctr])) {
                    exit = 1;
                }
                
                if (is_debug1(msg_log[msg_ctr])) {
                    if (is_piece_selected()) {
                        Piece *piece = get_selected_piece();
                        log_fmsg("id: %d", 1, piece->id);
                        log_fmsg("colour: %d", 1, piece->colour);
                    } else {
                        log_msg("::no piece selected");
                    }
                    clear_buffer();
                }
                
                if (char_ctr == 0) {
                    // nothing in buffer
                    // do nothing
                } else {
                    int ctr = msg_ctr;
                    log_msg(msg_log[ctr]);
                    insert_msg(msg_log[ctr]);
                    parse_command(msg_log[ctr]);
                }
            break;
            case 65:
            case 66:
            case 67:
            case 68:
            break;
            case 27:
                // escape
                if (wgetch(input_window) != '[') {
                    game_data->app_state = 3;
                    show_settings_panel(settings_panel);
                    //exit = 1;
                }
            break;
            default:
                insert_char(input_buffer);
            break;
        }
    }
    

    return exit;
}

int get_input() {
    return input_buffer;
}

