#include "TFT_Bargraph.h"

TFT_Bargraph::TFT_Bargraph(void)
{
   _gfx = 0;
}

void TFT_Bargraph::init(
    Adafruit_GFX *gfx, int16_t x, int16_t y, uint16_t w, uint16_t h,
    uint16_t outline, uint16_t fill, uint8_t segments, uint16_t segment_outline, uint16_t segment_color)
{
   // Tweak arguments and pass to the newer initButtonUL() function...
   initUL(gfx, x - (w / 2), y - (h / 2), w, h, outline, fill, segments, segment_outline, segment_color);
}

void TFT_Bargraph::initUL(
    Adafruit_GFX *gfx, int16_t x1, int16_t y1, uint16_t w, uint16_t h,
    uint16_t outline, uint16_t fill, uint8_t segments, uint16_t segment_outline, uint16_t segment_color)
{
   _x1 = x1;
   _y1 = y1;
   _w = w;
   _h = h;
   _outlinecolor = outline;
   _fillcolor = fill;
   _segments = segments;
   _segment_outline = segment_outline;
   _segment_color = segment_color;
   _gfx = gfx;
}

void TFT_Bargraph::draw(uint8_t value)
{
   int value_per_segment = 100 / _segments;

   uint8_t r = min(_w, _h) / 10; // Corner radius
   _gfx->fillRoundRect(_x1, _y1, _w, _h, r, _fillcolor);
   _gfx->drawRoundRect(_x1, _y1, _w, _h, r, _outlinecolor);
   uint8_t bar_h = _h - _h / 5;
   uint8_t bar_w = (_w - 4) / _segments;
   uint16_t bar_position = _x1 + 4;
   uint16_t segments_count = 0;
   while (bar_position + bar_w <= _x1 + _w)
   {
      _gfx->drawRoundRect(bar_position, _y1 + (_h - bar_h) / 2, bar_w - 2, bar_h, 2, _outlinecolor);
      if (value_per_segment * segments_count < value)
         _gfx->fillRoundRect(bar_position, _y1 + (_h - bar_h) / 2, bar_w - 2, bar_h, 2, _segment_color);
      bar_position += bar_w;
      segments_count++;
   }
}
