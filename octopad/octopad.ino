
#include "Multiplexer2.h"
#include "Input.h"
#include "Button.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           sound3;         //xy=712.5,681
AudioPlaySdWav           sound2;         //xy=714.5,643
AudioPlaySdWav           sound1;         //xy=717.5,602
AudioPlaySdWav           sound0;         //xy=719.5,550
AudioMixer4              mixerFinal;     //xy=898.5,592
AudioMixer4              mixerReverb;    //xy=1360.5,601
AudioFilterBiquad        globalFilter;   //xy=1516.5,602
AudioAmplifier           master;         //xy=1670.5,604
AudioOutputI2S           audioOutput;    //xy=1854.5,609
AudioConnection          patchCord1(sound3, 0, mixerFinal, 3);
AudioConnection          patchCord2(sound2, 0, mixerFinal, 2);
AudioConnection          patchCord3(sound1, 0, mixerFinal, 1);
AudioConnection          patchCord4(sound0, 0, mixerFinal, 0);
AudioConnection          patchCord5(mixerFinal, 0, mixerReverb, 1);
AudioConnection          patchCord6(mixerReverb, globalFilter);
AudioConnection          patchCord7(globalFilter, master);
AudioConnection          patchCord8(master, 0, audioOutput, 0);
AudioConnection          patchCord9(master, 0, audioOutput, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=775.5,814
// GUItool: end automatically generated code







AudioPlaySdWav* players [4]  = { &sound0, &sound1, &sound2, &sound3 };
String fileNames[10] = { {}, {}, {}, {}, {}, {}, {}, {}, {}, {} };

int firstDrum = 0;
int lastDrum = 49;

Multiplexer2 mux;
int currentDrum = 1;
void setup()   {      
  Serial.begin(9600);
  AudioMemory(2);
  mux.setPins(2,3,4,17,16);
  char arrayOfInputs2 [16]= {'p','p','p','p','p','p','p','p','d','d','d','d','d','d','d','d'};
  mux.createArrayOfInputs(arrayOfInputs2);


  sgtl5000_1.enable();
  sgtl5000_1.volume(0.2);

  SPI.setMOSI(7);
  SPI.setSCK(14);

  mixerFinal.gain(0,0.25);
  mixerFinal.gain(1,0.25);
  mixerFinal.gain(2,0.25);
  mixerFinal.gain(3,0.25);

/*
  freeverb1.roomsize(0.5);
  freeverb1.damping(0.5);
  reverbFilter.setLowpass(0,1200,0.707);
  reverbFilter.setHighpass(1,400,0.707);
*/
  mixerReverb.gain(0,0); // disable revereb
  mixerReverb.gain(1,1);
  mixerReverb.gain(2,0);
  mixerReverb.gain(3,0);

  
  
  globalFilter.setHighpass(0,20,0.707);

  master.gain(1.0);

  setDrumKit(currentDrum);
  if (!(SD.begin(10))) {
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
}



void setDrumKit(int which) { // rellena el array fileNames con los nombres de los archivos correspondientes
  Serial.println("Seleccionado: " + (String)which);
  fileNames[0] = (String)which + (String)"/snare.wav";
  fileNames[1] = (String)which + (String)"/kick.wav";
  fileNames[2] = (String)which + (String)"/tom1.wav";
  fileNames[3] = (String)which + (String)"/tom2.wav";
  fileNames[4] = (String)which + (String)"/tom3.wav";
  fileNames[5] = (String)which + (String)"/hhopened.wav";
  fileNames[6] = (String)which + (String)"/hhclosed.wav";
  fileNames[7] = (String)which + (String)"/crash.wav";
  fileNames[8] = (String)which + (String)"/ride.wav";
}


int lastPlayed = 0;
AudioPlaySdWav* playingHihatOpened;
void playSound(int i, float velocity) {
  int str_len = fileNames[i].length() + 1;
  char finalFileName[20];
  fileNames[i].toCharArray(finalFileName, str_len);

  Serial.println(finalFileName);
  
  // closed hh stops open hh
  if (i == 5) playingHihatOpened = players[lastPlayed];
  if (i == 6 && playingHihatOpened != NULL && playingHihatOpened->isPlaying()) playingHihatOpened->stop();

  mixerFinal.gain(lastPlayed, velocity); // velocity (max 0.25)
  players[lastPlayed]->play(finalFileName); // sound

  lastPlayed++;
  if (lastPlayed == 4) lastPlayed = 0;
  Serial.println("Memoria usada: " + (String)AudioMemoryUsageMax());
}

void loop()                     
{
  

  float results [16] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  bool changed [16] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
  bool buttonsCompleted = mux.read(results, changed);
  if (buttonsCompleted) {
    for (int i = 0; i<16; i++) {
      if (changed[i] && results[i] && i >= 0 && i <= 8 && results[i] > 100) {
        Serial.println(results[i]);
        playSound(i, 0.25);
      }
    }
  }

/*


      if (changed[i] && results[i] && i == 14) {
        currentDrum++;
        if (currentDrum == lastDrum+1) currentDrum = lastDrum;
        setDrumKit(currentDrum);
      }
      if (changed[i] && results[i] && i == 15) {
        currentDrum--;
        if (currentDrum == firstDrum-1) currentDrum = firstDrum;
        setDrumKit(currentDrum);
      }
*/
}
