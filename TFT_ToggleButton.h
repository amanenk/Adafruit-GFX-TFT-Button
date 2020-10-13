
#if ARDUINO >= 100
#include "Arduino.h"
#include "Print.h"
#else
#include "WProgram.h"
#endif
#include "gfxfont.h"
#include <Adafruit_GFX.h>

/// A simple drawn button UI element
class TFT_ToggleButton
{

public:
  TFT_ToggleButton(void);
  // "Classic" initButton() uses center & size
  void initButton(Adafruit_GFX *gfx, int16_t x, int16_t y,
                  uint16_t w, uint16_t h, uint16_t outline, uint16_t fill,
                  uint16_t textcolor);
  // New/alt initButton() uses upper-left corner & size
  void initButtonUL(Adafruit_GFX *gfx, int16_t x1, int16_t y1,
                    uint16_t w, uint16_t h, uint16_t outline, uint16_t fill,
                    uint16_t textcolor);
  void drawButton();
  boolean contains(int16_t x, int16_t y);

  void press(boolean p);
  boolean isPressed();
  boolean justPressed();
  boolean justReleased();
  boolean isEnabled();
  void setEnabled(boolean enabled);

private:
  Adafruit_GFX *_gfx;
  int16_t _x1, _y1; // Coordinates of top-left corner
  uint16_t _w, _h;
  uint16_t _outlinecolor, _fillcolor, _textcolor;

  boolean currstate, laststate, is_enabled;
};
