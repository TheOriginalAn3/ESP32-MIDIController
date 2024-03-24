#include "Mux.h"
#include <Arduino.h>

Mux::Mux(int pinData, int pinS0, int pinS1, int pinS2, bool isAnalog, bool isOutput) : pinData(pinData), pinS0(pinS2), pinS1(pinS1), pinS2(pinS0), isAnalog(isAnalog), isOutput(isOutput)
{
    if (isOutput)
    {
        pinMode(pinData, INPUT);
        pinMode(pinS0, OUTPUT);
        pinMode(pinS1, OUTPUT);
        pinMode(pinS2, OUTPUT);
        setChannel(muxChannel);
    }
    else
    {
        pinMode(pinData, OUTPUT);
        pinMode(pinS0, OUTPUT);
        pinMode(pinS1, OUTPUT);
        pinMode(pinS2, OUTPUT);
        setChannel(muxChannel);
    }
}

Mux::Mux(int pinData, int pinS0, int pinS1, int pinS2, bool isAnalog, bool isOutput, int muxChannel) : pinData(pinData), pinS0(pinS2), pinS1(pinS1), pinS2(pinS0), isAnalog(isAnalog), isOutput(isOutput), muxChannel(muxChannel)
{
    if (isOutput)
    {
        pinMode(pinData, INPUT);
        pinMode(pinS0, OUTPUT);
        pinMode(pinS1, OUTPUT);
        pinMode(pinS2, OUTPUT);
        setChannel(muxChannel);
    }
    else
    {
        pinMode(pinData, OUTPUT);
        pinMode(pinS0, OUTPUT);
        pinMode(pinS1, OUTPUT);
        pinMode(pinS2, OUTPUT);
        setChannel(muxChannel);
    }
}

void Mux::setChannel(int channel)
{
    muxChannel = channel;
    switch (channel)
    {
    case 0: // 000
        digitalWrite(pinS0, LOW);
        digitalWrite(pinS1, LOW);
        digitalWrite(pinS2, LOW);
        break;
    case 1: // 001
        digitalWrite(pinS0, LOW);
        digitalWrite(pinS1, LOW);
        digitalWrite(pinS2, HIGH);
        break;
    case 2: // 010
        digitalWrite(pinS0, LOW);
        digitalWrite(pinS1, HIGH);
        digitalWrite(pinS2, LOW);
        break;
    case 3: // 011
        digitalWrite(pinS0, LOW);
        digitalWrite(pinS1, HIGH);
        digitalWrite(pinS2, HIGH);
        break;
    case 4: // 100
        digitalWrite(pinS0, HIGH);
        digitalWrite(pinS1, LOW);
        digitalWrite(pinS2, LOW);
        break;
    case 5: // 101
        digitalWrite(pinS0, HIGH);
        digitalWrite(pinS1, LOW);
        digitalWrite(pinS2, HIGH);
        break;
    case 6: // 110
        digitalWrite(pinS0, HIGH);
        digitalWrite(pinS1, HIGH);
        digitalWrite(pinS2, LOW);
        break;
    case 7: // 111
        digitalWrite(pinS0, HIGH);
        digitalWrite(pinS1, HIGH);
        digitalWrite(pinS2, HIGH);
        break;
    default: // 000
        digitalWrite(pinS0, LOW);
        digitalWrite(pinS1, LOW);
        digitalWrite(pinS2, LOW);
        break;
    }
}

int Mux::getActiveChannel()
{
    return muxChannel;
}

bool Mux::getIsAnalog()
{
    return isAnalog;
}

bool Mux::getIsOutput()
{
    return isOutput;
}

// Make sure to use ADC-Capable pin if recieving analog data.
int Mux::readPinValueAndGetData()
{
    if (isAnalog)
    {
        return analogRead(pinData);
    }
    else
    {
        return digitalRead(pinData);
    }
}

// Make sure to use DAC-Capable pin if sending analog data.
void Mux::sendData(int data)
{
    if (isAnalog)
    {
        analogWrite(pinData, data);
    }
    else
    {
        digitalWrite(pinData, data);
    }
}

int Mux::getDataPin()
{
    return pinData;
}

int Mux::getS0()
{
    return pinS0;
}
int Mux::getS1()
{
    return pinS1;
}
int Mux::getS2()
{
    return pinS2;
}
