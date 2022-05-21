#ifndef Multiplexer2_guard
#define Multiplexer2_guard

#define Multiplexer2_h
#include "Arduino.h"
#include "Input.h"
#include "Button.h"
#include "Pot.h"
#include "Piezo.h"
//#include <SerialFlash.h>

class Multiplexer2
{
  public:
    Multiplexer2();
    void setPins(int selectorPin1, int selectorPin2, int selectorPin3, int inputPin1, int inputPin2);
    void createArrayOfInputs(char types [16]);
    bool read(float *, bool *);
    Input* getObject(int index);

  private:
    int _selectorPin1, _selectorPin2, _selectorPin3, _inputPin1, _inputPin2;
    Input * _arrayOfInputs [16];
    int _currentRead;
    long _lastUpdate;
    int _modes [8][3] = { {LOW, LOW, LOW}, {LOW, LOW, HIGH}, {LOW, HIGH, LOW}, {LOW, HIGH, HIGH}, {HIGH, LOW, LOW}, {HIGH, LOW, HIGH}, {HIGH, HIGH, LOW}, {HIGH, HIGH, HIGH} };
    float results [16] = {1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00 };
    bool changes [16] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
};



Multiplexer2::Multiplexer2() {
  _currentRead = 0;
  _lastUpdate = micros();
}

void Multiplexer2::setPins(int selectorPin1, int selectorPin2, int selectorPin3, int inputPin1, int inputPin2) {
  _selectorPin1 = selectorPin1;
  _selectorPin2 = selectorPin2;
  _selectorPin3 = selectorPin3;
  _inputPin1 = inputPin1;
  _inputPin2 = inputPin2;

  pinMode(_selectorPin1, OUTPUT);
  pinMode(_selectorPin2, OUTPUT);
  pinMode(_selectorPin3, OUTPUT);
  pinMode(_inputPin1, INPUT_PULLUP);
  pinMode(_inputPin2, INPUT_PULLUP);
}

void Multiplexer2::createArrayOfInputs(char types[16]) {
  for (int i = 0; i < 16; i++) {
    if (types[i] == 'd') _arrayOfInputs[i] = new Button();
    if (types[i] == 'a') _arrayOfInputs[i] = new Pot();
    if (types[i] == 'p') _arrayOfInputs[i] = new Piezo();
  }
  for (int i = 0; i < 8; i++) {
    _arrayOfInputs[i]->setPin(_inputPin1);
    _arrayOfInputs[i + 8]->setPin(_inputPin2);
  }
}

bool Multiplexer2::read(float *valuesArray, bool *changedArray) {
  long nowInMicros = micros();
  if (nowInMicros - _lastUpdate > 100) {
    if (_arrayOfInputs[_currentRead]->changed()) {
      changes[_currentRead] = true;
    } else {
      changes[_currentRead] = false;
    }

    if (_arrayOfInputs[_currentRead+8]->changed()) {
      changes[_currentRead+8] = true;
    } else {
      changes[_currentRead+8] = false;
    }

    results[_currentRead] = _arrayOfInputs[_currentRead]->read();
    results[_currentRead+8] = _arrayOfInputs[_currentRead+8]->read();
    
    _currentRead++;
    if (_currentRead == 8) _currentRead = 0;
    digitalWrite(_selectorPin1, _modes[_currentRead][0]);
    digitalWrite(_selectorPin2, _modes[_currentRead][1]);
    digitalWrite(_selectorPin3, _modes[_currentRead][2]);
    _lastUpdate = micros();
    if (_currentRead == 0) {
      for (int i = 0; i < 16; i++)  {
        valuesArray[i] = results[i];
        changedArray[i] = changes[i];
      }
      return true;
    }
  }
  return false;
  
}

Input* Multiplexer2::getObject(int index) {
  return _arrayOfInputs[index];
}


#endif
