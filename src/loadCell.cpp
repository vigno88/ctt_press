#include "loadCell.hpp"

LoadCell::LoadCell(long offset,long divider) : _offset(offset), _divider(divider) {
    _loadCell = new HX711();
    _loadCell->begin(18,19);
    _loadCell->set_scale(divider);
    _loadCell->set_offset(offset);
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

void LoadCell::setDivider(long divider) {
    _divider = divider;
}

void LoadCell::setOffset(long offset) {
    _offset = offset;
}