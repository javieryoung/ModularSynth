#ifndef EffectDelay_guard
#define EffectDelay_guard

class EffectChain;

#include "../../../externs.h"

class EffectDelay : public EffectPreFiltered {
  public:
    EffectDelay(EffectChain * chainList, bool stereo);
    ~EffectDelay();
    String type();
    void destroyScreen();
    void mainScreen() override;
    void event(String command, float param);
    void setDelayTime();
    void setFeedback();
    
  protected:
    float feedback, delayTime;
    AudioEffectDelay * delayRight;
    AudioEffectDelay * delayLeft;

    AudioMixer4 * effectLeft;
    AudioMixer4 * effectRight;

};


#endif
