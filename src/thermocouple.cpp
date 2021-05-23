#include "thermocouple.hpp"

Thermocouple::Thermocouple(int pin,max31856_thermocoupletype_t type) {
    // Initialize the thermocouple with the right pin and config
    _tc = new Adafruit_MAX31856(pin);
    if (!_tc->begin()) {
        Serial.println("Could not initialize thermocouple.");
        while (1) delay(10);
    }
    _tc->setThermocoupleType(type);
    _tc->setConversionMode(MAX31856_ONESHOT_NOWAIT);
    _lastTime = millis();
}

Thermocouple::~Thermocouple() {
  delete _tc;
}

float Thermocouple::getTemperature() {
    return _temperature;
}

void Thermocouple::run() {
  if(_isWaiting) {
    // The documnetation of the library had a polling delay of 500ms before calling the conversionComplete method
    if(millis() - _lastTime < POLL_DELAY) {
      return;
    }
    // Check if the conversion is done and read the temperature
    if(_tc->conversionComplete()) {
      _temperature = _tc->readThermocoupleTemperature();
      _isWaiting = 0;
    }
    return;
   }
  // If not waiting, call a temperature read
  _tc->triggerOneShot();
  _isWaiting = 1;
  _lastTime = millis();
}