#include <Arduino.h>
#include "RAMiniVector.h"

RAMiniVector <int> myVector;

void setup() {
    myVector.push_back(200);
    myVector.push_back(116);
    myVector.push_back(0);
    myVector.push_back(255);
}

void loop() {
    for (int i = 0; i < 4; i++) {
        analogWrite(5,myVector[i]);
        delay(100);
    }
}
