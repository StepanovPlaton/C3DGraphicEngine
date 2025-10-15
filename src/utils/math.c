#include "math.h"
#include <math.h>
#include <stdint.h>

#define FMATH
#ifdef FMATH

float e_rsqrt(float x) {
  const float x2 = x * 0.5F;
  const float threehalfs = 1.5F;
  union {
    float f;
    uint32_t i;
  } conv = {x};
  conv.i = 0x5f3759df - (conv.i >> 1);
  conv.f *= threehalfs - x2 * conv.f * conv.f;
  return conv.f;
}

float e_cos(float x) { return cosf(x); }
float e_sin(float x) { return sinf(x); }
float e_tan(float x) { return tanf(x); }

#else

float e_rsqrt(float x) { return 1.0f / sqrtf(x); }

float e_cos(float x) { return cosf(x); }
float e_sin(float x) { return sinf(x); }
float e_tan(float x) { return tanf(x); }

#endif
