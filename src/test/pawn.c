#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "pawn.h"

static void test_pawn_init(void** state) {

    Pawn pawns[24];

    Game game = { 0, 0, 0, 0 };

    char *filename = "1";

    pawn_init(&game, pawns, filename, 0);

    assert_int_equal(pawns[0].id, 1);
}
