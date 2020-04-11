#ifndef CORE_H_
#define CORE_H_

#define NUM_PAWNS 24
#define HEIGHT 8
#define WIDTH 8
#define STATE_EMPTY 0
#define STATE_WHITE_PAWN 1
#define STATE_BLACK_PAWN 2
#define STATE_WHITE_KING 3
#define STATE_BLACK_KING 4
#define KINGS_ROW_WHITE 7
#define KINGS_ROW_BLACK 0

#include <stdbool.h>

enum PAWN {
    white = 1,
    black = 2,
    white_king = 3,
    black_king = 4
};

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    Position pawn_captured_pos;
    Position pawn_moved_new_pos;
    Position pawn_moved_old_pos;
    bool is_pawn_promoted;
    bool is_jump;
    bool is_capture;
    int total_pawns_remaining;
    bool is_error;
    char error_msg[255];

} Report;

int get_pawn_moves(Position pos, int state[WIDTH][HEIGHT], 
                        Position moves[]);

int get_pawn_jumps(Position pos, int state[WIDTH][HEIGHT], 
                        Position jumps[]);

bool get_result(Position origin, Position dest, 
                int state[WIDTH][HEIGHT], int result[WIDTH][HEIGHT], Report *report);

#endif
