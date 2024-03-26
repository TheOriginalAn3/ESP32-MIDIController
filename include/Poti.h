#ifndef Poti_h
#define Poti_h

#include "Arduino.h"

class Poti
{
private:
    int pin;
    int previousVal = 0;
    int currentCCMessage = -1;
    int currentVal;
    byte controlNumber;
    byte midiChannel = 1;
    int absValueThreshold = 10;
    int absValue;
    int NUM_READINGS;
    int readings[10];
    int readIndex;
    int total;
    int previousAverage;

public:
    Poti(int pin, int controlNumber, byte midiChannel);
    Poti(int pin, int controlNumber, byte midiChannel, int absValueThreshold);
    bool hasSignificantChange();
    int getCurrentCCMessage();
    byte getControlNumber();
    byte getMidiChannel();
    byte getCurrentVal();
    int getAbsValue();
    int getAbsValueThreshold();
    void setAbsValueThreshold(int absValueThreshold);
};

#endif