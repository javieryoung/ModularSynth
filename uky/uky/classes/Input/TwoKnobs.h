#ifndef TwoKnobs_guard
#define TwoKnobs_guard

#include "Arduino.h"
#include "Input.h"
#include "Knob.h"

class TwoKnobs : public Input
{
  public:
    TwoKnobs(float x, float y, float w, float h, float margin, String t1, String t2);
    void draw(ILI9341_t3 *tft);
    bool touched(float x, float y);
    
  private:
    float x, y, w, h, m;
    Knob * knob1;
    Knob * knob2;

};

TwoKnobs::TwoKnobs(float x, float y, float w, float h, float margin, String t1, String t2) {
  this->x = x;
  this->y = y;
  this->w = w; // width of each knob
  this->h = h; // height of each knob
  this->m = margin;
  
  knob1 = new Knob(x, y, w, h, t1);
  knob2 = new Knob(x + w + margin, y, w, h, t2);
}

void TwoKnobs::draw(ILI9341_t3 *tft) {
  knob1->draw(tft);
  knob2->draw(tft);
}

bool TwoKnobs::touched(float x, float y) {
  return (
    x > this->x && x < this->x + (this->w * 2) + this->m &&
    y > this->y && y < this->y + this->h
  );
}

#endif
