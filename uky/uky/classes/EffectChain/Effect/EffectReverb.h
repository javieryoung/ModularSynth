#ifndef EffectReverb_guard
#define EffectReverb_guard

#include "Arduino.h"
class EffectChain;
#include "../EffectChain.h"

extern Screen* currentScreen;

class EffectReverb : public Effect
{
  public:
    EffectReverb(EffectChain * effectChain, bool stereo);
    ~EffectReverb();
    String type();
    void destroyScreen();
    void edit();
    void event(String command, float param);
    void setDamping();
    void setRoomSize();
    void setWet();
    EffectChain* effectChain;
    
  protected:
    float roomSize, damping, lowPass, highPass;
    AudioEffectFreeverb * effectLeft;
    AudioEffectFreeverb * effectRight;

};


#endif
