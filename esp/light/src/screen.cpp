#include "screen.h"

#ifdef OLED

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE, /* clock=*/GPIO_NUM_4, /* data=*/GPIO_NUM_5); // ESP32 Thing, HW I2C with pin remapping

void setupScreen()
{
  u8g2.begin();
  u8g2.setFont(u8g2_font_10x20_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

void setScreenMessage(String message)
{
  u8g2.clearBuffer();
  u8g2.drawStr(0, 0, message.c_str());
  u8g2.sendBuffer();
}

#endif