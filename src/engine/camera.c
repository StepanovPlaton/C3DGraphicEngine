#include "camera.h"

#include "../utils/math.h"
#include "vector.h"

void camera_get_view_matrix(const Camera *const camera, float *view_matrix) {
  float forward[3];
  vector_substruct(3, camera->position->coordinates,
                   camera->target->coordinates, forward);
  float normal_forward[3];
  vector_normalize(3, forward, normal_forward);
  float right[3];
  vector_cross_product(camera->up, forward, right);
  float normal_right[3];
  vector_normalize(3, right, normal_right);

  float up[3];
  vector_cross_product(normal_forward, normal_right, up);
  float normal_up[3];
  vector_normalize(3, up, normal_up);

  float *vectors[] = {normal_right, normal_up, normal_forward};
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      view_matrix[i * 4 + j] = 0;
      if (i == 3) {
        if (j == 3)
          view_matrix[i * 4 + j] = 1;
      } else if (j == 3) {
        view_matrix[i * 4 + j] =
            -1 * vector_dot_product(vectors[i], camera->position->coordinates);
      } else {
        view_matrix[i * 4 + j] = vectors[i][j];
      }
    }
  }
}
void camera_get_projection_matrix(const Camera *const camera,
                                  float *projection_matrix) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      projection_matrix[i * 4 + j] = 0;
    }
  }
  float f = 1 / e_tan(camera->fov / 2);
  projection_matrix[0 * 4 + 0] = f / camera->aspect_ratio;
  projection_matrix[1 * 4 + 1] = f;
  projection_matrix[2 * 4 + 2] = (camera->max_distance + camera->min_distance) /
                                 (camera->min_distance - camera->max_distance);
  projection_matrix[3 * 4 + 2] = -1;
  projection_matrix[2 * 4 + 3] =
      (2 * camera->max_distance * camera->min_distance) /
      (camera->min_distance - camera->max_distance);
}