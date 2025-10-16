#include "math.h"
#include <math.h>
#include <stdint.h>

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

#include "cos_table.h"
// Вспомогательная функция для нормализации угла в [0, 2π)
static inline float normalize_angle(float angle) {
  // Используем fmodf для быстрой нормализации
  angle = fmodf(angle, 2.0f * M_PI);
  if (angle < 0.0f)
    angle += 2.0f * M_PI;
  return angle;
}

float e_cos(float angle) {
  angle = normalize_angle(angle);
  float step = (2.0f * M_PI) / (COS_TABLE_SIZE - 1); // если таблица включает 2π
  int index = (int)(angle / step);
  if (index >= COS_TABLE_SIZE - 1)
    index = COS_TABLE_SIZE - 2;
  if (fabsf(angle - cos_table_angles[index]) < 1e-6f)
    return cos_table_values[index];
  float x0 = cos_table_angles[index];
  float x1 = cos_table_angles[index + 1];
  float y0 = cos_table_values[index];
  float y1 = cos_table_values[index + 1];
  if (x1 == x0)
    return y0;
  float t = (angle - x0) / (x1 - x0);
  return y0 + t * (y1 - y0);
}

float e_sin(float angle) { return e_cos(angle - M_PI_2); }

float e_tan(float angle) {
  float c = e_cos(angle);
  if (fabsf(c) < 1e-6f)
    return (e_sin(angle) > 0) ? HUGE_VALF : -HUGE_VALF;

  return e_sin(angle) / c;
}

#else

float e_rsqrt(float x) { return 1.0f / sqrtf(x); }

float e_cos(float x) { return cosf(x); }
float e_sin(float x) { return sinf(x); }
float e_tan(float x) { return tanf(x); }

#endif
