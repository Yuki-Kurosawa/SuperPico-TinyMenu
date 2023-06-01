#include <TinyMenu.h>
#include "unifont_en.h"
#include "unifont_cn.h"

TFT_eSPI tft = TFT_eSPI();
uint16_t bg = ST7735_BLACK;
uint16_t MenuBackColor = ST7735_BLUE;
MenuItem Menu[] = {
  { "Menu 1", {} },
  { "Menu 2", {} },
  { "Menu 3", {} },
  { "Menu 4", {} },
  { "Menu 5", {} },
  { "Menu 6", {} },
  { "Menu 7", {} },
  { "Menu 8", {} },
  { "Menu 9", {} },
  { "Menu 10", {} },
  { "Menu 11", {} },
  { "Menu 12", {} }
};

void setup() {
  tft.begin();
  tft.fillScreen(bg);
  tft.setRotation(2);
  tft.loadFont(unifont_en);
  tft.setTextSize(1);
  initMenu(Menu, MenuLen(Menu));
  Serial.begin(115200);
  while (!Serial) {}
}

void loop() {
}