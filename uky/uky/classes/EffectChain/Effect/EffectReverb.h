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

    void setSize();
    void setLowPass();
    void setLodamp();
    void setHidamp();
    void setDiffusion();

    AudioEffectPlateReverb * effectLeft;
    
  protected:
    float size, lowpass, lodamp, hidamp, diffusion;

};


#endif
