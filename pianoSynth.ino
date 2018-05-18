#include <Bounce2.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform13;     //xy=150,703
AudioSynthWaveform       waveform12;     //xy=151,655
AudioSynthWaveform       waveform11;     //xy=156,614
AudioSynthWaveform       waveform6;      //xy=157,379
AudioSynthWaveform       waveform14;     //xy=157,755
AudioSynthWaveform       waveform9;      //xy=159,526
AudioSynthWaveform       waveform8;      //xy=161,472
AudioSynthWaveform       waveform10;     //xy=162,566
AudioSynthWaveform       waveform7;      //xy=163,431
AudioSynthWaveform       waveform2;      //xy=167,174
AudioSynthWaveform       waveform4;      //xy=168,288
AudioSynthWaveform       waveform5;      //xy=169,333
AudioSynthWaveform       waveform3;      //xy=171,235
AudioSynthWaveform       waveform1;      //xy=172,120
AudioEffectMultiply      multiply6;      //xy=341,622
AudioEffectMultiply      multiply5;      //xy=342,545
AudioEffectMultiply      multiply3;      //xy=350,347
AudioEffectMultiply      multiply4;      //xy=350,460
AudioEffectMultiply      multiply7;      //xy=351,723
AudioEffectMultiply      multiply2;      //xy=354,264
AudioEffectMultiply      multiply1;      //xy=371,144
AudioEffectEnvelope      envelope1;      //xy=528,143
AudioEffectEnvelope      envelope2;      //xy=528,248
AudioEffectEnvelope      envelope5;      //xy=527,520
AudioEffectEnvelope      envelope4;      //xy=530,418
AudioEffectEnvelope      envelope6;      //xy=530,617
AudioEffectEnvelope      envelope7;      //xy=538,720
AudioEffectEnvelope      envelope3;      //xy=551,311
AudioMixer4              mixer1;         //xy=766,251
AudioMixer4              mixer2;         //xy=779,554
AudioMixer4              mixer3;         //xy=978,278
AudioFilterStateVariable filter1;        //xy=1116,278
AudioOutputI2S           i2s1;           //xy=1272,275
AudioConnection          patchCord1(waveform13, 0, multiply7, 0);
AudioConnection          patchCord2(waveform12, 0, multiply6, 1);
AudioConnection          patchCord3(waveform11, 0, multiply6, 0);
AudioConnection          patchCord4(waveform6, 0, multiply3, 1);
AudioConnection          patchCord5(waveform14, 0, multiply7, 1);
AudioConnection          patchCord6(waveform9, 0, multiply5, 0);
AudioConnection          patchCord7(waveform8, 0, multiply4, 1);
AudioConnection          patchCord8(waveform10, 0, multiply5, 1);
AudioConnection          patchCord9(waveform7, 0, multiply4, 0);
AudioConnection          patchCord10(waveform2, 0, multiply1, 1);
AudioConnection          patchCord11(waveform4, 0, multiply2, 1);
AudioConnection          patchCord12(waveform5, 0, multiply3, 0);
AudioConnection          patchCord13(waveform3, 0, multiply2, 0);
AudioConnection          patchCord14(waveform1, 0, multiply1, 0);
AudioConnection          patchCord15(multiply6, envelope6);
AudioConnection          patchCord16(multiply5, envelope5);
AudioConnection          patchCord17(multiply3, envelope3);
AudioConnection          patchCord18(multiply4, envelope4);
AudioConnection          patchCord19(multiply7, envelope7);
AudioConnection          patchCord20(multiply2, envelope2);
AudioConnection          patchCord21(multiply1, envelope1);
AudioConnection          patchCord22(envelope1, 0, mixer1, 0);
AudioConnection          patchCord23(envelope2, 0, mixer1, 1);
AudioConnection          patchCord24(envelope5, 0, mixer2, 0);
AudioConnection          patchCord25(envelope4, 0, mixer1, 3);
AudioConnection          patchCord26(envelope6, 0, mixer2, 1);
AudioConnection          patchCord27(envelope7, 0, mixer2, 2);
AudioConnection          patchCord28(envelope3, 0, mixer1, 2);
AudioConnection          patchCord29(mixer1, 0, mixer3, 0);
AudioConnection          patchCord30(mixer2, 0, mixer3, 1);
AudioConnection          patchCord31(mixer3, 0, filter1, 0);
AudioConnection          patchCord32(filter1, 0, i2s1, 0);
AudioConnection          patchCord33(filter1, 0, i2s1, 1);
// GUItool: end automatically generated code


//Custom headers importing
#include "BinaryDisplay.h"
#include "PlayManager.h"
#include "FrequencyData.h"

#define keyCount 7
//Should be x2 the keyCount
#define waveformCount 14

//Pin structures
const int buttons[] = {36, 37, 38, 39};
#define ledsSize 4
const int leds[ledsSize] = {24, 25, 26, 27};
const int keys[keyCount] = {29, 28, 35, 32, 31, 30, 33};

//Object declaration
BinaryDisplay displayer;
PlayManager manager;

//Audio structures
AudioEffectEnvelope *envelopes[] = {&envelope1, &envelope2, &envelope3, &envelope4, &envelope5, &envelope6, &envelope7};
AudioSynthWaveform *waveforms[waveformCount] = {&waveform1, &waveform2, &waveform3, &waveform4, &waveform5, &waveform6, &waveform7, &waveform8, &waveform9, &waveform10, &waveform11, &waveform12, &waveform13, &waveform14};

//Frequencies for keys
const float scale[] = { NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4 };

void setup() {
  AudioMemory(60);
  Serial.begin(9600);

  //Setup static custom objects
  manager.setup(keyCount, keys, envelopes);
  displayer.setup(ledsSize, leds);
  
  //Setup waveforms
  for (int i = 0; i < keyCount; i++) {
    waveforms[i * 2]->begin(1.0, scale[i], WAVEFORM_SINE);
    waveforms[i * 2 + 1]->begin(1.0, scale[i] / 2.0, WAVEFORM_SINE);
  }

  //Setup filter
  filter1.frequency(400);
  filter1.resonance(0.7);
  filter1.octaveControl(1);

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
}


void loop() {
  manager.updatePatches();
  displayer.updateLEDs();
}
