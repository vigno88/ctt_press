#include "cttPress.hpp"

CttPress::CttPress() {
    Serial.println("Ctt constructor");
}

void CttPress::run() {
    thermo1.run();
    thermo2.run();
    loadCell.run();
    motor.run();
}