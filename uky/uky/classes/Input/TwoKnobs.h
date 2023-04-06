#ifndef TwoKnobs_guard
#define TwoKnobs_guard

#include "Arduino.h"
#include "Input.h"
#include "Knob.h"

extern Adafruit_ILI9341 tft;

class TwoKnobs : public Input
{
  public:
    TwoKnobs(float x, float y, float w, float h, float margin, String t1, String t2);
    void draw();
    bool touched(float x, float y);
    void moved(String which, int direction);
    void select(bool s);
    void refresh();
    
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
  this->selected = false;
  knob1 = new Knob(x, y, w, h, t1);
  knob2 = new Knob(x + w + margin, y, w, h, t2);
}

void TwoKnobs::draw() {
  knob1->draw();
  knob2->draw();
  if (this->selected)
    tft.drawRoundRect(this->x-10, this->y-10, (this->w * 2) + this->m + 20, this->h + 40, 8, PRIMARY);
  else
    tft.drawRoundRect(this->x-10, this->y-10, (this->w * 2) + this->m + 20, this->h + 40, 8, BLACK);
}

bool TwoKnobs::touched(float x, float y) {
  return (
    x > this->x && x < this->x + (this->w * 2) + this->m &&
    y > this->y && y < this->y + this->h
  );
}

void TwoKnobs::moved(String which, int direction) {
  if (which == "left") {
    knob1->moved("", direction);
  } 
  if (which == "right") {
    knob2->moved("", direction);
  }
}
void TwoKnobs::refresh() {
  knob1->refresh();
  knob2->refresh();
}

#endif
