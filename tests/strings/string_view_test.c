#include <limits.h>
#include <stdint.h>
#include <string.h>

#include <includes/string_view.h>
#include <vendor/unity/unity_internals.h>
#include <vendor/unity/unity.h>

void setUp(void) {}
void tearDown(void) {}

static void test_empty_string_views_should_be_equal(void)
{
  cstdx_string_view_t a = {.len = 0, .base = NULL};
  cstdx_string_view_t b = {.len = 0, .base = NULL};

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

  cstdx_string_view_t a = {.len = N, .base = base1 };
  cstdx_string_view_t b = {.len = N, .base = base2 };

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

  cstdx_string_view_t a = {.len = N, .base = base1 };
  cstdx_string_view_t b = {.len = N, .base = base2 };

  TEST_ASSERT_EQUAL_UINT8(1, cstdx_string_view_equals(a, b));
  #undef N
}

static void test_empty_prefix_should_prefix_all_strings(void)
{
  const char *s = "hello, world\n";
  const uint64_t len = strlen(s);
  cstdx_string_view_t a = {.len=len, .base=s};
  cstdx_string_view_t null = {.len=0, .base=NULL};

  TEST_ASSERT_EQUAL_UINT8(1, cstdx_string_view_is_prefix(a, null));
}

static void test_prefix_cannot_be_larger_than_the_proper_string(void)
{
  const char *s = "hello";
  const uint64_t slen = strlen(s);
  const char *prefix = "hello world\n";
  const uint64_t prefixlen = strlen(prefix);

  cstdx_string_view_t sv = {.len=slen, .base=s};
  cstdx_string_view_t prefixv = {.len=prefixlen, .base=prefix};
  
  TEST_ASSERT_EQUAL_UINT8(0, cstdx_string_view_is_prefix(sv, prefixv));
}

static void test_is_prefix_can_find_prefixed_strings(void)
{
  
  const char *s = "hello world";
  const uint64_t slen = strlen(s);
  const char *prefix = "hello";
  const uint64_t prefixlen = strlen(prefix);

  cstdx_string_view_t sv = {.len=slen, .base=s};
  cstdx_string_view_t prefixv = {.len=prefixlen, .base=prefix};
  
  TEST_ASSERT_EQUAL_UINT8(1, cstdx_string_view_is_prefix(sv, prefixv));
}

static void test_can_split_a_string_on_its_parts(void)
{
  const char *s = "Hello, world!";
  const uint64_t slen = strlen(s);
  cstdx_string_view_t sv = (cstdx_string_view_t){.base=s, .len=slen};

  cstdx_string_view_iterable_t it = cstdx_string_view_split(sv, ',');

  cstdx_string_view_t hello = cstdx_string_view_from_cstr("Hello");
  cstdx_string_view_t world = cstdx_string_view_from_cstr(" world!");
  cstdx_string_view_t null = {0};

  TEST_ASSERT_EQUAL_UINT8(1, cstdx_string_view_equals(hello, cstdx_string_view_iterable_next(&it)));  
  TEST_ASSERT_EQUAL_UINT8(1, cstdx_string_view_equals(world, cstdx_string_view_iterable_next(&it)));
  TEST_ASSERT_EQUAL_UINT8(1, cstdx_string_view_equals(null, cstdx_string_view_iterable_next(&it)));
}

static void test_can_split_a_string_that_does_not_have_the_delimiter(void)
{
  const char *s = "Hello, world!\n";
  cstdx_string_view_t sv = cstdx_string_view_from_cstr(s);
  cstdx_string_view_t null = {0};

  cstdx_string_view_iterable_t it = cstdx_string_view_split(sv, '.');
  TEST_ASSERT_EQUAL_UINT8(1, cstdx_string_view_equals(sv, cstdx_string_view_iterable_next(&it)));
  TEST_ASSERT_EQUAL_UINT8(1, cstdx_string_view_equals(null, cstdx_string_view_iterable_next(&it)));
}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_empty_string_views_should_be_equal);
  RUN_TEST(test_different_strings_should_never_be_the_same);
  RUN_TEST(test_equal_strings_should_always_be_the_same);
  RUN_TEST(test_empty_prefix_should_prefix_all_strings);
  RUN_TEST(test_prefix_cannot_be_larger_than_the_proper_string);
  RUN_TEST(test_is_prefix_can_find_prefixed_strings);
  RUN_TEST(test_can_split_a_string_on_its_parts);
  RUN_TEST(test_can_split_a_string_that_does_not_have_the_delimiter);
  return UNITY_END();
}

