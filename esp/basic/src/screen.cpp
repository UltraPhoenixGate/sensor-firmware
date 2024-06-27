#include "screen.h"

#ifdef OLED

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, 6, 5, U8X8_PIN_NONE);

void setupScreen()
{
  u8g2.setContrast(250);
  u8g2.begin();
}

void setScreenMessage(String message)
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(30, 24, message.c_str());
  u8g2.sendBuffer();
}

#endif