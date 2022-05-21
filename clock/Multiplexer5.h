#ifndef Multiplexer5_guard
#define Multiplexer5_guard

#define Multiplexer5_h
#include "Arduino.h"

#include "Button.h"
#include "Pot.h"
//#include <SerialFlash.h>

class Multiplexer5
{
  public:
    Multiplexer5();
    void start();
    bool read(float *, bool *, float *, bool *, int);
    int currentReadToLed1(int);
    int currentReadToLed2(int);

  private:
    int _inputPin1, _inputPin2, _inputPin3, _inputPin4;
    Pot * _pots [16];
    Button * _buttons [8];
    int _currentRead = 0;
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
  pinMode(17, OUTPUT); // leds 0-7
  pinMode(21, OUTPUT); // leds 8-16
  

  pinMode(16, INPUT_PULLDOWN); // pot 0-7
  pinMode(20, INPUT_PULLDOWN); // pot 8-16
  pinMode(5, INPUT_PULLUP); // buttons
  for (int i = 0; i < 8; i++) {
    _buttons[i] = new Button();
    _buttons[i]->setPin(5);
    _pots[i] = new Pot();
    _pots[i]->setPin(16);
    _pots[i]->setLimits(0,255);
  }
  
  for (int i = 8; i < 16; i++) {
    _pots[i] = new Pot();
    _pots[i]->setPin(20);
    _pots[i]->setLimits(0,255);
  }

  pinMode(13,OUTPUT);
}

long ledChanged = 0;
int lastCounter = 0;

bool Multiplexer5::read(float *valuesPots, bool *changedPots, float *valuesButtons, bool *changedButtons, int counter) {
  long nowInMicros = micros();
  

  if (lastCounter != counter) {
    ledChanged = millis();
    lastCounter = counter;
  }
  if (millis() - ledChanged < 200) {
    if (counter >= 8) {
      if (currentReadToLed2(_currentRead) == counter-8) {
        digitalWrite(21,HIGH);
      } else {
        digitalWrite(21,LOW);
      }
      digitalWrite(17,LOW);
    } else {
      if (currentReadToLed1(_currentRead) == counter) {
        digitalWrite(17,HIGH);
      } else {
        digitalWrite(17,LOW);
      }
      digitalWrite(21,LOW);
    }
  } else {
    digitalWrite(17,LOW);
    digitalWrite(21,LOW);
  }

  if (nowInMicros - _lastUpdate > 50) {
    _lastUpdate = micros();

    
    
    _changedPots[_currentRead] = _pots[_currentRead]->changed();
    _changedPots[_currentRead+8] = _pots[_currentRead+8]->changed();

    _changedButtons[_currentRead] = _buttons[_currentRead]->changed();
    
    _resultsPots[_currentRead] = _pots[_currentRead]->read();
    _resultsPots[_currentRead+8] = _pots[_currentRead+8]->read();

    _resultsButtons[_currentRead] = _buttons[_currentRead]->read();
    
    _currentRead++;
    if (_currentRead == 8) _currentRead = 0;
    digitalWrite(2, _modes[_currentRead][0]);
    digitalWrite(3, _modes[_currentRead][1]);
    digitalWrite(4, _modes[_currentRead][2]);

    if (_currentRead == 0) {
      for (int i = 0; i < 16; i++) {
        valuesPots[i] = _resultsPots[i];
        changedPots[i] = _changedPots[i];

        if (i < 8) {
          valuesButtons[i] = _resultsButtons[i];
          changedButtons[i] = _changedButtons[i];
        }
      }
      return true;
    }
  }
  return false;
  
}


int Multiplexer5::currentReadToLed1(int currentRead) {
  if (currentRead == 0) return 0;
  if (currentRead == 1) return 5;
  if (currentRead == 2) return 1;
  if (currentRead == 3) return 6;
  if (currentRead == 4) return 2;
  if (currentRead == 5) return 3;
  if (currentRead == 6) return 7;
  if (currentRead == 7) return 4;
  return 0;
}
int Multiplexer5::currentReadToLed2(int currentRead) {
  if (currentRead == 0) return 3;
  if (currentRead == 1) return 4;
  if (currentRead == 2) return 6;
  if (currentRead == 3) return 5;
  if (currentRead == 4) return 7;
  if (currentRead == 5) return 1;
  if (currentRead == 6) return 2;
  if (currentRead == 7) return 0;
  return 0;
}

#endif
