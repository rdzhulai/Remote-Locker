#include <LiquidCrystal_I2C.h>

#define DISPLAY_COLS 16
#define DISPLAY_ROW 2

LiquidCrystal_I2C lcd(0x27, DISPLAY_COLS, DISPLAY_ROW);

void display_init()
{
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
}
void display_ask_credentials()
{
    lcd.print("Enter PIN or ");
    lcd.setCursor(0, 1);
    lcd.print("tap a tag");
}
