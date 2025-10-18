// #define FMATH

#include "engine/engine.h"

// #define WIN
// #define UNIX
// #define MICRO
#include "platforms/platform.h"

#include "objects.h"

float *render_matrix;

void init_engine() {
  logff(BLUE ITALIC, "Engine init...");

  render_matrix = (float *)malloc(4 * 4 * sizeof(float));

  float view_matrix[4 * 4];
  camera_get_view_matrix(&camera, view_matrix);
  logf("View matrix created\n");

  float projection_matrix[4 * 4];
  camera_get_projection_matrix(&camera, projection_matrix);
  logf("Projection matrix created\n");

  matrix_mult_matrix(4, projection_matrix, view_matrix, render_matrix);
  logf("Render matrix created\n");

  for (int i = 0; i < number_of_objects; i++) {
    Point center_of_object = object_get_centroid(&(objects[i]));
    point_mult_number(&center_of_object, -1);
    point_add_point(&center_of_object, objects[i].position);

    float translate_matrix[4 * 4];
    point_create_translate_matrix(&center_of_object, translate_matrix, 1);
    object_transform(&(objects[i]), 4, translate_matrix);

    logf("Go %s to (%f, %f, %f)\n", objects[i].name,
         objects[i].position->coordinates[0],
         objects[i].position->coordinates[1],
         objects[i].position->coordinates[2]);
  }

  logff(BLUE BOLD UNDERLINE, "Engine init complete!");
}

void render(const Screen *const screen, const Color *const color) {
  for (int i = 0; i < number_of_objects; i++) {
    object_draw(&(objects[i]), screen, render_matrix, &camera, color);
  }
}

void rotate(const float angles_speed[3]) {
  for (int i = 0; i < number_of_objects; i++) {
    float translate_matrix[4 * 4];
    point_create_translate_matrix(objects[i].position, translate_matrix, -1);
    object_transform(&(objects[i]), 4, translate_matrix);

    float rotate_matrix[3 * 3];
    create_rotate_matrix(angles_speed, rotate_matrix);
    object_transform(&(objects[i]), 3, rotate_matrix);

    point_create_translate_matrix(objects[i].position, translate_matrix, 1);
    object_transform(&(objects[i]), 4, translate_matrix);
  }
}
void tic() {
  for (int i = 0; i < number_of_objects; i++) {
    float translate_matrix[4 * 4];
    point_create_translate_matrix(objects[i].position, translate_matrix, -1);
    object_transform(&(objects[i]), 4, translate_matrix);

    float rotate_matrix[3 * 3];
    create_rotate_matrix(*(objects[i].rotate_speed), rotate_matrix);
    object_transform(&(objects[i]), 3, rotate_matrix);

    point_create_translate_matrix(objects[i].position, translate_matrix, 1);
    object_transform(&(objects[i]), 4, translate_matrix);
  }
}

void destroy() { free(render_matrix); }