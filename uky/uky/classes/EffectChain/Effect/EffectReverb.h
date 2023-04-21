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
    void setDamping(float value);
    void setRoomSize(float value);
    
  protected:
    float roomSize, damping, lowPass, highPass;
    AudioEffectFreeverb * effectLeft;
    AudioEffectFreeverb * effectRight;

};


#endif
