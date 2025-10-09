#ifndef UTILS_H
#define UTILS_H

struct ScreenPoint {
  int coordinates[2];
};
typedef struct ScreenPoint ScreenPoint;

struct Screen {
  int width;
  int height;
  void (*draw_line)(const ScreenPoint *sp1, const ScreenPoint *sp2);
};
typedef struct Screen Screen;

#endif