#include <string.h>
#include <ncurses.h>
#include <ctype.h>
#include "game.h"
#include "input.h"
#include "piece.h"

WINDOW *input_window;
WINDOW *output_window;

char msg_log[5000][255];

int msg_ctr = 0;
int char_ctr = 0;

char input_buffer;

void output_msg() {
    int x = 0;
    int y = 0;
    getmaxyx(output_window, y, x);
    int start_msg_ctr = msg_ctr - y + 2;
    if (start_msg_ctr < 0) { start_msg_ctr = 0; }
    for (int i = 0; i < msg_ctr && i < y + 2; i++) {
        mvwprintw(output_window, i, 1, msg_log[start_msg_ctr+i]);
    }
    mvwprintw(output_window, y-2, 1, msg_log[msg_ctr]);
}

void insert_char(char ch) {
    msg_log[msg_ctr][char_ctr] = ch;
    char_ctr++;
}

void insert_msg(char *message) {
    strcpy(msg_log[msg_ctr], message);
    msg_ctr++;
    char_ctr = 0;
}

void delete_char() {
    char_ctr = char_ctr < 1 ? 0 : char_ctr - 1;
    msg_log[msg_ctr][char_ctr] = '\0';
}

char* get_last_msg() {
    return msg_log[msg_ctr-1];
}

void init_input(WINDOW **windows) {
    input_window = windows[0];
    output_window = windows[2];
    nodelay(windows[0], true);
    insert_msg("***"); // blank placeholder
    insert_msg("Checkers in C!");
}

void parse_command(char *command) {
    if (strlen(command) == 2) {
        int x = command[0];
        int y = command[1];
        if ((isdigit(x) != 0) && (isdigit(y) != 0)) {
            select_square((x - '0') - 1, (y - '0') - 1);
        }   
    }
}

int is_exit(char *command) {
    int is_exit = 0;
    if ((strcmp(msg_log[msg_ctr], "quit") == 0) || strcmp(msg_log[msg_ctr], "exit") == 0) {
        is_exit = 1;
    } 
    return is_exit;
}

int handle_input() {
    int exit = 0;

    input_buffer = wgetch(input_window);

    // printf("%d", input_buffer);

    if (input_buffer == -1) {
        // do nothing
    } else if (input_buffer == 27) {
        exit = 1;
    } else if (input_buffer == 127) {
        delete_char();
    } else if (input_buffer == 10) {
        if (is_exit(msg_log[msg_ctr]) == 1) {
            exit = 1;
        } else if (char_ctr == 0) {
            // nothing in beffer
            // do nothing
        } else {
            int ctr = msg_ctr;
            insert_msg(msg_log[ctr]);
            parse_command(msg_log[ctr]);
        }
    } else {
        insert_char(input_buffer);
    }
    return exit;
}

int get_input() {
    return input_buffer;
} 

