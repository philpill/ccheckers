#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../options.h"

static void init_test_options(char **options) {

    for(int i = 0; i < 10; i++) {

        options[i] = malloc(sizeof(char) * 100);
    }
}

static void test_get_options_length(void **state) {

    char **options = malloc(sizeof(char*) * 10);

    init_test_options(options);

    int num_options = get_options(options);

    assert_int_equal(num_options, 3);
}

static void test_get_options_content(void **state) {

    char **options = malloc(sizeof(char*) * 10);

    init_test_options(options);

    get_options(options);

    assert_string_equal(options[1], "New Game");
}

static void test_get_set_option_mode(void **state) {

    OPTION_MODE mode = {0};

    mode = get_option_mode();

    assert_int_equal(mode, general);

    set_option_mode(new_game);

    mode = get_option_mode();

    assert_int_equal(mode, new_game);
}