#include "object.h"

#include "../utils/screen.h"
#include "camera.h"
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
                 const float *render_matrix, const Camera *const camera,
                 const Color *const color) {
  // Массив для отслеживания, какие рёбра нужно нарисовать
  char edge_drawn[object->number_of_edges];
  for (int i = 0; i < object->number_of_edges; ++i) {
    edge_drawn[i] = 0;
  }

  // Проходим по всем граням
  for (int face_idx = 0; face_idx < object->number_of_faces; ++face_idx) {
    const int *face = object->faces[face_idx];

    // Берём первые три вершины для вычисления нормали (достаточно для плоской
    // грани)
    Point p0 = object->points[face[0]];
    Point p1 = object->points[face[1]];
    Point p2 = object->points[face[2]];

    // Векторы по ребрам грани
    float v1[3] = {p1.coordinates[0] - p0.coordinates[0],
                   p1.coordinates[1] - p0.coordinates[1],
                   p1.coordinates[2] - p0.coordinates[2]};
    float v2[3] = {p2.coordinates[0] - p0.coordinates[0],
                   p2.coordinates[1] - p0.coordinates[1],
                   p2.coordinates[2] - p0.coordinates[2]};

    // Нормаль к грани (внешняя, если winding order — CCW при взгляде снаружи)
    float normal[3];
    vector_cross_product(v1, v2, normal);

    // Вычисляем центр грани (для направления к камере)
    float w[3] = {0.0f, 0.0f, 0.0f};
    for (int i = 0; i < object->face_sizes[face_idx]; ++i) {
      const Point *pt = &object->points[object->faces[face_idx][i]];
      w[0] += pt->coordinates[0];
      w[1] += pt->coordinates[1];
      w[2] += pt->coordinates[2];
    }
    w[0] /= (float)object->face_sizes[face_idx];
    w[1] /= (float)object->face_sizes[face_idx];
    w[2] /= (float)object->face_sizes[face_idx];

    // Вектор от центра грани к позиции камеры
    float to_camera[3] = {camera->position->coordinates[0] - w[0],
                          camera->position->coordinates[1] - w[1],
                          camera->position->coordinates[2] - w[2]};

    // Проверка видимости: если грань смотрит от камеры — пропускаем
    float dot = vector_dot_product(normal, to_camera);
    if (dot <= 0.0f) {
      continue; // back-face: невидима
    }

    // Отмечаем все рёбра этой грани как "нужно нарисовать"
    for (int j = 0; j < object->face_sizes[face_idx]; ++j) {
      int v_start = face[j];
      int v_end = face[(j + 1) % object->face_sizes[face_idx]];

      for (int edge_idx = 0; edge_idx < object->number_of_edges; ++edge_idx) {
        int e0 = object->edges[edge_idx][0];
        int e1 = object->edges[edge_idx][1];

        if ((e0 == v_start && e1 == v_end) || (e0 == v_end && e1 == v_start)) {
          edge_drawn[edge_idx] = 1;
          break;
        }
      }
    }
  }

  // Рисуем только отмеченные рёбра
  for (int i = 0; i < object->number_of_edges; ++i) {
    if (edge_drawn[i]) {
      ScreenPoint p1 = point_to_screen_point(
          &object->points[object->edges[i][0]], screen, render_matrix);
      ScreenPoint p2 = point_to_screen_point(
          &object->points[object->edges[i][1]], screen, render_matrix);
      screen->draw_line(&p1, &p2, color);
    }
  }
}