#ifndef EffectPreFiltered_guard
#define EffectPreFiltered_guard

class EffectPreFiltered : public Effect
{
  public:
    EffectPreFiltered();
    void setLowPass();
    void setHighPass();
    float lowPass, highPass;
    void doMainConnections();


    AudioFilterStateVariable * lowPassLeft; 
    AudioFilterStateVariable * highPassLeft; 
    AudioFilterStateVariable * lowPassRight; 
    AudioFilterStateVariable * highPassRight; 
    AudioAmplifier * filteredLeft;
    AudioAmplifier * filteredRight;

};

EffectPreFiltered::EffectPreFiltered() {

}


void EffectPreFiltered::doMainConnections() {
    // this creates the input amps and connects them to the effect and to the dry/wet mixer. 
    // also creates a pre-filter for the effect

    // this amp is just the input
    this->ampLeft = new AudioAmplifier();
    this->ampLeft->gain(1);
    
    this->filteredLeft = new AudioAmplifier();
    this->filteredLeft->gain(1);

    // LOW PASS
    this->lowPassLeft = new AudioFilterStateVariable();
    this->lowPassLeft->resonance(0.7); // no resonance

    AudioConnection * leftInputToLowPass = new AudioConnection(*this->ampLeft, 0, *this->lowPassLeft, 0);
    leftInputToLowPass->connect();
    this->connections.add(leftInputToLowPass);
    
    // HIGH PASS
    this->highPassLeft = new AudioFilterStateVariable();
    this->lowPassLeft->resonance(0.7); // no resonance

    AudioConnection * lowPassToHighPass = new AudioConnection(*this->lowPassLeft, 0, *this->highPassLeft, 0);
    lowPassToHighPass->connect();
    this->connections.add(lowPassToHighPass);

    AudioConnection * highPassToEffect = new AudioConnection(*this->highPassLeft, 2, *this->filteredLeft, 0);
    highPassToEffect->connect();
    this->connections.add(highPassToEffect);

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
      
      this->filteredRight = new AudioAmplifier();
      this->filteredRight->gain(1);
      
      // LOW PASS
      this->lowPassRight = new AudioFilterStateVariable();
      this->lowPassRight->resonance(0.7); // no resonance

      AudioConnection * rightInputToLowPass = new AudioConnection(*this->ampRight, 0, *this->lowPassRight, 0);
      rightInputToLowPass->connect();
      this->connections.add(rightInputToLowPass);
      
      // HIGH PASS
      this->highPassRight = new AudioFilterStateVariable();
      this->highPassRight->resonance(0.7); // no resonance

      AudioConnection * lowPassRighToHighPass = new AudioConnection(*this->lowPassRight, 0, *this->highPassRight, 0);
      lowPassRighToHighPass->connect();
      this->connections.add(lowPassRighToHighPass);

      AudioConnection * highPassRightToEffect = new AudioConnection(*this->highPassRight, 2, *this->filteredRight, 1);
      highPassRightToEffect->connect();
      this->connections.add(highPassRightToEffect);


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
