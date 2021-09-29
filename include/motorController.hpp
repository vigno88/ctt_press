#pragma once
#include "motor.hpp"
#include "Arduino.h"
#include "pid.hpp"
#include "loadCell.hpp"

enum StateController {
    C_IDLE,
    GOING_DOWN,
    IS_IN_RANGE,
    GOING_UP
};

class MotorController {
public:
    MotorController(Motor* motor, LoadCell* loadcell, int pin_limit);
    void setTo(double weight);
    void run();
    void stop();
    void start();
    // void setDurabilityConstant(double c);

    void setKp(double k);
    void setKi(double k);
    void setKd(double k);
    void setStepMultiplier(double multiplier);
    void setSampleTime(int time);
    double _goalPoint, _currentPoint, _output; 
    double _kp, _ki, _kd;
    int sampleTime = 5000;
    int maxLoad = 1000;

    void MoveDown();
    void MoveDownSlow();
    void MoveUp();
    void MoveUpSlow();
private:
    Motor* _motor = nullptr;
    LoadCell* _loadCell = nullptr;
    boolean isRunning = false;


    // double goalWeight = 0;
    
    // Stepper controller with PID
    const int _pidUpperLim = 100;
    double _stepMultiplier = 1;
    // double _goalPoint, _currentPoint, _output; 
    // double _kp, _ki, _kd;
    PID* _pid = nullptr;
    const double minimumDelayMicros = 5000;
    elapsedMicros timerPulse = 0;
    long currentDelay = 0;


    int pin_limit_switch = 0;
    StateController _state = C_IDLE;

    // long getDelay(float delta);

    long getDelay();
};