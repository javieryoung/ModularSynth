#ifndef EffectWaveshaper_cpp_guard
#define EffectWaveshaper_cpp_guard

#include "../../../externs.h"

EffectWaveshaper::EffectWaveshaper(EffectChain * effectChain, bool stereo) {
    this->stereo = stereo;
    this->wet = 1;
    this->effectChain = effectChain;
    // Default: sinwave
    this->angle = 0;
    this->length = 0.5;

    this->effectLeft = new AudioEffectWaveshaper(); 
    if(this->stereo) this->effectRight = new AudioEffectWaveshaper(); 
    
    this->doMainConnections();

    
    AudioConnection * filteredToEffectLeft = new AudioConnection(*this->ampLeft, 0, *this->effectLeft, 0);
    filteredToEffectLeft->connect();
    this->connections.add(filteredToEffectLeft);
    
    AudioConnection * leftWet = new AudioConnection(*this->effectLeft, 0, *this->dryWetLeft, 1);
    leftWet->connect();
    this->connections.add(leftWet);

    if(this->stereo) {
      AudioConnection * filteredToEffectRight = new AudioConnection(*this->inputRight, 0, *this->effectRight, 1);
      filteredToEffectRight->connect();
      this->connections.add(filteredToEffectRight);
    
      AudioConnection * rightWet = new AudioConnection(*this->effectRight , 0, *this->dryWetRight , 1);
      rightWet->connect();
      this->connections.add(rightWet);
      
    }
    this->setWet();
    
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
    k->setUpKnob("left", "angle", "Angle", -3, 3, this->angle);
    k->setUpKnob("right", "idk", "Idk", 0, 3, 0);
    this->screen->addInput(k);

    Input* k3 = new TwoKnobs(this->screen, 180, 40, 40, 40, 15);
    k3->setUpKnob("left", "length", "Length", -15, 15, 0);
    k3->setUpKnob("right", "wet", "Dry/Wet", 0, 100, this->wet*100);
    this->screen->addInput(k3);

    this->screen->draw();

    currentScreen = this->screen;
}

void EffectWaveshaper::reloadWaveshape() {
    Serial.println("A");
    float shape[257] = {};
    float minValue = 10000;
    float maxValue = -10000;
    Serial.println("B");
    for (int i = 0; i < 257; i++) {
        float x = (i*1.00)/128 - 1; // va de -1 a 1
        // f(x) = sin(ax PI) + cx
        shape[i] = sin(this->length * x * PI) + this->angle * x;
        if (shape[i] > maxValue) maxValue = shape[i];
        if (shape[i] < minValue) minValue = shape[i];
        Serial.println(shape[i]);
        
    }
    // NORMALIZE
    for (int i = 0; i < 257; i++) {
        if (minValue < 0 && -minValue > maxValue)
            shape[i] = shape[i]/(-minValue);
        else
            shape[i] = shape[i]/maxValue;
    }       
    Serial.println("C");
    
    this->effectLeft->shape((float *)shape, 257);
    if (this->stereo) this->effectRight->shape((float *)shape, 257);
    
    Serial.println("D");
    // DIBUJAR WAVESHAPE

    // va desde (40, 100) a (297, 250), o sea de 257x150
    float range = maxValue - minValue;
    int height = 150;
    tft.fillRect(40, 100, 257, height, BLACK);
    Serial.println("F");
    for (int x = 0; x < 257; x++) {
        float y = (shape[x] / range) * height;
        tft.drawPixel(x + 40, 100 + (height/2) - y, PRIMARY);
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
  if (command == "wet") {
    this->wet = param/100;
    this->setWet();
  }
}

#endif
