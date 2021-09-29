#pragma once
#include <Arduino.h>

#define DIR_UP false
#define DIR_DOWN true

// static bool pulseState = 0;
// static uint8_t stepPin = 0;

enum StateMotor {
    IDLE = 0,
    MOVING_UP,
    MOVING_DOWN
};

class Motor {
public:
    Motor(uint8_t step, uint8_t dir, uint8_t enable);
    // Will move up until it receives a StopMove or after reache maximum position
    void MoveUp();
    // Will move down until it receives a StopMove or after reache maximum position
    void MoveDown();
    // Stop the motor from moving
    void StopMove();
    void MoveUpSlow();
    void MoveDownSlow();

    void setSpeedMovement(uint16_t speed);
    void sendOneStep();
    void run();

    double getDistanceTravelled();
    void tareDistance();


    void sendStepDown(long x);
    void sendSingleStepDown();
    void sendSingleStepUp();

    long delaySlow = 150;
    StateMotor _state = StateMotor::IDLE;
private:
    uint8_t _stepPin = 0;
    uint8_t _dirPin = 0;
    uint8_t _enablePin = 0;

    // speedMovement is the number of step/second
    uint16_t _speedMovement = 200;
    // StateMotor _state = StateMotor::IDLE;
    bool _pulseState = false;
    bool _dirState = DIR_UP;

    elapsedMicros _timerPulse = 0;
    long _delayPulse = 5;

    long _stepTravelled = 0;
    double _mmPerStep = 0.00006515;

    bool needPulse();
    // Will drive the pulse down
    void runPulse();

    long _stepCount = 0;
    long _stepToReach = 0;
    bool isSendStepDone();

    long _currentTime = 0;
    long _lastTime = 0;
};