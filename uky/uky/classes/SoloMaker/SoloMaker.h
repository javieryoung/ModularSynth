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
};

SoloMaker::SoloMaker(AudioStream * output) {

    this->modular = new Modular(&outputLeft);
    this->modular->connect();
}

SoloMaker::~SoloMaker() {
    // TODO
}

void SoloMaker::mainScreen() {
    this->screen = new Screen(this);
    Input* synthButton = new Button(this->screen, "synthButton", 10, 10, 80, 50, "Synth");
    this->screen->addInput(synthButton);

    Input* effectsButton = new Button(this->screen, "effectsButton", 110, 10, 80, 50, "Effects");
    this->screen->addInput(effectsButton);

    Input* scaleButton = new Button(this->screen, "scaleButton", 220, 10, 80, 50, "Scale");
    this->screen->addInput(scaleButton);
    

    this->screen->draw();
    // this->showing = "chainList";
    currentScreen = this->screen;
}

void SoloMaker::event(String command, float param){
    Serial.println(command);
}

#endif
