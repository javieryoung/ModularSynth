#ifndef Knob_guard
#define Knob_guard

#include "Arduino.h"
#include "Input.h"

class Knob : public Input
{
  public:
    Knob(float x, float y, float w, float h, String label);
    void draw(ILI9341_t3 *tft);
    bool touched(float x, float y);
    
  private:
    float x, y, w, h;
    String label;

};

Knob::Knob(float x, float y, float w, float h, String label) {
  this->x = x;
  this->y = y;
  this->h = h;
  this->w = w;
  this->label = label;
}

void Knob::draw(ILI9341_t3 *tft) {
  float centerx = this->x + this->w/2;
  float centery = this->y + this->h/2;
  float radius = min(this->w, this->h)/2;
  tft->drawCircle(centerx, centery, radius, 0xFFFF);
  
  tft->setCursor(centerx - radius + 5, centery + radius + 5);
  tft->setTextColor(0xFFFF);
  tft->print(this->label);
}

bool Knob::touched(float x, float y) {
  return (
    x > this->x && x < this->x + this->w &&
    y > this->y && y < this->y + this->h
  );
}

#endif
