#include <includes/slice.h>

#define CSTDX_DEFINE_SUM_OVER_SUMMABLE(summable, result)            \
  /* Note: cstx_slice_sum does not look for oveflow */              \
  result cstdx_##summable ##_slice_sum(cstdx_##summable ##_slice s) \
  {\
    result r = 0;                        \
    for (uint64_t i = 0; i < s.len; ++i) \
      r += s.base[i];                    \
    return r;                            \
  }

CSTDX_DEFINE_SUM_OVER_SUMMABLE(uint8_t, uint64_t)
CSTDX_DEFINE_SUM_OVER_SUMMABLE(uint16_t, uint64_t)
CSTDX_DEFINE_SUM_OVER_SUMMABLE(uint32_t, uint64_t)
CSTDX_DEFINE_SUM_OVER_SUMMABLE(uint64_t, uint64_t)

CSTDX_DEFINE_SUM_OVER_SUMMABLE(int8_t, int64_t)
CSTDX_DEFINE_SUM_OVER_SUMMABLE(int16_t, int64_t)
CSTDX_DEFINE_SUM_OVER_SUMMABLE(int32_t, int64_t)
CSTDX_DEFINE_SUM_OVER_SUMMABLE(int64_t, int64_t)

CSTDX_DEFINE_SUM_OVER_SUMMABLE(float, double)
CSTDX_DEFINE_SUM_OVER_SUMMABLE(double, double)
