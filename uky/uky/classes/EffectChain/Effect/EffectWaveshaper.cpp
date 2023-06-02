#ifndef EffectWaveshaper_cpp_guard
#define EffectWaveshaper_cpp_guard

#include "../../../externs.h"

AudioEffectWaveshaper waveshaper;
EffectWaveshaper::EffectWaveshaper(EffectChain * effectChain, bool stereo) {
    this->stereo = stereo;
    this->wet = 1;
    this->effectChain = effectChain;
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

    // INITIAL WAVESHAPE
    for (int i = 0; i < this->shapeLength; i++) {
        float x = (i*1.00)/(this->shapeLength/2) - 1; // va de -1 a 1
        float y = (2*x)/(1+abs(x));
        this->shape[i] = y;
        // shape[i] = x;
    }


    this->setWet();
    this->setLowPass();
    this->setHighPass();
    this->setWaveshape();
    this->drawWaveshape();
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
  k->setUpKnob("left", "depth", "Depth", 1, 3, this->depth);
  k->setUpKnob("right", "wet", "Dry/Wet", 0, 100, this->wet*100);
  this->screen->addInput(k);

  Input* touchArea = new TouchArea(this->screen, "waveshape", this->touchAreaX, this->touchAreaY, this->touchAreaWidth, this->touchAreaHeight, "WaveShape");
  this->screen->addInput(touchArea);

  this->screen->draw();

  currentScreen = this->screen;
    
}

void EffectWaveshaper::setWaveshape() {
  this->effectLeft->shape((float *)this->shape, this->shapeLength);
  if (this->stereo) this->effectRight->shape((float *)this->shape, this->shapeLength);
}
void EffectWaveshaper::drawWaveshape() {
  // DIBUJAR WAVESHAPE
  // va desde (40, 100) a (297, 250), o sea de 257x150
  int width = this->touchAreaWidth;
  int height = this->touchAreaHeight; // promediamos cada punto en 3 para poder dibujar barritas
  int startX = this->touchAreaX;
  int startY = this->touchAreaY;
  int bars = this->bars;
  float barWidth = (width * 1.0)/(bars * 1.0);
  float valuesPerBar = (this->shapeLength * 1.0) / (bars * 1.0);
  tft.fillRect(startX, startY, width, height, BLACK);
  for (float x = 0; x < this->shapeLength; x+=valuesPerBar) {
    /*
    float avgY = 0;
    for (int x1 = x; x1 < valuesPerBar; x1++) avgY += shape[x1];
    avgY = avgY / valuesPerBar;
    */
    float avgY = this->shape[int(x)];

    float y = avgY * (height/2);
    tft.fillRect((x/valuesPerBar)*barWidth+startX, startY + (height/2), barWidth, -y, PRIMARY_0);     // relleno de la barrita
    tft.fillRect((x/valuesPerBar)*barWidth+startX, startY + (height/2) - y, barWidth, 3, PRIMARY);    // tope de la barrita
  }
}

void EffectWaveshaper::redrawBar(int bar) {
  int width = this->touchAreaWidth;
  int height = this->touchAreaHeight; // promediamos cada punto en 3 para poder dibujar barritas
  int startX = this->touchAreaX;
  int startY = this->touchAreaY;
  int bars = this->bars;


  float barWidth = (width * 1.0)/(bars * 1.0);
  float valuesPerBar = (this->shapeLength * 1.0) / (bars * 1.0);

  float avgY = this->shape[int(bar * valuesPerBar)];
  float y = avgY * (height/2);
  
  tft.fillRect(bar*barWidth+startX, startY, barWidth, height, BLACK); // vaciar barrita
  tft.fillRect(bar*barWidth+startX, startY + (height/2), barWidth, -y, PRIMARY_0); // relleno de la barrita
  tft.fillRect(bar*barWidth+startX, startY + (height/2) - y, barWidth, 3, PRIMARY); // tope de la barrita
}

void EffectWaveshaper::event(String command, float param){
  if (command == "clicked" && param == 0) { // click sobre izquierdo
    this->destroyScreen(); // solo quiero borrar la screen, el efecto me interesa quedarmelo
    this->effectChain->mainScreen();
  }
  if (command == "wet") {
    this->wet = param/100;
    this->setWet();
  }
  if (command == "waveshape") {
    int x = param / 100000;
    int y  = param - (x * 100000);
    // encontrando la barrita clickeada:
    float barWidth = this->touchAreaWidth/this->bars;
    int barTouched = x / barWidth;
    float newValue = (this->touchAreaHeight/2.0 - y*1.0) / (this->touchAreaHeight/2.0);

    float valuesPerBar = (this->shapeLength * 1.0) / (bars * 1.0);
    for (float i = barTouched*valuesPerBar; i < barTouched*valuesPerBar + valuesPerBar; i++) {
      this->shape[int(i)] = newValue;
    }
    
    this->setWaveshape();
    this->redrawBar(barTouched);
  }
}

#endif
