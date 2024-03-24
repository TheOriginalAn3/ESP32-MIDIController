#include "Poti.h"
#include <Arduino.h>

Poti::Poti(int pin, int controlNumber, byte midiChannel) : pin(pin), controlNumber(controlNumber), midiChannel(midiChannel)
{
    pinMode(pin, INPUT);
    for (int i = 0; i < 10; i++)
    {
        readings[i] = 0;
    }
}
Poti::Poti(int pin, int controlNumber, byte midiChannel, int absValueThreshold) : pin(pin), controlNumber(controlNumber), midiChannel(midiChannel), absValueThreshold(absValueThreshold)
{
    pinMode(pin, INPUT);
    for (int i = 0; i < 10; i++)
    {
        readings[i] = 0;
    }
}

bool Poti::hasSignificantChange()
{
    int sum = 0;
    currentVal = analogRead(pin);

    // Update the readings: subtract the last reading and add the new one
    total = total - readings[readIndex] + currentVal;
    readings[readIndex] = currentVal;

    // Advance to the next position in the array
    readIndex = (readIndex + 1) % 10;

    // Calculate the average
    int averageVal = total / 10;

    // Map the average value
    currentCCMessage = map(averageVal, 0, 4095, 0, 127);

    if (abs(averageVal - previousAverage) > absValueThreshold && currentCCMessage != previousVal)
    {
        previousVal = currentCCMessage;
        previousAverage = averageVal;
        return true;
    }
    return false;
}

int Poti::getCurrentCCMessage()
{
    return currentCCMessage;
}

byte Poti::getControllNumber()
{
    return controlNumber;
}

byte Poti::getMidiChannel()
{
    return midiChannel;
}

byte Poti::getCurrentVal()
{
    return currentVal;
}

int Poti::getAbsValueThreshold()
{
    return absValueThreshold;
}

void Poti::setAbsValueThreshold(int absValueThreshold)
{
    this->absValueThreshold = absValueThreshold;
}

int Poti::getAbsValue()
{
    absValue = abs(currentVal - previousVal);
    return absValue;
}