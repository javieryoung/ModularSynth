#ifndef EffectReverb_guard
#define EffectReverb_guard

class EffectChain;

#include "../../../externs.h"

class EffectReverb : public Effect {
  public:
    EffectReverb(EffectChain * chainList, bool stereo);
    ~EffectReverb();
    String type();
    void destroyScreen();
    void mainScreen() override;
    void event(String command, float param);
    void setDamping();
    void setRoomSize();
    AudioEffectFreeverb * effectLeft;
    AudioEffectFreeverb * effectRight;

  protected:
    float roomSize, damping;

};


#endif
