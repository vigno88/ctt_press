#include "ctt_press.hpp"
CttPress press;

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  delay(2000);
  press = CttPress();
}

void loop() {
  press.run();
}