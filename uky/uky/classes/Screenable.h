#ifndef Screenable_guard
#define Screenable_guard

#include "Arduino.h"
class Screenable
{
  public:
    Screenable();
    ~Screenable();
    virtual void event(String command, float param);
};

Screenable::Screenable() {
}

Screenable::~Screenable() {
}

#endif
