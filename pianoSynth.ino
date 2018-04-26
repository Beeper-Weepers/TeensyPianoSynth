#include <Bounce2.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform2;      //xy=167,179
AudioSynthWaveform       waveform4;      //xy=167,245
AudioSynthWaveform       waveform1;      //xy=169,53
AudioSynthWaveform       waveform3;      //xy=172,115
AudioEffectMultiply      multiply1;      //xy=348,83
AudioEffectMultiply      multiply2;      //xy=351,192
AudioEffectEnvelope      envelope2;      //xy=507,199
AudioEffectEnvelope      envelope1;      //xy=511,87
AudioMixer4              mixer1;         //xy=646,146
AudioFilterStateVariable filter1;        //xy=800,244
AudioOutputI2S           i2s1;           //xy=959,238
AudioConnection          patchCord1(waveform2, 0, multiply2, 0);
AudioConnection          patchCord2(waveform4, 0, multiply2, 1);
AudioConnection          patchCord3(waveform1, 0, multiply1, 0);
AudioConnection          patchCord4(waveform3, 0, multiply1, 1);
AudioConnection          patchCord5(multiply1, envelope1);
AudioConnection          patchCord6(multiply2, envelope2);
AudioConnection          patchCord7(envelope2, 0, mixer1, 1);
AudioConnection          patchCord8(envelope1, 0, mixer1, 0);
AudioConnection          patchCord9(mixer1, 0, filter1, 0);
AudioConnection          patchCord10(filter1, 1, i2s1, 0);
AudioConnection          patchCord11(filter1, 1, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=646,28
// GUItool: end automatically generated code


const int note1OnPin = 24;
const int note2OnPin = 25;
Bounce *note1OnBounce = new Bounce();
Bounce *note2OnBounce = new Bounce();
#define potPin A20

void setup() {
  AudioMemory(30);
  Serial.begin(9600);

  waveform1.begin(1.0, 440.0, WAVEFORM_SINE);
  waveform3.begin(1.0, 444.0 / 2, WAVEFORM_SINE);

  waveform2.begin(1.0, 493.88, WAVEFORM_SINE);
  waveform4.begin(1.0, 493.88 / 2, WAVEFORM_SINE);

  filter1.frequency(400);
  filter1.resonance(0.7);
  filter1.octaveControl(1);

  envelope1.hold(50);
  envelope2.hold(50);
  envelope1.decay(100);
  envelope2.decay(100);
  envelope1.sustain(0.4);
  envelope2.sustain(0.4);

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
  filter1.frequency((filterPot / 1024.0) * 500.0);
  Serial.println(filterPot);

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
