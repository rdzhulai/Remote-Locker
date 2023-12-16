#include <LiquidCrystal_I2C.h>

#define DISPLAY_COLS 16
#define DISPLAY_ROWS 2
#define DISPLAY_CAPACITY (DISPLAY_ROWS * DISPLAY_COLS)

LiquidCrystal_I2C lcd(0x27, DISPLAY_COLS, DISPLAY_ROWS);

void DisplayInit()
{
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
}

void ShowOnDisplay(String text)
{
    lcd.clear();
    int len = text.length();
    lcd.setCursor(0, 0);
    lcd.print(text);
    if (len > DISPLAY_COLS)
    {
        lcd.setCursor(0, 1);
        lcd.print(text.c_str() + DISPLAY_COLS);
    }
}

void ShowOnDisplayRow(String text, uint row)
{
    if (row < DISPLAY_ROWS)
    {
        lcd.setCursor(0, row);
        lcd.print("                ");
        lcd.setCursor(0, row);
        lcd.print(text);
    }
}
