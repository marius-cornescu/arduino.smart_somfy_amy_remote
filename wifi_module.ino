//= DEFINES ========================================================================================

//= INCLUDES =======================================================================================
#include "Common.h"
#include "Secrets.h"

#if defined(ESP8266)
  #include <ESP8266WiFi.h>
#elif defined(ESP32)
  #include <WiFi.h>
#endif

//= CONSTANTS ======================================================================================
const char host_name[] = HOST_NAME;
// WiFi credentials (password to "" for open networks)
const char ssid[] = WIFI_SSID;
const char pass[] = WIFI_PASSWORD;

//= VARIABLES ======================================================================================

unsigned long lastWiFiCheckTime = 0;
const unsigned long wifiCheckInterval = 60 * SEC;
const unsigned long maxDisconnectTime = 30 * 60 * SEC; // 30 minutes
unsigned long wifiDisconnectTime = 0;

//##################################################################################################
//==================================================================================================
//**************************************************************************************************
void wifi_Setup() {
  debugPrintln(F("Wifi:Setup >>>"));
  //..............................
  delay(TIME_TICK);
#if defined(ESP8266)
  WiFi.hostname(host_name);
  WiFi.setOutputPower(0);  // Sets WiFi RF power output to lowest level, lowest RF power usage
#elif defined(ESP32)
  WiFi.setHostname(host_name);
#endif
  // We start by connecting to a WiFi network
  debugPrintln(F(""));
  debugPrint(F("Connecting to "));
  debugPrint(ssid);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(50 * TIME_TICK);
    debugPrint(F("."));
  }

  debugPrintln(F(""));
  debugPrintln(wifi_GetConnectionStatusText());
  //..............................
  delay(10 * TIME_TICK);
  debugPrintln(F("Wifi:Setup <<<"));
}
//**************************************************************************************************
//==================================================================================================
void wifi_MaintainConnection() {
  unsigned long currentTime = millis();

  if (currentTime - lastWiFiCheckTime >= wifiCheckInterval) {
    lastWiFiCheckTime = currentTime;

    if (WiFi.status() != WL_CONNECTED) {
      if (wifiDisconnectTime == 0) {
        wifiDisconnectTime = currentTime;
      } else if (currentTime - wifiDisconnectTime >= maxDisconnectTime) {
        ESP.restart(); // Reboot the device
      }
    } else {
      wifiDisconnectTime = 0; // Reset the disconnect time if WiFi is connected
    }
  }
}
//==================================================================================================
const char* wifi_GetConnectionStatusText() {
  static char statusBuffer[48];

  if (WiFi.status() == WL_CONNECTED) {
    String ipAddress = WiFi.localIP().toString();
    snprintf(statusBuffer, sizeof(statusBuffer), "WiFi %s", ipAddress.c_str());
    return statusBuffer;
  }

  return "WiFi disconnected";
}
//==================================================================================================