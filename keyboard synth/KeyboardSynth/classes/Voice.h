#ifndef VOICE_H
#define VOICE_H

class Voice {
public:
    Voice() = default;
    virtual ~Voice() = default;

    virtual void noteOn(float frequency) = 0;
    virtual void noteOff();
    virtual AudioStream* lastNode();


protected:
    float frequency = 0.0f;
};

#endif


