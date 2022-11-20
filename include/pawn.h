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

bool  pawn_can_move_forward_right(Pawn* pawn);
bool  pawn_can_move_forward_left(Pawn* pawn);
bool  pawn_can_move_backward_right(Pawn* pawn);
bool  pawn_can_move_backward_left(Pawn* pawn);
bool  pawn_get_by_position(Pawn **pawn, int x, int y);
bool  pawn_is_at_position(Pawn* pawn, Position pos);
bool  pawn_is_owned_by_current_player(Pawn* pawn);
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
void  pawn_get_forward_right_pos(int direction, Position* pos, Position* pos_fr);
void  pawn_get_forward_left_pos(int direction, Position* pos, Position* pos_fl);
void  pawn_get_backward_right_pos(int direction, Position* pos, Position* pos_br);
void  pawn_get_backward_left_pos(int direction, Position* pos, Position* pos_bl);
void  pawn_get_state(int state[WIDTH][HEIGHT]);
void  pawn_move(Pawn *pawn, Position pos);
void  pawn_move_by_xy(Pawn *pawn, int x, int y);
void  pawn_select(Pawn *pawn);

#endif
