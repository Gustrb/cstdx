#include <limits.h>

#include <includes/slice.h>
#include <vendor/unity/unity.h>

void setUp(void) {}
void tearDown(void) {}

static void test_sum_adds_all_elements(void)
{
  uint8_t data[] = {1, 2, 3, 4};
  cstdx_uint8_t_slice s = {.base = data, .len = 4};

  TEST_ASSERT_EQUAL_UINT64(10, cstdx_uint8_t_slice_sum(s));
}

static void test_sum_of_empty_slice_is_zero(void)
{
  uint8_t data[] = {1, 2, 3, 4};
  cstdx_uint8_t_slice s = {.base = data, .len = 0};

  TEST_ASSERT_EQUAL_UINT64(0, cstdx_uint8_t_slice_sum(s));
}

static void test_sum_widens_past_element_type(void)
{
  uint8_t data[] = {255, 255, 255};
  cstdx_uint8_t_slice s = {.base = data, .len = 3};

  TEST_ASSERT_EQUAL_UINT64(765, cstdx_uint8_t_slice_sum(s));
}

static void test_sum_overflows(void)
{
  uint64_t data[] = {UINT64_MAX, 1};
  cstdx_uint64_t_slice s = {.base = data, .len = 2};
  TEST_ASSERT_EQUAL_UINT64(0, cstdx_uint64_t_slice_sum(s));
}

static void test_sum_first_1000_elements(void)
{
  const uint64_t total = 1000;
  const uint64_t expected = (total * (total + 1))/2;
  uint64_t data[1000] = {0};

  for (uint64_t i = 0; i < total; ++i)
  {
    data[i] = i+1;
  }

  cstdx_uint64_t_slice s = {.base = data, .len = 1000 };

  TEST_ASSERT_EQUAL_UINT64(expected, cstdx_uint64_t_slice_sum(s));
}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_sum_adds_all_elements);
  RUN_TEST(test_sum_of_empty_slice_is_zero);
  RUN_TEST(test_sum_widens_past_element_type);
  RUN_TEST(test_sum_overflows);
  RUN_TEST(test_sum_first_1000_elements);
  return UNITY_END();
}
