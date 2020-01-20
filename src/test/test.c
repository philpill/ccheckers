#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
//#include "./piece.c"
#include "./core.c"

// https://jagssoftware.wordpress.com/2018/02/20/cmocka-testing-framework-example/

int main(void)
{
    const struct CMUnitTest tests[] =
    {
        //cmocka_unit_test(test_piece_init),
        cmocka_unit_test(test_get_moves_works),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
