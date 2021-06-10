#ifndef Button_guard
#define Button_guard

#include "Arduino.h"
class Button
{
  public:
    Button();
    void setPin(int pin);
    float read();
    bool changed();
    
  private:
    int _pin;
    float _lastRead;
};

Button::Button() {
  _lastRead = 0.0;
}

void Button::setPin(int pin) {
    _pin = pin;
    pinMode(_pin, INPUT_PULLUP);
}

float Button::read() {
  if (digitalRead(_pin) == LOW)
    return.0;
  else
    return 1.0;
}

bool Button::changed() {
  float thisRead = read();
  if (thisRead != _lastRead) {
    _lastRead = thisRead;
    return true;
  }
  return false;
}

#endif
