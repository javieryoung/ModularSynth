/* RGB Analog Example, Teensyduino Tutorial #2
   http://www.pjrc.com/teensy/tutorial2.html

   This example code is in the public domain.
*/
const int velocityPotPin =  PIN_F0;
const int leds[] = { PIN_B0, PIN_B1, PIN_B2, PIN_B3, PIN_B7 };

float velocity;
const long minInMicros = 1000000; // 1 segundo
long lastTick = 0;
long lastOn = 0;
void setup()   {      
  Serial.begin(9600);
}

void light(int which) {
  digitalWrite(leds[which],HIGH);
}

void offAll() {
  digitalWrite(leds[0],LOW);
  digitalWrite(leds[1],LOW);
  digitalWrite(leds[2],LOW);
  digitalWrite(leds[3],LOW);
  digitalWrite(leds[4],LOW);
}

int count = 0;
void tick() {
  lastOn = millis();
  if (count == 8)
    count = 0;
    
  if (count == 0) {
    light(4);
  } 
  if (count == 1) {
    light(2);
  }
  if (count == 2) {
    light(4);
  }
  if (count == 3) {
    light(1);
    light(2);
  }
    
  if (count == 4) {
    light(4);
  } 
  if (count == 5) {
    light(2);
  }
  if (count == 6) {
    light(4);
  }
  if (count == 7) {
    light(0);
    light(1);
    light(2);
  }
  light(3);

  count++;
    
}

void loop()                     
{
  velocity = analogRead(velocityPotPin);
  float speedPercent = velocity / 1023;
  float tickTime = minInMicros - (minInMicros * speedPercent);

  if (micros() - lastTick > tickTime / 3) {
    lastTick = micros();
    tick();
  }

  if (lastOn > 0 && millis() - lastOn > 10) {
    offAll();
  }
}
