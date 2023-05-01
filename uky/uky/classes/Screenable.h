#ifndef Screenable_guard
#define Screenable_guard

#include "Arduino.h"
class Screenable
{
  public:
    Screenable();
    ~Screenable();
    virtual void event(String command, float param);
    virtual void mainScreen()=0;
};

Screenable::Screenable() {
}

Screenable::~Screenable() {
}

#endif
