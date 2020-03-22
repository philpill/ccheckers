#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "core.h"

/*
 * Initialise board to zeroes
 * 
 * @param  state Board to clear of pieces
 */
static void initialise_state(int state[WIDTH][HEIGHT]) {
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            state[i][j] = 0;
        }
    }
}

/*
 * Validate state of board and pieces
 *  - if there are not more than the max number of pieces
 * 
 * @param  state     Board and pieces to validate
 * @param  error_msg Reason for failure
 * @return true is state of board is valid
 */
static bool is_state_valid(int state[WIDTH][HEIGHT], char error_msg[]) {

    int num_pieces = 0;

    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            if (state[i][j] != 0) {
                num_pieces++;
            }
        }
    }

    if (num_pieces > NUM_PIECES) {
        strcpy(error_msg, "number of pieces in given state exceed expected value");
        return false;
    }

    // check pieces are not on the wrong squares
    // i.e. black squares only
    // bottom left and top right

    return true;
}

/*
 * Get the 8 theoretical possible squares for a piece to 
 * move/jump forward/backward to
 *'
 * @param pos   Origin position to calculate other moves
 * @param moves Array of possible moves
 */
static void get_all_moves(Position pos, Position moves[8]) {

    Position pos1 = { pos.x+1, pos.y+1 };
    Position pos2 = { pos.x+1, pos.y-1 };
    Position pos3 = { pos.x-1, pos.y+1 };
    Position pos4 = { pos.x-1, pos.y-1 };

    Position pos5 = { pos.x+2, pos.y+2 };
    Position pos6 = { pos.x+2, pos.y-2 };
    Position pos7 = { pos.x-2, pos.y+2 };
    Position pos8 = { pos.x-2, pos.y-2 };

    moves[0] = pos1;
    moves[1] = pos2;
    moves[2] = pos3;
    moves[3] = pos4;

    moves[4] = pos5;
    moves[5] = pos6;
    moves[6] = pos7;
    moves[7] = pos8;
}

/*
 * Get the 4 theoretical possible squares for a piece to 
 * jump forward/backward to
 *'
 * @param pos   Origin position to calculate other moves
 * @param moves Array of possible moves
 */
static void get_all_jumps(Position pos, Position moves[8]) {

    Position pos1 = { pos.x+2, pos.y+2 };
    Position pos2 = { pos.x+2, pos.y-2 };
    Position pos3 = { pos.x-2, pos.y+2 };
    Position pos4 = { pos.x-2, pos.y-2 };

    moves[0] = pos1;
    moves[1] = pos2;
    moves[2] = pos3;
    moves[3] = pos4;
}

/*
 * Check if move is within bounds of play
 * Currently fixed at 8 square grid
 * 
 * @param  move Destination position
 * @return true if within bounds
 */
static bool is_move_within_bounds(Position move) {


    bool is_within = true;
    is_within = move.x < 8 
                && move.x > -1 
                && move.y < 8
                && move.y > -1;

    //printf("is_move_within_bounds(): %d\n", is_within);

    return is_within;
}

/*
 * Check if proposed move is blocked
 * by another piece
 * 
 * @param  move Destination position
 * @return true if space is occupied
 */
static bool is_space_occupied(Position move, int state[WIDTH][HEIGHT]) {

    bool is_occupied = false;
    is_occupied = state[move.y][move.x] != 0;

    //printf("is_space_occupied(): %d\n", is_occupied);

    //if (is_occupied) {
    //printf("--> %d\n", state[move.y][move.x]);
    //}

    return is_occupied;
}

/*
 * Check if piece is a king
 * 
 * @param  piece Value from state data
 * @return true is piece is a king 
 */

static bool is_king(int piece) {
    return piece == 3 || piece == 4;
}

/*
 * Check is piece is moving forwards or backwards
 * 
 * @param  piece Value from state data
 * @param  pos   Original position
 * @param  move  Destination position
 * @return true is proposed move is forward advance
 */
static bool is_forward_move(int piece, Position pos, Position move) {

    //printf("is_forward_move(): ");

    bool is_down = move.y > pos.y;

    //printf("%d -> %d = %d, %d\n", pos.y, move.y, is_down, piece);

    bool is_forward_move = ((piece == 1 || piece == 3) && is_down) 
                            || ((piece == 2 || piece == 4) && !is_down);

    //printf("%d\n", is_forward_move);

    return is_forward_move;
}

/*
 * Check if a proposed move is a jump
 * (forwards or backwards)
 * 
 * @param  pos  Original position
 * @param  move Destination position
 * @return true if proposed move is a jump 
 */
static bool is_jump_move(Position pos, Position move) {
    if (abs(pos.x-move.x) == 2) {
        return true;
    }
    return false;
}

/*
 * Check if a proposed move is a valid jump
 * (forwards or backwards)
 * 
 * @param  pos       Original position
 * @param  move      Destination position
 * @param  state     Board with pieces data
 * @param  error_msg Reason for failure
 * @return true if proposed move is a valid jump 
 */
static bool is_valid_jump_move(Position pos, Position move, int state[WIDTH][HEIGHT], 
                                char error_msg[]) {
    if (!is_jump_move(pos, move)) {
        return false;
    }
    int x = (pos.x+move.x)/2;
    int y = (pos.y+move.y)/2;
    int piece = state[pos.y][pos.x];
    int intervening_piece = state[y][x];
    if (intervening_piece == 0) {
        strcpy(error_msg, "No intervening piece to jump");
        return false;
    } else {
        if ((piece == 1 || piece == 3)
            && (intervening_piece == 1 || intervening_piece == 3)) {
            strcpy(error_msg, "Cannot jump friendly piece");
            return false;
        } else if ((piece == 2 || piece == 4)
            && (intervening_piece == 2 || intervening_piece == 4)) {
            strcpy(error_msg, "Cannot jump friendly piece");
            return false;
        }
    }
    return true;
}

/*
 * Check if proposed move is valid, given current game state
 * 
 * @param  pos       Current position
 * @param  move      Proposed move
 * @param  state     Board with pieces data
 * @param  error_msg Reason for failure
 * @return true if move is valid
 */
static bool is_valid_move(Position pos, Position move, int state[WIDTH][HEIGHT], 
                            char error_msg[]) {

    //printf("----------\n[%d, %d]\n", move.x, move.y);

    if (!is_move_within_bounds(move)) return false;
    if (is_space_occupied(move, state)) return false; 

    // test for forward movement
    bool is_piece_king = is_king(state[pos.y][pos.x]);
    bool is_piece_forward_move = is_forward_move(state[pos.y][pos.x], pos, move); 
    if (!is_piece_forward_move) {
        // sprintf(error_msg, "%d %d %d %d", state[4][1], state[3][4], state[1][2], state[4][3]);
        strcat(error_msg, "Not forward move. "); 
        if (!is_piece_king) { 
            strcat(error_msg, "Non-king piece cannot move backwards. ");
            return false;
        }
    }

    // test for valid jump
    // doesn't have to be a jump move to be valid
    if (is_jump_move(pos, move)) {
        if (!is_valid_jump_move(pos, move, state, error_msg)) {
            return false;
        }
    }

    return true;
}

/*
 * Get all possible jumps for piece at position specified
 * 
 * @param  pos   Positing of piece to get jumps for
 * @param  state Board with pieces data
 * @param  jumps Possible jumps
 * @return number of valid jumps
 */
int get_piece_jumps(Position pos, int state[WIDTH][HEIGHT], 
                Position jumps[]) {

    int valid_jumps_cnt = 0;
    Position possible_jumps[4];
    char error_msg[255];

    if (!is_state_valid(state, error_msg)) {
        return valid_jumps_cnt;
    }

    // get the four possible grid jumps
    get_all_jumps(pos, possible_jumps);

    // test each grid
    for (int i = 0; i < 4; i++) {
        if (is_valid_move(pos, possible_jumps[i], state, error_msg)) {
            jumps[valid_jumps_cnt] = possible_jumps[i];
            valid_jumps_cnt++;
        }
    }

    return valid_jumps_cnt;
}

/*
 * Get all possible moves for piece at position specified
 * 
 * @param  pos   Positing of piece to get moves for
 * @param  state Board with pieces data
 * @param  moves Possible moves
 * @return number of valid moves
 */
int get_piece_moves(Position pos, int state[WIDTH][HEIGHT], 
                Position moves[]) {

    //printf("get_piece_moves(): %d\n", state[pos.y][pos.x]);

    int valid_moves_cnt = 0;
    Position possible_moves[8];
    char error_msg[255];

    if (!is_state_valid(state, error_msg)) {
        return valid_moves_cnt;
    }

    // get the eight possible grid moves
    get_all_moves(pos, possible_moves);

    // test each grid
    for (int i = 0; i < 8; i++) {
        if (is_valid_move(pos, possible_moves[i], state, error_msg)) {
            moves[valid_moves_cnt] = possible_moves[i];
            valid_moves_cnt++;
        }
    }

    return valid_moves_cnt;
}

/*
 * Get calculated results of moving a piece
 * 
 * @param  origin Original position of piece
 * @param  dest   New position of piece
 * @param  state  Current board with pieces data
 * @param  result Board with processed pieces data
 * @param  msg    Error information
 * @return true if success, else false
 */
bool get_result(Position origin, Position dest, 
                int state[WIDTH][HEIGHT], int result[WIDTH][HEIGHT], 
                Report *report) {

    char error_msg[255] = "";

    if (!is_state_valid(state, error_msg)) {
        report->is_error = true;
        strcpy(report->error_msg, error_msg);
        return false;
    }

    initialise_state(result);

    // validate move
    if (!is_valid_move(origin, dest, state, error_msg)) {
        report->is_error = true;
        strcpy(report->error_msg, error_msg);
        return false;
    }

    // copy positions from state to result
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (state[i][j] != 0) {
                result[i][j] = state[i][j];
            }
        }
    }

    // move piece
    result[dest.y][dest.x] = state[origin.y][origin.x];
    result[origin.y][origin.x] = 0;

    Position origin_pos = { origin.x, origin.y };
    report->piece_moved_old_pos = origin_pos;
    Position dest_pos = { dest.x, dest.y };
    report->piece_moved_new_pos = dest_pos;

    // remove pieces if captured
    if (abs(dest.y - origin.y) == 2) {

        report->is_jump = true;

        // 4 -> 6 ... 4 - 6 = -2 ... -2/2 = -1
        // 6 -> 4 ... 6 - 4 = 2 ... 2/2  = 1

        int result_y = origin.y - ((origin.y - dest.y)/2);
        int result_x = origin.x - ((origin.x - dest.x)/2);

        if (state[result_y][result_x] != 0) {

            result[result_y][result_x] = 0;

            Position captured = { result_x, result_y };
            report->piece_captured_pos = captured;

            // 4 - ((4 - 6)/2) = 4 - ((-2)/2) = 4 - -1 = 5
            // 3 - ((3 - 1)/2) = 3 - ((2)/2) = 3 - 1 = 2 

            report->is_capture = true;    
        }

    }

    // promote piece if on king's row
    if ((state[origin.y][origin.x] == 1) && (dest.y == 7)) {
        result[dest.y][dest.x] = 3;
        report->is_piece_promoted = true;
    }

    if ((state[origin.y][origin.x] == 2) && (dest.y == 0)) {
        result[dest.y][dest.x] = 4;
        report->is_piece_promoted = true;
    }

    return true;
}