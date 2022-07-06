

#include "SPI.h"
#include "ILI9341_t3.h"
#include <XPT2046_Touchscreen.h>
#include <Encoder.h>

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
  tft.println("Prueba...");


  Serial.begin(9600);
 
 

}


void loop(void) {
  if (ts.touched()) {
    TS_Point p = ts.getPoint();
  
    Serial.print("X = "); Serial.print(p.x);
    Serial.print("\tY = "); Serial.print(p.y);
    Serial.print("\tPressure = "); Serial.println(p.z);  
  }


  long nowInMillis = millis();
  if (nowInMillis - _lastUpdate > 200) {
    _lastUpdate = millis();
    long newLeft, newRight;
    newLeft = encoderLeft.read();
    if (newLeft != positionLeft) {
      if(newLeft < positionLeft) {
        tft.println("Left >");
      } else {
        tft.println("Left <");
      }
      positionLeft = newLeft;
    }

    
    newRight = encoderRight.read();
    if (newRight != positionRight) {
      if(newRight < positionRight) {
        tft.println("Right >");
      } else {
        tft.println("Right <");
      }
      positionRight = newRight;
    }
  }
  
}
