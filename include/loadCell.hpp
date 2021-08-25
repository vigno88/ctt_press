#pragma once
#include <HX711_ADC.h>



class LoadCell {
public:
    LoadCell();
    ~LoadCell();
    void run();
    void tare();
    float getWeight();
    void setScalingFactor(long scalingFactor);

private:
    HX711_ADC *_loadCell = nullptr;
    float _scalingFactor = 6850;
    float _weight = 0;

    long _lastTime = 0;
    uint8_t _isWaiting = 0;
    bool _isTaring = false;
    bool _newData = false;
};