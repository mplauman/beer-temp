#include <Adafruit_AHTX0.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>

#include "secrets.hpp"

namespace {
  Adafruit_AHTX0 aht;

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
  
  bool writeFloat(WiFiUDP &udp, const char *const bucket, float value) {
    char buffer[1024];

    int written = snprintf(buffer, sizeof(buffer), "%s:%.2f|g\n", bucket, value);
    if (written <= 0 || written >= sizeof(buffer)) {
      Serial.println("Error writing to buffer");
      return false;
    }
  
    if (!udp.beginPacket(STATSD_SERVER, STATSD_PORT)) {
      Serial.println("Connection to statsd server failed");
      return false;
    }

    if (!udp.write(buffer, written)) {
      Serial.println("Failed to write to UDP packet");
      return false;
    }

    if (!udp.endPacket()) {
      Serial.println("Failed to send UDP packet");
      return false;
    }

    return true;
  }
}

void setup() {
  Serial.begin(115200); // See `monitor_speed` in platformio.ini
  
  while (!aht.begin()) {
    Serial.println("Failed to initialize AHT21 sensor!");
    delay(1000);
  }
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("No WiFI connection, reconnecting...");
    connectToWiFi();
  }

  do {
    static sensors_event_t humidity, temp;
    if (!aht.getEvent(&humidity, &temp)) {
      Serial.println("Failed to read from AHT21 sensor");
      break;
    }

    WiFiUDP udp;
    if (!writeFloat(udp, STATSD_TEMPERATURE_BUCKET, temp.temperature)) {
      Serial.println("Failed to record temperature");
    }

    if (!writeFloat(udp, STATSD_HUMIDITY_BUCKET, humidity.relative_humidity)) {
      Serial.println("Failed to record humidity");
    }

    Serial.printf("temperature: %.2f °C, humidity: %.2f%%\n", temp.temperature, humidity.relative_humidity);
  } while (false);

  delay(5000);
}
