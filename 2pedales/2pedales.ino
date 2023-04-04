#include "Input.h"
#include "Button.h"
#include "Pot.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=402,359
AudioFilterStateVariable filter1;        //xy=635,343
AudioEffectFreeverb      freeverb1;      //xy=803,289
AudioMixer4              mixer1;         //xy=944,335
AudioOutputI2S           i2s2;           //xy=1109,357
AudioConnection          patchCord1(i2s1, 0, filter1, 0);
AudioConnection          patchCord2(filter1, 0, freeverb1, 0);
AudioConnection          patchCord3(filter1, 0, mixer1, 1);
AudioConnection          patchCord4(freeverb1, 0, mixer1, 0);
AudioConnection          patchCord5(mixer1, 0, i2s2, 0);
AudioConnection          patchCord6(mixer1, 0, i2s2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=639,483
// GUItool: end automatically generated code


Pot pot1;
Pot pot2;

void setup() {
  Serial.begin(9600);
  AudioMemory(10);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.6);

  mixer1.gain(0,0);
  mixer1.gain(1,1);
  mixer1.gain(2,0);
  mixer1.gain(3,0);
  
  pot2.setPin(32);
  pot1.setPin(33);

  freeverb1.roomsize(0.7);
  freeverb1.damping(0.5);

  filter1.frequency(4000);
  filter1.resonance(3.5);
}

double wet = 0.1;
int sign = 1;
void loop() {

  if (pot1.changed()) {
    Serial.println(pot1.read());
    double read = pot1.read() * 0.9;
    mixer1.gain(0,read);
    mixer1.gain(1,1.0-read);
  }
  if (pot2.changed()) {
    filter1.frequency(4400 - (pot2.read() * 2400));
  }
}

