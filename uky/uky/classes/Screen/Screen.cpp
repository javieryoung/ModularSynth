#ifndef ScreenCPP_guard
#define ScreenCPP_guard

#include "Arduino.h"
#include "../Screenable.h"
#include "Input/Input.h"

#include "../../externs.h"


Screen::Screen(Screenable * screenable) {
    this->screenable = screenable;
    this->inputs = LinkedList<Input*>();
}
Screen::~Screen() {
    for(int i = 0; i < this->inputs.size(); i++){
        delete this->inputs.get(i);
    }
    this->inputs.clear();
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
            if (this->getActiveElement() != NULL) {
                this->getActiveElement()->select(false);
            }
            this->inputs.get(i)->select(true);
            break;
        }
    }
}

Input* Screen::getActiveElement() {
    for(int i = 0; i < this->inputs.size(); i++){
        if (this->inputs.get(i)->selected ||this->inputs.get(i)->type() == "Menu") {
            // Algunos elementos serán unicos en pantalla y cuando se clickee un botón se aplicará sobre ellos (por ahora solo Menu)
            return this->inputs.get(i);
        }
    }
    return NULL;
}

void Screen::moved(String which, int direction) {
    if (this->getActiveElement() != NULL)
        this->getActiveElement()->moved(which, direction);
}

void Screen::clicked(String which) {
    if (this->getActiveElement() != NULL) {
        this->getActiveElement()->clicked(which);
    } else { // si se clickeo y no habia nada tiramos evento para ver que se hace
        this->event("clicked", (which == "left" ? 0 : 1));
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

void Screen::event(String command, float param) {
    this->screenable->event(command, param);
}
#endif
