#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "core.h"

/*
 * Initialise board to zeroes
 * 
 * @param  state Board to clear of pawns
 */
static void initialise_state(int state[WIDTH][HEIGHT]) {
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            state[i][j] = STATE_EMPTY;
        }
    }
}

/*
 * Validate state of board and pawns
 *  - if there are not more than the max number of pawns
 * 
 * @param  state     Board and pawns to validate
 * @param  error_msg Reason for failure
 * @return true is state of board is valid
 */
static bool is_state_valid(int state[WIDTH][HEIGHT], char error_msg[]) {

    int num_pawns = 0;

    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            if (state[i][j] != STATE_EMPTY) {
                num_pawns++;
            }
        }
    }

    if (num_pawns > NUM_PAWNS) {
        strcpy(error_msg, "number of pawns in given state exceed expected value");
        return false;
    }

    // check pawns are not on the wrong squares
    // i.e. black squares only
    // bottom left and top right

    return true;
}

/*
 * Get the 8 theoretical possible squares for a pawn to 
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
 * Get the 4 theoretical possible squares for a pawn to 
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
 * by another pawn
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
 * Check if pawn is a king
 * 
 * @param  pawn Value from state data
 * @return true is pawn is a king 
 */

static bool is_king(int pawn) {
    return pawn == STATE_WHITE_KING || pawn == STATE_BLACK_KING;
}

/*
 * Check is pawnis moving forwards or backwards
 * 
 * @param  pawn Value from state data
 * @param  pos   Original position
 * @param  move  Destination position
 * @return true is proposed move is forward advance
 */
static bool is_forward_move(int pawn, Position pos, Position move) {

    //printf("is_forward_move(): ");

    bool is_down = move.y > pos.y;

    //printf("%d -> %d = %d, %d\n", pos.y, move.y, is_down, pawn);

    bool is_forward_move = ((pawn == STATE_WHITE_PAWN && is_down) 
                            || (pawn == STATE_WHITE_KING && is_down) 
                            || (pawn == STATE_BLACK_PAWN && !is_down)
                            || (pawn == STATE_BLACK_KING && !is_down));

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
 * @param  state     Board with pawns data
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
    int pawn = state[pos.y][pos.x];
    int intervening_pawn = state[y][x];
    if (intervening_pawn == STATE_EMPTY) {
        strcpy(error_msg, "No intervening pawn to jump");
        return false;
    } else {
        if ((pawn == STATE_WHITE_PAWN || pawn == STATE_WHITE_KING)
            && (intervening_pawn == STATE_WHITE_PAWN || intervening_pawn == STATE_WHITE_KING)) {
            strcpy(error_msg, "Cannot jump friendly pawn");
            return false;
        } else if ((pawn == STATE_BLACK_PAWN || pawn == STATE_BLACK_KING)
            && (intervening_pawn == STATE_BLACK_PAWN || intervening_pawn == STATE_BLACK_KING)) {
            strcpy(error_msg, "Cannot jump friendly pawn");
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
 * @param  state     Board with pawns data
 * @param  error_msg Reason for failure
 * @return true if move is valid
 */
static bool is_valid_move(Position pos, Position move, int state[WIDTH][HEIGHT], 
                            char error_msg[]) {

    //printf("----------\n[%d, %d]\n", move.x, move.y);

    if (!is_move_within_bounds(move)) return false;
    if (is_space_occupied(move, state)) return false; 

    // test for forward movement
    bool is_pawn_king = is_king(state[pos.y][pos.x]);
    bool is_pawn_forward_move = is_forward_move(state[pos.y][pos.x], pos, move); 
    if (!is_pawn_forward_move) {
        if (!is_pawn_king) { 
            strcpy(error_msg, "Non-king pawn cannot move backwards. ");
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
 * Get all possible jumps for pawn at position specified
 * 
 * @param  pos   Positing of pawn to get jumps for
 * @param  state Board with pawns data
 * @param  jumps Possible jumps
 * @return number of valid jumps
 */
int get_pawn_jumps(Position pos, int state[WIDTH][HEIGHT], 
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
 * Get all possible moves for pawn at position specified
 * 
 * @param  pos   Positing of pawn to get moves for
 * @param  state Board with pawns data
 * @param  moves Possible moves
 * @return number of valid moves
 */
int get_pawn_moves(Position pos, int state[WIDTH][HEIGHT], 
                Position moves[]) {

    //printf("get_pawn_moves(): %d\n", state[pos.y][pos.x]);

    int valid_moves_cnt = 0;
    Position possible_moves[8];
    char error_msg[255] = "";

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
 * Get calculated results of moving a pawn
 * 
 * @param  origin Original position of pawn
 * @param  dest   New position of pawn
 * @param  state  Current board with pawns data
 * @param  result Board with processed pawns data
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
            if (state[i][j] != STATE_EMPTY) {
                result[i][j] = state[i][j];
            }
        }
    }

    // move pawn
    result[dest.y][dest.x] = state[origin.y][origin.x];
    result[origin.y][origin.x] = STATE_EMPTY;

    Position origin_pos = { origin.x, origin.y };
    report->pawn_moved_old_pos = origin_pos;
    Position dest_pos = { dest.x, dest.y };
    report->pawn_moved_new_pos = dest_pos;

    // remove pawns if captured
    if (abs(dest.y - origin.y) == 2) {

        report->is_jump = true;

        // 4 -> 6 ... 4 - 6 = -2 ... -2/2 = -1
        // 6 -> 4 ... 6 - 4 = 2 ... 2/2  = 1

        int result_y = origin.y - ((origin.y - dest.y)/2);
        int result_x = origin.x - ((origin.x - dest.x)/2);

        if (state[result_y][result_x] != STATE_EMPTY) {

            result[result_y][result_x] = STATE_EMPTY;

            Position captured = { result_x, result_y };
            report->pawn_captured_pos = captured;

            // 4 - ((4 - 6)/2) = 4 - ((-2)/2) = 4 - -1 = 5
            // 3 - ((3 - 1)/2) = 3 - ((2)/2) = 3 - 1 = 2 

            report->is_capture = true;    
        }
    }

    // promote pawn if on king's row
    if ((state[origin.y][origin.x] == STATE_BLACK_PAWN) && (dest.y == KINGS_ROW_BLACK)) {
        result[dest.y][dest.x] = STATE_BLACK_KING;
        report->is_pawn_promoted = true;
    }

    if ((state[origin.y][origin.x] == STATE_WHITE_PAWN) && (dest.y == KINGS_ROW_WHITE)) {
        result[dest.y][dest.x] = STATE_WHITE_KING;
        report->is_pawn_promoted = true;
    }

    return true;
}