// Teensy-Synth Part 1
// Basic test program
// By Notes and Volts
// www.notesandvolts.com

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "LFO.h"

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=429,378
AudioOutputI2S           i2s1;           //xy=747,377
AudioConnection          patchCord1(waveform1, 0, i2s1, 0);
AudioConnection          patchCord2(waveform1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=588,480
// GUItool: end automatically generated code

const int vFrequencyPin = 14;

LFO lfo;

void setup() {
  Serial.begin(9600);
  AudioMemory(20);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.22);
  waveform1.begin(WAVEFORM_SINE);
  waveform1.amplitude(0.75);
  waveform1.frequency(500);
  waveform1.pulseWidth(0.15);
  lfo.setFrequencyPin(15);
}

void loop() {
  // Serial.println(potRead);

  float lfoRead = lfo.update() + 0.5;
  // Serial.println(lfoRead);
  waveform1.frequency(lfoRead * 1000);
}
