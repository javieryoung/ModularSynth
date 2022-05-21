#ifndef Piezo_guard
#define Piezo_guard

#include "Arduino.h"
#include "Input.h"
//#include <SerialFlash.h>


class Piezo : public Input
{
  public:
    Piezo();
    virtual void setPin(int pin);
    virtual float read();
    virtual void setMin(float);
    virtual void setMax(float);
    virtual void setLimits(float,float);
    bool changed();
    
  private:
    float _minValue = 0;
    float _maxValue = 100;

    long _startedReading = 0;
    bool _reading = false;
    int _maxRead = 0;
};



Piezo::Piezo() { }

void Piezo::setPin(int pin) {
  _pin = pin;
  pinMode(pin, INPUT_PULLDOWN);
}

void Piezo::setMin(float min) {
  _minValue = min;
}
void Piezo::setMax(float max) {
  _maxValue = max;
}
void Piezo::setLimits(float min, float max) {
  _minValue = min;
  _maxValue = max;
}

float Piezo::read() {
  int sensorValue = analogRead(_pin);
  
  if (_reading) {
    if (sensorValue > _maxRead) {
        _maxRead = sensorValue;
    }
    if (micros() - _startedReading > 5000) { // read for 10000 us or 10ms
    // the fastest human can hit a snare every 49 ms so we are tranqui
        _reading = false;
        return _maxRead;
    }
  } else {
    if (sensorValue > 50) { // treshold = 50
        _startedReading = micros();
        _maxRead = sensorValue;
        _reading = true;
    }
  }
  return 0;
}

bool Piezo::changed() {
    return true;
}

#endif
