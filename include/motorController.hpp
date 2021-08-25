#pragma once
#include "motor.hpp"
#include "Arduino.h"
// #include "PID_v1.h"
#include "loadCell.hpp"

enum StateController {
    C_IDLE,
    GOING_DOWN,
    IS_IN_RANGE,
    GOING_UP
};

class MotorController {
public:
    MotorController(Motor* motor, LoadCell* loadcell);
    void setTo(double weight);
    void run();
    void stop();
    void start();
    void setDurabilityConstant(double c);
private:
    Motor* _motor = nullptr;
    LoadCell* _loadCell = nullptr;
    boolean isRunning = false;


    double goalWeight = 0;
    const double minimumDelayMicros = 5000;
    elapsedMicros timerPulse = 0;
    // const int ratingLo5dCell = 500;
    long currentDelay = 0;
    float durabilityConstant = 95/10;



    StateController _state = C_IDLE;
    // long timeBootUp = 0;
    // // int bootupDelayMS = 5000;

    long getDelay(float delta);
};