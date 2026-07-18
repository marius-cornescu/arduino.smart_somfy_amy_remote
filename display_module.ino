//= DEFINES ========================================================================================

//= INCLUDES =======================================================================================
#include "Common.h"
#include <Wire.h>
#include <string.h>

//= CONSTANTS ======================================================================================
#define DISPLAY_BUFFER_SIZE 128

//= VARIABLES ======================================================================================
#ifdef HAS_DISPLAY
char displayBuffer[DISPLAY_BUFFER_SIZE] = {0};
#endif

//##################################################################################################
//==================================================================================================
//**************************************************************************************************
void display_Setup() {
  debugPrintln(F("DISPLAY:Setup >>>"));
  //..............................
  display_Clear();
  //..............................
  delay(1 * TIME_TICK);
  debugPrintln(F("DISPLAY:Setup <<<"));
}
//**************************************************************************************************
//==================================================================================================
void display_Clear() {
#ifdef HAS_DISPLAY
  memset(displayBuffer, 0, sizeof(displayBuffer));
  debugPrintln(F("DISPLAY:Clear"));
#endif
}
//==================================================================================================
void display_Write(const char* text) {
#ifdef HAS_DISPLAY
  if (text == nullptr) {
    return;
  }

  size_t textLen = strlen(text);
  size_t currentLen = strlen(displayBuffer);

  if ((currentLen + textLen) >= sizeof(displayBuffer)) {
    textLen = sizeof(displayBuffer) - currentLen - 1;
  }

  strncat(displayBuffer, text, textLen);
  debugPrint(F("DISPLAY:Write -> "));
  debugPrintln(text);
#endif
}
//==================================================================================================
void display_WriteLine(const char* text) {
#ifdef HAS_DISPLAY
  display_Write(text);
  display_Write("\n");
#endif
}
//==================================================================================================