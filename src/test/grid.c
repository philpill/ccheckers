#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../grid.h"

// ┌─┬┐│├┼┤└┴┘

static void test_get_first_character(void** state) {
    char row[255];
    row[0] = '\0';
    get_top_row(row, 1, 0, 0);
    assert_string_equal(row, "┌─┐");
}


static void test_get_top_row(void** state) {
    char row[255];
    row[0] = '\0';
    get_top_row(row, 8, 0, 0);
    assert_string_equal(row, "┌─┬─┬─┬─┬─┬─┬─┬─┐");
}

static void test_get_spacer_row(void** state) {
    char row[255];
    row[0] = '\0';
    get_spacer_row(row, 4, 0, 1);
    assert_string_equal(row, "│   │   │   │   │");
}

static void test_get_middle_row(void** state) {
    char row[255];
    row[0] = '\0';
    get_middle_row(row, 3, 0, 0);
    assert_string_equal(row, "├─┼─┼─┤");
}

static void test_get_bottom_row(void** state) {
    char row[255];
    row[0] = '\0';
    get_bottom_row(row, 2, 0, 1);
    assert_string_equal(row, "└───┴───┘");
}
