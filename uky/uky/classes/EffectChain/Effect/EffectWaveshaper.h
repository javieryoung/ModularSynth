#ifndef EffectWaveshaper_guard
#define EffectWaveshaper_guard

class EffectChain;

#include "../../../externs.h"

class EffectWaveshaper : public EffectPreFiltered {
  public:
    EffectWaveshaper(EffectChain * chainList, bool stereo);
    ~EffectWaveshaper();
    String type();
    void destroyScreen();
    void mainScreen() override;
    void event(String command, float param);
    void reloadWaveshape();
    AudioEffectWaveshaper * effectLeft;
    AudioEffectWaveshaper * effectRight;
    
  protected:
    // f(x) = sin(ax PI) + cx
    float length;     // a
    float angle;      // c

};


#endif
