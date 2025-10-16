#ifndef UTILS_H
#define UTILS_H

typedef struct ScreenPoint {
  int coordinates[2];
} ScreenPoint;

typedef struct Color {
  char red;
  char green;
  char blue;
} Color;

typedef struct Screen {
  int width;
  int height;
  void (*draw_line)(const ScreenPoint *sp1, const ScreenPoint *sp2,
                    const Color *const color);
} Screen;

#endif