#ifndef tmp36_h
#define tmp36_h

#include "Arduino.h"
#include <Smoothed.h>

class tmp36
{
  public:
    tmp36(int pin);
    float getTemp();
    
  private:
    float _pin;
    Smoothed <float> _tempAveg;
    float _smoothedTempAvg;
    float _lastSmoothedTempAvg;   
};

#endif
