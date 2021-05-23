#pragma once
#include <Arduino.h>
#include <Wire.h>
#include "thermocouple.hpp"
#include "loadCell.hpp"
#include "pid.hpp"
#include "ssr.hpp"
#include "motor.hpp"

#define tc1Pin 10
#define tc2Pin 9

const uint16_t HEATER_DELAY = 2000;
const uint16_t TEMP_DELAY = 500;
const uint16_t PID_H_DELAY = 2000;

class CttPress {
public:
    CttPress();
    void run();

    SSR heatingPlate1 = SSR(HEATER_DELAY);
    SSR heatingPlate2 = SSR(HEATER_DELAY);
    Thermocouple thermo1 = Thermocouple(tc1Pin, MAX31856_TCTYPE_J);
    Thermocouple thermo2 = Thermocouple(tc2Pin, MAX31856_TCTYPE_J);
    PID pidHeatingPlate1 = PID(2, 0.5, 1, PID_H_DELAY);
    PID pidHeatingPlate2 = PID(2, 0.5, 1, PID_H_DELAY);
    LoadCell loadCell = LoadCell(0,0);
    Motor motor;

    LoadCell loadCell;
};

