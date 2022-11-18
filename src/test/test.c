#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "core.c"
#include "options.c"
#include "pawn.c"

// https://jagssoftware.wordpress.com/2018/02/20/cmocka-testing-framework-example/

int main(void)
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(test_get_pawn_moves_works),
        cmocka_unit_test(test_move_within_bounds),
        cmocka_unit_test(test_move_unoccupied_spaces),
        cmocka_unit_test(test_move_forward_0),
        cmocka_unit_test(test_move_forward_1_l),
        cmocka_unit_test(test_move_forward_1_r),
        cmocka_unit_test(test_move_forward_2),
        cmocka_unit_test(test_move_forward_3),
        cmocka_unit_test(test_calibrate_position),
        cmocka_unit_test(test_jump_move),
        cmocka_unit_test(test_invalid_jump_move),
        cmocka_unit_test(test_file_load),
        cmocka_unit_test(test_get_result_works),
        cmocka_unit_test(test_capture),
        cmocka_unit_test(test_board_orientation),
        cmocka_unit_test(test_promote_king),
        cmocka_unit_test(test_initial_population_0),
        cmocka_unit_test(test_get_jumps_works),
        cmocka_unit_test(test_get_options_length),
        cmocka_unit_test(test_get_options_content),
        cmocka_unit_test(test_get_set_option_mode),

        cmocka_unit_test(test_pawn_get_backward_right_pos),
        cmocka_unit_test(test_pawn_get_backward_left_pos),
        cmocka_unit_test(test_pawn_get_forward_right_pos),
        cmocka_unit_test(test_pawn_get_forward_left_pos),
        cmocka_unit_test(test_pawn_is_position_occupied),
        cmocka_unit_test(test_pawn_is_position_within_boundary)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
