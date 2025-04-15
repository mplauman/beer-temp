#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

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
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("No WiFI connection, reconnecting...");
    connectToWiFi();
  }

  do {
    static char buffer[1024];
    int written = snprintf(buffer, sizeof(buffer), "%s:%d|g\n", STATSD_BUCKET, 1);
    if (written <= 0 || written >= sizeof(buffer)) {
      Serial.println("Error writing to buffer");
      break;
    }

    WiFiUDP udp;
    if (!udp.beginPacket(STATSD_SERVER, STATSD_PORT)) {
      Serial.println("Connection to statsd server failed");
      break;
    }
    if (!udp.write(buffer, written)) {
      Serial.println("Failed to write to UDP packet");
      break;
    }
    if (!udp.endPacket()) {
      Serial.println("Failed to send UDP packet");
      break;
    }

    Serial.print(buffer); // includes a newline
  } while (false);

  delay(5000);
}
