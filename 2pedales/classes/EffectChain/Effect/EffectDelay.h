#ifndef EffectDelay_guard
#define EffectDelay_guard

class EffectChain;


class EffectDelay : public EffectPreFiltered {
  public:
    EffectDelay(EffectChain * chainList, bool stereo);
    ~EffectDelay();
    String type();
    void event(String command, float param);
    void setDelayTime();
    void setFeedback();
    
    float feedback, delayTime;
    AudioEffectDelay * delayRight;
    AudioEffectDelay * delayLeft;
    AudioMixer4 * effectLeft;
    AudioMixer4 * effectRight;

};


#endif
