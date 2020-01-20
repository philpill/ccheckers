#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../piece.h"

static void test_piece_init(void** state) {

    Piece pieces[24];

    Game game = { 0, 0, 0, 0 };

    char *filename = "1";

    init_piece(&game, pieces, filename, 0);

    assert_int_equal(pieces[0].id, 1);
}
