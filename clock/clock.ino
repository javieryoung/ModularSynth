#include "Pot.h"
#include "Multiplexer5.h"

Multiplexer5 mux;
int counter = 0;
long lastTick = 0;
unsigned int tickLength = 200;
unsigned int maxTickLength = 1000;
unsigned int minTickLength = 50;
unsigned int channelChance[7][16] = {
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};
unsigned int channelSpeed[7][16] = {
  {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255},
  {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255},
  {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255},
  {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255},
  {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255},
  {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255},
  {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255}
};
int channelSelected = 0;
Pot bpm;
void setup() {
  Serial.begin(9600);
  pinMode(15, INPUT_PULLUP);
  mux.start();
  digitalWrite(13,LOW);
  digitalWrite(18,LOW);



  

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
    checkDivision(counter);
    checkSteps(counter);
  }

  if (millis() - lastTick > 200){
    turnOffDivisions();
  }

  
  
  float resultsButtons[8] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
  bool changedButtons[8] = { false, false, false, false, false, false, false, false };
  float resultsPots[16] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
  bool changedPots[16] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
  bool muxCompleted = mux.read(resultsPots, changedPots, resultsButtons, changedButtons, counter);
  if (muxCompleted) {
    for (int i = 0; i < 16; i++ ){
      if (changedPots[i]){
        int modifying = digitalRead(15); // 0: chance, 1: speed
        if (modifying == 1){
          Serial.println("Modified speed: " + (String)potToStep(i) + " to: " + resultsPots[i] + " on channel: " + (String)channelSelected);
          channelSpeed[channelSelected][potToStep(i)] = resultsPots[i];
        }
        if (modifying == 0) {
          Serial.println("Modified chance: " + (String)potToStep(i) + " to: " + resultsPots[i] + " on channel: " + (String)channelSelected);
          channelChance[channelSelected][potToStep(i)] = resultsPots[i];        
        }
      }
    }
    for (int i = 0; i < 8; i++ ){
      if (changedButtons[i]){
        if (resultsButtons[i] == 1.0) {
          int channel = buttonToChannel(i);
          Serial.println("Channel selected: " + (String)channel);
          channelSelected = channel;
        }
      }
    }
  }


}

void checkDivision(int counter) {
  if (counter == 0 || counter == 2 || counter == 4 || counter == 6 || counter == 8 || counter == 10 || counter == 12 || counter == 14)
    sendDivision(19);
  if (counter == 0 || counter == 4 || counter == 8 || counter == 12)
    sendDivision(22);
  if (counter == 0 || counter == 8)
    sendDivision(23);
  if (counter == 0)
    sendDivision(0);


  sendDivision(18);
}

void sendDivision(int p) {
  analogWrite(p, 255);
}

void turnOffDivisions() {
  analogWrite(18, 1);
  analogWrite(19, 1);
  analogWrite(20, 1);
  analogWrite(22, 1);
  analogWrite(23, 1);
  analogWrite(0, 1);

  analogWrite(6, 1);
  analogWrite(7,1);
  analogWrite(8,1);
  analogWrite(9,1);
  analogWrite(10,1);
  analogWrite(11,1);
  analogWrite(12,1);
  
}

void checkSteps(int counter) {
  for (int i = 0; i < 7; i++) {
    unsigned int random = rand() % 245;
    if (channelChance[i][counter] > random) {
      analogWrite(channelToOutput(i), channelSpeed[i][counter]);
    }
  }
  // Serial.println("Step: " + (String)counter);
}


int potToStep(int pt) {
  if (pt == 3) return 0;
  if (pt == 2) return 1;
  if (pt == 4) return 2;
  if (pt == 6) return 3;
  if (pt == 1) return 4;
  if (pt == 7) return 5;
  if (pt == 5) return 6;
  if (pt == 0) return 7;
  if (pt == 13) return 8;
  if (pt == 15) return 9;
  if (pt == 11) return 10;
  if (pt == 9) return 11;
  if (pt == 14) return 12;
  if (pt == 8) return 13;
  if (pt == 12) return 14;
  if (pt == 10) return 15;
  return 0;
}


int buttonToChannel(int bt) {
  if (bt == 6) return 0;
  if (bt == 5) return 1;
  if (bt == 0) return 2;
  if (bt == 7) return 3;
  if (bt == 4) return 4;
  if (bt == 2) return 5;
  if (bt == 1) return 6;
  return 0;
}

int channelToOutput(int ch) {
  if (ch == 0) return 12;
  if (ch == 1) return 11;
  if (ch == 2) return 10;
  if (ch == 3) return 9;
  if (ch == 4) return 8;
  if (ch == 5) return 7;
  if (ch == 6) return 6;
  return 6;
}