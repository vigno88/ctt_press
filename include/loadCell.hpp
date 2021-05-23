#pragma once
#include "HX711.h"

#define POLL_DELAY 500

class LoadCell {
public:
    LoadCell(long LOADCELL_OFFSET,long LOADCELL_DIVIDER);
    ~LoadCell();
    void run();
    void tare();
    long getWeight();
    void setOffset(long offset);
    void setDivider(long divider);

private:
    HX711 *_loadCell = nullptr;
    long _offset = 0;
    long _divider = 0;
    long _weight = 0;

    long _lastTime = 0;
    uint8_t _isWaiting = 0;
};