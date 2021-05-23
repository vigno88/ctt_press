#pragma once
#include <Arduino.h>

// Define the pin of the SSR
#define pin 9

class SSR {
public:
    SSR(const uint32_t cycleTime);
    // setIntensity gets a value from 0 to 255. This is the value used for the SSR PWM
    void setIntensity(uint8_t i);
    void run();
private:
    uint8_t _isLow;
    uint32_t _dutyCycle;
    uint32_t _cycleTime;
    uint32_t _stepTime;

    uint64_t _lastTime;

};