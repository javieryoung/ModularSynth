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
#include "classes/Screen/Screen.cpp"
#include "classes/Screen/Input/Input.h"
#include "classes/Screen/Input/Knob.h"
#include "classes/Screen/Input/Menu.h"
#include "classes/Screen/Input/TwoKnobs.h"
#include "classes/Screen/Input/Button.h"

#include "classes/EffectChain/Effect/Effect.h"
#include "classes/EffectChain/EffectChain.h"
#include "classes/EffectChain/Effect/EffectReverb.h"

#include "classes/EffectChain/Effect/Effect.cpp"
#include "classes/EffectChain/EffectChain.cpp"
#include "classes/EffectChain/Effect/EffectReverb.cpp"

#include "classes/Modular/Modular.h"
#include "classes/SoloMaker/SoloMaker.h"


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


#include "externs.h"

// ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_MISO);
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);


double _lastUpdate = 0;

float notes[128] = {32.703, 34.648, 36.708, 38.891, 41.203, 43.654, 46.249, 48.999, 51.913, 55, 58.27, 61.735, 65.406, 69.296, 73.416, 77.782, 82.407, 87.307, 92.499, 97.999, 103.826, 110, 116.541, 123.471, 130.813, 138.591, 146.832, 155.563, 164.814, 174.614, 184.997, 195.998, 207.652, 220, 233.082, 246.942, 261.626, 277.183, 293.665, 311.127, 329.628, 349.228, 369.994, 391.995, 415.305, 440, 466.164, 493.883, 523.251, 554.365, 587.33, 622.254, 659.255, 698.456, 739.989, 783.991, 830.609, 880, 932.328, 987.767, 1046.502, 1108.731, 1174.659, 1244.508, 1318.51, 1396.913, 1479.978, 1567.982, 1661.219, 1760, 1864.655, 1975.533, 2093.005, 2217.461, 2349.318, 2489.016, 2637.02, 2793.826, 2959.955, 3135.963, 3322.438, 3520, 3729.31, 3951.066, 4186.009, 4434.922, 4698.636, 4978.032, 5274.041, 5587.652, 5919.911, 6271.927, 6644.875, 7040, 7458.62, 7902.133, 8372.018, 8869.844, 9397.273, 9956.063, 10548.08, 11175.3, 11839.82, 12543.85};
int currentNote = 0;

SoloMaker * sm;
EffectChain * effectChain;

void setup() {
  AudioMemory(24);
  
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
  sm = new SoloMaker(&outputLeft);
  sm->mainScreen();
  playNote(currentNote);
}


int positionLeft = 0;
int positionRight = 0;

void loop(void) {
  if (currentScreen == NULL) return ;

  
  if (buttonLeft.update()) {
    if (buttonLeft.fallingEdge()) {
      if (currentScreen != NULL) currentScreen->clicked("left");
    }
  } 
  if (buttonRight.update()) {
    if (buttonRight.fallingEdge()) {
      if (currentScreen != NULL) currentScreen->clicked("right");
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
    
    if (currentScreen != NULL) currentScreen->touched(px, py, p.z);
  }
  long nowInMillis = millis();
  if (nowInMillis - _lastUpdate > 100) {
    _lastUpdate = millis();
    long newLeft, newRight;
    newLeft = encoderLeft.read();
    if (newLeft != positionLeft) {
      if(newLeft < positionLeft) {
        if (currentScreen != NULL) currentScreen->moved("left", 1.0);
        playNote(1);
      } else {
        if (currentScreen != NULL) currentScreen->moved("left", -1.0);
        playNote(-1);
      }
      // m->playNote(440);
      positionLeft = newLeft;
    }
    newRight = encoderRight.read();
    if (newRight != positionRight) {
      if(newRight < positionRight) {
        if (currentScreen != NULL) currentScreen->moved("right", 1.0);
      } else {
        if (currentScreen != NULL) currentScreen->moved("right", -1.0);
      }
      positionRight = newRight;
    }
  }
  if (currentScreen != NULL) {
    currentScreen->refresh();
  }
}


int scales [10][12] = {
  {12, 0}, // octaves
  {7, 5, 0 },  // octaves & fifths
  {4, 3, 5, 0},  // major triads
  {3, 4, 5, 0},  // minor triads
  {3, 2, 2, 5, 0},  // minor triads+
  {3, 2, 5, 2, 0},  // blues 1
  {7, 0},  // 5th cycle
  {3, 2, 2, 0},  // blues 2
  {3, 2, 2, 3, 2, 0},  // pentatonic
  {3, 2, 1, 1, 3, 2, 0},  // pentatonic blues
};

int indexInScale = 0;
int selectedScale = 9;
int lastDirection;
void playNote(int direction) {
  if (lastDirection == direction)
    indexInScale += direction;

  lastDirection = direction;
  if (indexInScale == -1) {
    for (indexInScale = 1; scales[selectedScale][indexInScale] != 0; indexInScale++);
    indexInScale--;
  }
  if (scales[selectedScale][indexInScale] == 0) {
    indexInScale = 0;
  }
  currentNote = currentNote + (scales[selectedScale][indexInScale] * direction);

  Serial.print(" que es  ");
  Serial.println(noteName(currentNote));
  sm->modular->playNote(notes[currentNote]);

  
}

String noteName(int index) {
  if (index % 12 == 0)
    return "C";
  if (index % 12 == 1)
    return "C#";
  if (index % 12 == 2)
    return "D";
  if (index % 12 == 3)
    return "D#";
  if (index % 12 == 4)
    return "E";
  if (index % 12 == 5)
    return "F";
  if (index % 12 == 6)
    return "F#";
  if (index % 12 == 7)
    return "G";
  if (index % 12 == 8)
    return "G#";
  if (index % 12 == 9)
    return "A";
  if (index % 12 == 10)
    return "A#";
  if (index % 12 == 11)
    return "B";
  return "Unknown note";
}