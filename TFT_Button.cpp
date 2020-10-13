#include "TFT_Button.h"
/**************************************************************************/
/*!
   @brief    Create a simple drawn button UI element
*/
/**************************************************************************/
TFT_Button::TFT_Button(void) {
  _gfx = 0;
}

/**************************************************************************/
/*!
   @brief    Initialize button with our desired color/size/settings
   @param    gfx     Pointer to our display so we can draw to it!
   @param    x       The X coordinate of the center of the button
   @param    y       The Y coordinate of the center of the button
   @param    w       Width of the buttton
   @param    h       Height of the buttton
   @param    outline  Color of the outline (16-bit 5-6-5 standard)
   @param    fill  Color of the button fill (16-bit 5-6-5 standard)
   @param    textcolor  Color of the button label (16-bit 5-6-5 standard)
   @param    label  Ascii string of the text inside the button
   @param    textsize The font magnification of the label text
*/
/**************************************************************************/
// Classic initButton() function: pass center & size
void TFT_Button::initButton(
 Adafruit_GFX *gfx, int16_t x, int16_t y, uint16_t w, uint16_t h,
 uint16_t outline, uint16_t fill, uint16_t textcolor,
 char *label, uint8_t textsize)
{
  // Tweak arguments and pass to the newer initButtonUL() function...
  initButtonUL(gfx, x - (w / 2), y - (h / 2), w, h, outline, fill,
    textcolor, label, textsize);
}

/**************************************************************************/
/*!
   @brief    Initialize button with our desired color/size/settings, with upper-left coordinates
   @param    gfx     Pointer to our display so we can draw to it!
   @param    x1       The X coordinate of the Upper-Left corner of the button
   @param    y1       The Y coordinate of the Upper-Left corner of the button
   @param    w       Width of the buttton
   @param    h       Height of the buttton
   @param    outline  Color of the outline (16-bit 5-6-5 standard)
   @param    fill  Color of the button fill (16-bit 5-6-5 standard)
   @param    textcolor  Color of the button label (16-bit 5-6-5 standard)
   @param    label  Ascii string of the text inside the button
   @param    textsize The font magnification of the label text
*/
/**************************************************************************/
void TFT_Button::initButtonUL(
 Adafruit_GFX *gfx, int16_t x1, int16_t y1, uint16_t w, uint16_t h,
 uint16_t outline, uint16_t fill, uint16_t textcolor,
 char *label, uint8_t textsize)
{
  _x1           = x1;
  _y1           = y1;
  _w            = w;
  _h            = h;
  _outlinecolor = outline;
  _fillcolor    = fill;
  _textcolor    = textcolor;
  _textsize     = textsize;
  _gfx          = gfx;
  strncpy(_label, label, TFT_BUTTON_LABEL_LENGTH-1);
}

/**************************************************************************/
/*!
   @brief    Draw the button on the screen
   @param    inverted Whether to draw with fill/text swapped to indicate 'pressed'
*/
/**************************************************************************/
void TFT_Button::drawButton(boolean inverted) {
  uint16_t fill, outline, text;

  if(!inverted) {
    fill    = _fillcolor;
    outline = _outlinecolor;
    text    = _textcolor;
  } else {
    fill    = _textcolor;
    outline = _outlinecolor;
    text    = _fillcolor;
  }

  uint8_t r = min(_w, _h) / 10; // Corner radius
  _gfx->fillRoundRect(_x1, _y1, _w, _h, r, fill);
  _gfx->drawRoundRect(_x1, _y1, _w, _h, r, outline);

  _gfx->setCursor(_x1 + (_w/2) - (strlen(_label) * 3 * _textsize),
    _y1 + (_h/2) - (4 * _textsize));
  _gfx->setTextColor(text);
  _gfx->setTextSize(_textsize);
  _gfx->print(_label);
}

/**************************************************************************/
/*!
   @brief    Helper to let us know if a coordinate is within the bounds of the button
    @param    x       The X coordinate to check
    @param    y       The Y coordinate to check
   @returns   True if within button graphics outline
*/
/**************************************************************************/
boolean TFT_Button::contains(int16_t x, int16_t y) {
  return ((x >= _x1) && (x < (int16_t) (_x1 + _w)) &&
          (y >= _y1) && (y < (int16_t) (_y1 + _h)));
}

/**************************************************************************/
/*!
   @brief    Sets the state of the button, should be done by some touch function
   @param    p  True for pressed, false for not.
*/
/**************************************************************************/
void TFT_Button::press(boolean p) {
  laststate = currstate;
  currstate = p;
}

/**************************************************************************/
/*!
   @brief    Query whether the button is currently pressed
   @returns  True if pressed
*/
/**************************************************************************/
boolean TFT_Button::isPressed() { return currstate; }

/**************************************************************************/
/*!
   @brief    Query whether the button was pressed since we last checked state
   @returns  True if was not-pressed before, now is.
*/
/**************************************************************************/
boolean TFT_Button::justPressed() { return (currstate && !laststate); }

/**************************************************************************/
/*!
   @brief    Query whether the button was released since we last checked state
   @returns  True if was pressed before, now is not.
*/
/**************************************************************************/
boolean TFT_Button::justReleased() { return (!currstate && laststate); }
