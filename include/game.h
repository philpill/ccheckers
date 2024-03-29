#ifndef GAME_H_
#define GAME_H_

typedef enum {
    unknown,
    lobby,
    game,
    options
} APP_STATE;

typedef struct {
    int turn_counter;
    int player_colour;
    int player_win;
    int player_positive_move;
    APP_STATE app_state;
} Game;

void game_init(Game *game);
void game_end_turn();
int  game_select_square(int x, int y);
void game_destroy();

#endif
