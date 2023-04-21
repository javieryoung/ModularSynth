#ifndef SoloMaker_guard
#define SoloMaker_guard

#include "Arduino.h"
class SoloMaker : public Screenable
{
  public:
    SoloMaker(AudioStream * output);
    ~SoloMaker();
    void mainScreen();
    void event(String command, float param);
    AudioStream * output;
    Screen * screen;
    Modular * modular;
    EffectChain * effectChain
    void destroyScreen();
};

SoloMaker::SoloMaker(AudioStream * output) {
    this->modular = new Modular();
    this->modular->connect();

    this->effectChain = new EffectChain(false);
    this->effectChain->setInputLeft(this->modular->output);
    this->effectChain->setOutputLeft(&output);
    this->effectChain->connect();

}

SoloMaker::~SoloMaker() {
    // TODO
    delete this->modular;
    delete this->effectChain;
    this->destroyScreen();
}

void SoloMaker::destroyScreen() {
    delete this->screen;
    clear();
}

void SoloMaker::mainScreen() {
    this->screen = new Screen(this);
    
    Input* scaleButton = new Button(this->screen, "scaleButton", 10, 10, 80, 50, "Scale");
    this->screen->addInput(scaleButton);

    Input* synthButton = new Button(this->screen, "synthButton", 110, 10, 80, 50, "Synth");
    this->screen->addInput(synthButton);

    Input* effectsButton = new Button(this->screen, "effectsButton", 220, 10, 80, 50 "Effects");
    this->screen->addInput(effectsButton);

    

    this->screen->draw();
    // this->showing = "chainList";
    currentScreen = this->screen;
}

void SoloMaker::event(String command, float param){
    Serial.println(command);
    if (command == "synthButton") {
        this->destroyScreen();
        this->modular->mainScreen();
    }
    if (command == "effectsButton") {
        this->destroyScreen();
        this->effectChain->effectListScreen();
    }
    
}

#endif
