#include "Pot.h"
#include "Multiplexer5.h"

Multiplexer5 mux;
int counter = 0;
long lastTick = 0;
unsigned int tickLength = 200;
unsigned int maxTickLength = 1000;
unsigned int minTickLength = 50;
Pot bpm;
void setup() {
  Serial.begin(9600);
  mux.start();
  digitalWrite(13,LOW);
  digitalWrite(18,LOW);

  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(11,HIGH);
  digitalWrite(12,HIGH);

  
  digitalWrite(18,HIGH);
  digitalWrite(19,HIGH);
  digitalWrite(22,HIGH);
  digitalWrite(23,HIGH);
  digitalWrite(0,HIGH);

  bpm.setPin(14);
  bpm.setLimits(minTickLength,maxTickLength);
}

long lastBmpRead = 0;

void loop() {
  
  if (millis() - lastBmpRead > 100) {
    lastBmpRead = millis();
    tickLength = maxTickLength - bpm.read() + minTickLength;
  }

  if (millis() - lastTick > (tickLength)) { 
    counter++;
    lastTick = millis();
    if (counter == 16) counter = 0;
  }
  
  float resultsButtons[8] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
  bool changedButtons[8] = { false, false, false, false, false, false, false, false };
  float resultsPots[16] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
  bool changedPots[16] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
  bool muxCompleted = mux.read(resultsPots, changedPots, resultsButtons, changedButtons, counter);
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
