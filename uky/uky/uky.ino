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



#define TFT_DC      20
#define TFT_CS      21
#define TFT_RST    255 
#define TFT_MOSI     7
#define TFT_SCLK    14
#define TFT_MISO    12

#define CS_PIN  8
XPT2046_Touchscreen ts(CS_PIN); 


// ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_MISO);
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);


Encoder encoderLeft(1, 3);
Encoder encoderRight(4, 5);
double _lastUpdate = 0;
Screen* currentScreen;


void setup() {
  AudioMemory(32);
  
  sgtl5000_1.enable();
  sgtl5000_1.volume(1.0);

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

  EffectChain * effectChain = new EffectChain();
  effectChain->chainList();
  effectChain->setInputLeft(&inputLeft);
  effectChain->setInputRight(&inputRight);
  effectChain->setOutputRight(&outputRight);
  effectChain->setOutputLeft(&outputLeft);

  effectChain->connect();
  
}

int positionLeft = 0;
int positionRight = 0;

void loop(void) {
  
  if (buttonLeft.update()) {
    if (buttonLeft.fallingEdge()) {
      currentScreen->clicked("left");
    }
  } 
  if (buttonRight.update()) {
    if (buttonRight.fallingEdge()) {
      currentScreen->clicked("right");
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
    /*
    Serial.print("X = "); Serial.print(px);
    Serial.print("\tY = "); Serial.println(py);
    */
    
    currentScreen->touched(px, py, p.z);
  }
  long nowInMillis = millis();
  if (nowInMillis - _lastUpdate > 50) {
    _lastUpdate = millis();
    long newLeft, newRight;
    newLeft = encoderLeft.read();
    if (newLeft != positionLeft) {
      if(newLeft < positionLeft) {
        currentScreen->moved("left", 1.0);
      } else {
        currentScreen->moved("left", -1.0);
      }
      positionLeft = newLeft;
    }
    newRight = encoderRight.read();
    if (newRight != positionRight) {
      if(newRight < positionRight) {
        currentScreen->moved("right", 1.0);
      } else {
        currentScreen->moved("right", -1.0);
      }
      positionRight = newRight;
    }
  }
  currentScreen->refresh();
}

