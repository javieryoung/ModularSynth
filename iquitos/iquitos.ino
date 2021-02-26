#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>

#include "Multiplexer2.h"
#include "Input.h"
#include "Button.h"



// GUItool: begin automatically generated code
AudioSynthWaveformModulated waveformMod1;   //xy=802,559
AudioSynthWaveform       waveform1;      //xy=1061.8055725097656,253.38889122009277
AudioSynthWaveform       waveform2;      //xy=1061.8055725097656,302.3888912200928
AudioSynthWaveform       waveform3;      //xy=1061.8055725097656,348.3888912200928
AudioSynthWaveform       waveform4;      //xy=1061.8055725097656,397.3888912200928
AudioSynthWaveform       waveform5;      //xy=1062.8055725097656,456.3888912200928
AudioSynthWaveform       waveform6;      //xy=1062.8055725097656,504.3888912200928
AudioSynthWaveform       waveform7;      //xy=1062.8055725097656,551.3888912200928
AudioSynthWaveform       waveform8;      //xy=1062.8055725097656,599.3888912200928
AudioSynthWaveform       waveform9;      //xy=1063.8055725097656,652.3888912200928
AudioSynthWaveform       waveform10;     //xy=1063.8055725097656,701.3888912200928
AudioSynthWaveform       waveform11;     //xy=1063.8055725097656,747.3888912200928
AudioSynthWaveform       waveform12;     //xy=1063.8055725097656,796.3888912200928
AudioSynthWaveform       waveform13;     //xy=1064.8055725097656,854.3888912200928
AudioSynthWaveform       waveform14;     //xy=1064.8055725097656,903.3888912200928
AudioSynthWaveform       waveform15;     //xy=1064.8055725097656,949.3888912200928
AudioSynthWaveform       waveform16;     //xy=1064.8055725097656,998.3888912200928
AudioEffectEnvelope      envelopeWaveform3; //xy=1252.0555725097656,351.38888931274414
AudioEffectEnvelope      envelopeWaveform4; //xy=1263.3055725097656,398.88888931274414
AudioEffectEnvelope      envelopeWaveform9; //xy=1263.3055725097656,646.388858795166
AudioEffectEnvelope      envelopeWaveform2; //xy=1265.8055725097656,291.38888931274414
AudioEffectEnvelope      envelopeWaveform5; //xy=1272.0555725097656,456.38888931274414
AudioEffectEnvelope      envelopeWaveform11; //xy=1273.3055725097656,746.388858795166
AudioEffectEnvelope      envelopeWaveform6; //xy=1274.5555725097656,508.888858795166
AudioEffectEnvelope      envelopeWaveform1; //xy=1280.8055725097656,247.63888931274414
AudioEffectEnvelope      envelopeWaveform10; //xy=1280.8055725097656,697.638858795166
AudioEffectEnvelope      envelopeWaveform7; //xy=1282.0555725097656,550.138858795166
AudioEffectEnvelope      envelopeWaveform14; //xy=1288.3055725097656,892.638858795166
AudioEffectEnvelope      envelopeWaveform8; //xy=1290.8055725097656,592.638858795166
AudioEffectEnvelope      envelopeWaveform12; //xy=1290.8055725097656,791.388858795166
AudioEffectEnvelope      envelopeWaveform13; //xy=1299.5555725097656,845.138858795166
AudioEffectEnvelope      envelopeWaveform16; //xy=1299.5555725097656,990.138858795166
AudioEffectEnvelope      envelopeWaveform15; //xy=1305.8055725097656,933.888858795166
AudioMixer4              mixer1;         //xy=1666.5555686950684,342.13888931274414
AudioMixer4              mixer2;         //xy=1667.5555686950684,544.1388893127441
AudioMixer4              mixer3;         //xy=1669.5555686950684,741.1388893127441
AudioMixer4              mixer4;         //xy=1670.5555686950684,943.1388893127441
AudioSynthWaveform       waveformPrincipal;     //xy=1896,504
AudioMixer4              mixerOscillators;     //xy=1944.5555686950684,651.1388893127441
AudioEffectEnvelope      envelopePrincipal;      //xy=2006,581
AudioMixer4              mixerFinal;         //xy=2169,636
AudioAmplifier           amp1;           //xy=2508.305347442627,629.3888397216797
AudioOutputI2S           i2s1;           //xy=2655.555564880371,640.1388959884644
AudioConnection          patchCord1(waveform1, envelopeWaveform1);
AudioConnection          patchCord2(waveform2, envelopeWaveform2);
AudioConnection          patchCord3(waveform3, envelopeWaveform3);
AudioConnection          patchCord4(waveform4, envelopeWaveform4);
AudioConnection          patchCord5(waveform5, envelopeWaveform5);
AudioConnection          patchCord6(waveform6, envelopeWaveform6);
AudioConnection          patchCord7(waveform7, envelopeWaveform7);
AudioConnection          patchCord8(waveform8, envelopeWaveform8);
AudioConnection          patchCord9(waveform9, envelopeWaveform9);
AudioConnection          patchCord10(waveform10, envelopeWaveform10);
AudioConnection          patchCord11(waveform11, envelopeWaveform11);
AudioConnection          patchCord12(waveform12, envelopeWaveform12);
AudioConnection          patchCord13(waveform13, envelopeWaveform13);
AudioConnection          patchCord14(waveform14, envelopeWaveform14);
AudioConnection          patchCord15(waveform15, envelopeWaveform15);
AudioConnection          patchCord16(waveform16, envelopeWaveform16);
AudioConnection          patchCord17(envelopeWaveform3, 0, mixer1, 2);
AudioConnection          patchCord18(envelopeWaveform4, 0, mixer1, 3);
AudioConnection          patchCord19(envelopeWaveform9, 0, mixer3, 0);
AudioConnection          patchCord20(envelopeWaveform2, 0, mixer1, 1);
AudioConnection          patchCord21(envelopeWaveform5, 0, mixer2, 0);
AudioConnection          patchCord22(envelopeWaveform11, 0, mixer3, 2);
AudioConnection          patchCord23(envelopeWaveform6, 0, mixer2, 1);
AudioConnection          patchCord24(envelopeWaveform1, 0, mixer1, 0);
AudioConnection          patchCord25(envelopeWaveform10, 0, mixer3, 1);
AudioConnection          patchCord26(envelopeWaveform7, 0, mixer2, 2);
AudioConnection          patchCord27(envelopeWaveform14, 0, mixer4, 1);
AudioConnection          patchCord28(envelopeWaveform8, 0, mixer2, 3);
AudioConnection          patchCord29(envelopeWaveform12, 0, mixer3, 3);
AudioConnection          patchCord30(envelopeWaveform13, 0, mixer4, 0);
AudioConnection          patchCord31(envelopeWaveform16, 0, mixer4, 3);
AudioConnection          patchCord32(envelopeWaveform15, 0, mixer4, 2);
AudioConnection          patchCord33(mixer1, 0, mixerOscillators, 0);
AudioConnection          patchCord34(mixer2, 0, mixerOscillators, 1);
AudioConnection          patchCord35(mixer3, 0, mixerOscillators, 2);
AudioConnection          patchCord36(mixer4, 0, mixerOscillators, 3);
AudioConnection          patchCord37(waveformPrincipal, envelopePrincipal);
AudioConnection          patchCord38(mixerOscillators, 0, mixerFinal, 1);
AudioConnection          patchCord39(envelopePrincipal, 0, mixerFinal, 0);
AudioConnection          patchCord40(mixerFinal, amp1);
AudioConnection          patchCord41(amp1, 0, i2s1, 0);
AudioConnection          patchCord42(amp1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=2004.5555686950684,923.1388893127441
// GUItool: end automatically generated code




                            // A0
const float noteFreqs[128] = {27.5, 29.135, 30.868, 32.703, 34.648, 36.708, 38.891, 41.203, 43.654, 46.249, 48.999, 51.913, 55, 58.27, 61.735, 65.406, 69.296, 73.416, 77.782, 82.407, 87.307, 92.499, 97.999, 103.826, 110, 116.541, 123.471, 130.813, 138.591, 146.832, 155.563, 164.814, 174.614, 184.997, 195.998, 207.652, 220, 233.082, 246.942, 261.626, 277.183, 293.665, 311.127, 329.628, 349.228, 369.994, 391.995, 415.305, 440, 466.164, 493.883, 523.251, 554.365, 587.33, 622.254, 659.255, 698.456, 739.989, 783.991, 830.609, 880, 932.328, 987.767, 1046.502, 1108.731, 1174.659, 1244.508, 1318.51, 1396.913, 1479.978, 1567.982, 1661.219, 1760, 1864.655, 1975.533, 2093.005, 2217.461, 2349.318, 2489.016, 2637.02, 2793.826, 2959.955, 3135.963, 3322.438, 3520, 3729.31, 3951.066, 4186.009, 4434.922, 4698.636, 4978.032, 5274.041, 5587.652, 5919.911, 6271.927, 6644.875, 7040, 7458.62, 7902.133, 8372.018, 8869.844, 9397.273, 9956.063, 10548.08, 11175.3, 11839.82, 12543.85};
int buttons[16] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
Multiplexer2 multiplexerInputs;
Multiplexer2 multiplexerPots;
AudioSynthWaveform* waveforms [16]  = { &waveform1, &waveform2, &waveform3, &waveform4, &waveform5, &waveform6, &waveform7, &waveform8, &waveform9, &waveform10, &waveform11, &waveform12, &waveform13, &waveform14, &waveform15, &waveform16 };
AudioEffectEnvelope* envelopes [16]  = { &envelopeWaveform1, &envelopeWaveform2, &envelopeWaveform3, &envelopeWaveform4, &envelopeWaveform5, &envelopeWaveform6, &envelopeWaveform7, &envelopeWaveform8, &envelopeWaveform9, &envelopeWaveform10, &envelopeWaveform11, &envelopeWaveform12, &envelopeWaveform13, &envelopeWaveform14, &envelopeWaveform15, &envelopeWaveform16 };
int waveformsShapes [16] = { WAVEFORM_SINE, WAVEFORM_SINE, WAVEFORM_SINE, WAVEFORM_SINE, WAVEFORM_SINE, WAVEFORM_SINE, WAVEFORM_SINE, WAVEFORM_SINE, WAVEFORM_SINE, WAVEFORM_SINE, WAVEFORM_SINE, WAVEFORM_SINE, WAVEFORM_SINE, WAVEFORM_SINE, WAVEFORM_SINE, WAVEFORM_SINE };
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

int octave = 3;
int baseFrequency = 24;
int totalVoices = 2;
int selectedScale = 7;
float swirl;

void setup() {
  AudioMemory(20);
  analogReference(DEFAULT);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);

  for (int i = 0; i < 16; i ++) {
    waveforms[i]->begin(waveformsShapes[i]);
    waveforms[i]->pulseWidth(0.15);
    waveforms[i]->amplitude(1);

    envelopes[i]->attack(1);
    envelopes[i]->decay(1);
    envelopes[i]->sustain(1);
    envelopes[i]->release(1);
    
  }
  envelopePrincipal.attack(1);
  envelopePrincipal.decay(1);
  envelopePrincipal.sustain(1);
  envelopePrincipal.release(1);

  waveformPrincipal.begin(WAVEFORM_SINE);
  waveformPrincipal.pulseWidth(0.15);
  waveformPrincipal.amplitude(1);

  mixer1.gain(0, 0.40);
  mixer1.gain(1, 0.30);
  mixer1.gain(2, 0.20);
  mixer1.gain(3, 0.10);

  mixer2.gain(0, 0.40);
  mixer2.gain(1, 0.30);
  mixer2.gain(2, 0.20);
  mixer2.gain(3, 0.10);

  mixer3.gain(0, 0.40);
  mixer3.gain(1, 0.30);
  mixer3.gain(2, 0.20);
  mixer3.gain(3, 0.10);

  mixer4.gain(0, 0.40);
  mixer4.gain(1, 0.30);
  mixer4.gain(2, 0.20);
  mixer4.gain(3, 0.10);

  mixerOscillators.gain(0, 0.40);
  mixerOscillators.gain(1, 0.30);
  mixerOscillators.gain(2, 0.20);
  mixerOscillators.gain(3, 0.10);

  mixerFinal.gain(0, 0.5);
  mixerFinal.gain(1, 0.5);
  mixerFinal.gain(2, 0);
  mixerFinal.gain(3, 0);

  
  
  multiplexerInputs.setPins(4,5,8,16,17);
  char arrayOfInputs [16]= {'d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d'};
  multiplexerInputs.createArrayOfInputs(arrayOfInputs);

  multiplexerPots.setPins(0,1,2,21,20);
  char arrayOfInputs2 [16]= {'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a'};
  multiplexerPots.createArrayOfInputs(arrayOfInputs2);
  multiplexerPots.getObject(0)->setLimits(0,15);
  multiplexerPots.getObject(1)->setLimits(0.00,1.00);
  multiplexerPots.getObject(2)->setLimits(0,8);
  multiplexerPots.getObject(3)->setLimits(0.00,1.00);
  multiplexerPots.getObject(4)->setLimits(0.0,5.0);

  Serial.println(1);
}

void loop() {

  float resultPots [16] = {1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00, 1024.00 };
  bool changedPots [16] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
  multiplexerPots.read(resultPots, changedPots);
  if (changedPots[0]) {
    totalVoices = resultPots[0];
    Serial.println(totalVoices);
    changeFrequencies();
    activateEnvelopes();
  }
  if (changedPots[1]) {
    float masterVolume = resultPots[1];
    amp1.gain(masterVolume);
  }
  if (changedPots[2]) {
    selectedScale = resultPots[2];
    Serial.println("selectedScale: " + (String)selectedScale);
    changeFrequencies();
  }
  if (changedPots[3]) {
    float balance = resultPots[3];
    mixerFinal.gain(0, 1.0 - balance);
    mixerFinal.gain(1, balance);
    Serial.println("balance: " +  (String)balance);
  }
  if (changedPots[4]) {
    swirl = resultPots[4];
    Serial.println("swirl: " +  (String)swirl);
  }

  bool changedButtons [16] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
  float result [16] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
  multiplexerInputs.read(result, changedButtons);
  bool anyOn = false;
  for (int i = 0; i < 16; i++) {
    // NOTES
    if (i < 12) {
      if (result[i] == 1.0) {
        if (buttons[i] == 0.0) {
          playNote(i);
        }
        anyOn = true;
      }
    }

    // OCTAVES
    if (result[i] == 1.0 && buttons[i] == 0.0) {
      if (i == 15) {
        octave --;
      }
      if (i == 14) {
        octave ++;
      }
    }
 
    // SWITCHES
      
    buttons[i] = result[i];
  }
  if (!anyOn) {
    stopNote();
  }


}


void changeFrequencies() {
  int indexInScale = 0;
  int avance = 0;
  waveformPrincipal.frequency(noteFreqs[baseFrequency]);
  for (int i = 0; i < 16; i++) {
    avance += scales[selectedScale][indexInScale];
    int freqIndex = baseFrequency + avance;
    float freq = noteFreqs[freqIndex];
    indexInScale++;
    if (scales[selectedScale][indexInScale] == 0) {
      indexInScale = 0;
    }
    waveforms[i]->frequency(freq);
    if (envelopePrincipal.isActive()) {
      activateEnvelopes();
    }
  }
}

void activateEnvelopes() {
  if (!envelopePrincipal.isActive()) {
    envelopePrincipal.noteOn();
  }
  for (int i = 0; i < totalVoices; i++) {
    if (!envelopes[i]->isActive()){
      envelopes[i]->delay(swirl * random(0,600));
      envelopes[i]->noteOn();
    }
  }
  for (int i = totalVoices; i < 16; i++) 
    envelopes[i]->noteOff();
}



void stopEnvelopes() {
  if (envelopePrincipal.isActive())
    envelopePrincipal.noteOff();
  for (int i = 0; i < 16; i++) {
    if (envelopes[i]->isActive()){
      envelopes[i]->noteOff();
    }
  }
}

void playNote(int note) {
  baseFrequency = note + (octave * 12);
  changeFrequencies();
  activateEnvelopes();
}

void stopNote() {
  stopEnvelopes();
}
