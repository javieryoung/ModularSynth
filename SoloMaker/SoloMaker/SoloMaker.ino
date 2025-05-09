/* Encoder Library - TwoKnobs Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */

#include <Encoder.h>


#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform2;      //xy=87,148
AudioSynthWaveform       waveform8;      //xy=88,433
AudioSynthWaveform       waveform3;      //xy=89,193
AudioSynthWaveform       waveform6;      //xy=89,342
AudioSynthWaveform       waveform1;      //xy=90,101
AudioSynthWaveform       waveform4;      //xy=90,235
AudioSynthWaveform       waveform7;      //xy=90,388
AudioSynthWaveform       waveform5;      //xy=92,298
AudioEffectEnvelope      envelope8;      //xy=299,434
AudioEffectEnvelope      envelope5;      //xy=301,299
AudioEffectEnvelope      envelope7;      //xy=301,390
AudioEffectEnvelope      envelope6;      //xy=302,345
AudioEffectEnvelope      envelope1;      //xy=311,105
AudioEffectEnvelope      envelope2;      //xy=312,151
AudioEffectEnvelope      envelope4;      //xy=313,233
AudioEffectEnvelope      envelope3;      //xy=314,193
AudioMixer4              mixer1;         //xy=527,155
AudioMixer4              mixer2;         //xy=528,362
AudioMixer4              mixer3;         //xy=693,254
AudioFilterBiquad        biquad1;        //xy=849,247
AudioOutputI2S           audioOutput;    //xy=993,247
AudioConnection          patchCord1(waveform2, envelope2);
AudioConnection          patchCord2(waveform8, envelope8);
AudioConnection          patchCord3(waveform3, envelope3);
AudioConnection          patchCord4(waveform6, envelope6);
AudioConnection          patchCord5(waveform1, envelope1);
AudioConnection          patchCord6(waveform4, envelope4);
AudioConnection          patchCord7(waveform7, envelope7);
AudioConnection          patchCord8(waveform5, envelope5);
AudioConnection          patchCord9(envelope8, 0, mixer2, 3);
AudioConnection          patchCord10(envelope5, 0, mixer2, 0);
AudioConnection          patchCord11(envelope7, 0, mixer2, 2);
AudioConnection          patchCord12(envelope6, 0, mixer2, 1);
AudioConnection          patchCord13(envelope1, 0, mixer1, 0);
AudioConnection          patchCord14(envelope2, 0, mixer1, 1);
AudioConnection          patchCord15(envelope4, 0, mixer1, 3);
AudioConnection          patchCord16(envelope3, 0, mixer1, 2);
AudioConnection          patchCord17(mixer1, 0, mixer3, 0);
AudioConnection          patchCord18(mixer2, 0, mixer3, 1);
AudioConnection          patchCord19(mixer3, biquad1);
AudioConnection          patchCord20(biquad1, 0, audioOutput, 0);
AudioConnection          patchCord21(biquad1, 0, audioOutput, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=320,555
// GUItool: end automatically generated code



const float noteFreqs[128] = {27.5, 29.135, 30.868, 32.703, 34.648, 36.708, 38.891, 41.203, 43.654, 46.249, 48.999, 51.913, 55, 58.27, 61.735, 65.406, 69.296, 73.416, 77.782, 82.407, 87.307, 92.499, 97.999, 103.826, 110, 116.541, 123.471, 130.813, 138.591, 146.832, 155.563, 164.814, 174.614, 184.997, 195.998, 207.652, 220, 233.082, 246.942, 261.626, 277.183, 293.665, 311.127, 329.628, 349.228, 369.994, 391.995, 415.305, 440, 466.164, 493.883, 523.251, 554.365, 587.33, 622.254, 659.255, 698.456, 739.989, 783.991, 830.609, 880, 932.328, 987.767, 1046.502, 1108.731, 1174.659, 1244.508, 1318.51, 1396.913, 1479.978, 1567.982, 1661.219, 1760, 1864.655, 1975.533, 2093.005, 2217.461, 2349.318, 2489.016, 2637.02, 2793.826, 2959.955, 3135.963, 3322.438, 3520, 3729.31, 3951.066, 4186.009, 4434.922, 4698.636, 4978.032, 5274.041, 5587.652, 5919.911, 6271.927, 6644.875, 7040, 7458.62, 7902.133, 8372.018, 8869.844, 9397.273, 9956.063, 10548.08, 11175.3, 11839.82, 12543.85};
int scales [8][16] = {
  {12, 0}, // octaves
  {7, 5, 0 },  // octaves & fifths
  {4, 3, 5, 0},  // major triads
  {3, 4, 5, 0},  // minor triads
  {3, 2, 2, 5, 0},  // minor triads+
  {3, 2, 5, 2, 0},  // blues 1
  {7, 0},  // 5th cycle
  {3, 2, 2, 0},  // blues 2
};

int currentScale = 7;
int currentNote = 36;
int currentPositionInScale = 0;

Encoder knobLeft(2, 3);

AudioSynthWaveform* waveforms [8]  = { &waveform1, &waveform2, &waveform3, &waveform4, &waveform5, &waveform6, &waveform7, &waveform8 };
AudioEffectEnvelope* envelopes [8]  = { &envelope1, &envelope2, &envelope3, &envelope4, &envelope5, &envelope6, &envelope7, &envelope8 };

void setup() {
  AudioMemory(10);
  Serial.begin(9600);
  analogReadResolution(10); // Asegurar 10 bits de resolución (0-1023)
  analogReference(DEFAULT); // Usar 3.3V de referencia en Teensy 3.2

  setDelay(0);
  setAttack(1);
  setHold(200);
  setSustain(1.0);
  setRelease(500);

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

  mixer3.gain(0,0.5);
  mixer3.gain(1,0.5);
  mixer3.gain(2,0);
  mixer3.gain(3,0);
  beginWaveforms();
}


void beginWaveforms() {
  for (int i = 0; i <= 7; i++) {
    waveforms[i]->frequency(440);
    waveforms[i]->amplitude(1.0);
    waveforms[i]->begin(WAVEFORM_SQUARE);

  }
}



/// ENVELOPE
void setDelay(int milliseconds) {
  for (int i = 0; i <= 7; i++) {
    envelopes[i]->delay(milliseconds);
  }
}

void setAttack(int milliseconds) {
  for (int i = 0; i <= 7; i++) {
    envelopes[i]->attack(milliseconds);
  }
}
void setHold(int milliseconds) {
  for (int i = 0; i <= 7; i++) {
    envelopes[i]->hold(milliseconds);
  }
}
void setSustain(double level) {
  for (int i = 0; i <= 7; i++) {
    envelopes[i]->sustain(level);
  }
}
void setRelease(int milliseconds) {
  for (int i = 0; i <= 7; i++) {
    envelopes[i]->release(milliseconds);
  }
}

long positionLeft  = -999;
int lastRead = 0;

const int numSamples = 10;  // Número de lecturas a promediar

int getSmoothAnalogRead(int pin) {
    int sum = 0;
    for (int i = 0; i < numSamples; i++) {
        sum += analogRead(pin);
        delay(1);  // Pequeña pausa para evitar leer demasiado rápido
    }
    return sum / numSamples;
}


void loop() {
  int rawValue = getSmoothAnalogRead(14);
  float normalized = rawValue / 1023.0;
  Serial.print("FSR Value: ");
  Serial.println(normalized);
  float cutoffFreq = 100 + (20000 - 100) * (1.0 - normalized);
  biquad1.setLowpass(0, cutoffFreq, 2.0f);  
  lastRead = millis();


  long newLeft;

  newLeft = knobLeft.read();
  if (abs(newLeft - positionLeft) >= 4) {
    
    if (newLeft < positionLeft) {
      cambio(1);
    } else if (newLeft > positionLeft) {
      cambio(-1);
    }
    positionLeft = newLeft;
  }
}

void cambio(int direction) {

  currentPositionInScale += direction;
  if (currentPositionInScale == -1) {
    currentPositionInScale = sizeof(scales[currentScale]-2);
  }
  if (scales[currentScale][currentPositionInScale] == 0) {
    currentPositionInScale = 0;
  }
  Serial.println(currentPositionInScale);
  currentNote = currentNote + (scales[currentScale][currentPositionInScale] * direction);
  playSound(currentNote);
}

int lastPlayed = 0;
void playSound(int note) {
  waveforms[lastPlayed]->frequency(noteFreqs[note]);
  envelopes[lastPlayed]->noteOn();
  delay(20);
  envelopes[lastPlayed]->noteOff();
  lastPlayed++;
  if (lastPlayed == 8) lastPlayed = 0;
}