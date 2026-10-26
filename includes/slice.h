#ifndef CSTDX_SLICE_H
#define CSTDX_SLICE_H

#include <stdint.h>

#define CSTDX_SLICE_DEF(t) \
  typedef struct {         \
    t *base;               \
    uint64_t len;          \
  } cstdx_##t ##_slice;

CSTDX_SLICE_DEF(uint8_t)
CSTDX_SLICE_DEF(uint16_t)
CSTDX_SLICE_DEF(uint32_t)
CSTDX_SLICE_DEF(uint64_t)

CSTDX_SLICE_DEF(int8_t)
CSTDX_SLICE_DEF(int16_t)
CSTDX_SLICE_DEF(int32_t)
CSTDX_SLICE_DEF(int64_t)

CSTDX_SLICE_DEF(char)
CSTDX_SLICE_DEF(float)
CSTDX_SLICE_DEF(double)

#define CSTDX_SLICE_SUM_DECL(summable, result) \
  result cstdx_##summable ##_slice_sum(cstdx_##summable ##_slice s);

CSTDX_SLICE_SUM_DECL(uint8_t, uint64_t)
CSTDX_SLICE_SUM_DECL(uint16_t, uint64_t)
CSTDX_SLICE_SUM_DECL(uint32_t, uint64_t)
CSTDX_SLICE_SUM_DECL(uint64_t, uint64_t)

CSTDX_SLICE_SUM_DECL(int8_t, int64_t)
CSTDX_SLICE_SUM_DECL(int16_t, int64_t)
CSTDX_SLICE_SUM_DECL(int32_t, int64_t)
CSTDX_SLICE_SUM_DECL(int64_t, int64_t)

CSTDX_SLICE_SUM_DECL(float, double)
CSTDX_SLICE_SUM_DECL(double, double)


#endif
