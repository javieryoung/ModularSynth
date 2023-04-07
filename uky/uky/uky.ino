


#define PRIMARY 0xFFFF
#define BLACK 0x0000
#define SCREEN_WIDTH 320

#include "SPI.h"
#include "Adafruit_ILI9341.h"
#include <XPT2046_Touchscreen.h>
#include <Encoder.h>
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
  

  pinMode(buttonPinLeft, INPUT_PULLUP);
  pinMode(buttonPinRight, INPUT_PULLUP);

  SPI.setMOSI(7);
  SPI.setSCK(14);
  tft.begin();
  tft.setRotation(3);


  while(!ts.begin()) {
    Serial.print("No se inicio");
  }
  ts.setRotation(3);

  tft.fillScreen(BLACK);
  tft.setTextSize(2);
  
  /*
  currentScreen = new Screen();
  Input* k = new TwoKnobs(20, 40, 50, 50, 15, "hola", "chau");
  currentScreen->addInput(k);

  
  Input* k2 = new TwoKnobs(20, 160, 50, 50, 15, " hi ", " bye ");
  currentScreen->addInput(k2);

  currentScreen->draw();
  */
  EffectChain * effects = new EffectChain();
  effects->chainList();

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

