#include "TFT_ToggleButton.h"
// #include <ArduinoLog.h>
/**************************************************************************/
/*!
   @brief    Create a simple drawn button UI element
*/
/**************************************************************************/
TFT_ToggleButton::TFT_ToggleButton(void)
{
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
void TFT_ToggleButton::initButton(
    Adafruit_GFX *gfx, int16_t x, int16_t y, uint16_t w, uint16_t h,
    uint16_t outline, uint16_t fill, uint16_t textcolor)
{
   // Tweak arguments and pass to the newer initButtonUL() function...
   initButtonUL(gfx, x - (w / 2), y - (h / 2), w, h, outline, fill,
                textcolor);
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
void TFT_ToggleButton::initButtonUL(
    Adafruit_GFX *gfx, int16_t x1, int16_t y1, uint16_t w, uint16_t h,
    uint16_t outline, uint16_t fill, uint16_t textcolor)
{
   _x1 = x1;
   _y1 = y1;
   _w = w;
   _h = h;
   _outlinecolor = outline;
   _fillcolor = fill;
   _textcolor = textcolor;
   _gfx = gfx;
}

/**************************************************************************/
/*!
   @brief    Draw the button on the screen
   @param    inverted Whether to draw with fill/text swapped to indicate 'pressed'
*/
/**************************************************************************/
void TFT_ToggleButton::drawButton()
{
   uint8_t border_width = _h * 0.05 <= 1 ? 1 : round(_h * 0.05);
   uint8_t circleRadius = _h / 2.0;
   uint8_t circleRadius1 = round(_h / 2.0) - (border_width * 2);
   uint16_t y_center = _y1 + round(_h / 2);

   // Log.verbose("_h: %d, _w: %d, border_width: %d, circleRadius: %d, circleRadius1: %d, y_center: %d\n", _h, _w, border_width, circleRadius, circleRadius1, y_center);

   // outer background_outlinecolor
   _gfx->fillCircle(_x1 + circleRadius, y_center, circleRadius, _outlinecolor);
   _gfx->fillCircle(_x1 + _w - circleRadius, y_center, circleRadius, _outlinecolor);
   _gfx->fillRect(_x1 + circleRadius, y_center - circleRadius, _w - circleRadius * 2, _h, _outlinecolor);

   // inner background

   if (is_enabled)
   {
      _gfx->fillRect(_x1 + circleRadius1, y_center - circleRadius1, _w - circleRadius1 * 2, circleRadius1 * 2 + 1, _textcolor);
      _gfx->fillCircle(_x1 + _w - circleRadius1 - border_width, y_center, circleRadius1, _textcolor);
      _gfx->fillCircle(_x1 + circleRadius1 + border_width, y_center, circleRadius1, _fillcolor);
   }
   else
   {
      _gfx->fillCircle(_x1 + circleRadius1 + border_width, y_center, circleRadius1, _textcolor);
      _gfx->fillRect(_x1 + circleRadius1, y_center - circleRadius1, _w - circleRadius1 * 2, circleRadius1 * 2 + 1, _textcolor);
      _gfx->fillCircle(_x1 + _w - circleRadius1 - border_width, y_center, circleRadius1, _fillcolor);
   }
}

/**************************************************************************/
/*!
   @brief    Helper to let us know if a coordinate is within the bounds of the button
    @param    x       The X coordinate to check
    @param    y       The Y coordinate to check
   @returns   True if within button graphics outline
*/
/**************************************************************************/
boolean TFT_ToggleButton::contains(int16_t x, int16_t y)
{
   return ((x >= _x1) && (x < (int16_t)(_x1 + _w)) &&
           (y >= _y1) && (y < (int16_t)(_y1 + _h)));
}

/**************************************************************************/
/*!
   @brief    Sets the state of the button, should be done by some touch function
   @param    p  True for pressed, false for not.
*/
/**************************************************************************/
void TFT_ToggleButton::press(boolean p)
{
   laststate = currstate;
   currstate = p;
}

/**************************************************************************/
/*!
   @brief    Query whether the button is currently pressed
   @returns  True if pressed
*/
/**************************************************************************/
boolean TFT_ToggleButton::isPressed() { return currstate; }

/**************************************************************************/
/*!
   @brief    Query whether the button was pressed since we last checked state
   @returns  True if was not-pressed before, now is.
*/
/**************************************************************************/
boolean TFT_ToggleButton::justPressed() { return (currstate && !laststate); }

/**************************************************************************/
/*!
   @brief    Query whether the button was released since we last checked state
   @returns  True if was pressed before, now is not.
*/
/**************************************************************************/
boolean TFT_ToggleButton::justReleased()
{
   if (!currstate && laststate)
      is_enabled = !is_enabled;
   return (!currstate && laststate);
}

boolean TFT_ToggleButton::isEnabled()
{
   return is_enabled;
}

void TFT_ToggleButton::setEnabled(boolean enabled)
{
   is_enabled = enabled;
}
