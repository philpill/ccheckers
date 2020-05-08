#include <string.h>
#include <panel.h>
#include "options.h"
#include "windowmanager.h"

static int *exit;

static int highlighted_option = 0;
static OPTION_MODE current_option_mode = general;

static char *general_options[] = {
    "[return to game]",
    "New Game",
    "Quit"
};

static char *new_game_options[] = {
    "[return to previous menu]",
    "Local Hotseat",
    "Local AI",
    "Network",
    "Internet"
};

static int get_num_options() {
    int num_options = 0;
    if (current_option_mode == general) {
        num_options = 3;
    }
    if (current_option_mode == new_game) {
        num_options = 5;
    }
    return num_options;
}

static void exit_game() {
    *exit = 0;
}

void init_options(int *is_exit) {

    // load the functionality for each of the options
    exit = is_exit;
}

/*
 * Get currently highlighted option
 * 
 * @return index of highlighted option
 */
int get_highlighted_option() {
    return highlighted_option;
}

void highlight_option(int option_index) {
    int num_options = get_num_options();
    if (option_index <= 0) {
        highlight_first_option();
        return;
    }
    if (option_index >= num_options) {
        highlight_last_option();
        return;
    }
    highlighted_option = option_index;
}
void highlight_next_option() {
    int num_options = get_num_options();
    if (highlighted_option >= num_options) {
        highlight_first_option();
    } else {
        highlighted_option++;
    }
}
void highlight_previous_option() {
    if (highlighted_option <= 0) {
        highlight_last_option();
    } else {
        highlighted_option--;
    }
}
void highlight_first_option() {
    highlighted_option = 0;
}
void highlight_last_option() {
    int num_options = get_num_options();
    highlighted_option = num_options - 1;
}

// do something magical with function pointers here
void select_highlighted_option() {
    if (current_option_mode == general) {
        switch(highlighted_option) {
            case 0:
                // close options
                // hide_options_panel();
                break;
            case 1:
            case 2:
                // quit game
                exit_game();
                break;
        }
    }
    if (current_option_mode == new_game) {
        switch(highlighted_option) {
            case 0:
                // return to previous
                current_option_mode = general;
                break;
            case 1:
            case 2:
            case 3:
            case 4:
                // new game
                break;
        }
    }
}
void select_option(int index) {}

OPTION_MODE get_option_mode() { return current_option_mode; }
void set_option_mode(OPTION_MODE mode) { current_option_mode = mode; }

/*
 * Get the list of options for the currently
 * selected option mode
 * 
 * @param  options array of options to populate
 * @return number of options
 */
int get_options(char *options[]) {
    int length = 0;
    if (current_option_mode == general) {
        for (int i = 0; i < 3; i++) {
            strcpy(options[i], general_options[i]);
        }
        length = 3;
    }
    if (current_option_mode == new_game) {
        for (int i = 0; i < 5; i++) {
            strcpy(options[i], new_game_options[i]);
        }        
        length = 5;
    }    

    return length;
}
