#ifndef CORE_H_
#define CORE_H_

#define NUM_PIECES 24
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

enum PIECE {
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
    Position piece_captured_pos;
    Position piece_moved_new_pos;
    Position piece_moved_old_pos;
    bool is_piece_promoted;
    bool is_jump;
    bool is_capture;
    int total_pieces_remaining;
    bool is_error;
    char error_msg[255];

} Report;

int get_piece_moves(Position pos, int state[WIDTH][HEIGHT], 
                        Position moves[]);

int get_piece_jumps(Position pos, int state[WIDTH][HEIGHT], 
                        Position jumps[]);

bool get_result(Position origin, Position dest, 
                int state[WIDTH][HEIGHT], int result[WIDTH][HEIGHT], Report *report);

#endif
