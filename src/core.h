#ifndef CORE_H_
#define CORE_H_

#define NUM_PIECES 24
#define HEIGHT 8
#define WIDTH 8

#include <stdbool.h>

typedef struct {
    int x;
    int y;
} Position;

int get_moves(Position pos, int *state[WIDTH][HEIGHT], 
                        Position *moves[]);

bool get_result(Position origin, Position dest, 
                int *state[WIDTH][HEIGHT], int *result[WIDTH][HEIGHT], char *msg[]);

#endif
