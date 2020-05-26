#ifndef FUNC_H_
#define FUNC_H_

#include <stdbool.h>
#include "pawn.h"

bool is_pawn_at_position(Pawn *pawn, int x, int y);
bool is_pawn_owned_by_player(Pawn *pawn, int player_colour);


#endif
