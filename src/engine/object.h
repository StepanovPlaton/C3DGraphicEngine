#ifndef OBJECT_H
#define OBJECT_H

#include "../utils/screen.h"
#include "camera.h"
#include "point.h"

typedef struct Object {
  const char *const name;
  Point *const points;
  const int (*const edges)[2];
  const int *const *const faces;
  const int(*const face_sizes);
  const int number_of_points;
  const int number_of_edges;
  const int number_of_faces;
  Point *const position;
  const float (*const rotate_speed)[3];
} Object;

void object_transform(Object *const object, int size, float *translate_matrix);
Point object_get_centroid(const Object *const object);
void object_draw(const Object *object, const Screen *const screen,
                 const float *render_matrix, const Camera *const camera,
                 const Color *const color);

#endif