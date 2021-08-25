#pragma once
#include <Adafruit_MAX31856.h>
// #include "MAX31856.hpp"

#define POLL_DELAY 500

class Thermocouple {
public:
    Thermocouple(int p, max31856_thermocoupletype_t type);
    // Thermocouple(int pin, int type);
    ~Thermocouple();
    void run();
    float getTemperature();
private:
    // MAX31856 *_tc = nullptr;
    Adafruit_MAX31856 *_tc = nullptr;
    int _pin = 0;
    float _temperature = 0;
    long _lastTime = 0;
    uint8_t _isWaiting = 0;
};