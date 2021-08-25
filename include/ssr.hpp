#pragma once
#include <Arduino.h>

// Define the pin of the SSR

class SSR {
public:
    SSR(const uint32_t cycleTime, uint8_t pin);
    // setIntensity gets a value from 0 to 255. This is the value used for the SSR PWM
    void setIntensity(uint8_t i);
    // void run();

    int getIntensity();
    boolean isHigh();
private:
    uint8_t _isLow;
    uint32_t _dutyCycle;
    uint32_t _cycleTime;
    uint32_t _stepTime;

    uint64_t _lastTime;
    uint8_t _pin;
    
    int _i;

};