#ifndef MATRIX_H
#define MATRIX_H

void matrix_mult_matrix(int size, const float matrix1[size][size],
                        const float matrix2[size][size],
                        float result[size][size]);
void matrix_mult_vector(int size, const float matrix[size][size],
                        const float vector[size], float result[size]);

void create_axis_rotate_matrix(int axis, float angle,
                               float rotate_matrix[3][3]);
void create_rotate_matrix(const float rotate_speed[3],
                          float rotate_matrix[3][3]);
// void print_matrix(int size, float matrix[size][size]);

#endif