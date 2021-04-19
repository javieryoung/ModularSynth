#include <Pot.h>
#include <Multiplexer2.h>

Pot p;
Multiplexer2 mux;

void setup() {
  p.setPin(22);
}

void loop() {
  if (p.changed()) 
    Serial.println(p.read());


}
