#ifndef PLATFORM_H
#define PLATFORM_H

#include "../utils/screen.h"
#include "log.h"

#ifdef WIN
#include "win/win.h"

#define FPS 25
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define BG_COLOR BLACK_BRUSH
#define COLOR RGB(255, 255, 255)

#endif // WIN

#ifdef MICRO

#define FPS 25
#include "micro/micro.h"

#define DISPLAY_WIDTH 160
#define DISPLAY_HEIGHT 128
#define WINDOW_WIDTH DISPLAY_WIDTH
#define WINDOW_HEIGHT DISPLAY_HEIGHT

#endif // MICRO

void init_engine();
void render(const Screen *const screen, const Color *const color);
void tic();
void rotate(const float angles_speed[3]);
void destroy();

#endif
