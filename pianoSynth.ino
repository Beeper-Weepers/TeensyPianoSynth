#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform13;     //xy=116,916
AudioSynthWaveform       waveform12;     //xy=117,868
AudioSynthWaveform       waveform16;     //xy=120,1091
AudioSynthWaveform       waveform11;     //xy=122,827
AudioSynthWaveform       waveform6;      //xy=123,592
AudioSynthWaveform       waveform14;     //xy=123,968
AudioSynthWaveform       waveform15;     //xy=123,1026
AudioSynthWaveform       waveform9;      //xy=125,739
AudioSynthWaveform       waveform8;      //xy=127,685
AudioSynthWaveform       waveform10;     //xy=128,779
AudioSynthWaveform       waveform7;      //xy=129,644
AudioSynthWaveform       waveform2;      //xy=133,387
AudioSynthWaveform       waveform4;      //xy=134,501
AudioSynthWaveform       waveform5;      //xy=135,546
AudioSynthWaveform       waveform3;      //xy=137,448
AudioSynthWaveform       waveform1;      //xy=138,333
AudioEffectMultiply      multiply6;      //xy=307,835
AudioEffectMultiply      multiply5;      //xy=308,758
AudioEffectMultiply      multiply3;      //xy=316,560
AudioEffectMultiply      multiply4;      //xy=316,673
AudioEffectMultiply      multiply7;      //xy=317,936
AudioEffectMultiply      multiply2;      //xy=320,477
AudioEffectMultiply      multiply8;      //xy=320,1057
AudioEffectMultiply      multiply1;      //xy=337,357
AudioEffectEnvelope      envelope1;      //xy=494,356
AudioEffectEnvelope      envelope2;      //xy=494,461
AudioEffectEnvelope      envelope5;      //xy=493,733
AudioEffectEnvelope      envelope4;      //xy=496,631
AudioEffectEnvelope      envelope6;      //xy=496,830
AudioEffectEnvelope      envelope8;      //xy=499,1057
AudioEffectEnvelope      envelope7;      //xy=504,933
AudioEffectEnvelope      envelope3;      //xy=517,524
AudioMixer4              mixer1;         //xy=721,518
AudioMixer4              mixer2;         //xy=739,882
AudioMixer4              mixer3;         //xy=923,675
AudioSynthWaveformDc     dc1;            //xy=1085,581
AudioSynthWaveformDc     dc2;            //xy=1089,742
AudioFilterStateVariable filter1;        //xy=1090,656
AudioEffectMultiply      multiply10;     //xy=1234,732
AudioEffectMultiply      multiply9;      //xy=1236,587
AudioMixer4              mixer4;         //xy=1384,668
AudioOutputI2S           i2s1;           //xy=1523,666
AudioConnection          patchCord1(waveform13, 0, multiply7, 0);
AudioConnection          patchCord2(waveform12, 0, multiply6, 1);
AudioConnection          patchCord3(waveform16, 0, multiply8, 1);
AudioConnection          patchCord4(waveform11, 0, multiply6, 0);
AudioConnection          patchCord5(waveform6, 0, multiply3, 1);
AudioConnection          patchCord6(waveform14, 0, multiply7, 1);
AudioConnection          patchCord7(waveform15, 0, multiply8, 0);
AudioConnection          patchCord8(waveform9, 0, multiply5, 0);
AudioConnection          patchCord9(waveform8, 0, multiply4, 1);
AudioConnection          patchCord10(waveform10, 0, multiply5, 1);
AudioConnection          patchCord11(waveform7, 0, multiply4, 0);
AudioConnection          patchCord12(waveform2, 0, multiply1, 1);
AudioConnection          patchCord13(waveform4, 0, multiply2, 1);
AudioConnection          patchCord14(waveform5, 0, multiply3, 0);
AudioConnection          patchCord15(waveform3, 0, multiply2, 0);
AudioConnection          patchCord16(waveform1, 0, multiply1, 0);
AudioConnection          patchCord17(multiply6, envelope6);
AudioConnection          patchCord18(multiply5, envelope5);
AudioConnection          patchCord19(multiply3, envelope3);
AudioConnection          patchCord20(multiply4, envelope4);
AudioConnection          patchCord21(multiply7, envelope7);
AudioConnection          patchCord22(multiply2, envelope2);
AudioConnection          patchCord23(multiply8, envelope8);
AudioConnection          patchCord24(multiply1, envelope1);
AudioConnection          patchCord25(envelope1, 0, mixer1, 0);
AudioConnection          patchCord26(envelope2, 0, mixer1, 1);
AudioConnection          patchCord27(envelope5, 0, mixer2, 0);
AudioConnection          patchCord28(envelope4, 0, mixer1, 3);
AudioConnection          patchCord29(envelope6, 0, mixer2, 1);
AudioConnection          patchCord30(envelope8, 0, mixer2, 3);
AudioConnection          patchCord31(envelope7, 0, mixer2, 2);
AudioConnection          patchCord32(envelope3, 0, mixer1, 2);
AudioConnection          patchCord33(mixer1, 0, mixer3, 0);
AudioConnection          patchCord34(mixer2, 0, mixer3, 1);
AudioConnection          patchCord35(mixer3, 0, filter1, 0);
AudioConnection          patchCord36(dc1, 0, multiply9, 0);
AudioConnection          patchCord37(dc2, 0, multiply10, 1);
AudioConnection          patchCord38(filter1, 0, multiply9, 1);
AudioConnection          patchCord39(filter1, 2, multiply10, 0);
AudioConnection          patchCord40(multiply10, 0, mixer4, 1);
AudioConnection          patchCord41(multiply9, 0, mixer4, 0);
AudioConnection          patchCord42(mixer4, 0, i2s1, 0);
AudioConnection          patchCord43(mixer4, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=159,1182
// GUItool: end automatically generated code


//Custom headers importing
//#include "BinaryDisplay.h"
#include "PlayManager.h"
//#include "FrequencyData.h"

#define ENVELOPE_COUNT 8
//Should be x2 the keyCount
#define WAVEFORM_COUNT 16

//Pin structures
/*#define buttonsSize 4
const int buttonPins[] = {36, 37, 38, 39};
Bounce* buttons[] = {new Bounce(), new Bounce(), new Bounce(), new Bounce()};*/

//Keys
#define INPUT_COUNT 8
#define POWER_COUNT 8
const int KEY_COUNT = INPUT_COUNT * POWER_COUNT;

int inputPins[INPUT_COUNT] = {32, 31, 30, 29, 28, 27, 26, 25};
int powerPins[POWER_COUNT] = {24, 33, 34, 35, 36, 37, 38, 39};

//#define ledsSize 4
//const int leds[ledsSize] = {24, 25, 26, 27};

//Object declaration
//BinaryDisplay displayer;
PlayManager manager;

//Audio structures
AudioEffectEnvelope *envelopes[] = {&envelope1, &envelope2, &envelope3, &envelope4, &envelope5, &envelope6, &envelope7, &envelope8};
AudioSynthWaveform *waveforms[WAVEFORM_COUNT] = {&waveform1, &waveform2, &waveform3, &waveform4, &waveform5, &waveform6, &waveform7, &waveform8, &waveform9, &waveform10, &waveform11, &waveform12, &waveform13, &waveform14, &waveform15, &waveform16};

//Current waveform type for each oscillator
int currentWav1 = 0;
int currentWav2 = 0;
#define waveTSize 4
const int waveTypes[] = { WAVEFORM_SINE, WAVEFORM_SAWTOOTH, WAVEFORM_SQUARE, WAVEFORM_TRIANGLE };

//High/Low Filter Mix
#define filterPot A10

//Notes
float notes[KEY_COUNT];
#define STARTING_NOTE 36 //C2

void setup() {
  AudioMemory(80);
  Serial.begin(9600);

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.8);

  //Setup static custom objects
  manager.setup(POWER_COUNT, INPUT_COUNT, ENVELOPE_COUNT, powerPins, inputPins, envelopes, waveforms, notes);
  //displayer.setup(ledsSize, leds);

  //Setup notes
  for (int i = 0; i < KEY_COUNT; i++) {
    notes[i] = 440.0f * pow(2.0, (float)(STARTING_NOTE + i - 69) * 0.0833333f);
  }
  
  //Setup waveforms
  const float wav1Volume = 4.0 / 3.0;
  for (int i = 0; i < ENVELOPE_COUNT; i++) {
    waveforms[i * 2]->begin(wav1Volume, 0, WAVEFORM_SINE);
    waveforms[i * 2 + 1]->begin(0.75, 0, WAVEFORM_SINE);
  }

  //Setup up buttons
  /*for (int i = 0; i < buttonsSize; i++) {
    pinMode(buttonPins[i], INPUT);
    buttons[i]->attach(buttonPins[i]);
    buttons[i]->interval(5);
  }*/

  //Setup filter
  filter1.frequency(350);
  filter1.resonance(0.6);
  filter1.octaveControl(1);
  dc1.amplitude(0.5);
  dc2.amplitude(0.5);

  //Turn onboard LED on
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
}


void loop() {
  manager.updatePatches();
  //displayer.updateLEDs();

/*
  //Scale shifting
  buttons[0]->update();
  if (buttons[0]->rose()) {
    currentScale += (currentScale + 1) % scaleCount;

    //Store scale inside temporary var to access within frequency loop
    const float *scale = scales[currentScale];
    
    for (int i = 0; i < keyCount; i++) {
      waveforms[i * 2]->frequency(scale[i]);
      waveforms[i * 2 + 1]->frequency(scale[i] / 2.0);
    }

    displayer.setValue(currentScale);
    
  }
  
  //Osc 1 type shifting
  buttons[1]->update();
  if (buttons[1]->rose()) {
    currentWav1 = (currentWav1 + 1) % waveTSize;

    for (int i = 0; i < keyCount; i++) {
      waveforms[i * 2]->begin(waveTypes[currentWav1]);
    } 

    displayer.setValue(currentWav1);
  }

  //Osc 2 type shifting
  buttons[2]->update();
  if (buttons[2]->rose()) {
    currentWav2 = (currentWav2 + 1) % waveTSize;

    for (int i = 0; i < keyCount; i++) {
      waveforms[i * 2 + 1]->begin(waveTypes[currentWav2]);
    } 

    displayer.setValue(currentWav2);
  }

  //Filter mixing
  float mixValue = (float) analogRead(filterPot) / 1024.0;
  dc1.amplitude(1.0 - mixValue, 20);
  dc2.amplitude(mixValue, 20);
*/
}

