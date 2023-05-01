#ifndef EffectChain_guard
#define EffectChain_guard

#include "Arduino.h"

const String availableEffects[] = {"Reverb", "Delay"};

class EffectChain : public Screenable
{
  public:
    EffectChain(bool stereo, Screenable * parent);
    ~EffectChain();
    void addEffectScreen();
    void mainScreen() override;
    void addEffect(Effect *&e);
    void editEffect(int position);
    void event(String command, float param);
    void setInputLeft(AudioStream *);
    void setInputRight(AudioStream *);
    void setOutputLeft(AudioStream *);
    void setOutputRight(AudioStream *);
    void connect();
    void destroyConnections();
    Screenable * parent;
    
  protected:
    LinkedList<Effect*> effects;
    LinkedList<AudioConnection*> connections;
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
