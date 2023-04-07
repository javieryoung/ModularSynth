#ifndef Input_guard
#define Input_guard

#include "Arduino.h"
class Input
{
  public:
    Input();
    virtual ~Input();
    virtual String type();
    virtual void draw();
    virtual bool touched(float x, float y);
    virtual void moved(String which, int direction);
    virtual void clicked(String which);
    virtual void addOption(String option); // Menu
    virtual void setUpKnob(String which, String id, String label, float minValue, float maxValue, float startingValue); // TwoKnobs
    void select(bool s);
    virtual void refresh();
    bool selected;
    
  protected:
};

Input::Input() {
}
Input::~Input() {
}

void Input::setUpKnob(String which, String id, String label, float minValue, float maxValue, float startingValue){

}
void Input::addOption(String option){

}
void Input::select(bool s) {
  this->selected = s;
  this->draw();
}


#endif
