#include <TFT_eSPI.h>

#ifndef TINYMENU_H
#define TINYMENU_H

#define TINYMENU_ITEM_MAX 10
const int MenuItemMax = TINYMENU_ITEM_MAX;

struct MenuItem
{
  const char *MenuName;
  int SubMenuCount = 0;
  MenuItem (*SubMenu)[MenuItemMax];
};

struct CacheMenuItem
{
  int SubMenuSize=0;
  MenuItem *SubMenu;
};

extern TFT_eSPI tft;
extern uint16_t MenuBackColor;
extern uint16_t MenuForeColor;

#define PAGE_SIZE 8
#define MenuLen(m) (sizeof(m) / sizeof(MenuItem))

void initMenu(MenuItem Menu[], int size);

#endif