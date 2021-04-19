#include "Led.h"
#include "Multiplexer5.h"

Multiplexer5 mux;

void setup() {
  Serial.begin(9600);
  mux.start();
  Led* led = mux.getLed(0);
  led->on(200);
  led = mux.getLed(2);
  led->on(200);
  led = mux.getLed(4);
  led->on(200);
  led = mux.getLed(6);
  led->on(200);
}

void loop() {
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  analogWrite(5, 255);
  Serial.println(1);
  float resultsButtons[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
  bool changedButtons[8] = { false, false, false, false, false, false, false, false };
  float resultsPots[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  bool changedPots[16] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
  bool muxCompleted = mux.read(resultsPots, changedPots, resultsButtons, changedButtons);
  if (muxCompleted) {
    for (int i = 0; i < 16; i++ ){
      if (changedPots[i]){
        Serial.println(resultsPots[i]);
      }
    }
    for (int i = 0; i < 8; i++ ){
      if (changedButtons[i]){
        Serial.println(resultsButtons[i]);
      }
    }
  }


}
