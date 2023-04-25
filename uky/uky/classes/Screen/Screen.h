#ifndef Screen_guard
#define Screen_guard

#include "Arduino.h"
#include "../Screenable.h"
#include "Input/Input.h"


class Screen
{
  public:
    Screen(Screenable * screenable);
    ~Screen();
    void addInput(Input *&i);
    void draw();
    void touched(float x, float y, float pressure);
    void moved(String which, int direction);
    void clicked(String which);
    void refresh();
    void event(String command, float param);
    
  private:
    LinkedList<Input*> inputs;
    long lastRefresh;
    Input* getActiveElement();
    Screenable * screenable;

};
#endif
