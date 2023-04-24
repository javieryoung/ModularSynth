#ifndef EffectChain_guard
#define EffectChain_guard

#include "Arduino.h"
#include "../Screenable.h"
#include "Effect/Effect.h"

const String availableEffects[] = {"Reverb", "Delay"};

class EffectChain : public Screenable
{
  public:
    EffectChain(bool stereo);
    ~EffectChain();
    void chainListScreen();
    void effectListScreen();
    void addEffect(Effect *&e);
    void editEffect(int position);
    void event(String command, float param);
    void setInputLeft(AudioStream *);
    void setInputRight(AudioStream *);
    void setOutputLeft(AudioStream *);
    void setOutputRight(AudioStream *);
    void connect();
    void destroyConnections();
    
  protected:
    LinkedList<Effect*> effects;
    LinkedList<AudioConnection*> connectionsLeft;
    LinkedList<AudioConnection*> connectionsRight;
    Screen* screen = NULL;
    String showing;
    void destroyScreen();
    AudioStream * inputLeft;
    AudioStream * inputRight;
    AudioStream * outputLeft;
    AudioStream * outputRight;
    AudioStream * effectLeft;
    AudioStream * effectRight;

    bool stereo;
};




#endif
