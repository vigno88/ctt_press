#include "pid.hpp"

PID::PID(double kp, double ki, double kd, uint64_t s) : _kp(kp), _ki(ki), _kd(kd), _samplingDelay(s) {
    _target = 0;
    _previousTime = millis();
    _lastError = _cumError = 0;
    _isOn = false;
}

double PID::getOutput(double input) {
    if(!_isOn) {
        return 0;
    }
    // Divide by a thousand because in our case the elapsed time will be in second
    double elapsedTime = (double) (millis() - _previousTime)/1000;
    double error = (double)_target - input; 
    // integral
    _cumError += error * elapsedTime;
    // derivative
    double rateError = (error - _lastError)/elapsedTime;
    _lastError = error;
    _previousTime = millis(); 
    return _kp*error + _ki*_cumError + _kd*rateError;
}

void PID::setTarget(uint8_t t) {
    _target = t;
}