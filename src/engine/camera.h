#ifndef CAMERA_H
#define CAMERA_H

#include "point.h"

typedef struct Camera {
  Point *const position;
  Point *const target;
  float up[3];
  const float fov;
  const float max_distance;
  const float min_distance;
  const float aspect_ratio;
} Camera;

void camera_get_view_matrix(const Camera *const camera, float *view_matrix);
void camera_get_projection_matrix(const Camera *const camera,
                                  float *projection_matrix);

#endif