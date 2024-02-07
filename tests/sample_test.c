#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

static void compare_integer_pass(void **state) {
  int i = 4;

  assert_int_equal(i, 4);
}

static void compare_integer_failure(void **state) {
  int i = 4;

  assert_int_not_equal(i, 5);
}

static void compare_fail(void **state) {
  int i = 4;

  assert_int_equal(i, 5);
}

int main(void) {
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(compare_integer_pass),
    cmocka_unit_test(compare_integer_failure),
    cmocka_unit_test(compare_fail),
  };
  return cmocka_run_group_tests_name("compare integer tests", tests, NULL, NULL);
}