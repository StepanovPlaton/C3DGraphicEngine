#ifndef POINT_H
#define POINT_H

#include "../utils/screen.h"

typedef struct Point {
  float coordinates[3];
} Point;

void point_add_point(Point *const point, const Point *const other_point);
void point_substact_point(Point *const point, const Point *const other_point);
void point_mult_number(Point *const point, const int k);
void point_transform(Point *const point, int size,
                     const float *translate_matrix);
void point_create_translate_matrix(const Point *const position,
                                   float *translate_matrix, int k);
ScreenPoint point_to_screen_point(Point *point, const Screen *const screen,
                                  const float *render_matrix);

#endif