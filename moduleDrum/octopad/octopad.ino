
#include "PWM.h"








#include "Multiplexer2.h"
#include "Input.h"
#include "Button.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>


// GUItool: begin automatically generated code
AudioPlaySdWav           sound3;         //xy=212,375
AudioPlaySdWav           sound2;         //xy=214,337
AudioPlaySdWav           sound1;         //xy=217,296
AudioPlaySdWav           sound0;         //xy=219,244
AudioMixer4              mixerFinal;     //xy=398,286
AudioEffectFreeverb      freeverb1;      //xy=614,248
AudioMixer4              mixerReverb;    //xy=860,295
AudioFilterBiquad        globalFilter;   //xy=1016,296
AudioAmplifier           master;         //xy=1170,298
AudioOutputI2S           audioOutput;    //xy=1354,303
AudioConnection          patchCord1(sound3, 0, mixerFinal, 3);
AudioConnection          patchCord2(sound2, 0, mixerFinal, 2);
AudioConnection          patchCord3(sound1, 0, mixerFinal, 1);
AudioConnection          patchCord4(sound0, 0, mixerFinal, 0);
AudioConnection          patchCord5(mixerFinal, 0, mixerReverb, 1);
AudioConnection          patchCord6(mixerFinal, freeverb1);
AudioConnection          patchCord7(freeverb1, 0, mixerReverb, 0);
AudioConnection          patchCord8(mixerReverb, globalFilter);
AudioConnection          patchCord9(globalFilter, master);
AudioConnection          patchCord10(master, 0, audioOutput, 0);
AudioConnection          patchCord11(master, 0, audioOutput, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=275,508
// GUItool: end automatically generated code



PWM pwm(17);

AudioPlaySdWav* players [4]  = { &sound0, &sound1, &sound2, &sound3 };
String fileNames[10] = { {}, {}, {}, {}, {}, {}, {}, {}, {}, {} };

int firstDrum = 0;
int lastDrum = 49;

Multiplexer2 mux;
int currentDrum = 2;

void setDrumKit(int which) { // rellena el array fileNames con los nombres de los archivos correspondientes
  // Serial.println("Seleccionado: " + (String)which);
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

void setup()   {
  Serial.begin(9600);
  AudioMemory(10);
  pwm.begin(true);
  mux.setPins(2,3,4,17,16);
  char arrayOfInputs2 [16]= {'p','p','p','p','p','p','p','p','d','d','d','d','d','d','d','d'};
  mux.createArrayOfInputs(arrayOfInputs2);


  sgtl5000_1.enable();
  sgtl5000_1.volume(0.9);

  SPI.setMOSI(7);
  SPI.setSCK(14);

  mixerFinal.gain(0,0.25);
  mixerFinal.gain(1,0.25);
  mixerFinal.gain(2,0.25);
  mixerFinal.gain(3,0.25);

  freeverb1.roomsize(0.5);
  freeverb1.damping(0.5);
  mixerReverb.gain(0,0.3); // disable revereb
  mixerReverb.gain(1,0.7);
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



int lastPlayed = 0;
AudioPlaySdWav* playingHihatOpened;
void playSound(int i, float velocity) {
  int str_len = fileNames[i].length() + 1;
  char finalFileName[20];
  fileNames[i].toCharArray(finalFileName, str_len);

  // Serial.println(finalFileName);
  
  // closed hh stops open hh
  if (i == 5) playingHihatOpened = players[lastPlayed];
  if (i == 6 && playingHihatOpened != NULL && playingHihatOpened->isPlaying()) playingHihatOpened->stop();

  mixerFinal.gain(lastPlayed, velocity); // velocity (max 0.25)
  players[lastPlayed]->play(finalFileName); // sound

  lastPlayed++;
  if (lastPlayed == 4) lastPlayed = 0;
  // Serial.println("Memoria usada: " + (String)AudioMemoryUsageMax());
}
long lastPwm;

long lastSoundPlayed = 0;
void loop()                     
{
  
  long valPwm = pwm.getValue();
  
  if (valPwm > 10) {

    if (!(lastPwm > valPwm-10 && lastPwm < valPwm+10)) {
      Serial.println("PWM:" + (String)valPwm);
      int whichSound = 1;
      if (valPwm > 0 && valPwm < 70)
        whichSound = 1;
      if (valPwm >= 70 && valPwm < 140)
        whichSound = 0;
      if (valPwm >= 140)
        whichSound = 6;
      Serial.println("Sound:" + (String)whichSound);
      playSound(whichSound, 0.1);
    }
  }

    lastPwm = valPwm;


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
