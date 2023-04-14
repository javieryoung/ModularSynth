

#include "SPI.h"
#include "ILI9341_t3n.h"
#include <XPT2046_Touchscreen.h>
#include <Encoder.h>




// when used w/ Audio Adapter, must use an alternate CS pin for the display
const int TFT_CHIP_SELECT = 14;
const int TFT_DATA_COMMAND = 9;
ILI9341_t3n tft = ILI9341_t3n(TFT_CHIP_SELECT, TFT_DATA_COMMAND);

// create TFT framebuffer
DMAMEM uint16_t framebuf[320 * 240];

// when used w/ Audio Adapter, must use an alternate CS pin for the touchscreen
#define TS_CS_PIN  5

XPT2046_Touchscreen ts(TS_CS_PIN, 255);





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

  
}
