/*
 * USB MIDI adapter.
 * 
 * ---
 * 
 * To allow larger sysex packages, modify the Control Surface library as follows:
 * 
 * In:
 * src\MIDI_Parsers\MIDI_MessageTypes.hpp
 * change:
 * uint8_t length;
 * to:
 * size_t length;
 * 
 * In:
 * src/Settings/Settings.hpp
 * change:
 * constexpr size_t SYSEX_BUFFER_SIZE = 128;
 * to:
 * constexpr size_t SYSEX_BUFFER_SIZE = 320;
 * 
 * This should be fixed when Control Surface 2.x will be released.
 * 
 * ---
 * 
 * To use a different USB device name, edit hardware/arduino/avr/boards.txt in your Arduino IDE install using admin privileges.
 * Change:
 * leonardo.build.usb_product="Arduino Leonardo"
 * to:
 * leonardo.build.usb_product="..."
 * change it back after uploading the project to your Arduino device.
 */

#include <Control_Surface.h> // Include the Control Surface library

USBMIDI_Interface midiusb;
// use this one instead to dump all MIDI data to the serial monitor
// USBDebugMIDI_Interface midiusb;
HardwareSerialMIDI_Interface midiser = {Serial1, MIDI_BAUD};

// Create a MIDI pipe factory to connect the MIDI interfaces to eachother and to the Control Surface
MIDI_PipeFactory<5> pipes;

// Example for adding extra controllers:
// CCPotentiometer pot = { A0, MIDI_CC::Expression_Controller };

// pin to which the power LED is connected
const int ledPin = 10;

// setup code
void setup() {
  Serial.begin(115200);

  // turn on the power LED
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  // forward MIDI USB to MIDI serial
  midiusb >> pipes >> midiser;
  // forward MIDI serial to MIDI USB
  midiser >> pipes >> midiusb;
  // send control suface messages only to MIDI USB
  Control_Surface >> pipes >> midiusb;

  // connect both MIDI USB and serial to control surface
  midiser >> pipes >> Control_Surface;
  midiusb >> pipes >> Control_Surface;

  // initialize Control Surface _after_ connecting the interfaces
  Control_Surface.begin();
}

// main processing loop
void loop() {
  Control_Surface.loop();
}
