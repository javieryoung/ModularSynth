

#include "SPI.h"
#include "ILI9341_t3.h"
#include <XPT2046_Touchscreen.h>
#include <Encoder.h>


#include "Sine.h"
#include "SawTooth.h"
#include "Square.h"
#include "Triangle.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=142,351
AudioEffectWaveshaper    waveshape;      //xy=336,295
AudioMixer4              mixer;          //xy=716,347
AudioOutputI2S           i2sOut;         //xy=912,346
AudioConnection          patchCord1(i2s1, 0, waveshape, 0);
AudioConnection          patchCord2(i2s1, 0, mixer, 1);
AudioConnection          patchCord3(waveshape, 0, mixer, 0);
AudioConnection          patchCord4(mixer, 0, i2sOut, 0);
AudioConnection          patchCord5(mixer, 0, i2sOut, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1064,339
// GUItool: end automatically generated code



#define TFT_DC      20
#define TFT_CS      21
#define TFT_RST    255 
#define TFT_MOSI     7
#define TFT_SCLK    14
#define TFT_MISO    12
ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_MISO);

#define CS_PIN  8
XPT2046_Touchscreen ts(CS_PIN); 

Encoder encoderLeft(1, 3);
Encoder encoderRight(4, 5);

long positionLeft  = -999;
long positionRight = -999;
long _lastUpdate = 0;

void setup() {
  AudioMemory(32);
  sgtl5000_1.enable();
  // sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  sgtl5000_1.volume(0.5);
  

  SPI.setMOSI(7);
  SPI.setSCK(14);
  tft.begin();
  tft.setRotation(3);


  while(!ts.begin()) {
    Serial.print("No se inicio");
  }
  ts.setRotation(3);

  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_YELLOW);
  tft.setTextSize(2);

  // 240x320 Pixels
  tft.setCursor(35, 200);
  tft.setTextColor(0xFFFF);
  tft.print("Wave");
  
  tft.setCursor(210, 200);
  tft.setTextColor(0xFFFF);
  tft.print("DryWet");
  
  mixer.gain(0,0.5);
  mixer.gain(1,0.5);
  mixer.gain(2,0);
  mixer.gain(3,0);

  waveshape.shape(Sine, 257);
}


int currentWave = 0;
int dryWet = 10;
String waveNames[4] = { 
  "  Sine  ", 
  "SawTooth", 
  " Square ", 
  "Triangle"
};
void writeWave() {
  tft.fillRect(5, 220, 110, 150, 0xFFFF);
  tft.setCursor(12, 222);
  tft.setTextColor(0x0000);
  tft.print(waveNames[currentWave]);
}
void selectWave(int d) {
  currentWave += d;
  if (currentWave == 4) currentWave = 0;
  if (currentWave == -1) currentWave = 3;
  writeWave();
  if (currentWave == 0)
    waveshape.shape(Sine, 257);
  if (currentWave == 1)
    waveshape.shape(SawTooth, 257);
  if (currentWave == 2)
    waveshape.shape(Square, 257);
  if (currentWave == 3)
    waveshape.shape(Triangle, 257);
}

void writeDryWet() {
  tft.fillRect(225, 220, 50, 150, 0xFFFF);
  tft.setCursor(240, 222);
  tft.setTextColor(0x0000);
  tft.print(dryWet);
}

void setDryWet(int d) {
  dryWet += d;
  if (dryWet > 100) dryWet = 100;
  if (dryWet < 0) dryWet = 0;
  mixer.gain(0,(dryWet / 100.0)); // wet
  mixer.gain(1,((100.0 - dryWet) / 100.0)); // dry

  writeDryWet();
}

void loop(void) {
  if (ts.touched()) {
    TS_Point p = ts.getPoint();
  
    Serial.print("X = "); Serial.print(p.x);
    Serial.print("\tY = "); Serial.print(p.y);
    Serial.print("\tPressure = "); Serial.println(p.z);  
  }
  long nowInMillis = millis();
  if (nowInMillis - _lastUpdate > 50) {
    _lastUpdate = millis();
    long newLeft, newRight;
    newLeft = encoderLeft.read();
    if (newLeft != positionLeft) {
      if(newLeft < positionLeft) {
        selectWave(1);
        // tft.println("Left >");
      } else {
        selectWave(-1);
        // tft.println("Left <");
      }
      positionLeft = newLeft;
    }
    newRight = encoderRight.read();
    if (newRight != positionRight) {
      if(newRight < positionRight) {
        setDryWet(1);
        // tft.println("Right >");
      } else {
        setDryWet(-1);
        // tft.println("Right <");
      }
      positionRight = newRight;
    }
  }
  
}
