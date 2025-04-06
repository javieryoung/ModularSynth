/*
ESTO FUNCIONA CON UN TEENSY 4.0 con las siguientes conexiones:
2 pcf8574 conectados al pin 19 y 18 de teensy (SDA y SCL (o al reves))
entradas de encoder a y b a los primeros 2 pin de entrada de cada pcf8574 (conecte cada encoder a un chip distinto pa probar)
entradas del boton del encoder al tercer pin de entrada del pcf8574 que le corresponde
pin del medio de los encoder a GND, y lo mismo el boton
*/


#include <Wire.h>

// Direcciones de los PCF8574P (ajustar según las conexiones)
#define PCF8574_1 0x20  // Dirección del primer PCF8574P (Encoder 1)
#define PCF8574_2 0x21  // Dirección del segundo PCF8574P (Encoder 2)

// Pines del Encoder 1
#define ENC1_A 0  // Pin A del Encoder 1 (en PCF8574_1)
#define ENC1_B 1  // Pin B del Encoder 1 (en PCF8574_1)
#define ENC1_SW 2 // Botón del Encoder 1 (en PCF8574_1)

// Pines del Encoder 2
#define ENC2_A 0  // Pin A del Encoder 2 (en PCF8574_2)
#define ENC2_B 1  // Pin B del Encoder 2 (en PCF8574_2)
#define ENC2_SW 2 // Botón del Encoder 2 (en PCF8574_2)

unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
#define DEBOUNCE_DELAY 5 // Tiempo de debounce en milisegundos

byte lastState1A = 0;  // Último estado de A para Encoder 1
byte lastState1B = 0;  // Último estado de B para Encoder 1
byte lastState2A = 0;  // Último estado de A para Encoder 2
byte lastState2B = 0;  // Último estado de B para Encoder 2

void setup() {
    Serial.begin(115200);
    Wire.begin();  // Inicia la comunicación I2C

    // Configura los pines del PCF8574 como entradas
    Wire.beginTransmission(PCF8574_1);
    Wire.write(0xFF);  // Configura todos los pines como entrada
    Wire.endTransmission();

    Wire.beginTransmission(PCF8574_2);
    Wire.write(0xFF);  // Configura todos los pines como entrada
    Wire.endTransmission();
}

void loop() {
    unsigned long currentTime = millis();

    // Leer el estado del Encoder 1
    Wire.requestFrom(PCF8574_1, 1);
    if (Wire.available()) {
        byte state1 = Wire.read();

        byte enc1A = (state1 >> ENC1_A) & 1;
        byte enc1B = (state1 >> ENC1_B) & 1;

        // Detectar cambio de estado en A o B
        if ((enc1A != lastState1A || enc1B != lastState1B) && (currentTime - lastDebounceTime1) > DEBOUNCE_DELAY) {
            if ((lastState1A == 0 && lastState1B == 1 && enc1A == 1 && enc1B == 1) || 
                (lastState1A == 1 && lastState1B == 0 && enc1A == 0 && enc1B == 0)) {
                Serial.println("Encoder 1 → Derecha");
            } else if ((lastState1A == 0 && lastState1B == 1 && enc1A == 0 && enc1B == 0) || 
                       (lastState1A == 1 && lastState1B == 0 && enc1A == 1 && enc1B == 1)) {
                Serial.println("Encoder 1 → Izquierda");
            }

            lastState1A = enc1A;
            lastState1B = enc1B;
            lastDebounceTime1 = currentTime;
        }

        // Leer el botón del Encoder 1
        if (((state1 >> ENC1_SW) & 1) == 0) {
            Serial.println("Botón Encoder 1 PRESIONADO");
        }
    }

    // Leer el estado del Encoder 2
    Wire.requestFrom(PCF8574_2, 1);
    if (Wire.available()) {
        byte state2 = Wire.read();

        byte enc2A = (state2 >> ENC2_A) & 1;
        byte enc2B = (state2 >> ENC2_B) & 1;

        // Detectar cambio de estado en A o B
        if ((enc2A != lastState2A || enc2B != lastState2B) && (currentTime - lastDebounceTime2) > DEBOUNCE_DELAY) {
            if ((lastState2A == 0 && lastState2B == 1 && enc2A == 1 && enc2B == 1) || 
                (lastState2A == 1 && lastState2B == 0 && enc2A == 0 && enc2B == 0)) {
                Serial.println("Encoder 2 → Derecha");
            } else if ((lastState2A == 0 && lastState2B == 1 && enc2A == 0 && enc2B == 0) || 
                       (lastState2A == 1 && lastState2B == 0 && enc2A == 1 && enc2B == 1)) {
                Serial.println("Encoder 2 → Izquierda");
            }

            lastState2A = enc2A;
            lastState2B = enc2B;
            lastDebounceTime2 = currentTime;
        }

        // Leer el botón del Encoder 2
        if (((state2 >> ENC2_SW) & 1) == 0) {
            Serial.println("Botón Encoder 2 PRESIONADO");
        }
    }

    delay(5); // Pequeño retardo para estabilizar la lectura
}

