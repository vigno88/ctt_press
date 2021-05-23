#include "ctt_press.hpp"

CttPress::CttPress() {
    Serial.println("Ctt constructor");
}

void CttPress::run() {
    thermo1.run();
    thermo2.run();
}