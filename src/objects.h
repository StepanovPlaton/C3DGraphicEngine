#ifndef OBJECTS_H
#define OBJECTS_H

#include "engine/engine.h"

// == Cube ==

Point cube_points[] = {
    {.coordinates = {0.0f, 0.0f, 0.0f}}, {.coordinates = {1.0f, 0.0f, 0.0f}},
    {.coordinates = {1.0f, 1.0f, 0.0f}}, {.coordinates = {0.0f, 1.0f, 0.0f}},
    {.coordinates = {0.0f, 0.0f, 1.0f}}, {.coordinates = {1.0f, 0.0f, 1.0f}},
    {.coordinates = {1.0f, 1.0f, 1.0f}}, {.coordinates = {0.0f, 1.0f, 1.0f}}};
const int cube_edges[][2] = {{0, 1}, {1, 2}, {2, 3}, {3, 0}, {4, 5}, {5, 6},
                             {6, 7}, {7, 4}, {0, 4}, {1, 5}, {2, 6}, {3, 7}};
int cube_face0[] = {3, 2, 1, 0};
int cube_face1[] = {4, 5, 6, 7};
int cube_face2[] = {0, 4, 7, 3};
int cube_face3[] = {2, 6, 5, 1};
int cube_face4[] = {1, 5, 4, 0};
int cube_face5[] = {3, 7, 6, 2};
const int *cube_faces[] = {cube_face0, cube_face1, cube_face2,
                           cube_face3, cube_face4, cube_face5};
const int cube_face_sizes[] = {4, 4, 4, 4, 4, 4};

const float cube_speed[] = {0.03f, -0.03f, 0.03f};
Point cube_position = {.coordinates = {2.0f, 2.0f, 2.0f}};
// Point cube_position = {.coordinates = {3.0f, 6.0f, 5.0f}};
const Object cube = {.name = "cube",
                     .points = cube_points,
                     .edges = cube_edges,
                     .faces = cube_faces,
                     .face_sizes = cube_face_sizes,
                     .number_of_points = 8,
                     .number_of_edges = 12,
                     .number_of_faces = 6,
                     .position = &cube_position,
                     .rotate_speed = &cube_speed};

// // == Pyramid ==

// Point pyramid_points[] = {{.coordinates = {-1.0f, 0.0f, -1.0f}},
//                           {.coordinates = {1.0f, 0.0f, -1.0f}},
//                           {.coordinates = {1.0f, 0.0f, 1.0f}},
//                           {.coordinates = {-1.0f, 0.0f, 1.0f}},
//                           {.coordinates = {0.0f, 1.5f, 0.0f}}};
// const int pyramid_edges[][2] = {{0, 1}, {1, 2}, {2, 3}, {3, 0},
//                                 {0, 4}, {1, 4}, {2, 4}, {3, 4}};
// const int pyramid_face0[] = {0, 1, 2, 3};
// const int pyramid_face1[] = {1, 0, 4};
// const int pyramid_face2[] = {2, 1, 4};
// const int pyramid_face3[] = {3, 2, 4};
// const int pyramid_face4[] = {0, 3, 4};
// const int *pyramid_faces[] = {pyramid_face0, pyramid_face1, pyramid_face2,
//                               pyramid_face3, pyramid_face4};
// const int pyramid_face_sizes[] = {4, 3, 3, 3, 3};

// const float pyramid_speed[] = {0.03f, 0.03f, -0.03f};
// Point pyramid_position = {.coordinates = {6.0f, 3.0f, 5.0f}};
// const Object pyramid = {.name = "pyramid",
//                         .points = pyramid_points,
//                         .edges = pyramid_edges,
//                         .faces = pyramid_faces,
//                         .face_sizes = pyramid_face_sizes,
//                         .number_of_points = 5,
//                         .number_of_edges = 8,
//                         .number_of_faces = 5,
//                         .position = &pyramid_position,
//                         .rotate_speed = &pyramid_speed};

// // == Prism ==

// Point prism_points[] = {
//     {.coordinates = {0.0f, 0.0f, 0.0f}}, {.coordinates = {1.0f, 0.0f, 0.0f}},
//     {.coordinates = {0.5f, 0.0f, 1.0f}}, {.coordinates = {0.0f, 1.0f, 0.0f}},
//     {.coordinates = {1.0f, 1.0f, 0.0f}}, {.coordinates =
//     {0.5f, 1.0f, 1.0f}}};
// const int prism_edges[][2] = {{0, 1}, {1, 2}, {2, 0}, {3, 4}, {4, 5},
//                               {5, 3}, {0, 3}, {1, 4}, {2, 5}};
// const int prism_face0[] = {0, 1, 2};
// const int prism_face1[] = {3, 5, 4};
// const int prism_face2[] = {0, 3, 4, 1};
// const int prism_face3[] = {1, 4, 5, 2};
// const int prism_face4[] = {2, 5, 3, 0};
// const int *prism_faces[] = {prism_face0, prism_face1, prism_face2,
// prism_face3,
//                             prism_face4};
// const int prism_face_sizes[] = {3, 3, 4, 4, 4};

// const float prism_speed[] = {-0.03f, 0.03f, 0.03f};
// Point prism_position = {.coordinates = {10.0f, 10.0f, 10.0f}};
// const Object prism = {.name = "prism",
//                       .points = prism_points,
//                       .edges = prism_edges,
//                       .faces = prism_faces,
//                       .face_sizes = prism_face_sizes,
//                       .number_of_points = 6,
//                       .number_of_edges = 9,
//                       .number_of_faces = 5,
//                       .position = &prism_position,
//                       .rotate_speed = &prism_speed};

const int number_of_objects = 1;
// Object objects[] = {cube, pyramid, prism};
Object objects[] = {cube};

Point camera_position = {.coordinates = {0.0f, 0.0f, 0.0f}};
Point camera_target = {.coordinates = {1.0f, 1.0f, 1.0f}};
const Camera camera = {.position = &camera_position,
                       .target = &camera_target,
                       .up = {-1.0f, -1.0f, 1.0f},
                       .fov = 120.0f,
                       .max_distance = 20.0f,
                       .min_distance = .0f,
                       .aspect_ratio =
                           (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT};

#endif