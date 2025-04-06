#ifndef BASSVOICE_H
#define BASSVOICE_H

#include "Voice.h"
#include <Audio.h>

class BassVoice : public Voice {
public:
    BassVoice();
    ~BassVoice() override;

    void noteOn(float frequency) override;
    void noteOff();
    AudioStream* lastNode();

private:
    // Componentes de audio
    AudioSynthWaveform *waveform1;
    AudioSynthWaveform *waveform2;
    AudioSynthNoisePink *pink;
    AudioMixer4 *mixer;
    AudioFilterStateVariable *filter;
    AudioEffectEnvelope *envelope;

    // Conexiones de audio
    AudioConnection *patchCord1;
    AudioConnection *patchCord2;
    AudioConnection *patchCord3;
    AudioConnection *patchCord4;
    AudioConnection *patchCord5;

};

#endif // BASSVOICE_H
