#pragma once
#include <Arduino.h>
#include <Wire.h>
#include "thermocouple.hpp"
#include "loadCell.hpp"
#include "pid.hpp"
#include "ssr.hpp"
#include "motor.hpp"

// Thermocouple 1
#define tc1Pin 10
// Thermocouple 2
#define tc2Pin 9
// Motor
#define motorStep 23
#define motorDir 22
#define motorEnable 21

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
    LoadCell loadCell = LoadCell();
    Motor motor = Motor(motorStep, motorDir, motorEnable);

};

