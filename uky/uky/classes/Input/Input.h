#ifndef Input_guard
#define Input_guard

#include "Arduino.h"
class Input
{
  public:
    Input();
    virtual void draw();
    virtual bool touched(float x, float y);
    virtual void moved(String which, int direction);
    void select(bool s);
    virtual void refresh();
    
  protected:
    bool selected;

};

Input::Input() {
  
}

void Input::select(bool s) {
  this->selected = s;
  this->draw();
}


#endif
