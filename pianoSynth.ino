#include <Bounce2.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform13;     //xy=95,668
AudioSynthWaveform       waveform12;     //xy=96,620
AudioSynthWaveform       waveform16;     //xy=99,843
AudioSynthWaveform       waveform11;     //xy=101,579
AudioSynthWaveform       waveform6;      //xy=102,344
AudioSynthWaveform       waveform14;     //xy=102,720
AudioSynthWaveform       waveform15;     //xy=102,778
AudioSynthWaveform       waveform9;      //xy=104,491
AudioSynthWaveform       waveform8;      //xy=106,437
AudioSynthWaveform       waveform10;     //xy=107,531
AudioSynthWaveform       waveform7;      //xy=108,396
AudioSynthWaveform       waveform2;      //xy=112,139
AudioSynthWaveform       waveform4;      //xy=113,253
AudioSynthWaveform       waveform5;      //xy=114,298
AudioSynthWaveform       waveform3;      //xy=116,200
AudioSynthWaveform       waveform1;      //xy=117,85
AudioEffectMultiply      multiply6;      //xy=286,587
AudioEffectMultiply      multiply5;      //xy=287,510
AudioEffectMultiply      multiply3;      //xy=295,312
AudioEffectMultiply      multiply4;      //xy=295,425
AudioEffectMultiply      multiply7;      //xy=296,688
AudioEffectMultiply      multiply2;      //xy=299,229
AudioEffectMultiply      multiply8;      //xy=299,809
AudioEffectMultiply      multiply1;      //xy=316,109
AudioEffectEnvelope      envelope1;      //xy=473,108
AudioEffectEnvelope      envelope2;      //xy=473,213
AudioEffectEnvelope      envelope5;      //xy=472,485
AudioEffectEnvelope      envelope4;      //xy=475,383
AudioEffectEnvelope      envelope6;      //xy=475,582
AudioEffectEnvelope      envelope8;      //xy=478,809
AudioEffectEnvelope      envelope7;      //xy=483,685
AudioEffectEnvelope      envelope3;      //xy=496,276
AudioMixer4              mixer1;         //xy=700,270
AudioMixer4              mixer2;         //xy=718,634
AudioMixer4              mixer3;         //xy=904,431
AudioEffectFlange        flange1;        //xy=1047,428
AudioEffectReverb        reverb1;        //xy=1189,433
AudioFilterStateVariable filter1;        //xy=1332,425
AudioMixer4              mixer5;         //xy=1469,411
AudioAmplifier           amp1;           //xy=1604,401
AudioOutputI2S           i2s1;           //xy=1747,400
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
AudioConnection          patchCord35(mixer3, flange1);
AudioConnection          patchCord36(flange1, reverb1);
AudioConnection          patchCord37(reverb1, 0, filter1, 0);
AudioConnection          patchCord38(filter1, 0, mixer5, 0);
AudioConnection          patchCord39(filter1, 1, mixer5, 1);
AudioConnection          patchCord40(filter1, 2, mixer5, 2);
AudioConnection          patchCord41(mixer5, amp1);
AudioConnection          patchCord42(amp1, 0, i2s1, 0);
AudioConnection          patchCord43(amp1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=105,934
// GUItool: end automatically generated code
 

//Custom headers importing
#include "PlayManager.h"

#define ENVELOPE_COUNT 8
//Should be x2 the keyCount
#define WAVEFORM_COUNT 16

//Pin structures
#define BUTTONS_SIZE 5
const uint8_t buttonPins[] = {42, 41, 54, 56, 57};
Bounce* buttons[] = {new Bounce(), new Bounce(), new Bounce(), new Bounce(), new Bounce()}; 

//Keys
#define INPUT_COUNT 8
#define POWER_COUNT 8
const uint8_t KEY_COUNT = INPUT_COUNT * POWER_COUNT; //If key count exceeds 256, change the type to int

int inputPins[INPUT_COUNT] = {32, 31, 30, 29, 28, 27, 26, 25};
int powerPins[POWER_COUNT] = {46, 33, 34, 35, 36, 37, 38, 39};

//Object declaration
PlayManager manager;

//Audio structures
AudioEffectEnvelope *envelopes[] = {&envelope1, &envelope2, &envelope3, &envelope4, &envelope5, &envelope6, &envelope7, &envelope8};
AudioSynthWaveform *waveforms[WAVEFORM_COUNT] = {&waveform1, &waveform2, &waveform3, &waveform4, &waveform5, &waveform6, &waveform7, &waveform8, &waveform9, &waveform10, &waveform11, &waveform12, &waveform13, &waveform14, &waveform15, &waveform16};

//Current waveform type for each oscillator
uint8_t currentWav1 = 0;
uint8_t currentWav2 = 0;
#define WAVE_T_SIZE 4
const int waveTypes[] = { WAVEFORM_SINE, WAVEFORM_SAWTOOTH, WAVEFORM_SQUARE, WAVEFORM_TRIANGLE };

//Pass filter settings
#define FILTER_COUNT 3
uint8_t currentFilter = 0;

//Reverb
#define REVERB_TIME 0.2
boolean reverbOn = false;

//Flange
#define FLANGE_DELAY_LENGTH (6*AUDIO_BLOCK_SAMPLES)
short delayLine[FLANGE_DELAY_LENGTH];
const int s_idx = FLANGE_DELAY_LENGTH/4;
const int s_depth = FLANGE_DELAY_LENGTH/4;
const double s_freq = .5;
boolean flangeOn = false;

//Potentiometer
#define VOLUME_POT A1
#define FREQ_POT A21
#define RES_POT A24

#define ATTACK_POT A10
#define DECAY_POT A23
#define SUSTAIN_POT A11
#define RELEASE_POT A22

//Notes
float notes[KEY_COUNT];
#define STARTING_NOTE 36 //C2

void setup() {
  //Allocate a (proper) amount of memory usage
  AudioMemory(30);
  
  Serial.begin(9600);

  sgtl5000_1.enable();
  sgtl5000_1.volume(1.0);

  //Setup static custom objects
  manager.setup(POWER_COUNT, INPUT_COUNT, ENVELOPE_COUNT, powerPins, inputPins, envelopes, waveforms, notes);

  //Setup notes
  for (uint8_t i = 0; i < KEY_COUNT; i++) {
    notes[i] = 440.0f * pow(2.0, (float)(STARTING_NOTE + i - 69) * 0.0833333f);
  }
  
  //Setup waveforms
  const float waveVolume = 1.0 / ENVELOPE_COUNT;
  for (uint8_t i = 0; i < ENVELOPE_COUNT; i++) {
    waveforms[i * 2]->begin(waveVolume, 0, WAVEFORM_SINE);
    waveforms[i * 2 + 1]->begin(waveVolume, 0, WAVEFORM_SINE);
  }

  //Setup up buttons
  for (int i = 0; i < BUTTONS_SIZE  ; i++) {
    pinMode(buttonPins[i], INPUT_PULLDOWN);
    buttons[i]->attach(buttonPins[i]);
    buttons[i]->interval(5);
  }

  //Setup filter
  filter1.frequency(2000);
  filter1.resonance(0.7);
  filter1.octaveControl(1);
  mixer5.gain(0, 1.0);
  mixer5.gain(1, 0.0);
  mixer5.gain(2, 0.0);

  //Set amplifications and volume levels
  amp1.gain(4.0);

  //Flange
  flange1.begin(delayLine,FLANGE_DELAY_LENGTH,s_idx,s_depth,s_freq);
  flange1.voices(FLANGE_DELAY_PASSTHRU,0,0);

  //Reverb
  reverb1.reverbTime(0);
  
  //Turn onboard LED on
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
}


void loop() {
  manager.updatePatches();
  
  //Osc 1 type shifting
  buttons[0]->update();
  if (buttons[0]->rose()) {
    currentWav1 = (currentWav1 + 1) % WAVE_T_SIZE;

    AudioNoInterrupts();
    for (int i = 0; i < ENVELOPE_COUNT; i++) {
      waveforms[i * 2]->begin(waveTypes[currentWav1]);
    }
    AudioInterrupts();

  }

  //Osc 2 type shifting
  buttons[1]->update();
  if (buttons[1]->rose()) {
    currentWav2 = (currentWav2 + 1) % WAVE_T_SIZE;

    AudioNoInterrupts();
    for (int i = 0; i < ENVELOPE_COUNT; i++) {
      waveforms[i * 2 + 1]->begin(waveTypes[currentWav2]);
    } 
    AudioInterrupts();

  }

  //Filter type shifting
  buttons[2]->update();
  if (buttons[2]->rose()) {
    Serial.println("filter");
    currentFilter = (currentFilter + 1) % FILTER_COUNT;
    for (uint8_t i = 0; i < FILTER_COUNT; i++) {
      mixer5.gain(i, 0.0);
    }
    mixer5.gain(currentFilter, 1.0);
  }

  //Reverb toggle
  buttons[3]->update();
  if (buttons[3]->rose()) {
    Serial.println("reverb");
    AudioNoInterrupts();
    reverbOn = !reverbOn;
    if (reverbOn) {
      reverb1.reverbTime(REVERB_TIME);
      //May have to halve the mixer3 inputs later on to reduce clipping
    } else {
      reverb1.reverbTime(0);
    }
    AudioInterrupts();
  }

  //Flange toggle
  buttons[4]->update();
  if (buttons[4]->rose()) {
    Serial.println("Flange");
    flangeOn = !flangeOn;
    AudioNoInterrupts();
    if (flangeOn) {
      flange1.voices(s_idx,s_depth,s_freq);  
    } else {
      flange1.voices(FLANGE_DELAY_PASSTHRU,0,0);
    }
    AudioInterrupts();
  }

  //Volume
  float volVal = ((analogRead(VOLUME_POT) >> 2) << 2) / 1024.0;
  sgtl5000_1.volume(volVal);

  //Filter Frequency (0 to 2000)
  float freqVal = ((((1024 - analogRead(FREQ_POT)) >> 3) << 3) / 1024.0) * 2000.0;
  filter1.frequency(freqVal);

  //Filter Resonance (0.7 to 5.0)
  float resVal = (((28 - analogRead(RES_POT)) / 28.0) + 0.7) * 5.0 - 0.7;
  filter1.resonance(resVal);

  //ADSR Potentiometers
  float attackValue = (analogRead(ATTACK_POT) / 1024.0) * 300.0; // ms (0 - 300)
  float decayValue = (analogRead(DECAY_POT) / 1024.0) * 300.0; // ms (0 - 300)
  float sustainValue = (float) (1024 - analogRead(SUSTAIN_POT)) / 1024.0;
  float releaseValue = ((float) (1024 - analogRead(RELEASE_POT)) / 1024.0) * 1000.0; // ms (0 - 1000)
  for (uint8_t i = 0; i < ENVELOPE_COUNT; i++) { 
    envelopes[i]->attack(attackValue);
    envelopes[i]->decay(decayValue);
    envelopes[i]->sustain(sustainValue);
    envelopes[i]->release(releaseValue);
  }

  Serial.print(volVal);
  Serial.print("  ");
  Serial.print(attackValue);
  Serial.print("  ");
  Serial.print(decayValue);
  Serial.print("  ");
  Serial.print(sustainValue);
  Serial.print("  ");
  Serial.print(releaseValue);
  Serial.print("  ");
  Serial.print(freqVal);
  Serial.print("  ");
  Serial.println(resVal); 
}

