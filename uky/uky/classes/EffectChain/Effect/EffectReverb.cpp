#ifndef EffectReverb_cpp_guard
#define EffectReverb_cpp_guard


extern Screen * currentScreen;

EffectReverb::EffectReverb(EffectChain * effectChain, bool stereo) {
    this->effectChain = effectChain;
    this->roomSize = 0.5;
    this->damping = 0.5;
    this->lowPass = 0;
    this->highPass = 0;
    this->stereo = stereo;
    this->wet = 100;
    

    this->effectLeft = new AudioEffectFreeverb();

    this->dryWetLeft = new AudioMixer4();
    this->dryWetLeft->gain(2, 0);
    this->dryWetLeft->gain(3, 0);

    AudioConnection * leftDry = new AudioConnection(*this->inputLeft, 0, *this->dryWetLeft, 0);
    leftDry->connect();
    this->connections.add(leftDry);
    
    AudioConnection * leftWet = new AudioConnection(*this->effectLeft, 0, *this->dryWetLeft, 1);
    leftWet->connect();
    this->connections.add(leftWet);
    
    if(this->stereo) {

      this->effectRight = new AudioEffectFreeverb();

      this->dryWetRight = new AudioMixer4();
      this->dryWetRight->gain(2, 0);
      this->dryWetRight->gain(3, 0);

      AudioConnection * rightDry = new AudioConnection(*this->inputRight, 0, *this->dryWetRight, 0);
      rightDry->connect();
      this->connections.add(rightDry);

      AudioConnection * rightWet = new AudioConnection(*this->effectRight, 0, *this->dryWetRight, 1);
      rightWet->connect();
      this->connections.add(rightWet);

    }

    this->setDamping();
    this->setRoomSize();
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

void EffectReverb::setWet() {
  this->dryWetLeft->gain(0, 1-(this->wet/100));
  this->dryWetLeft->gain(1, (this->wet/100));
  if (this->stereo) {
    this->dryWetRight->gain(0, 1-(this->wet/100));
    this->dryWetRight->gain(1, (this->wet/100));
  }
}

void EffectReverb::event(String command, float param){
  if (command == "clicked" && param == 0) { // click sobre izquierdo
      this->destroyScreen(); // solo quiero borrar la screen, el efecto me interesa quedarmelo
      this->effectChain->chainListScreen();
  }
  if (command == "highPass") {
    this->highPass = param;
    
  }
  if (command == "lowPass") {
    this->lowPass = param;
  }
  if (command == "damping") {
    this->damping = param;
    this->setDamping();
  }
  if (command == "roomSize") {
    this->roomSize = param;
    this->setRoomSize();
  }
  if (command == "wet") {
    this->wet = param;
    this->setWet();
  }
}

#endif
