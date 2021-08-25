#include "loadCell.hpp"

LoadCell::LoadCell() {
    _loadCell = new  HX711_ADC(18, 19);
    _loadCell->begin();
    _loadCell->start(2000, true);
    _loadCell->setSamplesInUse(80);
    if (_loadCell->getTareTimeoutFlag()) {
        Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
    } else {
        _loadCell->setCalFactor(_scalingFactor); // set calibration value (float)
        Serial.println("Startup load cell is complete");
    }
    _lastTime = millis();
}

LoadCell::~LoadCell() {
    delete _loadCell;
} 

long timer = 0;

void LoadCell::run() {
    if(_loadCell->update()) {
        _newData = true;
    }
     if (_newData) {
      _weight = _loadCell->getData();
      _newData = false;
    }
    if(_loadCell->getTareStatus()) {
        _isTaring = false;
    }
    if(_isTaring) {
        _weight = 99.99;
    }
}

void LoadCell::tare() {
    // if(_loadCell->getTareStatus()){
        _loadCell->tareNoDelay();
        _isTaring = true;
    // }
    // _loadCell->tare();
}

float LoadCell::getWeight() {
    return _weight;
}

void LoadCell::setScalingFactor(long scalingFactor) {
    _scalingFactor = scalingFactor;
    _loadCell->setCalFactor(_scalingFactor);
    // _loadCell->set_scale(_scalingFactor);
}
