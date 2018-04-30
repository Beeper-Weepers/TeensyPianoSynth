#include <Bounce2.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform4;      //xy=105,410
AudioSynthWaveform       waveform2;      //xy=106,356
AudioSynthWaveform       waveform3;      //xy=113,290
AudioSynthWaveform       waveform1;      //xy=118,240
AudioEffectMultiply      multiply1;      //xy=315,260
AudioEffectMultiply      multiply2;      //xy=315,376
AudioEffectEnvelope      envelope1;      //xy=469,270
AudioEffectEnvelope      envelope2;      //xy=471,368
AudioMixer4              mixer1;         //xy=711,242
AudioSynthWaveform       waveform5;      //xy=788,310
AudioEffectMultiply      multiply3;      //xy=904,236
AudioFilterStateVariable filter1;        //xy=1047,243
AudioEffectReverb        reverb1;        //xy=1195,241
AudioOutputI2S           i2s1;           //xy=1366,247
AudioConnection          patchCord1(waveform4, 0, multiply2, 1);
AudioConnection          patchCord2(waveform2, 0, multiply2, 0);
AudioConnection          patchCord3(waveform3, 0, multiply1, 1);
AudioConnection          patchCord4(waveform1, 0, multiply1, 0);
AudioConnection          patchCord5(multiply1, envelope1);
AudioConnection          patchCord6(multiply2, envelope2);
AudioConnection          patchCord7(envelope1, 0, mixer1, 0);
AudioConnection          patchCord8(envelope2, 0, mixer1, 1);
AudioConnection          patchCord9(mixer1, 0, multiply3, 0);
AudioConnection          patchCord10(waveform5, 0, multiply3, 1);
AudioConnection          patchCord11(multiply3, 0, filter1, 0);
AudioConnection          patchCord12(filter1, 0, reverb1, 0);
AudioConnection          patchCord13(reverb1, 0, i2s1, 0);
AudioConnection          patchCord14(reverb1, 0, i2s1, 1);
// GUItool: end automatically generated code


const int note1OnPin = 24;
const int note2OnPin = 25;
Bounce *note1OnBounce = new Bounce();
Bounce *note2OnBounce = new Bounce();
#define potPin A20

void setup() {
  AudioMemory(50);
  Serial.begin(9600);

  waveform1.begin(1.0, 440.0, WAVEFORM_SINE);
  waveform3.begin(1.0, 444.0 / 2, WAVEFORM_SINE);

  waveform2.begin(1.0, 493.88, WAVEFORM_SINE);
  waveform4.begin(1.0, 493.88 / 2, WAVEFORM_SINE);

  filter1.frequency(500);
  filter1.resonance(0.707);
  filter1.octaveControl(4);

  envelope1.hold(100);
  envelope2.hold(100);
  envelope1.decay(1500);
  envelope2.decay(1500);
  envelope1.sustain(0.0); //volume
  envelope2.sustain(0.0);
  envelope1.release(700);
  envelope2.release(700);

  waveform5.begin(1.0, 500, WAVEFORM_SAWTOOTH);

  reverb1.reverbTime(0.05);

  //Turn pot
  //pinMode(potPin, INPUT);

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
  //Filter update with pots
  int filterPot = analogRead(potPin);
  waveform5.frequency((filterPot / 1024.0) * 600.0);

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
