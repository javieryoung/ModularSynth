#include "Piezo.h"
#include "Multiplexer2.h"

Piezo p;
Multiplexer2 mux;

void setup() {
  Serial.begin(115200);
  //p.setPin(16);
  p.setPin(17);
  mux.setPins(2,3,4,17,16);
  char arrayOfInputs2 [16]= {'p','p','p','p','p','p','p','p','d','d','d','d','d','d','d','d'};
  mux.createArrayOfInputs(arrayOfInputs2);
}

void loop() {


  float results [16] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  bool changed [16] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
  bool buttonsCompleted = mux.read(results, changed);
  if (buttonsCompleted) {
    for (int i = 0; i<16; i++) {
      if (changed[i] && results[i] && i >= 0 && i <= 8 && results[i] > 100) {
        Serial.println(results[i]);
      }
    }
  }



}
