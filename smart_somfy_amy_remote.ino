//  Smart SOMFY AMY 4 IO Remote
//  "MakerGO ESP32 C3 SuperMini"
/*
  PIN CONNECTIONS
  -------------------------------
  -------------------------------
  -------------------------------

*/
//= DEFINES ========================================================================================
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//#define DEBUG
//#define DEBUG_REMOTE

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define OFF 0x1
#define ON 0x0

#define VCC_SENSOR_PIN A0
#define SOUND_SENSOR_PIN A1


//= INCLUDES =======================================================================================
#include "Common.h"


//= CONSTANTS ======================================================================================

//= VARIABLES ======================================================================================


//##################################################################################################
//==================================================================================================
//**************************************************************************************************
void setup() {
// #if defined(DEBUG) || defined(DEBUG_REMOTE)
//   // Open serial communications and wait for port to open:
//   Serial.begin(115200);
//   while (!Serial) { ; }
//   delay(5 * SEC);
// #endif
  debugPrintln(F("START-UP >>>>>>>>>>>>>>>"));
  //..............................
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, ON);
  //..............................
  //
  bcm_Setup();
  //
  digitalWrite(LED_BUILTIN, OFF);
  //..............................
  debugPrintln(F("START-UP <<<<<<<<<<<<<<<"));
}
//**************************************************************************************************
//OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
void loop() {
  debugPrintln(F("##############################"));
  //
  bool shouldPublishMeasurements = collectMeasurements();
  //
  if (shouldPublishMeasurements) {
    debugPrintln(F("MAIN: Publish measurements"));
    //
    digitalWrite(LED_BUILTIN, ON);
    //

    //
    digitalWrite(LED_BUILTIN, OFF);
  }
  //
  //sleepFDRS(PERIOD_MEASUREMENT);
}
//OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
//==================================================================================================
bool collectMeasurements() {
  debugPrintln(F("MAIN: Collect measurements"));
  //

  //
  return true;
}
//==================================================================================================

//==================================================================================================
