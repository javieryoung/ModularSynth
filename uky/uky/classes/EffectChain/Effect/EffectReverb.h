#ifndef EffectReverb_guard
#define EffectReverb_guard

class EffectChain;

#include "../../../externs.h"

class EffectReverb : public EffectPreFiltered {
  public:
    EffectReverb(EffectChain * chainList, bool stereo);
    ~EffectReverb();
    String type();
    void destroyScreen();
    void mainScreen() override;
    void event(String command, float param);
    void setDamping();
    void setRoomSize();
    void setWet();
    
  protected:
    float roomSize, damping;

};


#endif
