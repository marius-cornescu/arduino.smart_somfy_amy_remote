//  Smart SOMFY AMY 4 IO Remote
//  "MakerGO ESP32 C3 SuperMini"
/*
  PIN CONNECTIONS
  -------------------------------
  -------------------------------
  -------------------------------

*/
//= DEFINES ========================================================================================
//
#define PUBLISH_PORT_TOPIC "home/remote/somfy-remote/port/"
#define PUBLISH_STATUS_TOPIC "home/remote/somfy-remote/status"

#define SUBSCRIBE_TOPIC "home/remote/somfy-remote/command/+"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//#define DEBUG
//#define DEBUG_REMOTE
//#define DEBUG_MQTT

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define OFF 0x1
#define ON 0x0


//= INCLUDES =======================================================================================
#include "Common.h"
#include <PubSubClient.h>
#include <Wire.h>

//= CONSTANTS ======================================================================================
#if defined(ESP8266)
  Client wifiClient = espClient;
#elif defined(ESP32)
  Client wifiClient = client;
#endif

//= VARIABLES ======================================================================================


//##################################################################################################
//==================================================================================================
//**************************************************************************************************
void setup() {
#ifdef DEBUG
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) { ; }
#endif
  debugPrintln(F("START-UP >>>>>>>>>>>>>>>"));
  //..............................
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, ON);
  //..............................
  //
  wifi_Setup();
  //
  //pins_Setup();
  //
  mqtt_Setup();
  //
  digitalWrite(LED_BUILTIN, OFF);
  //
  delay(1 * TIME_TICK);
  //..............................
  debugPrintln(F("START-UP <<<<<<<<<<<<<<<"));
}
//**************************************************************************************************
//OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
void loop() {
  wifi_MaintainConnection();
  mqtt_MaintainConnection();
  //
  if (mqtt_ShouldPublish()) {
    publishStatusDataToMqtt();
  }
  //
  delay(100 * TIME_TICK);
}
//OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
//==================================================================================================
void publishStatusDataToMqtt() {
  digitalWrite(LED_BUILTIN, LOW);
  //
  // could print sw version; params like PUBLISH_COLLDOWN_TIME
  //
  // char statusReport[4];
  // utoa((unsigned)voltage_supply, statusReport, 10);
  // mqtt_PublishString(PUBLISH_STATUS_TOPIC, statusReport);
  //
  digitalWrite(LED_BUILTIN, HIGH);
}
//==================================================================================================

//==================================================================================================
