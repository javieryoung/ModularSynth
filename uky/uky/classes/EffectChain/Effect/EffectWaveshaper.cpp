#ifndef EffectWaveshaper_cpp_guard
#define EffectWaveshaper_cpp_guard

#include "../../../externs.h"

AudioEffectWaveshaper waveshaper;


EffectWaveshaper::EffectWaveshaper(EffectChain * effectChain, bool stereo) {
    this->stereo = stereo;
    this->wet = 1;
    this->effectChain = effectChain;
    // Default: sinwave
    this->angle = 1;
    this->length = 1;
    this->amplitude = 1;
    this->lowPass = 10000;
    this->highPass = 0;

    this->effectLeft = &waveshaper; 
    if(this->stereo) this->effectRight = new AudioEffectWaveshaper(); 
    
    this->doMainConnections();

    
    AudioConnection * leftInputToDelayMixer = new AudioConnection(*this->filteredLeft, 0, * this->effectLeft, 0);
    leftInputToDelayMixer->connect();
    this->connections.add(leftInputToDelayMixer);
    
    AudioConnection * leftWet = new AudioConnection(*this->effectLeft, 0, *this->dryWetLeft, 1);
    leftWet->connect();
    this->connections.add(leftWet);

    if(this->stereo) {
      AudioConnection * rightInputToDelayMixer = new AudioConnection(*this->filteredRight, 0, * this->effectRight, 0);
      rightInputToDelayMixer->connect();
      this->connections.add(rightInputToDelayMixer);
    
      AudioConnection * rightWet = new AudioConnection(*this->effectRight , 0, *this->dryWetRight , 1);
      rightWet->connect();
      this->connections.add(rightWet);
      
    }
    this->setWet();
    this->setLowPass();
    this->setHighPass();

    this->reloadWaveshape();
}

EffectWaveshaper::~EffectWaveshaper() {
  this->destroyScreen();
  for(int i = 0; i < this->connections.size(); i++){
      this->connections.get(i)->disconnect();
      delete this->connections.get(i);
  }
  this->connections.clear();
}

String EffectWaveshaper::type() { return "WaveShaper"; }

void EffectWaveshaper::destroyScreen() {
    if (this->screen != NULL)
        delete this->screen;
    this->screen = NULL;
    clear();
}


void EffectWaveshaper::mainScreen() {
    this->screen = new Screen(this);

    Input* k = new TwoKnobs(this->screen, 10, 40, 40, 40, 15);
    k->setUpKnob("left", "angle", "Angle", 1, 3, this->angle);
    k->setUpKnob("right", "amplitude", "Amplitude", 1, 3, this->amplitude);
    this->screen->addInput(k);

    Input* k3 = new TwoKnobs(this->screen, 180, 40, 40, 40, 15);
    k3->setUpKnob("left", "length", "Length", 0, 10, 0);
    k3->setUpKnob("right", "wet", "Dry/Wet", 0, 100, this->wet*100);
    this->screen->addInput(k3);

    this->screen->draw();

    currentScreen = this->screen;
}

void EffectWaveshaper::reloadWaveshape() {
    Serial.println("A");
    int length = 257;
    float shape[length] = {};
    Serial.println("B");
    for (int i = 0; i < length; i++) {
        float x = (i*1.00)/(length/2) - 1; // va de -1 a 1
        // f(x) = sin(ax PI) bx + cx
        Serial.print("f(");
        Serial.print(x);
        Serial.print(") = ");
        float y = pow(x, 1/this->angle);
        Serial.println(y);
        
        shape[i] = y;
    }
    Serial.println("C");
    
    this->effectLeft->shape((float *)shape, length);
    if (this->stereo) this->effectRight->shape((float *)shape, length);
    
    Serial.println("D");
    // DIBUJAR WAVESHAPE
    // va desde (40, 100) a (297, 250), o sea de 257x150
    int height = 80;
    tft.fillRect(40, 120, length, height, BLACK);
    Serial.println("F");
    for (int x = 0; x < length; x++) {
        float y = shape[x] * (height/2);
        tft.drawPixel(x + 40, 120 + (height/2) - y, PRIMARY);
    }
    Serial.println("G");
    
}

void EffectWaveshaper::event(String command, float param){
  if (command == "clicked" && param == 0) { // click sobre izquierdo
      this->destroyScreen(); // solo quiero borrar la screen, el efecto me interesa quedarmelo
      this->effectChain->mainScreen();
  }
  if (command == "angle") {
    this->angle = param;
    this->reloadWaveshape();
  }
  if (command == "length") {
    this->length = param;
    this->reloadWaveshape();
  }
  if (command == "amplitude") {
    this->amplitude = param;
    this->reloadWaveshape();
  }
  if (command == "wet") {
    this->wet = param/100;
    this->setWet();
  }
}

#endif
