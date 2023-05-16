#ifndef EffectDelay_cpp_guard
#define EffectDelay_cpp_guard

#include "../../../externs.h"

EffectDelay::EffectDelay(EffectChain * effectChain, bool stereo) {
    this->stereo = stereo;
    this->wet = 100;
    this->effectChain = effectChain;
    this->feedback = 0.5;
    this->delayTime = 200;
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
  this->destroyScreen();
  for(int i = 0; i < this->connections.size(); i++){
      this->connections.get(i)->disconnect();
      delete this->connections.get(i);
  }
  this->connections.clear();
}

String EffectDelay::type() { return "Delay"; }

void EffectDelay::destroyScreen() {
    if (this->screen != NULL)
        delete this->screen;
    this->screen = NULL;
    clear();
}

void EffectDelay::mainScreen() {
    this->screen = new Screen(this);

    Input* k = new TwoKnobs(this->screen, 10, 40, 40, 40, 15);
    k->setUpKnob("left", "feedback", "Feedback", 0, 100, this->feedback*100);
    k->setUpKnob("right", "delayTime", "DelayTime", 0, 500, this->delayTime);
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

void EffectDelay::setFeedback() {
  this->effectLeft->gain(1, this->feedback);  
  
  if (this->stereo) {
    this->effectRight->gain(0, 1-(this->feedback));
    this->effectRight->gain(1, this->feedback);  
  }
}

void EffectDelay::setDelayTime() {
  this->delayLeft->delay(0, this->delayTime);
  if (this->stereo) this->delayRight->delay(0, this->delayTime);
}


void EffectDelay::event(String command, float param){
  if (command == "clicked" && param == 0) { // click sobre izquierdo
      this->destroyScreen(); // solo quiero borrar la screen, el efecto me interesa quedarmelo
      this->effectChain->mainScreen();
  }
  if (command == "highPass") {
    this->highPass = param;
    this->setHighPass();
  }
  if (command == "lowPass") {
    this->lowPass = param;
    this->setLowPass();
  }
  if (command == "feedback") {
    this->feedback = param/100;
    this->setFeedback();
  }
  if (command == "delayTime") {
    this->delayTime = param;
    this->setDelayTime();
  }
  if (command == "wet") {
    this->wet = param;
    this->setWet();
  }
}

#endif
