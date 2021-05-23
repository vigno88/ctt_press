#pragma once

class Motor {
public:
    Motor(uint8_t step, uint8_t dir);
    // Will move up until it receives a StopMove or after reache maximum position
    void MoveUp();
    // Will move down until it receives a StopMove or after reache maximum position
    void MoveDown();
    // Stop the motor from moving
    void StopMove();
    void setSpeedMovement(uint16_t speed);
private:
    uint8_t _stepPin = 0;
    uint8_t _dirPin = 0;
    // speedMovement is the number of step/second
    uint16_t speedMovement = 200;
};