#include <string.h>
#include <ncurses.h>
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
    mvwprintw(output_window, msg_ctr, 0, get_last_msg());
    getmaxyx(output_window, y, x);
    mvwprintw(output_window, y-2, 0, msg_log[msg_ctr]);
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

char* get_last_msg() {
    return msg_log[msg_ctr-1];
}

void init_input(WINDOW **windows) {
    input_window = windows[0];
    output_window = windows[2];
    nodelay(windows[0], true);
    insert_msg("xtest1");
}

int handle_input() {
    int exit = 0;

    // wprintw(windows[2], "test"); 
    input_buffer = wgetch(input_window);

    //printf("%d", input_buffer);

    //wprintw(output_window, get_last_msg());
    //mvwprintw(output_window, msg_ctr, 0, get_last_msg()); 

    if (input_buffer == -1) {
        // do nothing
    } else if (input_buffer == 27) {
        exit = 1;
    } else if (input_buffer == 10) {
        //insert_char('\r');
        insert_char('\n');
        //insert_char('\0');
        insert_msg(msg_log[msg_ctr]);
        
    } else {
        insert_char(input_buffer);
    }
    return exit;
}

int get_input() {
    return input_buffer;
} 
