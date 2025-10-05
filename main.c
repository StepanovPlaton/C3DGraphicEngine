#include <math.h>
#include <stdio.h>
#include <windows.h>

#include "utils/utils.h"

#define WINDOW_WIDTH 800.0f
#define WINDOW_HEIGHT 600.0f

#define BG_COLOR BLACK_BRUSH
#define COLOR RGB(255, 255, 255)

Point3D cube_points[] = {{0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f},
                         {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f},
                         {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 1.0f},
                         {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f}};
int cube_edges[][2] = {{0, 1}, {1, 2}, {2, 3}, {3, 0}, {4, 5}, {5, 6},
                       {6, 7}, {7, 4}, {0, 4}, {1, 5}, {2, 6}, {3, 7}};
Point3D cube_position = {.coordinates = {3.0f, 6.0f, 5.0f}};
float cube_speed[] = {0.03f, 0.0f, 0.0f};

const Object cube = {.points = cube_points,
                     .edges = cube_edges,
                     .number_of_points = 8,
                     .number_of_edges = 12,
                     .position = &cube_position,
                     .rotate_speed = &cube_speed};

Point3D pyramid_points[] = {{-1.0f, 0.0f, -1.0f},
                            {1.0f, 0.0f, -1.0f},
                            {1.0f, 0.0f, 1.0f},
                            {-1.0f, 0.0f, 1.0f},
                            {0.0f, 1.5f, 0.0f}};
int pyramid_edges[][2] = {{0, 1}, {1, 2}, {2, 3}, {3, 0},
                          {0, 4}, {1, 4}, {2, 4}, {3, 4}};
Point3D pyramid_position = {.coordinates = {6.0f, 3.0f, 5.0f}};
float pyramid_speed[] = {0.0f, 0.0f, 0.03f};

const Object pyramid = {.points = pyramid_points,
                        .edges = pyramid_edges,
                        .number_of_points = 5,
                        .number_of_edges = 8,
                        .position = &pyramid_position,
                        .rotate_speed = &pyramid_speed};

const int number_of_objects = 2;
Object objects[] = {cube, pyramid};

Camera camera = {.position = {0.0f, 0.0f, 0.0f},
                 .target = {1.0f, 1.0f, 1.0f},
                 .up = {-1.0f, -1.0f, 1.0f},
                 .fov = 120.0f,
                 .max_distance = 20.0f,
                 .min_distance = .0f,
                 .aspect_ratio = WINDOW_WIDTH / WINDOW_HEIGHT};

float render_matrix[4][4];

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                            LPARAM lParam) {
  switch (uMsg) {
  case WM_CREATE:
    SetTimer(hwnd, 1, 50, NULL);
    return 0;
  case WM_PAINT: {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    RECT rect;
    GetClientRect(hwnd, &rect);
    FillRect(hdc, &rect, (HBRUSH)GetStockObject(BG_COLOR));
    float width = rect.right - rect.left;
    float height = rect.bottom - rect.top;

    Screen screen = {.width = width,
                     .height = height,
                     .hdc = &hdc,
                     .render_matrix = &render_matrix};

    HPEN hPen = CreatePen(PS_SOLID, 1, COLOR);
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

    for (int i = 0; i < number_of_objects; i++) {
      draw_object(&(objects[i]), &screen);
    }

    SelectObject(hdc, hOldPen);
    DeleteObject(hPen);

    EndPaint(hwnd, &ps);
    return 0;
  }

  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;

  case WM_TIMER:
    for (int i = 0; i < number_of_objects; i++) {
      float reverse_translate_matrix[4][4];
      create_translate_matrix(objects[i].position, reverse_translate_matrix,
                              -1);
      transform_object(&(objects[i]), 4, reverse_translate_matrix);

      Point3D center_of_object = calculate_centroid(&(objects[i]));
      float reverse_center_translate_matrix[4][4];
      create_translate_matrix(&center_of_object,
                              reverse_center_translate_matrix, -1);
      transform_object(&(objects[i]), 4, reverse_center_translate_matrix);

      float rotate_matrix[3][3];
      create_rotate_matrix(*(objects[i].rotate_speed), rotate_matrix);
      transform_object(&(objects[i]), 3, rotate_matrix);

      float center_translate_matrix[4][4];
      create_translate_matrix(&center_of_object, center_translate_matrix, 1);
      transform_object(&(objects[i]), 4, center_translate_matrix);

      float translate_matrix[4][4];
      create_translate_matrix(objects[i].position, translate_matrix, 1);
      transform_object(&(objects[i]), 4, translate_matrix);
    }

    InvalidateRect(hwnd, NULL, TRUE);
    return 0;

  case WM_KEYDOWN:
    return 0;
  }

  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
  const char CLASS_NAME[] = "C3DGraphicEngine";

  WNDCLASS wc = {0};
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = CLASS_NAME;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  RegisterClass(&wc);

  HWND hwnd = CreateWindowEx(0, CLASS_NAME, CLASS_NAME, WS_OVERLAPPEDWINDOW,
                             CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH,
                             WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);

  if (hwnd == NULL) {
    return 0;
  }

  float view_matrix[4][4];
  create_view_matrix(&camera, view_matrix);
  float projection_matrix[4][4];
  create_projection_matrix(&camera, projection_matrix);
  matrix_mult_matrix(4, projection_matrix, view_matrix, render_matrix);

  for (int i = 0; i < number_of_objects; i++) {
    float translate_matrix[4][4];
    create_translate_matrix(objects[i].position, translate_matrix, 1);
    transform_object(&(objects[i]), 4, translate_matrix);
  }

  ShowWindow(hwnd, nCmdShow);
  UpdateWindow(hwnd);

  MSG msg = {0};
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}
