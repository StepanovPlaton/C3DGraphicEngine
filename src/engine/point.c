#include "point.h"

#include "../utils/screen.h"
#include "matrix.h"

void point_transform(Point *const point, int size,
                     const float translate_matrix[size][size]) {
  float new_coordinates[3];
  float old_coordinates[] = {point->coordinates[0], point->coordinates[1],
                             point->coordinates[2], 1.0f};
  matrix_mult_vector(size, translate_matrix, old_coordinates, new_coordinates);
  for (int i = 0; i < 3; i++)
    point->coordinates[i] = new_coordinates[i];
}
void point_create_translate_matrix(const Point *const position,
                                   float translate_matrix[4][4], int k) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      translate_matrix[i][j] = 0;
      if (i == j)
        translate_matrix[i][j] = 1;
      else if (j == 3)
        translate_matrix[i][j] = position->coordinates[i] * k;
    }
  }
}

ScreenPoint point_convert_to_screen_point(Point *point, Screen *screen,
                                          const float render_matrix[4][4]) {
  float tmp[] = {point->coordinates[0], point->coordinates[1],
                 point->coordinates[2], 1.0f};
  float point_projection_view[4];
  matrix_mult_vector(4, render_matrix, tmp, point_projection_view);

  float perspective_coordinates[3] = {
      point_projection_view[0] / point_projection_view[3],
      point_projection_view[1] / point_projection_view[3],
      point_projection_view[2] / point_projection_view[3],
  };
  ScreenPoint spoint = {
      .coordinates = {((perspective_coordinates[0] + 1.0f) / 2.0f) *
                          (float)screen->width,
                      ((perspective_coordinates[1] + 1.0f) / 2.0f) *
                          (float)screen->height}};
  return spoint;
}