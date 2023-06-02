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
    AudioEffectWaveshaper * effectLeft;
    AudioEffectWaveshaper * effectRight;
    void setWaveshape();
    void drawWaveshape();
    void redrawBar(int);
  protected:
    
    float depth;      // c

  private:
    int touchAreaX = 20;
    int touchAreaY = 120;
    float touchAreaWidth = 250;
    float touchAreaHeight = 100;
    int bars = 40;
    int shapeLength = 129;
    float shape[129] = {};
};


#endif
