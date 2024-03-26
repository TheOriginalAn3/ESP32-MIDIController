#include "MuxedPoti.h"
#include <Arduino.h>

MuxedPoti::MuxedPoti(Mux &mux, int muxYChannel, int controlNumber, byte midiChannel) : mux(mux), muxYChannel(muxYChannel), controlNumber(controlNumber), midiChannel(midiChannel)
{
    mux.setChannel(muxYChannel);
    for (int i = 0; i < 10; i++)
    {
        readings[i] = 0;
    }
}

MuxedPoti::MuxedPoti(Mux &mux, int muxYChannel, int controlNumber, byte midiChannel, int absValueThreshold) : mux(mux), muxYChannel(muxYChannel), controlNumber(controlNumber), midiChannel(midiChannel), absValueThreshold(absValueThreshold)
{
    mux.setChannel(muxYChannel);
    for (int i = 0; i < 10; i++)
    {
        readings[i] = 0;
    }
}

bool MuxedPoti::hasSignificantChange()
{
    mux.setChannel(muxYChannel);
    sum = 0;
    currentVal = mux.readPinValueAndGetData();

    // Update the readings: subtract the last reading and add the new one
    total = total - readings[readIndex] + currentVal;
    readings[readIndex] = currentVal;

    // Advance to the next position in the array
    readIndex = (readIndex + 1) % 10;

    // Calculate the average
    averageVal = total / 10;

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

int MuxedPoti::getCurrentCCMessage()
{
    return currentCCMessage;
}

byte MuxedPoti::getControlNumber()
{
    return controlNumber;
}

byte MuxedPoti::getMidiChannel()
{
    return midiChannel;
}

byte MuxedPoti::getCurrentVal()
{
    return currentVal;
}

int MuxedPoti::getAbsValueThreshold()
{
    return absValueThreshold;
}

void MuxedPoti::setAbsValueThreshold(int absValueThreshold)
{
    this->absValueThreshold = absValueThreshold;
}

int MuxedPoti::getAbsValue()
{
    absValue = abs(currentVal - previousVal);
    return absValue;
}





















void MuxedPoti::printMuxLocation() {
    Serial.print("Mux object located at: 0x");
    Serial.println((uintptr_t)&mux, HEX);
}

