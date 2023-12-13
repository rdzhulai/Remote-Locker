#include <Keypad.h>

#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4
#define ENTER_KEY 'F'

char hexaKeys[KEYPAD_ROWS][KEYPAD_COLS] = {
    {'0', '1', '2', '3'},
    {'4', '5', '6', '7'},
    {'8', '9', 'A', 'B'},
    {'C', 'D', 'E', 'F'}};

byte rowPins[KEYPAD_ROWS] = {27, 5, 4, 2};
byte colPins[KEYPAD_COLS] = {15, 16, 17, 14};

Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);

String read_pin()
{
    String pin;
    while (true)
    {
        char key = keypad.getKey();
        if (key)
        {
            if (key == ENTER_KEY)
                break;
            pin += key;
            Serial.println(pin);
        }
    }
    return pin;
}