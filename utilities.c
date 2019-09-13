#include <stdlib.h>
#include "utilities.h"
#include "piece.h"

/*
 * Function: get_intervening_position
 *
 * Get middle position of two other positions.
 * Only valid if there is exactly one square
 * between the two given parameters.
 *
 * This could be trivial, but I win't know till
 * after I've tried this ...
 *
 * intervening_pos: position to populate if valid
 * a_pos: first position
 * b_pos: second position
 */
int get_intervening_position(Position *intervening_pos, Position *a_pos, Position *b_pos) {
    int is_valid = ((abs(a_pos->x-b_pos->x) == 2)
                        && (abs(a_pos->y-b_pos->y) == 2));
    if (is_valid) {
        intervening_pos->x = (a_pos->x+b_pos->x)/2;
        intervening_pos->y = (a_pos->y+b_pos->y)/2;
    }
    return is_valid;
}