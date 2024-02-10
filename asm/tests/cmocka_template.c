#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

static void UNIT_TEST_NAME(void **state) {

}

int main(void) {
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(UNIT_TEST_NAME),
  };
  return cmocka_run_group_tests_name("CHANGE NAME", tests, NULL, NULL);
}