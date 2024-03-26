#include <Arduino.h>
#include <Poti.h>
#include <Mux.h>
#include <MuxedPoti.h>
#include <ESP32Encoder.h>
#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
// #include <MIDI.h>

// Functions
void checkAndSendMIDICC(MuxedPoti &poti);
void checkAndSendMIDICC(Poti &poti);
void checkAndSendMIDICC(ESP32Encoder &enc);
void tftPrintTest();
void tftUpdateValueTest();


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

// Encoders
ESP32Encoder ENC1;
ESP32Encoder ENC2;
ESP32Encoder ENC3;
ESP32Encoder ENC4;

// TFT Display
TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

void setup()
{
	// MIDI.begin(MIDI_CHANNEL_OMNI);
	Serial.begin(9600);

	FADER1.printMuxLocation();
	FADER2.printMuxLocation();
	FADER3.printMuxLocation();
	FADER4.printMuxLocation();
	POTI1.printMuxLocation();
	POTI2.printMuxLocation();
	POTI3.printMuxLocation();
	POTI4.printMuxLocation();
	// Serial.println(mux.getActiveChannel());
	// Serial.println(mux.getDataPin());
	// Serial.println(mux.getS0());
	// Serial.println(mux.getS1());
	// Serial.println(mux.getS2());

	ENC1.attachHalfQuad(15, 27);
	ENC1.setMIDIParam(12, 1);
	ENC2.attachHalfQuad(2, 14);
	ENC2.setMIDIParam(12, 2);
	ENC3.attachHalfQuad(0, 12); 
	ENC3.setMIDIParam(12, 3);
	ENC4.attachHalfQuad(4, 13);                                                                                                                                                                                                    
	ENC4.setMIDIParam(12, 4);


  // Use this initializer if you're using a 1.8" TFT
  tft.init();   // initialize a ST7735S chip
  Serial.println("Initialized Display");
  tftPrintTest();
  Serial.println("done");
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
	// ENCODERS
	checkAndSendMIDICC(ENC1);
	checkAndSendMIDICC(ENC2);
	checkAndSendMIDICC(ENC3);
	checkAndSendMIDICC(ENC4);

	// tftUpdateValueTest();
}

void checkAndSendMIDICC(Poti &poti)
{
	if (poti.hasSignificantChange())
	{
		// MIDI.sendControlChange(poti.getControlNumber(), poti.getCurrentCCMessage(), poti.getMidiChannel()); // Sending on channel 1
		Serial.print(poti.getControlNumber());
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

void checkAndSendMIDICC(MuxedPoti &poti)
{
	if (poti.hasSignificantChange())
	{
		// MIDI.sendControlChange(poti.getControlNumber(), poti.getCurrentCCMessage(), poti.getMidiChannel()); // Sending on channel 1
		Serial.print(poti.getControlNumber());
		Serial.print(" : ");
		Serial.print(poti.getCurrentCCMessage());
		Serial.print(" : ");
		Serial.println(poti.getMidiChannel());
	}
}

void checkAndSendMIDICC(ESP32Encoder &enc)
{
	if (enc.getLastValue() != enc.getCount()/2)
	{
		// MIDI.sendControlChange(poti.getControlNumber(), poti.getCurrentCCMessage(), poti.getMidiChannel()); // Sending on channel 1
		Serial.print(enc.getControlNumber());
		Serial.print(" : ");
		Serial.print(enc.getCurrentCCMessage());
		Serial.print(" : ");
		Serial.println(enc.getMidiChannel());
	}
}

void tftPrintTest() {
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.println("Hello");

  tft.setCursor(0, 30);
  tft.println("World!");
}

void tftUpdateValueTest() {
	tftPrintTest();
	for (int i = 0; i < 127; i++)
	{	
		tft.setCursor(0, 60);
		tft.fillRect(0, 60, 128, 30, TFT_BLACK);
		tft.setCursor(0, 60);
		tft.println(i);
		delay(100);
	}
}