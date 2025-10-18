
#include "micro.h"
#include "../platform.h"

#include "./lib/MPU6050/MPU6050.h"
#include "./lib/TVout/TVout.h"
#include <util/delay.h>

TVout TV;

void draw_line(const ScreenPoint *const sp1, const ScreenPoint *const sp2,
               const Color *const color) {
  TV.drawLine(sp1->coordinates[0], sp1->coordinates[1], sp2->coordinates[0],
              sp2->coordinates[1], 1);
}
Screen screen = {.width = 128, .height = 64, .draw_line = &draw_line};
Color white = {.red = (char)255, .green = (char)255, .blue = (char)255};

float gx, gy, gz;

int main(void) {
  TV.begin(NTSC, 128, 64);
  mpu6050_init();

  init_engine();

  while (1) {
    TV.clearScreen();

    mpu6050_read_gyro(&gx, &gy, &gz);
    float angles[3] = {gx / 250.0f, gy / 250.0f, gz / 250.0f};
    rotate(angles);

    render(&screen, &white);

    // _delay_ms(1000 / FPS);
  }
  return 0;
}