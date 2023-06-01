#ifndef TouchArea_guard
#define TouchArea_guard


#include "Arduino.h"
#include "../Screen.h"
#include "Input.h"
#include "../../../externs.h"

class TouchArea : public Input
{
  public:
    TouchArea(Screen* screen, String id, float x, float y, float w, float h, String label);
    ~TouchArea();
    String type();
    void draw();
    bool touched(float x, float y);
    void clicked(String which);
    void refresh();
    void select(bool s);
    
  private:
    float x, y, w, h, minVal, maxVal;
    String id;
    String label;
    int value;
    int last_value; // only to know when to refresh
    long changed;
    Screen* screen;

};

TouchArea::TouchArea(Screen* screen, String id, float x, float y, float w, float h, String label) {
  this->screen = screen;
  this->id = id;
  this->x = x;
  this->y = y;
  this->h = h;
  this->w = w;
  this->label = label;
}
TouchArea::~TouchArea() {
  
}

String TouchArea::type() { return "TouchArea"; }

void TouchArea::draw() {
    
}

bool TouchArea::touched(float x, float y) {
  bool result = (
    x > this->x && x < this->x + this->w &&
    y > this->y && y < this->y + this->h
  ); 
  float parameter = x * 10000 + y; // si la coordenada es (100, 50) queda 1.000.050
  // lo des-hacemos usando
  // int x = parameter / 10000;
  // int y  = parameter - (x * 10000);
  this->screen->event(this->id, parameter);
  return result;
}


void TouchArea::select(bool s) {
  this->selected = s;
}

void TouchArea::clicked(String which) {
}

void TouchArea::refresh() {
}



#endif
