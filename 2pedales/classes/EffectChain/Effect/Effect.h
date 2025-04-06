#ifndef Effect_guard
#define Effect_guard

class EffectChain;
class Effect 
{
  public:
    Effect();
    virtual String type();
    
    AudioStream * getInput(String which);
    AudioStream * getOutput(String which);
    bool stereo;
    float wet; // 0: dry, 1: wet
    void doMainConnections();
    EffectChain * effectChain;
    void setWet();

    AudioStream * inputLeft;
    AudioStream * inputRight;
    AudioMixer4 * dryWetLeft; // OUTPUT
    AudioMixer4 * dryWetRight; // OUTPUT
    AudioAmplifier * ampLeft; // INPUT
    AudioAmplifier * ampRight; // INPUT
    LinkedList<AudioConnection*> connections;

};


#endif
