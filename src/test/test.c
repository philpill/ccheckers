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
        // cmocka_unit_test(test_get_piece_moves_works),
        // cmocka_unit_test(test_move_within_bounds),
        // cmocka_unit_test(test_move_unoccupied_spaces),
        // cmocka_unit_test(test_move_forward_0),
        // cmocka_unit_test(test_move_forward_1_l),
        // cmocka_unit_test(test_move_forward_1_r),
        // cmocka_unit_test(test_move_forward_2),
        // cmocka_unit_test(test_calibrate_position),
        // cmocka_unit_test(test_jump_move),
        // cmocka_unit_test(test_invalid_jump_move),
        // cmocka_unit_test(test_file_load),
        cmocka_unit_test(test_get_result_works)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
