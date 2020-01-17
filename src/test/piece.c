#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../piece.h"
#include "../utilities.h"
#include "../input.h"
#include "../game.h"
#include "../log.h"

static void piece_init(void** state) {

    Piece pieces[24];

    Game game = { 0, 0, 0, 0 };

    char *filename = "1";

    init_piece(&game, pieces, filename, 0);

    assert_int_equal(pieces[0].id, 1);
}

int main(void)
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(piece_init),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
