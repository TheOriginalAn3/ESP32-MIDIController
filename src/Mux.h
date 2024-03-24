#ifndef Mux_h
#define Mux_h

#include "Arduino.h"

class Mux
{
private:
    int pinData, pinS0, pinS1, pinS2;
    bool isAnalog;
    bool isOutput;
    int muxChannel = 0;

public:
    Mux(int pinData, int pinS0, int pinS1, int pinS2, bool isAnalog, bool isOutput);
    Mux(int pinData, int pinS0, int pinS1, int pinS2, bool isAnalog, bool isOutput, int muxChannel);

    int getActiveChannel();
    void setChannel(int channel);

    int readPinValueAndGetData();
    void sendData(int data);

    bool getIsAnalog();
    bool getIsOutput();

    void checkInitialization();

    int getDataPin();
    int getS0();
    int getS1();
    int getS2();
};

#endif