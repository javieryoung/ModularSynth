// Teensy-Synth Part 1 
// Basic test program
// By Notes and Volts
// www.notesandvolts.com

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=429,378
AudioOutputI2S           i2s1;           //xy=747,377
AudioConnection          patchCord1(waveform1, 0, i2s1, 0);
AudioConnection          patchCord2(waveform1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=588,480
// GUItool: end automatically generated code

const int buttonPin1 = 14;
const int buttonPin2 = 15;
const int buttonPin3 = 16;
Bounce pushbutton1 = Bounce(buttonPin1, 10);  // 10 ms debounce
Bounce pushbutton2 = Bounce(buttonPin2, 10);  // 10 ms debounce
Bounce pushbutton3 = Bounce(buttonPin3, 10);  // 10 ms debounce

void setup() {
  Serial.begin(9600);
  AudioMemory(20);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.32);
  waveform1.begin(WAVEFORM_SINE);
  waveform1.amplitude(0.75);
  waveform1.frequency(50);
  waveform1.pulseWidth(0.15);
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
}

void loop() {
  /*
 for(int freq = 50; freq <= 500; freq++){
  waveform1.frequency(freq);
  delay(10);
 }
 */
  if (pushbutton1.update()) {
    if (pushbutton1.fallingEdge()) {
      waveform1.frequency(150);
    }
  }
  if (pushbutton2.update()) {
    if (pushbutton2.fallingEdge()) {
      waveform1.frequency(200);
      Serial.println(1);
    }
  }
  if (pushbutton3.update()) {
    if (pushbutton3.fallingEdge()) {
      waveform1.frequency(250);
    }
  }

}
