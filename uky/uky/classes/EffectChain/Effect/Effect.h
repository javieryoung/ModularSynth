#ifndef Effect_guard
#define Effect_guard

#include "Arduino.h"

class Effect : public Screenable
{
  public:
    Effect();
    virtual void edit();
    virtual String type();
    
  protected:
    ;


};

Effect::Effect() {
  
}
String Effect::type() {
  return "Effect?";
}


#endif
