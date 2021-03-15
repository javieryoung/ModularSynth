#ifndef Input_guard
#define Input_guard

#include "Arduino.h"
//#include <SerialFlash.h>


class Input
{
  public:
    Input();
    virtual  float read();
    virtual void setPin(int);
    virtual bool changed();
    virtual void setLimits(float,float);

  protected:
    int _pin;
    
};

Input::Input() { }
float Input::read() { return 1.0; }
void Input::setPin(int _pin) {  }
void Input::setLimits(float m, float n) {  }


#endif
