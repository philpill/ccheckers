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