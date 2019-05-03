#ifndef GAME_H_
#define GAME_H_

typedef struct {
    int turnCounter;
    int playerTurn;
    int playerWin;    
} Game;

int select_square(int x, int y);

#endif
