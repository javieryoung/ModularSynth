#ifndef Knob_guard
#define Knob_guard


#include "Arduino.h"
#include "../Screen.h"
#include "Input.h"


extern Adafruit_ILI9341 tft;

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
    
  private:
    float x, y, w, h, minVal, maxVal;
    String id;
    String label;
    int value;
    int last_value; // only to know when to refresh
    long changed;
    Screen* screen;

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
    printCenteredString(this->label, centerx, centery + r+5 + TEXT_HEIGHT);
  } else {
    // borrar texto anterior
    tft.fillRect(this->x, this->y + this->h+5, this->w, 22, BLACK);
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
  this->value += (direction * 1.0);
  
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



#endif
