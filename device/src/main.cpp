#include <Arduino.h>
#include "display.h"
#include "keypad.h"
#include "server.h"
#include "tag_reader.h"

#define SERIAL_BAUD 9600

void setup()
{
  Serial.begin(SERIAL_BAUD);
  wifi_connect();
  display_init();
  tag_reader_init();
  display_ask_credentials();
  try
  {
    WriteDataToTag("Hello");
    String data = GetDataFromTag();
    Serial.printf("%s", data);
    delay(2000);
    WriteDataToTag("Bye");
  }
  catch (...)
  {
  }
}

void loop()
{
}