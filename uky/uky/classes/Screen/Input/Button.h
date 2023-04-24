#ifndef Button_guard
#define Button_guard


#include "Arduino.h"
#include "../Screen.h"
#include "Input.h"


extern Adafruit_ILI9341 tft;

class Button : public Input
{
  public:
    Button(Screen* screen, String id, float x, float y, float w, float h, String label);
    ~Button();
    String type();
    void draw();
    bool touched(float x, float y);
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

Button::Button(Screen* screen, String id, float x, float y, float w, float h, String label) {
  this->screen = screen;
  this->id = id;
  this->x = x;
  this->y = y;
  this->h = h;
  this->w = w;
  this->label = label;
}
Button::~Button() {
  
}

String Button::type() { return "Button"; }

void Button::draw() {
  tft.drawRoundRect(this->x, this->y, this->w, this->h, 8, PRIMARY);
  tft.setTextColor(BLACK);
  printCenteredString(this->label, this->x + this->w/2, this->y + (TEXT_HEIGHT + this->h)/2);
}

bool Button::touched(float x, float y) {
  bool result = (
    x > this->x && x < this->x + this->w &&
    y > this->y && y < this->y + this->h
  ); 

  if (result) {
    this->screen->event(this->id, true);
  }
  return result;
  
}

void Button::clicked(String which) {
  this->screen->event(this->id, this->value);
}

void Button::refresh() {
  this->draw();
}



#endif
