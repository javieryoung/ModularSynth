#ifndef BASS_H
#define BASS_H

#include <Audio.h>
#include "BassVoice.h"

class Bass {
public:
    Bass();                            // Constructor
    ~Bass();                           // Destructor
    LinkedList<BassVoice*> voices;
    LinkedList<AudioConnection*> connections;

    void noteOn(float frequency);      // Toca una nota con la frecuencia dada
    AudioStream* lastNode();

private:
    int currentVoice;
    
    AudioMixer4 *mixer1;
    AudioMixer4 *mixer2;
    AudioMixer4 *mixerOutput;
};

#endif
