#pragma once
#include "motor.hpp"
#include "Arduino.h"
#include <PID_v1.h>
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
    // void setDurabilityConstant(double c);

    void setKp(double k);
    void setKi(double k);
    void setKd(double k);
    void setStepMultiplier(int multiplier);
    void setSampleTime(int time);
private:
    Motor* _motor = nullptr;
    LoadCell* _loadCell = nullptr;
    boolean isRunning = false;


    // double goalWeight = 0;
    
    // Stepper controller with PID
    const int _pidUpperLim = 100;
    int _stepMultiplier = 1;
    PID* _pid = nullptr;
    double _goalPoint, _currentPoint, _output; 
    double _kp, _ki, _kd;


    const double minimumDelayMicros = 5000;
    elapsedMicros timerPulse = 0;
    long currentDelay = 0;
    // float durabilityConstant = 95/10;



    StateController _state = C_IDLE;

    // long getDelay(float delta);

    long getDelay();
};