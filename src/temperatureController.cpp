#include "temperatureController.hpp"

TemperatureController::TemperatureController(SSR* ssr, Thermocouple* t) {
    _ssr = ssr;
    _t = t;
    _goalPoint = 0;
    _currentPoint = _t->getTemperature();
    _output = 0;
    _kp = 0;
    _ki = 0;
    _kd = 0;
    _isRunning = false;
    _pid = new PID(&_currentPoint, &_output, &_goalPoint,_kp, _ki, _kd, DIRECT);
    //turn the PID on
    _pid->SetMode(AUTOMATIC);
}


void TemperatureController::print() {
    // Serial.printf("Goal: %f, current: %f, output: %f, kp: %f, ki: %f, kd:%f\n", _goalPoint, _currentPoint, _output, _kp, _ki, _kd);

}
TemperatureController::~TemperatureController() {
    if(_pid != nullptr) {
        delete _pid;
    }
    _pid = nullptr;
}

void TemperatureController::start() {
    if(_pid != nullptr) {
        delete _pid;
    }
     _pid = new PID(&_currentPoint, &_output, &_goalPoint,_kp, _ki, _kd, DIRECT);
    //turn the PID on
    _pid->SetMode(AUTOMATIC);
    _isRunning = true;
}

void TemperatureController::stop() {
    _isRunning = false;
    _goalPoint = 15;
    _ssr->setIntensity(0);
    // delete _pid;
}

void TemperatureController::setGoal(double g) {
    _goalPoint = g;
}


void TemperatureController::setKp(double k) {
    _kp = k;
    _pid->SetTunings(_kp,_ki, _kd);
}

void TemperatureController::setKi(double k) {
    _ki = k;
    _pid->SetTunings(_kp,_ki, _kd);
}

void TemperatureController::setKd(double k) {
    _kd = k;
    _pid->SetTunings(_kp,_ki, _kd);
}

void TemperatureController::run() {
    if (_isRunning) {
         _currentPoint = _t->getTemperature();
        _pid->Compute();
        _ssr->setIntensity((int) _output);
    }
}