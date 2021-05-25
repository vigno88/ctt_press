#include "motor.hpp"

void sendOneStep() {
    digitalWrite(stepPin, pulseState);
    pulseState = !pulseState;
}

Motor::Motor(uint8_t step, uint8_t dir, uint8_t enable):  _dirPin(dir), _enablePin(enable) {
    // Enable the motor
    Serial.println("Enable");
    stepPin = step;
    digitalWrite(_enablePin, HIGH);
    _isMoving = false;
}

void Motor::run() {
    // if(_isMoving && (_timerPulse > _delayPulse)) {
    //     digitalWrite(_stepPin, _pulseState);
    //     _pulseState = !_pulseState;
    // }
}

void Motor::MoveUp() {
    // Set the direction
    Serial.println("Move up");
    digitalWrite(_dirPin, DIR_UP);
    stepTimer.begin(sendOneStep, _delayPulse);
    // _isMoving = true;
    // _timerPulse = 0;
}

void Motor::MoveDown() {
    // Set the direction
    Serial.println("Move down");
    digitalWrite(_dirPin, DIR_DOWN);
    stepTimer.begin(sendOneStep, _delayPulse);
    // _isMoving = true;
    // _timerPulse = 0;
}

void Motor::StopMove() {
    Serial.println("Stop move");
    _isMoving = false;
    stepTimer.end();
}