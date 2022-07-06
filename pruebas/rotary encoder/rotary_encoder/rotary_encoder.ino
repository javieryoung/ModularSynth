/* Encoder Library - TwoKnobs Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */

#include <Encoder.h>
// Change these pin numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder encoder(8, 9);
//   avoid using pins with LEDs attached

void setup() {
  Serial.begin(9600);
  Serial.println("TwoKnobs Encoder Test:");
}


int _selectorPin1 = 1;
int _selectorPin2 = 2;
int _selectorPin3 = 3;
long positionLeft  = -999;
long positionRight = -999;
long _lastUpdate = 0;
int _modes [8][3] = { {LOW, LOW, LOW}, {LOW, LOW, HIGH}, {LOW, HIGH, LOW}, {LOW, HIGH, HIGH}, {HIGH, LOW, LOW}, {HIGH, LOW, HIGH}, {HIGH, HIGH, LOW}, {HIGH, HIGH, HIGH} };
int _currentRead = 0;

void loop() {
  long newLeft, newRight;
  long nowInMicros = micros();
  if (nowInMicros - _lastUpdate > 50) {
    _currentRead++;
    if (_currentRead == 8) _currentRead = 0;
    digitalWrite(_selectorPin1, _modes[_currentRead][0]);
    digitalWrite(_selectorPin2, _modes[_currentRead][1]);
    digitalWrite(_selectorPin3, _modes[_currentRead][2]);
    _lastUpdate = micros();
    if (_currentRead == 4) {
      newLeft = encoder.read();
      if (newLeft != positionLeft) {
        Serial.print("Left = ");
        Serial.print(newLeft);
        Serial.print(", Right = ");
        Serial.print(positionRight);
        Serial.println();
        positionLeft = newLeft;
      }
    }
    if (_currentRead == 6) {
      newRight = encoder.read();
      if (newRight != positionRight) {
        Serial.print("Left = ");
        Serial.print(positionLeft);
        Serial.print(", Right = ");
        Serial.print(newRight);
        Serial.println();
        positionRight = newRight;
      }
    }
  }
  // if a character is sent from the serial monitor,
  // reset both back to zero.
}