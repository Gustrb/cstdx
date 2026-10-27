#ifndef CSTDX_STRING_VIEW_H
#define CSTDX_STRING_VIEW_H

#include <stdint.h>

typedef struct {
  const char *base;
  uint64_t len;
} cstdx_string_view_t;

typedef struct {
  cstdx_string_view_t total;
  char delim;
} cstdx_string_view_iterable_t;

uint8_t cstdx_string_view_equals(cstdx_string_view_t a, cstdx_string_view_t b);
uint8_t cstdx_string_view_is_prefix(cstdx_string_view_t a, cstdx_string_view_t prefix);

cstdx_string_view_iterable_t cstdx_string_view_split(cstdx_string_view_t base, char delim);
cstdx_string_view_t cstdx_string_view_iterable_next(cstdx_string_view_iterable_t *it);
cstdx_string_view_t cstdx_string_view_from_cstr(const char *s);

#endif
