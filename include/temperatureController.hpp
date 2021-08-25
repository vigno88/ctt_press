#pragma once
#include "ssr.hpp"
#include "thermocouple.hpp"
#include <PID_v1.h>

class TemperatureController {
public:
    TemperatureController(SSR* ssr, Thermocouple* t);
    ~TemperatureController();

    void start();
    void stop();

    void setGoal(double g);
    void setKp(double k);
    void setKi(double k);
    void setKd(double k);
    void run();
    void print();
private:
    SSR* _ssr = nullptr;
    Thermocouple* _t = nullptr;
    PID* _pid = nullptr;
    double _goalPoint, _currentPoint, _output; 
    double _kp, _ki, _kd;
    boolean _isRunning;
};