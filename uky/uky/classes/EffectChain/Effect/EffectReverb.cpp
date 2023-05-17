#ifndef EffectReverb_cpp_guard
#define EffectReverb_cpp_guard

#include "../../../externs.h"

EffectReverb::EffectReverb(EffectChain * effectChain, bool stereo) {
    this->stereo = stereo;
    this->wet = 1;
    this->effectChain = effectChain;
    this->size = 0.5;
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

EffectReverb::~EffectReverb() {
  this->destroyScreen();
  for(int i = 0; i < this->connections.size(); i++){
      this->connections.get(i)->disconnect();
      delete this->connections.get(i);
  }
  this->connections.clear();
}

String EffectReverb::type() { return "Reverb"; }

void EffectReverb::destroyScreen() {
    if (this->screen != NULL)
        delete this->screen;
    this->screen = NULL;
    clear();
}



    void setSize();
    void sethidamp();
    void setLodamp();
    void setHidamp();
    void setDiffusion();

void EffectReverb::mainScreen() {
    this->screen = new Screen(this);

    Input* k = new TwoKnobs(this->screen, 10, 40, 40, 40, 15);
    k->setUpKnob("left", "size", "Size", 0, 100, this->size);
    k->setUpKnob("right", "lowpass", "LowPass", 0, 100, this->lowpass*100);
    this->screen->addInput(k);

    Input* k2 = new TwoKnobs(this->screen, 180, 40, 40, 40, 15);
    k2->setUpKnob("left", "lodamp", "LoDamp", 0, 100, this->lodamp*100);      // start with no filter
    k2->setUpKnob("right", "hidamp", "HiDamp", 0, 100, this->hidamp*100);  // start with no filter
    this->screen->addInput(k2);

    Input* k3 = new TwoKnobs(this->screen, 10, 150, 40, 40, 15);
    k3->setUpKnob("left", "diffusion", "Diffusion", 0, 100, 0);
    k3->setUpKnob("right", "wet", "Dry/Wet", 0, 100, this->wet*100);
    this->screen->addInput(k3);

    this->screen->draw();

    currentScreen = this->screen;
}

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
  if (command == "clicked" && param == 0) { // click sobre izquierdo
      this->destroyScreen(); // solo quiero borrar la screen, el efecto me interesa quedarmelo
      this->effectChain->mainScreen();
  }
  if (command == "lowpass") {
    this->lowpass = param/100;
    this->setLowPass();
  }
  if (command == "size") {
    this->size = param/100;
    this->setSize();
  }
  if (command == "lodamp") {
    this->lodamp = param/100;
    this->setLodamp();
  }
  if (command == "hidamp") {
    this->hidamp = param/100;
    this->setHidamp();
  }
  if (command == "diffusion") {
    this->diffusion = param/100;
    this->setDiffusion();
  }
  if (command == "wet") {
    this->wet = param/100;
    this->setWet();
  }
}

#endif
