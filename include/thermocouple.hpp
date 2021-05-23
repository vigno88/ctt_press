#pragma once
#include <Adafruit_MAX31856.h>

#define POLL_DELAY 500

class Thermocouple {
public:
    Thermocouple(int pin, max31856_thermocoupletype_t type);
    ~Thermocouple();
    void run();
    float getTemperature();
private:
    Adafruit_MAX31856 *_tc = nullptr;
    float _temperature = 0;
    long _lastTime = 0;
    uint8_t _isWaiting = 0;
};