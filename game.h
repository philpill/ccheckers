#ifndef GAME_H_
#define GAME_H_

typedef struct {
    int turnCounter;
    int playerColour;
    int playerWin;
} Game;

void init_game(Game *game);
void end_turn();
int select_square(int x, int y);

#endif
