#ifndef Effect_guard
#define Effect_guard

#include "Arduino.h"

class Effect : public Screenable
{
  public:
    Effect();
    virtual void edit();
    virtual String type();
    virtual AudioStream * getAudioStream(String which);
    
  protected:


};

Effect::Effect() {
  
}
String Effect::type() {
  return "Effect?";
}

AudioStream * Effect::getAudioStream(String which) {
  return NULL;
}

#endif
