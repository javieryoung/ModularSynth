#include "Input.h"
#include "Button.h"
#include "Pot.h"
Button b;
Pot p;

Input* inputs[2];

void setup() {
  // put your setup code here, to run once:
  inputs[0] = new Button();
  inputs[0]->setPin(20);
  inputs[1] = new Pot();
  inputs[1]->setPin(21);
}

void loop() {
  // put your main code here, to run repeatedly:
  float potRead = inputs[1]->read();
  Serial.println(potRead);
}
