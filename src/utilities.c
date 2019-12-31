#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "utilities.h"
#include "piece.h"
#include "log.h"

/*
 * Get middle position of two other positions.
 * Only valid if there is exactly one square
 * between the two given parameters.
 *
 * This could be trivial, but I won't know till
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



/*
 * Get unique number to use for game id
 * https://stackoverflow.com/a/822368
 * 
 * @return integer for id 
 */
int get_id() {

    srand(time(NULL));   // Initialization, should only be called once.
    int r = rand();      // Returns a pseudo-random integer between 0 and RAND_MAX.

    return r;
}

int get_timestamp(char *buf) {

    time_t ltime; /* calendar time */
    ltime=time(NULL); /* get current cal time */

    return snprintf(buf, 30, "%s", asctime( localtime(&ltime) ));
}