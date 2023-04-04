#ifndef Input_guard
#define Input_guard

#include "Arduino.h"
class Input
{
  public:
    Input();
    virtual void draw(ILI9341_t3 *tft);
    virtual bool touched(float x, float y);
    
  private:

};

Input::Input() {
  
}


#endif
