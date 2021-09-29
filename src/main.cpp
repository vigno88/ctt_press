#include "cttPress.hpp"
#include "serverCommunication.hpp"

int main() {
  pinMode(tc1Pin, INPUT);
  pinMode(tc2Pin, INPUT);
  pinMode(motorStep, OUTPUT);
  pinMode(motorDir, OUTPUT);
  pinMode(motorEnable, OUTPUT);
  pinMode(pin_ssr1, OUTPUT);
  pinMode(pin_ssr2, OUTPUT);
  pinMode(pin_limit_switch, INPUT);

  Serial.begin(115200);
  Serial1.begin(115200);
  delay(2000);

  CttPress press = CttPress();
  ServerCommunication comm = ServerCommunication(&press);
  
  while(1) {
    press.run();
    comm.run();
  }
  return 0;
}

