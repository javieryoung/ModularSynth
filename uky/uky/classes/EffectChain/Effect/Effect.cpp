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

    
    // conect input to effect
    AudioConnection * leftInput = new AudioConnection(*this->ampLeft, 0, *this->effectLeft, 0);
    leftInput->connect();
    this->connections.add(leftInput);

    this->dryWetLeft = new AudioMixer4();
    this->dryWetLeft->gain(2, 0);
    this->dryWetLeft->gain(3, 0);


    AudioConnection * leftDry = new AudioConnection(*this->ampLeft, 0, *this->dryWetLeft, 0);
    leftDry->connect();
    this->connections.add(leftDry);
    AudioConnection * leftWet = new AudioConnection(*this->effectLeft, 0, *this->dryWetLeft, 1);
    leftWet->connect();
    this->connections.add(leftWet);

    if(this->stereo) {
      this->ampRight = new AudioAmplifier();
      this->ampRight->gain(1);


      AudioConnection * rightInput = new AudioConnection(*this->ampRight, 0, *this->effectRight, 0);
      rightInput->connect();
      this->connections.add(rightInput);

      this->dryWetRight = new AudioMixer4();
      this->dryWetRight->gain(2, 0);
      this->dryWetRight->gain(3, 0);

      AudioConnection * rightDry = new AudioConnection(*this->ampRight, 0, *this->dryWetRight, 0);
      rightDry->connect();
      this->connections.add(rightDry);
      AudioConnection * rightWet = new AudioConnection(*this->effectRight, 0, *this->dryWetRight, 1);
      rightWet->connect();
      this->connections.add(rightWet);
    }
}
String Effect::type() {
  return "Effect?";
}

void Effect::setWet() {
  this->dryWetLeft->gain(0, 1-(this->wet/100));
  this->dryWetLeft->gain(1, (this->wet/100));
  if (this->stereo) {
    this->dryWetRight->gain(0, 1-(this->wet/100));
    this->dryWetRight->gain(1, (this->wet/100));
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
