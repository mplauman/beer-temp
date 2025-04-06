#include <Arduino.h>

void setup() {
  Serial.begin(115200); // See `monitor_speed` in platformio.ini
  delay(2000);
}

void loop() {
  Serial.println("Hello, world!");
  delay(1000);
}
