#ifndef EffectReverb_cpp_guard
#define EffectReverb_cpp_guard

#include "../../../externs.h"

EffectReverb::EffectReverb(EffectChain * effectChain, bool stereo) {
    this->stereo = stereo;
    this->wet = 100;
    this->effectChain = effectChain;
    this->roomSize = 0.5;
    this->damping = 0.5;
    this->lowPass = 10000;
    this->highPass = 0;

    // create effect
    this->effectLeft = new AudioEffectFreeverb();
    
    if(this->stereo) {
      this->effectRight = new AudioEffectFreeverb();
    }

    this->doMainConnections();

    
    AudioConnection * filteredToEffectLeft = new AudioConnection(*this->filteredLeft, 0, *this->effectLeft, 0);
    filteredToEffectLeft->connect();
    this->connections.add(filteredToEffectLeft);
    
    AudioConnection * leftWet = new AudioConnection(*this->effectLeft, 0, *this->dryWetLeft, 1);
    leftWet->connect();
    this->connections.add(leftWet);

    if(this->stereo) {
      AudioConnection * filteredToEffectRight = new AudioConnection(*this->filteredRight, 2, *this->effectRight, 0);
      filteredToEffectRight->connect();
      this->connections.add(filteredToEffectRight);
    
      AudioConnection * rightWet = new AudioConnection(*this->effectRight , 0, *this->dryWetRight , 1);
      rightWet->connect();
      this->connections.add(rightWet);
      
      
    }
    
    this->setDamping();
    this->setRoomSize();
    this->setWet();
    this->setLowPass();
    this->setHighPass();
    
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

void EffectReverb::mainScreen() {
    this->screen = new Screen(this);

    Input* k = new TwoKnobs(this->screen, 10, 40, 40, 40, 15);
    k->setUpKnob("left", "roomSize", "Room", 0, 100, this->roomSize);
    k->setUpKnob("right", "damping", "Damp", 0, 100, this->damping);
    this->screen->addInput(k);

    Input* k2 = new TwoKnobs(this->screen, 180, 40, 40, 40, 15);
    k2->setUpKnob("left", "highPass", "HP", 20, 10000, 0);      // start with no filter
    k2->setUpKnob("right", "lowPass", "LP", 20, 10000, 10000);  // start with no filter
    this->screen->addInput(k2);

    Input* k3 = new TwoKnobs(this->screen, 10, 150, 40, 40, 15);
    k3->setUpKnob("left", "wet", "Dry/Wet", 0, 100, this->wet);
    k3->setUpKnob("right", "idk", "Idk", 0, 100, 0);
    this->screen->addInput(k3);

    this->screen->draw();

    currentScreen = this->screen;
}

void EffectReverb::setDamping() {
  this->effectLeft->damping(this->damping/100);
  if (this->stereo) this->effectRight->damping(this->damping/100);
}

void EffectReverb::setRoomSize() {
  this->effectLeft->roomsize(this->roomSize/100);
  if (this->stereo) this->effectRight->roomsize(this->roomSize/100);
}


void EffectReverb::event(String command, float param){
  if (command == "clicked" && param == 0) { // click sobre izquierdo
      this->destroyScreen(); // solo quiero borrar la screen, el efecto me interesa quedarmelo
      this->effectChain->mainScreen();
  }
  if (command == "damping") {
    this->damping = param;
    this->setDamping();
  }
  if (command == "roomSize") {
    this->roomSize = param;
    this->setRoomSize();
  }
  if (command == "highPass") {
    this->highPass = param;
    this->setHighPass();
  }
  if (command == "lowPass") {
    this->lowPass = param;
    this->setLowPass();
  }
  if (command == "wet") {
    this->wet = param;
    this->setWet();
  }
}

#endif
