#include <includes/string_view.h>

// TODO: Benchmark it...
uint8_t cstdx_string_view_equals(cstdx_string_view_t a, cstdx_string_view_t b)
{
  if (a.len != b.len)   return 0;
  if (a.base == b.base) return 1;

  for (uint64_t i = 0; i < a.len; ++i)
  {
    if (a.base[i] != b.base[i]) return 0;
  }
  return 1;
}

// TODO: Benchmark it...
uint8_t cstdx_string_view_is_prefix(cstdx_string_view_t a, cstdx_string_view_t prefix)
{
  if (prefix.len == 0)
  {
    return 1;
  }

  if (prefix.len > a.len)
  {
    return 0;
  }

  for (uint64_t i = 0; i < prefix.len; ++i)
  {
    if (prefix.base[i] != a.base[i])
    {
      return 0;
    }
  }

  return 1;
}
