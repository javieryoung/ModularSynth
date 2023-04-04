#ifndef Knob_guard
#define Knob_guard

#include "Arduino.h"
#include "Input.h"

class Knob : public Input
{
  public:
    Knob(ILI9341_t3 *tft, float x, float y, float w, float h, String label);
    void draw();
    bool touched(float x, float y);
    void moved(String which, int direction);
    
  private:
    ILI9341_t3 *tft;
    float x, y, w, h;
    String label;
    int value;
    long changed;

};

Knob::Knob(ILI9341_t3 *tft, float x, float y, float w, float h, String label) {
  this->tft = tft;
  this->x = x;
  this->y = y;
  this->h = h;
  this->w = w;
  this->label = label;
  this->value = 0;
  this->changed = 0;
}

void Knob::draw() {
  this->tft->fillRect(this->x, this->y, this->w, this->h+25, BLACK);
  float centerx = this->x + this->w/2;
  float centery = this->y + this->h/2;
  float radius = min(this->w, this->h)/2;
  this->tft->drawCircle(centerx, centery, radius, 0xFFFF);
  
  if (millis() - this->changed > 1000) {
    this->tft->setCursor(centerx - radius, centery + radius+5);
    this->tft->setTextColor(0xFFFF);
    this->tft->print(this->label);
  } else {
    this->tft->setCursor(centerx - radius, centery + radius+5);
    this->tft->setTextColor(0xFFFF);
    this->tft->print(this->value);
  }
}

bool Knob::touched(float x, float y) {
  return (
    x > this->x && x < this->x + this->w &&
    y > this->y && y < this->y + this->h
  );
}
void Knob::moved(String which, int direction) {
  this->value += (direction * 1.0);
  this->tft->drawRect(this->x, this->y + this->h, 12, this->w, BLACK);
  this->changed = millis();
  this->draw();
  Serial.println(this->value);
}

#endif
