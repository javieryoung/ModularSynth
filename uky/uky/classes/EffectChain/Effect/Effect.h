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
    
    void setInputLeft(AudioStream * inputLeft);
    void setInputRight(AudioStream * inputRight);
    bool stereo;
    float wet; // 0: dry, 1: wet
    
  protected:
    Screen* screen = NULL;
    AudioStream * inputLeft;
    AudioStream * inputRight;
    AudioMixer4 * dryWetLeft;
    AudioMixer4 * dryWetRight;
    LinkedList<AudioConnection*> connections;

};

Effect::Effect() {
  
}
String Effect::type() {
  return "Effect?";
}

void Effect::setInputLeft(AudioStream * inputLeft) {
  this->inputLeft = inputLeft;
}

void Effect::setInputRight(AudioStream * inputRight) {
  this->inputRight = inputRight;
}



AudioStream * Effect::getAudioStream(String which) {
  if (which == "left") {
    return this->dryWetLeft;
  } else {
    return this->dryWetRight;
  }
}

#endif
