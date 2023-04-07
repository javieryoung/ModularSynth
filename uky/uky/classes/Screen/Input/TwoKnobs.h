#ifndef TwoKnobs_guard
#define TwoKnobs_guard

#include "Arduino.h"
#include "../Screen.h"
#include "Input.h"
#include "Knob.h"


extern Adafruit_ILI9341 tft;

class TwoKnobs : public Input
{
  public:
    TwoKnobs(Screen* screen, float x, float y, float w, float h, float margin);
    ~TwoKnobs();
    String type();
    void setUpKnob(String which, String id, String label, float minValue, float maxValue, float startingValue);
    void draw();
    bool touched(float x, float y);
    void moved(String which, int direction);
    void clicked(String which);
    void select(bool s);
    void refresh();
    
  private:
    float x, y, w, h, m;
    Knob * knob1;
    Knob * knob2;
    Screen* screen;

};

TwoKnobs::TwoKnobs(Screen* screen, float x, float y, float w, float h, float margin) {
  this->screen = screen;
  this->x = x;
  this->y = y;
  this->w = w; // width of each knob
  this->h = h; // height of each knob
  this->m = margin;
  this->selected = false;
}

TwoKnobs::~TwoKnobs() {
  delete knob1;
  delete knob2;
}

String TwoKnobs::type() { return "TwoKnobs"; }

void TwoKnobs::setUpKnob(String which, String id, String label, float minValue, float maxValue, float startingValue) {
  if (which == "left") {
    knob1 = new Knob(this->screen, id, this->x, this->y, this->w, this->h, label, minValue, maxValue, startingValue);
  } else {
    knob2 = new Knob(this->screen, id, this->x + this->w + this->m, this->y, this->w, this->h, label, minValue, maxValue, startingValue);
  }

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


void TwoKnobs::clicked(String which) {
  if (this->selected) {
    this->selected = false;
    this->draw();
  }
  if (which == "left") {
    knob1->clicked("left");
  }
  if (which == "right") {
    knob2->clicked("right");
  }
}


void TwoKnobs::refresh() {
  knob1->refresh();
  knob2->refresh();
}


#endif
