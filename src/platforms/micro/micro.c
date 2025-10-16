#include "./lib/MPU6050/MPU6050.h"
#include "./lib/ST7789/ST7789.h"

#include "../platform.h"
#include "micro.h"

void draw_line(const ScreenPoint *sp1, const ScreenPoint *sp2,
               const Color *const color) {
  st7789_draw_line(sp1->coordinates[0], sp1->coordinates[1],
                   sp2->coordinates[0], sp2->coordinates[1],
                   RGB565(color->red, color->green, color->blue));
};
const Screen screen = {
    .width = DISPLAY_WIDTH, .height = DISPLAY_HEIGHT, .draw_line = &draw_line};

const Color white = {255, 255, 255};
const Color black = {0, 0, 0};

float gx, gy, gz;

int main(void) {
  st7789_init();
  mpu6050_init();

  init_engine();

  st7789_fill_screen(RGB565(0, 0, 0));

  while (1) {
    render(&screen, &black);

    mpu6050_read_gyro(&gx, &gy, &gz);
    float angles_speed[3] = {gx / 255.0f, gy / 255.0f, gz / 255.0f};
    rotate(angles_speed);

    render(&screen, &white);
  }

  return 0;
}