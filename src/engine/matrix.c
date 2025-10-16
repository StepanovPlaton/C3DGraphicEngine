#include "matrix.h"
#include "../utils/math.h"

void matrix_mult_matrix(int size, const float *matrix1, const float *matrix2,
                        float *result) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      result[i * size + j] = 0;
    }
  }
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      for (int k = 0; k < size; k++) {
        result[i * size + j] += matrix1[i * size + k] * matrix2[k * size + j];
      }
    }
  }
}
void matrix_mult_vector(int size, const float *matrix, const float vector[size],
                        float result[size]) {
  for (int i = 0; i < size; i++)
    result[i] = 0;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      result[i] += matrix[i * size + j] * vector[j];
    }
  }
}
void create_axis_rotate_matrix(int axis, float angle, float *rotate_matrix) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      rotate_matrix[i * 3 + j] = 0;
    }
  }

  float cos_angle = e_cos(angle);
  float sin_angle = e_sin(angle);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (i == axis || j == axis) {
        if (i == j)
          rotate_matrix[i * 3 + j] = 1;
        else
          rotate_matrix[i * 3 + j] = 0;
      } else {
        if (i == j) {
          rotate_matrix[i * 3 + j] = cos_angle;
        } else {
          if ((i < j && axis == 2) || (i > j && axis != 2)) {
            rotate_matrix[i * 3 + j] = sin_angle;
          } else {
            rotate_matrix[i * 3 + j] = -sin_angle;
          }
        }
      }
    }
  }
}

void create_rotate_matrix(const float rotate_speed[3], float *rotate_matrix) {
  float x_rotate[3 * 3];
  create_axis_rotate_matrix(0, rotate_speed[0], x_rotate);
  float y_rotate[3 * 3];
  create_axis_rotate_matrix(1, rotate_speed[1], y_rotate);
  float z_rotate[3 * 3];
  create_axis_rotate_matrix(2, rotate_speed[2], z_rotate);
  float xy_rotate[3 * 3];
  matrix_mult_matrix(3, x_rotate, y_rotate, xy_rotate);
  matrix_mult_matrix(3, xy_rotate, z_rotate, rotate_matrix);
}

// void print_matrix(int size, float matrix[size][size]) {
//   for (int i = 0; i < size; i++) {
//     printf("(");
//     for (int j = 0; j < size; j++) {
//       printf("%f", matrix[i][j]);
//       if (j != size - 1)
//         printf(",\t");
//     }
//     printf(")\n");
//   }
// }