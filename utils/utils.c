#include "utils.h"

#include <math.h>
#include <stdio.h>
#include <windows.h>

// === Vectors ===
void vector_substruct(int size, float v1[size], float v2[size], float r[size]) {
  for (int i = 0; i < size; i++)
    r[i] = v1[i] - v2[i];
}
void cross_product_vectors(float v1[3], float v2[3], float r[3]) {
  r[0] = v1[1] * v2[2] - v1[2] * v2[1];
  r[1] = v1[2] * v2[0] - v1[0] * v2[2];
  r[2] = v1[0] * v2[1] - v1[1] * v2[0];
}
float dot_product_vectors(float v1[3], float v2[3]) {
  return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}
void vector_normalize(int size, float coordinates[size]) {
  float divider = 0;
  for (int i = 0; i < size; i++)
    divider += coordinates[i] * coordinates[i];
  divider = sqrt(divider);
  float new_coordinates[size];
  for (int i = 0; i < size; i++)
    coordinates[i] /= divider;
}
void print_vector(int size, float vector[size]) {
  printf("(");
  for (int i = 0; i < size; i++) {
    printf("%f", vector[i]);
    if (i != size - 1)
      printf(",\t");
  }
  printf(")\n");
}

// === Matrices ===
void print_matrix(int size, float matrix[size][size]) {
  for (int i = 0; i < size; i++) {
    printf("(");
    for (int j = 0; j < size; j++) {
      printf("%f", matrix[i][j]);
      if (j != size - 1)
        printf(",\t");
    }
    printf(")\n");
  }
}
void matrix_mult_matrix(int size, float matrix1[size][size],
                        float matrix2[size][size], float result[size][size]) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      result[i][j] = 0;
    }
  }
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      for (int k = 0; k < size; k++) {
        result[i][j] += matrix1[i][k] * matrix2[k][j];
      }
    }
  }
}
void matrix_mult_vector(int size, float matrix[size][size], float vector[size],
                        float result[size]) {
  for (int i = 0; i < size; i++)
    result[i] = 0;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      result[i] += matrix[i][j] * vector[j];
    }
  }
}
void create_axis_rotate_matrix(int axis, float angle,
                               float rotate_matrix[3][3]) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      rotate_matrix[i][j] = 0;
    }
  }

  float cos_angle = cosf(angle);
  float sin_angle = sinf(angle);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (i == axis || j == axis) {
        if (i == j)
          rotate_matrix[i][j] = 1;
        else
          rotate_matrix[i][j] = 0;
      } else {
        if (i == j) {
          rotate_matrix[i][j] = cos_angle;
        } else {
          if ((i < j && axis == 2) || (i > j && axis != 2)) {
            rotate_matrix[i][j] = sin_angle;
          } else {
            rotate_matrix[i][j] = -sin_angle;
          }
        }
      }
    }
  }
}

void create_rotate_matrix(float rotate_speed[3], float rotate_matrix[3][3]) {
  float x_rotate[3][3];
  create_axis_rotate_matrix(0, rotate_speed[0], x_rotate);
  float y_rotate[3][3];
  create_axis_rotate_matrix(1, rotate_speed[1], y_rotate);
  float z_rotate[3][3];
  create_axis_rotate_matrix(2, rotate_speed[2], z_rotate);
  float xy_rotate[3][3];
  matrix_mult_matrix(3, x_rotate, y_rotate, xy_rotate);
  matrix_mult_matrix(3, xy_rotate, z_rotate, rotate_matrix);
}

// === Points in scene ===
void transform_point(Point3D *point, int size,
                     float translate_matrix[size][size]) {
  float new_coordinates[3];
  float old_coordinates[] = {point->coordinates[0], point->coordinates[1],
                             point->coordinates[2], 1.0f};
  matrix_mult_vector(size, translate_matrix, old_coordinates, new_coordinates);
  for (int i = 0; i < 3; i++)
    point->coordinates[i] = new_coordinates[i];
}
void create_translate_matrix(Point3D *position, float translate_matrix[4][4],
                             int k) {
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

// === Points on screen ===
ScreenPoint convert_to_screen_point(Point3D *point, Screen *screen) {
  float tmp[] = {point->coordinates[0], point->coordinates[1],
                 point->coordinates[2], 1.0f};
  float point_projection_view[4];
  matrix_mult_vector(4, *(screen->render_matrix), tmp, point_projection_view);

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

void draw_line(Screen *screen, ScreenPoint *sp1, ScreenPoint *sp2) {
  MoveToEx(*(screen->hdc), sp1->coordinates[0], sp1->coordinates[1], NULL);
  LineTo(*(screen->hdc), sp2->coordinates[0], sp2->coordinates[1]);
}

// === Camera ===
void create_view_matrix(Camera *camera, float view_matrix[4][4]) {
  float forward[3];
  vector_substruct(3, camera->position.coordinates, camera->target.coordinates,
                   forward);
  vector_normalize(3, forward);
  float right[3];
  cross_product_vectors(camera->up, forward, right);
  vector_normalize(3, right);

  float up[3];
  cross_product_vectors(forward, right, up);
  vector_normalize(3, up);

  float *vectors[] = {right, up, forward};
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      view_matrix[i][j] = 0;
      if (i == 3) {
        if (j == 3)
          view_matrix[i][j] = 1;
      } else if (j == 3) {
        view_matrix[i][j] =
            -1 * dot_product_vectors(vectors[i], camera->position.coordinates);
      } else {
        view_matrix[i][j] = vectors[i][j];
      }
    }
  }
}
void create_projection_matrix(Camera *camera, float projection_matrix[4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      projection_matrix[i][j] = 0;
    }
  }
  float f = 1 / tan(camera->fov / 2);
  projection_matrix[0][0] = f / camera->aspect_ratio;
  projection_matrix[1][1] = f;
  projection_matrix[2][2] = (camera->max_distance + camera->min_distance) /
                            (camera->min_distance - camera->max_distance);
  projection_matrix[3][2] = -1;
  projection_matrix[2][3] = (2 * camera->max_distance * camera->min_distance) /
                            (camera->min_distance - camera->max_distance);
}

// === Composite objects ===
void transform_object(const Object *object, int size,
                      float translate_matrix[size][size]) {
  for (int i = 0; i < object->number_of_points; i++) {
    transform_point(&(object->points[i]), size, translate_matrix);
  }
}
void draw_object(const Object *object, Screen *screen) {
  for (int i = 0; i < object->number_of_edges; i++) {
    Point3D point1 = object->points[object->edges[i][0]];
    ScreenPoint screen_point1 = convert_to_screen_point(&point1, screen);
    Point3D point2 = object->points[object->edges[i][1]];
    ScreenPoint screen_point2 = convert_to_screen_point(&point2, screen);
    draw_line(screen, &screen_point1, &screen_point2);
  }
}
Point3D calculate_centroid(const Object *object) {
  Point3D centroid = {{0.0f, 0.0f, 0.0f}};

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