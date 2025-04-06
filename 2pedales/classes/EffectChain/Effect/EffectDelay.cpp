#ifndef EffectDelay_cpp_guard
#define EffectDelay_cpp_guard


EffectDelay::EffectDelay(EffectChain * effectChain, bool stereo) {
    this->stereo = stereo;
    this->wet = 0.3;
    this->effectChain = effectChain;
    this->feedback = 0.5;
    this->delayTime = 10;
    this->lowPass = 10000;
    this->highPass = 0;

    this->effectLeft = new AudioMixer4(); // delay mixer
    if (this->stereo) this->effectRight = new AudioMixer4(); // delay mixer
    this->doMainConnections();
    
    // create effect
    this->delayLeft = new AudioEffectDelay();
    for (int i = 1; i <= 7; i ++) { this->delayLeft->disable(i); }
    this->effectLeft->gain(0,1);
    this->effectLeft->gain(2,0);
    this->effectLeft->gain(3,0);

    AudioConnection * leftInputToDelayMixer = new AudioConnection(*this->filteredLeft, 0, * this->effectLeft, 0);
    leftInputToDelayMixer->connect();
    this->connections.add(leftInputToDelayMixer);

    AudioConnection * leftDelayMixerToDelay = new AudioConnection(* this->effectLeft, 0, *this->delayLeft, 0);
    leftDelayMixerToDelay->connect();
    this->connections.add(leftDelayMixerToDelay);

    AudioConnection * leftDelayToDelayMixer = new AudioConnection(*this->delayLeft, 0, * this->effectLeft, 1);
    leftDelayToDelayMixer->connect();
    this->connections.add(leftDelayToDelayMixer);

    AudioConnection * leftEffectToDryWet = new AudioConnection(*this->effectLeft, 0, * this->dryWetLeft, 1);
    leftEffectToDryWet->connect();
    this->connections.add(leftEffectToDryWet);
    
    if(this->stereo) {
      this->delayRight = new AudioEffectDelay();
      for (int i = 1; i <= 7; i ++) this->delayRight->disable(i);
      this->effectRight->gain(2,0);
      this->effectRight->gain(3,0);

      AudioConnection * rightInputToDelayMixer = new AudioConnection(*this->filteredRight, 0, * this->effectRight, 0);
      rightInputToDelayMixer->connect();
      this->connections.add(rightInputToDelayMixer);

      AudioConnection * rightDelayMixerToDelay = new AudioConnection(* this->effectRight, 0, *this->delayRight, 0);
      rightDelayMixerToDelay->connect();
      this->connections.add(rightDelayMixerToDelay);

      AudioConnection * rightDelayToDelayMixer = new AudioConnection(*this->delayRight, 0, * this->effectRight, 1);
      rightDelayToDelayMixer->connect();
      this->connections.add(rightDelayToDelayMixer);

      AudioConnection * rightEffectToDryWet = new AudioConnection(*this->effectRight, 0, * this->dryWetRight, 0);
      rightEffectToDryWet->connect();
      this->connections.add(rightEffectToDryWet);

      
    }
    this->setFeedback();
    this->setDelayTime();
    this->setWet();
    this->setLowPass();
    this->setHighPass();
}

EffectDelay::~EffectDelay() {
  for(int i = 0; i < this->connections.size(); i++){
      this->connections.get(i)->disconnect();
      delete this->connections.get(i);
  }
  this->connections.clear();
}

String EffectDelay::type() { return "Delay"; }


void EffectDelay::setFeedback() {
  this->effectLeft->gain(1.0, this->feedback);  
  
  if (this->stereo) {
    this->effectRight->gain(0, 1.0-(this->feedback));
    this->effectRight->gain(1, this->feedback);  
  }
}

void EffectDelay::setDelayTime() {
  this->delayLeft->delay(0, this->delayTime);
  if (this->stereo) this->delayRight->delay(0, this->delayTime);
}


void EffectDelay::event(String command, float param){
}

#endif
