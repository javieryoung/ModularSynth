#ifndef Led_guard
#define Led_guard

#include "Arduino.h"
#include "Input.h"
class Led
{
  public:
    Led();
    void setPin(int pin);
    void on(int);
    void blink(int, unsigned long);
    void off();
    void reload();
    
  private:
    int _pin;
    unsigned long _started;
    unsigned long _shouldLast;
    int _state;
    bool _blinking;
};

Led::Led() {
  _started = 0;
  _state = 0;
  _blinking = false;
}

void Led::setPin(int pin) {
    _pin = pin;
    pinMode(_pin, OUTPUT);
    _blinking = false;
}

void Led::on(int intensity) {
  analogWrite(_pin,intensity);
  _state = 1;
}

void Led::blink(int intensity, unsigned long time) {
  this->on(intensity);
  _started = micros();
  _shouldLast = time;
  _blinking = true;
}

void Led::off() {
  analogWrite(_pin,0);
  _state = 0;
}

void Led::reload() {
    if (_state == 1 && _blinking) {
        if (micros() - _started > _shouldLast) {
            this->off();
        }
    }
}

#endif
