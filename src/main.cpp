#include <Arduino.h>
#include <Mux.h>
#include <MuxedPoti.h>
// #include <MIDI.h>

// Functions
void checkAndSendMIDICC(MuxedPoti &poti);
// void checkAndSendMIDICC(Poti &poti);
void checkAndSendMIDICC();

// MIDI
// MIDI_CREATE_INSTANCE(HardwareSerial, Serial2, MIDI);

// Define periferials
// Muxes
Mux mux(35, 26, 33, 32, true, false);

// Muxed Potis
MuxedPoti FADER1(mux, 7, 10, 1);
MuxedPoti FADER2(mux, 6, 10, 2);
MuxedPoti FADER3(mux, 5, 10, 3);
MuxedPoti FADER4(mux, 4, 10, 4);
MuxedPoti POTI1(mux, 3, 11, 1);
MuxedPoti POTI2(mux, 2, 11, 2);
MuxedPoti POTI3(mux, 1, 11, 3);
MuxedPoti POTI4(mux, 0, 11, 4);

/*
// // Rotary Encoders
const int RE1_pinA = 27; // Interrupt
const int RE1_pinB = 4;	 // Data

int RE1_currentAState = LOW;
int RE1_currentBState = LOW;

volatile int RE1_lastEncoded = 0;
volatile long RE1_encoderValue = 0;
volatile int RE1_counter = 0;
int RE1_counterLast = 0;

unsigned long lastInterruptTime = 0;
const long debounceDelay = 5; // Debounce delay in milliseconds

int incr = 0;

void RE1pinA_updateCC()
{
	RE1_currentBState = digitalRead(RE1_pinB);
	RE1_currentAState = digitalRead(RE1_pinA);
	unsigned long currentTime = millis();
	if (currentTime - lastInterruptTime > debounceDelay)
	{
		if (RE1_currentAState != RE1_currentBState)
		{
			RE1_encoderValue++;
		}
		else if (RE1_currentAState == RE1_currentBState)
		{
			RE1_counter--;
		}
	}
	lastInterruptTime = currentTime;
}
*/

void setup()
{
	// MIDI.begin(MIDI_CHANNEL_OMNI);
	Serial.begin(9600);

	// pinMode(RE1_pinA, INPUT_PULLDOWN);
	// pinMode(RE1_pinB, INPUT_PULLDOWN);

	// attachInterrupt(digitalPinToInterrupt(RE1_pinA), RE1pinA_updateCC, RISING);
	FADER1.printMuxLocation();
	FADER2.printMuxLocation();
	FADER3.printMuxLocation();
	FADER4.printMuxLocation();
	POTI1.printMuxLocation();
	POTI2.printMuxLocation();
	POTI3.printMuxLocation();
	POTI4.printMuxLocation();
	Serial.println(mux.getActiveChannel());
	Serial.println(mux.getDataPin());
	Serial.println(mux.getS0());
	Serial.println(mux.getS1());
	Serial.println(mux.getS2());
}

void loop()
{
	// FADERS AND POTIS
	checkAndSendMIDICC(FADER1);
	checkAndSendMIDICC(FADER2);
	checkAndSendMIDICC(FADER3);
	checkAndSendMIDICC(FADER4);
	checkAndSendMIDICC(POTI1);
	checkAndSendMIDICC(POTI2);
	checkAndSendMIDICC(POTI3);
	checkAndSendMIDICC(POTI4);
	// checkAndSendMIDICC();
	// Serial.println(digitalRead(RE1_pinB));
	// delay(40);
	// Serial.println(RE1_counter);

	// Working
	// RE1_currentAState = digitalRead(RE1_pinA);
	// RE1_currentBState = digitalRead(RE1_pinB);
	// Serial.print(RE1_currentAState);
	// Serial.println(RE1_currentBState);

	// if (RE1_counter != RE1_counterLast) {
	//   Serial.println(RE1_counter);
	//   RE1_counterLast = RE1_counter;
	// }
}

// void checkAndSendMIDICC(Poti &poti)
// {
// 	if (poti.hasSignificantChange())
// 	{
// 		// MIDI.sendControlChange(poti.getControllNumber(), poti.getCurrentCCMessage(), poti.getMidiChannel()); // Sending on channel 1
// 		Serial.print(poti.getControllNumber());
// 		Serial.print(" : ");
// 		// if ((&poti == &POTI1) || (&poti == &POTI2) || (&poti == &POTI3) || (&poti == &POTI4))
// 		// {
// 		//   Serial.print(map(poti.getCurrentCCMessage(), 0, 127, 127, 0));
// 		// }
// 		// else
// 		Serial.print(poti.getCurrentCCMessage());
// 		Serial.print(" : ");
// 		Serial.println(poti.getMidiChannel());
// 	}
// }

void checkAndSendMIDICC(MuxedPoti &poti)
{
	if (poti.hasSignificantChange())
	{
		// MIDI.sendControlChange(poti.getControllNumber(), poti.getCurrentCCMessage(), poti.getMidiChannel()); // Sending on channel 1
		Serial.print(poti.getControllNumber());
		Serial.print(" : ");
		// if ((&poti == &POTI1) || (&poti == &POTI2) || (&poti == &POTI3) || (&poti == &POTI4))
		// {
		//   Serial.print(map(poti.getCurrentCCMessage(), 0, 127, 127, 0));
		// }
		// else
		Serial.print(poti.getCurrentCCMessage());
		Serial.print(" : ");
		Serial.println(poti.getMidiChannel());
	}
}

// void checkAndSendMIDICC()
// {
// 	if (RE1_counter != RE1_counterLast)
// 	{
// 		Serial.println("RE1: " + RE1_counter);
// 	}
// }
