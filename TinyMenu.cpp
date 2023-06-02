#include "TinyMenu.h"

MenuItem *Current = (MenuItem *)NULL;

int nextPin = 3;
int prevPin = 2;
int backPin = 15;
int okPin = 17;

volatile int selectedIndex = 0;
volatile int menuSize = 0;
volatile int firstRowIndex = 0;
volatile int lastRowIndex = 0;

void renderMenu(MenuItem menu[], int size, int mode);
void renderMenuMove(MenuItem menu[], int size, int mode);

void nextButton();
void prevButton();
void okButton();
void backButton();

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
    int menuIndex = 0;
    int realPageSize=0;

    if (Current == NULL)
    {
        lastRowIndex = size;
        if (size < PAGE_SIZE)
        {
            realPageSize = size;
        }
        else
        {
            lastRowIndex = menuIndex + PAGE_SIZE;
            realPageSize = PAGE_SIZE;
        }
        for (menuIndex = firstRowIndex; menuIndex < realPageSize; menuIndex++)
        {
            tft.setCursor(0, 16 * menuIndex + 4);
            if (menuIndex == 0)
            {
                tft.fillRect(0, 0 * 16 + 4, 128, 16, MenuForeColor);
                tft.setTextColor(MenuBackColor);
                tft.println(menu[menuIndex].MenuName);
                selectedIndex = 0;
            }
            else
            {
                tft.fillRect(0, 16 * menuIndex + 4, 128, 16, MenuBackColor);
                tft.setTextColor(MenuForeColor);
                tft.println(menu[menuIndex].MenuName);
            }
        }
        Current = menu;
        menuSize = size;
    }
    else if (mode > 0)
    {
        menuIndex = selectedIndex - mode;
        int row = menuIndex - firstRowIndex;
        tft.fillRect(0, row * 16 + 4, 128, 16, MenuBackColor);
        tft.setTextColor(MenuForeColor);
        tft.setCursor(0, row * 16 + 4);
        tft.println(menu[menuIndex].MenuName);

        menuIndex = selectedIndex;
        row = menuIndex - firstRowIndex;
        tft.fillRect(0, row * 16 + 4, 128, 16, MenuForeColor);
        tft.setTextColor(MenuBackColor);
        tft.setCursor(0, row * 16 + 4);
        tft.println(menu[menuIndex].MenuName);
    }
    else if (mode < 0)
    {
        menuIndex = selectedIndex - mode;
        int row = menuIndex - firstRowIndex;
        tft.fillRect(0, row * 16 + 4, 128, 16, MenuBackColor);
        tft.setTextColor(MenuForeColor);
        tft.setCursor(0, row * 16 + 4);
        tft.println(menu[menuIndex].MenuName);

        menuIndex = selectedIndex;
        row = menuIndex - firstRowIndex;
        tft.fillRect(0, row * 16 + 4, 128, 16, MenuForeColor);
        tft.setTextColor(MenuBackColor);
        tft.setCursor(0, row * 16 + 4);
        tft.println(menu[menuIndex].MenuName);
    }
}

void renderMenuMove(MenuItem menu[], int size, int mode)
{
    int menuIndex = 0;
    tft.fillScreen(MenuBackColor);
    for (menuIndex = firstRowIndex; menuIndex < lastRowIndex; menuIndex++)
    {
        int row = menuIndex - firstRowIndex;
        tft.setCursor(0, 16 * row + 4);
        if (menuIndex == selectedIndex)
        {
            tft.fillRect(0, 16 * row + 4, 128, 16, MenuForeColor);
            tft.setTextColor(MenuBackColor);
            tft.println(menu[menuIndex].MenuName);
        }
        else
        {
            tft.fillRect(0, 16 * row + 4, 128, 16, MenuBackColor);
            tft.setTextColor(MenuForeColor);
            tft.println(menu[menuIndex].MenuName);
        }
    }
}

void nextButton()
{
    if (selectedIndex + 1 >= menuSize)
        return;

    if (selectedIndex + 1 >= lastRowIndex)
    {
        lastRowIndex++;
        firstRowIndex++;
        selectedIndex++;
        renderMenuMove(Current, menuSize, 1);
        return;
    }

    selectedIndex++;
    renderMenu(Current, menuSize, 1);
}

void prevButton()
{
    if (selectedIndex - 1 < 0)
        return;

    if (selectedIndex - 1 < firstRowIndex)
    {
        firstRowIndex--;
        lastRowIndex--;
        selectedIndex--;
        renderMenuMove(Current, menuSize, -1);
        return;
    }

    selectedIndex--;
    renderMenu(Current, menuSize, -1);
}

void okButton()
{
    
}

void backButton()
{

}

