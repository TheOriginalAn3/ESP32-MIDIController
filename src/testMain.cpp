#if 0
#include <Arduino.h>

void setup() {
    Serial.begin(9600);
    analogReadResolution(16);
}

void loop(){
    Serial.println(analogRead(34));
}

#endif