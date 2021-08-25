#pragma once
#include <Arduino.h>
#include <Wire.h>
#include "thermocouple.hpp"
#include "loadCell.hpp"
#include "ssr.hpp"
#include "motor.hpp"
#include "motorController.hpp"
#include "temperatureController.hpp"

// Thermocouple 1
#define tc1Pin 9
// Thermocouple 2
#define tc2Pin 10
// Motor
#define motorStep 23
#define motorDir 22
#define motorEnable 21

// SSR
#define pin_ssr1 3
#define pin_ssr2 4


const uint16_t HEATER_DELAY = 2000;
const uint16_t TEMP_DELAY = 500;
const uint16_t PID_H_DELAY = 2000;

class CttPress {
public:
    CttPress();
    void run();

    SSR heatingPlateTop = SSR(HEATER_DELAY,pin_ssr1);
    SSR heatingPlateBottom = SSR(HEATER_DELAY,pin_ssr2);
    Thermocouple thermoTop = Thermocouple(tc1Pin, MAX31856_TCTYPE_J);
    Thermocouple thermoBottom = Thermocouple(tc2Pin, MAX31856_TCTYPE_J);

    TemperatureController tcTop = TemperatureController(&heatingPlateTop, &thermoTop);
    TemperatureController tcBottom = TemperatureController(&heatingPlateBottom, &thermoBottom);
    LoadCell loadCell = LoadCell();
    Motor motor = Motor(motorStep, motorDir, motorEnable);
    MotorController controller = MotorController(&motor, &loadCell);

};

