#include <TinyMenu.h>
#include "unifont_en.h"
#include "unifont_cn.h"

TFT_eSPI tft = TFT_eSPI();
uint16_t bg = ST7735_BLACK;
uint16_t MenuBackColor = ST7735_BLUE;
uint16_t MenuForeColor = ST7735_WHITE;

MenuItem Menu[] PROGMEM = {
  { "Menu 1", 3 },
  { "Menu 2", 0 },
  { "Menu 3", 0 }  //,
  // { "Menu 4", 0 },
  // { "Menu 5", 0 },
  // { "Menu 6", 0 },
  // { "Menu 7", 0 },
  // { "Menu 8", 0 },
  // { "Menu 9", 0},
  // { "Menu 10", 0 },
  // { "Menu 11", 0 },
  // { "Menu 12", 0 }
};

void nothing()
{

}

MenuItem Menu1[10] = {
  { "Menu 1.1", 0, nothing },
  { "Menu 1.2", 4 },
  { "Menu 1.3", 0 }
};



MenuItem Menu1_2[10] = {
  { "Menu 1.2.1", 0, nothing },
  { "Menu 1.2.2", 0, nothing },
  { "Menu 1.2.3", 0, nothing },
  { "Menu 1.2.4", 0, nothing }
};


void bindMenus() {
  Menu[0].SubMenu = &Menu1;
  Menu1[1].SubMenu = &Menu1_2;
}

void setup() {
  tft.begin();
  tft.fillScreen(bg);
  tft.setRotation(2);
  tft.loadFont(unifont_en);
  tft.setTextSize(1);

  bindMenus();
  initMenu(Menu, MenuLen(Menu));

  Serial.begin(115200);
  while (!Serial) {}
}

void loop() {
}