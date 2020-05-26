#include <stdbool.h>
#include "func.h"
#include "pawn.h"

bool is_pawn_at_position(Pawn *pawn, int x, int y) {
    return pawn->position.x == x && pawn->position.y == y;
}

bool is_pawn_owned_by_player(Pawn *pawn, int player_colour) {
    return pawn->colour == player_colour;
}

