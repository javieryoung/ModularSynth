#ifndef LFO_guard
#define LFO_guard


#define LFO_h
#include "Arduino.h"
#include "Pot.h"
#include <SerialFlash.h>
#include "math.h"

//   >
//   <


class LFO
{
  public:
    LFO();
    void setFrequencyPin(int pin);
    float update();
    int type; // 0: sin     1: lineal    2: arcsin    3: square     4: lineal-instant-drop     5: lineal-instant-up
    
  private:
    int _pin;
    float _currentValue;
    long _lastUpdate;
    float _frequency;
    float _normalizedCurrentValue;
    int _sign;
    Pot pot;
};


LFO::LFO() {}

void LFO::setFrequencyPin(int pin) {
    type = 2;
    _pin = pin;
    pot = Pot();
    pot.setPin(_pin);
    pot.minValue = 0.0;
    pot.maxValue = 0.9;
    _sign=1;
    _currentValue = 0;
    _normalizedCurrentValue = 0;
    _lastUpdate = 0;
}

float LFO::update() {
    _frequency = (1.0 - pot.read()) * 1000 * 1000;
    long timePassed = (micros() - _lastUpdate);
    if (timePassed > 2000) {
      float absDifference = (timePassed / _frequency) * 1000 * 1000;
      if (_sign == 1) {
          if (absDifference + _normalizedCurrentValue > 1 * 1000 * 1000) {
              absDifference = (1 * 1000 * 1000) - (_normalizedCurrentValue + absDifference);
              _sign = -1;
              if (type == 4 || type == 6) {
                    _sign = 1;
                    _normalizedCurrentValue = 0;
                }
          }
      }
      if (_sign == -1) {
          if (_normalizedCurrentValue - absDifference < 0) {
              absDifference = (_normalizedCurrentValue - absDifference) * (-1);
              _sign = 1;
              if (type == 5 || type == 7) {
                    _sign = -1;
                    _normalizedCurrentValue = 1 * 1000 * 1000;
                }
          }
      }

      
      _normalizedCurrentValue = _normalizedCurrentValue + (_sign * absDifference);
      _currentValue = _normalizedCurrentValue / (1000000.00);
      
      if (_currentValue > 1.0) 
          _currentValue = 1.0;
      if (_currentValue < 0.0)
          _currentValue = 0.0;
       

      if (type == 0) {
        float sinRes = cos(_currentValue * 2 * PI);
        _currentValue = (sinRes + 1.0) / 2.0;
      }
      if (type == 3) {
        if (_currentValue < 0.5)
          _currentValue = 0;
        else
          _currentValue = 1;
      }
      if (type == 2) {
        float arcsin = asin(_currentValue*2 - 1);
        _currentValue = ((PI / 2) + arcsin) / PI;
      }


      _lastUpdate = micros();
      
    }
    return _currentValue;
}


#endif
