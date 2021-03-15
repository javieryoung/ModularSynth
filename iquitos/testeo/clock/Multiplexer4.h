#ifndef Multiplexer4_guard
#define Multiplexer4_guard

#define Multiplexer4_h
#include "Arduino.h"
#include "Input.h"
#include "Button.h"
#include "Pot.h"
//#include <SerialFlash.h>

class Multiplexer4
{
  public:
    Multiplexer4();
    void setPins(int selectorPin1, int selectorPin2, int selectorPin3, int inputPin1, int inputPin2, int inputPin3, int inputPin4);
    void createArrayOfInputs(char types [32]);
    bool read(float *, bool *);
    Input* getObject(int index);

  private:
    int _selectorPin1, _selectorPin2, _selectorPin3, _inputPin1, _inputPin2, _inputPin3, _inputPin4;
    Input * _arrayOfInputs [32];
    int _currentRead;
    long _lastUpdate;
    int _modes [8][3] = { {LOW, LOW, LOW}, {LOW, LOW, HIGH}, {LOW, HIGH, LOW}, {LOW, HIGH, HIGH}, {HIGH, LOW, LOW}, {HIGH, LOW, HIGH}, {HIGH, HIGH, LOW}, {HIGH, HIGH, HIGH} };
    float results [32] = {1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00 };
    bool changes [32] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
};



Multiplexer4::Multiplexer4() {
  _currentRead = 0;
  _lastUpdate = micros();
}

void Multiplexer4::setPins(int selectorPin1, int selectorPin2, int selectorPin3, int inputPin1, int inputPin2, int inputPin3, int inputPin4) {
  _selectorPin1 = selectorPin1;
  _selectorPin2 = selectorPin2;
  _selectorPin3 = selectorPin3;
  _inputPin1 = inputPin1;
  _inputPin2 = inputPin2;
  _inputPin3 = inputPin3;
  _inputPin4 = inputPin4;

  pinMode(_selectorPin1, OUTPUT);
  pinMode(_selectorPin2, OUTPUT);
  pinMode(_selectorPin3, OUTPUT);
  pinMode(_inputPin1, INPUT_PULLUP);
  pinMode(_inputPin2, INPUT_PULLUP);
  pinMode(_inputPin3, INPUT_PULLUP);
  pinMode(_inputPin4, INPUT_PULLUP);
}

void Multiplexer4::createArrayOfInputs(char types[32]) {
  for (int i = 0; i < 32; i++) {
    if (types[i] == 'd') _arrayOfInputs[i] = new Button();
    if (types[i] == 'a') _arrayOfInputs[i] = new Pot();
  }
  for (int i = 0; i < 8; i++) {
    _arrayOfInputs[i]->setPin(_inputPin1);
    _arrayOfInputs[i + 8]->setPin(_inputPin2);
    _arrayOfInputs[i + 16]->setPin(_inputPin3);
    _arrayOfInputs[i + 24]->setPin(_inputPin4);
  }
}

bool Multiplexer4::read(float *valuesArray, bool *changedArray) {
  long nowInMicros = micros();
  if (nowInMicros - _lastUpdate > 50) {

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
    if (_arrayOfInputs[_currentRead+16]->changed()) {
      changes[_currentRead+16] = true;
    } else {
      changes[_currentRead+16] = false;
    }

    if (_arrayOfInputs[_currentRead+24]->changed()) {
      changes[_currentRead+24] = true;
    } else {
      changes[_currentRead+24] = false;
    }

    results[_currentRead] = _arrayOfInputs[_currentRead]->read();
    results[_currentRead+8] = _arrayOfInputs[_currentRead+8]->read();
    results[_currentRead+16] = _arrayOfInputs[_currentRead+16]->read();
    results[_currentRead+24] = _arrayOfInputs[_currentRead+24]->read();
    
    _currentRead++;
    if (_currentRead == 8) _currentRead = 0;
    digitalWrite(_selectorPin1, _modes[_currentRead][0]);
    digitalWrite(_selectorPin2, _modes[_currentRead][1]);
    digitalWrite(_selectorPin3, _modes[_currentRead][2]);
    _lastUpdate = micros();
    if (_currentRead == 0) {
      for (int i = 0; i < 32; i++)  {
        valuesArray[i] = results[i];
        changedArray[i] = changes[i];
      }
      return true;
    }
  }
  return false;
  
}

Input* Multiplexer4::getObject(int index) {
  return _arrayOfInputs[index];
}


#endif
