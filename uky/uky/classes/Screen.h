#ifndef Screen_guard
#define Screen_guard

#include "Arduino.h"
#include "Input/Input.h"
class Screen
{
  public:
    Screen(ILI9341_t3 *tft);
    void addInput(Input *&i);
    void draw();
    void touched(float x, float y, float pressure);
    
  private:
    LinkedList<Input*> inputs;
    ILI9341_t3 *tft;

};

Screen::Screen(ILI9341_t3 *tft) {
  this->tft = tft;
  this->inputs = LinkedList<Input*>();
}

void Screen::addInput(Input *&i) {
    this->inputs.add(i);
}

void Screen::draw() {
    for(int i = 0; i < this->inputs.size(); i++){
        this->inputs.get(i)->draw(this->tft);
    }
}

void Screen::touched(float x, float y, float pressure) {
    for(int i = 0; i < this->inputs.size(); i++){
        if (this->inputs.get(i)->touched(x, y)) {
            // CLICKEADO
        }
    }
}

#endif
