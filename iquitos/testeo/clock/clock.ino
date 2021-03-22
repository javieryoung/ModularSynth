
#include "Button.h"
#include "Pot.h"

Pot pot;
void setup() {
  pinMode(2, OUTPUT); // mux S0
  pinMode(3, OUTPUT); // mux S1
  pinMode(4, OUTPUT); // mux S2
  pinMode(23, OUTPUT); // output
  pinMode(22, INPUT); // output
  pinMode(14, OUTPUT); // output
  pinMode(5, OUTPUT); // output
  pot.setPin(22);
  pot.setLimits(0.0,1.0);

}
long lastChange= 0;
int analogValue = 100;
int i = 0;
void loop() {
  int _modes [8][3] = { {LOW, LOW, LOW}, {LOW, LOW, HIGH}, {LOW, HIGH, LOW}, {LOW, HIGH, HIGH}, {HIGH, LOW, LOW}, {HIGH, LOW, HIGH}, {HIGH, HIGH, LOW}, {HIGH, HIGH, HIGH} };
  analogWrite(23,analogValue);
  if (millis() - lastChange > 1000) {
    digitalWrite(2, _modes[i][0]);
    digitalWrite(3, _modes[i][1]);
    digitalWrite(4, _modes[i][2]);
    if(i == 0) {
      analogWrite(5,analogValue);
    } else {
      analogWrite(5,1);
    }

    i++;
    if (i == 8) i = 0;
    lastChange = millis();
  }

  if (pot.changed() ){
    float potRead = pot.read();
    analogWrite(14,potRead);
    Serial.println(potRead);
  }
}
