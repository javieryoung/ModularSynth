#include "BassVoice.h"

BassVoice::BassVoice() {
    this->waveform2  = new AudioSynthWaveform();
    this->waveform1  = new AudioSynthWaveform();
    this->pink  = new AudioSynthNoisePink();
    this->mixer  = new AudioMixer4();
    this->filter  = new AudioFilterStateVariable();
    this->envelope  = new AudioEffectEnvelope();
    this->patchCord1 = new AudioConnection(*this->waveform2, 0, *this->mixer, 1);
    this->patchCord2 = new AudioConnection(*this->waveform1, 0, *this->mixer, 0);
    this->patchCord3 = new AudioConnection(*this->pink, 0, *this->mixer, 2);
    this->patchCord4 = new AudioConnection(*this->mixer, 0, *this->filter, 0);
    this->patchCord5 = new AudioConnection(*this->filter, 0, *this->envelope, 0);

    this->waveform1->begin(WAVEFORM_SINE);
    this->waveform2->begin(WAVEFORM_SQUARE);
    this->waveform1->amplitude(0.5);
    this->waveform2->amplitude(0.5);

    this->pink->amplitude(0.3);

    this->mixer->gain(0, 0.5);
    this->mixer->gain(1, 0.5);
    this->mixer->gain(2, 0.3);

    this->filter->frequency(200);
    this->filter->resonance(1.0);

    this->envelope->attack(5);
    this->envelope->decay(15);
    this->envelope->sustain(0.8);
    this->envelope->release(500);
}

BassVoice::~BassVoice() {
    // TODO
}

void BassVoice::noteOn(float freq) {
    this->waveform1->frequency(freq);
    this->waveform2->frequency(freq);
    this->envelope->noteOn();
}

void BassVoice::noteOff() {
    this->envelope->noteOff();
}

AudioStream * BassVoice::lastNode() {
    return this->envelope;
}
