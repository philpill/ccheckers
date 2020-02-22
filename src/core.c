#include "core.h"
#include <stdio.h>

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
 * @param  state Board and pieces to validate
 * @return true is state of board is valid
 */
static bool is_state_valid(int state[WIDTH][HEIGHT]) {

    int num_pieces = 0;

    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            if (state[i][j] != 0) {
                num_pieces++;
            }
        }
    }

    if (num_pieces > NUM_PIECES) {
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

    printf("is_move_within_bounds(): %d\n", is_within);

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
    is_occupied = state[move.x][move.y] != 0;

    printf("is_space_occupied(): %d\n", is_occupied);

    if (is_occupied) {
    printf("--> %d\n", state[move.x][move.y]);

    }

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

    printf("is_forward_move(): ");

    bool is_down = move.y > pos.y;

    //printf("%d -> %d = %d\n", pos.y, move.y, is_down);

    bool is_forward_move = ((piece == 1 || piece == 3) && is_down);

    printf("%d\n", is_forward_move);

    return is_forward_move;
}

/*
 * Check if proposed move is valid, given current game state
 * 
 * @param  pos  Current position
 * @param  move Proposed move
 * @return true if move is valid
 */
static bool is_valid_move(Position pos, Position move, int state[WIDTH][HEIGHT]) {

    printf("----------\n[%d, %d]\n----------\n", move.x, move.y);

    if (!is_move_within_bounds(move)) return false;
    if (is_space_occupied(move, state)) return false; 

    // test for forward movement
    bool is_piece_king = is_king(state[pos.x][pos.y]);
    bool is_piece_forward_move = is_forward_move(state[pos.x][pos.y], pos, move); 
    if (!is_piece_forward_move && !is_piece_king) return false;

    // test for valid jump

    return true;
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

    int valid_moves_cnt = 0;
    Position possible_moves[8];

    if (!is_state_valid(state)) {
        return valid_moves_cnt;
    }

    // get the eight possible grid moves
    get_all_moves(pos, possible_moves);

    // test each grid
    for (int i = 0; i < 8; i++) {
        if (is_valid_move(pos, possible_moves[i], state)) {
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
 * @return true if success  
 */
bool get_result(Position origin, Position dest, 
                int state[WIDTH][HEIGHT], int result[WIDTH][HEIGHT], 
                char *msg[]) {

    if (!is_state_valid(state)) {
        return false;
    }

    initialise_state(result);

    return false;
}
