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

int init_pawn(Game *game, Pawn *pawns, char *filename, int direction);

void get_state_by_pawns(int state[WIDTH][HEIGHT]);

void select_pawn(Pawn *pawn);

void deselect_pawn();

Pawn *get_selected_pawn();

Pawn *capture_pawn_at_position(Position *pos);

bool select_pawn_by_position(Pawn *pawn, int x, int y);

bool get_pawn_by_position(Pawn **pawn, int x, int y);

bool is_pawn_selected();

bool is_pawn_selected_by_id(int id);

void move_pawn(Pawn *pawn, int x, int y);

bool is_player_dead(int colour);

#endif
