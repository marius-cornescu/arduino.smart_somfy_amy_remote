//= DEFINES ========================================================================================

//= INCLUDES =======================================================================================
#include "Common.h"
#include <string.h>

#ifdef HAS_DISPLAY
  #include <Wire.h>
  #include <Adafruit_GFX.h>
  #include <Adafruit_SSD1306.h>
#endif

//= CONSTANTS ======================================================================================
// 128×32 = [0.91 Inch OLED Module 0.91" White Blue 128X32 LCD LED Display 0.91" IIC Communicate] || 21 chars x 4 lines || "a12345678901234567890\nb12345678901234567890\nc12345678901234567890\nd12345678901234567890"
// 128X64 = [TENSTAR ROBOT 1.3" OLED Display Module White Blue Color Drive Chip SH1106 128X64 1.3 Inch LCD IIC I2C]

#ifdef HAS_DISPLAY
  #define DISPLAY_BUFFER_SIZE 128
// 
  #define SCREEN_WIDTH 128
  #define SCREEN_HEIGHT 32
  #define OLED_RESET    -1
#endif

//= VARIABLES ======================================================================================
#ifdef HAS_DISPLAY

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
char displayBuffer[DISPLAY_BUFFER_SIZE] = {0};

#endif

//##################################################################################################
//==================================================================================================
//**************************************************************************************************
void display_Setup() {
  debugPrintln(F("DISPLAY:Setup >>>"));
  //..............................
#ifdef HAS_DISPLAY
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    debugPrintln(F("DISPLAY:Init failed"));
    return;
  }
  display.clearDisplay();
  display.display();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(0, 0);
  display_Clear();
  //
  display_Demo();
#endif
  //..............................
  delay(1 * TIME_TICK);
  debugPrintln(F("DISPLAY:Setup <<<"));
}
//**************************************************************************************************
//==================================================================================================
void display_Clear() {
#ifdef HAS_DISPLAY
  memset(displayBuffer, 0, sizeof(displayBuffer));
  display.clearDisplay();
  display.display();
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
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextWrap(true);
  display.print(displayBuffer);
  display.display();
  debugPrint(F("DISPLAY:Write -> "));
  debugPrintln(text);
#endif
}
//==================================================================================================
void display_Write(const __FlashStringHelper* text) {
#ifdef HAS_DISPLAY
  display_Write(String(text).c_str());
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
void display_WriteLine(const __FlashStringHelper* text) {
#ifdef HAS_DISPLAY
  display_Write(text);
#endif
}
//==================================================================================================
void display_Demo() {
#ifdef HAS_DISPLAY
  display.clearDisplay();
  display.ssd1306_command(SSD1306_DISPLAYALLON);  // turn the entire display on, all pixels lit
  display.display();
  delay(2 * SEC);  // hold the pixels full-on
  display.ssd1306_command(SSD1306_DISPLAYALLON_RESUME);  // resume display rendering
  display.display();
#endif
}
//==================================================================================================