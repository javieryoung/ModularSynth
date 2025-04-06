#include <Wire.h>
#include <Encoder.h>

#include <Audio.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>


#include "Input.h"
#include "Button.h"
#include "Pot.h"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "classes/LinkedList.h"

#include "classes/extraEffects/effect_platervbstereo.h"
#include "classes/extraEffects/effect_platervbstereo.cpp"

#include "classes/EffectChain/Effect/Effect.h"
#include "classes/EffectChain/Effect/EffectPreFiltered.h"
#include "classes/EffectChain/Effect/EffectDelay.h"
#include "classes/EffectChain/Effect/EffectReverb.h"
#include "classes/EffectChain/EffectChain.h"

#include "classes/EffectChain/Effect/Effect.cpp"
#include "classes/EffectChain/Effect/EffectDelay.cpp"
#include "classes/EffectChain/Effect/EffectReverb.cpp"
#include "classes/EffectChain/EffectChain.cpp"
/*

#include "classes/EffectChain/Effect/EffectWaveshaper.h"

#include "classes/EffectChain/Effect/EffectWaveshaper.cpp"
*/

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define SCREEN_ADDRESS 0x3C  // Dirección I2C del OLED

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pines del Encoder
#define ENCODER_A 6
#define ENCODER_B 7
#define ENCODER_SW 8  // Botón del encoder

// Pines de los Potenciómetros
#define POT1 14  // Pin 14
#define POT2 15  // Pin 15


long encoderPos = 0;
long lastEncoderPos = 0;


// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine;           //xy=243,469
AudioInputI2S            i2s2;           //xy=381,409
AudioEffectEnvelope      env;            //xy=390,469
AudioAmplifier           inputRight;     //xy=559,450
AudioAmplifier           inputLeft;      //xy=576,404
AudioAmplifier           outputLeft;     //xy=827,394
AudioAmplifier           outputRight;    //xy=841,449
AudioOutputI2S           i2s1;           //xy=1044,424
AudioConnection          patchCord1(sine, env);
AudioConnection          patchCord2(env, inputLeft);
AudioConnection          patchCord3(env, inputRight);
AudioConnection          patchCord4(outputLeft, 0, i2s1, 0);
AudioConnection          patchCord5(outputLeft, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1039,354
// GUItool: end automatically generated code



// Encoder encoder(ENCODER_A,ENCODER_B);
int positionEncoder = 0;
int lastEncoderRead = 0;

Button encoderButton;

double _lastUpdate = 0;
double _lastNoteOn = 0;

void setup() {
  Serial.begin(115200);

  // Inicializar pantalla OLED
  /*
  Wire.begin();
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("Error al iniciar OLED"));
    while (1);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setRotation(2);
  display.setTextColor(SSD1306_WHITE);

  */
  // Configurar Encoder
  // pinMode(ENCODER_SW, INPUT_PULLDOWN);  // Configura el botón del encoder

  Serial.println("Sistema iniciado.");

  AudioMemory(128);

  env.delay(0);
  env.attack(10);
  env.hold(0);
  env.release(20);

  inputLeft.gain(1);
  inputRight.gain(1);
  outputLeft.gain(1);
  outputRight.gain(1);

  sine.frequency(440);
  sine.amplitude(0.5);

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);

  EffectChain * effectChain = new EffectChain(false);
  effectChain->setInputLeft(&inputLeft);
  effectChain->setOutputLeft(&outputLeft);
  effectChain->connect();

  Effect * effectDelay = new EffectDelay(effectChain, false);
  effectChain->addEffect(effectDelay);

  Effect * effectReverb = new EffectReverb(effectChain, false);
  effectChain->addEffect(effectReverb);

  pinMode(14, INPUT);
  pinMode(15, INPUT);

}


void loop() {

  /*
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Enc: ");
  display.println(positionEncoder);
  display.print("Btn: ");
  display.println(encoderButton.read() ? "ON" : "OFF");
  display.display();
  */

  int rawValue = analogRead(14); // Lee el ADC (0-1023 en Teensy 4.0)
  Serial.print("POT1: ");
  Serial.print(rawValue);
  rawValue = analogRead(15); // Lee el ADC (0-1023 en Teensy 4.0)
  Serial.print("POT2: ");
  Serial.println(rawValue);
  delay(500);

  /*
  if (millis() - _lastUpdate > 50) {
    _lastUpdate = millis();
    long newPosition = encoder.read();
    if (abs(newPosition - lastEncoderRead) >= 2) {
      
      if (lastEncoderRead < newPosition) {
        positionEncoder += 100;
      } else if (lastEncoderRead > newPosition) {
        positionEncoder -= 100;
      }
    }
    lastEncoderRead = newPosition;
  }
  */
  
  if (millis() - _lastNoteOn > 1500) {
    _lastNoteOn = millis();
    env.noteOn();
  }
  if (millis() - _lastNoteOn > 5) {
    env.noteOff();
  }
}

