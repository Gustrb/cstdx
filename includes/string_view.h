#ifndef CSTDX_STRING_VIEW_H
#define CSTDX_STRING_VIEW_H

#include <stdint.h>

typedef struct {
  const char *base;
  uint64_t len;
} cstdx_string_view_t;

uint8_t cstdx_string_view_equals(cstdx_string_view_t a, cstdx_string_view_t b);
uint8_t cstdx_string_view_is_prefix(cstdx_string_view_t a, cstdx_string_view_t prefix);

#endif
