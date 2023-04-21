#ifndef EffectChain_cpp_guard
#define EffectChain_cpp_guard

EffectChain::EffectChain(bool stereo) {
    this->screen = NULL;
    this->stereo = stereo;
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
    for(int i = 0; i < this->connectionsRight.size(); i++){
        this->connectionsRight.get(i)->disconnect();
        delete this->connectionsRight.get(i);
    }
    this->connectionsRight.clear();
    for(int i = 0; i < this->connectionsLeft.size(); i++){
        this->connectionsLeft.get(i)->disconnect();
        delete this->connectionsLeft.get(i);
    }
    this->connectionsLeft.clear();
}

void EffectChain::connect() {
    if (this->effects.size() > 0){
        // the first one splits channel 0(right) and channel 1(left);
        
        AudioStream * currentAudioStreamRight = this->inputRight;
        AudioStream * currentAudioStreamLeft = this->inputLeft;

        for(int i = 0; i < this->effects.size(); i++){
            this->effects.get(i)->setInputLeft(currentAudioStreamLeft);
            if(this->stereo) this->effects.get(i)->setInputRight(currentAudioStreamRight);

            if(this->stereo) AudioStream * nextAudioStreamRight = this->effects.get(i)->getAudioStream("right");
            AudioStream * nextAudioStreamLeft = this->effects.get(i)->getAudioStream("left");
            

            if(this->stereo) {
                AudioConnection * r = new AudioConnection(*currentAudioStreamRight, *nextAudioStreamRight);
                r->connect();
                this->connectionsRight.add(r); // right
            }

            AudioConnection * l = new AudioConnection(*currentAudioStreamLeft, *nextAudioStreamLeft);
            l->connect();
            this->connectionsLeft.add(l); // left
            
            if(this->stereo) currentAudioStreamRight = nextAudioStreamRight;
            currentAudioStreamLeft = nextAudioStreamLeft;
        }
        
        if(this->stereo) {
            AudioConnection * rFinal = new AudioConnection(*currentAudioStreamRight, *this->outputRight);
            rFinal->connect();
            this->connectionsRight.add(rFinal); // right
        }

        AudioConnection * lFinal = new AudioConnection(*currentAudioStreamLeft, *this->outputLeft);
        lFinal->connect();
        this->connectionsLeft.add(lFinal); // left
    } else {
        if(this->stereo) {
            AudioConnection * rFinal = new AudioConnection(*this->inputRight, *this->outputRight);
            rFinal->connect();
            this->connectionsRight.add(rFinal); // right
        }

        AudioConnection * lFinal = new AudioConnection(*this->inputLeft, *this->outputLeft);
        lFinal->connect();
        this->connectionsLeft.add(lFinal); // left
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
                    Effect * e = new EffectReverb(this, this->stereo);
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