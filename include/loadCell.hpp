#pragma once
#include "HX711.h"

#define POLL_DELAY 500

class LoadCell {
public:
    LoadCell();
    ~LoadCell();
    void run();
    void tare();
    long getWeight();
    void setScalingFactor(long scalingFactor);

private:
    HX711 *_loadCell = nullptr;
    double _scalingFactor = 0.01;
    long _weight = 0;

    long _lastTime = 0;
    uint8_t _isWaiting = 0;
};