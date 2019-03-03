#ifndef UTILITIES_H_
#define UTILITIES_H_

#include "piece.h"

bool get_intervening_position(Position *intervening_pos,
                                Position *a_pos, Position *b_pos);

int get_id();

int get_timestamp(char *buf);

#endif