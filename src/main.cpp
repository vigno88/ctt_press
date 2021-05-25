#include "cttPress.hpp"
#include "serverCommunication.hpp"

// CttPress press;
// ServerCommunication comm;

// void setup() {
//   Serial.begin(115200);
//   Serial1.begin(115200);
//   delay(2000);
//   press = CttPress();
//   comm = ServerCommunication(&press);
// }

// void loop() {
//   press.run();
//   comm.run();
// }

int main() {
  pinMode(tc1Pin, INPUT);
  pinMode(tc2Pin, INPUT);
  pinMode(motorStep, OUTPUT);
  pinMode(motorDir, OUTPUT);
  pinMode(motorEnable, OUTPUT);
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