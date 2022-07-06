#include "Multiplexer2.h"
#include "Input.h"
#include "Button.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SerialFlash.h>


// GUItool: begin automatically generated code
AudioPlaySdWav          sound4;       //xy=362.6666564941406,441.66666412353516
AudioPlaySdWav          loopPlayer;       //xy=364.66666412353516,599.6667041778564
AudioPlaySdWav          sound3;         //xy=367.6666564941406,362.0000047683716
AudioPlaySdWav          sound6;       //xy=368.66666412353516,551.6667041778564
AudioPlaySdWav          sound2;         //xy=369.6666564941406,324.0000047683716
AudioPlaySdWav          sound1;         //xy=372.6666564941406,283.0000047683716
AudioPlaySdWav          sound0;         //xy=374.6666564941406,231.00000476837158
AudioPlaySdWav          sound5;       //xy=376.6666564941406,506.66666412353516
AudioMixer4              mixer1;     //xy=587.6667022705078,276
AudioMixer4              mixer2;         //xy=598.6667022705078,458.6666717529297
AudioMixer4              mixerReverb;    //xy=1015.6666564941406,282.0000047683716
AudioFilterBiquad        globalFilter;   //xy=1171.6666564941406,283.0000047683716
AudioAmplifier           master;         //xy=1325.6666564941406,285.0000047683716
AudioOutputI2S           audioOutput;    //xy=1509.6666564941406,290.0000047683716
AudioConnection          patchCord1(sound4, 0, mixer2, 0);
AudioConnection          patchCord2(loopPlayer, 0, mixer2, 3);
AudioConnection          patchCord3(sound3, 0, mixer1, 3);
AudioConnection          patchCord4(sound6, 0, mixer2, 2);
AudioConnection          patchCord5(sound2, 0, mixer1, 2);
AudioConnection          patchCord6(sound1, 0, mixer1, 1);
AudioConnection          patchCord7(sound0, 0, mixer1, 0);
AudioConnection          patchCord8(sound5, 0, mixer2, 1);
AudioConnection          patchCord9(mixer1, 0, mixerReverb, 1);
AudioConnection          patchCord10(mixer2, 0, mixerReverb, 2);
AudioConnection          patchCord11(mixerReverb, globalFilter);
AudioConnection          patchCord12(globalFilter, master);
AudioConnection          patchCord13(master, 0, audioOutput, 0);
AudioConnection          patchCord14(master, 0, audioOutput, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=361.66666412353516,678.0001201629639
// GUItool: end automatically generated code



AudioPlaySdWav* players [7]  = { &sound0, &sound1, &sound2, &sound3, &sound4, &sound6, &sound6 };
Multiplexer2 mux;
bool playingLoop = false;

void setup() {
  Serial.begin(9600);
  AudioMemory(10);
  mux.setPins(2,3,4,20,17);
  char arrayOfInputs2 [16]= {
    'd','d','d','d','d','d','d','d',
    'd','d','d','d','a','d','d','d'};
  mux.createArrayOfInputs(arrayOfInputs2);
  mux.getObject(12)->setLimits(0,1);

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.6);


  mixer1.gain(0,0.25);
  mixer1.gain(1,0.25);
  mixer1.gain(2,0.25);
  mixer1.gain(3,0.25);

  mixer2.gain(0,0.25);
  mixer2.gain(1,0.25);
  mixer2.gain(2,0.25);
  mixer2.gain(3,0.15);

/*
  freeverb1.roomsize(0.5);
  freeverb1.damping(0.5);
  reverbFilter.setLowpass(0,1200,0.707);
  reverbFilter.setHighpass(1,400,0.707);
*/
  mixerReverb.gain(0,0); // disable revereb
  mixerReverb.gain(1,0.5);
  mixerReverb.gain(2,0.5);
  mixerReverb.gain(3,0);

  
  
  globalFilter.setHighpass(0,20,0.707);

  master.gain(0.9);

  SPI.setMOSI(7);
  SPI.setSCK(14);
  if (!(SD.begin(10))) {
    // stop here, but print a message repetitively
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }

}

bool reading = false;
int lastRead = 0;
long startRead = 0;
long lastSoundPlayed = 0;

void loop() {
  reloadLoop();
  float results [16] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  bool changed [16] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
  bool buttonsCompleted = mux.read(results, changed);
  if (buttonsCompleted && millis() - lastSoundPlayed > 20) {
    for (int i = 0; i<=7; i++) {
      if (changed[i] && results[i]) {
        Serial.println(i);
        playSound(i);
        lastSoundPlayed = millis();
      }
    }
    if (changed[10] && results[10]) {
      switchLoop();
    }

    if (changed[12]) {
      Serial.println(results[12]);
      master.gain(1-results[12]);
    }

    if (changed[8] || changed[14]) {
      if (!reading) {
        reading = true;
        startRead = millis();
      }
      if (millis() - startRead < 100) {
        if (changed[8]) lastRead = 8;
        if (changed[14]) lastRead = 14;
      } else {
        reading = false;
        if (lastRead == 8) changeLoop(-1);
        if (lastRead == 14) changeLoop(1);
      }
    }
    
      

  }

}


int lastPlayed = 0;
void playSound(int i) {

  switch (i) {
    case 0:
      players[lastPlayed]->play("eltupe.wav");
      break;
    case 1:
      players[lastPlayed]->play("medasunbeso.wav");
      break;
    case 2:
      players[lastPlayed]->play("dijonadienunca.wav");
      break;
    case 3:
      players[lastPlayed]->play("sosunaplaga.wav");
      break;
    case 4:
      players[lastPlayed]->play("yosoymana.wav");
      break;
    case 5:
      players[lastPlayed]->play("mmsi.wav");
      break;
    case 6:
      players[lastPlayed]->play("lamaxima.wav");
      break;
    case 7:
      players[lastPlayed]->play("miau.wav");
      break;
  }
  
  lastPlayed++;
  if (lastPlayed == 6) lastPlayed = 0;
}


int startedLoop = 0;
void switchLoop() {
  playingLoop = !playingLoop;
  if (playingLoop) {
      startedLoop = millis();
      playLoop();
  } else {
    loopPlayer.stop();
  }
}

void reloadLoop() {
  if (playingLoop && millis() - startedLoop >= 4100) {
    startedLoop = millis();
    playLoop();
  }
}

int loopSelected = 0;

void changeLoop(int i) {
  loopSelected += i;
  if (loopSelected == 4) loopSelected = 0;
  if (loopSelected == -1) loopSelected = 3;
  loopPlayer.stop();
  if (playingLoop)
    playLoop();
}
void playLoop() {
    switch(loopSelected) {
      case 0: 
        loopPlayer.play("loop1.wav");
        break;
      case 1: 
        loopPlayer.play("loop2.wav");
        break;
      case 2: 
        loopPlayer.play("loop3.wav");
        break;
      case 3: 
        loopPlayer.play("loop4.wav");
        break;
    }
    
}
