/*
 Copyright (c) 2010 Myles Metzer
 Permission is hereby granted, free of charge, to any person
 obtaining a copy of this software and associated documentation
 files (the "Software"), to deal in the Software without
 restriction, including without limitation the rights to use,
 copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the
 Software is furnished to do so, subject to the following
 conditions:
 The above copyright notice and this permission notice shall be
 included in all copies or substantial portions of the Software.
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef TVOUT_H
#define TVOUT_H

#include "video_gen.h"
#include <avr/pgmspace.h>
#include <stdlib.h>

#define PAL 1
#define NTSC 0
#define _PAL 1
#define _NTSC 0

#define WHITE 1
#define BLACK 0
#define INVERT 2

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2
#define BYTE 0

class TVout {
public:
  uint8_t *screen;
  uint8_t begin(uint8_t mode);
  uint8_t begin(uint8_t mode, uint8_t x, uint8_t y);
  void end();

  // accessor functions
  unsigned int hres();
  unsigned int vres();
  char charLine();

  // flow control functions
  void delay(unsigned int x);
  void delayFrame(unsigned int x);
  unsigned long millis();

  // basic rendering functions
  void clearScreen();
  void invert();
  void fill(uint8_t color);
  void setPixel(uint8_t x, uint8_t y, char c);
  bool getPixel(uint8_t x, uint8_t y);
  void drawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, char c);
  void drawRow(uint8_t line, uint16_t x0, uint16_t x1, uint8_t c);
  void drawColumn(uint8_t row, uint16_t y0, uint16_t y1, uint8_t c);
  void drawRect(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h, char c,
                char fc = -1);
  void drawCircle(uint8_t x0, uint8_t y0, uint8_t radius, char c, char fc = -1);
  void bitmap(uint8_t x, uint8_t y, const unsigned char *bmp, uint16_t i = 0,
              uint8_t width = 0, uint8_t lines = 0);
  void shift(uint8_t distance, uint8_t direction);

  // tone functions
  void tone(unsigned int frequency, unsigned long durationMS);
  void tone(unsigned int frequency);
  void noTone();

private:
  // hook setup functions
  void setVBIHook(void (*func)());
  void setHBIHook(void (*func)());

  // override setup functions
  void forceVscale(char sfactor);
  void forceOutStart(uint8_t time);
  void forceLineStart(uint8_t line);
  void incTxtLine();

  uint8_t _cursorX, _cursorY;
};

static void inline sp(uint8_t x, uint8_t y, char c);
#endif
