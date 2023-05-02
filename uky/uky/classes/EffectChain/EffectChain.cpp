#ifndef EffectChain_cpp_guard
#define EffectChain_cpp_guard

EffectChain::EffectChain(bool stereo, Screenable * parent) {
    this->screen = NULL;
    this->stereo = stereo;
    this->parent = parent;
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

void EffectChain::mainScreen() {
    destroyScreen();
    this->screen = new Screen(this);
    Input* m = new Menu(this->screen);
    
    for(int i = 0; i < this->effects.size(); i++){
        m->addOption(this->effects.get(i)->type());
    }
    m->addOption("+ effect");

    
    this->screen->addInput(m);
    this->screen->draw();
    this->showing = "mainScreen";
    currentScreen = this->screen;
}


void EffectChain::addEffectScreen() {
    destroyScreen();
    this->screen = new Screen(this);
    Input* m = new Menu(this->screen);
    for (String element : availableEffects)  {
        m->addOption(element);
    }
    this->screen->addInput(m);
    this->screen->draw();
    this->showing = "effectListScreen";
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
    this->effects.get(position)->mainScreen();
}


void EffectChain::event(String command, float param){

    if (this->showing == "mainScreen") {
        
        if (command == "clicked" && param == 0) { // click sobre izquierdo
            this->destroyScreen();
            this->parent->mainScreen();
        }
        if (command == "selected") {
            if (param == this->effects.size()) {
                this->addEffectScreen();
            } else {
                this->editEffect(param);
            }
        }
    } else {
        if (this->showing == "effectListScreen") {
            if (command == "clicked" && param == 0) { // click sobre izquierdo
                this->destroyScreen();
                this->mainScreen();
            }
            if (command == "selected") {
                if (param == 0) {
                    // REVERB
                    Effect * e = new EffectReverb(this, this->stereo);
                    this->addEffect(e);
                    this->editEffect(this->effects.size()-1);
                }
                if (param == 1) {
                    // DELAY
                    Effect * e = new EffectDelay(this, this->stereo);
                    this->addEffect(e);
                    this->editEffect(this->effects.size()-1);

                }
            }
        }
    }
}

#endif