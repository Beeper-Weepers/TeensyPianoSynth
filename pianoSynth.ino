#include <Bounce2.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "BinaryDisplay.h"

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform2;      //xy=116,453
AudioSynthWaveform       waveform3;      //xy=117,374
AudioSynthWaveform       waveform4;      //xy=117,494
AudioSynthWaveform       waveform1;      //xy=118,335
AudioEffectMultiply      multiply2;      //xy=261,482
AudioEffectMultiply      multiply1;      //xy=274,352
AudioEffectEnvelope      envelope2;      //xy=399,449
AudioEffectEnvelope      envelope1;      //xy=434,371
AudioMixer4              mixer1;         //xy=633,387
AudioFilterStateVariable filter1;        //xy=763,387
AudioOutputI2S           i2s1;           //xy=899,380
AudioConnection          patchCord1(waveform2, 0, multiply2, 0);
AudioConnection          patchCord2(waveform3, 0, multiply1, 1);
AudioConnection          patchCord3(waveform4, 0, multiply2, 1);
AudioConnection          patchCord4(waveform1, 0, multiply1, 0);
AudioConnection          patchCord5(multiply2, envelope2);
AudioConnection          patchCord6(multiply1, envelope1);
AudioConnection          patchCord7(envelope2, 0, mixer1, 1);
AudioConnection          patchCord8(envelope1, 0, mixer1, 0);
AudioConnection          patchCord9(mixer1, 0, filter1, 0);
AudioConnection          patchCord10(mixer1, 0, filter1, 1);
AudioConnection          patchCord11(filter1, 0, i2s1, 0);
AudioConnection          patchCord12(filter1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=234,584
// GUItool: end automatically generated code


const int note1OnPin = 24;
const int note2OnPin = 25;
Bounce *note1OnBounce = new Bounce();
Bounce *note2OnBounce = new Bounce();


void setup() {
  AudioMemory(18);
  Serial.begin(9600);
  
  waveform1.begin(1.0, 440.0, WAVEFORM_SINE);
  waveform3.begin(1.0, 444.0 / 2, WAVEFORM_SINE);
  
  waveform2.begin(1.0, 493.88, WAVEFORM_SINE);
  waveform4.begin(1.0, 493.88 / 2, WAVEFORM_SINE);
  
  filter1.frequency(400);
  filter1.resonance(0.7);
  filter1.octaveControl(1);

  pinMode(note1OnPin, INPUT);  
  //digitalWrite(inputPin ,HIGH);
  note1OnBounce->attach(note1OnPin);
  note1OnBounce->interval(5);

  pinMode(note2OnPin, INPUT);  
  //digitalWrite(inputPin ,HIGH);
  note2OnBounce->attach(note2OnPin);
  note2OnBounce->interval(5);
}


void loop() {
  //Turn on note if the button rose and off if it fell
  note1OnBounce->update();
  if (note1OnBounce->rose()) {
    envelope1.noteOn();
  } else if (note1OnBounce->fell()) {
    envelope1.noteOff();
  }

  //Turn on note if the button rose and off if it fell
  note2OnBounce->update();
  if (note2OnBounce->rose()) {
    envelope2.noteOn();
  } else if (note2OnBounce->fell()) {
    envelope2.noteOff();
  }
}
