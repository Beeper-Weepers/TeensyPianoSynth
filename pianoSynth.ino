#include <Bounce2.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform13;     //xy=360,649
AudioSynthWaveform       waveform12;     //xy=361,601
AudioSynthWaveform       waveform11;     //xy=366,560
AudioSynthWaveform       waveform6;      //xy=367,325
AudioSynthWaveform       waveform14;     //xy=367,701
AudioSynthWaveform       waveform9;      //xy=369,472
AudioSynthWaveform       waveform8;      //xy=371,418
AudioSynthWaveform       waveform10;     //xy=372,512
AudioSynthWaveform       waveform7;      //xy=373,377
AudioSynthWaveform       waveform2;      //xy=377,120
AudioSynthWaveform       waveform4;      //xy=378,234
AudioSynthWaveform       waveform5;      //xy=379,279
AudioSynthWaveform       waveform3;      //xy=381,181
AudioSynthWaveform       waveform1;      //xy=382,66
AudioEffectMultiply      multiply6;      //xy=551,568
AudioEffectMultiply      multiply5;      //xy=552,491
AudioEffectMultiply      multiply3;      //xy=560,293
AudioEffectMultiply      multiply4;      //xy=560,406
AudioEffectMultiply      multiply7;      //xy=561,669
AudioEffectMultiply      multiply2;      //xy=564,210
AudioEffectMultiply      multiply1;      //xy=581,90
AudioEffectEnvelope      envelope1;      //xy=738,89
AudioEffectEnvelope      envelope2;      //xy=738,194
AudioEffectEnvelope      envelope5;      //xy=737,466
AudioEffectEnvelope      envelope4;      //xy=740,364
AudioEffectEnvelope      envelope6;      //xy=740,563
AudioEffectEnvelope      envelope7;      //xy=748,666
AudioEffectEnvelope      envelope3;      //xy=761,257
AudioMixer4              mixer1;         //xy=976,197
AudioMixer4              mixer2;         //xy=989,500
AudioMixer4              mixer3;         //xy=1188,224
AudioFilterStateVariable filter1;        //xy=1326,224
AudioOutputI2S           i2s1;           //xy=1482,221
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
AudioControlSGTL5000     sgtl5000_1;     //xy=359,761
// GUItool: end automatically generated code

//Custom headers importing
#include "BinaryDisplay.h"
#include "PlayManager.h"
#include "FrequencyData.h"

#define keyCount 7
//Should be x2 the keyCount
#define waveformCount 14

//Pin structures
#define buttonsSize 4
const int buttonPins[] = {36, 37, 38, 39};
Bounce* buttons[] = {new Bounce(), new Bounce(), new Bounce(), new Bounce()};

const int keys[keyCount] = {31, 30, 33, 29, 28, 35, 32};

#define ledsSize 4
const int leds[ledsSize] = {24, 25, 26, 27};

//Object declaration
BinaryDisplay displayer;
PlayManager manager;

//Audio structures
AudioEffectEnvelope *envelopes[] = {&envelope1, &envelope2, &envelope3, &envelope4, &envelope5, &envelope6, &envelope7};
AudioSynthWaveform *waveforms[waveformCount] = {&waveform1, &waveform2, &waveform3, &waveform4, &waveform5, &waveform6, &waveform7, &waveform8, &waveform9, &waveform10, &waveform11, &waveform12, &waveform13, &waveform14};

//Current scale for keys
int currentScale = 0;

//Current waveform type for each oscillator
int currentWav1 = 0;
int currentWav2 = 0;
#define waveTSize 4
const int waveTypes[] = { WAVEFORM_SINE, WAVEFORM_SAWTOOTH, WAVEFORM_SQUARE, WAVEFORM_TRIANGLE };

void setup() {
  AudioMemory(80);
  Serial.begin(9600);

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.8);

  //Setup static custom objects
  manager.setup(keyCount, keys, envelopes, &displayer);
  displayer.setup(ledsSize, leds);
  
  //Setup waveforms
  for (int i = 0; i < keyCount; i++) {
    waveforms[i * 2]->begin(4.0 / 3.0, cMajor[i], WAVEFORM_SINE);
    waveforms[i * 2 + 1]->begin(0.75, cMajor[i] / 2.0, WAVEFORM_TRIANGLE);
  }

  //Setup up buttons
  for (int i = 0; i < buttonsSize; i++) {
    pinMode(buttonPins[i], INPUT);
    buttons[i]->attach(buttonPins[i]);
    buttons[i]->interval(5);
  }

  //Setup filter
  filter1.frequency(350);
  filter1.resonance(0.6);
  filter1.octaveControl(1);

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
}


void loop() {
  manager.updatePatches();
  displayer.updateLEDs();

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
  }

  //Osc 2 type shifting
  buttons[2]->update();
  if (buttons[2]->rose()) {
    currentWav2 = (currentWav2 + 1) % waveTSize;

    for (int i = 0; i < keyCount; i++) {
      waveforms[i * 2 + 1]->begin(waveTypes[currentWav2]);
    } 
  }
}
