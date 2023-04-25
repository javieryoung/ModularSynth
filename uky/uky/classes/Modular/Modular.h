#ifndef Modular_guard
#define Modular_guard

#include "Arduino.h"


class Modular : public Screenable
{
  public:
    Modular(AudioStream * output);
    ~Modular();
    int getAvailableVoice();
    void playNote(float freq);
    void connect();
    void menuScreen();
    void event(String command, float param);
    void mainScreen();
    AudioStream * output;
    
    
  private:
    AudioMixer4 * mixer1;
    AudioMixer4 * mixer2;
    AudioMixer4 * mixerFinal;
    AudioEffectEnvelope * envelopes[8];
    AudioSynthWaveformModulated * waves[8];
    AudioConnection * patches[19];
    Screen * screen;


};

Modular::Modular(AudioStream * output) {
    this->output = output;

}

Modular::~Modular() {
    // TODO
}

void Modular::connect() {
    this->mixer1 = new AudioMixer4();
    this->mixer2 = new AudioMixer4();
    this->mixerFinal = new AudioMixer4();

    // envelopes
    for (int i = 0; i < 8; i++) {
        this->envelopes[i] = new AudioEffectEnvelope();

        this->envelopes[i]->attack(10);
        this->envelopes[i]->decay(1);
        this->envelopes[i]->sustain(1);
        this->envelopes[i]->release(1000);
        
    }
    // waves
    for (int i = 0; i < 8; i++) {
        this->waves[i] = new AudioSynthWaveformModulated();
        this->waves[i]->frequency(440);
        this->waves[i]->amplitude(1);
        this->waves[i]->frequencyModulation(1);
        
        this->waves[i]->begin(WAVEFORM_SINE);
    }
    // patches
    for (int i = 0; i < 8; i++) {
        if (i < 4)
            this->patches[i] = new AudioConnection(*this->envelopes[i], 0, *this->mixer1, i);
        if (i >= 4)
            this->patches[i] = new AudioConnection(*this->envelopes[i], 0, *this->mixer2, i-4);
        this->patches[i]->connect();
    }
    for (int i = 8; i < 16; i++) {
        this->patches[i] = new AudioConnection(*this->waves[i-8], 0, *this->envelopes[i-8], 0);
        this->patches[i]->connect();
    }
    this->patches[16] = new AudioConnection(*this->mixer1, 0, *this->mixerFinal, 0);
    this->patches[17] = new AudioConnection(*this->mixer2, 0, *this->mixerFinal, 1);
    this->patches[18] = new AudioConnection(*this->mixerFinal, 0, *this->output, 0);
    this->patches[16]->connect();
    this->patches[17]->connect();
    this->patches[18]->connect();

    
    this->mixer1->gain(0,0.25);
    this->mixer1->gain(1,0.25);
    this->mixer1->gain(2,0.25);
    this->mixer1->gain(3,0.25);

    this->mixer2->gain(0,0.25);
    this->mixer2->gain(1,0.25);
    this->mixer2->gain(2,0.25);
    this->mixer2->gain(3,0.25);

    this->mixerFinal->gain(0,0.50);
    this->mixerFinal->gain(1,0.50);
    this->mixerFinal->gain(2,0);
    this->mixerFinal->gain(3,0);
}


int Modular::getAvailableVoice() {
    for (int i = 0; i < 8; i++) {
        if (!this->envelopes[i]->isActive())
            return i;
    }
    return 0;
}

void Modular::playNote(float freq) {
    int voice = this->getAvailableVoice();
    if (voice != -1) {
        this->waves[voice]->frequency(freq);
        this->envelopes[voice]->noteOn();
        delay(50);
        this->envelopes[voice]->noteOff();
    }
}

void Modular::menuScreen() {
}


void Modular::event(String command, float param){
    Serial.println(command);
    if(command == "attack") {
        for (int i = 0; i < 8; i++) {
            this->envelopes[i]->attack(param*1000);
        }
    }
    if(command == "decay") {
        for (int i = 0; i < 8; i++) {
            this->envelopes[i]->decay(param*1000);
        }
    }
    if(command == "sustain") {
        for (int i = 0; i < 8; i++) {
            this->envelopes[i]->sustain(param);
        }
    }
    if(command == "release") {
        for (int i = 0; i < 8; i++) {
            this->envelopes[i]->release(param*1000);
        }
    }
}


void Modular::mainScreen(){
    clear();
    this->screen = new Screen(this);
    Input* attackDecayKnobs = new TwoKnobs(this->screen, 50, 150, 40, 40, 10);
    attackDecayKnobs->setUpKnob("left", "attack", "A", 0, 3, 0);
    attackDecayKnobs->setUpKnob("right", "decay", "D", 0, 3, 0);
    this->screen->addInput(attackDecayKnobs);   

    Input* sustainReleaseKnobs = new TwoKnobs(this->screen, 50+100+10, 150, 40, 40, 10);
    sustainReleaseKnobs->setUpKnob("left", "sustain", "S", 0, 1, 0);
    sustainReleaseKnobs->setUpKnob("right", "release", "R", 0, 3, 0);
    this->screen->addInput(sustainReleaseKnobs);   

    this->screen->draw();
    // this->showing = "chainList";
    currentScreen = this->screen;
}

#endif