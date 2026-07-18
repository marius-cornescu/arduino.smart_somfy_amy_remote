//  Smart SOMFY AMY 4 IO Remote
//  "MakerGO ESP32 C3 SuperMini"
/*
  PIN CONNECTIONS
  -------------------------------
  -------------------------------
  -------------------------------
  -------------------------------
Sketch uses 983295 bytes (75%) of program storage space. Maximum is 1310720 bytes.
Global variables use 37440 bytes (11%) of dynamic memory, leaving 290240 bytes for local variables. Maximum is 327680 bytes.
  -------------------------------
*/
//= DEFINES ========================================================================================
//
#define MQTT_BASE_TOPIC "home/remote/somfy-remote"
#define PUBLISH_PORT_TOPIC MQTT_BASE_TOPIC "/port/"
#define PUBLISH_STATUS_TOPIC MQTT_BASE_TOPIC "/status"
#define SUBSCRIBE_TOPIC MQTT_BASE_TOPIC "/command/+"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define DEBUG
//#define DEBUG_REMOTE
//#define DEBUG_MQTT

#define HAS_DISPLAY

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define OFF 0x1
#define ON 0x0


//= INCLUDES =======================================================================================
#include "Common.h"
#include <PubSubClient.h>
#include <Wire.h>

#if defined(ESP8266)
  #include <ESP8266WiFi.h>
#elif defined(ESP32)
  #include <WiFi.h>
#endif

//= CONSTANTS ======================================================================================


//= VARIABLES ======================================================================================
WiFiClient wifiClient;


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
  mqtt_Setup();
  //
  display_Setup();
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
  //display_Write("a12345678901234567890\nb12345678901234567890\nc12345678901234567890\nd12345678901234567890");
  display_SetLine(0, wifi_GetConnectionStatusText());
  display_SetLine(1, mqtt_GetConnectionStatusText());
  //display_Demo();
  //
  wifi_MaintainConnection();
  mqtt_MaintainConnection();
  //
  if (mqtt_ShouldPublish()) {
    publishStatusDataToMqtt();
  }
  //
  delay(500 * TIME_TICK);
  //
  display_Clear();
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
