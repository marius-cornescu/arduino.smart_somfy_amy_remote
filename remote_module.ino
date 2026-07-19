//= DEFINES ========================================================================================
#define REMOTE_SHORT_PRESS_DURATION 100 // 50–200ms
#define REMOTE_LONG_PRESS_DURATION 1000 // 500–2000ms

//= INCLUDES =======================================================================================
#include "Common.h"
#include <Wire.h>

//= CONSTANTS ======================================================================================
const byte REMOTE_BUTTON_PORTS[] = {A0, A1, A2, A3};  // button 1 -> A0, 2 -> A1, 3 -> A2, 4 -> A3
const byte REMOTE_BUTTON_ACTIVE_LEVEL = LOW;
const byte REMOTE_BUTTON_RELEASE_LEVEL = HIGH;

//= VARIABLES ======================================================================================


//##################################################################################################
//==================================================================================================
//**************************************************************************************************
void remote_Setup() {
  debugPrintln(F("REMOTE:Setup >>>"));
  //..............................
  for (byte i = 0; i < ARRAY_LEN(REMOTE_BUTTON_PORTS); ++i) {
    pinMode(REMOTE_BUTTON_PORTS[i], OUTPUT);
    digitalWrite(REMOTE_BUTTON_PORTS[i], REMOTE_BUTTON_RELEASE_LEVEL);
  }
  //..............................
  delay(1 * TIME_TICK);
  debugPrintln(F("REMOTE:Setup <<<"));
}
//**************************************************************************************************
//==================================================================================================
void remote_PressButtonShort(byte buttonId) {
  _PressButtonWithDuration(buttonId, false);
}
//==================================================================================================
void remote_PressButtonLong(byte buttonId) {
  _PressButtonWithDuration(buttonId, true);
}
//==================================================================================================
byte _GetButtonPort(byte buttonId) {
  if (buttonId < 1 || buttonId > ARRAY_LEN(REMOTE_BUTTON_PORTS)) {
    return 0xFF;
  }

  return REMOTE_BUTTON_PORTS[buttonId - 1];
}
//==================================================================================================
void _PressButtonWithDuration(byte buttonId, bool longPress) {
  byte buttonPort = _GetButtonPort(buttonId);
  if (buttonPort == 0xFF) {
    debugPrintln(F("REMOTE: Invalid button id"));
    return;
  }

  debugPrint(F("REMOTE: Press button "));
  debugPrint(buttonId);
  debugPrint(F(" on port "));
  debugPrint(buttonPort);
  debugPrint(longPress ? F(" (long)") : F(" (short)"));
  debugPrintln(F(""));

  pinMode(buttonPort, OUTPUT);
  digitalWrite(buttonPort, REMOTE_BUTTON_ACTIVE_LEVEL);
  delay(longPress ? REMOTE_LONG_PRESS_DURATION : REMOTE_SHORT_PRESS_DURATION);
  digitalWrite(buttonPort, REMOTE_BUTTON_RELEASE_LEVEL);
}
//==================================================================================================