#include <stdlib.h>
#include "utilities.h"
#include "piece.h"

/*
 * Get middle position of two other positions.
 * Only valid if there is exactly one square
 * between the two given parameters.
 *
 * This could be trivial, but I win't know till
 * after I've tried this ...
 *
 * @param  intervening_pos position to populate if valid
 * @param  a_pos first position
 * @param  b_pos second position
 * @return true if position is valid
 */
bool get_intervening_position(Position *intervening_pos, Position *a_pos, Position *b_pos) {
    int is_valid = ((abs(a_pos->x-b_pos->x) == 2)
                        && (abs(a_pos->y-b_pos->y) == 2));
    if (is_valid) {
        intervening_pos->x = (a_pos->x+b_pos->x)/2;
        intervening_pos->y = (a_pos->y+b_pos->y)/2;
    }
    return is_valid;
}