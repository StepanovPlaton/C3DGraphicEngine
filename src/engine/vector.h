#ifndef VECTOR_H
#define VECTOR_H

void vector_substruct(int size, const float v1[size], const float v2[size],
                      float r[size]);
void cross_product_vectors(const float v1[3], const float v2[3], float r[3]);
float dot_product_vectors(const float v1[3], const float v2[3]);
void vector_normalize(int size, const float v[size], float r[size]);
// void print_vector(int size, float vector[size]);

#endif
