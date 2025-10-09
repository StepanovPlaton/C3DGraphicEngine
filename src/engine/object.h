#ifndef OBJECT_H
#define OBJECT_H

#include "../utils/screen.h"
#include "point.h"

typedef struct Object {
  const char *const name;
  Point *const points;
  const int (*const edges)[2];
  const int number_of_points;
  const int number_of_edges;
  Point *const position;
  const float (*const rotate_speed)[3];
} Object;

void object_transform(Object *const object, int size,
                      float translate_matrix[size][size]);
Point object_get_centroid(const Object *const object);
void object_draw(const Object *object, Screen *screen,
                 const float render_matrix[4][4]);

#endif