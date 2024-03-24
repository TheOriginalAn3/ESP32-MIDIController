#ifndef MuxedPoti_h
#define MuxedPoti_h

#include "Arduino.h"
#include "Mux.h"

class MuxedPoti
{
private:
    // Mux Stuff
    Mux &mux;
    int muxYChannel;

    // Poti Stuff
    int pin;
    int currentCCMessage = -1;
    byte controlNumber;
    byte midiChannel = 1;
    int absValueThreshold = 10;

    // Debounce calculation variables
    int previousVal = 0;
    int currentVal;
    int absValue;
    int NUM_READINGS;
    int readings[10];
    int readIndex;
    int sum;
    int total;
    int previousAverage;
    int averageVal;

public:
    MuxedPoti(Mux &mux, int muxYChannel, int controlNumber, byte midiChannel);
    MuxedPoti(Mux &mux, int muxYChannel, int controlNumber, byte midiChannel, int absValueThreshold);
    bool hasSignificantChange();
    int getCurrentCCMessage();
    byte getControllNumber();
    byte getMidiChannel();
    byte getCurrentVal();
    int getAbsValue();
    int getAbsValueThreshold();
    void setAbsValueThreshold(int absValueThreshold);
    void printMuxLocation();
};

#endif