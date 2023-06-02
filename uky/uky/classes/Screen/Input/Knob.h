#ifndef Knob_guard
#define Knob_guard


#include "Arduino.h"
#include "../Screen.h"
#include "Input.h"


#include "../../../externs.h"

class Knob : public Input
{
  public:
    Knob(Screen* screen, String id, float x, float y, float w, float h, String label, float minVal, float maxVal, float startingValue);
    ~Knob();
    String type();
    void draw();
    bool touched(float x, float y);
    void moved(String which, int direction);
    void clicked(String which);
    void refresh();
    void select(bool s);
    
  private:
    float x, y, w, h, minVal, maxVal;
    String id;
    String label;
    float value;
    float last_value; // only to know when to refresh
    long changed;
    Screen* screen;
    
  protected:
    void drawKnob();
    void drawText();

};

Knob::Knob(Screen* screen, String id, float x, float y, float w, float h, String label, float minVal = 0, float maxVal = 15, float startingValue = 0) {
  this->screen = screen;
  this->id = id;
  this->x = x;
  this->y = y;
  this->h = h;
  this->w = w;
  this->label = label;
  this->value = startingValue;
  this->last_value = 1;
  this->changed = 0;
  this->minVal = minVal;
  this->maxVal = maxVal;
}
Knob::~Knob() {
  
}

String Knob::type() { return "Knob"; }

void Knob::draw() {
  
  if (this->value != this->last_value) {
    this->drawKnob();
    this->drawText();
    this->last_value = this->value;
  }

}

void Knob::drawKnob() {
  float centerx = this->x + this->w/2;
  float centery = this->y + this->h/2;
  float r = min(this->w, this->h)/2;
  
  // vaciar circulo anterior
  for (int i = 0; i < r; i++) {
    tft.fillCircle(centerx, centery, i, BLACK);
  }
  
  // dibujar circulo
  int thick = 2;
  for (int i = 0; i < thick; i++) {
      tft.drawCircle(centerx, centery, r-i, PRIMARY);
  }
  
  // Knob line:
  float angle = this->value/this->maxVal * PI*1.5 - (2*PI)-(PI*1.25);
  float catOp = sin(angle) * r;
  float catAdy = cos(angle) * r;
  tft.drawLine(centerx, centery, centerx+catAdy, centery+catOp, PRIMARY);
  tft.fillCircle(centerx, centery, r/2, BLACK);
}

void Knob::drawText() {
  float centerx = this->x + this->w/2;
  float centery = this->y + this->h/2;
  float r = min(this->w, this->h)/2;
  // borrar texto anterior
  tft.fillRect(this->x, this->y + this->h+5, this->w, 22, BLACK);

  if (millis() - this->changed > 1000) {
    printCenteredString(this->label, centerx, centery + r+5 + TEXT_HEIGHT);
  } else {
    printCenteredString(this->value, centerx, centery + r+5 + TEXT_HEIGHT);
  }
}


bool Knob::touched(float x, float y) {
  return (
    x > this->x && x < this->x + this->w &&
    y > this->y && y < this->y + this->h
  );
}
void Knob::moved(String which, int direction) {
  this->value += (direction * 1.0) * (this->maxVal - this->minVal)/20;
  
  if (this->value > this->maxVal) this->value = this->maxVal;
  if (this->value < this->minVal) this->value = this->minVal;

  this->screen->event(this->id, this->value);

  this->changed = millis();
  this->draw();
}


void Knob::clicked(String which) {
  
}

void Knob::refresh() {
  this->draw();
}



void Knob::select(bool s) {
  this->selected = s;
  this->draw();
}
#endif
