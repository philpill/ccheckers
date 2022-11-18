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

static void test_pawn_get_forward_right_pos(void** state) {
    int direction = 1;
    Position current_pos = {1, 1};
    Position calculated_pos;
    pawn_get_forward_right_pos(direction, &current_pos, &calculated_pos);
    assert_int_equal(calculated_pos.x, 0);
    assert_int_equal(calculated_pos.y, 2);

    direction = -1;
    pawn_get_forward_right_pos(direction, &current_pos, &calculated_pos);
    assert_int_equal(calculated_pos.x, 2);
    assert_int_equal(calculated_pos.y, 0);
}

static void test_pawn_get_forward_left_pos(void** state) {
    int direction = 1;
    Position current_pos = {5, 7};
    Position calculated_pos;
    pawn_get_forward_left_pos(direction, &current_pos, &calculated_pos);
    assert_int_equal(calculated_pos.x, 6);
    assert_int_equal(calculated_pos.y, 8);

    direction = -1;
    pawn_get_forward_left_pos(direction, &current_pos, &calculated_pos);
    assert_int_equal(calculated_pos.x, 4);
    assert_int_equal(calculated_pos.y, 6);
}

static void test_pawn_get_backward_left_pos(void** state) {
    int direction = 1;
    Position current_pos = {4, 8};
    Position calculated_pos;
    pawn_get_backward_left_pos(direction, &current_pos, &calculated_pos);
    assert_int_equal(calculated_pos.x, 5);
    assert_int_equal(calculated_pos.y, 7);

    direction = -1;
    pawn_get_backward_left_pos(direction, &current_pos, &calculated_pos);
    assert_int_equal(calculated_pos.x, 3);
    assert_int_equal(calculated_pos.y, 9);
}

static void test_pawn_get_backward_right_pos(void** state) {
    int direction = 1;
    Position current_pos = {6, 3};
    Position calculated_pos;
    pawn_get_backward_right_pos(direction, &current_pos, &calculated_pos);
    assert_int_equal(calculated_pos.x, 5);
    assert_int_equal(calculated_pos.y, 2);

    direction = -1;
    pawn_get_backward_right_pos(direction, &current_pos, &calculated_pos);
    assert_int_equal(calculated_pos.x, 7);
    assert_int_equal(calculated_pos.y, 4);
}

static void test_pawn_is_position_within_boundary(void** state) {

    bool is_within = false;

    Position pos_1 = {0, 0};
    is_within = pawn_is_position_within_boundary(pos_1);
    assert_true(is_within);

    Position pos_2 = {0, 7};
    is_within = pawn_is_position_within_boundary(pos_2);
    assert_true(is_within);

    Position pos_3 = {7, 0};
    is_within = pawn_is_position_within_boundary(pos_3);
    assert_true(is_within);

    Position pos_4 = {7, 7};
    is_within = pawn_is_position_within_boundary(pos_4);
    assert_true(is_within);

    Position pos_5 = {-1, 0};
    is_within = pawn_is_position_within_boundary(pos_5);
    assert_false(is_within);

    Position pos_6 = {0, -1};
    is_within = pawn_is_position_within_boundary(pos_6);
    assert_false(is_within);

    Position pos_7 = {8, 0};
    is_within = pawn_is_position_within_boundary(pos_7);
    assert_false(is_within);

    Position pos_8 = {0, 8};
    is_within = pawn_is_position_within_boundary(pos_8);
    assert_false(is_within);

    Position pos_9 = {-1, -1};
    is_within = pawn_is_position_within_boundary(pos_9);
    assert_false(is_within);

    Position pos_10 = {8, 8};
    is_within = pawn_is_position_within_boundary(pos_10);
    assert_false(is_within);
}