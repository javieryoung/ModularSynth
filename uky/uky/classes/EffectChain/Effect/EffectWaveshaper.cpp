#ifndef EffectWaveshaper_cpp_guard
#define EffectWaveshaper_cpp_guard

#include "../../../externs.h"

EffectWaveshaper::EffectWaveshaper(EffectChain * effectChain, bool stereo) {
    this->stereo = stereo;
    this->wet = 1;
    this->effectChain = effectChain;
    this->angle = 1;
    this->length = 1;
    this->amplitude = 1;
    this->lowPass = 10000;
    this->highPass = 0;


    this->effectLeft = new AudioEffectWaveshaper();
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

    Input* touchArea = new TouchArea(this->screen, "waveshape", this->touchAreaX, this->touchAreaY, this->touchAreaWidth, this->touchAreaHeight, "WaveShape");
    this->screen->addInput(touchArea);

    this->screen->draw();

    currentScreen = this->screen;
}

void EffectWaveshaper::reloadWaveshape() {
    int length = 257;
    float shape[length] = {};
    for (int i = 0; i < length; i++) {
        float x = (i*1.00)/(length/2) - 1; // va de -1 a 1
        float y = pow(x, 1/3);
        shape[i] = y;
    }
    
    this->effectLeft->shape((float *)shape, length);
    if (this->stereo) this->effectRight->shape((float *)shape, length);
    
    // DIBUJAR WAVESHAPE
    // va desde (40, 100) a (297, 250), o sea de 257x150
    int width = this->touchAreaWidth;
    int height = this->touchAreaHeight; // promediamos cada punto en 3 para poder dibujar barritas
    int startX = this->touchAreaX;
    int startY = this->touchAreaY;
    int bars = 100;
    float barWidth = width/bars;
    float valuesPerBar = length / bars;
    tft.fillRect(startX, startY, width, height, BLACK);
    for (float x = 0; x < length; x+=valuesPerBar) {
      float avgY = 0;
      for (int x1 = x; x1 < valuesPerBar; x1++) avgY += shape[x1];
      avgY = avgY / valuesPerBar;

      float y = avgY * (height/2);
      if (y > 0) 
        tft.fillRect(x+startX, startY + (height/2) - y, barWidth, y, PRIMARY_0); // relleno de la barrita
      else
        tft.fillRect(x+startX, startY + height/2, barWidth, -y, PRIMARY_0); // relleno de la barrita
      tft.fillRect(x+startX, startY + (height/2) - y, barWidth, 2, PRIMARY); // tope de la barrita
    }
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
  if (command == "waveshape") {
    int x = param / 10000;
    int y  = param - (x * 10000);
    Serial.print("X: ");
    Serial.print(x);
    Serial.print("Y: ");
    Serial.println(y);

  }
}

#endif
