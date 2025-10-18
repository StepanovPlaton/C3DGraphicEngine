#ifndef PLATFORM_H
#define PLATFORM_H

#include "../utils/screen.h"
#include "log.h"

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

EXTERNC void init_engine();
EXTERNC void render(const Screen *const screen, const Color *const color);
EXTERNC void tic();
EXTERNC void rotate(const float angles_speed[3]);
EXTERNC void destroy();

#ifdef WIN
#include "win/win.h"

#define FPS 25
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define BG_COLOR BLACK_BRUSH
#define COLOR RGB(255, 255, 255)

#endif // WIN

#ifdef MICRO

#define FPS 20
#define DISPLAY_WIDTH 32
#define DISPLAY_HEIGHT 24
#define WINDOW_WIDTH DISPLAY_WIDTH
#define WINDOW_HEIGHT DISPLAY_HEIGHT

#include "micro/micro.h"

#endif // MICRO

#endif
