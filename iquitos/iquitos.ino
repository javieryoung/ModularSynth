#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>

#include "Multiplexer4.h"
#include "Input.h"
#include "Button.h"

// GUItool: begin automatically generated code
AudioSynthWaveform       FMwave;         //xy=597.5,705.5
AudioSynthWaveformModulated waveform1;      //xy=1140.5,428.5
AudioSynthWaveformModulated waveform2;      //xy=1140.5,477.5
AudioSynthWaveformModulated waveform3;      //xy=1140.5,523.5
AudioSynthWaveformModulated waveform4;      //xy=1140.5,572.5
AudioSynthWaveformModulated waveform5;      //xy=1141.5,631.5
AudioSynthWaveformModulated waveform6;      //xy=1141.5,679.5
AudioSynthWaveformModulated waveform7;      //xy=1141.5,726.5
AudioSynthWaveformModulated waveform8;      //xy=1141.5,774.5
AudioSynthWaveformModulated waveform9;      //xy=1142.5,827.5
AudioSynthWaveformModulated waveform10;     //xy=1142.5,876.5
AudioSynthWaveformModulated waveform11;     //xy=1142.5,922.5
AudioSynthWaveformModulated waveform12;     //xy=1142.5,971.5
AudioSynthWaveformModulated waveform13;     //xy=1143.5,1029.5
AudioSynthWaveformModulated waveform14;     //xy=1143.5,1078.5
AudioSynthWaveformModulated waveform15;     //xy=1143.5,1124.5
AudioSynthWaveformModulated waveform16;     //xy=1143.5,1173.5
AudioSynthWaveformModulated waveformPrincipal; //xy=1178.5,347.5
AudioEffectEnvelope      envelopeWaveform3; //xy=1331.5,526.5
AudioEffectEnvelope      envelopeWaveform4; //xy=1342.5,573.5
AudioEffectEnvelope      envelopeWaveform9; //xy=1342.5,821.5
AudioEffectEnvelope      envelopeWaveform2; //xy=1344.5,466.5
AudioEffectEnvelope      envelopeWaveform5; //xy=1351.5,631.5
AudioEffectEnvelope      envelopeWaveform11; //xy=1352.5,921.5
AudioEffectEnvelope      envelopeWaveform6; //xy=1353.5,683.5
AudioEffectEnvelope      envelopeWaveform1; //xy=1359.5,422.5
AudioEffectEnvelope      envelopeWaveform10; //xy=1359.5,872.5
AudioEffectEnvelope      envelopeWaveform7; //xy=1361.5,725.5
AudioEffectEnvelope      envelopeWaveform14; //xy=1367.5,1067.5
AudioEffectEnvelope      envelopeWaveform8; //xy=1369.5,767.5
AudioEffectEnvelope      envelopeWaveform12; //xy=1369.5,966.5
AudioEffectEnvelope      envelopeWaveform13; //xy=1378.5,1020.5
AudioEffectEnvelope      envelopeWaveform16; //xy=1378.5,1165.5
AudioEffectEnvelope      envelopeWaveform15; //xy=1384.5,1108.5
AudioEffectEnvelope      envelopePrincipal; //xy=1516.5,348.5
AudioMixer4              mixer1;         //xy=1745.5,517.5
AudioMixer4              mixer2;         //xy=1746.5,719.5
AudioMixer4              mixer3;         //xy=1748.5,916.5
AudioMixer4              mixer4;         //xy=1749.5,1118.5
AudioMixer4              mixerOscillators; //xy=2023.5,826.5
AudioMixer4              mixerFinal;     //xy=2288.500072479248,768.2500228881836
AudioAmplifier           amp1;           //xy=2517.50008392334,759.5000228881836
AudioOutputI2S           i2s1;           //xy=2702.0000915527344,760.5000219345093
AudioConnection          patchCord1(FMwave, 0, waveform1, 0);
AudioConnection          patchCord2(FMwave, 0, waveform2, 0);
AudioConnection          patchCord3(FMwave, 0, waveform3, 0);
AudioConnection          patchCord4(FMwave, 0, waveformPrincipal, 0);
AudioConnection          patchCord5(FMwave, 0, waveform4, 0);
AudioConnection          patchCord6(FMwave, 0, waveform5, 0);
AudioConnection          patchCord7(FMwave, 0, waveform6, 0);
AudioConnection          patchCord8(FMwave, 0, waveform7, 0);
AudioConnection          patchCord9(FMwave, 0, waveform8, 0);
AudioConnection          patchCord10(FMwave, 0, waveform9, 0);
AudioConnection          patchCord11(FMwave, 0, waveform10, 0);
AudioConnection          patchCord12(FMwave, 0, waveform11, 0);
AudioConnection          patchCord13(FMwave, 0, waveform12, 0);
AudioConnection          patchCord14(FMwave, 0, waveform13, 0);
AudioConnection          patchCord15(FMwave, 0, waveform14, 0);
AudioConnection          patchCord16(FMwave, 0, waveform15, 0);
AudioConnection          patchCord17(FMwave, 0, waveform16, 0);
AudioConnection          patchCord18(waveform1, envelopeWaveform1);
AudioConnection          patchCord19(waveform2, envelopeWaveform2);
AudioConnection          patchCord20(waveform3, envelopeWaveform3);
AudioConnection          patchCord21(waveform4, envelopeWaveform4);
AudioConnection          patchCord22(waveform5, envelopeWaveform5);
AudioConnection          patchCord23(waveform6, envelopeWaveform6);
AudioConnection          patchCord24(waveform7, envelopeWaveform7);
AudioConnection          patchCord25(waveform8, envelopeWaveform8);
AudioConnection          patchCord26(waveform9, envelopeWaveform9);
AudioConnection          patchCord27(waveform10, envelopeWaveform10);
AudioConnection          patchCord28(waveform11, envelopeWaveform11);
AudioConnection          patchCord29(waveform12, envelopeWaveform12);
AudioConnection          patchCord30(waveform13, envelopeWaveform13);
AudioConnection          patchCord31(waveform14, envelopeWaveform14);
AudioConnection          patchCord32(waveform15, envelopeWaveform15);
AudioConnection          patchCord33(waveform16, envelopeWaveform16);
AudioConnection          patchCord34(waveformPrincipal, envelopePrincipal);
AudioConnection          patchCord35(envelopeWaveform3, 0, mixer1, 2);
AudioConnection          patchCord36(envelopeWaveform4, 0, mixer1, 3);
AudioConnection          patchCord37(envelopeWaveform9, 0, mixer3, 0);
AudioConnection          patchCord38(envelopeWaveform2, 0, mixer1, 1);
AudioConnection          patchCord39(envelopeWaveform5, 0, mixer2, 0);
AudioConnection          patchCord40(envelopeWaveform11, 0, mixer3, 2);
AudioConnection          patchCord41(envelopeWaveform6, 0, mixer2, 1);
AudioConnection          patchCord42(envelopeWaveform1, 0, mixer1, 0);
AudioConnection          patchCord43(envelopeWaveform10, 0, mixer3, 1);
AudioConnection          patchCord44(envelopeWaveform7, 0, mixer2, 2);
AudioConnection          patchCord45(envelopeWaveform14, 0, mixer4, 1);
AudioConnection          patchCord46(envelopeWaveform8, 0, mixer2, 3);
AudioConnection          patchCord47(envelopeWaveform12, 0, mixer3, 3);
AudioConnection          patchCord48(envelopeWaveform13, 0, mixer4, 0);
AudioConnection          patchCord49(envelopeWaveform16, 0, mixer4, 3);
AudioConnection          patchCord50(envelopeWaveform15, 0, mixer4, 2);
AudioConnection          patchCord51(envelopePrincipal, 0, mixerFinal, 0);
AudioConnection          patchCord52(mixer1, 0, mixerOscillators, 0);
AudioConnection          patchCord53(mixer2, 0, mixerOscillators, 1);
AudioConnection          patchCord54(mixer3, 0, mixerOscillators, 2);
AudioConnection          patchCord55(mixer4, 0, mixerOscillators, 3);
AudioConnection          patchCord56(mixerOscillators, 0, mixerFinal, 1);
AudioConnection          patchCord57(mixerFinal, amp1);
AudioConnection          patchCord58(amp1, 0, i2s1, 0);
AudioConnection          patchCord59(amp1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=2083.5,1098.5
// GUItool: end automatically generated code








                            // A0
const float noteFreqs[128] = {27.5, 29.135, 30.868, 32.703, 34.648, 36.708, 38.891, 41.203, 43.654, 46.249, 48.999, 51.913, 55, 58.27, 61.735, 65.406, 69.296, 73.416, 77.782, 82.407, 87.307, 92.499, 97.999, 103.826, 110, 116.541, 123.471, 130.813, 138.591, 146.832, 155.563, 164.814, 174.614, 184.997, 195.998, 207.652, 220, 233.082, 246.942, 261.626, 277.183, 293.665, 311.127, 329.628, 349.228, 369.994, 391.995, 415.305, 440, 466.164, 493.883, 523.251, 554.365, 587.33, 622.254, 659.255, 698.456, 739.989, 783.991, 830.609, 880, 932.328, 987.767, 1046.502, 1108.731, 1174.659, 1244.508, 1318.51, 1396.913, 1479.978, 1567.982, 1661.219, 1760, 1864.655, 1975.533, 2093.005, 2217.461, 2349.318, 2489.016, 2637.02, 2793.826, 2959.955, 3135.963, 3322.438, 3520, 3729.31, 3951.066, 4186.009, 4434.922, 4698.636, 4978.032, 5274.041, 5587.652, 5919.911, 6271.927, 6644.875, 7040, 7458.62, 7902.133, 8372.018, 8869.844, 9397.273, 9956.063, 10548.08, 11175.3, 11839.82, 12543.85};
int buttons[16] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
Multiplexer4 multiplexer;
AudioSynthWaveformModulated* waveforms [16]  = { &waveform1, &waveform2, &waveform3, &waveform4, &waveform5, &waveform6, &waveform7, &waveform8, &waveform9, &waveform10, &waveform11, &waveform12, &waveform13, &waveform14, &waveform15, &waveform16 };
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
int baseFrequency = 36;
int totalVoices = 2;
int selectedScale = 7;
float swirl;
float highestFreq;
int fmMode = 0; // 0 FLO, 1 use oscillator
int randomSwirl = 0;
float detune = 0.0;

void setup() {
  AudioMemory(120);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.6);

  for (int i = 0; i < 16; i ++) {
    waveforms[i]->begin(waveformsShapes[i]);
    waveforms[i]->amplitude(1);
    waveforms[i]->frequencyModulation(1);

    envelopes[i]->attack(10);
    envelopes[i]->decay(1);
    envelopes[i]->sustain(1);
    envelopes[i]->release(10);
    
  }
  envelopePrincipal.attack(10);
  envelopePrincipal.decay(1);
  envelopePrincipal.sustain(1);
  envelopePrincipal.release(10);

  waveformPrincipal.begin(WAVEFORM_SINE);
  waveformPrincipal.amplitude(1);
  waveformPrincipal.frequencyModulation(1);

  FMwave.begin(WAVEFORM_SINE);
  FMwave.frequency(20);
  FMwave.amplitude(0);


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

  
  /*
  multiplexerInputs.setPins(4,5,8,16,17);
  char arrayOfInputs [16]= {'d','d','d','d','d','d','d','d','d','d','d','d','d','d','d','d'};
  multiplexerInputs.createArrayOfInputs(arrayOfInputs);
  */
  
  multiplexer.setPins(3,4,5,21,20,17,16);
  char arrayOfInputs2 [32]= {'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a'};
  arrayOfInputs2[31] = 'd';
  arrayOfInputs2[25] = 'd';
  arrayOfInputs2[29] = 'd';
  multiplexer.createArrayOfInputs(arrayOfInputs2);
  multiplexer.getObject(3)->setLimits(0,16); // voices
  multiplexer.getObject(4)->setLimits(0.00,1.00); // detune
  multiplexer.getObject(9)->setLimits(0.0,20.0); // fm frequency
  multiplexer.getObject(23)->setLimits(0.00,1.00); // root note
  multiplexer.getObject(17)->setLimits(0.0,1.0); // fm amplitude
  multiplexer.getObject(19)->setLimits(0.00,1.00); // balance
  multiplexer.getObject(22)->setLimits(0,8); // scale
  multiplexer.getObject(12)->setLimits(0.00,1.00); // master volume
  multiplexer.getObject(16)->setLimits(0.0,50.0); // swirl
  multiplexer.getObject(21)->setLimits(0,4); // fm waveshape
  multiplexer.getObject(23)->setLimits(0,6); // root note
  multiplexer.getObject(4)->setLimits(0.5,1.5); // detune
  multiplexer.getObject(0)->setLimits(0,340); // delay time

  /*  
  multiplexer.getObject(5)->setLimits(1,6);
  */

  Serial.println(1);
}

bool buttonState = 1.0;
void loop() {

  float results [32] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
  bool changed [32] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
  bool potsCompleted = multiplexer.read(results, changed);
  if (potsCompleted) {
    for (int i = 0; i < 32; i++ ){
      if (i != 28 && i != 7 && i != 2 && i != 30 && i != 15 && i != 24 && i != 5 && i != 1 && i != 13 && i != 27) {
      //if (true) {
        if (changed[i]){
          Serial.println(i);
        }
        if (i == 29 && changed[i] && buttonState != results[i]) {
          Serial.println("Boton");
          int usoMemoria = AudioMemoryUsageMax();
          Serial.println("Uso memoria: " + (String)usoMemoria);
          if (results[i] == 1.0)
            stopEnvelopes();
          else
            activateEnvelopes();
          buttonState = results[i];
        }
        if (changed[3]) {
          totalVoices = results[3];
          Serial.println("voices: " +  (String)totalVoices);
          changeFrequencies();
          activateEnvelopes();
        }

        if (changed[23]) {
          int rootNote = results[23];
          baseFrequency = 12 * rootNote;
          changeFrequencies();
          Serial.println("root note: " +  (String)rootNote);
        }

        if (changed[4]) {
          detune = results[4];
          Serial.println("detune: " +  (String)detune);
          changeFrequencies();
        }


        if (changed[19]) {
          float balance = results[19];
          mixerFinal.gain(0, 1.0 - balance);
          mixerFinal.gain(1, balance);
          Serial.println("balance: " +  (String)balance);
        }
        if (changed[22]) {
          selectedScale = results[22];
          Serial.println("selectedScale: " + (String)selectedScale);
          changeFrequencies();
        }

        // SWIRL
        if (changed[16]) {
          swirl = results[16];
          Serial.println("swirl: " +  (String)swirl);
        }
        if (changed[25]) {
          randomSwirl = results[25];
          Serial.println("random swirl: " +  (String)randomSwirl);
        }



        if (changed[12]) {
          float masterVolume = results[12];
          Serial.println("masterVolume: " + (String)masterVolume);
          amp1.gain(masterVolume);
        }

        // FM WAVE
        if (changed[17]) {
          float amplitude = results[17];
          Serial.println("amplitude fm: " +  (String)amplitude);
          FMwave.amplitude(amplitude);
        }

        if (changed[9]) {
          float freq = results[9];
          if (fmMode == 0)
            FMwave.frequency(freq); 
          else{
            float baseFreq = noteFreqs[baseFrequency];
            FMwave.frequency(baseFreq);
          }
          Serial.println("fm freq: " +  (String)freq);
          
        }
        if (changed[31]) {
          fmMode = results[31];
          Serial.println("fmMode: " +  (String)fmMode);
        }
        if (changed[0]) {
          int delay = results[0];
          //delay1.delay(1, delay);
          Serial.println("delay: " +  (String)delay);
        }
        if (changed[21]) {
          int fmWaveform = results[21];
          int t = WAVEFORM_SINE;
          switch (fmWaveform){
          case 0:
            t = WAVEFORM_SINE;
            break;
          case 1:
            t = WAVEFORM_SAWTOOTH;
            break;
          case 2:
            t = WAVEFORM_SAWTOOTH_REVERSE;
            break;
          case 3:
            t = WAVEFORM_SQUARE;
            break;
          case 4:
            t = WAVEFORM_TRIANGLE;
            break;
          
          default:
            t = WAVEFORM_SINE;
            break;
          }

          Serial.println("SM input: " + (String) fmWaveform);
          Serial.println("SM waveform: " + (String)t);
          FMwave.begin(t);
        }
      }
    }
    /*
    if (changedPots[1]) {
      float masterVolume = resultPots[1];
      Serial.println("masterVolume: " + (String)masterVolume);
      amp1.gain(masterVolume);
    }

    if (changedPots[5]) {
      int type = resultPots[5];
      int t = WAVEFORM_SINE;
      switch(type) {
        case 1:
          t = WAVEFORM_SINE;
          break;
        case 2:
          t = WAVEFORM_SAWTOOTH;
          break;
        case 3:
          t = WAVEFORM_SAWTOOTH_REVERSE;
          break;
        case 4:
          t = WAVEFORM_SQUARE;
          break;
        case 5:
          t = WAVEFORM_SINE;
          break;
      }
      Serial.println("freq wave: " +  (String)type);
      FMwave.begin(t);
    }
    if (changedPots[7]) {
      float amplitude = resultPots[7];
      Serial.println("amplitude fm: " +  (String)amplitude);
      FMwave.amplitude(amplitude);
    }
    */
  }
  
  

/*
  bool changedButtons [16] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
  float result [16] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
  bool completed = multiplexerInputs.read(result, changedButtons);
  if (completed) {
  bool anyOn = false;
    for (int i = 0; i < 16; i++) {
      // NOTES
      if (i < 12) {
        if (result[i] == 1.0) {
          if (buttons[i] == 0.0) {
            playNote(i);
            Serial.println("note: " + (String)i);
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
      if (changedButtons[i] && i == 13) {
        if (result[i] == 1) {
          fmMode = 0;
          Serial.println("A on");
        } else {
          fmMode = 1;
          Serial.println("A off");
        }
      }
      if (changedButtons[i] && i == 12) {
        if (result[i] == 1)
          Serial.println("B on");
        else
          Serial.println("B off");
      }
        
      buttons[i] = result[i];
    }
    if (!anyOn) {
      stopNote();
    }
  }
  */

}


void changeFrequencies() {
  int indexInScale = 0;
  int avance = 0;
  waveformPrincipal.frequency(noteFreqs[baseFrequency] * detune);
  for (int i = 0; i < 16; i++) {
    avance += scales[selectedScale][indexInScale];
    int freqIndex = baseFrequency + avance;
    float freq = noteFreqs[freqIndex];
    indexInScale++;
    if (scales[selectedScale][indexInScale] == 0) {
      indexInScale = 0;
    }
    waveforms[i]->frequency(freq * detune);
    if (i == 15) 
      highestFreq = freq;
    if (envelopePrincipal.isSustain()) {
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
      int rand = randomSwirl ? random(0,100) : i * 10;
      envelopes[i]->delay(swirl * ( rand ));
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
