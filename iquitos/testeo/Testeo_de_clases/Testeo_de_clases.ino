#include "Input.h"
#include "Button.h"
#include "Pot.h"
#include "PWM.h"
Button b;
Pot p;

Input* inputs[2];
PWM pwm(22);

void setup() {
  pwm.begin(1);
  Serial.begin(115200);
}

void loop() {
  int pwmChange = pwm.getValue();
  Serial.println(pwmChange);
  delay(50);
}
