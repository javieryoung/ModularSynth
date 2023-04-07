#ifndef EffectChain_cpp_guard
#define EffectChain_cpp_guard

EffectChain::EffectChain() {
    this->screen = NULL;
}

void EffectChain::destroyScreen() {
    if (this->screen != NULL)
        delete this->screen;
    this->screen = NULL;
    clear();
}

void EffectChain::chainList() {
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


void EffectChain::effectList() {
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
    for(int i = 0; i < this->connectionsRight.size(); i++){
        delete this->connectionsRight.get(i);
    }
    this->connectionsRight.clear();
    for(int i = 0; i < this->connectionsLeft.size(); i++){
        delete this->connectionsLeft.get(i);
    }
    this->connectionsLeft.clear();
}

void EffectChain::connect() {
    if ( false && this->effects.size() > 0){
        // the first one splits channel 0(right) and channel 1(left);
        AudioStream * currentAudioStreamRight = this->inputRight;
        AudioStream * currentAudioStreamLeft = this->inputLeft;

        for(int i = 0; i < this->effects.size(); i++){
            AudioStream * nextAudioStreamRight = this->effects.get(i)->getAudioStream("right");
            AudioStream * nextAudioStreamLeft = this->effects.get(i)->getAudioStream("left");

            this->connectionsRight.add((new AudioConnection(*currentAudioStreamRight, 0, *nextAudioStreamRight, 0))); // right
            this->connectionsLeft.add((new AudioConnection(*currentAudioStreamLeft, 0, *nextAudioStreamLeft, 0))); // left

            currentAudioStreamRight = nextAudioStreamRight;
            currentAudioStreamLeft = nextAudioStreamLeft;
        }


        this->connectionsRight.add((new AudioConnection(*currentAudioStreamRight, 0, *this->outputRight, 0))); // right
        this->connectionsLeft.add((new AudioConnection(*currentAudioStreamLeft, 0, *this->outputLeft, 0))); // left
    } else {
        this->connectionsRight.add((new AudioConnection(*this->inputRight, 0, *this->outputRight, 0))); // right
        this->connectionsLeft.add((new AudioConnection(*this->inputLeft, 0, *this->outputLeft, 0))); // left
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
                this->effectList();
            } else {
                this->editEffect(param);
            }
        }
    } else {
        if (this->showing == "effectList") {
            if (command == "selected") {
                if (param == 0) {
                    // REVERB
                    Effect * e = new EffectReverb(this);
                    this->addEffect(e);
                    this->editEffect(this->effects.size()-1);
                }
                if (param == 1) {
                    // DELAY

                }
            }
        }
    }
}

#endif