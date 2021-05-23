#pragma once
#include <Arduino.h>

class PID {
public:
    PID(double kp, double ki, double kd, uint64_t samplingDelay);
    void setTarget(uint8_t target);
    double getOutput(double input);
    void turnOn();
    void turnOff();
private:
    double _kp;
    double _ki;
    double _kd;
    uint64_t  _previousTime, _samplingDelay;
    uint8_t _target;
    double  _lastError, _cumError;
    bool _isOn;
};
