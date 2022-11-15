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

bool  pawn_get_by_position(Pawn **pawn, int x, int y);
bool  pawn_is_player_dead(int colour);
bool  pawn_is_position_occupied(Position pos);
bool  pawn_is_position_within_boundary(Position pos);
bool  pawn_is_selected_by_id(int id);
bool  pawn_is_selected();
bool  pawn_select_by_position(Pawn *pawn, int x, int y);
int   pawn_get_all_playable(Pawn *pawns);
int   pawn_init(Game *game, Pawn *pawns, char *filename, int direction);
Pawn* pawn_capture_at_position(Position *pos);
Pawn* pawn_get_selected();
void  pawn_deselect_all();
void  pawn_get_state_by_pawns(int state[WIDTH][HEIGHT]);
void  pawn_move(Pawn *pawn, int x, int y);
void  pawn_select(Pawn *pawn);

#endif
