#include "vendor/unity/unity_internals.h"
#include <limits.h>

#include <includes/string_view.h>
#include <vendor/unity/unity.h>

void setUp(void) {}
void tearDown(void) {}

static void test_empty_string_views_should_be_equal(void)
{
  cstdx_string_view_h a = {.len = 0, .base = NULL};
  cstdx_string_view_h b = {.len = 0, .base = NULL};

  TEST_ASSERT_EQUAL_UINT8(1, cstdx_string_view_equals(a, b));

  a.len = 1; b.len = 1;
  TEST_ASSERT_EQUAL_UINT8(1, cstdx_string_view_equals(a, b));
}

static void test_different_strings_should_never_be_the_same(void)
{
  #define N 1024

  char base1[N] = {0};
  char base2[N] = {0};

  for (uint64_t i = 0; i < N; ++i)
  {
    base1[i] = 'a';
    base2[i] = base1[i] + 1;
  }

  cstdx_string_view_h a = {.len = N, .base = base1 };
  cstdx_string_view_h b = {.len = N, .base = base2 };

  TEST_ASSERT_EQUAL_UINT8(0, cstdx_string_view_equals(a, b));
  #undef N
}

static void test_equal_strings_should_always_be_the_same(void)
{
  #define N 1024

  char base1[N] = {0};
  char base2[N] = {0};

  for (uint64_t i = 0; i < N; ++i)
  {
    base1[i] = 'a';
    base2[i] = base1[i];
  }

  cstdx_string_view_h a = {.len = N, .base = base1 };
  cstdx_string_view_h b = {.len = N, .base = base2 };

  TEST_ASSERT_EQUAL_UINT8(1, cstdx_string_view_equals(a, b));
  #undef N
}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_empty_string_views_should_be_equal);
  RUN_TEST(test_different_strings_should_never_be_the_same);
  RUN_TEST(test_equal_strings_should_always_be_the_same);
  return UNITY_END();
}

