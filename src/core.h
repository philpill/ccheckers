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

typedef struct {
    Position piece_captured_pos;
    Position piece_moved_new_pos;
    Position piece_moved_old_pos;
    bool is_piece_promoted;
    int total_pieces_remaining;
    bool is_error;
    char error_msg[255];

} Report;

int get_piece_moves(Position pos, int state[WIDTH][HEIGHT], 
                        Position moves[]);

int get_piece_jumps(Position pos, int state[WIDTH][HEIGHT], 
                        Position jumps[]);

bool get_result(Position origin, Position dest, 
                int state[WIDTH][HEIGHT], int result[WIDTH][HEIGHT], Report report);

#endif
