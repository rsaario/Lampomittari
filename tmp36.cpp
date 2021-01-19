#include "Arduino.h"
#include "tmp36.h"
#include <Smoothed.h>

tmp36::tmp36(int pin) {
  _pin = pin; 
   _tempAveg.begin(SMOOTHED_AVERAGE, 100);
}


float tmp36::getTemp() {
  int reading = analogRead(_pin);
    float voltage = reading * (5000 / 1024.0);
    float temperature = (voltage - 500) / 10;
    _tempAveg.add(temperature);
    _smoothedTempAvg = _tempAveg.get();
   return _smoothedTempAvg;
}
