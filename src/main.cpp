#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "secrets.hpp"

void connectToWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200); // See `monitor_speed` in platformio.ini
  delay(2000);

  connectToWiFi();  
}

void loop() {
  Serial.println("Hello, world!");
  delay(1000);
}
