#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../core.h"
#include "../resource.h"

static void test_get_moves_works(void** state) {

    Position pos = { 1, 1 };

    int map[8][8];

    load_file("0", map);

    Position moves[8];

    int moves_cnt = get_moves(pos, map, moves);

    assert_int_equal(moves_cnt, 0);
}
