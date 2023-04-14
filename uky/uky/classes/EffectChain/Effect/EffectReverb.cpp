#ifndef EffectReverb_cpp_guard
#define EffectReverb_cpp_guard


extern Screen * currentScreen;

EffectReverb::EffectReverb(EffectChain * effectChain) {
    this->effectChain = effectChain;
    this->roomSize = 0;
    this->damping = 0;
    this->lowPass = 0;
    this->highPass = 0;
    
    this->effectLeft = new AudioEffectFreeverb();
    this->effectLeft->roomsize(0);
    this->effectLeft->damping(0);

    delay(10);

    this->effectRight = new AudioEffectFreeverb();
    this->effectRight->roomsize(0.5);
    this->effectRight->damping(0.5);
    
}

EffectReverb::~EffectReverb() {
  delete this->screen;
}
String EffectReverb::type() { return "Reverb"; }

void EffectReverb::destroyScreen() {
    clear();
    delete this->screen;
}

void EffectReverb::edit() {
    this->screen = new Screen(this);

    Input* k = new TwoKnobs(this->screen, 10, 40, 40, 40, 15);
    k->setUpKnob("left", "roomSize", "Room", 0, 100, this->roomSize);
    k->setUpKnob("right", "damping", "Damp", 0, 100, this->damping);
    this->screen->addInput(k);

    Input* k2 = new TwoKnobs(this->screen, 180, 40, 40, 40, 15);
    k2->setUpKnob("left", "highPass", "HP", 0, 100, this->highPass);
    k2->setUpKnob("right", "lowPass", "LP", 0, 100, this->lowPass);
    this->screen->addInput(k2);

    this->screen->draw();

    currentScreen = this->screen;
}


void EffectReverb::event(String command, float param){
  Serial.print(command);
  Serial.println(param);
  if (command == "clicked" && param == 0) { // click sobre izquierdo
      this->destroyScreen(); // solo quiero borrar la screen, el efecto me interesa quedarmelo
      this->effectChain->chainList();
  }
  if (command == "highPass") {
    this->highPass = param;
    
  }
  if (command == "lowPass") {
    this->lowPass = param;
  }
  if (command == "damping") {
    this->damping = param;
    this->effectLeft->damping(param/100.0);
  }
  if (command == "roomSize") {
    this->roomSize = param;
    this->effectLeft->roomsize(param/100.0);
  }
}

AudioStream * EffectReverb::getAudioStream(String which) {
  if (which == "left") {
    return this->effectLeft;
  } else {
    return this->effectRight;
  }
}

#endif
