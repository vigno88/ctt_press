#include "loadCell.hpp"

LoadCell::LoadCell() {
    _loadCell = new HX711();
    _loadCell->begin(18,19);
    _lastTime = millis();
}

LoadCell::~LoadCell() {
    delete _loadCell;
} 

void LoadCell::run() {
    if(_isWaiting) {
        if(millis() - _lastTime < POLL_DELAY) {
            return;
        }
        // Check if ready
        if(_loadCell->wait_ready_timeout(1000)) {
            _weight = _loadCell->get_units(10);
            _isWaiting = 0;
        }
        return;
    }
    _isWaiting = 1;
    _lastTime = millis();
}

void LoadCell::tare() {
    _loadCell->tare();
}

long LoadCell::getWeight() {
    return _weight;
}

void LoadCell::setScalingFactor(long scalingFactor) {
    _scalingFactor = scalingFactor;
    _loadCell->set_scale(_scalingFactor);
}
