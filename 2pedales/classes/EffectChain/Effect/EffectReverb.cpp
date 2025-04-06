#ifndef EffectReverb_cpp_guard
#define EffectReverb_cpp_guard

EffectReverb::EffectReverb(EffectChain * effectChain, bool stereo) {
    this->stereo = stereo;
    this->wet = 0.6;
    this->effectChain = effectChain;
    this->size = 0.1;
    this->lowpass = 0.5;
    this->hidamp = 0;
    this->lodamp = 0;

    // ATENCION
    // este efecto ya es stereo, por lo que no precisamos crear un effectRight. Usamos solo el left.
    // create effect
    this->effectLeft = new AudioEffectPlateReverb(); 
    
    this->doMainConnections();

    AudioConnection * filteredToEffectLeft = new AudioConnection(*this->ampLeft, 0, *this->effectLeft, 0);
    filteredToEffectLeft->connect();
    this->connections.add(filteredToEffectLeft);
    if (!this->stereo) { // the effect has to have two inputs si o si
      AudioConnection * filteredToEffectLeftButRight = new AudioConnection(*this->ampLeft, 0, *this->effectLeft, 1);
      filteredToEffectLeftButRight->connect();
      this->connections.add(filteredToEffectLeftButRight);
    }
    
    AudioConnection * leftWet = new AudioConnection(*this->effectLeft, 0, *this->dryWetLeft, 1);
    leftWet->connect();
    this->connections.add(leftWet);

    if(this->stereo) {
      AudioConnection * filteredToEffectRight = new AudioConnection(*this->inputRight, 0, *this->effectLeft, 1);
      filteredToEffectRight->connect();
      this->connections.add(filteredToEffectRight);
    
      AudioConnection * rightWet = new AudioConnection(*this->effectLeft , 0, *this->dryWetRight , 1);
      rightWet->connect();
      this->connections.add(rightWet);
      
    }
    
    this->setSize();
    this->setLowPass();
    this->setLodamp();
    this->setHidamp();
    this->setDiffusion();
    this->setWet();
    
}

String EffectReverb::type() { return "Reverb"; }


void EffectReverb::setSize() {
  this->effectLeft->size(this->size/100);
}

void EffectReverb::setLowPass() {
  this->effectLeft->lowpass(this->lowpass/100);
}

void EffectReverb::setLodamp() {
  this->effectLeft->lodamp(this->lodamp/100);
}

void EffectReverb::setHidamp() {
  this->effectLeft->hidamp(this->hidamp/100);
}

void EffectReverb::setDiffusion() {
  this->effectLeft->diffusion(this->diffusion/100);
}

void EffectReverb::event(String command, float param){
}

#endif
