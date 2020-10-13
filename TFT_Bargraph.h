
#if ARDUINO >= 100
#include "Arduino.h"
#include "Print.h"
#else
#include "WProgram.h"
#endif
#include "gfxfont.h"
#include <Adafruit_GFX.h>


/// A simple drawn button UI element
class TFT_Bargraph
{

public:
  TFT_Bargraph(void);
  // "Classic" initButton() uses center & size
  void init(
      Adafruit_GFX *gfx, int16_t x, int16_t y, uint16_t w, uint16_t h,
      uint16_t outline, uint16_t fill, uint8_t segments, uint16_t segment_outline, uint16_t segment_color);
  // New/alt initButton() uses upper-left corner & size
  void initUL(
      Adafruit_GFX *gfx, int16_t x, int16_t y, uint16_t w, uint16_t h,
      uint16_t outline, uint16_t fill, uint8_t segments, uint16_t segment_outline, uint16_t segment_color);
  void draw(uint8_t value);

private:
  Adafruit_GFX *_gfx;
  int16_t _x1, _y1; // Coordinates of top-left corner
  uint16_t _w, _h;
  uint8_t _textsize, _segments;
  uint16_t _outlinecolor, _fillcolor, _textcolor, _segment_outline, _segment_color;
};
