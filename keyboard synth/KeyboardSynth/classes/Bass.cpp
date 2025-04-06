#include "Bass.h"
#include "BassVoice.h"

Bass::Bass() {
    this->currentVoice = 0;

    this->mixer1  = new AudioMixer4();
    this->mixer2  = new AudioMixer4();
    this->mixerOutput  = new AudioMixer4();

    for (int i = 0; i < 8; ++i) {
        BassVoice* voice = new BassVoice();
        this->voices.add(voice);
        auto* src = voice->lastNode();  // src es un AudioStream*
        if (i < 4){
            AudioConnection* connection = new AudioConnection(*src, 0, *this->mixer1, i);
            this->connections.add(connection);
        } else {
            AudioConnection* connection = new AudioConnection(*src, 0, *this->mixer2, i-4);
            this->connections.add(connection);
        }
    }
    AudioConnection* connection;
    connection = new AudioConnection(*this->mixer1, 0, *this->mixerOutput, 0);
    this->connections.add(connection);
    connection = new AudioConnection(*this->mixer2, 0, *this->mixerOutput, 1);
    this->connections.add(connection);

    this->mixer1->gain(0, 0.25);
    this->mixer1->gain(1, 0.25);
    this->mixer1->gain(2, 0.25);
    this->mixer1->gain(3, 0.25);
    this->mixer2->gain(0, 0.25);
    this->mixer2->gain(1, 0.25);
    this->mixer2->gain(2, 0.25);
    this->mixer2->gain(3, 0.25);
    this->mixerOutput->gain(0, 0.5);
    this->mixerOutput->gain(1, 0.5);
}

Bass::~Bass() {
    // TODO
}

void Bass::noteOn(float frequency) {
    this->voices.get(this->currentVoice)->noteOn(frequency);
    delay(10);
    this->voices.get(this->currentVoice)->noteOff();
    this->currentVoice += 1;
    if (this->currentVoice == 8) {
        this->currentVoice = 0;
    }
}

AudioStream * Bass::lastNode() {
    return this->mixerOutput;
}
