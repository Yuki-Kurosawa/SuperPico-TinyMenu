#include "TinyMenu.h"

MenuItem *Current = (MenuItem *)NULL;
MenuItem *Parent = (MenuItem *)NULL;

int nextPin = 3;
int prevPin = 2;

volatile int mindex = 0;
volatile int sindex = 0;
volatile int psize = 0;
volatile int msize = 0;
volatile int lsize = 0;
volatile int rsize = 0;

void renderMenu(MenuItem menu[], int size, int mode);
void renderMenuNext(MenuItem menu[], int size, int mode);
void renderMenuPrev(MenuItem menu[], int size, int mode);

void nextButton();
void prevButton();

void initMenu(MenuItem Menu[], int size)
{
    tft.fillScreen(MenuBackColor);
    pinMode(nextPin, INPUT_PULLUP);
    pinMode(prevPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(nextPin), nextButton, FALLING);
    attachInterrupt(prevPin, prevButton, FALLING);
    renderMenu(Menu, size, 0);
}

void renderMenu(MenuItem menu[], int size, int mode)
{
    if (Current == NULL)
    {
        rsize = size;
        if (size < PAGE_SIZE)
        {
            psize = size;
        }
        else
        {
            rsize = mindex + PAGE_SIZE;
            psize = PAGE_SIZE;
        }
        for (mindex = lsize; mindex < psize; mindex++)
        {
            tft.setCursor(0, 16 * mindex + 4);
            if (mindex == 0)
            {
                tft.fillRect(0, 0 * 16 + 4, 128, 16, ST7735_WHITE);
                tft.setTextColor(ST7735_BLUE);
                tft.println(menu[mindex].MenuName);
                sindex = 0;
            }
            else
            {
                tft.fillRect(0, 16 * mindex + 4, 128, 16, ST7735_BLUE);
                tft.setTextColor(ST7735_WHITE);
                tft.println(menu[mindex].MenuName);
            }
        }
        Current = menu;
        msize = size;
    }
    else if (mode > 0)
    {
        mindex = sindex - mode;
        int row = mindex - lsize;
        tft.fillRect(0, row * 16 + 4, 128, 16, ST7735_BLUE);
        tft.setTextColor(ST7735_WHITE);
        tft.setCursor(0, row * 16 + 4);
        tft.println(menu[mindex].MenuName);

        mindex = sindex;
        row = mindex - lsize;
        tft.fillRect(0, row * 16 + 4, 128, 16, ST7735_WHITE);
        tft.setTextColor(ST7735_BLUE);
        tft.setCursor(0, row * 16 + 4);
        tft.println(menu[mindex].MenuName);
    }
    else if (mode < 0)
    {
        mindex = sindex - mode;
        int row = mindex - lsize;
        tft.fillRect(0, row * 16 + 4, 128, 16, ST7735_BLUE);
        tft.setTextColor(ST7735_WHITE);
        tft.setCursor(0, row * 16 + 4);
        tft.println(menu[mindex].MenuName);

        mindex = sindex;
        row = mindex - lsize;
        tft.fillRect(0, row * 16 + 4, 128, 16, ST7735_WHITE);
        tft.setTextColor(ST7735_BLUE);
        tft.setCursor(0, row * 16 + 4);
        tft.println(menu[mindex].MenuName);
    }
}

void renderMenuNext(MenuItem menu[], int size, int mode)
{
    tft.fillScreen(ST7735_BLUE);
    for (mindex = lsize; mindex < rsize; mindex++)
    {
        int row = mindex - lsize;
        tft.setCursor(0, 16 * row + 4);
        if (mindex == sindex)
        {
            tft.fillRect(0, 16 * row + 4, 128, 16, ST7735_WHITE);
            tft.setTextColor(ST7735_BLUE);
            tft.println(menu[mindex].MenuName);
        }
        else
        {
            tft.fillRect(0, 16 * row + 4, 128, 16, ST7735_BLUE);
            tft.setTextColor(ST7735_WHITE);
            tft.println(menu[mindex].MenuName);
        }
    }
}

void renderMenuPrev(MenuItem menu[], int size, int mode)
{
    tft.fillScreen(ST7735_BLUE);
    for (mindex = lsize; mindex < rsize; mindex++)
    {
        int row = mindex - lsize;
        tft.setCursor(0, 16 * row + 4);
        if (mindex == sindex)
        {
            tft.fillRect(0, 16 * row + 4, 128, 16, ST7735_WHITE);
            tft.setTextColor(ST7735_BLUE);
            tft.println(menu[mindex].MenuName);
        }
        else
        {
            tft.fillRect(0, 16 * row + 4, 128, 16, ST7735_BLUE);
            tft.setTextColor(ST7735_WHITE);
            tft.println(menu[mindex].MenuName);
        }
    }
}

void nextButton()
{
    if (sindex + 1 >= msize)
        return;

    if (sindex + 1 >= rsize)
    {
        rsize++;
        lsize++;
        sindex++;
        renderMenuNext(Current, msize, 1);
        return;
    }

    sindex++;
    renderMenu(Current, msize, 1);
}

void prevButton()
{
    if (sindex - 1 < 0)
        return;

    if (sindex - 1 < lsize)
    {
        lsize--;
        rsize--;
        sindex--;
        renderMenuPrev(Current, msize, -1);
        return;
    }

    sindex--;
    renderMenu(Current, msize, -1);
}