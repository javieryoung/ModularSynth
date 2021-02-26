// Teensy-Synth Part 4
// ADSR Test
// By Notes and Volts
// www.notesandvolts.com

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform2;      //xy=526,293
AudioSynthWaveform       waveform1;      //xy=530,234
AudioSynthNoisePink      pink1;          //xy=538,344
AudioMixer4              mixer1;         //xy=721,294
AudioEffectEnvelope      envelope1;      //xy=876,294
AudioOutputI2S           i2s1;           //xy=1037,301
AudioConnection          patchCord1(waveform2, 0, mixer1, 1);
AudioConnection          patchCord2(waveform1, 0, mixer1, 0);
AudioConnection          patchCord3(pink1, 0, mixer1, 2);
AudioConnection          patchCord4(mixer1, envelope1);
AudioConnection          patchCord5(envelope1, 0, i2s1, 0);
AudioConnection          patchCord6(envelope1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=709,396
// GUItool: end automatically generated code


// GLOBAL VARIABLES
byte globalNote = 0;
byte globalVelocity = 0;

const int pinButton = 14;
Bounce pushbutton = Bounce(pinButton, 10);  // 10 ms debounce

void setup() {
  Serial.begin(9600);
  AudioMemory(20);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.32);
  waveform1.begin(WAVEFORM_SAWTOOTH);
  waveform1.amplitude(0.75);
  waveform1.frequency(82.41);
  waveform1.pulseWidth(0.15);

  waveform2.begin(WAVEFORM_SAWTOOTH);
  waveform2.amplitude(0.75);
  waveform2.frequency(123);
  waveform2.pulseWidth(0.15);

  pink1.amplitude(1.0);

  mixer1.gain(0, 1.0);
  mixer1.gain(1, 1.0);
  mixer1.gain(2, 1.0);

  envelope1.attack(0);
  envelope1.decay(30);
  envelope1.sustain(1);
  envelope1.release(500);

  pinMode(pinButton, INPUT_PULLUP);
}


void loop() {
  if (pushbutton.update()) {
    if (pushbutton.fallingEdge()) {
      oscPlay();
      Serial.println(1);
    }
    if (pushbutton.risingEdge()) {
      oscStop();
      Serial.println(0);
    }
  }
}



void oscPlay() {
  waveform1.frequency(523.25);
  waveform2.frequency(659.25);
  waveform1.amplitude(0.75);
  waveform2.amplitude(0.75);
  pink1.amplitude(0.25);

  envelope1.noteOn();
}

void oscStop() {
  envelope1.noteOff();
}
