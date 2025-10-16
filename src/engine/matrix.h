#ifndef MATRIX_H
#define MATRIX_H

void matrix_mult_matrix(int size, const float *matrix1, const float *matrix2,
                        float *result);
void matrix_mult_vector(int size, const float *matrix, const float vector[size],
                        float result[size]);

void create_axis_rotate_matrix(int axis, float angle, float *rotate_matrix);
void create_rotate_matrix(const float rotate_speed[3], float *rotate_matrix);
// void print_matrix(int size, float matrix[size][size]);

#endif