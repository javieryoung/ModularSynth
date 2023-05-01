#ifndef Menu_guard
#define Menu_guard

#include "Arduino.h"
#include "../Screen.h"
#include "../../../externs.h"

class Menu : public Input
{
  public:
    Menu(Screen* screen);
    ~Menu();
    String type();
    void draw();
    bool touched(float x, float y);
    void moved(String which, int direction);
    void clicked(String which);
    void addOption(String option);
    void refresh();
    void select(bool s);
    
  protected:
    bool selected;
    int value = 0;
    int last_value = 10;
    LinkedList<String> options;
    Screen* screen;

};

Menu::Menu(Screen* screen) {
  this->screen = screen;
  this->options = LinkedList<String>();
}
Menu::~Menu() {
  
}

String Menu::type() { return "Menu"; }

void Menu::draw() {
  if(this->value != this->last_value) {
    for(int i = 0; i < this->options.size(); i++){
      float margin = 10;
      tft.setCursor(margin*2, margin + i * 30 + TEXT_HEIGHT + 4);
      if (i == this->value) {
        tft.fillRoundRect(margin, margin + i * 30, SCREEN_WIDTH - margin*2, 25, 8, PRIMARY);
        
        tft.setTextColor(BLACK);
      } else {
        tft.fillRoundRect(margin, margin + i * 30, SCREEN_WIDTH - margin*2, 25, 8, BLACK);
        
        tft.setTextColor(PRIMARY);
      }
      Serial.println(this->options.get(i));
      tft.print(this->options.get(i));
    }
  }
  this->last_value = this->value;
}


bool Menu::touched(float x, float y) {
  return false;
}

void Menu::moved(String which, int direction) {
  this->value += direction;
  if (this->value > this->options.size()-1) this->value = this->options.size()-1;
  if (this->value < 0) this->value = 0;
  this->draw();
}

void Menu::addOption(String option) {
  this->options.add(option);
}

void Menu::clicked(String which) {
  if (which == "right")
    this->screen->event("selected", this->value);
  else
    this->screen->event("clicked", 0); // clicked left
}

void Menu::refresh() {

}


void Menu::select(bool s) {
  this->selected = s;
  this->draw();
}


#endif
