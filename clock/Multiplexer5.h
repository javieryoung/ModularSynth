#ifndef Multiplexer5_guard
#define Multiplexer5_guard

#define Multiplexer5_h
#include "Arduino.h"

#include "Button.h"
#include "Pot.h"
#include "Led.h"
//#include <SerialFlash.h>

class Multiplexer5
{
  public:
    Multiplexer5();
    void start();
    bool read(float *, bool *, float *, bool *);
    Led* getLed(int index);

  private:
    int _selectorPin1, _selectorPin2, _selectorPin3, _inputPin1, _inputPin2, _inputPin3, _inputPin4;
    Led * _leds [16];
    Pot * _pots [16];
    Button * _buttons [8];
    int _currentRead;
    long _lastUpdate;
    int _modes [8][3] = { {LOW, LOW, LOW}, {LOW, LOW, HIGH}, {LOW, HIGH, LOW}, {LOW, HIGH, HIGH}, {HIGH, LOW, LOW}, {HIGH, LOW, HIGH}, {HIGH, HIGH, LOW}, {HIGH, HIGH, HIGH} };
    
    float _resultsPots [16] = {1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00};
    bool _changedPots [16] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
    float _resultsButtons [16] = {1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00};
    bool _changedButtons [16] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };

};



Multiplexer5::Multiplexer5() {
  _currentRead = 0;
  _lastUpdate = micros();
}

void Multiplexer5::start() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(17, INPUT_PULLDOWN); // leds 0-7
  pinMode(21, INPUT_PULLDOWN); // leds 8-16
  pinMode(16, INPUT_PULLDOWN); // pot 0-7
  pinMode(20, INPUT_PULLDOWN); // pot 8-16
  pinMode(5, INPUT_PULLUP); // buttons
  for (int i = 0; i < 8; i++) {
    _leds[i] = new Led();
    _leds[i]->setPin(17);
    _buttons[i] = new Button();
    _buttons[i]->setPin(5);
    _pots[i] = new Pot();
    _pots[i]->setPin(16);
  }
  
  for (int i = 8; i < 16; i++) {
    _leds[i] = new Led();
    _leds[i]->setPin(21);
    _pots[i] = new Pot();
    _pots[i]->setPin(20);
  }

  pinMode(13,OUTPUT);
}

bool Multiplexer5::read(float *valuesPots, bool *changedPots, float *valuesButtons, bool *changedButtons) {
  long nowInMicros = micros();
  if (nowInMicros - _lastUpdate > 50) {

    _leds[_currentRead]->reload();
    _leds[_currentRead+8]->reload();

    _changedPots[_currentRead] = _pots[_currentRead]->changed();
    _changedPots[_currentRead+8] = _pots[_currentRead+8]->changed();

    _changedButtons[_currentRead] = _buttons[_currentRead]->changed();
    _changedButtons[_currentRead+8] = _buttons[_currentRead+8]->changed();
    
    _resultsPots[_currentRead] = _pots[_currentRead]->read();
    _resultsPots[_currentRead+8] = _pots[_currentRead+8]->read();

    _resultsButtons[_currentRead] = _buttons[_currentRead]->read();
    
    _currentRead++;
    if (_currentRead == 8) _currentRead = 0;
    digitalWrite(_selectorPin1, _modes[_currentRead][0]);
    digitalWrite(_selectorPin2, _modes[_currentRead][1]);
    digitalWrite(_selectorPin3, _modes[_currentRead][2]);

    _lastUpdate = micros();

    if (_currentRead == 0) {
      for (int i = 0; i < 16; i++) {
        valuesPots[i] = _resultsPots[i];
        changedPots[i] = _changedPots[i];

        valuesButtons[i] = _resultsButtons[i];
        changedButtons[i] = _changedButtons[i];
      }
      return true;
    }
  }
  return false;
  
}

Led* Multiplexer5::getLed(int index) {
  return _leds[index];
}




#endif
