#ifndef EffectReverb_guard
#define EffectReverb_guard

#include "Arduino.h"
class EffectChain;
#include "../EffectChain.h"
#include "../../../externs.h"

class EffectReverb : public EffectPreFiltered
{
  public:
    EffectReverb(EffectChain * chainList, bool stereo);
    ~EffectReverb();
    String type();
    void destroyScreen();
    void edit();
    void event(String command, float param);
    void setDamping();
    void setRoomSize();
    void setWet();
    
  protected:
    float roomSize, damping;

};


#endif
