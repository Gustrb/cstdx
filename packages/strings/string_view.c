#include <includes/string_view.h>
#include <string.h>

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

cstdx_string_view_iterable_t cstdx_string_view_split(cstdx_string_view_t base, char delim)
{
  return (cstdx_string_view_iterable_t){.delim=delim, .total=base};
}

cstdx_string_view_t cstdx_string_view_iterable_next(cstdx_string_view_iterable_t *it)
{
  if (it->total.len == 0) return (cstdx_string_view_t){0};

  uint64_t len = 0;
  const char *ptr = it->total.base;
  for (len = 0; len < it->total.len; ++len)
  {
    if (it->total.base[len] == it->delim)
    {
      break;
    }
  }

  if (it->total.len - len != 0)
  {
    // Note: skip the comma
    it->total.base = ptr + len + 1;
    it->total.len = it->total.len - len - 1, 0;
  }
  else
  {
    it->total.base = NULL;
    it->total.len = 0;
  }

  return (cstdx_string_view_t){.base=ptr, .len=len};
}

cstdx_string_view_t cstdx_string_view_from_cstr(const char *s)
{
  uint64_t l = strlen(s);
  return (cstdx_string_view_t){.base=s, .len=l};
}
