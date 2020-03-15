#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../core.h"
#include "../resource.h"

static void test_get_piece_moves_works(void** state) {

    Position pos = { 1, 1 };

    int map[8][8];

    load_file("0", map);

    Position moves[8];

    int moves_cnt = get_piece_moves(pos, map, moves);

    assert_in_range(moves_cnt, 0, 8);
}

static void test_move_within_bounds(void** state) {

    Position pos = { 0, 0 };

    int map[8][8];

    load_file("0", map);

    map[0][0] = 1;

    Position moves[8];

    int moves_cnt = get_piece_moves(pos, map, moves);

    assert_int_equal(moves_cnt, 1);
}

static void test_move_unoccupied_spaces(void** state) {

    Position pos = { 4, 4 };

    int map[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 2, 0},
        {0, 0, 0, 2, 0, 2, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 0, 2, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    Position moves[8];

    int moves_cnt = get_piece_moves(pos, map, moves);

    assert_int_equal(moves_cnt, 1);
}

static void test_move_forward_1_l(void **state) {

    Position pos = { 0, 2 };

    int map[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    Position moves[8];

    int moves_cnt = get_piece_moves(pos, map, moves);

    assert_int_equal(moves_cnt, 1);
}

static void test_move_forward_1_r(void **state) {

    Position pos = { 7, 1 };

    int map[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    Position moves[8];

    int moves_cnt = get_piece_moves(pos, map, moves);

    assert_int_equal(moves_cnt, 1);
}

static void test_move_forward_2(void **state) {

    Position pos = { 2, 0 };

    int map[8][8] = {
        {0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    Position moves[8];

    int moves_cnt = get_piece_moves(pos, map, moves);

    assert_int_equal(moves_cnt, 2);
}

static void test_move_forward_0(void **state) {

    Position pos = { 1, 7 };

    int map[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0},
    };

    Position moves[8];

    int moves_cnt = get_piece_moves(pos, map, moves);

    assert_int_equal(moves_cnt, 0);
}

static void test_calibrate_position(void **state) {

    Position pos = { 0, 0 };

    int map[8][8] = {
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    Position moves[8];

    int moves_cnt = get_piece_moves(pos, map, moves);

    assert_int_equal(moves_cnt, 1);
}

static void test_jump_move(void **state) {

    Position pos = { 0, 0 };

    int map[8][8] = {
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 2, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    Position moves[8];

    int moves_cnt = get_piece_moves(pos, map, moves);

    assert_int_equal(moves_cnt, 1);
}

static void test_invalid_jump_move(void **state) {

    Position pos = { 0, 0 };

    int map[8][8] = {
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    Position moves[8];

    int moves_cnt = get_piece_moves(pos, map, moves);

    assert_int_equal(moves_cnt, 0);
}

static void test_file_load(void **state) {

    Position pos = { 1, 1 };

    int map[8][8];

    load_file("3", map);

    Position moves[8];

    int moves_cnt = get_piece_moves(pos, map, moves);

    assert_int_equal(moves_cnt, 2);
}

static void test_get_result_works(void **state) {

    Position origin = { 0, 0 };
    Position dest = { 1, 1 };

    int result_data[8][8];

    char msg[255];

    int state_data[8][8] = {
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    Report report = {};

    int result = get_result(origin, dest, state_data, result_data, report);

    assert_int_equal(result, 0);

    assert_int_equal(result_data[1][1], 1);
}

static void test_capture(void **state) {

    Position origin = { 0, 0 };
    Position dest = { 2, 2 };

    int result_data[8][8];

    char msg[255];

    int state_data[8][8] = {
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 2, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    Report report = {};

    // piece in expected position
    assert_int_equal(state_data[0][0], 1); 

    // target piece in expected position
    assert_int_equal(state_data[1][1], 2); 

    // destination position empty
    assert_int_equal(state_data[2][2], 0); 

    int result = get_result(origin, dest, state_data, result_data, report);

    // no errors
    assert_int_equal(result, 0); 

    // target piece removed from board
    assert_int_equal(result_data[1][1], 0); 

    // piece moved from original position
    assert_int_equal(result_data[0][0], 0); 

    // piece moved to new position
    assert_int_equal(result_data[2][2], 1); 
}

static void test_board_orientation(void **state) {

    Position origin = { 0, 2 };
    Position dest = { 1, 3 };

    int result_data[8][8];

    char msg[255];

    int state_data[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    Report report = {};

    int result = get_result(origin, dest, state_data, result_data, report);

    assert_int_equal(result, 0);

    // x and y are swapped round to what you might expect ...
    // i.e. first ordinal is y and second is x
    assert_int_equal(result_data[3][1], 1); 
}

static void test_promote_king(void **state) {

    Position origin = { 0, 6 };
    Position dest = { 1, 7 };

    int result_data[8][8];

    char msg[255];

    int state_data[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    Report report = { };

    int result = get_result(origin, dest, state_data, result_data, report);

    // piece promoted
    assert_int_equal(result_data[7][1], 3); 
}