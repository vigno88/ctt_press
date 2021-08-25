#include "motor.hpp"

void Motor::sendOneStep() {
    digitalWrite(_stepPin,_pulseState);
    _pulseState = !_pulseState;
    
    if(_state == StateMotor::MOVING_DOWN) {
        _stepTravelled++;
    } else if(_state == StateMotor::MOVING_UP) {
        _stepTravelled--;
    }
}

Motor::Motor(uint8_t step, uint8_t dir, uint8_t enable):  _dirPin(dir), _enablePin(enable) {
    // Enable the motor
    Serial.println("Enable");
    _stepPin = step;
    digitalWrite(_enablePin, HIGH);
    _state = StateMotor::IDLE;
}

void Motor::run() {
    if(_state != StateMotor::IDLE  && (_timerPulse > _delayPulse)) {
        sendOneStep();
        _timerPulse = 0;
    }
}

void Motor::sendStepDown(long x) {
    _stepCount = 0;
    _stepToReach = x;
    _state = StateMotor::MOVING_DOWN;
    _delayPulse = 5;
    digitalWrite(_dirPin, DIR_DOWN);
}

void Motor::sendSingleStepDown() {
    _state = StateMotor::MOVING_DOWN;
    digitalWrite(_dirPin, DIR_DOWN);
    sendOneStep();
    _state = StateMotor::IDLE;
}

void Motor::sendSingleStepUp() {
    _state = StateMotor::MOVING_UP;
    digitalWrite(_dirPin, DIR_UP);
    sendOneStep();
    _state = StateMotor::IDLE;
}

bool Motor::isSendStepDone() {
    if(_stepCount == _stepToReach) {
        return true;
    }
    return false;
}

void Motor::MoveUp() {
    if(_state == StateMotor::IDLE) {
        // Set the direction
        Serial.println("Move up");
        digitalWrite(_dirPin, DIR_UP);
        _state = StateMotor::MOVING_UP;
        _timerPulse = 0;
        _delayPulse = 5;
    }
}
void Motor::MoveUpSlow() {
    if(_state == StateMotor::IDLE) {
        // Set the direction
        Serial.println("Move up");
        digitalWrite(_dirPin, DIR_UP);
        _state = StateMotor::MOVING_UP;
        _timerPulse = 0;
        _delayPulse = 75;
    }
}

void Motor::MoveDown() {
    if(_state == StateMotor::IDLE) {
        // Set the direction
        Serial.println("Move down");
        digitalWrite(_dirPin, DIR_DOWN);
        _state = StateMotor::MOVING_DOWN;
        _timerPulse = 0;
        _delayPulse = 5;
    }
}

void Motor::MoveDownSlow() {
    if(_state == StateMotor::IDLE) {
        // Set the direction
        Serial.println("Move down");
        digitalWrite(_dirPin, DIR_DOWN);
        _state = StateMotor::MOVING_DOWN;
        _timerPulse = 0;
        _delayPulse = 75;
    }
}

void Motor::StopMove() {
    Serial.println("Stop move");
    _state = StateMotor::IDLE;
}

void Motor::tareDistance() {
    _stepTravelled = 0;
}

double Motor::getDistanceTravelled() {
    return _stepTravelled * _mmPerStep;
}