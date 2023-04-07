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