#include <Arduino.h>
#include "display.h"
#include "keypad.h"
#include "server.h"
#include "tag_reader.h"

#define SERIAL_BAUD 9600

State state = {-1, "", "", "", true, true, ""};

void InputCredentials(String &username, String &password);
int SelectOption(String options[], int n);
String ReadText(bool hidden);

void core1Task(void *paramenter)
{
  State previousState;
  for (;;)
  {
    previousState.user_id = state.user_id;
    previousState.username = state.username;
    previousState.name = state.name;
    previousState.locked = state.locked;
    previousState.blocked = state.blocked;
    previousState.status = state.status;

    UpdateState(state);
    if (previousState.locked != state.locked)
      digitalWrite(33, state.locked ? LOW : HIGH);
    delay(1000);
  }
}

void setup()
{
  pinMode(33, OUTPUT);
  xTaskCreatePinnedToCore(
      core1Task,   // Function to run on the second core
      "core1Task", // Task name
      10000,       // Stack size (bytes)
      NULL,        // Task input parameter
      1,           // Task priority
      NULL,        // Task handle
      0            // Core to run the task on (1 or 0)
  );
  Serial.begin(9600);
  Serial.println(xPortGetCoreID());
  DisplayInit();
  TagReaderInit();
  ShowOnDisplay("Connecting...");
  ConnectToWiFi();
}

void loop()
{

  InputCredentials(state.username, state.password);
  Serial.println("Name:" + state.username + ", Password:" + state.password);
  if (SignIn(state))
  {

    State changedState;
    while (true)
    {
      ShowOnDisplayRow("Settings", 0);
      String options[] = {"Toggle " + state.name, "Status", "Write Tag"};
      switch (SelectOption(options, 3))
      {
      case 0:
        if (state.blocked)
        {
          ShowOnDisplay(state.name + " is blocked");
          WaitKey(ENTER_KEY);
          break;
        }
        changedState.blocked = state.blocked;
        changedState.locked = !state.locked;
        changedState.name = state.name;
        changedState.username = state.username;
        changedState.user_id = changedState.user_id;
        changedState.username = state.username;
        changedState.password = state.password;
        if (!ChangeState(changedState))
        {
          ShowOnDisplay("Failed to " + String(state.locked ? "unlock" : "lock"));
          WaitKey(ENTER_KEY);
          break;
        }
        break;
      case 1:
        Serial.println(state.status);
        ShowOnDisplay(state.status);
        WaitKey(ENTER_KEY);
        break;
      case 2:
        ShowOnDisplay("Writing...");
        if (!WriteCredentialsToTag(state.username, state.password))
        {
          ShowOnDisplay("Failed");
          WaitKey(ENTER_KEY);
        }
        break;

      default:
        throw;
      }
    }
  }
}

String ReadText(bool hidden)
{
  String text;
  lcd.setCursor(DISPLAY_COLS - 1, DISPLAY_ROWS - 1);
  lcd.printf("%d", currentKeypad);
  while (true)
  {
    char key = keypads[currentKeypad].getKey();
    switch (key)
    {
    case 0:
      break;
    case ENTER_KEY:
      return text;
    case NEXT_KEY:
      if (++currentKeypad == KEY_MAPS)
        currentKeypad = 0;
      lcd.setCursor(DISPLAY_COLS - 1, DISPLAY_ROWS - 1);
      lcd.printf("%d", currentKeypad);
      break;
    case UNDEFINED_KEY:
      break;
    default:
      text += key;
      if (!hidden)
        ShowOnDisplay(text);
      lcd.setCursor(DISPLAY_COLS - 1, DISPLAY_ROWS - 1);
      lcd.printf("%d", currentKeypad);
    }
  }
}

int SelectOption(String options[], int n)
{
  ShowOnDisplayRow(options[0], 1);
  for (int i = 0;;)
  {
    char key = keypads[currentKeypad].getKey();
    switch (key)
    {
    case ENTER_KEY:
      return i;
    case NEXT_KEY:
      if (++i == n)
        i = 0;
      ShowOnDisplayRow(options[i], 1);
    }
  }
}

void InputCredentials(String &username, String &password)
{
  ShowOnDisplay("Authorization:");
  String options[] = {"Type credentials", "Tap tag"};
  while (true)
  {
    switch (SelectOption(options, 2))
    {
    case 0:
      while (true)
      {
        ShowOnDisplay("Enter Name:");
        username = ReadText(false);
        if (username.length() <= 16)
          break;
        ShowOnDisplay("16 chars max");
        WaitKey(ENTER_KEY);
      }
      while (true)
      {
        ShowOnDisplay("Enter password:");
        password = ReadText(false);
        if (password.length() <= 16)
          break;
        ShowOnDisplay("16 chars max");
        WaitKey(ENTER_KEY);
      }
      return;
    case 1:
      ShowOnDisplay("Reading...");
      if (ReadCredentialsFromTag(username, password))
        return;
      ShowOnDisplay("Failed");
      WaitKey(ENTER_KEY);
      break;
    default:
      throw;
    }
  }
}