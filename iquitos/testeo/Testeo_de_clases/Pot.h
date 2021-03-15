#ifndef Pot_guard
#define Pot_guard

#include "Arduino.h"
#include "Input.h"
//#include <SerialFlash.h>


class Pot : public Input
{
  public:
    Pot();
    virtual void setPin(int pin);
    virtual float read();
    virtual void setMin(float);
    virtual void setMax(float);
    virtual void setLimits(float,float);
    bool changed();
    
  private:
    float _EMA_a;      //initialization of EMA alpha
    float _EMA_S;        //initialization of EMA S
    int _maxValueAverage;
    float _lastRead;
    float _minValue = 0.00;
    float _maxValue = 1.00;
    float _tolerance = 0.02;
};



Pot::Pot() { }

void Pot::setPin(int pin) {
  _pin = pin;
  _EMA_a = 0.1;      //initialization of EMA alpha
  _EMA_S = 0;          //initialization of EMA S
  _maxValueAverage = 940;
  _lastRead = 0;
  pinMode(pin, INPUT_PULLDOWN);
}

void Pot::setMin(float min) {
  _minValue = min;
}
void Pot::setMax(float max) {
  _maxValue = max;
}
void Pot::setLimits(float min, float max) {
  _minValue = min;
  _maxValue = max;
}

float Pot::read() {
  int sensorValue = analogRead(_pin);
  _EMA_S = (_EMA_a*sensorValue) + ((1-_EMA_a)*_EMA_S);
  if (_EMA_S > _maxValueAverage) _maxValueAverage = _EMA_S;
  float normalized = _EMA_S / (float)_maxValueAverage;
  float toRet = normalized * (_maxValue - _minValue) + _minValue;
  return toRet;
}

bool Pot::changed() {
  float thisRead = read();
  if (
    abs(_lastRead - thisRead) > _maxValue * _tolerance ||  // si vario mas que (tolerance)%
    (thisRead < _maxValue * _tolerance && thisRead != _minValue) || // si esta (tolerance)% cerca del valor minimo (y no es valor minimo)
    (thisRead > _maxValue * (1.0-_tolerance) && thisRead != _maxValue) // si esta (tolerance)% cerca del valor maximo (y no es valor maximo)
    ) {
    _lastRead = thisRead;
    return true;
  }
  return false;
}

#endif
