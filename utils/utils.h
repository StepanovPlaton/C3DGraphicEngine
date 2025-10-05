#ifndef OBJECTS_H
#define OBJECTS_H

#include <windows.h>

// === Vectors ===
void vector_substruct(int size, float v1[size], float v2[size], float r[size]);
void cross_product_vectors(float v1[3], float v2[3], float r[3]);
float dot_product_vectors(float v1[3], float v2[3]);
void vector_normalize(int size, float coordinates[size]);
void print_vector(int size, float vector[size]);

// === Matrix ===
void print_matrix(int size, float matrix[size][size]);
void matrix_mult_matrix(int size, float matrix1[size][size],
                        float matrix2[size][size], float result[size][size]);
void matrix_mult_vector(int size, float matrix[size][size], float vector[size],
                        float result[size]);

void create_axis_rotate_matrix(int axis, float angle,
                               float rotate_matrix[3][3]);
void create_rotate_matrix(float rotate_speed[3], float rotate_matrix[3][3]);

// === Point in scene ===
struct Point3D {
  float coordinates[3];
};
typedef struct Point3D Point3D;
void transform_point(Point3D *point, int size,
                     float translate_matrix[size][size]);
void create_translate_matrix(Point3D *position, float translate_matrix[4][4],
                             int k);

// === Screen summary ===
struct Screen {
  int width;
  int height;
  HDC *hdc;
  float (*render_matrix)[4][4];
};
typedef struct Screen Screen;

// === Point on screen ===
struct ScreenPoint {
  int coordinates[2];
};
typedef struct ScreenPoint ScreenPoint;
ScreenPoint convert_to_screen_point(Point3D *point, Screen *screen);
void draw_line(Screen *screen, ScreenPoint *sp1, ScreenPoint *sp2);

// === Camera in scene ===
struct Camera {
  Point3D position;
  Point3D target;
  float up[3];
  float fov;
  float max_distance;
  float min_distance;
  float aspect_ratio;
};
typedef struct Camera Camera;
void create_view_matrix(Camera *camera, float view_matrix[4][4]);
void create_projection_matrix(Camera *camera, float projection_matrix[4][4]);

// === Composite object in scene ===
struct Object {
  Point3D *points;
  int (*edges)[2];
  int number_of_points;
  int number_of_edges;
  Point3D *position;
  float (*rotate_speed)[3];
};
typedef struct Object Object;
void transform_object(const Object *object, int size,
                      float translate_matrix[size][size]);
void draw_object(const Object *object, Screen *screen);
Point3D calculate_centroid(const Object *object);

#endif