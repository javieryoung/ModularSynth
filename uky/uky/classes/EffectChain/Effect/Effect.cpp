#ifndef EffectCPP_guard
#define EffectCPP_guard

#include "Arduino.h"


Effect::Effect() {
}

void Effect::doMainConnections() {
    // this creates the input amps and connects them to the effect and to the dry/wet mixer.  
    
    

    // this amp is just the input
    this->ampLeft = new AudioAmplifier();
    this->ampLeft->gain(1);

    

    this->dryWetLeft = new AudioMixer4();
    this->dryWetLeft->gain(2, 0);
    this->dryWetLeft->gain(3, 0);


    AudioConnection * leftDry = new AudioConnection(*this->ampLeft, 0, *this->dryWetLeft, 0);
    leftDry->connect();
    this->connections.add(leftDry);
    if(this->stereo) {
      this->ampRight = new AudioAmplifier();
      this->ampRight->gain(1);


      this->dryWetRight = new AudioMixer4();
      this->dryWetRight->gain(2, 0);
      this->dryWetRight->gain(3, 0);

      AudioConnection * rightDry = new AudioConnection(*this->ampRight, 0, *this->dryWetRight, 0);
      rightDry->connect();
      this->connections.add(rightDry);
    }
}
String Effect::type() {
  return "Effect?";
}

void Effect::setWet() {
  this->dryWetLeft->gain(0, 1-(this->wet));
  this->dryWetLeft->gain(1, (this->wet));
  if (this->stereo) {
    this->dryWetRight->gain(0, 1-(this->wet));
    this->dryWetRight->gain(1, (this->wet));
  }
}


AudioStream * Effect::getInput(String which) {
  if (which == "left") {
    return this->ampLeft;
  } else {
    return this->ampRight;
  }
}


AudioStream * Effect::getOutput(String which) {
  if (which == "left") {
    return this->dryWetLeft;
  } else {
    return this->dryWetRight;
  }
}

#endif
