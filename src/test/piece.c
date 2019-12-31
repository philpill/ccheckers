#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../piece.c"
#include "../utilities.c"
#include "../input.c"
#include "../game.c"

static void piece_init(void** state) {

    Piece pieces[24];

    init_pieces(pieces);

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