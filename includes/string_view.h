#ifndef CSTDX_STRING_VIEW_H
#define CSTDX_STRING_VIEW_H

#include <stdint.h>

typedef struct {
  const char *base;
  uint64_t len;
} cstdx_string_view_h;

uint8_t cstdx_string_view_equals(cstdx_string_view_h a, cstdx_string_view_h b);

#endif
