#include "cttPress.hpp"

CttPress::CttPress() {
    Serial.println("Ctt constructor");
    

    tcTop.setKp(4);
    tcTop.setKi(0.2);
    tcTop.setKd(1);
    tcTop.setGoal(20);
    tcTop.start();


    tcBottom.setKp(4);
    tcBottom.setKi(0.2);
    tcBottom.setKd(1);
    tcBottom.setGoal(20);
    tcBottom.start();
}


void CttPress::run() {
    thermoTop.run();
    tcTop.run();
    thermoBottom.run();
    tcBottom.run();

    loadCell.run();
    motor.run();
    controller.run();
}

