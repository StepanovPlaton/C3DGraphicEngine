#ifndef OBJECTS_H
#define OBJECTS_H

#include "engine/engine.h"

Point cube_points[] = {
    {.coordinates = {0.0f, 0.0f, 0.0f}}, {.coordinates = {1.0f, 0.0f, 0.0f}},
    {.coordinates = {1.0f, 1.0f, 0.0f}}, {.coordinates = {0.0f, 1.0f, 0.0f}},
    {.coordinates = {0.0f, 0.0f, 1.0f}}, {.coordinates = {1.0f, 0.0f, 1.0f}},
    {.coordinates = {1.0f, 1.0f, 1.0f}}, {.coordinates = {0.0f, 1.0f, 1.0f}}};

Point cube_position = {.coordinates = {3.0f, 6.0f, 5.0f}};
const int cube_edges[][2] = {{0, 1}, {1, 2}, {2, 3}, {3, 0}, {4, 5}, {5, 6},
                             {6, 7}, {7, 4}, {0, 4}, {1, 5}, {2, 6}, {3, 7}};
const float cube_speed[] = {0.03f, 0.0f, 0.0f};
const Object cube = {.name = "cube",
                     .points = cube_points,
                     .edges = cube_edges,
                     .number_of_points = 8,
                     .number_of_edges = 12,
                     .position = &cube_position,
                     .rotate_speed = &cube_speed};

Point pyramid_points[] = {{.coordinates = {-1.0f, 0.0f, -1.0f}},
                          {.coordinates = {1.0f, 0.0f, -1.0f}},
                          {.coordinates = {1.0f, 0.0f, 1.0f}},
                          {.coordinates = {-1.0f, 0.0f, 1.0f}},
                          {.coordinates = {0.0f, 1.5f, 0.0f}}};
Point pyramid_position = {.coordinates = {6.0f, 3.0f, 5.0f}};
const int pyramid_edges[][2] = {{0, 1}, {1, 2}, {2, 3}, {3, 0},
                                {0, 4}, {1, 4}, {2, 4}, {3, 4}};
const float pyramid_speed[] = {0.0f, 0.0f, 0.03f};
const Object pyramid = {.name = "pyramid",
                        .points = pyramid_points,
                        .edges = pyramid_edges,
                        .number_of_points = 5,
                        .number_of_edges = 8,
                        .position = &pyramid_position,
                        .rotate_speed = &pyramid_speed};

Point prism_points[] = {
    {.coordinates = {0.0f, 0.0f, 0.0f}}, {.coordinates = {1.0f, 0.0f, 0.0f}},
    {.coordinates = {0.5f, 0.0f, 1.0f}}, {.coordinates = {0.0f, 1.0f, 0.0f}},
    {.coordinates = {1.0f, 1.0f, 0.0f}}, {.coordinates = {0.5f, 1.0f, 1.0f}}};
Point prism_position = {.coordinates = {10.0f, 10.0f, 10.0f}};
const int prism_edges[][2] = {{0, 1}, {1, 2}, {2, 0}, {3, 4}, {4, 5},
                              {5, 3}, {0, 3}, {1, 4}, {2, 5}};
const float prism_speed[] = {0.0f, 0.03f, 0.0f};
const Object prism = {.name = "prism",
                      .points = prism_points,
                      .edges = prism_edges,
                      .number_of_points = 6,
                      .number_of_edges = 9,
                      .position = &prism_position,
                      .rotate_speed = &prism_speed};

const int number_of_objects = 3;
Object objects[] = {cube, pyramid, prism};

Point camera_position = {.coordinates = {0.0f, 0.0f, 0.0f}};
Point camera_target = {.coordinates = {1.0f, 1.0f, 1.0f}};
const Camera camera = {.position = &camera_position,
                       .target = &camera_target,
                       .up = {-1.0f, -1.0f, 1.0f},
                       .fov = 120.0f,
                       .max_distance = 20.0f,
                       .min_distance = .0f,
                       .aspect_ratio = WINDOW_WIDTH / WINDOW_HEIGHT};

#endif