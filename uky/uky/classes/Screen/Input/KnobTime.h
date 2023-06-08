#ifndef KnobTime_guard
#define KnobTime_guard


#include "Arduino.h"
#include "../Screen.h"
#include "Input.h"


#include "../../../externs.h"

class KnobTime : public Input
{    
  protected:
    void drawKnob();
    void drawText();

};

void KnobTime::drawText() {
  float centerx = this->x + this->w/2;
  float centery = this->y + this->h/2;
  float r = min(this->w, this->h)/2;
  // borrar texto anterior
  tft.fillRect(this->x, this->y + this->h+5, this->w, 22, BLACK);

  if (millis() - this->changed > 1000) {
    printCenteredString(this->label, centerx, centery + r+5 + TEXT_HEIGHT);
  } else {
    float value = this->value;
    float unit = "ms";
    if (value > 1) {
      unit = "s";
      value = value / 1000;
      value = float(int (value*100))/100; // leave only 2 decimal points
    }
    printCenteredString(value + " " + unit, centerx, centery + r+5 + TEXT_HEIGHT);
  }
}


bool KnobTime::touched(float x, float y) {
  return (
    x > this->x && x < this->x + this->w &&
    y > this->y && y < this->y + this->h
  );
}
void KnobTime::moved(String which, int direction) {
  this->value += (direction * 1.0) * (this->maxVal - this->minVal)/20;
  
  if (this->value > this->maxVal) this->value = this->maxVal;
  if (this->value < this->minVal) this->value = this->minVal;

  this->screen->event(this->id, this->value);

  this->changed = millis();
  this->draw();
}


void KnobTime::clicked(String which) {
  
}

void KnobTime::refresh() {
  this->draw();
}



void KnobTime::select(bool s) {
  this->selected = s;
  this->draw();
}
#endif
