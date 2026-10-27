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
  return (cstdx_string_view_iterable_t){.delim.c=delim, .tag=CSTDX_VIEW_ITERABLE_TAG_CHAR, .total=base};
}

cstdx_string_view_iterable_t cstdx_string_view_split_string_view(cstdx_string_view_t base, cstdx_string_view_t delim)
{
  return (cstdx_string_view_iterable_t){.delim.sv=delim, .tag=CSTDX_VIEW_ITERABLE_TAG_SV, .total=base};
}

static cstdx_string_view_t cstdx_string_view_iterable_next_string_view(cstdx_string_view_iterable_t *it);

cstdx_string_view_t cstdx_string_view_iterable_next(cstdx_string_view_iterable_t *it)
{
  if (it->total.len == 0) return (cstdx_string_view_t){0};
  if (it->tag == CSTDX_VIEW_ITERABLE_TAG_SV) return cstdx_string_view_iterable_next_string_view(it);

  uint64_t len = 0;
  const char *ptr = it->total.base;
  for (len = 0; len < it->total.len; ++len)
  {
    if (it->tag == CSTDX_VIEW_ITERABLE_TAG_CHAR)
    {
      if (it->total.base[len] == it->delim.c)
      {
        break;
      }
    }
  }


  if (it->total.len - len != 0)
  {
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

static cstdx_string_view_t cstdx_string_view_iterable_next_string_view(cstdx_string_view_iterable_t *it)
{
  if (it->total.len < it->delim.sv.len)
  {
    it->total.base = NULL;
    it->total.len = 0;
    return (cstdx_string_view_t){.base=NULL, .len=0};
  }

  uint64_t len = 0;
  const char *ptr = it->total.base;
  for (len = 0; len < it->total.len; len++)
  {
    const char *base = ptr + len;
    cstdx_string_view_t sub = {.base=base, .len=it->delim.sv.len};

    if (cstdx_string_view_equals(sub, it->delim.sv))
    {
      break;
    }
  }

  if (it->total.len - len != 0)
  {
    it->total.base = ptr + len + it->delim.sv.len;
    it->total.len = it->total.len - len - it->delim.sv.len, 0;
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
