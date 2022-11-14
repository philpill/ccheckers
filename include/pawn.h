#ifndef PAWN_H
#define PAWN_H

#include <stdbool.h>
#include "game.h"
#include "core.h"

typedef struct {
    int colour;
    bool is_king;
    bool is_captured;
    int x_pos;
    int y_pos;
    Position position;
    int id;
    int direction;
    bool is_selected;
} Pawn;

int pawn_init(Game *game, Pawn *pawns, char *filename, int direction);

void pawn_get_state_by_pawns(int state[WIDTH][HEIGHT]);

void pawn_select(Pawn *pawn);

void pawn_deselect_all();

Pawn *pawn_get_selected();

Pawn *pawn_capture_at_position(Position *pos);

bool pawn_select_by_position(Pawn *pawn, int x, int y);

bool pawn_get_by_position(Pawn **pawn, int x, int y);

bool pawn_is_selected();

bool pawn_is_selected_by_id(int id);

void pawn_move(Pawn *pawn, int x, int y);

bool pawn_is_player_dead(int colour);

int pawn_get_all_playable(Pawn *pawns);

#endif
