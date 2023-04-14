#define PRIMARY 0xFFFF
#define BLACK 0x0000
#define SCREEN_WIDTH 320
#define TEXT_HEIGHT 14

#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <Fonts/FreeSans9pt7b.h>

#include "SPI.h"
#include <XPT2046_Touchscreen.h>
#include <Encoder.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s2;           //xy=234,362
AudioAmplifier           inputLeft;           //xy=405,318
AudioAmplifier           inputRight;           //xy=409,369
AudioAmplifier           outputLeft;           //xy=690,311
AudioAmplifier           outputRight;           //xy=704,366
AudioOutputI2S           i2s1;           //xy=907,341
AudioConnection          patchCord1(i2s2, 0, inputLeft, 0);
AudioConnection          patchCord2(i2s2, 1, inputRight, 0);
AudioConnection          patchCord3(outputLeft, 0, i2s1, 0);
AudioConnection          patchCord4(outputRight, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=902,271
// GUItool: end automatically generated code



#define PI 3.1415926535897932384626433832795

#include "functions.h"



#include "classes/LinkedList.h"
#include "classes/Screen/Screen.h"
#include "classes/Screen/Input/Input.h"
#include "classes/Screen/Input/Knob.h"
#include "classes/Screen/Input/Menu.h"
#include "classes/Screen/Input/TwoKnobs.h"

#include "classes/EffectChain/EffectChain.h"
#include "classes/EffectChain/Effect/EffectReverb.h"

#include "classes/EffectChain/EffectChain.cpp"
#include "classes/EffectChain/Effect/EffectReverb.cpp"

#include "classes/Modular/Modular.h"


#include "waves/Sine.h"
#include "waves/SawTooth.h"
#include "waves/Square.h"
#include "waves/Triangle.h"

#include <Bounce.h>
const int buttonPinLeft = 17;
const int buttonPinRight = 16;
Bounce buttonLeft = Bounce(buttonPinLeft, 10);
Bounce buttonRight = Bounce(buttonPinRight, 10);

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>


// TEENSY 3.2
#define TFT_DC      20
#define TFT_CS      21
#define CS_PIN  8
Encoder encoderLeft(1, 3);
Encoder encoderRight(4, 5);

/*
// TEENSY 4.0
#define TFT_DC      9
#define TFT_CS      14
#define CS_PIN  5
Encoder encoderLeft(1, 0);
Encoder encoderRight(4, 22);
*/



#define TFT_RST    255 
#define TFT_MOSI     7
#define TFT_SCLK    14
#define TFT_MISO    12


XPT2046_Touchscreen ts(CS_PIN); 


// ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_MISO);
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);


double _lastUpdate = 0;
// Screen* currentScreen;

float notes[142] = { 16.35, 17.32, 17.32, 18.35, 19.45, 19.45, 20.60, 21.83, 23.12, 23.12, 24.50, 25.96, 25.96, 27.50, 29.14, 29.14, 30.87, 32.70, 34.65, 34.65, 36.71, 38.89, 38.89, 41.20, 43.65, 46.25, 46.25, 49.00, 51.91, 51.91, 55.00, 58.27, 58.27, 61.74, 65.41, 69.30, 69.30, 73.42, 77.78, 77.78, 82.41, 87.31, 92.50, 92.50, 98.00,103.83,103.83,110.00,116.54,116.54,123.47,130.81,138.59,138.59,146.83,155.56,155.56,164.81,174.61,185.00,185.00,196.00,207.65,207.65,220.00,233.08,233.08,246.94,261.63,277.18,277.18,293.66,311.13,311.13,329.63,349.23,369.99,369.99,392.00,415.30,415.30,440.00,466.16,466.16,493.88,523.25,554.37,554.37,587.33,622.25,622.25,659.26,698.46,739.99,739.99,783.99,830.61,830.61,880.00,932.33,932.33,987.77,046.50,108.73,108.73,174.66,244.51,244.51,318.51,396.91,479.98,479.98,567.98,661.22,661.22,760.00,864.66,864.66,975.53,093.00,217.46,217.46,349.32,489.02,489.02,637.02,793.83,959.96,959.96,135.96,322.44,322.44,520.00,729.31,729.31,951.07,186.01,434.92,434.92,698.64,978.03,978.03 };
int currentNote = 70;
Modular * m;

void setup() {
  AudioMemory(64);
  
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);

  pinMode(buttonPinLeft, INPUT_PULLUP);
  pinMode(buttonPinRight, INPUT_PULLUP);

  SPI.setMOSI(7);
  SPI.setSCK(14);
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(BLACK);
  tft.setTextSize(0.1);
  tft.setFont(&FreeSans9pt7b);

  while(!ts.begin()) {
    Serial.print("No se inicio");
  }
  ts.setRotation(3);
  outputLeft.gain(1);
  outputRight.gain(1);
  m = new Modular(&outputRight);

}


int positionLeft = 0;
int positionRight = 0;

void loop(void) {
  
  if (buttonLeft.update()) {
    if (buttonLeft.fallingEdge()) {
      // currentScreen->clicked("left");
    }
  } 
  if (buttonRight.update()) {
    if (buttonRight.fallingEdge()) {
      // currentScreen->clicked("right");
    }
  } 
  
  
  if (ts.touched()) {
    TS_Point p = ts.getPoint();
  

    // CALIBRATED
    float topLeftX = 3792;
    float topLeftY = 3873;
    float bottomRightX = 164;
    float bottomRightY = 208;


    float px = (1 - (p.x-bottomRightX) / (topLeftX-bottomRightX)) * 320;
    float py = (1 - (p.y-bottomRightY) / (topLeftY-bottomRightY)) * 240;
    
    Serial.print("X = "); Serial.print(px);
    Serial.print("\tY = "); Serial.println(py);
    
    
    // currentScreen->touched(px, py, p.z);
  }
  long nowInMillis = millis();
  if (nowInMillis - _lastUpdate > 100) {
    _lastUpdate = millis();
    long newLeft, newRight;
    newLeft = encoderLeft.read();
    if (newLeft != positionLeft) {
      if(newLeft < positionLeft) {
        // currentScreen->moved("left", 1.0);
        if (currentNote < 141) 
          currentNote = currentNote+1;
      } else {
        // currentScreen->moved("left", -1.0);
        if (currentNote != 0) 
          currentNote = currentNote-1;
      }
      Serial.print("playing note number ");
      Serial.println(currentNote);
      m->playNote(notes[currentNote]);
      // m->playNote(440);
      positionLeft = newLeft;
    }
    newRight = encoderRight.read();
    if (newRight != positionRight) {
      if(newRight < positionRight) {
        // currentScreen->moved("right", 1.0);
      } else {
        // currentScreen->moved("right", -1.0);
      }
      positionRight = newRight;
    }
  }
  // currentScreen->refresh();
}

