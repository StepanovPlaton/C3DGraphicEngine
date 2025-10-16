#include "object.h"

#include "../utils/screen.h"
#include "vector.h"

void object_transform(Object *const object, int size, float *translate_matrix) {
  for (int i = 0; i < object->number_of_points; i++) {
    point_transform(&(object->points[i]), size, translate_matrix);
  }
}

Point object_get_centroid(const Object *const object) {
  Point centroid = {{0.0f, 0.0f, 0.0f}};

  for (int i = 0; i < object->number_of_points; i++) {
    centroid.coordinates[0] += object->points[i].coordinates[0];
    centroid.coordinates[1] += object->points[i].coordinates[1];
    centroid.coordinates[2] += object->points[i].coordinates[2];
  }

  float inv_n = 1.0f / (float)object->number_of_points;
  centroid.coordinates[0] *= inv_n;
  centroid.coordinates[1] *= inv_n;
  centroid.coordinates[2] *= inv_n;

  return centroid;
}

void object_draw(const Object *object, const Screen *const screen,
                 const float *render_matrix, const Color *const color) {
  for (int i = 0; i < object->number_of_edges; i++) {
    ScreenPoint screen_point1 = point_to_screen_point(
        &object->points[object->edges[i][0]], screen, render_matrix);
    ScreenPoint screen_point2 = point_to_screen_point(
        &object->points[object->edges[i][1]], screen, render_matrix);
    screen->draw_line(&screen_point1, &screen_point2, color);
  }
}