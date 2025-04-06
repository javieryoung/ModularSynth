#ifndef EffectChain_guard
#define EffectChain_guard

#include "Arduino.h"

class EffectChain
{
  public:
    EffectChain(bool stereo);
    virtual ~EffectChain();
    void event(String command, float param);
    void setInputLeft(AudioStream *);
    void setInputRight(AudioStream *);
    void setOutputLeft(AudioStream *);
    void setOutputRight(AudioStream *);
    void connect();
    void destroyConnections();
    void addEffect(Effect *&e);
    
  protected:
    LinkedList<Effect*> effects;
    LinkedList<AudioConnection*> connections;
    String showing;
    AudioStream * inputLeft;
    AudioStream * inputRight;
    AudioStream * outputLeft;
    AudioStream * outputRight;
    AudioStream * effectLeft;
    AudioStream * effectRight;

    bool stereo;
};




#endif
