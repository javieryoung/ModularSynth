


#define PRIMARY 0xFFFF
#define BLACK 0x0000

#include "SPI.h"
#include "ILI9341_t3.h"
#include <XPT2046_Touchscreen.h>
#include <Encoder.h>


#include "classes/LinkedList.h"
#include "classes/Screen.h"
#include "classes/Input/Input.h"
#include "classes/Input/Knob.h"
#include "classes/Input/TwoKnobs.h"

#include "waves/Sine.h"
#include "waves/SawTooth.h"
#include "waves/Square.h"
#include "waves/Triangle.h"

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



ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_MISO);

#define CS_PIN  8
XPT2046_Touchscreen ts(CS_PIN); 

Encoder encoderLeft(1, 3);
Encoder encoderRight(4, 5);
double _lastUpdate = 0;
Screen* currentScreen;


void setup() {
  AudioMemory(32);
  

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
  
  currentScreen = new Screen(&tft);
  Input* k = new TwoKnobs(&tft, 20, 40, 50, 50, 15, "hola", "chau");
  currentScreen->addInput(k);

  
  Input* k2 = new TwoKnobs(&tft, 20, 160, 50, 50, 15, " hi ", " bye ");
  currentScreen->addInput(k2);

  currentScreen->draw();

}

int positionLeft = 0;
int positionRight = 0;

void loop(void) {
  
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
