#pragma once
#include <Arduino.h>

#define DIR_UP false
#define DIR_DOWN true

static bool pulseState = 0;
static uint8_t stepPin = 0;

class Motor {
public:
    Motor(uint8_t step, uint8_t dir, uint8_t enable);
    // Will move up until it receives a StopMove or after reache maximum position
    void MoveUp();
    // Will move down until it receives a StopMove or after reache maximum position
    void MoveDown();
    // Stop the motor from moving
    void StopMove();
    void setSpeedMovement(uint16_t speed);
    // void sendOneStep();
    void run();
private:
    // uint8_t _stepPin = 0;
    uint8_t _dirPin = 0;
    uint8_t _enablePin = 0;

    // speedMovement is the number of step/second
    uint16_t _speedMovement = 200;
    bool _isMoving = false;
    // bool _pulseState = false;
    bool _dirState = DIR_UP;

    // Timer used to send pulse while using moving function
    // elapsedMicros _timerPulse = 0;
    double _delayPulse = 10;
    IntervalTimer stepTimer;
};