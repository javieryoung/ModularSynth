#include "Input.h"
#include "Button.h"
#include "Pot.h"
#include "PWM.h"
Button b;
Pot p;

Input* inputs[2];
PWM pwmClock0(17);

void setup() {
  pwm.begin(1);
  pwmClock0.begin(1);
  Serial.begin(115200);
}

void loop() 
  long readClock0 = pwmClock0.getValue();
  Serial.println(readClock0);
}
