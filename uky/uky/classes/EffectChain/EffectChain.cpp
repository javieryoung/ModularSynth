#ifndef EffectChain_cpp_guard
#define EffectChain_cpp_guard

EffectChain::EffectChain(bool stereo) {
    this->screen = NULL;
    this->stereo = stereo;
}
EffectChain::~EffectChain() {
    // TODO
}


void EffectChain::destroyScreen() {
    if (this->screen != NULL)
        delete this->screen;
    this->screen = NULL;
    clear();
}

void EffectChain::chainListScreen() {
    destroyScreen();
    this->screen = new Screen(this);
    Input* m = new Menu(this->screen);
    
    for(int i = 0; i < this->effects.size(); i++){
        m->addOption(this->effects.get(i)->type());
    }
    m->addOption("+ effect");

    
    this->screen->addInput(m);
    this->screen->draw();
    this->showing = "chainList";
    currentScreen = this->screen;
}


void EffectChain::effectListScreen() {
    destroyScreen();
    this->screen = new Screen(this);
    Input* m = new Menu(this->screen);
    for (String element : availableEffects)  {
        m->addOption(element);
    }
    this->screen->addInput(m);
    this->screen->draw();
    this->showing = "effectList";
    currentScreen = this->screen;
}


void EffectChain::addEffect(Effect *&e) {
    this->effects.add(e);
    this->destroyConnections();
    this->connect();
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



void EffectChain::editEffect(int position) {
    this->destroyScreen();
    this->effects.get(position)->edit();
}


void EffectChain::event(String command, float param){
    Serial.println(param);
    if (this->showing == "chainList") {
        if (command == "selected") {
            if (param == this->effects.size()) {
                this->effectListScreen();
            } else {
                this->editEffect(param);
            }
        }
    } else {
        if (this->showing == "effectList") {
            if (command == "selected") {
                if (param == 0) {
                    // REVERB
                    Serial.println("A");
                    Effect * e = new EffectReverb(this, this->stereo);
                    Serial.println("B");
                    this->addEffect(e);
                    Serial.println("C");
                    this->editEffect(this->effects.size()-1);
                    Serial.println("D");
                }
                if (param == 1) {
                    // DELAY

                }
            }
        }
    }
}

#endif