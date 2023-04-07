#ifndef EffectChain_guard
#define EffectChain_guard

#include "Arduino.h"
#include "../Screenable.h"
#include "Effect/Effect.h"

const String availableEffects[] = {"Reverb", "Delay"};

class EffectChain : public Screenable
{
  public:
    EffectChain();
    void chainList();
    void effectList();
    void addEffect(Effect *&e);
    void editEffect(int position);
    void event(String command, float param);
    
  protected:
    LinkedList<Effect*> effects;
    Screen* screen = NULL;
    String showing;
    void destroyScreen();

};




#endif
