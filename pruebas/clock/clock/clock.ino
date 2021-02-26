/* RGB Analog Example, Teensyduino Tutorial #2
   http://www.pjrc.com/teensy/tutorial2.html

   This example code is in the public domain.
*/
const int velocityPotPin =  PIN_F0;
const int clockPin = PIN_D2;

float velocity;
const long minInMicros = 1000000; // 1 segundo
long lastTick = 0;
long lastOn = 0;
void setup()   {      
  Serial.begin(9600);
  pinMode(clockPin, OUTPUT);
}

void clockOn() {
  analogWrite(clockPin, 255);
}

void clockOff() {
  analogWrite(clockPin,0);
}

int count = 0;
void tick() {
  lastOn = millis();
  clockOn();
  count++;
}

void loop()                     
{
  velocity = analogRead(velocityPotPin);
  float speedPercent = velocity / 1023;
  float tickTime = minInMicros - (minInMicros * speedPercent);

  if (micros() - lastTick > tickTime) {
    lastTick = micros();
    tick();
  }

  if (lastOn > 0 && millis() - lastOn >5) {
    clockOff();
  }
}
