#include <Keypad.h>

#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4
#define ENTER_KEY '#'
#define NEXT_KEY '>'
#define KEY_MAPS 3
#define UNDEFINED_KEY ' '

char keyMaps[KEY_MAPS][KEYPAD_ROWS][KEYPAD_COLS] = {
    {{'a', 'b', 'c', 'd'},
     {'e', 'f', 'g', 'h'},
     {'i', 'j', 'k', 'l'},
     {'m', 'n', '>', '#'}},
    {{'o', 'p', 'q', 'r'},
     {'s', 't', 'u', 'v'},
     {'w', 'x', 'y', 'z'},
     {UNDEFINED_KEY, UNDEFINED_KEY, '>', '#'}},
    {{'0', '1', '2', '3'},
     {'4', '5', '6', '7'},
     {'8', '9', UNDEFINED_KEY, UNDEFINED_KEY},
     {UNDEFINED_KEY, UNDEFINED_KEY, '>', '#'}}};

byte rowPins[KEYPAD_ROWS] = {27, 5, 4, 2};
byte colPins[KEYPAD_COLS] = {15, 16, 17, 14};

Keypad keypads[] = {
    Keypad(makeKeymap(keyMaps[0]), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS),
    Keypad(makeKeymap(keyMaps[1]), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS),
    Keypad(makeKeymap(keyMaps[2]), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS),
};

int currentKeypad = 0;

void WaitKey(char k)
{
    while (true)
    {
        char key = keypads[currentKeypad].getKey();
        if (key == k)
            return;
    }
}
