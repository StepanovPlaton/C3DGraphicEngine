#include "vector.h"

#include "../utils/math.h"

void vector_substruct(int size, const float v1[size], const float v2[size],
                      float r[size]) {
  for (int i = 0; i < size; i++)
    r[i] = v1[i] - v2[i];
}
void vector_cross_product(const float v1[3], const float v2[3], float r[3]) {
  r[0] = v1[1] * v2[2] - v1[2] * v2[1];
  r[1] = v1[2] * v2[0] - v1[0] * v2[2];
  r[2] = v1[0] * v2[1] - v1[1] * v2[0];
}
float vector_dot_product(const float v1[3], const float v2[3]) {
  return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}
void vector_normalize(int size, const float v[size], float r[size]) {
  float divider = 0;
  for (int i = 0; i < size; i++)
    divider += v[i] * v[i];
  divider = e_rsqrt(divider);
  for (int i = 0; i < size; i++)
    r[i] = v[i] * divider;
}

// void print_vector(int size, float vector[size]) {
//   printf("(");
//   for (int i = 0; i < size; i++) {
//     printf("%f", vector[i]);
//     if (i != size - 1)
//       printf(",\t");
//   }
//   printf(")\n");
// }