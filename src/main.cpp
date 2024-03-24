#include <Arduino.h>
#include <Poti.h>
// #include <MIDI.h>

// Functions
void checkAndSendMIDICC(Poti &poti);
void checkAndSendMIDICC();

// MIDI
// MIDI_CREATE_INSTANCE(HardwareSerial, Serial2, MIDI);

// Define periferials
// Faders and potis
Poti FADER1(36, 10, 1); // default threshold value of 10
Poti FADER2(39, 10, 2);
Poti FADER3(34, 10, 3);
Poti FADER4(35, 10, 4);
Poti POTI1(32, 11, 1);
Poti POTI2(33, 11, 2);
Poti POTI3(25, 11, 3);
Poti POTI4(26, 11, 4);

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

void setup()
{
	// MIDI.begin(MIDI_CHANNEL_OMNI);
	Serial.begin(9600);

	pinMode(RE1_pinA, INPUT_PULLDOWN);

	pinMode(RE1_pinB, INPUT_PULLDOWN);

	// attachInterrupt(digitalPinToInterrupt(RE1_pinA), RE1pinA_updateCC, RISING);
}

void loop()
{
	// FADERS AND POTIS
	checkAndSendMIDICC(FADER1, 7);
	checkAndSendMIDICC(FADER2, 6);
	checkAndSendMIDICC(FADER3, 5);
	checkAndSendMIDICC(FADER4, 4);
	checkAndSendMIDICC(POTI1, 3);
	checkAndSendMIDICC(POTI2, 2);
	checkAndSendMIDICC(POTI3, 1);
	checkAndSendMIDICC(POTI4, 0);
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

void checkAndSendMIDICC(Poti &poti, int muxChannel_y)
{
	switch (muxChannel_y)
	{
	case 0:
		digitalWrite()
		break;
	
	default:
		break;
	}
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

void checkAndSendMIDICC()
{
	if (RE1_counter != RE1_counterLast)
	{
		Serial.println("RE1: " + RE1_counter);
	}
}
