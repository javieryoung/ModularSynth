#ifndef Multiplexer2_guard
#define Multiplexer2_guard

#define Multiplexer2_h
#include "Arduino.h"
#include "Input.h"
#include "Button.h"
#include "Pot.h"
//#include <SerialFlash.h>

class Multiplexer2
{
  public:
    Multiplexer2();
    void setPins(int selectorPin1, int selectorPin2, int selectorPin3, int inputPin1, int inputPin2);
    void createArrayOfInputs(char types [16]);
    void read(float *, bool *);
    Input* getObject(int index);

  private:
    int _selectorPin1, _selectorPin2, _selectorPin3, _inputPin1, _inputPin2;
    Input * _arrayOfInputs [16];

};



Multiplexer2::Multiplexer2() { }

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
  }
  for (int i = 0; i < 8; i++) {
    _arrayOfInputs[i]->setPin(_inputPin1);
    _arrayOfInputs[i + 8]->setPin(_inputPin2);
  }
}

void Multiplexer2::read(float *valuesArray, bool *changedArray) {

  int modes [8][3] = { {LOW, LOW, LOW}, {LOW, LOW, HIGH}, {LOW, HIGH, LOW}, {LOW, HIGH, HIGH}, {HIGH, LOW, LOW}, {HIGH, LOW, HIGH}, {HIGH, HIGH, LOW}, {HIGH, HIGH, HIGH} };
  for (int i = 0; i < 8; i++) {
    digitalWrite(_selectorPin1, modes[i][0]);
    digitalWrite(_selectorPin2, modes[i][1]);
    digitalWrite(_selectorPin3, modes[i][2]);
    delayMicroseconds(50);

    if (_arrayOfInputs[i]->changed()) {
      changedArray[i] = true;
    } else {
      changedArray[i] = false;
    }

    if (_arrayOfInputs[i+8]->changed()) {
      changedArray[i+8] = true;
    } else {
      changedArray[i+8] = false;
    }

    valuesArray[i] = _arrayOfInputs[i]->read();
    valuesArray[i+8] = _arrayOfInputs[i+8]->read();
  }
}

Input* Multiplexer2::getObject(int index) {
  return _arrayOfInputs[index];
}


#endif
