#ifndef EffectReverb_guard
#define EffectReverb_guard

#include "Arduino.h"
class EffectChain;
#include "../EffectChain.h"

extern Screen* currentScreen;

class EffectReverb : public Effect
{
  public:
    EffectReverb(EffectChain * effectChain);
    ~EffectReverb();
    String type();
    void destroyScreen();
    void edit();
    void event(String command, float param);
    AudioStream * getAudioStream(String which);
    
  protected:
    Screen* screen = NULL;
    EffectChain* effectChain;
    float roomSize, damping, lowPass, highPass;
    AudioEffectFreeverb * effectLeft;
    AudioEffectFreeverb * effectRight;

};


#endif
