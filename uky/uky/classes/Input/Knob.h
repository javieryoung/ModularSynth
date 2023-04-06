#ifndef Knob_guard
#define Knob_guard


#include "Arduino.h"
#include "Input.h"


extern Adafruit_ILI9341 tft;




class Knob : public Input
{
  public:
    Knob(float x, float y, float w, float h, String label, float minVal, float maxVal);
    void draw();
    bool touched(float x, float y);
    void moved(String which, int direction);
    void refresh();
    
  private:
    float x, y, w, h, minVal, maxVal;
    String label;
    int value;
    int last_value; // only to know when to refresh
    long changed;

};

Knob::Knob(float x, float y, float w, float h, String label, float minVal = 0, float maxVal = 15) {
  this->x = x;
  this->y = y;
  this->h = h;
  this->w = w;
  this->label = label;
  this->value = 0;
  this->last_value = 1;
  this->changed = 0;
  this->minVal = minVal;
  this->maxVal = maxVal;
}

void Knob::draw() {
  float centerx = this->x + this->w/2;
  float centery = this->y + this->h/2;
  float r = min(this->w, this->h)/2;
  if (this->value != this->last_value) {
    // vaciar circulo anterior
    for (int i = 0; i < r; i++) {
      tft.fillCircle(centerx, centery, i, BLACK);
    }
    // borrar texto anterior
    tft.fillRect(this->x, this->y + this->h+5, this->w, 22, BLACK);

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
    
    this->last_value = this->value;
  }
  


  

  if (millis() - this->changed > 1000) {
    // borrar texto anterior
    tft.fillRect(this->x, this->y + this->h+5, this->w, 22, BLACK);
    printCenteredString(this->label, centerx, centery + r+5);
  } else {
    // borrar texto anterior
    tft.fillRect(this->x, this->y + this->h+5, this->w, 22, BLACK);
    printCenteredString(this->value, centerx, centery + r+5);
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
  
  if (this->value > this->maxVal) this->value = this->maxVal;
  if (this->value < this->minVal) this->value = this->minVal;

  this->changed = millis();
  this->draw();
}

void Knob::refresh() {
  this->draw();
}
#endif
