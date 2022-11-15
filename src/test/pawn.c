#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "pawn.h"

static void test_pawn_init(void** state) {
    Pawn pawns[24];
    Game game = { 0, 0, 0, 0 };
    char* filename = "1";
    pawn_init(&game, pawns, filename, 0);
    assert_int_equal(pawns[0].id, 1);
}

static void test_pawn_is_position_occupied(void** state) {
    Pawn pawns[24];
    Game game = { 0, 0, 0, 0 };
    char* filename = "1";
    pawn_init(&game, pawns, filename, 0);
    Position occupied_pos = { 0, 1 };
    Position empty_pos = { 0, 0 };
    bool is_occupied = false;
    bool is_empty = false;
    is_occupied = pawn_is_position_occupied(occupied_pos);
    is_empty = pawn_is_position_occupied(empty_pos);
    assert_true(is_occupied);
    assert_false(is_empty);
}

static void test_pawn_is_position_within_boundary(void** state) {
    Position pos_1 = {0, 0};
    bool is_within_1 = pawn_is_position_within_boundary(pos_1);
    assert_true(is_within_1);

    Position pos_2 = {-1, 0};
    bool is_within_2 = pawn_is_position_within_boundary(pos_2);
    assert_false(is_within_2);
}