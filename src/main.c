#include <math.h>
#include <stdio.h>

#include "engine/engine.h"

// #define WIN
// #define UNIX
// #define MICRO
#include "platforms/platform.h"

#include "objects.h"

float render_matrix[4][4];

void init_engine() {
  printff(BLUE ITALIC, "Engine init...");

  float view_matrix[4][4];
  camera_get_view_matrix(&camera, view_matrix);
  printf("View matrix created\n");

  float projection_matrix[4][4];
  camera_get_projection_matrix(&camera, projection_matrix);
  printf("Projection matrix created\n");
  matrix_mult_matrix(4, projection_matrix, view_matrix, render_matrix);
  printf("Render matrix created\n");

  for (int i = 0; i < number_of_objects; i++) {
    float translate_matrix[4][4];
    point_create_translate_matrix(objects[i].position, translate_matrix, 1);
    object_transform(&(objects[i]), 4, translate_matrix);
    printf("Go %s to (%f, %f, %f)\n", objects[i].name,
           objects[i].position->coordinates[0],
           objects[i].position->coordinates[1],
           objects[i].position->coordinates[2]);
  }

  printff(BLUE BOLD UNDERLINE, "Engine init complete!");
}

void render(Screen screen) {
  for (int i = 0; i < number_of_objects; i++) {
    object_draw(&(objects[i]), &screen, render_matrix);
  }
}

void tic() {
  for (int i = 0; i < number_of_objects; i++) {
    float reverse_translate_matrix[4][4];
    point_create_translate_matrix(objects[i].position, reverse_translate_matrix,
                                  -1);
    object_transform(&(objects[i]), 4, reverse_translate_matrix);

    Point center_of_object = object_get_centroid(&(objects[i]));
    float reverse_center_translate_matrix[4][4];
    point_create_translate_matrix(&center_of_object,
                                  reverse_center_translate_matrix, -1);
    object_transform(&(objects[i]), 4, reverse_center_translate_matrix);

    float rotate_matrix[3][3];
    create_rotate_matrix(*(objects[i].rotate_speed), rotate_matrix);
    object_transform(&(objects[i]), 3, rotate_matrix);

    float center_translate_matrix[4][4];
    point_create_translate_matrix(&center_of_object, center_translate_matrix,
                                  1);
    object_transform(&(objects[i]), 4, center_translate_matrix);

    float translate_matrix[4][4];
    point_create_translate_matrix(objects[i].position, translate_matrix, 1);
    object_transform(&(objects[i]), 4, translate_matrix);
  }
}

void destroy() {}