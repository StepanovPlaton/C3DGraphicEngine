#ifndef PLATFORM_H
#define PLATFORM_H

#include "../utils/screen.h"
#include "log.h"

#ifdef WIN
#include "win.h"

#define FPS 10
#define WINDOW_WIDTH 800.0f
#define WINDOW_HEIGHT 600.0f
#define BG_COLOR BLACK_BRUSH
#define COLOR RGB(255, 255, 255)
#endif

void init_engine();
void render(Screen screen);
void tic();
void destroy();

#endif