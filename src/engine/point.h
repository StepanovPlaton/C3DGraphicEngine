#ifndef POINT_H
#define POINT_H

#include "../utils/screen.h"

typedef struct Point {
  float coordinates[3];
} Point;

void point_transform(Point *const point, int size,
                     const float translate_matrix[size][size]);
void point_create_translate_matrix(const Point *const position,
                                   float translate_matrix[4][4], int k);
ScreenPoint point_convert_to_screen_point(Point *point, Screen *screen,
                                          const float render_matrix[4][4]);

#endif