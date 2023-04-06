#ifndef Screen_guard
#define Screen_guard

#include "Arduino.h"
#include "Input/Input.h"


class Screen
{
  public:
    Screen();
    void addInput(Input *&i);
    void draw();
    void touched(float x, float y, float pressure);
    void moved(String which, int direction);
    void refresh();
    
  private:
    LinkedList<Input*> inputs;
    Input* selectedInput;
    long lastRefresh;

};

Screen::Screen() {
  this->inputs = LinkedList<Input*>();
  this->selectedInput = NULL;
}

void Screen::addInput(Input *&i) {
    this->inputs.add(i);
}

void Screen::draw() {
    for(int i = 0; i < this->inputs.size(); i++){
        this->inputs.get(i)->draw();
    }
}

void Screen::touched(float x, float y, float pressure) {
    for(int i = 0; i < this->inputs.size(); i++){
        if (this->inputs.get(i)->touched(x, y)) {
            if (this->selectedInput != NULL) {
                this->selectedInput->select(false);
            }
            this->selectedInput = this->inputs.get(i); 
            this->selectedInput->select(true);
        }
    }
}

void Screen::moved(String which, int direction) {
    if (this->selectedInput != NULL) {
        this->selectedInput->moved(which, direction);
    }
}
void Screen::refresh() {
    if (millis() - this->lastRefresh > 500) {
        this->lastRefresh = millis();
        for(int i = 0; i < this->inputs.size(); i++) {
            this->inputs.get(i)->refresh();
        }
    }
}
#endif
