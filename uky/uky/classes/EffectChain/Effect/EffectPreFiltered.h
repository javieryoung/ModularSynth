#ifndef Effect_guard
#define Effect_guard

#include "Arduino.h"
class EffectChain;
class EffectPreFiltered : public Effect
{
  public:
    EffectPreFiltered();
    void setLowPass();
    void setHighPass();
    float lowPass, highPass;

  protected:
    AudioFilterStateVariable * lowPassLeft; 
    AudioFilterStateVariable * highPassLeft; 
    AudioFilterStateVariable * lowPassRight; 
    AudioFilterStateVariable * highPassRight; 
    AudioMixer4 * preFilterMixerLeft;
    AudioMixer4 * preFilterMixerRight;

};



void EffectPreFiltered::doMainConnections() {
    // this creates the input amps and connects them to the effect and to the dry/wet mixer. 
    // also creates a pre-filter for the effect

    // this amp is just the input
    this->ampLeft = new AudioAmplifier();
    this->ampLeft->gain(1);

    this->preFilterMixerLeft = new AudioMixer4();
    this->preFilterMixerLeft->gain(0, 0.5);
    this->preFilterMixerLeft->gain(1, 0.5);
    this->preFilterMixerLeft->gain(2, 0);
    this->preFilterMixerLeft->gain(3, 0);

    
    // LOW PASS
    this->lowPassLeft = new AudioFilterStateVariable();
    this->lowPassLeft->resonance(0.7); // no resonance

    AudioConnection * leftInputToLowPass = new AudioConnection(*this->ampLeft, 0, *this->lowPassLeft, 0);
    leftInputToLowPass->connect();
    this->connections.add(leftInputToLowPass);

    AudioConnection * lowPassToMixer = new AudioConnection(*this->lowPassLeft, 0, *this->preFilterMixerLeft, 0);
    lowPassToMixer->connect();
    this->connections.add(lowPassToMixer);
    
    // HIGH PASS
    this->highPassLeft = new AudioFilterStateVariable();
    this->highPassLeft->resonance(0.7); // no resonance

    AudioConnection * leftInputToHighPass = new AudioConnection(*this->ampLeft, 0, *this->highPassLeft, 0);
    leftInputToHighPass->connect();
    this->connections.add(leftInputToHighPass);

    AudioConnection * highPassToMixer = new AudioConnection(*this->highPassLeft, 2, *this->preFilterMixerLeft, 1);
    highPassToMixer->connect();
    this->connections.add(highPassToMixer);


    // connect filter mixer to effect
    AudioConnection * filterMixerToEffect = new AudioConnection(*this->preFilterMixerLeft, 0, *this->effectLeft, 0);
    filterMixerToEffect->connect();
    this->connections.add(filterMixerToEffect);

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
      // this amp is just the input
      this->ampRight = new AudioAmplifier();
      this->ampRight->gain(1);

      this->preFilterMixerRight = new AudioMixer4();
      this->preFilterMixerRight->gain(0, 0.5);
      this->preFilterMixerRight->gain(1, 0.5);
      this->preFilterMixerRight->gain(2, 0);
      this->preFilterMixerRight->gain(3, 0);

      
      // LOW PASS
      this->lowPassRight = new AudioFilterStateVariable();
      this->lowPassRight->resonance(0.7); // no resonance

      AudioConnection * rightInputToLowPass = new AudioConnection(*this->ampRight, 0, *this->lowPassRight, 0);
      rightInputToLowPass->connect();
      this->connections.add(rightInputToLowPass);

      AudioConnection * lowPassToMixer = new AudioConnection(*this->lowPassRight, 0, *this->preFilterMixerRight, 0);
      lowPassToMixer->connect();
      this->connections.add(lowPassToMixer);
      
      // HIGH PASS
      this->highPassRight = new AudioFilterStateVariable();
      this->highPassRight->resonance(0.7); // no resonance

      AudioConnection * rightInputToHighPass = new AudioConnection(*this->ampRight, 0, *this->highPassRight, 0);
      rightInputToHighPass->connect();
      this->connections.add(rightInputToHighPass);

      AudioConnection * highPassToMixer = new AudioConnection(*this->highPassRight, 2, *this->preFilterMixerRight, 1);
      highPassToMixer->connect();
      this->connections.add(highPassToMixer);


      // connect filter mixer to effect
      AudioConnection * filterMixerToEffect = new AudioConnection(*this->preFilterMixerRight, 0, *this->effectRight, 0);
      filterMixerToEffect->connect();
      this->connections.add(filterMixerToEffect);

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

void EffectPreFiltered::setLowPass() {
  this->lowPassLeft->frequency(this->lowPass);
  if (this->stereo) {
    this->lowPassRight->frequency(this->lowPass);
  }
}

void EffectPreFiltered::setHighPass() {
  this->highPassLeft->frequency(this->highPass);
  if (this->stereo) {
    this->highPassRight->frequency(this->highPass);
  }
}


#endif
