# Smart SOMFY AMY Remote

A compact Arduino sketch for a MakerGO ESP32 C3 SuperMini remote that connects to WiFi, maintains MQTT communication, and exchanges remote-control messages.

## What it does
- Connects to WiFi and keeps the connection alive
- Sets up MQTT publish/subscribe communication
- Publishes status data and handles remote commands

## Project files
- [smart_somfy_amy_remote.ino](smart_somfy_amy_remote.ino): main sketch with setup and loop
- [wifi_module.ino](wifi_module.ino): WiFi setup and connection maintenance
- [mqtt_pubsub_module.ino](mqtt_pubsub_module.ino): MQTT logic
- [remote_module.ino](remote_module.ino): remote-control behavior
- [Common.h](Common.h): shared macros and helpers

## Build notes
- Target board: ESP32 C3 SuperMini
- Required libraries: PubSubClient, WiFi, and Wire
- Configure WiFi and MQTT settings in [Secrets.h](Secrets.h)
