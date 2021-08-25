#include "ssr.hpp"

SSR::SSR(const uint32_t cycleTime,uint8_t pin): _cycleTime(cycleTime), _pin(pin) {
    // Start the ssr with no voltage on the output pin
    _dutyCycle = 0;
    _isLow = 0;
    _lastTime = millis();
    _stepTime = _cycleTime / 255;
    digitalWrite(_pin, LOW);
}

void SSR::setIntensity(uint8_t i) {
    _i = i;
    // Scale the intensity to a time between 0 and the cycleTime
    _dutyCycle = i * _stepTime;
    analogWrite(_pin, i);
}

// void SSR::run() {
//     // long currentTime = millis();
//     // // Set the SSR to low if the _dutyCycle time as passed
//     // if(currentTime - _lastTime > _dutyCycle  && currentTime - _lastTime < _cycleTime && _isLow < 1) {
//     //     digitalWrite(_pin, LOW);
//     //     Serial.println("Set ssr to low");
//     //     _isLow = 1;

//     // } 
//     // // Set the SSR to high if the _cycleTime as passed (reset the cycle)
//     // if( currentTime - _lastTime > _cycleTime && currentTime - _lastTime < _cycleTime) {
//     //     _lastTime = millis();
//     //     digitalWrite(_pin, HIGH);
//     //     Serial.println("Set ssr to high");
//     //     _isLow = 0;
//     // }
// }

int SSR::getIntensity() {
    return _i;
}
bool SSR::isHigh() {
    return (_isLow == 0);
}