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
    
    float depth;      // c

  private:
    int touchAreaX = 20;
    int touchAreaY = 120;
    int touchAreaWidth = 200;
    int touchAreaHeight = 100;


};


#endif
