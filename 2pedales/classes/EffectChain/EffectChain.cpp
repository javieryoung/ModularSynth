#ifndef EffectChain_cpp_guard
#define EffectChain_cpp_guard

EffectChain::EffectChain(bool stereo) {
    this->stereo = stereo;
}
EffectChain::~EffectChain() {
    // TODO
}

void EffectChain::setInputLeft(AudioStream *i) {
    this->inputLeft = i;
}
void EffectChain::setInputRight(AudioStream *i) {
    this->inputRight = i;
}
void EffectChain::setOutputLeft(AudioStream *o) {
    this->outputLeft = o;
}
void EffectChain::setOutputRight(AudioStream *o) {
    this->outputRight = o;
}

void EffectChain::destroyConnections() {
    for(int i = 0; i < this->connections.size(); i++){
        this->connections.get(i)->disconnect();
        delete this->connections.get(i);
    }
    this->connections.clear();
    for(int i = 0; i < this->connections.size(); i++){
        this->connections.get(i)->disconnect();
        delete this->connections.get(i);
    }
    this->connections.clear();
}

void EffectChain::addEffect(Effect *&e) {
  this->effects.add(e);
  this->destroyConnections();
  this->connect();
}

void EffectChain::connect() {
    // the first one splits channel 0(right) and channel 1(left);
    
    AudioStream * currentAudioStreamRight = this->inputRight;
    AudioStream * currentAudioStreamLeft = this->inputLeft;

    for(int i = 0; i < this->effects.size(); i++){

        AudioConnection * currentToInputL = new AudioConnection(*currentAudioStreamLeft, 0, *this->effects.get(i)->getInput("left"), 0);
        currentToInputL->connect();
        this->connections.add(currentToInputL); // left
        currentAudioStreamLeft = this->effects.get(i)->getOutput("left");

        if (this->stereo) {
            AudioConnection * currentToInputR = new AudioConnection(*currentAudioStreamRight, 0, *this->effects.get(i)->getInput("right"), 0);
            currentToInputR->connect();
            this->connections.add(currentToInputR); // right
            currentAudioStreamLeft = this->effects.get(i)->getOutput("right");
        }
        
    }
    
    AudioConnection * lFinal = new AudioConnection(*currentAudioStreamLeft, 0, *this->outputLeft, 0);
    lFinal->connect();
    this->connections.add(lFinal); // left

    if(this->stereo) {
        AudioConnection * rFinal = new AudioConnection(*currentAudioStreamRight, 0, *this->outputRight, 0);
        rFinal->connect();
        this->connections.add(rFinal); // right
    }
    
}


void EffectChain::event(String command, float param){
}

#endif