#ifndef OPTIONS_H
#define OPTIONS_H

typedef enum {
    unknown_option,
    general,
    new_game
} OPTION_MODE;

void init_options();
int get_highlighted_option();
void highlight_option(int option_index);
void highlight_next_option();
void highlight_previous_option();
void highlight_first_option();
void highlight_last_option();

void select_highlighted_option();
void select_option(int index);

OPTION_MODE get_option_mode();
void set_option_mode(OPTION_MODE mode);

int get_options(char *options[]);

#endif
