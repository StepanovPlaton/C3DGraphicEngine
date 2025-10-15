#include "./lib/ST7789/ST7789.h"

#include "../platform.h"
#include "micro.h"

void draw_line(const ScreenPoint *sp1, const ScreenPoint *sp2) {
  st7789_draw_line(0, 0, 160, 128, COLOR_WHITE);
  st7789_draw_line(sp1->coordinates[0], sp1->coordinates[1],
                   sp2->coordinates[0], sp2->coordinates[1], COLOR_WHITE);
};
Screen screen = {
    .width = DISPLAY_WIDTH, .height = DISPLAY_HEIGHT, .draw_line = &draw_line};

int main(void) {
  init_engine();

  st7789_init();

  while (1) {
    st7789_fill_screen(COLOR_BLACK);
    render(screen);

    _delay_ms(1000 / FPS);
  }

  return 0;
}